#include <fstream>
#include "utility.hpp"

template<typename T>
void readFromStream(std::ifstream &stream, T &obj) {
    stream.read(reinterpret_cast<char *>(&obj), sizeof(T));
    if (!stream.good()) {
        throw std::ifstream::failure("Error reading from stream");
    }
}

template<typename T>
void writeToStream(std::ofstream &stream, const T &obj) {
    stream.write(reinterpret_cast<const char *>(&obj), sizeof(T));
    if (!stream.good()) {
        throw std::ofstream::failure("Error writing to stream");
    }
}
