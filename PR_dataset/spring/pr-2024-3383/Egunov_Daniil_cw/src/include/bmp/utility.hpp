#ifndef BMP_UTILITY_HPP
#define BMP_UTILITY_HPP

#include <fstream>

template<typename T>
void readFromStream(std::ifstream &stream, T &obj);

template<typename T>
void writeToStream(std::ofstream &stream, const T &obj);

#include "utility.tcc"

#endif //BMP_UTILITY_HPP
