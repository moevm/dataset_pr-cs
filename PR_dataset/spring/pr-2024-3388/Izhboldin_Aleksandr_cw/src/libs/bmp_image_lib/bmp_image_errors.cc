#include "bmp_image_errors.h"

using namespace bmp_image_errors;

BmpImageError::BmpImageError(std::string msg) {
  msg_ = k_error_pref + msg;
}

BmpImageError::BmpImageError(std::string msg, int x, int y) : BmpImageError(msg) {
  msg_ += " with coords: x=" + std::to_string(x) + " y=" + std::to_string(y);
}

const char *BmpImageError::what() const noexcept {
  return msg_.c_str();
}
