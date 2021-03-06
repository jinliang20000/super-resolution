// This binary is used just to visualize a single image using the image
// visualization tools in the SuperResolution codebase. This binary can display
// regular images as well as false-color representations of hyperspectral
// images.

#include "image/image_data.h"
#include "util/data_loader.h"
#include "util/macros.h"
#include "util/util.h"
#include "util/visualization.h"

#include "gflags/gflags.h"
#include "glog/logging.h"

// The only required argument is the path the the image. This can either be a
// regular image file or a hyperspectral configuration file which specifies
// information about a binary ENVI image file that can be loaded at the
// specified range.
DEFINE_string(image_path, "",
    "The path to an input image file (regular or hyperspectral config).");

// Optionally, set this flag to enable automatic image resizing. This will
// scale smaller images up and scale larger images down to visualize them more
// uniformly on the screen.
DEFINE_bool(rescale_image, false,
    "If true, rescales the image to fit on the screen.");

// Optionally, this parameter will enable printing out statistics about the
// image for the user to get more information. Statistics include the image
// dimensions (as loaded into memory), the number of negative pixel values, the
// min/max pixel values, etc.
DEFINE_bool(print_image_info, false,
    "If true, the image data report will be printed to standard output.");

int main(int argc, char** argv) {
  super_resolution::util::InitApp(argc, argv, "Image visualization.");

  REQUIRE_ARG(FLAGS_image_path);

  super_resolution::ImageData image =
      super_resolution::util::LoadImage(FLAGS_image_path);
  if (FLAGS_print_image_info) {
    image.GetImageDataReport().Print();
  }
  super_resolution::util::DisplayImage(
      image, "Image: " + FLAGS_image_path, FLAGS_rescale_image);

  return EXIT_SUCCESS;
}
