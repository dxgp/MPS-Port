#pragma once
#include "MPSMatrixTypes.hpp"

namespace MPS{
    class MatrixRandomDistributionDescriptor: public NS::Copying<MPS::MatrixRandomDistributionDescriptor>{
        public:
        // do I need this alloc and init? While it is importand because NS::Copying requires it, do I need it?
        static MPS::MatrixRandomDistributionDescriptor* alloc();
        MPS::MatrixRandomDistributionDescriptor* init();
        MPS::MatrixRandomDistribution distributionType();
        float minimum();
        float maximum();
        float mean();
        float standardDeviation();
        static MPS::MatrixRandomDistributionDescriptor* uniformDistributionDescriptorWithMinimum(float minimum, float maximum);
        static MPS::MatrixRandomDistributionDescriptor* normalDistributionDescriptorWithMean(float mean, float standardDeviation);
        static MPS::MatrixRandomDistributionDescriptor* normalDistributionDescriptorWithMean(float mean, float standardDeviation, float minimum, float maximum);
        static MPS::MatrixRandomDistributionDescriptor* defaultDistributionDescriptor(); 
    };
    /* 
    since you can't really initialize using this MatrixRandom class, the functions should be 
    added to both the subclasses to make this work. Otherwise, they won't even have these functions
    */
    class MatrixRandom: public NS::Referencing<MPS::Kernel>{
        public:
        static MPS::MatrixRandom* alloc();
        MPS::DataType destinationDataType() const;
        MPS::MatrixRandomDistribution distributionType() const;
        NS::UInteger batchStart();
        NS::UInteger batchSize();
        // MPS::MatrixRandom* initWithDevice(MTL::Device* device); use one of the subclasses of MatrixRandom
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Vector* destinationVector);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* destinationMatrix);
    };
    class MatrixRandomMTGP32: public NS::Referencing<MPS::MatrixRandom>{
        public:
        static MPS::MatrixRandomMTGP32* alloc();
        MPS::DataType destinationDataType() const;
        MPS::MatrixRandomDistribution distributionType() const;
        NS::UInteger batchStart();
        NS::UInteger batchSize();
        // the two initWithDevice calls below use the defaultDistributionDescriptor...
        MPS::MatrixRandomMTGP32* initWithDevice(MTL::Device* device); // generates a random distribution with a data type of UInt32
        MPS::MatrixRandomMTGP32* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed); // generates a random distribution with a data type of UInt32 with seed
        MPS::MatrixRandomMTGP32* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed, MPS::MatrixRandomDistributionDescriptor* distributionDescriptor); 
        MPS::MatrixRandomMTGP32* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
        void synchronizeStateOnCommandBuffer(MTL::CommandBuffer* commandBuffer);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Vector* destinationVector);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* destinationMatrix);
    };
    // philox does not have a synchronize on command buffer function. Interesting.
    class MatrixRandomPhilox: public NS::Referencing<MPS::MatrixRandom>{
        public:
        static MPS::MatrixRandomPhilox* alloc();
        MPS::DataType destinationDataType() const;
        MPS::MatrixRandomDistribution distributionType() const;
        NS::UInteger batchStart();
        NS::UInteger batchSize();
        MPS::MatrixRandomPhilox* initWithDevice(MTL::Device* device);
        MPS::MatrixRandomPhilox* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed, MPS::MatrixRandomDistributionDescriptor* distributionDescriptor);
        MPS::MatrixRandomPhilox* initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed);
        MPS::MatrixRandomPhilox* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Vector* destinationVector);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* destinationMatrix);
    };
}

