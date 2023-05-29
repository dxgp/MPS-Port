#pragma once

#include "../../Foundation/NSObject.hpp"
#include "../../Metal/Metal.hpp"
#include "../MPSPrivate.hpp"


namespace MPS{
    _NS_OPTIONS(NS::UInteger, KernelOptions){
        MPSKernelOptionsNone = 0U,
        MPSKernelOptionsSkipAPIValidation = 1U << 0,
        MPSKernelOptionsAllowReducedPrecision = 1U << 1,
        MPSKernelOptionsInsertDebugGroups = 1U << 3,
        MPSKernelOptionsVerbose = 1U << 4,
    };
    _NS_ENUM(NS::UInteger, ImageEditMode){
        MPSImageEdgeModeZero = 0,
        MPSImageEdgeModeClamp = 1,
        MPSImageEdgeModeMirror,
        MPSImageEdgeModeMirrorWithEdge,
        MPSImageEdgeModeConstant,
    };
    _NS_ENUM(NS::UInteger, ImageFeatureChannelFormat){
            MPSImageFeatureChannelFormatNone = 0,
            MPSImageFeatureChannelFormatUnorm8 = 1,
            MPSImageFeatureChannelFormatUnorm16 = 2,
            MPSImageFeatureChannelFormatFloat16 = 3,
            MPSImageFeatureChannelFormatFloat32  = 4,
            MPSImageFeatureChannelFormat_reserved0 = 5,
            MPSImageFeatureChannelFormatCount,
    };
    _NS_ENUM(uint32_t, DataType){
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
            NS::Integer x;    /**<    The horizontal component of the offset. Units: pixels   */
            NS::Integer y;    /**<    The vertical component of the offset. Units: pixels     */
            NS::Integer z;    /**<    The depth component of the offset. Units: pixels        */
    }MPSOffset;
    typedef struct Origin{
        double  x;  /**< The x coordinate of the position       */
        double  y;  /**< The y coordinate of the position       */
        double  z;  /**< The z coordinate of the position       */
    }MPSOrigin;
    typedef struct Size {
        double  width;      /**< The width of the region    */
        double  height;     /**< The height of the region   */
        double  depth;      /**< The depth of the region    */
    }MPSSize;
    typedef struct DimensionSlice {
        NS::UInteger        start;        /**< the position of the first element in the slice */
        NS::UInteger        length;        /**< the number of elements in the slice. */
    }MPSDimensionSlice;

    typedef struct Region {
        MPSOrigin       origin;     /**< The top left corner of the region.  Units: pixels  */
        MPSSize         size;       /**< The size of the region. Units: pixels              */
    }MPSRegion;
    typedef struct ScaleTransform {
        double  scaleX;                         /**< horizontal scaling factor */
        double  scaleY;                         /**< vertical scaling factor */
        double  translateX;                     /**< horizontal translation */
        double  translateY;                     /**< vertical translation */
    }MPSScaleTransform;

    typedef struct ImageCoordinate {
        NS::UInteger x;           /**<    The horizontal component of the coordinate. Units: pixels      */
        NS::UInteger y;           /**<    The vertical component of the coordinate. Units: pixels        */
        NS::UInteger channel;     /**<    The index of the channel or feature channel within the pixel   */
    }MPSImageCoordinate;

    typedef struct ImageRegion {
        MPSImageCoordinate offset;      /**<    The position of the top left corner of the subregion */
        MPSImageCoordinate size;        /**<    The size {pixels, pixels, channels} of the subregion */
    }MPSImageRegion;

    const MTL::Region RectNoClip;

    // @protocol   MPSDeviceProvider
    //     /*! @abstract   Return the device to use when making MPSKernel subclasses from the NSCoder */
    //     -(id <MTLDevice>) mpsMTLDevice;
    // @end
    class DeviceProvider{
        public:
            MTL::Device* mpsMTLDevice;
    };

    // For future reference, the original definition was typedef NSArray<NSNumber*> MPSShape; i.e. MPSShape is an array of NS::Numbers.
    typedef NS::Array* Shape; // wtf
    
    // **************************************************************************************************************** MPS DEVICE PROVIDER ADD HEREE ****************************************************************************************************************

}