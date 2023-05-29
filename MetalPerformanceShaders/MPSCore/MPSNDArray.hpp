#pragma once

#include "MPSCoreTypes.hpp"
#include "../../Metal/MTLBuffer.hpp"
#include <simd/simd.h>
#include "../../Foundation/Foundation.hpp"

// note: maybe clang can use the _nonnull attribute. Check it out?
namespace MPS{
    class Matrix{};
    class MatrixDescriptor{};
    // class Image{};
    typedef NS::Array* MPSImageBatch;
    class NDArrayDescriptor: NS::Referencing<NDArrayDescriptor>{
        MPS::DataType dataType();
        NS::UInteger numberOfDimensions();
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
    class Kernel{};
    // should I put NS::Referencing?????
    class NDArrayAllocator: NS::SecureCoding<NDArrayAllocator>, NS::Copying<NDArrayAllocator>{
        MPS::NDArray* arrayForoomandBuufer(MTL::CommandBuffer* cmdBuf, MPS::NDArrayDescriptor* descriptor, MPS::Kernel* kernel);
    };
    class NDArray: NS::Referencing<NDArray>{
        static NDArrayAllocator* defaultAllocator();
        NS::String* label();
        MPS::DataType dataType() const;
        size_t dataTypeSize() const;
        NS::UInteger numberOfDimensions() const;
        NS::UInteger lengthOfDimension(NS::UInteger dimsionIndex);
        MTL::Device* device() const;
        MPS::NDArrayDescriptor* descriptor();
        MPS::NDArray* initWithDevice(MTL::Device* device, NDArrayDescriptor* descriptor);
        MPS::NDArray* initWithDevice(MTL::Device* device, double value);
        NS::UInteger resourceSize();
        MPS::NDArray* arrayViewWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MPS::NDArrayDescriptor descriptor, MPS::AliasingStrategy aliasing);
        MPS::NDArray* parent() const;
        void exportDataWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MTL::Buffer* buffer, MPS::DataType destinationDataType, NS::UInteger offset, NS::Integer rowStrides);
        void importDataWithCommandBuffer(MTL::CommandBuffer* cmdBuf, MTL::Buffer* buffer, MPS::DataType sourceDataType, NS::UInteger offset, NS::Integer* rowStrides);
        // Note: Left two more initializers related to images here.
        void readBytes(void* buffer, NS::Integer* strideBytesPerDimension);
        void writeBytes(void* buffer, NS::Integer* strideBytesPerDimension);
        void synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer);
    }; 
    class TemporaryNDArray: NS::Referencing<MPS::NDArray>{
        static MPS::NDArrayAllocator* defaultAllocator;
        static MPS::TemporaryNDArray initWithDevice(MTL::Device device, MPS::NDArrayDescriptor* descriptor);
        NS::UInteger readCount();
    };
}

_MPS_INLINE MPS::DataType MPS::NDArrayDescriptor::dataType(){
    return Object::sendMessage<MPS::DataType>(this,_MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE NS::UInteger MPS::NDArrayDescriptor::numberOfDimensions(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(numberOfDimensions));
}
_MPS_INLINE MPS::DimensionSlice MPS::NDArrayDescriptor::sliceRangeForDimension(NS::UInteger dimensionIndex){
    return Object::sendMessage<MPS::DimensionSlice>(this, _MPS_PRIVATE_SEL(sliceRangeForDimension_), dimensionIndex);
}
_MPS_INLINE void MPS::NDArrayDescriptor::sliceDimension(NS::UInteger dimensionIndex, MPS::DimensionSlice subRange){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(sliceDimension_), dimensionIndex, subRange);
}
_MPS_INLINE void MPS::NDArrayDescriptor::transposeDimension(NS::UInteger dimensionIndex, NS::UInteger dimensionIndex2){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(this, _MPS_PRIVATE_SEL(transposeDimension_), dimensionIndex, dimensionIndex2));
}
_MPS_INLINE vector_uchar16 MPS::NDArrayDescriptor::dimensionOrder(){
    return Object::sendMessage<vector_uchar16>(this, _MPS_PRIVATE_SEL(dimensionOrder));
}
_MPS_INLINE MPS::NDArrayDescriptor* MPS::NDArrayDescriptor::descriptorWithDataType(MPS::DataType, NS::UInteger numberOfDimensions, NS::UInteger* dimensionSizes){
    return Object::sendMessage<MPS::NDArrayDescriptor*>(_MPS_PRIVATE_CLS(MPSNDArrayDescriptor),_MPS_PRIVATE_SEL(descriptorWithDataType_), dataType, numberOfDimensions, dimensionSizes);
}


