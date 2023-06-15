#pragma once

#include "../../Foundation/NSObject.hpp"
#include "../../Metal/Metal.hpp"
#include "../MPSPrivate.hpp"


namespace MPS{
    _NS_OPTIONS(NS::UInteger, MatrixRandomDistribution){
        MatrixRandomDistributionDefault = 1U,
        MatrixRandomDistributionUniform = 2U,
        MatrixRandomDistributionNormal = 3U
    };
    // _NS_ENUM(int, MatrixDecompositionStatus){
    enum MatrixDecompositionStatus: int{
        MatrixDecompositionStatusSuccess = 0,
        MatrixDecompositionStatusFailure = -1,
        MatrixDecompositionStatusSingular = -2,
        MatrixDecompositionStatusNonPositiveDefinite = -3,
    };
    _NS_OPTIONS(NS::UInteger, KernelOptions){
        MPSKernelOptionsNone = 0U,
        MPSKernelOptionsSkipAPIValidation = 1U << 0,
        MPSKernelOptionsAllowReducedPrecision = 1U << 1,
        MPSKernelOptionsInsertDebugGroups = 1U << 3,
        MPSKernelOptionsVerbose = 1U << 4,
    };
    // _NS_ENUM(NS::UInteger, ImageEditMode){
    enum ImageEditMode: NS::UInteger{
        MPSImageEdgeModeZero = 0,
        MPSImageEdgeModeClamp = 1,
        MPSImageEdgeModeMirror,
        MPSImageEdgeModeMirrorWithEdge,
        MPSImageEdgeModeConstant,
    };
    // _NS_ENUM(NS::UInteger, ImageFeatureChannelFormat){
    enum ImageFeatureChannelFormat: NS::UInteger{
        MPSImageFeatureChannelFormatNone = 0,
        MPSImageFeatureChannelFormatUnorm8 = 1,
        MPSImageFeatureChannelFormatUnorm16 = 2,
        MPSImageFeatureChannelFormatFloat16 = 3,
        MPSImageFeatureChannelFormatFloat32  = 4,
        MPSImageFeatureChannelFormat_reserved0 = 5,
        MPSImageFeatureChannelFormatCount,
    };
    // _NS_ENUM(uint32_t, DataType){
    enum DataType: uint32_t {
        MPSDataTypeInvalid = 0,
        MPSDataTypeFloatBit = 0x10000000,
        MPSDataTypeFloat32   = MPSDataTypeFloatBit | 32,
        MPSDataTypeFloat16   = MPSDataTypeFloatBit | 16,
        MPSDataTypeSignedBit  = 0x20000000,
        MPSDataTypeInt8     = MPSDataTypeSignedBit | 8,
        MPSDataTypeInt16   = MPSDataTypeSignedBit | 16,
        MPSDataTypeInt32   = MPSDataTypeSignedBit | 32,
        MPSDataTypeInt64  = MPSDataTypeSignedBit | 64,
        MPSDataTypeUInt8    = 8,
        MPSDataTypeUInt16   = 16,
        MPSDataTypeUInt32   = 32,
        MPSDataTypeUInt64   = 64,
        MPSDataTypeNormalizedBit = 0x40000000,
        MPSDataTypeUnorm1 = MPSDataTypeNormalizedBit | 1,
        MPSDataTypeUnorm8 = MPSDataTypeNormalizedBit | 8,
    };
    _NS_OPTIONS(NS::UInteger, AliasingStrategy){
        MPSAliasingStrategyDefault = 0,
        MPSAliasingStrategyDontCare = MPSAliasingStrategyDefault,
        MPSAliasingStrategyShallAlias = 1UL << 0,
        MPSAliasingStrategyShallNotAlias  = 1UL << 1,
        MPSAliasingStrategyAliasingReserved = MPSAliasingStrategyShallAlias | MPSAliasingStrategyShallNotAlias,
        MPSAliasingStrategyPreferTemporaryMemory = 1UL << 2,                             
        MPSAliasingStrategyPreferNonTemporaryMemory = 1UL << 3,     
    };
    typedef struct{
            NS::Integer x;    
            NS::Integer y;    
            NS::Integer z;    
    }MPSOffset;
    typedef struct Origin{
        double  x;  
        double  y;  
        double  z;  
    }MPSOrigin;
    typedef struct Size {
        double  width;      
        double  height;     
        double  depth;      
    }MPSSize;
    typedef struct DimensionSlice {
        NS::UInteger        start;       
        NS::UInteger        length;     
    }MPSDimensionSlice;

    typedef struct Region {
        MPSOrigin       origin;    
        MPSSize         size;      
    }MPSRegion;
    typedef struct ScaleTransform {
        double  scaleX;                        
        double  scaleY;                        
        double  translateX;                    
        double  translateY;                   
    }MPSScaleTransform;

    typedef struct ImageCoordinate {
        NS::UInteger x;           
        NS::UInteger y;           
        NS::UInteger channel;     
    }MPSImageCoordinate;

    typedef struct ImageRegion {
        MPSImageCoordinate offset;      
        MPSImageCoordinate size;       
    }MPSImageRegion;

    // const MTL::Region RectNoClip;

    class DeviceProvider{
        public:
            MTL::Device* mpsMTLDevice;
    };

    // For future reference, the original definition was typedef NSArray<NSNumber*> MPSShape; i.e. MPSShape is an array of NS::Numbers.
    typedef NS::Array* Shape; // wtf
    
    // **************************************************************************************************************** MPS DEVICE PROVIDER ADD HEREE ****************************************************************************************************************

}