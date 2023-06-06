bool areEqual(float a, float b) {
    return (fabs(a - b) <= FLT_EPSILON * std::max(1.0f, std::max(a, b)));
}
void generateRandomFloatData(MTL::Buffer *buffer){
    float *dataptr = (float *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/sizeof(float);index++){
        dataptr[index] = ((float)rand() / float(RAND_MAX))*10;
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
void generateRandomFloatData(MTL::Buffer *buffer, std::vector<float>& data){
    float *dataptr = (float *)buffer->contents();
    for(uint64_t index = 0; index<buffer->length()/sizeof(float);index++){
        float gen_num = ((float)rand() / float(RAND_MAX))*10;
        dataptr[index] = gen_num;
        data.push_back(gen_num);
    }
}