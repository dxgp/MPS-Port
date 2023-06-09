echo "Compiling test"
clang++ -std=c++17 -stdlib=libc++ -O2 -I./metal-cpp -I /opt -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -framework MetalPerformanceShaders -g MPSMatrixDecomposition_test.cpp -o MPSMatrixDecomposition_test.x
clang++ -std=c++17 -stdlib=libc++ -O2 -I./metal-cpp -I /opt -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -framework MetalPerformanceShaders -g MPSMatrixFindTopK_test.cpp -o MPSMatrixFindTopK_test.x
clang++ -std=c++17 -stdlib=libc++ -O2 -I./metal-cpp -I /opt -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -framework MetalPerformanceShaders -g MPSMatrixMultiplication_test.cpp -o MPSMatrixMultiplication_test.x
clang++ -std=c++17 -stdlib=libc++ -O2 -I./metal-cpp -I /opt -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -framework MetalPerformanceShaders -g MPSMatrixRandom_test.cpp -o MPSMatrixRandom_test.x
clang++ -std=c++17 -stdlib=libc++ -O2 -I./metal-cpp -I /opt -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -framework MetalPerformanceShaders -g MPSMatrixSoftMax_test.cpp -o MPSMatrixSoftMax_test.x
echo "Compilation complete, running tests"
echo "************************ MPSMatrixDecomposition_test ************************"
./MPSMatrixDecomposition_test.x -ni
echo "************************ MPSMatrixFindTopK_test ************************"
./MPSMatrixFindTopK_test.x -ni
echo "************************ MPSMatrixMultiplication_test ************************"
./MPSMatrixMultiplication_test.x -ni
echo "************************ MPSMatrixRandom_test ************************"
./MPSMatrixRandom_test.x -ni
echo "************************ MPSMatrixSoftMax_test ************************"
./MPSMatrixSoftMax_test.x -ni
echo "Tests complete"
echo "Cleaning up..."
rm *.x
rm -r *.x.dSYM