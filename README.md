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

Here's the documentation. It's just enough to get you started. I'll add more to the documentation including what works and what doesn't but until then:

## Creating Matrices
To create a matrix, you need `MPS::MatrixDescriptor` objects. You must create a descriptor for a matrix, which is later used to actually create the matrix. For e.g.To create a descriptor for a 5x4 matrix with with float32 datatype:

```cpp
MPS::MatrixDescriptor* mps_matdes = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 4, 4*4, MPS::MPSDataTypeFloat32);
```
The first argument is the number of rows, followed by the number of columns, followed by the number of bytes in a row i.e. `numCols*dataTypeSize`, followed by the actual data type.

The actual matrix creation then works as follows (the `alloc` syntax does look like an eyesore. This is why the final goal is to create a wrapper around these operations):
```cpp
MTL::Device* device = MTL::CreateSystemDefaultDevice();
MPS::MatrixDescriptor* mps_matdes = MPS::MatrixDescriptor::matrixDescriptorWithRows(5, 4, 4*4, MPS::MPSDataTypeFloat32);
MPS::Matrix* matrix = MPS::Matrix::alloc(); matrix->initWithDevice(device, mps_matdes);
```

To actually put the data inside the matrix, one method would be to use `matrix->data()` which just returns a pointer to the `MTL::Buffer` containing the data (row major order). Then, just loop through it and add your data.

We can also initialize the matrix with an array. To initialize it with an array that contains your data, you need to initialize a buffer with that array and then initialize the matrix with that buffer (easy, huh? array->buffer->matrix) . Still, the cleanest way to write this would be:

```cpp
float data[] = {yourdatahere};
MTL::Buffer* buf = device->newBuffer(data,bufferSizeInBytes,MTL::ResourceStorageModeShared);
MPS::MatrixDescriptor* matdes = MPS::MatrixDescriptor::matrixDescriptorWithRows(...);
MPS::Matrix* mat = MPS::Matrix::alloc();mat->initWithBuffer(buf,matdes);
```

If you already have a `float` array, it makes more sense to do this than to copy the data into the buffer.

When in doubt, just open the header file corresponding to the operation you want to perform or the data structure you want to know more about.


## Matrix Multiplication
Now, here's a complete example that declares and then multiplies two 3x3 matrices:

```cpp
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
void printMTLBuffer(MTL::Buffer *buf, std::string name){
    std::cout<<name<<":"<<"<";
    float *ptr = (float*)buf->contents();
    for(int i=0;i<buf->length()/sizeof(float) - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[buf->length()/sizeof(float) - 1]<<">";
    std::cout<<std::endl;
}

int main(){
    // add the data to an array
    float mat1_data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    float mat2_data[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    //declare the device, command buffer, command queue
    MTL::Device* device = MTL::CreateSystemDefaultDevice();
    MTL::CommandQueue* cmdQueue = device->newCommandQueue();
    MTL::CommandBuffer* cmdbuf = cmdQueue->commandBuffer();

    //create buffers from the above data
    MTL::Buffer* b1 = device->newBuffer(mat1_data, 36, MTL::ResourceStorageModeShared);
    MTL::Buffer* b2 = device->newBuffer(mat2_data, 36, MTL::ResourceStorageModeShared);

    //create matrix descriptors
    MPS::MatrixDescriptor* m1_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(3,3,12,MPS::MPSDataTypeFloat32);
    MPS::MatrixDescriptor* m2_des = MPS::MatrixDescriptor::matrixDescriptorWithRows(3,3,12,MPS::MPSDataTypeFloat32);

    //create matrices from their matrix descriptors
    MPS::Matrix* m1 = MPS::Matrix::alloc(); m1->initWithBuffer(b1, m1_des);
    MPS::Matrix* m2 = MPS::Matrix::alloc(); m2->initWithBuffer(b2, m2_des);
    MPS::Matrix* m_res = MPS::Matrix::alloc(); m_res->initWithDevice(device, MPS::MatrixDescriptor::matrixDescriptorWithRows(3,3,12,MPS::MPSDataTypeFloat32));

    //allocate a matrix multiplication object
    MPS::MatrixMultiplication* mps_matmul = MPS::MatrixMultiplication::alloc();
    mps_matmul->initWithDevice(device, 3, 3, 3);

    //encode the matmul op. to the command buffer
    mps_matmul->encodeToCommandBuffer(cmdbuf, m1, m2, m_res);

    //commit command buffer
    cmdbuf->commit();
    cmdbuf->waitUntilCompleted();
    
    // print the data
    printMTLBuffer(b1, "m1");
    printMTLBuffer(b2, "m2");
    printMTLBuffer(m_res->data(), "res");
    return 0;
}

```






