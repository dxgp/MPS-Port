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
    SUBCASE("Rectangular Matrix Decomposition (5x3)"){

        std::vector<float> data;
        MPS::Matrix* source_mat = MPS::Matrix::alloc();source_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 3, 12, MPS::MPSDataTypeFloat32));
        MPS::Matrix* result_mat = MPS::Matrix::alloc();result_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 3, 12, MPS::MPSDataTypeFloat32));
        MPS::Matrix* pivot_indices = MPS::Matrix::alloc();pivot_indices->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(1, 3, 12, MPS::MPSDataTypeUInt32));
        MTL::Buffer* buf = device->newBuffer(4, MTL::ResourceStorageModeShared);

        //random data generation
        generateRandomFloatData(source_mat->data(), data);
        
        //eigen part
        Eigen::MatrixXf sourceMatrix = Eigen::Map<Eigen::MatrixXf>(data.data(), 5, 3).transpose();
        Eigen::FullPivLU<Eigen::MatrixXf> luDecomp(sourceMatrix);
        Eigen::MatrixXf lowerTriangularMatrix = luDecomp.matrixLU().triangularView<Eigen::Lower>();
        Eigen::MatrixXf upperTriangularMatrix = luDecomp.matrixLU().triangularView<Eigen::StrictlyUpper>();
        Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> permutationMatrix = luDecomp.permutationP();
        Eigen::VectorXi permutationIndices = permutationMatrix.indices();

        std::cout<<"REACHED"<<std::endl;
        // metal part
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
        MPS::MatrixDecompositionLU* lu_decomp = MPS::MatrixDecompositionLU::alloc();
        lu_decomp->initWithDevice(device, 5, 3);
        lu_decomp->encodeToCommandBuffer(cmdBuffer, source_mat, result_mat, pivot_indices, buf);
        cmdBuffer->commit();
        cmdBuffer->waitUntilCompleted();

        Eigen::MatrixXf eigen_result = (upperTriangularMatrix + lowerTriangularMatrix).transpose();

        std::cout<<eigen_result<<std::endl;
        printMTLBuffer(result_mat->data(), "Result");
        std::cout<<"MTL Code return: "<<(((MPS::MatrixDecompositionStatus *) buf->contents())[0])<<std::endl;
        printMTLBuffer(source_mat->data(), "input");
        CHECK(verifyDecompositionResult(result_mat->data(), eigen_result.data()));
    }
}
TEST_CASE("Testing Cholesky Decomposition"){
    SUBCASE("Square Matrix Decomposition"){

    }
    SUBCASE("Rectangular Matrix Decomposition"){

    }
}