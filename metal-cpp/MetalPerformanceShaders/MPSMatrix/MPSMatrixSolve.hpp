#pragma once
#include "MPSMatrixTypes.hpp"

namespace MPS{
    class MatrixSolveTriangular: public NS::Referencing<MPS::MatrixBinaryKernel>{
        public:
        static MPS::MatrixSolveTriangular* alloc();
        MPS::MatrixSolveTriangular* initWithDevice(MTL::Device* device, bool right, bool upper, bool transpose, bool unit, NS::UInteger order, NS::UInteger numberOfRightHandSides, double alpha);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* rightHandSideMatrix, MPS::Matrix* solutionMatrix);
    };
    class MatrixSolveLU: public NS::Referencing<MPS::MatrixBinaryKernel>{
        public:
        static MPS::MatrixSolveLU* alloc();
        MPS::MatrixSolveLU* initWithDevice(MTL::Device* device, bool transpose, NS::UInteger order, NS::UInteger numberOfRightHandSides);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* rightHandSideMatrix, MPS::Matrix* pivotIndices, MPS::Matrix* solutionMatrix);
    };
    class MatrixSolveCholesky: public NS::Referencing<MPS::MatrixBinaryKernel>{
        public:
        static MPS::MatrixSolveCholesky* alloc();
        MPS::MatrixSolveCholesky* initWithDevice(MTL::Device* device, bool upper, NS::UInteger order, NS::UInteger numberOfRightHandSides);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* rightHandSideMatrix, MPS::Matrix* solutionMatrix);
    };
}
/// @{ @private
_MPS_INLINE MPS::MatrixSolveTriangular* MPS::MatrixSolveTriangular::alloc(){
    return NS::Object::alloc<MPS::MatrixSolveTriangular>(_MPS_PRIVATE_CLS(MPSMatrixSolveTriangular));
}
_MPS_INLINE MPS::MatrixSolveTriangular* MPS::MatrixSolveTriangular::initWithDevice(MTL::Device* device, bool right, bool upper, bool transpose, bool unit, NS::UInteger order, NS::UInteger numberOfRightHandSides, double alpha){
    return Object::sendMessage<MPS::MatrixSolveTriangular*>(this, _MPS_PRIVATE_SEL(initWithDevice_right_upper_transpose_unit_order_numberOfRightHandSides_alpha_),device, right, upper, transpose, unit, order, numberOfRightHandSides, alpha);
}
_MPS_INLINE void MPS::MatrixSolveTriangular::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* rightHandSideMatrix, MPS::Matrix* solutionMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_sourceMatrix_rightHandSideMatrix_solutionMatrix_),commandBuffer, sourceMatrix, rightHandSideMatrix, solutionMatrix);
}


_MPS_INLINE MPS::MatrixSolveLU* MPS::MatrixSolveLU::alloc(){
    return NS::Object::alloc<MPS::MatrixSolveLU>(_MPS_PRIVATE_CLS(MPSMatrixSolveLU));
}
_MPS_INLINE MPS::MatrixSolveLU* MPS::MatrixSolveLU::initWithDevice(MTL::Device* device, bool transpose, NS::UInteger order, NS::UInteger numberOfRightHandSides){
    return Object::sendMessage<MPS::MatrixSolveLU*>(this, _MPS_PRIVATE_SEL(initWithDevice_transpose_order_numberOfRightHandSides_),device, transpose, order, numberOfRightHandSides);
}
_MPS_INLINE void MPS::MatrixSolveLU::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* rightHandSideMatrix, MPS::Matrix* pivotIndices, MPS::Matrix* solutionMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_sourceMatrix_rightHandSideMatrix_pivotIndices_solutionMatrix_),commandBuffer, sourceMatrix, rightHandSideMatrix, pivotIndices, solutionMatrix);
}


_MPS_INLINE MPS::MatrixSolveCholesky* MPS::MatrixSolveCholesky::alloc(){
    return NS::Object::alloc<MPS::MatrixSolveCholesky>(_MPS_PRIVATE_CLS(MPSMatrixSolveCholesky));
}
_MPS_INLINE MPS::MatrixSolveCholesky* MPS::MatrixSolveCholesky::initWithDevice(MTL::Device* device, bool upper, NS::UInteger order, NS::UInteger numberOfRightHandSides){
    return Object::sendMessage<MPS::MatrixSolveCholesky*>(this, _MPS_PRIVATE_SEL(initWithDevice_upper_order_numberOfRightHandSides_),device, upper, order, numberOfRightHandSides);
}
_MPS_INLINE void MPS::MatrixSolveCholesky::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* rightHandSideMatrix, MPS::Matrix* solutionMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_sourceMatrix_rightHandSideMatrix_solutionMatrix_),commandBuffer, sourceMatrix, rightHandSideMatrix, solutionMatrix);
}

/// @}