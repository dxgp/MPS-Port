// this block is for resolving an issue with M1 intellisense and eigen
#if __INTELLISENSE__
#undef __ARM_NEON
#undef __ARM_NEON__
#endif
#include "common_test.hpp"
#include <Eigen/Dense>
#include <Eigen/LU>
#include "../metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixDecomposition.hpp"
#include "../metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

MTL::Device* device = MTL::CreateSystemDefaultDevice();

bool verifyDecompositionResult(MTL::Buffer* buffer, float* matrix_val){
    float* buffer_vals = (float*) buffer->contents();
    for(int i=0;i<(buffer->length()/4); i++){
        if(!areEqual(buffer_vals[i], matrix_val[i])){
            std::cout<<buffer_vals[i]<<" ---- "<<matrix_val[i]<<std::endl;
            return false;
        }
    }
    return true;
}
bool compareBuffers(MTL::Buffer* b1, MTL::Buffer* b2){
    float* b1_vals = (float*)b1->contents();
    float* b2_vals = (float*)b2->contents();
    for(int i=0; i<b1->length()/4;i++){
        if(!areEqual(b1_vals[i], b2_vals[i])){
            return false;
        }
    }
    return true;
}
void removeElementsAboveDiagonal(float* matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = i + 1; j < columns; j++) {
            matrix[i * columns + j] = 0.0;
        }
    }
}

TEST_CASE("Testing LU Decomposition"){
    SUBCASE("Square Matrix Decomposition (5x5)"){
        srand(50);
        rand();
        rand();

        std::vector<float> data;
        MPS::Matrix* source_mat = MPS::Matrix::alloc();source_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
        MPS::Matrix* result_mat = MPS::Matrix::alloc();result_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
        MPS::Matrix* pivot_indices = MPS::Matrix::alloc();pivot_indices->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(1, 5, 20, MPS::MPSDataTypeUInt32));
        MTL::Buffer* buf = device->newBuffer(4, MTL::ResourceStorageModeShared);

        //random data generation
        generateRandomFloatData(source_mat->data(), data);

        //eigen part
        Eigen::MatrixXf sourceMatrix = Eigen::Map<Eigen::MatrixXf>(data.data(), 5, 5).transpose();
        Eigen::PartialPivLU<Eigen::MatrixXf> luDecomp(sourceMatrix);
        Eigen::MatrixXf lowerTriangularMatrix = luDecomp.matrixLU().triangularView<Eigen::Lower>();
        Eigen::MatrixXf upperTriangularMatrix = luDecomp.matrixLU().triangularView<Eigen::StrictlyUpper>();
        Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> permutationMatrix = luDecomp.permutationP();
        Eigen::VectorXi permutationIndices = permutationMatrix.indices();


        // metal part
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
        MPS::MatrixDecompositionLU* lu_decomp = MPS::MatrixDecompositionLU::alloc();
        lu_decomp->initWithDevice(device, 5, 5);
        lu_decomp->encodeToCommandBuffer(cmdBuffer, source_mat, result_mat, pivot_indices, buf);
        cmdBuffer->commit();
        cmdBuffer->waitUntilCompleted();

        Eigen::MatrixXf eigen_result = (upperTriangularMatrix + lowerTriangularMatrix).transpose();

        CHECK(verifyDecompositionResult(result_mat->data(), eigen_result.data()));
    }
}
TEST_CASE("Testing Cholesky Decomposition"){
    SUBCASE("Square Matrix Decomposition (5x5)"){
        srand(100);
        std::vector<float> data;
        MPS::Matrix* source_mat = MPS::Matrix::alloc();source_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
        MPS::Matrix* source_psd = MPS::Matrix::alloc();source_psd->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
        MPS::Matrix* result_mat = MPS::Matrix::alloc();result_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
        MPS::Matrix* pivot_indices = MPS::Matrix::alloc();pivot_indices->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(1, 5, 20, MPS::MPSDataTypeUInt32));


        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* psdGenCmdBuf = cmdQueue->commandBuffer();
        MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();mps_matmul->initWithDevice(device,false, true, 5, 5, 5, 1.0, 0.0);
        generateRandomFloatData(source_mat->data());
        mps_matmul->encodeToCommandBuffer(psdGenCmdBuf, source_mat, source_mat, source_psd);
        psdGenCmdBuf->commit();
        psdGenCmdBuf->waitUntilCompleted();
        MPS::MatrixDecompositionCholesky* cholesky_decmp = MPS::MatrixDecompositionCholesky::alloc();
        MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
        cholesky_decmp->initWithDevice(device, true, 5);
        cholesky_decmp->encodeToCommandBuffer(cmdBuffer, source_psd, result_mat, nullptr);
        cmdBuffer->commit();
        cmdBuffer->waitUntilCompleted();
        removeElementsAboveDiagonal(((float *)result_mat->data()->contents()), 5, 5);


        MPS::Matrix* reconstructed_mat = MPS::Matrix::alloc();reconstructed_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
        MTL::CommandBuffer* reconstructCmdBuf = cmdQueue->commandBuffer();
        MPS::MatrixMultiplication* reconstruct_matmul = MPS::MatrixMultiplication::alloc();reconstruct_matmul->initWithDevice(device, false, true, 5, 5, 5, 1.0, 0.0);
        reconstruct_matmul->encodeToCommandBuffer(reconstructCmdBuf, result_mat, result_mat, reconstructed_mat);
        reconstructCmdBuf->commit();
        reconstructCmdBuf->waitUntilCompleted();
        
        CHECK(compareBuffers(source_psd->data(), reconstructed_mat->data()));
        // Interesting how metal's cholesky doesn't actually remove elements above the diagonal on its own.
    }
}