#pragma once

#include "MPSCoreTypes.hpp"
#include "../../Metal/MTLBuffer.hpp"
#include <simd/simd.h>
#include "../../Foundation/Foundation.hpp"
#include "../MPSHeaderBridge.hpp"

// note: maybe clang can use the _nonnull attribute. Check it out?
namespace MPS{
    class Matrix;
    class MatrixDescriptor;
    // class Image{};
    typedef NS::Array* MPSImageBatch;
    class NDArrayDescriptor: public NS::Referencing<NDArrayDescriptor>{
        MPS::DataType dataType();
        NS::UInteger numberOfDimensions();
        NS::UInteger lengthOfDimension(NS::UInteger dimensionIndex);
        MPS::DimensionSlice sliceRangeForDimension(NS::UInteger dimensionIndex);
        void  sliceDimension(NS::UInteger dimsionIndex, MPS::DimensionSlice subRange);
        void transposeDimension(NS::UInteger dimensionIndex, NS::UInteger dimensionIndex2);
        vector_uchar16 dimensionOrder();
        // NOTE: Replace dimensionSizes with NS::Size::Make?? A lot easier.
        static MPS::NDArrayDescriptor* descriptorWithDataType(MPS::DataType dataType, NS::UInteger numberOfDimensions, NS::UInteger* dimensionSizes);
        // NOTE: THIS IS ALSO A LITTLE DICEY
        static MPS::NDArrayDescriptor* descriptorWithDataType(MPS::DataType dataType, NS::Array* shape);
        //static NDArrayDescriptor* descriptorWithDatType(MPS::DataType dataType, ...) While cpp 11 does support varidic args, this won't work. internal implementational details will differ
        void reshapeWithDimensionCount(NS::UInteger numberOfDimensions, NS::UInteger* dimensionSizes);
        void reshapeWithShape(NS::Array* shape);
    };
    class Kernel;
    class NDArray;
    // should I put NS::Referencing?????
    class NDArrayAllocator: public NS::Copying<NDArrayAllocator>{
        static MPS::NDArrayAllocator* alloc();
        MPS::NDArrayAllocator* init();
        MPS::NDArray* arrayForCommandBuffer(MTL::CommandBuffer* cmdBuf, MPS::NDArrayDescriptor* descriptor, MPS::Kernel* kernel);
    };
    class NDArray: public NS::Referencing<NDArray>{
        static NDArrayAllocator* defaultAllocator();
        NS::String* label();
        MPS::DataType dataType() const;
        size_t dataTypeSize() const;
        NS::UInteger numberOfDimensions() const;
        NS::UInteger lengthOfDimension(NS::UInteger dimensionIndex);
        MTL::Device* device() const;
        MPS::NDArrayDescriptor* descriptor();
        MPS::NDArray* initWithDevice(MTL::Device* device, NDArrayDescriptor* descriptor);
        MPS::NDArray* initWithDevice(MTL::Device* device, double value);
        NS::UInteger resourceSize();
        MPS::NDArray* arrayViewWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MPS::NDArrayDescriptor* descriptor, MPS::AliasingStrategy aliasing);
        MPS::NDArray* parent() const;
        void exportDataWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MTL::Buffer* buffer, MPS::DataType destinationDataType, NS::UInteger offset, NS::Integer* rowStrides);
        void importDataWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MTL::Buffer* buffer, MPS::DataType sourceDataType, NS::UInteger offset, NS::Integer* rowStrides);
        // Note: Left two more initializers related to images here.
        void readBytes(void* buffer, NS::Integer* strideBytesPerDimension);
        void writeBytes(void* buffer, NS::Integer* strideBytesPerDimension);
        void synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer);
    }; 
    class TemporaryNDArray: NS::Referencing<MPS::NDArray>{
        static MPS::NDArrayAllocator* defaultAllocator();
        static MPS::TemporaryNDArray* temporaryNDArrayWithCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::NDArrayDescriptor* descriptor);
        //static MPS::TemporaryNDArray* initWithDevice(MTL::Device* device, MPS::NDArrayDescriptor* descriptor);
        NS::UInteger readCount();
    };
}
/// @{ @private
// class NDArrayDescriptor
_MPS_INLINE MPS::DataType MPS::NDArrayDescriptor::dataType(){
    return Object::sendMessage<MPS::DataType>(this,_MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE NS::UInteger MPS::NDArrayDescriptor::numberOfDimensions(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(numberOfDimensions));
}
_MPS_INLINE NS::UInteger MPS::NDArrayDescriptor::lengthOfDimension(NS::UInteger dimensionIndex){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(lengthOfDimension_), dimensionIndex);
}
_MPS_INLINE MPS::DimensionSlice MPS::NDArrayDescriptor::sliceRangeForDimension(NS::UInteger dimensionIndex){
    return Object::sendMessage<MPS::DimensionSlice>(this, _MPS_PRIVATE_SEL(sliceRangeForDimension_), dimensionIndex);
}
_MPS_INLINE void MPS::NDArrayDescriptor::sliceDimension(NS::UInteger dimensionIndex, MPS::DimensionSlice subRange){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(sliceDimension_withSubrange_), dimensionIndex, subRange);
}
_MPS_INLINE void MPS::NDArrayDescriptor::transposeDimension(NS::UInteger dimensionIndex, NS::UInteger dimensionIndex2){
    Object::sendMessage<void>(this,_MPS_PRIVATE_SEL(transposeDimension_withDimension_), dimensionIndex, dimensionIndex2);
}
_MPS_INLINE vector_uchar16 MPS::NDArrayDescriptor::dimensionOrder(){
    return Object::sendMessage<vector_uchar16>(this, _MPS_PRIVATE_SEL(dimensionOrder));
}
_MPS_INLINE MPS::NDArrayDescriptor* MPS::NDArrayDescriptor::descriptorWithDataType(MPS::DataType dataType, NS::UInteger numberOfDimensions, NS::UInteger* dimensionSizes){
    return Object::sendMessage<MPS::NDArrayDescriptor*>(_MPS_PRIVATE_CLS(MPSNDArrayDescriptor),_MPS_PRIVATE_SEL(descriptorWithDataType_dimensionCount_dimensionSizes_), dataType, numberOfDimensions, dimensionSizes);
}
_MPS_INLINE MPS::NDArrayDescriptor* MPS::NDArrayDescriptor::descriptorWithDataType(MPS::DataType dataType, NS::Array* shape){
    return Object::sendMessage<MPS::NDArrayDescriptor*>(_MPS_PRIVATE_CLS(MPSNDArrayDescriptor),_MPS_PRIVATE_SEL(descriptorWithDataType_shape_), dataType, shape);
}
_MPS_INLINE void MPS::NDArrayDescriptor::reshapeWithDimensionCount(NS::UInteger numberOfDimensions, NS::UInteger* dimensionSizes){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(reshapeWithDimensionCount_dimensionSizes_), numberOfDimensions, dimensionSizes);
}
_MPS_INLINE void MPS::NDArrayDescriptor::reshapeWithShape(NS::Array* shape){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(reshapeWithShape_), shape);
}

