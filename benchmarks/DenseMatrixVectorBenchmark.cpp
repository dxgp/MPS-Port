#include <iostream>
#include <fstream>


#include <Accelerate/Accelerate.h>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "../metal-cpp/Foundation/Foundation.hpp"
#include "../metal-cpp/Metal/Metal.hpp"
#include "../metal-cpp/QuartzCore/QuartzCore.hpp"



#include "../metal-cpp/MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"
#include "../metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"
#include "../basic_utils.hpp"
#include <fstream>

typedef std::chrono::microseconds time_unit;
auto unit_name = "microseconds";

template <class T>
void statistics(T *array, size_t length, T &array_mean, T &array_std)
{
    array_mean = 0;
    for (size_t repeat = 0; repeat < length; repeat++)
    {
        array_mean += array[repeat];
    }
    array_mean /= length;

    array_std = 0;
    for (size_t repeat = 0; repeat < length; repeat++)
    {
        array_std += pow(array_mean - array[repeat], 2.0);
    }
    array_std /= length;
    array_std = pow(array_std, 0.5);
}

int main(){
    MTL::Device* device = MTL::CreateSystemDefaultDevice();
    uint64_t sizes[] = {(uint64_t) 32, (uint64_t) 64, (uint64_t) 128,(uint64_t)1024,(uint64_t)2048,(uint64_t)4096, (uint64_t)8192,(uint64_t) 16384};
    int repeats = 100;
    auto durations = new float[repeats];
    auto durations_blas = new float[repeats];
    auto durations_vdsp = new float[repeats];
    for(auto size: sizes){
        MPS::MatrixDescriptor* mat_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(size, size, size*4, MPS::MPSDataTypeFloat32);
        MPS::VectorDescriptor* vector_des = MPS::VectorDescriptor::vectorDescriptorWithLength(size, MPS::MPSDataTypeFloat32);
        MPS::VectorDescriptor* rvec_des = MPS::VectorDescriptor::vectorDescriptorWithLength(size, MPS::MPSDataTypeFloat32);
        MPS::Matrix* matrix = MPS::Matrix::alloc();matrix->initWithDevice(device, mat_des);
        MPS::Vector* vector = MPS::Vector::alloc();vector->initWithDevice(device, vector_des);
        MPS::Vector* result_vec = MPS::Vector::alloc();result_vec->initWithDevice(device, rvec_des);
        generateRandomFloatData(matrix->data());
        generateRandomFloatData(vector->data());
        MPS::MatrixVectorMultiplication* matvec_mul = MPS::MatrixVectorMultiplication::alloc();
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        float * matrix_ptr = (float *)(matrix->data()->contents());
        float * vector_ptr = (float *)(vector->data()->contents());
        float * result_ptr = (float *) (result_vec->data()->contents());
        for(int i=0; i<repeats;i++){
            MTL::CommandBuffer* cmdBuf = cmdQueue->commandBuffer();
            matvec_mul->initWithDevice(device, size, size);
            matvec_mul->encodeToCommandBuffer(cmdBuf, matrix, vector, result_vec);
            auto start = std::chrono::high_resolution_clock::now();
            cmdBuf->commit();
            cmdBuf->waitUntilCompleted();
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<time_unit>(stop-start).count();
            durations[i] = duration;
            start = std::chrono::high_resolution_clock::now();
            vDSP_mmul(matrix_ptr, 1, vector_ptr, 1, result_ptr, 1, size, 1, size);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<time_unit>(stop-start).count();
            durations_vdsp[i] = duration;
        }
        float array_mean;
        float array_std;
        statistics<float>(durations, repeats, array_mean, array_std);
        std::cout<<"******* ARRAY SIZE: "<<size<<"*******"<<std::endl;
        std::cout << "Metal Performance" <<std::endl;
        std::cout << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl<< std::endl;
        float array_mean_vdsp;
        float array_std_vdsp;
        statistics<float>(durations_vdsp, repeats, array_mean_vdsp, array_std_vdsp);
        std::cout << "vDSP Performance" <<std::endl;
        std::cout << array_mean_vdsp << unit_name << " \t +/- " << array_std_vdsp << unit_name << std::endl<< std::endl;
    }
}






