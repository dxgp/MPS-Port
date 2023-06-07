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

#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixRandom.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "basic_utils.hpp"

MTL::Device* device = MTL::CreateSystemDefaultDevice();

TEST_CASE("Creating a MatrixRandomDistributionDescriptor object"){
    SUBCASE("Using uniformDistributionDescriptorWithMinimum"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::uniformDistributionDescriptorWithMinimum(3.0, 6.0);
        CHECK(areEqual(desc->minimum(), 3.0));
        CHECK(areEqual(desc->maximum(), 6.0));
    }
    SUBCASE("Using normalDistributionDescriptorWithMean"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(3.0, 0.5);
        CHECK(areEqual(desc->mean(), 3.0));
        CHECK(areEqual(desc->standardDeviation(), 0.5));
    }
    SUBCASE("Using normalDistributionDescriptorWithMean with min and max"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(3.0, 0.5, 1.0, 6.0);
        CHECK(areEqual(desc->mean(), 3.0));
        CHECK(areEqual(desc->standardDeviation(), 0.5));
        CHECK(areEqual(desc->minimum(), 1.0));
        CHECK(areEqual(desc->maximum(), 6.0));
    }
    SUBCASE("Using the default descriptor"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::defaultDistributionDescriptor();
        CHECK(desc!=nullptr);
    }
}
TEST_CASE("Creating a random MTGP32 matrix"){
    SUBCASE("initWithDevice"){
        MPS::Matrix* mat = MPS::Matrix::alloc();mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeUInt32));
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* commandBuffer = cmdQueue->commandBuffer();
        MPS::MatrixRandomMTGP32* mtgp32_mat = MPS::MatrixRandomMTGP32::alloc();
        mtgp32_mat->initWithDevice(device);
        mtgp32_mat->synchronizeStateOnCommandBuffer(commandBuffer);
        mtgp32_mat->encodeToCommandBuffer(commandBuffer, mat);
        commandBuffer->commit();
        commandBuffer->waitUntilCompleted();
        // printMTLBufferInt32(mat->data(), "Generated data");

    }
    SUBCASE("initWithDevice with destinationDataType, seed"){
        MPS::Matrix* mat = MPS::Matrix::alloc();mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 5, 20, MPS::MPSDataTypeUInt32));
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* commandBuffer = cmdQueue->commandBuffer();
        MPS::MatrixRandomMTGP32* mtgp32_mat = MPS::MatrixRandomMTGP32::alloc();
        mtgp32_mat->initWithDevice(device, MPS::MPSDataTypeUInt32, 23);
        mtgp32_mat->synchronizeStateOnCommandBuffer(commandBuffer);
        mtgp32_mat->encodeToCommandBuffer(commandBuffer, mat);
        commandBuffer->commit();
        commandBuffer->waitUntilCompleted();
        // printMTLBufferInt32(mat->data(), "Generated data");
    }
    SUBCASE("initWithDevice with a normal distribution descriptor with min and max"){
        MPS::Matrix* mat = MPS::Matrix::alloc();mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(1000, 100, 400, MPS::MPSDataTypeFloat32));
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* commandBuffer = cmdQueue->commandBuffer();
        MPS::MatrixRandomMTGP32* mtgp32_mat = MPS::MatrixRandomMTGP32::alloc();
        // TREAD VERY CAREFULLY HERE. IF IT CAN'T GENERATE NUMBERS BETWEEN THAT RANGE, IT MAY IGNORE IT. SO, MAKE SURE YOU GIVE IT A WIDE ENOUGH RANGE.
        // IT WOULD BE INTERESTING TO EXPLORE THE LIMITS OF THIS THING
        mtgp32_mat->initWithDevice(device, MPS::MPSDataTypeFloat32, 23, MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(10.0, 1, -10, 10));
        mtgp32_mat->encodeToCommandBuffer(commandBuffer, mat);
        mtgp32_mat->synchronizeStateOnCommandBuffer(commandBuffer);
        commandBuffer->commit();
        commandBuffer->waitUntilCompleted();
        std::cout<<computeMean((float*)((mat->data())->contents()), 100000)<<" ---- "<<3.0<<std::endl;
        float computed_mean = computeMean((float*)((mat->data())->contents()), 100000);
        float computed_std = computeStd((float*)(mat->data()->contents()), 100000, computed_mean);
        float computed_min = computeMin((float*)((mat->data())->contents()), 100000);
        float computed_max = computeMax((float*)((mat->data())->contents()), 100000);
        CHECK(areEqualLowPrecision(computed_mean, 10.0));
        CHECK(areEqualLowPrecision(computed_std, 1));
        CHECK(computed_min>=-10);
        CHECK(computed_max<=10.0);
    }
    SUBCASE("Creation with a normal distribution descriptor without min and max"){
        MPS::Matrix* mat = MPS::Matrix::alloc();mat->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(100, 100, 400, MPS::MPSDataTypeFloat32));
        MTL::CommandQueue* cmdQueue = device->newCommandQueue();
        MTL::CommandBuffer* commandBuffer = cmdQueue->commandBuffer();
        MPS::MatrixRandomMTGP32* mtgp32_mat = MPS::MatrixRandomMTGP32::alloc();
        mtgp32_mat->initWithDevice(device, MPS::MPSDataTypeFloat32, 23, MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(3.0, 0.5, 1.0, 6.0));
        mtgp32_mat->synchronizeStateOnCommandBuffer(commandBuffer);
        mtgp32_mat->encodeToCommandBuffer(commandBuffer, mat);
        commandBuffer->commit();
        commandBuffer->waitUntilCompleted();
        std::cout<<computeMean((float*)((mat->data())->contents()), 1000)<<" ---- "<<3.0<<std::endl;
        float computed_mean = computeMean((float*)((mat->data())->contents()), 1000);
        float computed_std = computeStd((float*)(mat->data()->contents()), 1000, computed_mean);
        CHECK(areEqualLowPrecision(computed_mean, 3.0));
        CHECK(areEqualLowPrecision(computed_std, 0.5));
    }
    SUBCASE("Creation with a normal distribution descriptor with min and max"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a default descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
}
TEST_CASE("Creating a random Philox matrix"){
    SUBCASE("Creation with a uniform distribution descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a normal distribution descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a normal distribution descriptor with min and max"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a default descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
}
