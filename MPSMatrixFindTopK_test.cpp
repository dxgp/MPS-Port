#include <iostream>
#include <fstream>


#include <Accelerate/Accelerate.h>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "metal-cpp/Foundation/Foundation.hpp"
#include "metal-cpp/Metal/Metal.hpp"
#include "metal-cpp/QuartzCore/QuartzCore.hpp"

#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixFindTopK.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
void printMTLBuffer(MTL::Buffer *buf, std::string name){
    std::cout<<name<<":"<<"<";
    float *ptr = (float*)buf->contents();
    for(int i=0;i<buf->length()/sizeof(float) - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[buf->length()/sizeof(float) - 1]<<">";
    std::cout<<std::endl;
}
void printMTLBufferInt32(MTL::Buffer* buf, std::string name){
    std::cout<<name<<":"<<"<";
    uint32_t *ptr = (uint32_t*)buf->contents();
    for(int i=0;i<buf->length()/4 - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[buf->length()/4 - 1]<<">";
    std::cout<<std::endl;
}
MTL::Device* dev = MTL::CreateSystemDefaultDevice();
TEST_CASE("Creating the MPSMatrixFindTopK Object"){
    MPS::MatrixFindTopK* findtopk_obj = MPS::MatrixFindTopK::alloc();
    findtopk_obj->initWithDevice(dev, 4);
    CHECK(findtopk_obj->numberOfTopKValues() == 4);
}
void generateRandomFloatData(MTL::Buffer *buffer){
    float32_t *dataptr = (float32_t *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/4;index++){
        dataptr[index] = ((float32_t)rand() / float(RAND_MAX))*10;
    }
}
TEST_CASE("Finding the top K values"){
    MPS::MatrixFindTopK* findtopk_obj = MPS::MatrixFindTopK::alloc();
    findtopk_obj->initWithDevice(dev, 1);
    MPS::MatrixDescriptor* mat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32);
    MPS::MatrixDescriptor* index_matrix_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 2, 8, MPS::MPSDataTypeUInt32);
    MPS::MatrixDescriptor* val_matrix_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 2, 8, MPS::MPSDataTypeFloat32);
    MPS::Matrix* matrix = MPS::Matrix::alloc(); matrix->initWithDevice(dev, mat_des);

    MPS::Matrix* index_matrix = MPS::Matrix::alloc(); index_matrix->initWithDevice(dev, index_matrix_des);

    MPS::Matrix* val_matrix = MPS::Matrix::alloc(); val_matrix->initWithDevice(dev, val_matrix_des);
    //assert(matrix->dataType() == val_matrix->dataType());
    generateRandomFloatData(matrix->data());
    // generateRandomFloatData(val_matrix->data());
    std::cout<<"Mat1 datatype:"<<matrix->dataType()<<std::endl;
    std::cout<<"Mat2 datatype:"<<val_matrix->dataType()<<std::endl;
    std::cout<<"Mat3 datatype:"<<index_matrix->dataType()<<std::endl;
    MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
    MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
    findtopk_obj->encodeToCommandBuffer(cmdBuffer, matrix, index_matrix, val_matrix);
    cmdBuffer->commit();
    cmdBuffer->waitUntilCompleted();
    printMTLBuffer(matrix->data(), "Matrix Data");
    printMTLBufferInt32(index_matrix->data(), "Index data");
    printMTLBuffer(val_matrix->data(), "Value data");
}