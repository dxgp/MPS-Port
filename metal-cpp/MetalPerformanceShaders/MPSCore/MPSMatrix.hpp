#pragma once
#include "../../Foundation/NSObject.hpp"
#include "../../Metal/Metal.hpp"
#include "../MPSPrivate.hpp"

namespace MPS{
    class MatrixDescriptor: public NS::Referencing<MPS::MatrixDescriptor>{
        NS::UInteger rows();
        NS::UInteger columns();
        NS::UInteger matrices() const;
        MPS::DataType dataType();
        NS::UInteger rowBytes();
        NS::UInteger matrixBytes() const;
        
        //(DEPRECATED) static MPS::MatrixDescriptor* matrixDescriptorWithDimensions(NS::UInteger rows, NS::UInteger columns, NS::UInteger rowBytes, MPS::DataType dataType);
        static MPS::MatrixDescriptor* matrixDescriptorWithRows(NS::UInteger rows, NS::UInteger columns, NS::UInteger rowBytes, MPS::DataType dataType);
        static MPS::MatrixDescriptor* matrixDescriptorWithRows(NS::UInteger rows, NS::UInteger columns, NS::UInteger matrices, NS::UInteger rowBytes, NS::UInteger matrixBytes, MPS::DataType dataType);
        static size_t rowBytesForColumns(NS::UInteger columns, MPS::DataType dataType);
    };
    class VectorDescriptor: public NS::Referencing<MPS::VectorDescriptor>{
        NS::UInteger length();
        NS::UInteger vectors() const;
        MPS::DataType dataType();
        NS::UInteger vectorBytes() const;
        static MPS::VectorDescriptor* vectorDescriptorWithLength(NS::UInteger length, MPS::DataType dataType);
        static MPS::VectorDescriptor* vectorDescriptorWithLength(NS::UInteger length, NS::UInteger vectors, NS::UInteger vectorBytes, MPS::DataType dataType);
        static size_t vectorBytesForLength(NS::UInteger length, MPS::DataType dataType);
    };
    class Matrix: public NS::Referencing<MPS::Matrix>{
        MTL::Device* device() const;
        NS::UInteger rows() const;
        NS::UInteger columns() const;
        NS::UInteger matrices() const;
        MPS::DataType dataType() const;
        NS::UInteger rowBytes() const;
        NS::UInteger matrixBytes() const;
        NS::UInteger offset() const;
        MTL::Buffer* data() const;
        MPS::Matrix* initWithBuffer(MTL::Buffer* buffer, MPS::MatrixDescriptor* descriptor);
        MPS::Matrix* initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset, MPS::MatrixDescriptor* descriptor);
        MPS::Matrix* initWithDevice(MTL::Device* device, MPS::MatrixDescriptor* descriptor);
        void synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer);
        NS::UInteger resourceSize();
    };
    class Vector: public NS::Referencing<MPS::Vector>{
        MTL::Device* device() const;
        NS::UInteger length() const;
        NS::UInteger vectors() const;
        MPS::DataType dataType() const;
        NS::UInteger vectorBytes() const;
        NS::UInteger offset() const;
        MTL::Buffer* data() const;
        MPS::Vector* initWithBuffer(MTL::Buffer* buffer, MPS::VectorDescriptor* descriptor);
        MPS::Vector* initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset, MPS::VectorDescriptor* descriptor);
        MPS::Vector* initWithDevice(MTL::Device* device, MPS::VectorDescriptor* descriptor);
        void synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer);
        NS::UInteger resourceSize();
    };
    class TemporaryMatrix: public NS::Referencing<MPS::Matrix>{
        static MPS::TemporaryMatrix* temporaryMatrixWithCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::MatrixDescriptor* matrixDescriptor);
        static void prefetchStorageWithCommandBuffer(MTL::CommandBuffer* commandBuffer, NS::Array* descriptorList);
        // (UNAVAILABLE) MPS::TemporaryMatrix* initWithBuffer(MTL::Buffer* buffer, MPS::MatrixDescriptor* descriptor);
        NS::UInteger readCount();
    };
    class TemporaryVector: public NS::Referencing<MPS::Vector>{
        static MPS::TemporaryVector* temporaryVectorWithCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::VectorDescriptor* descriptor);
        static void prefetchStorageWithCommandBuffer(MTL::CommandBuffer* commandBuffer, NS::Array* descriptorList);
        NS::UInteger readCount();
    };
}

