#include <iostream>
#include <fstream>


#include <Accelerate/Accelerate.h>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "metal-cpp/Foundation/Foundation.hpp"
#include "metal-cpp/Metal/Metal.hpp"
#include "metal-cpp/QuartzCore/QuartzCore.hpp"

#include "metal-cpp/MetalPerformanceShaders/MPSMatrix/MPSMatrixRandom.hpp"
#include "metal-cpp/MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "basic_utils.hpp"

TEST_CASE("Creating a MatrixRandomDistributionDescriptor object"){
    SUBCASE("Using uniformDistributionDescriptorWithMinimum"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::uniformDistributionDescriptorWithMinimum(3.0, 6.0);
        CHECK(areEqual(desc->minimum(), 3.0));
        CHECK(areEqual(desc->maximum(), 6.0));
    }
    SUBCASE("Using normalDistributionDescriptorWithMean"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(3.0, 0.5);
        CHECK(areEqual(desc->mean(), 3.0));
        CHECK(areEqual(desc->standardDeviation(), 0.5));
    }
    SUBCASE("Using normalDistributionDescriptorWithMean with min and max"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::normalDistributionDescriptorWithMean(3.0, 0.5, 1.0, 6.0);
        CHECK(areEqual(desc->mean(), 3.0));
        CHECK(areEqual(desc->standardDeviation(), 0.5));
        CHECK(areEqual(desc->minimum(), 1.0));
        CHECK(areEqual(desc->maximum(), 6.0));
    }
    SUBCASE("Using the default descriptor"){
        MPS::MatrixRandomDistributionDescriptor* desc = MPS::MatrixRandomDistributionDescriptor::defaultDistributionDescriptor();
        CHECK(desc!=nullptr);
    }
}
TEST_CASE("Creating a random MTGP32 matrix"){
    SUBCASE("Creation with a uniform distribution descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a normal distribution descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a normal distribution descriptor with min and max"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a default descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
}
TEST_CASE("Creating a random Philox matrix"){
    SUBCASE("Creation with a uniform distribution descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a normal distribution descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a normal distribution descriptor with min and max"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
    SUBCASE("Creation with a default descriptor"){
        SUBCASE("initWithDevice"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed, distributionDescriptor"){

        }
        SUBCASE("initWithDevice with destinationDataType, seed"){

        }
    }
}
