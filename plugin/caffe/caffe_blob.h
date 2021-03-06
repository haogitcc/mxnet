/*!
 * Copyright (c) 2016 by Contributors
 * \file caffe_blob.h
 * \brief conversion between tensor and caffeBlob
 * \author Haoran Wang 
*/
#ifndef PLUGIN_CAFFE_CAFFE_BLOB_H_
#define PLUGIN_CAFFE_CAFFE_BLOB_H_

#include<mshadow/tensor.h>
#include<mshadow/tensor_blob.h>
#include<vector>
#include<caffe/blob.hpp>

namespace mxnet {
namespace op {

namespace caffe {

// Declare Memory Type for Caffe blob
enum caffeMemoryTypes {Data, Grad, Non};

mshadow::TShape Vector2TShape(const std::vector<int> &vec_int);
std::vector<int> TShape2Vector(const mshadow::TShape &tshape);

// implementation of tensor to blob, called by TensorToBlob
template<typename Device, typename Dtype>
void SetDataGradToBlob(caffeMemoryTypes memType,
                       typename std::vector< ::caffe::Blob<Dtype>*>::iterator blob,
                       typename std::vector<mshadow::TBlob>::const_iterator itr);

/**
 * \brief The interface to convert mxnet's tensor to caffe's blob
 * \brief called in caffe_operator_inl.h
 */
template<typename Device, typename Dtype>
void TBlob2CaffeBlob(caffeMemoryTypes memType,
                     typename std::vector< ::caffe::Blob<Dtype>*>::iterator blob,
                     typename std::vector<mshadow::TBlob>::const_iterator tblob,
                     int n = 1) {
  for (int i = 0; i < n; ++i, ++blob, ++tblob) {
    (*blob)->Reshape(TShape2Vector((*tblob).shape_));
    SetDataGradToBlob<Device, Dtype>(memType, blob, tblob);
  }
}

}  // namespace caffe
}  // namespace op
}  // namespace mxnet

#endif  // PLUGIN_CAFFE_CAFFE_BLOB_H_
