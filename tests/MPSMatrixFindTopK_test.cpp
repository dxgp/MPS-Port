#include "common_test.hpp"
#include "../metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixFindTopK.hpp"

MTL::Device* dev = MTL::CreateSystemDefaultDevice();
TEST_CASE("Creating the MPSMatrixFindTopK Object"){
    MPS::MatrixFindTopK* findtopk_obj = MPS::MatrixFindTopK::alloc();
    findtopk_obj->initWithDevice(dev, 4);
    CHECK(findtopk_obj->numberOfTopKValues() == 4);
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