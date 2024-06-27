#pragma once

#include <string>

namespace arg_errors {
// Errors
const std::string k_error_pref = "ArgError: ";
const std::string k_error_pref_place = " in arg:";
const std::string k_error_multifunction("more or less than one functions were selected");
const std::string k_error_not_enough_args = "the necessary arguments were not given";
const std::string k_error_not_correct_arg_val = "the argument value is not set in the correct format";
const std::string k_error_unknown_arg = "an unknown argument was received";
const std::string k_error_missing_arg = "the obligatory argument was not provided";
const std::string k_error_no_input_file = "no input file was provided";
const std::string k_error_input_output_same_file = "the input and output file are the same";
}

class ArgsExceptions : public std::exception {
 public:
  explicit ArgsExceptions(std::string msg);
  ArgsExceptions(std::string msg, std::string place);
  ~ArgsExceptions() = default;

  const char *what() const noexcept override;
 private:
  std::string msg_;
};