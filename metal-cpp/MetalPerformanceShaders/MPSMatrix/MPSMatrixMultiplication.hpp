#pragma once
#include "../MPSCore/MPSKernel.hpp"
#include "MPSMatrixTypes.hpp"

namespace MPS{
    class MatrixMultiplication: public NS::Referencing<MPS::Kernel>{
        public:
        static MPS::MatrixMultiplication* alloc();
        MTL::Origin resultMatrixOrigin();
        MTL::Origin leftMatrixOrigin();
        MTL::Origin rightMatrixOrigin();
        NS::UInteger batchStart();
        NS::UInteger batchSize();
        // interior columns refers to the number of columns of the left input matrix i.e. the common thread in the two matrices.
        // this is the op being performed: C = alpha * op(A) * op(B) + beta * C
        MPS::MatrixMultiplication* initWithDevice(MTL::Device* device, bool transposeLeft, bool transposeRight, NS::UInteger resultRows, NS::UInteger resultColumns, NS::UInteger interiorColumns, double alpha, double beta);
        //default alpha is 1.0 and beta is 0.0
        MPS::MatrixMultiplication* initWithDevice(MTL::Device* device, NS::UInteger resultRows, NS::UInteger resultColumns, NS::UInteger interiorColumns);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* leftMatrix, MPS::Matrix* rightMatrix, MPS::Matrix* resultMatrix);
    };
    class MatrixVectorMultiplication: public NS::Referencing<MPS::MatrixBinaryKernel>{
        public:
        static MPS::MatrixVectorMultiplication* alloc();
        MPS::MatrixVectorMultiplication* initWithDevice(MTL::Device* device, bool transpose, NS::UInteger rows, NS::UInteger columns, double alpha, double beta);
        MPS::MatrixVectorMultiplication* initWithDevice(MTL::Device* device, NS::UInteger rows, NS::UInteger columns);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Vector* inputVector, MPS::Vector* resultVector);
    };
}

_MPS_INLINE MPS::MatrixMultiplication* MPS::MatrixMultiplication::alloc(){
    return NS::Object::alloc<MPS::MatrixMultiplication>(_MPS_PRIVATE_CLS(MPSMatrixMultiplication));
}
_MPS_INLINE MPS::MatrixVectorMultiplication* MPS::MatrixVectorMultiplication::alloc(){
    return NS::Object::alloc<MPS::MatrixVectorMultiplication>(_MPS_PRIVATE_CLS(MPSMatrixVectorMultiplication));
}

_MPS_INLINE MTL::Origin MPS::MatrixMultiplication::resultMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(resultMatrixOrigin));
}


_MPS_INLINE MTL::Origin MPS::MatrixMultiplication::leftMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(leftMatrixOrigin));
}


_MPS_INLINE MTL::Origin MPS::MatrixMultiplication::rightMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(rightMatrixOrigin));
}


_MPS_INLINE NS::UInteger MPS::MatrixMultiplication::batchStart(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchStart));
}


_MPS_INLINE NS::UInteger MPS::MatrixMultiplication::batchSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchSize));
}


_MPS_INLINE MPS::MatrixMultiplication* MPS::MatrixMultiplication::initWithDevice(MTL::Device* device, bool transposeLeft, bool transposeRight, NS::UInteger resultRows, NS::UInteger resultColumns, NS::UInteger interiorColumns, double alpha, double beta){
    return Object::sendMessage<MPS::MatrixMultiplication*>(this, _MPS_PRIVATE_SEL(initWithDevice_transposeLeft_transposeRight_resultRows_resultColumns_interiorColumns_alpha_beta_), device, transposeLeft, transposeRight, resultRows, resultColumns, interiorColumns, alpha, beta);
}


_MPS_INLINE MPS::MatrixMultiplication* MPS::MatrixMultiplication::initWithDevice(MTL::Device* device, NS::UInteger resultRows, NS::UInteger resultColumns, NS::UInteger interiorColumns){
    return Object::sendMessage<MPS::MatrixMultiplication*>(this, _MPS_PRIVATE_SEL(initWithDevice_resultRows_resultColumns_interiorColumns_), device, resultRows, resultColumns, interiorColumns);
}


_MPS_INLINE void MPS::MatrixMultiplication::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* leftMatrix, MPS::Matrix* rightMatrix, MPS::Matrix* resultMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_leftMatrix_rightMatrix_resultMatrix_), commandBuffer, leftMatrix, rightMatrix, resultMatrix);
}


_MPS_INLINE MPS::MatrixVectorMultiplication* MPS::MatrixVectorMultiplication::initWithDevice(MTL::Device* device, bool transpose, NS::UInteger rows, NS::UInteger columns, double alpha, double beta){
    return Object::sendMessage<MPS::MatrixVectorMultiplication*>(this, _MPS_PRIVATE_SEL(initWithDevice_transpose_rows_columns_alpha_beta_), device, transpose, rows, columns, alpha, beta);
}

_MPS_INLINE MPS::MatrixVectorMultiplication* MPS::MatrixVectorMultiplication::initWithDevice(MTL::Device* device, NS::UInteger rows, NS::UInteger columns){
    return Object::sendMessage<MPS::MatrixVectorMultiplication*>(this, _MPS_PRIVATE_SEL(initWithDevice_rows_columns_), device, rows, columns);
}
_MPS_INLINE void MPS::MatrixVectorMultiplication::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Vector* inputVector, MPS::Vector* resultVector){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_inputMatrix_inputVector_resultVector_), commandBuffer, inputMatrix, inputVector, resultVector);
}