_MPS_INLINE NS::UInteger MPS::MatrixDescriptor::rows(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(rows));
}
_MPS_INLINE NS::UInteger MPS::MatrixDescriptor::columns(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(columns));
}
_MPS_INLINE NS::UInteger MPS::MatrixDescriptor::matrices() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(matrices));
}
_MPS_INLINE MPS::DataType MPS::MatrixDescriptor::dataType(){
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE NS::UInteger MPS::MatrixDescriptor::rowBytes(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(rowBytes));
}
_MPS_INLINE NS::UInteger MPS::MatrixDescriptor::matrixBytes() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(matrixBytes));
}
_MPS_INLINE MPS::MatrixDescriptor* MPS::MatrixDescriptor::matrixDescriptorWithRows(NS::UInteger rows, NS::UInteger columns, NS::UInteger rowBytes, MPS::DataType dataType){
    return Object::sendMessage<MPS::MatrixDescriptor*>(_MPS_PRIVATE_CLS(MPSMatrixDescriptor), _MPS_PRIVATE_SEL(matrixDescriptorWithRows_columns_rowBytes_dataType_), rows, columns, rowBytes, dataType);
}
_MPS_INLINE MPS::MatrixDescriptor* MPS::MatrixDescriptor::matrixDescriptorWithRows(NS::UInteger rows, NS::UInteger columns, NS::UInteger matrices, NS::UInteger rowBytes, NS::UInteger matrixBytes, MPS::DataType dataType){
    return Object::sendMessage<MPS::MatrixDescriptor*>(_MPS_PRIVATE_CLS(MPSMatrixDescriptor), _MPS_PRIVATE_SEL(matrixDescriptorWithRows_columns_matrices_rowBytes_matrixBytes_dataType_), rows, columns, matrices, rowBytes, matrixBytes, dataType);
}
_MPS_INLINE size_t MPS::MatrixDescriptor::rowBytesForColumns(NS::UInteger columns, MPS::DataType dataType){
    return Object::sendMessage<size_t>(_MPS_PRIVATE_CLS(MPSMatrixDescriptor), _MPS_PRIVATE_SEL(rowBytesForColumns_dataType_), columns, dataType);
}

// Class VectorDescriptor
_MPS_INLINE NS::UInteger MPS::VectorDescriptor::length(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(length));
}
_MPS_INLINE NS::UInteger MPS::VectorDescriptor::vectors() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(vectors));
}
_MPS_INLINE MPS::DataType MPS::VectorDescriptor::dataType(){
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE NS::UInteger MPS::VectorDescriptor::vectorBytes() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(vectorBytes));
}
_MPS_INLINE MPS::VectorDescriptor* MPS::VectorDescriptor::vectorDescriptorWithLength(NS::UInteger length, MPS::DataType dataType){
    return Object::sendMessage<MPS::VectorDescriptor*>(_MPS_PRIVATE_CLS(MPSVectorDescriptor), _MPS_PRIVATE_SEL(vectorDescriptorWithLength_dataType_), length, dataType);
}
_MPS_INLINE MPS::VectorDescriptor* MPS::VectorDescriptor::vectorDescriptorWithLength(NS::UInteger length, NS::UInteger vectors, NS::UInteger vectorBytes, MPS::DataType dataType){
    return Object::sendMessage<MPS::VectorDescriptor*>(_MPS_PRIVATE_CLS(MPSVectorDescriptor), _MPS_PRIVATE_SEL(vectorDescriptorWithLength_vectors_vectorBytes_dataType_), length, vectors, vectorBytes, dataType);
}
_MPS_INLINE size_t MPS::VectorDescriptor::vectorBytesForLength(NS::UInteger length, MPS::DataType dataType){
    return Object::sendMessage<size_t>(_MPS_PRIVATE_CLS(MPSVectorDescriptor), _MPS_PRIVATE_SEL(vectorBytesForLength_dataType_), length, dataType);
}

