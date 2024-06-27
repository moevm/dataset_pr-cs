#pragma once

#include <string>

namespace bmp_image_errors {
// Errors
const std::string k_error_pref = "ImageError: ";
const std::string k_error_get_pixel = "pixel cannot be reached";
const std::string k_error_not_bmp_image = "the file is not a BMP image";
const std::string k_error_comp = "compression isn't supported";
const std::string k_error_bits = "image must be 24 bit per pixel";
const std::string k_error_planes = "image must have only one plane";

}

class BmpImageError : public std::exception {
 public:
  explicit BmpImageError(std::string msg);
  BmpImageError(std::string msg, int x, int y);
  ~BmpImageError() = default;

  const char *what() const noexcept override;
 private:
  std::string msg_;
};
