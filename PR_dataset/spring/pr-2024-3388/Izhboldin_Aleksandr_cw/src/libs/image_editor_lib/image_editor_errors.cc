#include "image_editor_errors.h"

using namespace image_editor_errors;

ImageEditorError::ImageEditorError(std::string msg) {
  msg_ = k_error_pref + msg;
}

const char *ImageEditorError::what() const noexcept {
  return msg_.c_str();
}
