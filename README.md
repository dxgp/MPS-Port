# MPS-Port
I created this project so that I could use Metal Performance Shaders with metal-cpp. Currently, it supports all "MPSMatrix" operations like decomposition, find top k elements, matrix multiplication, random matrix generation, softmax, matrix solve.

The extension was written in the same style as metal-cpp. Just read the docs below to understand how to perform these operations because the syntax can be a little weird at times.

All functions and class definitions are under the `MPS` namespace. So, if an objC call were `MPSMatrixMultiplication`, it would be written in C++ as `MPS::MatrixMultiplication`.


## Headers
Just include the `MPSMatrix.hpp` file in `metal-cpp/MetalPerformanceShaders/MPSMatrix` folder. As an example, here's how the headers look like for me:

```cpp
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

```
The command I use to compile is:
```zsh
clang++ -std=c++17 -stdlib=libc++ -O2 -I../metal-cpp -I /opt -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -framework MetalPerformanceShaders -g {put your file name here}  -o test.x
```

Make sure you update the `-I` argument to where your metal-cpp folder is located.

## Creating Matrices
### Descriptors
Central to creating matrices is `MPS::MatrixDescriptor` objects. You must create a descriptor for a matrix, which is later used to actually create the matrix. To create a descriptor for a 5x4 matrix with with float32 datatype:

<!--         static MPS::MatrixDescriptor* matrixDescriptorWithRows(NS::UInteger rows, NS::UInteger columns, NS::UInteger rowBytes, MPS::DataType dataType);
        static MPS::MatrixDescriptor* matrixDescriptorWithRows(NS::UInteger rows, NS::UInteger columns, NS::UInteger matrices, NS::UInteger rowBytes, NS::UInteger matrixBytes, MPS::DataType dataType); -->
```cpp
MPS::MatrixDescriptor* mps_matdes = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 4, 4*4, MPS::MPSDataTypeFloat32);
```