//class NDArrayAllocator
_MPS_INLINE MPS::NDArrayAllocator* MPS::NDArrayAllocator::alloc(){
    //return Object::sendMessage<MPS::NDArrayAllocator*>(_MPS_PRIVATE_CLS(MPSNDArrayAllocator), _MPS_PRIVATE_SEL(alloc));
    return NS::Object::alloc<MPS::NDArrayAllocator>(_MPS_PRIVATE_CLS(MPSNDArrayAllocator));
}
_MPS_INLINE MPS::NDArrayAllocator* MPS::NDArrayAllocator::init(){
    //return Object::sendMessage<MPS::NDArrayAllocator*>(_MPS_PRIVATE_CLS(MPSNDArray), _MPS_PRIVATE_SEL(init));
    return NS::Object::init<MPS::NDArrayAllocator>();
}
_MPS_INLINE MPS::NDArray* MPS::NDArrayAllocator::arrayForCommandBuffer(MTL::CommandBuffer* cmdBuf, MPS::NDArrayDescriptor* descriptor, MPS::Kernel* kernel){
    return Object::sendMessage<MPS::NDArray*>(this, _MPS_PRIVATE_SEL(arrayForCommandBuffer_arrayDescriptor_kernel_), cmdBuf, descriptor, kernel);
}

