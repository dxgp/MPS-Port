#include"common_test.hpp"
#include "../metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"

bool matmul_verify(MTL::Buffer* mat1, MTL::Buffer* mat2, MTL::Buffer* rmat, int M, int N, int K){
    float *fmat1 = (float *)mat1->contents();
    float *fmat2 = (float *)mat2->contents();
    float *frmat = (float *)rmat->contents();
    float *rvals = new float[rmat->length()/sizeof(float)];
    vDSP_mmul(fmat1, 1, fmat2, 1, rvals, 1, M, N, K);
    for(int i=0; i<M*N; i++){
        if(!areEqual(frmat[i], rvals[i])){
            return false;
        }
    }
    return true;
}

// =========================================== START: MATRIX & VECTOR CREATION ============================================
MTL::Device* dev = MTL::CreateSystemDefaultDevice();
//test for creating MatrixDescriptor
TEST_CASE("MatrixDescriptor creation"){
    MPS::MatrixDescriptor* matrix_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(30, 45, 180, MPS::MPSDataTypeFloat32);
    CHECK(matrix_des->rows() == 30);
    CHECK(matrix_des->columns() == 45);
    CHECK(matrix_des->rowBytes() == 180);
    CHECK(matrix_des->matrixBytes() == 5400);
}
//test for creating a VectorDescriptor
TEST_CASE("VectorDescriptor creation"){
    MPS::VectorDescriptor* vector_des = MPS::VectorDescriptor::vectorDescriptorWithLength(100, MPS::MPSDataTypeFloat32);
    CHECK(vector_des->length() == 100);
    CHECK(vector_des->vectors() == 1);
    CHECK(vector_des->vectorBytes() == 400);
}
//test for matrix creation
TEST_CASE("Matrix Creation"){
    MPS::MatrixDescriptor* matrix_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(30, 45, 180, MPS::MPSDataTypeFloat32);
    // min size of buffer (descriptor.rows-1) * descriptor.rowBytes + descriptor.columns * (element size)
    SUBCASE("Using initWithBuffer, no offser"){
        MTL::Buffer* buf = dev->newBuffer((matrix_des->rows() - 1)*matrix_des->rowBytes() + matrix_des->columns()*4, MTL::ResourceStorageModeShared);
        MPS::Matrix* matrix = MPS::Matrix::alloc();
        matrix->initWithBuffer(buf, matrix_des);
        CHECK(matrix->rows() == 30);
        CHECK(matrix->columns() == 45);
        CHECK(matrix->matrices() == 1);
        CHECK(matrix->rowBytes()==matrix_des->rowBytes());
    }
    SUBCASE("Using initWithBuffer, offset specified"){
        MTL::Buffer* buf = dev->newBuffer((matrix_des->rows() - 1)*matrix_des->rowBytes() + matrix_des->columns()*4 + 1, MTL::ResourceStorageModeShared);
        MPS::Matrix* matrix = MPS::Matrix::alloc();
        matrix->initWithBuffer(buf, 1, matrix_des);
        CHECK(matrix->rows() == 30);
        CHECK(matrix->columns() == 45);
        CHECK(matrix->matrices() == 1);
        CHECK(matrix->rowBytes() == matrix_des->rowBytes());
        CHECK(matrix->offset() == 1);
    }
    SUBCASE("Using initWithDevice"){
        // MTL::Buffer* buf = dev->newBuffer((matrix_des->rows() - 1)*matrix_des->rowBytes() + matrix_des->columns()*4, MTL::ResourceStorageModeShared);
        MPS::Matrix* matrix = MPS::Matrix::alloc();
        matrix->initWithDevice(dev, matrix_des);
        CHECK(matrix->rows() == 30);
        CHECK(matrix->columns() == 45);
        CHECK(matrix->matrices() == 1);
        CHECK(matrix->rowBytes()==matrix_des->rowBytes());
    }
}
//test for vector creation
TEST_CASE("Vector Creation"){
    MPS::VectorDescriptor* vector_des = MPS::VectorDescriptor::vectorDescriptorWithLength(100, MPS::MPSDataTypeFloat32);
    SUBCASE("Using initWithBuffer, no offset"){
        MTL::Buffer* buf = dev->newBuffer(400, MTL::ResourceStorageModeShared);
        MPS::Vector* vector = MPS::Vector::alloc();
        vector->initWithBuffer(buf, vector_des);
        CHECK(vector->length() == 100);
        CHECK(vector->vectors() == 1);
        CHECK(vector->vectorBytes() == 400);
    }
    SUBCASE("Using initWithBuffer, offset specified"){
        MTL::Buffer* buf = dev->newBuffer(403, MTL::ResourceStorageModeShared);
        MPS::Vector* vector = MPS::Vector::alloc();
        vector->initWithBuffer(buf, 3, vector_des);
        CHECK(vector->length() == 100);
        CHECK(vector->vectors() == 1);
        CHECK(vector->vectorBytes() == 400);
        // when specifying offset, make sure it matches with the size of the buffer as well as the number of elements specified.
        CHECK(vector->offset() == 3);
    }
    SUBCASE("Using initWithDevice"){
        MTL::Buffer* buf = dev->newBuffer(400, MTL::ResourceStorageModeShared);
        MPS::Vector* vector = MPS::Vector::alloc();
        vector->initWithDevice(dev, vector_des);
        CHECK(vector->length() == 100);
        CHECK(vector->vectors() == 1);
        CHECK(vector->vectorBytes() == 400);
    }
}
TEST_CASE("Creating a matrix multiplication object"){
    MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
    SUBCASE("Initializing with alpha and beta"){
        mps_matmul->initWithDevice(dev, false, false, 30, 90, 45, 1.0, 0.0);
        CHECK(mps_matmul!=nullptr);
    }
    SUBCASE("Initializing without alpha and beta"){
        mps_matmul->initWithDevice(dev, 30, 90, 45);
        CHECK(mps_matmul!=nullptr);
    }
}


