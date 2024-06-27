#pragma once

#include <string>

namespace image_editor_errors {
// Errors
const std::string k_error_pref = "ImageEditorError: ";
const std::string k_error_wrong_angle = "the programme does not support this angle";
}

class ImageEditorError : public std::exception {
 public:
  explicit ImageEditorError(std::string msg);
  ~ImageEditorError() = default;

  const char *what() const noexcept override;
 private:
  std::string msg_;
};
