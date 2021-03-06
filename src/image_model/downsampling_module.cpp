#include "image_model/downsampling_module.h"

#include <cmath>

#include "image/image_data.h"
#include "util/matrix_util.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "glog/logging.h"

namespace super_resolution {

DownsamplingModule::DownsamplingModule(const int scale) : scale_(scale) {
  CHECK_GE(scale_, 1);
}

void DownsamplingModule::ApplyToImage(
    ImageData* image_data, const int index) const {

  CHECK_NOTNULL(image_data);

  const double scale_factor = 1.0 / static_cast<double>(scale_);
  // Area interpolation method aliases images by dropping pixels.
  image_data->ResizeImage(scale_factor, INTERPOLATE_NEAREST);
}

void DownsamplingModule::ApplyTransposeToImage(
    ImageData* image_data, const int index) const {

  CHECK_NOTNULL(image_data);

  // The transpose of downsampling is trivial upsampling to size * scale_. We
  // will use non-interpolating upsampling, so the pixels will be mapped to the
  // higher resolution with zeros padded between them. This is defined in
  // ImageData::ResizeImage() using additive interpolation.
  image_data->ResizeImage(scale_, INTERPOLATE_ADDITIVE);
}

cv::Mat DownsamplingModule::GetOperatorMatrix(
    const cv::Size& image_size, const int index) const {

  const int num_high_res_pixels = image_size.width * image_size.height;
  const int num_low_res_pixels = num_high_res_pixels / (scale_ * scale_);
  cv::Mat downsampling_matrix = cv::Mat::zeros(
      num_low_res_pixels, num_high_res_pixels, util::kOpenCvMatrixType);

  int next_row = 0;
  for (int row = 0; row < image_size.height; ++row) {
    if (row % scale_ != 0) {
      continue;
    }
    for (int col = 0; col < image_size.width; ++col) {
      if (col % scale_ != 0) {
        continue;
      }
      const int index = row * image_size.width + col;
      downsampling_matrix.at<double>(next_row, index) = 1;
      next_row++;
    }
  }
  return downsampling_matrix;
}

}  // namespace super_resolution