// =========================================== END: MATRIX & VECTOR CREATION ============================================


// =========================================== START: MATRIX & VECTOR MULT. ============================================
TEST_CASE("Performing a matrix-matrix multiplication"){
    MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
    SUBCASE("4x4 with 4x4"){
        MPS::MatrixDescriptor* mat1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);
        MPS::MatrixDescriptor* mat2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);
        MPS::MatrixDescriptor* rmat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);
        MPS::Matrix* mat1 = MPS::Matrix::alloc(); mat1->initWithDevice(dev, mat1_des);
        MPS::Matrix* mat2 = MPS::Matrix::alloc(); mat2->initWithDevice(dev, mat2_des);
        MPS::Matrix* rmat = MPS::Matrix::alloc(); rmat->initWithDevice(dev, rmat_des);
        generateRandomFloatData(mat1->data());
        generateRandomFloatData(mat2->data());
        MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
        MTL::CommandBuffer* cmdBuf = cmdQueue->commandBuffer();
        mps_matmul->initWithDevice(dev, 4, 4, 4);
        mps_matmul->encodeToCommandBuffer(cmdBuf, mat1, mat2, rmat);
        cmdBuf->commit();
        cmdBuf->waitUntilCompleted();
        CHECK(matmul_verify(mat1->data(), mat2->data(), rmat->data(), 4, 4, 4) == true);
    }
    SUBCASE("4x3 with 3x5"){
        MPS::MatrixDescriptor* mat1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 3, 12, MPS::MPSDataTypeFloat32);
        MPS::MatrixDescriptor* mat2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(3, 5, 20, MPS::MPSDataTypeFloat32);
        MPS::MatrixDescriptor* rmat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 5, 20, MPS::MPSDataTypeFloat32);
        MPS::Matrix* mat1 = MPS::Matrix::alloc(); mat1->initWithDevice(dev, mat1_des);
        MPS::Matrix* mat2 = MPS::Matrix::alloc(); mat2->initWithDevice(dev, mat2_des);
        MPS::Matrix* rmat = MPS::Matrix::alloc(); rmat->initWithDevice(dev, rmat_des);
        generateRandomFloatData(mat1->data());
        generateRandomFloatData(mat2->data());
        MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
        MTL::CommandBuffer* cmdBuf = cmdQueue->commandBuffer();
        mps_matmul->initWithDevice(dev, 4, 5, 3);
        mps_matmul->encodeToCommandBuffer(cmdBuf, mat1, mat2, rmat);
        cmdBuf->commit();
        cmdBuf->waitUntilCompleted();
        CHECK(matmul_verify(mat1->data(), mat2->data(), rmat->data(), 4, 5, 3));
    }
    SUBCASE("4x1 with 1x5"){
        MPS::MatrixDescriptor* mat1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 1, 4, MPS::MPSDataTypeFloat32);
        MPS::MatrixDescriptor* mat2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(1, 5, 20, MPS::MPSDataTypeFloat32);
        MPS::MatrixDescriptor* rmat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 5, 20, MPS::MPSDataTypeFloat32);
        MPS::Matrix* mat1 = MPS::Matrix::alloc(); mat1->initWithDevice(dev, mat1_des);
        MPS::Matrix* mat2 = MPS::Matrix::alloc(); mat2->initWithDevice(dev, mat2_des);
        MPS::Matrix* rmat = MPS::Matrix::alloc(); rmat->initWithDevice(dev, rmat_des);
        generateRandomFloatData(mat1->data());
        generateRandomFloatData(mat2->data());
        MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
        MTL::CommandBuffer* cmdBuf = cmdQueue->commandBuffer();
        mps_matmul->initWithDevice(dev, 4, 5, 1);
        mps_matmul->encodeToCommandBuffer(cmdBuf, mat1, mat2, rmat);
        cmdBuf->commit();
        cmdBuf->waitUntilCompleted();
        CHECK(matmul_verify(mat1->data(), mat2->data(), rmat->data(), 4, 5, 1));
    }
}

