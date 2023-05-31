#pragma once

#include "../MPSCore/MPSKernel.hpp"
#include "../MPSCore/MPSCoreTypes.hpp"
#include "../MPSCore/MPSKernelTypes.hpp"
#include "../MPSCore/MPSMatrix.hpp"
#include "../../Metal/Metal.hpp"

namespace MPS{
    class MatrixUnaryKernel: public NS::Referencing<MPS::Kernel>{
        MTL::Origin sourceMatrixOrigin();
        MTL::Origin resultMatrixOrigin();
        NS::UInteger batchStart();
        NS::UInteger batchSize();
    };
    class MatrixBinaryKernel: public NS::Referencing<MPS::Kernel>{
        MTL::Origin primarySourceMatrixOrigin();
        MTL::Origin secondarySourceMatrixOrigin();
        MTL::Origin resultMatrixOrigin();
        NS::UInteger batchStart();
        NS::UInteger batchSize();
    };
}
_MPS_INLINE MTL::Origin MPS::MatrixUnaryKernel::sourceMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(sourceMatrixOrigin));
}
_MPS_INLINE MTL::Origin MPS::MatrixUnaryKernel::resultMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(resultMatrixOrigin));
}
_MPS_INLINE NS::UInteger MPS::MatrixUnaryKernel::batchStart(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchStart));
}
_MPS_INLINE NS::UInteger MPS::MatrixUnaryKernel::batchSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchSize));
}
_MPS_INLINE MTL::Origin MPS::MatrixBinaryKernel::primarySourceMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(primarySourceMatrixOrigin));
}
_MPS_INLINE MTL::Origin MPS::MatrixBinaryKernel::secondarySourceMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(secondarySourceMatrixOrigin));
}
_MPS_INLINE MTL::Origin MPS::MatrixBinaryKernel::resultMatrixOrigin(){
    return Object::sendMessage<MTL::Origin>(this, _MPS_PRIVATE_SEL(resultMatrixOrigin));
}
_MPS_INLINE NS::UInteger MPS::MatrixBinaryKernel::batchStart(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchStart));
}
_MPS_INLINE NS::UInteger MPS::MatrixBinaryKernel::batchSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(batchSize));
}
