#pragma once
#include "../MPSCore/MPSKernel.hpp"
#include "MPSMatrixTypes.hpp"

namespace MPS{
    //only compatible with float32 and float16
    class MatrixFindTopK: public NS::Referencing<MPS::MatrixUnaryKernel>{
        public:
        static MPS::MatrixFindTopK* alloc();
        NS::UInteger sourceRows();
        NS::UInteger sourceColumns();
        NS::UInteger indexOffset();
        NS::UInteger numberOfTopKValues();
        MPS::MatrixFindTopK* initWithDevice(MTL::Device* device, NS::UInteger numberOfTopKValues);
        void encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Matrix* resultIndexMatrix, MPS::Matrix* resultValueMatrix);
        // MPS::MatrixFindTopK* initWithCoder(NS::Coder* aDecoder, MTL::Device* device); this is for using byte streams as input data
        // one more zone function, skipped
    };
}
/// @{ @private
_MPS_INLINE MPS::MatrixFindTopK* MPS::MatrixFindTopK::alloc(){
    return NS::Object::alloc<MPS::MatrixFindTopK>(_MPS_PRIVATE_CLS(MPSMatrixFindTopK));
}
_MPS_INLINE NS::UInteger MPS::MatrixFindTopK::sourceRows(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(sourceRows));
}
_MPS_INLINE NS::UInteger MPS::MatrixFindTopK::sourceColumns(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(sourceColumns));
}
_MPS_INLINE NS::UInteger MPS::MatrixFindTopK::indexOffset(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(indexOffset));
}
_MPS_INLINE NS::UInteger MPS::MatrixFindTopK::numberOfTopKValues(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(numberOfTopKValues));
}
_MPS_INLINE MPS::MatrixFindTopK* MPS::MatrixFindTopK::initWithDevice(MTL::Device* device, NS::UInteger numberOfTopKValues){
    return Object::sendMessage<MPS::MatrixFindTopK*>(this, _MPS_PRIVATE_SEL(initWithDevice_numberOfTopKValues_), device, numberOfTopKValues);
}
_MPS_INLINE void MPS::MatrixFindTopK::encodeToCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::Matrix* inputMatrix, MPS::Matrix* resultIndexMatrix, MPS::Matrix* resultValueMatrix){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(encodeToCommandBuffer_inputMatrix_resultIndexMatrix_resultValueMatrix_), commandBuffer, inputMatrix, resultIndexMatrix, resultValueMatrix);
}
// _MPS_INLINE MPS::MatrixFindTopK* MPS::MatrixFindTopK::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
//     return Object::sendMessage<MPS::MatrixFindTopK*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_), aDecoder, device);
// }
/// @}