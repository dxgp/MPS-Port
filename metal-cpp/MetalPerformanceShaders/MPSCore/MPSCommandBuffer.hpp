#pragma once

#include "../../Foundation/NSObject.hpp"
#include "../MPSPrivate.hpp"
#include "../MPSDefines.hpp"
#include "../MPSHeaderBridge.hpp"


#include "MPSCoreTypes.hpp"


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
        void retireHeap(MTL::Heap heap, double seconds);
    };
}