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


#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixSoftMax.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "basic_utils.hpp"

MTL::Device* device = MTL::CreateSystemDefaultDevice();
TEST_CASE("Using MatrixSoftMax"){
    MPS::MatrixSoftMax* softmax_mat = MPS::MatrixSoftMax::alloc(); softmax_mat->initWithDevice(device);
    MPS::Matrix* input_mat = MPS::Matrix::alloc();input_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
    MPS::Matrix* result_mat = MPS::Matrix::alloc();result_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
    generateRandomFloatData(input_mat->data());
    MTL::CommandQueue* cmdQueue = device->newCommandQueue();
    MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
    softmax_mat->encodeToCommandBuffer(cmdBuffer, input_mat, result_mat);
    cmdBuffer->commit();
    cmdBuffer->waitUntilCompleted();
    printMTLBuffer(input_mat->data(), "Input:");
    printMTLBuffer(result_mat->data(), "Result");
}
TEST_CASE("MatrixLogSoftMax"){
    MPS::MatrixLogSoftMax* softmax_mat = MPS::MatrixLogSoftMax::alloc(); softmax_mat->initWithDevice(device);
    MPS::Matrix* input_mat = MPS::Matrix::alloc();input_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
    MPS::Matrix* result_mat = MPS::Matrix::alloc();result_mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32));
    generateRandomFloatData(input_mat->data());
    MTL::CommandQueue* cmdQueue = device->newCommandQueue();
    MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
    softmax_mat->encodeToCommandBuffer(cmdBuffer, input_mat, result_mat);
    cmdBuffer->commit();
    cmdBuffer->waitUntilCompleted();
    printMTLBuffer(input_mat->data(), "Input:");
    printMTLBuffer(result_mat->data(), "Result");
}
TEST_CASE("MatrixSoftMaxGradient"){
    
}
TEST_CASE("MatrixLogSoftMaxGradient"){

}




