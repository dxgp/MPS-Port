#include "bench_common.hpp"
#include "../metal-cpp/MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"
#include "../metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixMultiplication.hpp"


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
    int repeats = 10;
    auto durations = new float[repeats];
    auto durations_blas = new float[repeats];
    auto durations_vdsp = new float[repeats];
    for(auto size: sizes){
        MPS::Matrix* mat1 = MPS::Matrix::alloc();mat1->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(size, size, 4*size, MPS::MPSDataTypeFloat32));
        MPS::Matrix* mat2 = MPS::Matrix::alloc();mat2->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(size, size, 4*size, MPS::MPSDataTypeFloat32));
        MPS::Matrix* rmat = MPS::Matrix::alloc();rmat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(size, size, 4*size, MPS::MPSDataTypeFloat32));
        MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
        generateRandomFloatData(mat1->data());
        generateRandomFloatData(mat2->data());
        float* arrayM1 = (float *) (mat1->data()->contents());
        float* arrayM2 = (float *) (mat2->data()->contents());
        float* arrayR = (float *) (rmat->data()->contents());
        auto start = std::chrono::high_resolution_clock::now();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<time_unit>(stop-start).count();
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        for(int i=0; i<repeats;i++){
            start = std::chrono::high_resolution_clock::now();
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size, 1.0, arrayM1, size, arrayM2, size, 0.0, arrayR, size);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<time_unit>(stop-start).count();
            durations_blas[i] = duration;
            start = std::chrono::high_resolution_clock::now();
            vDSP_mmul(arrayM1, 1, arrayM2, 1, arrayR, 1, size, size, size);
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<time_unit>(stop-start).count();
            durations_vdsp[i] = duration;
            MTL::CommandBuffer* cmdBuffer = cmdQueue->commandBuffer();
            mps_matmul->initWithDevice(device, size, size, size);
            mps_matmul->encodeToCommandBuffer(cmdBuffer, mat1, mat2, rmat);
            start = std::chrono::high_resolution_clock::now();
            cmdBuffer->commit();
            cmdBuffer->waitUntilCompleted();
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<time_unit>(stop-start).count();
            durations[i] = duration;
        }
        float array_mean;
        float array_std;
        statistics<float>(durations, repeats, array_mean, array_std);
        std::cout<<"******* ARRAY SIZE: "<<size<<"*******"<<std::endl;
        std::cout << "Metal Performance" <<std::endl;
        std::cout << array_mean << unit_name << " \t +/- " << array_std << unit_name << std::endl<< std::endl;
        float array_mean_blas;
        float array_std_blas;
        statistics<float>(durations_blas, repeats, array_mean_blas, array_std_blas);
        std::cout << "BLAS Performance" <<std::endl;
        std::cout << array_mean_blas << unit_name << " \t +/- " << array_std_blas << unit_name << std::endl<< std::endl;
        float array_mean_vdsp;
        float array_std_vdsp;
        statistics<float>(durations_vdsp, repeats, array_mean_vdsp, array_std_vdsp);
        std::cout << "vDSP Performance" <<std::endl;
        std::cout << array_mean_vdsp << unit_name << " \t +/- " << array_std_vdsp << unit_name << std::endl<< std::endl;
    }
    
}