//class NDArray
_MPS_INLINE MPS::NDArrayAllocator* MPS::NDArray::defaultAllocator(){
    return Object::sendMessage<MPS::NDArrayAllocator*>(_MPS_PRIVATE_CLS(MPSNDArray), _MPS_PRIVATE_SEL(defaultAllocator));
}
_MPS_INLINE NS::String* MPS::NDArray::label(){
    return Object::sendMessage<NS::String*>(this, _MPS_PRIVATE_SEL(label));
}
_MPS_INLINE MPS::DataType MPS::NDArray::dataType() const{
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE size_t MPS::NDArray::dataTypeSize() const{
    return Object::sendMessage<size_t>(this, _MPS_PRIVATE_SEL(dataTypeSize));
}
_MPS_INLINE NS::UInteger MPS::NDArray::numberOfDimensions() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(numberOfDimensions));
}
_MPS_INLINE NS::UInteger MPS::NDArray::lengthOfDimension(NS::UInteger dimensionIndex){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(lengthOfDimension_), dimensionIndex);
}
_MPS_INLINE MTL::Device* MPS::NDArray::device() const{
    return Object::sendMessage<MTL::Device*>(this, _MPS_PRIVATE_SEL(device));
}
_MPS_INLINE MPS::NDArrayDescriptor* MPS::NDArray::descriptor(){
    return Object::sendMessage<MPS::NDArrayDescriptor*>(this, _MPS_PRIVATE_SEL(descriptor));
}
_MPS_INLINE MPS::NDArray* MPS::NDArray::initWithDevice(MTL::Device* device, NDArrayDescriptor* descriptor){
    return Object::sendMessage<MPS::NDArray*>(this, _MPS_PRIVATE_SEL(initWithDevice_descriptor_), device, descriptor);
}
_MPS_INLINE MPS::NDArray* MPS::NDArray::initWithDevice(MTL::Device* device, double value){
    return Object::sendMessage<MPS::NDArray*>(this, _MPS_PRIVATE_SEL(initWithDevice_scalar_), device, value);
}
_MPS_INLINE NS::UInteger MPS::NDArray::resourceSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(resourceSize));
}
_MPS_INLINE MPS::NDArray* MPS::NDArray::arrayViewWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MPS::NDArrayDescriptor* descriptor, MPS::AliasingStrategy aliasing){
    return Object::sendMessage<MPS::NDArray*>(this, _MPS_PRIVATE_SEL(arrayViewWithCommandBuffer_descriptor_aliasing_), cmdBuf, descriptor, aliasing);
}
_MPS_INLINE MPS::NDArray* MPS::NDArray::parent() const{
    return Object::sendMessage<MPS::NDArray*>(this, _MPS_PRIVATE_SEL(parent));
}
_MPS_INLINE void MPS::NDArray::exportDataWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MTL::Buffer* buffer, MPS::DataType destinationDataType, NS::UInteger offset, NS::Integer* rowStrides){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(exportDataWithCommandBuffer_toBuffer_destinationDataType_offset_rowStrides_), cmdBuf, buffer, destinationDataType, offset, rowStrides);
}
_MPS_INLINE void MPS::NDArray::importDataWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MTL::Buffer* buffer, MPS::DataType sourceDataType, NS::UInteger offset, NS::Integer* rowStrides){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(importDataWithCommandBuffer_fromBuffer_sourceDataType_offset_rowStrides_), cmdBuf, buffer, sourceDataType, offset, rowStrides);
}
_MPS_INLINE void MPS::NDArray::readBytes(void* buffer, NS::Integer* strideBytesPerDimension){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(readBytes_strideBytes_), buffer, strideBytesPerDimension);
}
_MPS_INLINE void MPS::NDArray::writeBytes(void* buffer, NS::Integer* strideBytesPerDimension){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(writeBytes_strideBytes_), buffer, strideBytesPerDimension);
}
_MPS_INLINE void MPS::NDArray::synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(synchronizeOnCommandBuffer_), commandBuffer);
}

// class TemporaryNDArray
_MPS_INLINE MPS::NDArrayAllocator* MPS::TemporaryNDArray::defaultAllocator(){
    return Object::sendMessage<MPS::NDArrayAllocator*>(_MPS_PRIVATE_CLS(MPSTemporaryNDArray), _MPS_PRIVATE_SEL(defaultAllocator));
}
// _MPS_INLINE MPS::TemporaryNDArray* MPS::TemporaryNDArray::initWithDevice(MTL::Device* device, MPS::NDArrayDescriptor* descriptor){
//     return Object::sendMessage<MPS::TemporaryNDArray*>(_MPS_PRIVATE_CLS(MPSTemporaryNDArray), _MPS_PRIVATE_SEL(initWithDevice_), device, descriptor);
// } USE INIT WITH CMD BUF INSTEAD
_MPS_INLINE NS::UInteger MPS::TemporaryNDArray::readCount(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(readCount));
}

_MPS_INLINE MPS::TemporaryNDArray* MPS::TemporaryNDArray::temporaryNDArrayWithCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::NDArrayDescriptor* descriptor){
    return Object::sendMessage<MPS::TemporaryNDArray*>(_MPS_PRIVATE_CLS(MPSTemporaryNDArray), _MPS_PRIVATE_SEL(temporaryNDArrayWithCommandBuffer_descriptor_), commandBuffer, descriptor);
}

/// @}