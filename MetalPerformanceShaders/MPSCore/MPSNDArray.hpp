#pragma once

#include "MPSCoreTypes.hpp"
#include "../../Metal/MTLBuffer.hpp"
#include <simd/simd.h>

// note: maybe clang can use the _nonnull attribute. Check it out?
typedef NS::Array* MPSImageBatch;
namespace MPS{
    class NDArrayDescriptor: NS::Referencing<NDArrayDescriptor>{
        MPS::DataType dataType();
        NS::UInteger numberOfDimensions();
        MPS::DimensionSlice sliceRangeForDimension(NS::UInteger dimensionIndex);
        void  sliceDimension(NS::UInteger dimsionIndex, MPS::DimensionSlice subRange);
        void transposeDimension(NS::UInteger dimensionIndex, NS::UInteger dimensionIndex2);
        vector_uchar16 dimensionOrder();
        // NOTE: Replace dimensionSizes with NS::Size::Make?? A lot easier.
        static MPS::NDArrayDescriptor* descriptorWithDataType(MPS::DataType dataType, NS::UInteger numberOfDimension, NS::UInteger* dimsionSizes);
        // NOTE: THIS IS ALSO A LITTLE DICEY
        static MPS::NDArrayDescriptor* descriptorWithDataType(MPS::DataType dataType, NS::Array* shape);
        //static NDArrayDescriptor* descriptorWithDatType(MPS::DataType dataType, ...) While cpp 11 does support varidic args, this won't work. internal implementational details will differ
        void reshapeWithDimensionCount(NS::UInteger numberOfDimensions, NS::UInteger* dimensionSizes);
        void reshapeWithShape(NS::Array* shape);
    };
    // should I put NS::Referencing?????
    class NDArrayAllocator: NS::SecureCoding<NDArrayAllocator>, NS::Copying<NDArrayAllocator>{
        
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
