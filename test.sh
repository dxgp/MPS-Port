clang++ -std=c++17 -stdlib=libc++ -O2 -I./metal-cpp -fno-objc-arc -framework Metal -framework Foundation -framework MetalKit -framework Accelerate -g main.cpp -o test.x
./test.x
echo "Compilation successful"
sudo rm test.x
sudo rm -r test.x.dSYM
