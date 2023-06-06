#pragma once
#include "MPSMatrixTypes.hpp"

namespace MPS{
    _NS_OPTIONS(NS::UInteger, MatrixRandomDistribution){
        MatrixRandomDistributionDefault = 1U,
        MatrixRandomDistributionUniform = 2U,
        MatrixRandomDistributionNormal = 3U
    };
    class MatrixRandomDistributionDescriptor: public NS::Copying<MPS::MatrixRandomDistributionDescriptor>{
        static MPS::MatrixRandomDistributionDescriptor* alloc();
        MPS::MatrixRandomDistribution distributionType();
        float minimum();
        float maximum();
        float mean();
        float standardDeviation();
        static MPS::MatrixRandomDistributionDescriptor* uniformDistributionDescriptorWithMinimum(float minimum, float maximum);
        static MPS::MatrixRandomDistributionDescriptor* normalDistributionDescriptorWithMean(float mean, float standardDeviation);
        static MPS::MatrixRandomDistributionDescriptor* defaultDistributionDescriptor(); 
    };
    class MatrixRandom: public NS::Referencing<MPS::Kernel>{
        MPS::DataType destinationDataType() const;
        MPS::MatrixRandomDistribution distributionType() const;
        NS::UInteger batchStart();
        NS::UInteger batchSize();
        // MPS::MatrixRandom* initWithDevice(MTL::Device* device); use one of the subclasses of MatrixRandom
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Vector* destinationVector);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* destinationMatrix);
    };
    class MatrixRandomMTGP32: public NS::Referencing<MPS::MatrixRandom>{
        MPS::MatrixRandomMTGP32* initWithDevice(MTL::Device* device);
        MPS::MatrixRandomMTGP32* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed, MPS::MatrixRandomDistributionDescriptor* distributionDescriptor);
        void synchronizeStateOnCommandBuffer(MTL::CommandBuffer* commandBuffer);
        MPS::MatrixRandomMTGP32* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed);
        MPS::MatrixRandomMTGP32* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
    };
    class MatrixRandomPhilox: public NS::Referencing<MPS::MatrixRandom>{
        MPS::MatrixRandomPhilox* initWithDevice(MTL::Device* device);
        MPS::MatrixRandomPhilox* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed, MPS::MatrixRandomDistributionDescriptor* distributionDescriptor);
        MPS::MatrixRandomPhilox* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed);
        MPS::MatrixRandomPhilox* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
    };

}