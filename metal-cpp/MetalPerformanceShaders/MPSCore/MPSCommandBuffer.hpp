#pragma once

#include "../../Foundation/NSObject.hpp"
#include "../MPSPrivate.hpp"
#include "../MPSDefines.hpp"
#include "../MPSHeaderBridge.hpp"
#include "MPSCoreTypes.hpp"
#include "../../Metal/MTLBuffer.hpp"

namespace MPS
{
    class Predicate : public NS::Referencing<MPS::Predicate>{
        public:
        MTL::Buffer* predicateBuffer() const;
        NS::UInteger predicateOffset() const;
        static MPS::Predicate* predicateWithBuffer(MTL::Buffer* buffer, NS::UInteger offset);
        MPS::Predicate* initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset);
        MPS::Predicate* initWithDevice(MTL::Device* device);
    };
    class HeapProvider: public NS::Referencing<MPS::HeapProvider>{
        public:
        MTL::Heap* newHeapWithDescriptor(MTL::HeapDescriptor* descriptor);
        void retireHeap(MTL::Heap* heap, double seconds);
    };
    class CommandBuffer: public NS::Referencing<MTL::CommandBuffer>{
        MTL::CommandBuffer* commandBuffer() const;
        MTL::CommandBuffer* rootCommandBuffer() const;
        MPS::Predicate* predicate();
        MPS::HeapProvider* heapProvider();
        static MPS::CommandBuffer* commandBufferWithCommandBuffer(MTL::CommandBuffer* commandBuffer);
        static MPS::CommandBuffer* commandBufferFromCommandQueue(MTL::CommandQueue* commandQueue);
        MPS::CommandBuffer* initWithCommandBuffer(MTL::CommandBuffer* commandBuffer);
        void commitAndContinue();
        void prefetchHeapForWorkloadSize(size_t size);
    }
}

_MPS_INLINE MTL::Buffer* MPS::Predicate::predicateBuffer() const{
    return Object::sendMessage<MTL::Buffer*>(this, _MPS_PRIVATE_SEL(predicateBuffer));
}
_MPS_INLINE NS::UInteger MPS::Predicate::predicateOffset() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(predicateOffset));
}
_MPS_INLINE MPS::Predicate* MPS::Predicate::predicateWithBuffer(MTL::Buffer* buffer, NS::UInteger offset){
    return Object::sendMessage<MPS::Predicate*>(_MPS_PRIVATE_CLS(MPSPredicate), _MPS_PRIVATE_SEL(predicateWithBuffer_), buffer, offset);
}
_MPS_INLINE MPS::Predicate* MPS::Predicate::initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset){
    return Object::sendMessage<MPS::Predicate*>(this, _MPS_PRIVATE_SEL(initWithBuffer_), buffer, offset);
}
_MPS_INLINE MPS::Predicate* MPS::Predicate::initWithDevice(MTL::Device* device){
    return Object::sendMessage<MPS::Predicate*>(this, _MPS_PRIVATE_SEL(initWithDevice_), device);
}

//class HeapProvider
_MPS_INLINE MTL::Heap* MPS::HeapProvider::newHeapWithDescriptor(MTL::HeapDescriptor* descriptor){
    return Object::sendMessage<MTL::Heap*>(this, _MPS_PRIVATE_SEL(newHeapWithDescriptor_), descriptor);
}
_MPS_INLINE void MPS::HeapProvider::retireHeap(MTL::Heap* heap, double seconds){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(retireHeap_), heap, seconds);
}
_MPS_INLINE MTL::CommandBuffer* MPS::CommandBuffer::commandBuffer() const{
    return Object::sendMessage<MTL::CommandBuffer*>(this, _MPS_PRIVATE_SEL(commandBuffer));
}
_MPS_INLINE MTL::CommandBuffer* MPS::CommandBuffer::rootCommandBuffer() const{
    return Object::sendMessage<MTL::CommandBuffer*>(this, _MPS_PRIVATE_SEL(rootCommandBuffer));
}
_MPS_INLINE MPS::Predicate* MPS::CommandBuffer::predicate() {
    return Object::sendMessage<MPS::Predicate*>(this, _MPS_PRIVATE_SEL(predicate));
}
_MPS_INLINE MPS::HeapProvider* MPS::CommandBuffer::heapProvider(){
    return Object::sendMessage<MPS::HeapProvider*>(this, _MPS_PRIVATE_SEL(heapProvider));
}
_MPS_INLINE MPS::CommandBuffer* MPS::CommandBuffer::commandBufferWithCommandBuffer(MTL::CommandBuffer* commandBuffer){
    return Object::sendMessage<MPS::CommandBuffer*>(_MPS_PRIVATE_CLS(MPSCommandBuffer), _MPS_PRIVATE_SEL(commandBufferWithCommandBuffer_), commandBuffer);
}
_MPS_INLINE MPS::CommandBuffer* MPS::CommandBuffer::commandBufferFromCommandQueue(MTL::CommandQueue* commandQueue){
    return Object::sendMessage<MPS::CommandBuffer*>(_MPS_PRIVATE_CLS(MPSCommandBuffer), _MPS_PRIVATE_SEL(commandBufferFromCommandQueue_), commandQueue);
}
_MPS_INLINE MPS::CommandBuffer* MPS::CommandBuffer::initWithCommandBuffer(MTL::CommandBuffer* commandBuffer){
    return Object::sendMessage<MPS::CommandBuffer*>(this, _MPS_PRIVATE_SEL(initWithCommandBuffer_), commandBuffer);
}
_MPS_INLINE void MPS::CommandBuffer::commitAndContinue(){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(commitAndContinue));
}
_MPS_INLINE void MPS::CommandBuffer::prefetchHeapForWorkloadSize(size_t size){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(prefetchHeapForWorkloadSize_), size);
}






