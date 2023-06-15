#pragma once
#include "MPSCoreTypes.hpp"
#include "MPSCommandBuffer.hpp"

namespace MPS{
    class Kernel: public NS::Copying<Kernel>{
        static MPS::Kernel* alloc();
        MPS::Kernel* init();
        MPS::KernelOptions options();
        MTL::Device* device() const;
        NS::String* label();
        MPS::Kernel* initWithDevice(MTL::Device* device);
        //MPS::Kernel copyWithZone(NS::Zone ) Skipping all zone related functions. If it doesn't work out, then I'll look into it
        MPS::Kernel* initWithCoder(NS::Coder* aDecoder);
        MPS::Kernel* initWithCoder(NS::Coder* aDecoder, MTL::Device* device);
    };
}
/// @{ @private
_MPS_INLINE MPS::Kernel* MPS::Kernel::alloc(){
    return NS::Object::alloc<MPS::Kernel>(_MPS_PRIVATE_CLS(MPSKernel));
}
_MPS_INLINE MPS::Kernel* MPS::Kernel::init(){
    return NS::Object::init<MPS::Kernel>();
}
_MPS_INLINE MPS::KernelOptions MPS::Kernel::options(){
    return Object::sendMessage<MPS::KernelOptions>(this, _MPS_PRIVATE_SEL(options));
}
_MPS_INLINE MTL::Device* MPS::Kernel::device() const{
    return Object::sendMessage<MTL::Device*>(this, _MPS_PRIVATE_SEL(device));
}
_MPS_INLINE NS::String* MPS::Kernel::label(){
    return Object::sendMessage<NS::String*>(this, _MPS_PRIVATE_SEL(label));
}
_MPS_INLINE MPS::Kernel* MPS::Kernel::initWithDevice(MTL::Device* device){
    return Object::sendMessage<MPS::Kernel*>(this, _MPS_PRIVATE_SEL(initWithDevice_), device);
}
_MPS_INLINE MPS::Kernel* MPS::Kernel::initWithCoder(NS::Coder* aDecoder){
    return Object::sendMessage<MPS::Kernel*>(this, _MPS_PRIVATE_SEL(initWithCoder_), aDecoder);
}
_MPS_INLINE MPS::Kernel* MPS::Kernel::initWithCoder(NS::Coder* aDecoder, MTL::Device* device){
    return Object::sendMessage<MPS::Kernel*>(this, _MPS_PRIVATE_SEL(initWithCoder_device_), aDecoder, device);
}
/// @}