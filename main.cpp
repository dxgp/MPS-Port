#include <iostream>
#include <fstream>
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "metal-cpp/Foundation/Foundation.hpp"
#include "metal-cpp/Metal/Metal.hpp"
#include "metal-cpp/QuartzCore/QuartzCore.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSNDArray.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSCommandBuffer.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSKernelTypes.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"
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
int main(){
    MTL::Device* dev = MTL::CreateSystemDefaultDevice();
    MPS::MatrixDescriptor* mat1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);  
    MPS::MatrixDescriptor* mat2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);
    MPS::MatrixDescriptor* rmat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(4, 4, 16, MPS::MPSDataTypeFloat32);  
    MTL::Buffer* buf_mat1 = dev->newBuffer(512, MTL::ResourceStorageModeShared);
    MTL::Buffer* buf_mat2 = dev->newBuffer(512, MTL::ResourceStorageModeShared);
    MTL::Buffer* buf_rmat = dev->newBuffer(512, MTL::ResourceStorageModeShared);
    // putting data in mat1 and mat2
    generateRandomFloatData(buf_mat1);
    generateRandomFloatData(buf_mat2);
    uint32_t *m1 = (uint32_t *)buf_mat1->contents();
    uint32_t *m2 = (uint32_t *)buf_mat2->contents();
    for(int i=0;i<16;i++){
        m1[i] = (rand() % 10) + 1;
        m2[i] = (rand() % 10) + 1;
    }
    // dummy data work done
    MPS::Matrix* mat1 = MPS::Matrix::alloc();
    mat1->initWithBuffer(buf_mat1, mat1_des);
    MPS::Matrix* mat2 = MPS::Matrix::alloc();
    mat2->initWithBuffer(buf_mat2, mat2_des);
    MPS::Matrix* rmat = MPS::Matrix::alloc();
    rmat->initWithBuffer(buf_rmat, rmat_des);
    generateRandomFloatData(mat1->data());
    generateRandomFloatData(mat2->data());
    printMTLBuffer(mat1->data(), "MAT1");
    printMTLBuffer(mat2->data(), "MAT2");
    std::cout<<"matrixBytes:"<<mat1->matrixBytes()<<std::endl;
    // MPS::Matrix* mat2 = MPS::Matrix::initWithBuffer(buf_mat2, mat2_des);
    // MPS::Matrix* rmat = MPS::Matrix::initWithBuffer(buf_rmat, rmat_des);
    MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
    mps_matmul->initWithDevice(dev, 4, 4, 4);
    MTL::CommandQueue* cmdq = dev->newCommandQueue();
    MTL::CommandBuffer* cmdbuf = cmdq->commandBuffer();
    mps_matmul->encodeToCommandBuffer(cmdbuf, mat1, mat2, rmat);
    cmdbuf->commit();
    cmdbuf->waitUntilCompleted();
    printMTLBuffer(buf_rmat, "RESULT:");
    return 0;
}
