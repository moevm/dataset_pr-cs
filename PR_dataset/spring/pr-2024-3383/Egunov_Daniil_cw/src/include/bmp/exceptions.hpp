#ifndef BMP_EXCEPTIONS_HPP
#define BMP_EXCEPTIONS_HPP

#include <stdexcept>

class BMPError : public std::runtime_error {
protected:
    std::string m_filepath;
public:
    explicit BMPError(const std::string &filepath,
                      const std::string &message = "A BMP error") :
            std::runtime_error(filepath + ": " + message),
            m_filepath(filepath) {};
};

class UnsupportedBMPHeaderFieldValueError : public BMPError {
protected:
    std::string m_field_name;
    std::string m_actual_value;
    std::string m_expected_value;

public:
    UnsupportedBMPHeaderFieldValueError(const std::string &filepath,
                                        const std::string &field_name,
                                        const std::string &actual_value,
                                        const std::string &expected_value) :
            BMPError(filepath, "Unsupported BMP field value in header: " + field_name +
                               " = " + actual_value + ", expected " + expected_value),
            m_field_name(field_name),
            m_actual_value(actual_value),
            m_expected_value(expected_value) {};
};

#endif //BMP_EXCEPTIONS_HPP
