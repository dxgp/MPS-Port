#pragma once
#include "MPSPrivate.hpp"

namespace MPS::Private::Class
{
    // _MTL_PRIVATE_DEF_CLS(MTLAccelerationStructureBoundingBoxGeometryDescriptor);
    //MPSNDArray
    _MPS_PRIVATE_DEF_CLS(MPSNDArrayAllocator);
    _MPS_PRIVATE_DEF_CLS(MPSNDArray);
    _MPS_PRIVATE_DEF_CLS(MPSNDArrayDescriptor);
    _MPS_PRIVATE_DEF_CLS(MPSTemporaryNDArray);
    
    //MPSCommandBuffer
    _MPS_PRIVATE_DEF_CLS(MPSPredicate);
    _MPS_PRIVATE_DEF_CLS(MPSCommandBuffer);

    //MPSKernel
    _MPS_PRIVATE_DEF_CLS(MPSKernel);

    //MPSMatrix
    _MPS_PRIVATE_DEF_CLS(MPSMatrix);
    _MPS_PRIVATE_DEF_CLS(MPSVector);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixDescriptor);
    _MPS_PRIVATE_DEF_CLS(MPSVectorDescriptor);

    //MPSMatrixMultiplication
    _MPS_PRIVATE_DEF_CLS(MPSMatrixMultiplication);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixVectorMultiplication);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixFindTopK);
    
    //MPSMatrixDecomposition
    _MPS_PRIVATE_DEF_CLS(MPSMatrixDecompositionLU);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixDecompositionCholesky);

    //MPSMatrixRandom
    _MPS_PRIVATE_DEF_CLS(MPSMatrixRandomDistributionDescriptor);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixRandomMTGP32);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixRandomPhilox);

    //MPSMatrixSoftMax
    _MPS_PRIVATE_DEF_CLS(MPSMatrixSoftMax);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixLogSoftMax);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixSoftMaxGradient);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixLogSoftMaxGradient);

    //MPSMatrixSolve
    _MPS_PRIVATE_DEF_CLS(MPSMatrixSolveTriangular);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixSolveLU);
    _MPS_PRIVATE_DEF_CLS(MPSMatrixSolveCholesky);

}

namespace MPS::Private::Protocol
{
    // _MTL_PRIVATE_DEF_PRO(MTLAccelerationStructure);
}

