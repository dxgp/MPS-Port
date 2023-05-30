#pragma once
#include "MPSPrivate.hpp"

namespace MPS::Private::Class
{
    // _MTL_PRIVATE_DEF_CLS(MTLAccelerationStructureBoundingBoxGeometryDescriptor);
    _MPS_PRIVATE_DEF_CLS(MPSNDArrayAllocator);
    _MPS_PRIVATE_DEF_CLS(MPSNDArray);
    _MPS_PRIVATE_DEF_CLS(MPSNDArrayDescriptor);
    _MPS_PRIVATE_DEF_CLS(MPSTemporaryNDArray);
    
}

namespace MPS::Private::Protocol
{
    // _MTL_PRIVATE_DEF_PRO(MTLAccelerationStructure);
}

namespace MPS::Private::Selector
{
    // _MTL_PRIVATE_DEF_SEL(GPUEndTime,"GPUEndTime");
    _MPS_PRIVATE_DEF_SEL(numberOfDimensions, "numberOfDimensions");
    _MPS_PRIVATE_DEF_SEL(sliceRangeForDimension_, "sliceRangeForDimension:");
    _MPS_PRIVATE_DEF_SEL(sliceDimension_, "sliceDimension:");
    _MPS_PRIVATE_DEF_SEL(transposeDimension_, "transposeDimension:");
    _MPS_PRIVATE_DEF_SEL(dimensionOrder, "dimensionOrder");
    _MPS_PRIVATE_DEF_SEL(descriptorWithDataType_, "descriptorWithDataType:");
    _MPS_PRIVATE_DEF_SEL(reshapeWithDimension_, "reshapeWithDimension:");
    _MPS_PRIVATE_DEF_SEL(reshapeWithShape_, "reshapeWithShape:");
    _MPS_PRIVATE_DEF_SEL(alloc, "alloc:");
    _MPS_PRIVATE_DEF_SEL(init, "init");
    _MPS_PRIVATE_DEF_SEL(arrayForCommandBuffer_, "arrayForCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(defaultAllocator, "defaultAllocator");
    _MPS_PRIVATE_DEF_SEL(label, "label");
    _MPS_PRIVATE_DEF_SEL(dataType, "dataType");
    _MPS_PRIVATE_DEF_SEL(dataTypeSize, "dataTypeSize");
    _MPS_PRIVATE_DEF_SEL(lengthOfDimension_, "lengthOfDimension:");
    _MPS_PRIVATE_DEF_SEL(device, "device");
    _MPS_PRIVATE_DEF_SEL(descriptor, "descriptor");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_, "initWithDevice:");
    _MPS_PRIVATE_DEF_SEL(resourceSize, "resoureSize");
    _MPS_PRIVATE_DEF_SEL(arrayViewWithCommandBuffer_, "arrayViewWithCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(parent, "parent");
    _MPS_PRIVATE_DEF_SEL(exportDataWithCommandBuffer_, "exportDataWithCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(importDataWithCommandBuffer_, "importDataWithCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(readBytes_, "readBytes:");
    _MPS_PRIVATE_DEF_SEL(writeBytes_, "writeBytes:");
    _MPS_PRIVATE_DEF_SEL(synchronizeOnCommandBuffer_, "synchronizeOnCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(readCount, "readCount");

}