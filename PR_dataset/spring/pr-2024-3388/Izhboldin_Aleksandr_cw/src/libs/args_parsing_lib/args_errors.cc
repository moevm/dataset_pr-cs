#include "args_errors.h"

using namespace arg_errors;

ArgsExceptions::ArgsExceptions(std::string msg) {
  msg_ = k_error_pref + msg;
}

ArgsExceptions::ArgsExceptions(std::string msg, std::string place) : ArgsExceptions(msg) {
  msg_ += k_error_pref_place + place;
}

const char *ArgsExceptions::what() const noexcept {
  return msg_.c_str();
}