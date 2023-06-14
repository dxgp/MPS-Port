#include <iostream>
#include <fstream>


#include <Accelerate/Accelerate.h>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "QuartzCore/QuartzCore.hpp"



#include "MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"
#include "MetalPerformanceShaders/MPSMatrix/MPSMatrix.hpp"
void printMTLBuffer(MTL::Buffer *buf, std::string name){
    std::cout<<name<<":"<<"<";
    float *ptr = (float*)buf->contents();
    for(int i=0;i<buf->length()/sizeof(float) - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[buf->length()/sizeof(float) - 1]<<">";
    std::cout<<std::endl;
}

int main(){
    // add the data to an array
    float mat1_data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    float mat2_data[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    //declare the device, command buffer, command queue
    MTL::Device* device = MTL::CreateSystemDefaultDevice();
    MTL::CommandQueue* cmdQueue = device->newCommandQueue();
    MTL::CommandBuffer* cmdbuf = cmdQueue->commandBuffer();

    //create buffers from the above data
    MTL::Buffer* b1 = device->newBuffer(mat1_data, 36, MTL::ResourceStorageModeShared);
    MTL::Buffer* b2 = device->newBuffer(mat2_data, 36, MTL::ResourceStorageModeShared);

    //create matrix descriptors
    MPS::MatrixDescriptor* m1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(3,3,12,MPS::MPSDataTypeFloat32);
    MPS::MatrixDescriptor* m2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(3,3,12,MPS::MPSDataTypeFloat32);

    //create matrices from their matrix descriptors
    MPS::Matrix* m1 = MPS::Matrix::alloc(); m1->initWithBuffer(b1, m1_des);
    MPS::Matrix* m2 = MPS::Matrix::alloc(); m2->initWithBuffer(b2, m2_des);
    MPS::Matrix* m_res = MPS::Matrix::alloc(); m_res->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(3,3,12,MPS::MPSDataTypeFloat32));

    //allocate a matrix multiplication object
    MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
    mps_matmul->initWithDevice(device, 3, 3, 3);

    //encode the matmul op. to the command buffer
    mps_matmul->encodeToCommandBuffer(cmdbuf, m1, m2, m_res);

    //commit command buffer
    cmdbuf->commit();
    cmdbuf->waitUntilCompleted();
    
    // print the data
    printMTLBuffer(b1, "m1");
    printMTLBuffer(b2, "m2");
    printMTLBuffer(m_res->data(), "res");
    return 0;
}