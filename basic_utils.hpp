#include <cmath>
bool areEqual(float a, float b) {
    return (fabs(a - b) <= 1e-6f * std::max(1.0f, std::max(a, b)));
}
void generateRandomFloatData(MTL::Buffer *buffer){
    rand();
    rand();
    rand();
    rand();
    float *dataptr = (float *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/sizeof(float);index++){
        dataptr[index] = ((float)rand() / float(RAND_MAX));
    }
}
void generateRandomFloat16Data(MTL::Buffer *buffer){
    rand();
    rand();
    rand();
    rand();
    float16_t *dataptr = (float16_t *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/sizeof(float16_t);index++){
        dataptr[index] = ((float16_t)rand() / float16_t(RAND_MAX));
    }
}

void printMTLBufferInt32(MTL::Buffer* buf, std::string name){
    std::cout<<name<<":"<<"<";
    uint32_t *ptr = (uint32_t*)buf->contents();
    for(int i=0;i<buf->length()/4 - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[buf->length()/4 - 1]<<">";
    std::cout<<std::endl;
}
void printMTLBuffer(MTL::Buffer *buf, std::string name){
    std::cout<<name<<":"<<"<";
    float *ptr = (float*)buf->contents();
    for(int i=0;i<buf->length()/sizeof(float) - 1;i++){
        std::cout<<ptr[i]<<",";
    }
    std::cout<<ptr[buf->length()/sizeof(float) - 1]<<">";
    std::cout<<std::endl;
}
void printFloatArray(float* arr, std::string name, int length){
    std::cout<<name<<":"<<"<";
    for(int i=0;i<length - 1;i++){
        std::cout<<arr[i]<<",";
    }
    std::cout<<arr[length - 1]<<">";
    std::cout<<std::endl;
}
void generateRandomFloatData(MTL::Buffer *buffer, std::vector<float>& data){
    float *dataptr = (float *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/sizeof(float);index++){
        float gen_num = ((float)rand() / float(RAND_MAX))*10;
        dataptr[index] = gen_num;
        data.push_back(gen_num);
    }
}
float computeMean(const float* array, size_t size) {
    float sum = 0.0f;
    for (size_t i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum / static_cast<float>(size);
}
bool areEqualLowPrecision(float a, float b) {
    float precision = 1.0f;
    float diff = a - b;
    return (diff >= -precision) && (diff <= precision);
}

float computeStd(const float* array, size_t size, float mean) {
    float sumSq = 0.0f;

    for (size_t i = 0; i < size; ++i) {
        float diff = array[i] - mean;
        sumSq += diff * diff;
    }

    float variance = sumSq / static_cast<float>(size);
    return std::sqrt(variance);
}
float computeMin(const float* array, size_t size){
    float minVal = array[0];
    for(size_t i=1; i<size; i++){
        if(array[i]<minVal){
            minVal = array[i];
        }
    }
    return minVal;
}
float computeMax(const float* array, size_t size){
    float maxVal = array[0];
    for(size_t i=1; i<size; i++){
        if(array[i]>maxVal){
            maxVal = array[i];
        }
    }
    return maxVal;
}