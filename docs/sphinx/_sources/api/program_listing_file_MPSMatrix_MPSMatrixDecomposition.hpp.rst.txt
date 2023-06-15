
.. _program_listing_file_MPSMatrix_MPSMatrixDecomposition.hpp:

Program Listing for File MPSMatrixDecomposition.hpp
===================================================

|exhale_lsh| :ref:`Return to documentation for file <file_MPSMatrix_MPSMatrixDecomposition.hpp>` (``MPSMatrix/MPSMatrixDecomposition.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "MPSMatrixTypes.hpp"
   
   
   namespace MPS{
       _NS_ENUM(int, MatrixDecompositionStatus){
           MatrixDecompositionStatusSuccess = 0,
           MatrixDecompositionStatusFailure = -1,
           MatrixDecompositionStatusSingular = -2,
           MatrixDecompositionStatusNonPositiveDefinite = -3,
       };
       class MatrixDecompositionLU: public NS::Referencing<MPS::MatrixUnaryKernel>{
           public:
           static MPS::MatrixDecompositionLU* alloc();
           MPS::MatrixDecompositionLU* initWithDevice(MTL::Device* device, NS::UInteger rows, NS::UInteger columns);
           // pivot indices matrix must be of types MPSDataTypeUInt32 and must also have enough space to hold an array of size 1xmin(rows, columns)
           // source matrix must have enough space to contain rows*columns elements
           void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* resultMatrix, MPS::Matrix* pivotIndices, MTL::Buffer* status);
       };
       class MatrixDecompositionCholesky: public NS::Referencing<MPS::MatrixUnaryKernel>{
           public:
           static MPS::MatrixDecompositionCholesky* alloc();
           MPS::MatrixDecompositionCholesky* initWithDevice(MTL::Device* device, bool lower, NS::UInteger order);
           void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* resultMatrix, MTL::Buffer* status);
       };
   }
   _MPS_INLINE MPS::MatrixDecompositionLU* MPS::MatrixDecompositionLU::alloc(){
       return NS::Object::alloc<MPS::MatrixDecompositionLU>(_MPS_PRIVATE_CLS(MPSMatrixDecompositionLU));
   }
   _MPS_INLINE MPS::MatrixDecompositionLU* MPS::MatrixDecompositionLU::initWithDevice(MTL::Device* device, NS::UInteger rows, NS::UInteger columns){
       return Object::sendMessage<MPS::MatrixDecompositionLU*>(this, _MPS_PRIVATE_SEL(initWithDevice_rows_columns_), device, rows, columns);
   }
   _MPS_INLINE void MPS::MatrixDecompositionLU::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* resultMatrix, MPS::Matrix* pivotIndices, MTL::Buffer* status){
       Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_sourceMatrix_resultMatrix_pivotIndices_status_), commandBuffer, sourceMatrix, resultMatrix, pivotIndices, status);
   }
   _MPS_INLINE MPS::MatrixDecompositionCholesky* MPS::MatrixDecompositionCholesky::alloc(){
       return NS::Object::alloc<MPS::MatrixDecompositionCholesky>(_MPS_PRIVATE_CLS(MPSMatrixDecompositionCholesky));
   }
   _MPS_INLINE MPS::MatrixDecompositionCholesky* MPS::MatrixDecompositionCholesky::initWithDevice(MTL::Device* device, bool lower, NS::UInteger order){
       return Object::sendMessage<MPS::MatrixDecompositionCholesky*>(this, _MPS_PRIVATE_SEL(initWithDevice_lower_order_), device, lower, order);
   }
   _MPS_INLINE void MPS::MatrixDecompositionCholesky::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* sourceMatrix, MPS::Matrix* resultMatrix, MTL::Buffer* status){
       Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_sourceMatrix_resultMatrix_status_), commandBuffer, sourceMatrix, resultMatrix, status);
   }
   