/// @{ @private
_MPS_INLINE MPS::MatrixRandomDistributionDescriptor* MPS::MatrixRandomDistributionDescriptor::alloc(){
    return NS::Object::alloc<MPS::MatrixRandomDistributionDescriptor>(_MPS_PRIVATE_CLS(MPSMatrixRandomDistributionDescriptor));
}
_MPS_INLINE MPS::MatrixRandomDistributionDescriptor* MPS::MatrixRandomDistributionDescriptor::init(){
    return NS::Object::init<MPS::MatrixRandomDistributionDescriptor>();
}
_MPS_INLINE MPS::MatrixRandomDistribution MPS::MatrixRandomDistributionDescriptor::distributionType(){
    return Object::sendMessage<MPS::MatrixRandomDistribution>(this, _MPS_PRIVATE_SEL(distributionType));
}
_MPS_INLINE float MPS::MatrixRandomDistributionDescriptor::minimum(){
    return Object::sendMessage<float>(this, _MPS_PRIVATE_SEL(minimum));
}
_MPS_INLINE float MPS::MatrixRandomDistributionDescriptor::maximum(){
    return Object::sendMessage<float>(this, _MPS_PRIVATE_SEL(maximum));
}
_MPS_INLINE float MPS::MatrixRandomDistributionDescriptor::mean(){
    return Object::sendMessage<float>(this, _MPS_PRIVATE_SEL(mean));
}
_MPS_INLINE float MPS::MatrixRandomDistributionDescriptor::standardDeviation(){
    return Object::sendMessage<float>(this, _MPS_PRIVATE_SEL(standardDeviation));
}
_MPS_INLINE MPS::MatrixRandomDistributionDescriptor* MPS::MatrixRandomDistributionDescriptor::uniformDistributionDescriptorWithMinimum(float minimum, float maximum){
    return Object::sendMessage<MPS::MatrixRandomDistributionDescriptor*>(_MPS_PRIVATE_CLS(MPSMatrixRandomDistributionDescriptor), _MPS_PRIVATE_SEL(uniformDistributionDescriptorWithMinimum_maximum_), minimum, maximum);
}
_MPS_INLINE MPS::MatrixRandomDistributionDescriptor* MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(float mean, float standardDeviation){
    return Object::sendMessage<MPS::MatrixRandomDistributionDescriptor*>(_MPS_PRIVATE_CLS(MPSMatrixRandomDistributionDescriptor), _MPS_PRIVATE_SEL(normalDistributionDescriptorWithMean_standardDeviation_), mean, standardDeviation);
}
_MPS_INLINE MPS::MatrixRandomDistributionDescriptor* MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(float mean, float standardDeviation, float minimum, float maximum){
    return Object::sendMessage<MPS::MatrixRandomDistributionDescriptor*>(_MPS_PRIVATE_CLS(MPSMatrixRandomDistributionDescriptor), _MPS_PRIVATE_SEL(normalDistributionDescriptorWithMean_standardDeviation_minimum_maximum_), mean, standardDeviation, minimum, maximum);
}
_MPS_INLINE MPS::MatrixRandomDistributionDescriptor* MPS::MatrixRandomDistributionDescriptor::defaultDistributionDescriptor(){
    return Object::sendMessage<MPS::MatrixRandomDistributionDescriptor*>(_MPS_PRIVATE_CLS(MPSMatrixRandomDistributionDescriptor), _MPS_PRIVATE_SEL(defaultDistributionDescriptor));
}

_MPS_INLINE MPS::MatrixRandomMTGP32* MPS::MatrixRandomMTGP32::alloc(){
    return NS::Object::alloc<MPS::MatrixRandomMTGP32>(_MPS_PRIVATE_CLS(MPSMatrixRandomMTGP32));
}
_MPS_INLINE MPS::MatrixRandomPhilox* MPS::MatrixRandomPhilox::alloc(){
    return NS::Object::alloc<MPS::MatrixRandomPhilox>(_MPS_PRIVATE_CLS(MPSMatrixRandomPhilox));
}

