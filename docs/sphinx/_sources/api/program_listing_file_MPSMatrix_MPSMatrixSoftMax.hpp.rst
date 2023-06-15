
.. _program_listing_file_MPSMatrix_MPSMatrixSoftMax.hpp:

Program Listing for File MPSMatrixSoftMax.hpp
=============================================

|exhale_lsh| :ref:`Return to documentation for file <file_MPSMatrix_MPSMatrixSoftMax.hpp>` (``MPSMatrix/MPSMatrixSoftMax.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   
   #include "MPSMatrixTypes.hpp"
   
   namespace MPS{
       class MatrixSoftMax: public NS::Referencing<MPS::MatrixUnaryKernel>{
           public:
           static MPS::MatrixSoftMax* alloc();
           NS::UInteger sourceRows();
           NS::UInteger sourceColumns();
           MPS::MatrixSoftMax* initWithDevice(MTL::Device* device);
           void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Matrix* resultMatrix);
           MPS::MatrixSoftMax* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
           // another zone function here
       };
       class MatrixLogSoftMax: NS::Referencing<MPS::MatrixSoftMax>{
           public:
           static MPS::MatrixLogSoftMax* alloc();
           NS::UInteger sourceRows();
           NS::UInteger sourceColumns();
           MPS::MatrixLogSoftMax* initWithDevice(MTL::Device* device);
           void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Matrix* resultMatrix);
           MPS::MatrixLogSoftMax* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
       };
       class MatrixSoftMaxGradient: NS::Referencing<MPS::MatrixBinaryKernel>{
           public:
           static MPS::MatrixSoftMaxGradient* alloc();
           NS::UInteger sourceRows();
           NS::UInteger sourceColumns();
           MPS::MatrixSoftMaxGradient* initWithDevice(MTL::Device* device);
           void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* gradientMatrix, MPS::Matrix* forwardOutputMatrix, MPS::Matrix* resultMatrix);
           MPS::MatrixSoftMaxGradient* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
           // another zone function here
       };
       class MatrixLogSoftMaxGradient: NS::Referencing<MPS::MatrixSoftMaxGradient>{
           public:
           static MPS::MatrixLogSoftMaxGradient* alloc();
           NS::UInteger sourceRows();
           NS::UInteger sourceColumns();
           MPS::MatrixLogSoftMaxGradient* initWithDevice(MTL::Device* device);
           void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* gradientMatrix, MPS::Matrix* forwardOutputMatrix, MPS::Matrix* resultMatrix);
           MPS::MatrixLogSoftMaxGradient* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
       };
   }
   _MPS_INLINE MPS::MatrixSoftMax* MPS::MatrixSoftMax::alloc(){
       return NS::Object::alloc<MPS::MatrixSoftMax>(_MPS_PRIVATE_CLS(MPSMatrixSoftMax));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixSoftMax::sourceRows(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(sourceRows));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixSoftMax::sourceColumns(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(sourceColumns));
   }
   _MPS_INLINE MPS::MatrixSoftMax* MPS::MatrixSoftMax::initWithDevice(MTL::Device* device){
       return Object::sendMessage<MPS::MatrixSoftMax*>(this, _MPS_PRIVATE_SEL(initWithDevice_), device);
   }
   _MPS_INLINE void MPS::MatrixSoftMax::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Matrix* resultMatrix){
       Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_inputMatrix_resultMatrix_),commandBuffer, inputMatrix, resultMatrix);
   }
   _MPS_INLINE MPS::MatrixSoftMax* MPS::MatrixSoftMax::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
       return Object::sendMessage<MPS::MatrixSoftMax*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_),aDecoder, device);
   }
   //Matrix Log SoftMax
   _MPS_INLINE MPS::MatrixLogSoftMax* MPS::MatrixLogSoftMax::alloc(){
       return NS::Object::alloc<MPS::MatrixLogSoftMax>(_MPS_PRIVATE_CLS(MPSMatrixLogSoftMax));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixLogSoftMax::sourceRows(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(sourceRows));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixLogSoftMax::sourceColumns(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(sourceColumns));
   }
   _MPS_INLINE MPS::MatrixLogSoftMax* MPS::MatrixLogSoftMax::initWithDevice(MTL::Device* device){
       return Object::sendMessage<MPS::MatrixLogSoftMax*>(this, _MPS_PRIVATE_SEL(initWithDevice_), device);
   }
   _MPS_INLINE void MPS::MatrixLogSoftMax::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Matrix* resultMatrix){
       Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_inputMatrix_resultMatrix_),commandBuffer, inputMatrix, resultMatrix);
   }
   _MPS_INLINE MPS::MatrixLogSoftMax* MPS::MatrixLogSoftMax::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
       return Object::sendMessage<MPS::MatrixLogSoftMax*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_), aDecoder, device);
   }
   
   //MPSMatrixSoftMaxGradient
   _MPS_INLINE MPS::MatrixSoftMaxGradient* MPS::MatrixSoftMaxGradient::alloc(){
       return NS::Object::alloc<MPS::MatrixSoftMaxGradient>(_MPS_PRIVATE_CLS(MPSMatrixSoftMaxGradient));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixSoftMaxGradient::sourceRows(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL( sourceRows));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixSoftMaxGradient::sourceColumns(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL( sourceColumns));
   }
   _MPS_INLINE MPS::MatrixSoftMaxGradient* MPS::MatrixSoftMaxGradient::initWithDevice(MTL::Device* device){
       return Object::sendMessage<MPS::MatrixSoftMaxGradient*>(this, _MPS_PRIVATE_SEL( initWithDevice_), device);
   }
   _MPS_INLINE void MPS::MatrixSoftMaxGradient::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* gradientMatrix, MPS::Matrix* forwardOutputMatrix, MPS::Matrix* resultMatrix){
       Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_gradientMatrix_forwardOutputMatrix_resultMatrix_),commandBuffer, gradientMatrix, forwardOutputMatrix, resultMatrix);
   }
   _MPS_INLINE MPS::MatrixSoftMaxGradient* MPS::MatrixSoftMaxGradient::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
       return Object::sendMessage<MPS::MatrixSoftMaxGradient*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_),aDecoder, device);
   }
   
   //MPSMatrixLogSoftMaxGradient
   _MPS_INLINE MPS::MatrixLogSoftMaxGradient* MPS::MatrixLogSoftMaxGradient::alloc(){
       return NS::Object::alloc<MPS::MatrixLogSoftMaxGradient>(_MPS_PRIVATE_CLS(MPSMatrixLogSoftMaxGradient));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixLogSoftMaxGradient::sourceRows(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL( sourceRows));
   }
   _MPS_INLINE NS::UInteger MPS::MatrixLogSoftMaxGradient::sourceColumns(){
       return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL( sourceColumns));
   }
   _MPS_INLINE MPS::MatrixLogSoftMaxGradient* MPS::MatrixLogSoftMaxGradient::initWithDevice(MTL::Device* device){
       return Object::sendMessage<MPS::MatrixLogSoftMaxGradient*>(this, _MPS_PRIVATE_SEL( initWithDevice_), device);
   }
   _MPS_INLINE void MPS::MatrixLogSoftMaxGradient::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* gradientMatrix, MPS::Matrix* forwardOutputMatrix, MPS::Matrix* resultMatrix){
       Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_gradientMatrix_forwardOutputMatrix_resultMatrix_),commandBuffer, gradientMatrix, forwardOutputMatrix, resultMatrix);
   }
   _MPS_INLINE MPS::MatrixLogSoftMaxGradient* MPS::MatrixLogSoftMaxGradient::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
       return Object::sendMessage<MPS::MatrixLogSoftMaxGradient*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_),aDecoder, device);
   }
   
   
   
   
   
   