TEST_CASE("Testing matrix-vector multiplication"){
    MPS::MatrixVectorMultiplication* matvec_mul = MPS::MatrixVectorMultiplication::alloc();
    SUBCASE("Square matrix (5x5) with vector (5x1)"){
        MPS::MatrixDescriptor* mat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32);
        MPS::VectorDescriptor* vector_des = MPS::VectorDescriptor::vectorDescriptorWithLength(5, MPS::MPSDataTypeFloat32);
        MPS::VectorDescriptor* rvec_des = MPS::VectorDescriptor::vectorDescriptorWithLength(5, MPS::MPSDataTypeFloat32);
        MPS::Matrix* matrix = MPS::Matrix::alloc();matrix->initWithDevice(dev, mat_des);
        MPS::Vector* vector = MPS::Vector::alloc();vector->initWithDevice(dev, vector_des);
        MPS::Vector* result_vec = MPS::Vector::alloc();result_vec->initWithDevice(dev, rvec_des);
        generateRandomFloatData(matrix->data());
        generateRandomFloatData(vector->data());
        MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
        MTL::CommandBuffer* cmdBuf = cmdQueue->commandBuffer();
        matvec_mul->initWithDevice(dev, 5, 5);
        matvec_mul->encodeToCommandBuffer(cmdBuf, matrix, vector, result_vec);
        cmdBuf->commit();
        cmdBuf->waitUntilCompleted();
        CHECK(matmul_verify(matrix->data(), vector->data(), result_vec->data(), 5, 1, 5));
    }
    SUBCASE("Rectangular matrix (3x5) with vector (5x1)"){
        MPS::MatrixDescriptor* mat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(3, 5, 20, MPS::MPSDataTypeFloat32);
        MPS::VectorDescriptor* vector_des = MPS::VectorDescriptor::vectorDescriptorWithLength(5, MPS::MPSDataTypeFloat32);
        MPS::VectorDescriptor* rvec_des = MPS::VectorDescriptor::vectorDescriptorWithLength(3, MPS::MPSDataTypeFloat32);
        MPS::Matrix* matrix = MPS::Matrix::alloc();matrix->initWithDevice(dev, mat_des);
        MPS::Vector* vector = MPS::Vector::alloc();vector->initWithDevice(dev, vector_des);
        MPS::Vector* result_vec = MPS::Vector::alloc();result_vec->initWithDevice(dev, rvec_des);
        generateRandomFloatData(matrix->data());
        generateRandomFloatData(vector->data());
        MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
        MTL::CommandBuffer* cmdBuf = cmdQueue->commandBuffer();
        matvec_mul->initWithDevice(dev, 3, 5);
        matvec_mul->encodeToCommandBuffer(cmdBuf, matrix, vector, result_vec);
        cmdBuf->commit();
        cmdBuf->waitUntilCompleted();
        CHECK(matmul_verify(matrix->data(), vector->data(), result_vec->data(), 3, 1, 5));
    }
}
// =========================================== END: MATRIX & VECTOR MULT. ============================================