//Class Matrix
_MPS_INLINE MTL::Device* MPS::Matrix::device() const{
    return Object::sendMessage<MTL::Device*>(this, _MPS_PRIVATE_SEL(device));
}
_MPS_INLINE NS::UInteger MPS::Matrix::rows() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(rows));
}
_MPS_INLINE NS::UInteger MPS::Matrix::columns() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(columns));
}
_MPS_INLINE NS::UInteger MPS::Matrix::matrices() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(matrices));
}
_MPS_INLINE MPS::DataType MPS::Matrix::dataType() const{
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE NS::UInteger MPS::Matrix::rowBytes() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(rowBytes));
}
_MPS_INLINE NS::UInteger MPS::Matrix::matrixBytes() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(matrixBytes));
}
_MPS_INLINE NS::UInteger MPS::Matrix::offset() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(offset));
}
_MPS_INLINE MTL::Buffer* MPS::Matrix::data() const{
    return Object::sendMessage<MTL::Buffer*>(this, _MPS_PRIVATE_SEL(data));
}
_MPS_INLINE MPS::Matrix* MPS::Matrix::initWithBuffer(MTL::Buffer* buffer, MPS::MatrixDescriptor* descriptor){
    return Object::sendMessage<MPS::Matrix*>(this, _MPS_PRIVATE_SEL(initWithBuffer_descriptor_), buffer, descriptor);
}
_MPS_INLINE MPS::Matrix* MPS::Matrix::initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset, MPS::MatrixDescriptor* descriptor){
    return Object::sendMessage<MPS::Matrix*>(this, _MPS_PRIVATE_SEL(initWithBuffer_offset_descriptor_), buffer, offset, descriptor);
}
_MPS_INLINE MPS::Matrix* MPS::Matrix::initWithDevice(MTL::Device* device, MPS::MatrixDescriptor* descriptor){
    return Object::sendMessage<MPS::Matrix*>(this, _MPS_PRIVATE_SEL(initWithDevice_descriptor_), device, descriptor);
}
_MPS_INLINE void MPS::Matrix::synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer){
    Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(synchronizeOnCommandBuffer_), commandBuffer);
}
_MPS_INLINE NS::UInteger MPS::Matrix::resourceSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(resourceSize));
}
// class Vector
_MPS_INLINE MTL::Device* MPS::Vector::device() const{
    return Object::sendMessage<MTL::Device*>(this, _MPS_PRIVATE_SEL(device));
}
_MPS_INLINE NS::UInteger MPS::Vector::vectors() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(vectors));
}
_MPS_INLINE NS::UInteger MPS::Vector::length() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(length));
}
_MPS_INLINE MPS::DataType MPS::Vector::dataType() const{
    return Object::sendMessage<MPS::DataType>(this, _MPS_PRIVATE_SEL(dataType));
}
_MPS_INLINE NS::UInteger MPS::Vector::vectorBytes() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(vectorBytes));
}
_MPS_INLINE NS::UInteger MPS::Vector::offset() const{
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(offset));
}
_MPS_INLINE MTL::Buffer* MPS::Vector::data() const{
    return Object::sendMessage<MTL::Buffer*>(this, _MPS_PRIVATE_SEL(data));
}
_MPS_INLINE MPS::Vector* MPS::Vector::initWithBuffer(MTL::Buffer* buffer, MPS::VectorDescriptor* descriptor){
    return Object::sendMessage<MPS::Vector*>(this, _MPS_PRIVATE_SEL(initWithBuffer_descriptor_), buffer, descriptor);
}
_MPS_INLINE MPS::Vector* MPS::Vector::initWithBuffer(MTL::Buffer* buffer, NS::UInteger offset, MPS::VectorDescriptor* descriptor){
    return Object::sendMessage<MPS::Vector*>(this, _MPS_PRIVATE_SEL(initWithBuffer_offset_descriptor_), buffer, offset, descriptor);
}
_MPS_INLINE MPS::Vector* MPS::Vector::initWithDevice(MTL::Device* device, MPS::VectorDescriptor* descriptor){
    return Object::sendMessage<MPS::Vector*>(this, _MPS_PRIVATE_SEL(initWithDevice_descriptor_), device, descriptor);
}
_MPS_INLINE void MPS::Vector::synchronizeOnCommandBuffer(MTL::CommandBuffer* commandBuffer){
    return Object::sendMessage<void>(this, _MPS_PRIVATE_SEL(synchronizeOnCommandBuffer_), commandBuffer);
}
_MPS_INLINE NS::UInteger MPS::Vector::resourceSize(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(resourceSize));
}
// class TemporaryMatrix
_MPS_INLINE MPS::TemporaryMatrix* MPS::TemporaryMatrix::temporaryMatrixWithCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::MatrixDescriptor* descriptor){
    return Object::sendMessage<MPS::TemporaryMatrix*>(_MPS_PRIVATE_CLS(MPSTemporaryMatrix), _MPS_PRIVATE_SEL(temporaryMatrixWithCommandBuffer_matrixDescriptor_), commandBuffer, descriptor);
}
_MPS_INLINE void MPS::TemporaryMatrix::prefetchStorageWithCommandBuffer(MTL::CommandBuffer* commandBuffer, NS::Array* descriptorList){
    Object::sendMessage<void>(_MPS_PRIVATE_CLS(MPSTemporaryMatrix), _MPS_PRIVATE_SEL(prefetchStorageWithCommandBuffer_matrixDescriptorList_), commandBuffer, descriptorList);
}
_MPS_INLINE NS::UInteger MPS::TemporaryMatrix::readCount(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(readCount));
}
// class TemporaryVector
_MPS_INLINE MPS::TemporaryVector* MPS::TemporaryVector::temporaryVectorWithCommandBuffer(MTL::CommandBuffer* commandBuffer, MPS::VectorDescriptor* descriptor){
    return Object::sendMessage<MPS::TemporaryVector*>(_MPS_PRIVATE_CLS(MPSTemporaryVector), _MPS_PRIVATE_SEL(temporaryVectorWithCommandBuffer_descriptor_), commandBuffer, descriptor);
}
_MPS_INLINE void MPS::TemporaryVector::prefetchStorageWithCommandBuffer(MTL::CommandBuffer* commandBuffer, NS::Array* descriptorList){
    Object::sendMessage<void>(_MPS_PRIVATE_CLS(MPSTemporaryVector), _MPS_PRIVATE_SEL(prefetchStorageWithCommandBuffer_descriptorList_), commandBuffer, descriptorList);
}
_MPS_INLINE NS::UInteger MPS::TemporaryVector::readCount(){
    return Object::sendMessage<NS::UInteger>(this, _MPS_PRIVATE_SEL(readCount));
}