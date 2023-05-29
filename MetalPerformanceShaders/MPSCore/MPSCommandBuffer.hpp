#pragma once

#include "../../Foundation/NSObject.hpp"
#include "../MPSPrivate.hpp"
#include "../MPSDefines.hpp"
#include "../MPSHeaderBridge.hpp"


#include "MPSCoreTypes.hpp"


namespace MPS
{
    class Predicate : public NS::Referencing<Predicate>{
        public:
        MTL::Buffer* predicateBuffer() const;
        NS::UInteger predicateOffset() const;
        static Predicate* predicateWithBuffer(MTL::Buffer* buffer, NS::UInteger offset);
        Predicate* initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset);

    };
}