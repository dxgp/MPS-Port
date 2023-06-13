#include <iostream>
#include <fstream>


#include <Accelerate/Accelerate.h>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MPS_PRIVATE_IMPLEMENTATION

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "QuartzCore/QuartzCore.hpp"



#include "MetalPerformanceShaders/MPSCore/MPSCoreTypes.hpp"
#include "MetalPerformanceShaders/MPSMatrix/MPSMatrix.hpp"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../basic_utils.hpp"
