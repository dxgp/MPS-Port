#include "common_test.hpp"


MTL::Device* dev = MTL::CreateSystemDefaultDevice();
std::vector<float> not_in_place_sort(std::vector<float> original) {
    std::sort(original.begin(), original.end(), std::greater<float>());
    return original;
}
bool verifyTopK(float* inputs, int numberOfTopVals, float* result, int numRows, int numCols){
    float* calc_res = new float[numRows*numberOfTopVals];
    for(int i=0; i<numRows; i++){
        std::vector<float> rowVec;
        for(int j=0; j<numCols;j++){
            rowVec.push_back(inputs[i*numCols + j]);
        }
        std::vector<float> sorted_row = not_in_place_sort(rowVec);
        for(int k=0; k<numberOfTopVals;k++){
            calc_res[i*numberOfTopVals + k] = sorted_row[k];
        }
    }
    for(int i=0; i<numRows*numberOfTopVals;i++){
        if(!areEqual(calc_res[i], result[i])){
            return false;
        }
    }
    return true;
}
TEST_CASE("Creating the MPSMatrixFindTopK Object"){
    MPS::MatrixFindTopK* findtopk_obj = MPS::MatrixFindTopK::alloc();
    findtopk_obj->initWithDevice(dev, 4);
    CHECK(findtopk_obj->numberOfTopKValues() == 4);
}
TEST_CASE("Finding the top K values"){
    MPS::MatrixFindTopK* findtopk_obj = MPS::MatrixFindTopK::alloc();
    findtopk_obj->initWithDevice(dev, 2);
    MPS::MatrixDescriptor* mat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeFloat32);
    MPS::MatrixDescriptor* index_matrix_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 2, 8, MPS::MPSDataTypeUInt32);
    MPS::MatrixDescriptor* val_matrix_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 2, 8, MPS::MPSDataTypeFloat32);
    MPS::Matrix* matrix = MPS::Matrix::alloc(); matrix->initWithDevice(dev, mat_des);
    MPS::Matrix* index_matrix = MPS::Matrix::alloc(); index_matrix->initWithDevice(dev, index_matrix_des);
    MPS::Matrix* val_matrix = MPS::Matrix::alloc(); val_matrix->initWithDevice(dev, val_matrix_des);
    generateRandomFloatData(matrix->data());
    MTL::CommandQueue* cmdQueue = dev->newCommandQueue();
    MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
    findtopk_obj->encodeToCommandBuffer(cmdBuffer, matrix, index_matrix, val_matrix);
    cmdBuffer->commit();
    cmdBuffer->waitUntilCompleted();
    CHECK(verifyTopK((float *)(matrix->data()->contents()), 2,(float *)(val_matrix->data()->contents()) , 5, 5));
}