//MatrixRandomMTGP32. Don't really know if doing this will work
_MPS_INLINE MPS::DataType MPS::MatrixRandomMTGP32::destinationDataType() const{
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(destinationDataType));
}
_MPS_INLINE MPS::MatrixRandomDistribution MPS::MatrixRandomMTGP32::distributionType() const{
    return Object::sendMessage<MPS::MatrixRandomDistribution>(this, _MPS_PRIVATE_SEL(distributionType));
}
_MPS_INLINE NS::UInteger MPS::MatrixRandomMTGP32::batchStart(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchStart));
}
_MPS_INLINE NS::UInteger MPS::MatrixRandomMTGP32::batchSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchSize));
}
_MPS_INLINE MPS::MatrixRandomMTGP32* MPS::MatrixRandomMTGP32::initWithDevice(MTL::Device* device){
    return Object::sendMessage<MPS::MatrixRandomMTGP32*>(this, _MPS_PRIVATE_SEL(initWithDevice_), device);
}
_MPS_INLINE MPS::MatrixRandomMTGP32* MPS::MatrixRandomMTGP32::initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed, MPS::MatrixRandomDistributionDescriptor* distributionDescriptor){
    return Object::sendMessage<MPS::MatrixRandomMTGP32*>(this, _MPS_PRIVATE_SEL(initWithDevice_destinationDataType_seed_distributionDescriptor_), device, destinationDataType, seed, distributionDescriptor);
}
_MPS_INLINE void MPS::MatrixRandomMTGP32::synchronizeStateOnCommandBuffer(MTL::CommandBuffer* commandBuffer){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(synchronizeStateOnCommandBuffer_), commandBuffer);
}
_MPS_INLINE MPS::MatrixRandomMTGP32* MPS::MatrixRandomMTGP32::initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed){
    return Object::sendMessage<MPS::MatrixRandomMTGP32*>(this, _MPS_PRIVATE_SEL(initWithDevice_destinationDataType_seed_), device, destinationDataType, seed);
}
_MPS_INLINE MPS::MatrixRandomMTGP32* MPS::MatrixRandomMTGP32::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
    return Object::sendMessage<MPS::MatrixRandomMTGP32*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_), aDecoder, device);
}
_MPS_INLINE void MPS::MatrixRandomMTGP32::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Vector* destinationVector){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_destinationVector_), commandBuffer, destinationVector);
}
_MPS_INLINE void MPS::MatrixRandomMTGP32::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* destinationMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_destinationMatrix_), commandBuffer, destinationMatrix);
}


_MPS_INLINE MPS::DataType MPS::MatrixRandomPhilox::destinationDataType() const{
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(destinationDataType));
}
_MPS_INLINE MPS::MatrixRandomDistribution MPS::MatrixRandomPhilox::distributionType() const{
    return Object::sendMessage<MPS::MatrixRandomDistribution>(this, _MPS_PRIVATE_SEL(distributionType));
}
_MPS_INLINE NS::UInteger MPS::MatrixRandomPhilox::batchStart(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchStart));
}
_MPS_INLINE NS::UInteger MPS::MatrixRandomPhilox::batchSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchSize));
}
_MPS_INLINE MPS::MatrixRandomPhilox* MPS::MatrixRandomPhilox::initWithDevice(MTL::Device* device){
    return Object::sendMessage<MPS::MatrixRandomPhilox*>(this, _MPS_PRIVATE_SEL(initWithDevice_), device);
}
_MPS_INLINE MPS::MatrixRandomPhilox* MPS::MatrixRandomPhilox::initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed, MPS::MatrixRandomDistributionDescriptor* distributionDescriptor){
    return Object::sendMessage<MPS::MatrixRandomPhilox*>(this, _MPS_PRIVATE_SEL(initWithDevice_destinationDataType_seed_distributionDescriptor_), device, destinationDataType, seed, distributionDescriptor);
}
// _MPS_INLINE void MPS::MatrixRandomPhilox::synchronizeStateOnCommandBuffer(MTL::CommandBuffer* commandBuffer){
//     Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(synchronizeStateOnCommandBuffer_), commandBuffer);
// }
_MPS_INLINE MPS::MatrixRandomPhilox* MPS::MatrixRandomPhilox::initWithDevice(MTL::Device* device, MPS::DataType destinationDataType, NS::UInteger seed){
    return Object::sendMessage<MPS::MatrixRandomPhilox*>(this, _MPS_PRIVATE_SEL(initWithDevice_destinationDataType_seed_), device, destinationDataType, seed);
}
_MPS_INLINE MPS::MatrixRandomPhilox* MPS::MatrixRandomPhilox::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
    return Object::sendMessage<MPS::MatrixRandomPhilox*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_), aDecoder, device);
}
_MPS_INLINE void MPS::MatrixRandomPhilox::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Vector* destinationVector){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_destinationVector_), commandBuffer, destinationVector);
}
_MPS_INLINE void MPS::MatrixRandomPhilox::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* destinationMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_destinationMatrix_), commandBuffer, destinationMatrix);
}


/// @}