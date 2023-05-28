#pragma once

#include "../../Foundation/NSObject.hpp"
#include "../../Metal/Metal.hpp"
#include "../MPSPrivate.hpp"


namespace MPS{
    _NS_ENUM(NS::UInteger, MPSKernelOptions){
        MPSKernelOptionsNone = 0U,
        MPSKernelOptionsSkipAPIValidation = 1U << 0,
        MPSKernelOptionsAllowReducedPrecision = 1U << 1,
        MPSKernelOptionsVerbose = 1U << 4,
        MPSKernelOptionsDisableInternalTiling = 1U << 2,
        MPSKernelOptionsInsertDebugGroups = 1U << 3
    };
    _NS_ENUM(NS::UInteger, MPSImageEdgeMode){
        MPSImageEdgeModeZero = 0,
        MPSImageEdgeModeClamp = 1,
        MPSImageEdgeModeMirror,
        MPSImageEdgeModeMirrorWithEdge,
        MPSImageEdgeModeConstant
    };
    _NS_ENUM(NS::UInteger, MPSImageFeatureChannelFormat){
        MPSImageFeatureChannelFormatNone = 0,
        MPSImageFeatureChannelFormatUnorm8 = 1,
        MPSImageFeatureChannelFormatUnorm16 = 2,
        MPSImageFeatureChannelFormatFloat16 = 3,
        MPSImageFeatureChannelFormatFloat32 = 4,
        MPSImageFeatureChannelFormat_reserved0 = 5,
        MPSImageFeatureChannelFormatCount
    };
    _NS_ENUM(NS::UInteger, MPSDataType){
        MPSDataTypeFloatBit = 0x10000000,
        MPSDataTypeFloat16 = 1 << MPSDataTypeFloatBit|16,
        MPSDataTypeFloat32 = 2 << MPSDataTypeFloatBit|32,
        MPSDataTypeSignedBit = 0x20000000,
        MPSDataTypeInt8 = MPSDataTypeSignedBit | 8,
        MPSDataTypeInt16 = MPSDataTypeSignedBit | 16,
        MPSDataTypeInt32 = MPSDataTypeSignedBit | 32,
        MPSDataTypeInt64 = MPSDataTypeSignedBit | 64,
        
        MPSDataTypeUInt8 = 8,
        MPSDataTypeUInt16 = 16,
        MPSDataTypeUInt32 = 32,
        MPSDataTypeUInt64 = 64,
        MPSDataTypeNormalizedBit = 0x40000000,
        MPSDataTypeUnorm1 = MPSDataTypeNormalizedBit | 1,
        MPSDataTypeUnorm8 = MPSDataTypeNormalizedBit | 8
    };
}