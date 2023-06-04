#include <iostream>
#include <fstream>
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "metal-cpp/Foundation/Foundation.hpp"
#include "metal-cpp/Metal/Metal.hpp"
#include "metal-cpp/QuartzCore/QuartzCore.hpp"

#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
void printMTLBuffer(MTL::Buffer *buf, std::string name){
    std::cout<<name<<":"<<"<";
    float *ptr = (float*)buf->contents();
    for(int i=0;i<16 - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[16 - 1]<<">";
    std::cout<<std::endl;
}
void generateRandomFloatData(MTL::Buffer *buffer){
    float *dataptr = (float *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/sizeof(float);index++){
        dataptr[index] = ((float)rand() / float(RAND_MAX))*10;
    }
}

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
        MTL::Buffer* buf = dev->newBuffer((matrix_des->rows() - 1)*matrix_des->rowBytes() + matrix_des->columns()*4, MTL::ResourceStorageModeShared);
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
//test for creating a VectorDescriptor
//test for creating a Matrix
//test for creating a Vector
//test for creating a TemporaryMatrix
//test for creating a TemporaryVector
//test for creating a MatrixMultiplication object
//test for creating a MatrixVectorMulti plication object
//test for performing a matrix-matrix multiplication
//test for performing a matrix-vector multiplication

// int main(){
//     MTL::Device* dev = MTL::CreateSystemDefaultDevice();
//     MPS::MatrixDescriptor* mat1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);  
//     MPS::MatrixDescriptor* mat2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);
//     MPS::MatrixDescriptor* rmat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);  
//     MTL::Buffer* buf_mat1 = dev->newBuffer(512, MTL::ResourceStorageModeShared);
//     MTL::Buffer* buf_mat2 = dev->newBuffer(512, MTL::ResourceStorageModeShared);
//     MTL::Buffer* buf_rmat = dev->newBuffer(512, MTL::ResourceStorageModeShared);
//     // putting data in mat1 and mat2
//     // dummy data work done
//     MPS::Matrix* mat1 = MPS::Matrix::alloc();
//     mat1->initWithBuffer(buf_mat1, mat1_des);
//     MPS::Matrix* mat2 = MPS::Matrix::alloc();
//     mat2->initWithBuffer(buf_mat2, mat2_des);
//     MPS::Matrix* rmat = MPS::Matrix::alloc();
//     rmat->initWithBuffer(buf_rmat, rmat_des);
//     generateRandomFloatData(mat1->data());
//     generateRandomFloatData(mat2->data());
//     printMTLBuffer(mat1->data(), "MAT1");
//     printMTLBuffer(mat2->data(), "MAT2");
//     std::cout<<"matrixBytes:"<<mat1->matrixBytes()<<std::endl;
//     // MPS::Matrix* mat2 = MPS::Matrix::initWithBuffer(buf_mat2, mat2_des);
//     // MPS::Matrix* rmat = MPS::Matrix::initWithBuffer(buf_rmat, rmat_des);
//     MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
//     mps_matmul->initWithDevice(dev, 4, 4, 4);
//     MTL::CommandQueue* cmdq = dev->newCommandQueue();
//     MTL::CommandBuffer* cmdbuf = cmdq->commandBuffer();
//     mps_matmul->encodeToCommandBuffer(cmdbuf, mat1, mat2, rmat);
//     cmdbuf->commit();
//     cmdbuf->waitUntilCompleted();
//     printMTLBuffer(buf_rmat, "RESULT:");
//     return 0;
// }
