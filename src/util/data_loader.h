// Provides data file I/O utility functions, including a LoadImages function
// that can read image files in any supported format from a given data path.

#ifndef SRC_UTIL_DATA_LOADER_H_
#define SRC_UTIL_DATA_LOADER_H_

#include <string>
#include <vector>

#include "image/image_data.h"

namespace super_resolution {
namespace util {

// Returns true if the given path is a directory, and false otherwise. If the
// given path is not valid or cannot be accessed, this will cause an error.
bool IsDirectory(const std::string& path);

// Returns true if the given path is a regular file, and false otherwise.
// Regular files are standard files (binary or text), and they do not include
// directories, pipes, symlinks, etc. If the given path is not valid or cannot
// be accessed, this will cause an error.
//
// If include_hidden_files is false, any hidden files will NOT be considered as
// valid files, returning false.
bool IsFile(const std::string& path, const bool include_hidden_files = false);

// Returns true if the given extension is a supported standard image extension
// that can be read or written with OpenCV.
bool IsSupportedImageExtension(const std::string& extension);

// Returns a list of images loaded from the given data_path. If the data_path
// points to a directory, the list will contain images loaded from all files in
// that directory. If it is the name of a file, the returned list will contain
// that single image.
//
// The given data_path should be an image file or directory containing
// multiple image files. The file(s) can be one of the following formats:
//   - Standard image file (.jpg, .png, etc.)
//   - TODO: Standard video file (.avi, .mpg, etc.)
//   - Hyperspectral data in text format.
//   - TODO: Binary hyperspectral data files.
// Unsupported or invalid files or directories will result in an error.
std::vector<ImageData> LoadImages(const std::string& data_path);

// A shortcut for LoadImages if only a single image is needed.
ImageData LoadImage(const std::string& data_path);

// Saves the given image to a file at the given path. If the image has one or
// three channels (monochrome or RGB, respectively), it will be saved as an
// OpenCV image. Otherwise, it will be saved as a hyperspectral image. The user
// provides the extension which defines the type of image that is saved (e.g.
// JPEG or PNG).
void SaveImage(const ImageData& image, const std::string& data_path);

}  // namespace util
}  // namespace super_resolution

#endif  // SRC_UTIL_DATA_LOADER_H_
