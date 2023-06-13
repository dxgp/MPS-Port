#include "common_test.hpp"


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
}
TEST_CASE("MatrixSoftMaxGradient"){

}
TEST_CASE("MatrixLogSoftMaxGradient"){

}