namespace MPS::Private::Selector
{
    // _MTL_PRIVATE_DEF_SEL(GPUEndTime,"GPUEndTime");
    //MPSNDArray
    _MPS_PRIVATE_DEF_SEL(numberOfDimensions, "numberOfDimensions");
    _MPS_PRIVATE_DEF_SEL(lengthOfDimension_, "lengthOfDimension:");
    _MPS_PRIVATE_DEF_SEL(sliceRangeForDimension_, "sliceRangeForDimension:");
    _MPS_PRIVATE_DEF_SEL(sliceDimension_withSubrange_, "sliceDimension:withSubrange:");
    _MPS_PRIVATE_DEF_SEL(transposeDimension_withDimension_, "transposeDimension:withDimension:");
    _MPS_PRIVATE_DEF_SEL(dimensionOrder, "dimensionOrder");
    _MPS_PRIVATE_DEF_SEL(descriptorWithDataType_dimensionCount_dimensionSizes_, "descriptorWithDataType:dimensionCount:dimensionSizes:");
    _MPS_PRIVATE_DEF_SEL(descriptorWithDataType_shape_, "descriptorWithDataType:shape:");
    _MPS_PRIVATE_DEF_SEL(reshapeWithDimensionCount_dimensionSizes_, "reshapeWithDimensionCount:dimensionSizes:");
    _MPS_PRIVATE_DEF_SEL(reshapeWithShape_, "reshapeWithShape:");
    _MPS_PRIVATE_DEF_SEL(alloc, "alloc:");
    _MPS_PRIVATE_DEF_SEL(init, "init");
    _MPS_PRIVATE_DEF_SEL(arrayForCommandBuffer_arrayDescriptor_kernel_, "arrayForCommandBuffer:arrayDescriptor:kernel:");
    _MPS_PRIVATE_DEF_SEL(defaultAllocator, "defaultAllocator");
    _MPS_PRIVATE_DEF_SEL(label, "label");
    _MPS_PRIVATE_DEF_SEL(dataType, "dataType");
    _MPS_PRIVATE_DEF_SEL(dataTypeSize, "dataTypeSize");
    _MPS_PRIVATE_DEF_SEL(device, "device");
    _MPS_PRIVATE_DEF_SEL(descriptor, "descriptor");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_descriptor_, "initWithDevice:descriptor:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_scalar_, "initWithDevice:scalar:");
    _MPS_PRIVATE_DEF_SEL(resourceSize, "resoureSize");
    _MPS_PRIVATE_DEF_SEL(arrayViewWithCommandBuffer_descriptor_aliasing_, "arrayViewWithCommandBuffer:descriptor:aliasing:");
    _MPS_PRIVATE_DEF_SEL(parent, "parent");
    _MPS_PRIVATE_DEF_SEL(exportDataWithCommandBuffer_toBuffer_destinationDataType_offset_rowStrides_, "exportDataWithCommandBuffer:toBuffer:destinationDataType:offset:rowStrides:");
    _MPS_PRIVATE_DEF_SEL(importDataWithCommandBuffer_fromBuffer_sourceDataType_offset_rowStrides_, "importDataWithCommandBuffer:fromBuffer:sourceDataType:offset:rowStrides:");
    _MPS_PRIVATE_DEF_SEL(readBytes_strideBytes_, "readBytes:strideBytes:");
    _MPS_PRIVATE_DEF_SEL(writeBytes_strideBytes_, "writeBytes:strideBytes:");
    _MPS_PRIVATE_DEF_SEL(synchronizeOnCommandBuffer_, "synchronizeOnCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(readCount, "readCount");
    _MPS_PRIVATE_DEF_SEL(temporaryNDArrayWithCommandBuffer_descriptor_, "temporaryNDArrayWithCommandBuffer:descriptor:");
    
    //MPSCommandBuffer
    _MPS_PRIVATE_DEF_SEL(predicateBuffer, "predicateBuffer");
    _MPS_PRIVATE_DEF_SEL(predicateOffset, "predicateOffset");
    _MPS_PRIVATE_DEF_SEL(predicateWithBuffer_offset_, "predicateWithBuffer:offset:");
    _MPS_PRIVATE_DEF_SEL(initWithBuffer_offset_, "initWithBuffer:offset:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_, "initWithDevice:");
    _MPS_PRIVATE_DEF_SEL(newHeapWithDescriptor_, "newHeapWithDescriptor:");
    _MPS_PRIVATE_DEF_SEL(retireHeap_cacheDelay_, "retireHeap:cacheDelay:");
    _MPS_PRIVATE_DEF_SEL(commandBuffer, "commandBuffer");
    _MPS_PRIVATE_DEF_SEL(rootCommandBuffer, "rootCommandBuffer");
    _MPS_PRIVATE_DEF_SEL(predicate, "predicate");
    _MPS_PRIVATE_DEF_SEL(heapProvider, "heapProvider");
    _MPS_PRIVATE_DEF_SEL(commandBufferWithCommandBuffer_, "commandBufferWithCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(commandBufferFromCommandQueue_, "commandBufferFromCommandQueue:");
    _MPS_PRIVATE_DEF_SEL(initWithCommandBuffer_, "initWithCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(commitAndContinue, "commitAndContinue");
    _MPS_PRIVATE_DEF_SEL(prefetchHeapForWorkloadSize_, "prefetchHeapForWorkloadSize:");

    //MPSKernel
    _MPS_PRIVATE_DEF_SEL(options, "options");
    _MPS_PRIVATE_DEF_SEL(initWithCoder_, "initWithCoder:");
    _MPS_PRIVATE_DEF_SEL(initWithCoder_device_, "initWithCoder:device:");

    //MPSMatrix
    _MPS_PRIVATE_DEF_SEL(rows, "rows");
    _MPS_PRIVATE_DEF_SEL(columns, "columns");
    _MPS_PRIVATE_DEF_SEL(matrices, "matrices");
    _MPS_PRIVATE_DEF_SEL(rowBytes, "rowBytes");
    _MPS_PRIVATE_DEF_SEL(matrixBytes, "matrixBytes");
    _MPS_PRIVATE_DEF_SEL(matrixDescriptorWithRows_columns_rowBytes_dataType_, "matrixDescriptorWithRows:columns:rowBytes:dataType:");
    _MPS_PRIVATE_DEF_SEL(matrixDescriptorWithRows_columns_matrices_rowBytes_matrixBytes_dataType_, "matrixDescriptorWithRows:columns:matrices:rowBytes:matrixBytes:dataType:");
    _MPS_PRIVATE_DEF_SEL(rowBytesForColumns_dataType_, "rowBytesForColumns:dataType:");
    _MPS_PRIVATE_DEF_SEL(length, "length");
    _MPS_PRIVATE_DEF_SEL(vectors, "vectors");
    _MPS_PRIVATE_DEF_SEL(vectorBytes, "vectorBytes");
    _MPS_PRIVATE_DEF_SEL(vectorDescriptorWithLength_dataType_, "vectorDescriptorWithLength:dataType:");
    _MPS_PRIVATE_DEF_SEL(vectorDescriptorWithLength_vectors_vectorBytes_dataType_, "vectorDescriptorWithLength:vectors:vectorBytes:dataType:");
    _MPS_PRIVATE_DEF_SEL(vectorBytesForLength_dataType_, "vectorBytesForLength:dataType:");
    _MPS_PRIVATE_DEF_SEL(offset, "offset");
    _MPS_PRIVATE_DEF_SEL(data, "data");
    _MPS_PRIVATE_DEF_SEL(initWithBuffer_descriptor_, "initWithBuffer:descriptor:");
    _MPS_PRIVATE_DEF_SEL(initWithBuffer_offset_descriptor_, "initWithBuffer:offset:descriptor:");
    _MPS_PRIVATE_DEF_SEL(temporaryMatrixWithCommandBuffer_matrixDescriptor_, "temporaryMatrixWithCommandBuffer:matrixDescriptor:");
    _MPS_PRIVATE_DEF_SEL(prefetchStorageWithCommandBuffer_matrixDescriptorList_, "prefetchStorageWithCommandBuffer:matrixDescriptorList:");
    _MPS_PRIVATE_DEF_SEL(temporaryVectorWithCommandBuffer_descriptor_, "temporaryVectorWithCommandBuffer:descriptor:");
    _MPS_PRIVATE_DEF_SEL(prefetchStorageWithCommandBuffer_descriptorList_, "prefetchStorageWithCommandBuffer:descriptorList:");

    //MPSMatrixTypes
    _MPS_PRIVATE_DEF_SEL(sourceMatrixOrigin, "sourceMatrixOrigin");
    _MPS_PRIVATE_DEF_SEL(resultMatrixOrigin, "resultMatrixOrigin");
    _MPS_PRIVATE_DEF_SEL(batchStart, "batchStart");
    _MPS_PRIVATE_DEF_SEL(batchSize, "batchSize");
    _MPS_PRIVATE_DEF_SEL(primarySourceMatrixOrigin, "primarySourceMatrixOrigin");
    _MPS_PRIVATE_DEF_SEL(secondarySourceMatrixOrigin, "secondarySourceMatrixOrigin");

    //MPSMatrixMultiplication
    _MPS_PRIVATE_DEF_SEL(leftMatrixOrigin, "leftMatrixOrigin");
    _MPS_PRIVATE_DEF_SEL(rightMatrixOrigin, "rightMatrixOrigin");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_transposeLeft_transposeRight_resultRows_resultColumns_interiorColumns_alpha_beta_, "initWithDevice:transposeLeft:transposeRight:resultRows:resultColumns:interiorColumns:alpha:beta:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_resultRows_resultColumns_interiorColumns_, "initWithDevice:resultRows:resultColumns:interiorColumns:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_rows_columns_, "initWithDevice:rows:columns:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_leftMatrix_rightMatrix_resultMatrix_, "encodeToCommandBuffer:leftMatrix:rightMatrix:resultMatrix:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_transpose_rows_columns_alpha_beta_, "initWithDevice:transpose:rows:columns:alpha:beta:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_inputMatrix_inputVector_resultVector_, "encodeToCommandBuffer:inputMatrix:inputVector:resultVector:");

    //MPSMatrixFindTopK
    _MPS_PRIVATE_DEF_SEL(sourceRows, "sourceRows");
    _MPS_PRIVATE_DEF_SEL(sourceColumns, "sourceColumns");
    _MPS_PRIVATE_DEF_SEL(indexOffset, "indexOffset");
    _MPS_PRIVATE_DEF_SEL(numberOfTopKValues, "numberOfTopKValues");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_numberOfTopKValues_, "initWithDevice:numberOfTopKValues:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_inputMatrix_resultIndexMatrix_resultValueMatrix_, "encodeToCommandBuffer:inputMatrix:resultIndexMatrix:resultValueMatrix:");


    //MPSMatrixDecomposition
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_sourceMatrix_resultMatrix_pivotIndices_status_, "encodeToCommandBuffer:sourceMatrix:resultMatrix:pivotIndices:status:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_lower_order_, "initWithDevice:lower:order:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_sourceMatrix_resultMatrix_status_, "encodeToCommandBuffer:sourceMatrix:resultMatrix:status:");

    //MPSMatrixRandom
    _MPS_PRIVATE_DEF_SEL(distributionType, "distributionType");
    _MPS_PRIVATE_DEF_SEL(minimum, "minimum");
    _MPS_PRIVATE_DEF_SEL(maximum, "maximum");
    _MPS_PRIVATE_DEF_SEL(mean, "mean");
    _MPS_PRIVATE_DEF_SEL(standardDeviation, "standardDeviation");
    _MPS_PRIVATE_DEF_SEL(uniformDistributionDescriptorWithMinimum_maximum_, "uniformDistributionDescriptorWithMinimum:maximum:");
    _MPS_PRIVATE_DEF_SEL(normalDistributionDescriptorWithMean_standardDeviation_, "normalDistributionDescriptorWithMean:standardDeviation:");
    _MPS_PRIVATE_DEF_SEL(normalDistributionDescriptorWithMean_standardDeviation_minimum_maximum_, "normalDistributionDescriptorWithMean:standardDeviation:minimum:maximum:");
    _MPS_PRIVATE_DEF_SEL(defaultDistributionDescriptor, "defaultDistributionDescriptor");
    _MPS_PRIVATE_DEF_SEL(destinationDataType, "destinationDataType");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_destinationDataType_seed_distributionDescriptor_, "initWithDevice:destinationDataType:seed:distributionDescriptor:");
    _MPS_PRIVATE_DEF_SEL(synchronizeStateOnCommandBuffer_, "synchronizeStateOnCommandBuffer:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_destinationDataType_seed_, "initWithDevice:destinationDataType:seed:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_destinationVector_, "encodeToCommandBuffer:destinationVector:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_destinationMatrix_, "encodeToCommandBuffer:destinationMatrix:");

    //MPSMatrixSoftMax
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_inputMatrix_resultMatrix_, "encodeToCommandBuffer:inputMatrix:resultMatrix:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_gradientMatrix_forwardOutputMatrix_resultMatrix_, "encodeToCommandBuffer:gradientMatrix:forwardOutputMatrix:resultMatrix:");

    //MPSMatrixSolve
    _MPS_PRIVATE_DEF_SEL(initWithDevice_right_upper_transpose_unit_order_numberOfRightHandSides_alpha_, "initWithDevice:right:upper:transpose:unit:order:numberOfRightHandSides:alpha:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_sourceMatrix_rightHandSideMatrix_solutionMatrix_, "encodeToCommandBuffer:sourceMatrix:rightHandSideMatrix:solutionMatrix:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_transpose_order_numberOfRightHandSides_, "initWithDevice:transpose:order:numberOfRightHandSides:");
    _MPS_PRIVATE_DEF_SEL(encodeToCommandBuffer_sourceMatrix_rightHandSideMatrix_pivotIndices_solutionMatrix_, "encodeToCommandBuffer:sourceMatrix:rightHandSideMatrix:pivotIndices:solutionMatrix:");
    _MPS_PRIVATE_DEF_SEL(initWithDevice_upper_order_numberOfRightHandSides_, "initWithDevice:upper:order:numberOfRightHandSides:");

}