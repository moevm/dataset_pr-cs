#include "new_file.h"

void writeBMP(const std::string& filename, const BMPHeader& header, const BMPInfoHeader& infoHeader, const std::vector<std::vector<Pixel>>& bitArr) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing");
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    int absHeight = abs(infoHeader.height);

    for (int i = absHeight - 1; i >= 0; i--) { // Запись снизу вверх
        for (const auto& pixel : bitArr[i]) {
            file.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
        }
        for (int j = 0; j < (4 - (infoHeader.width * sizeof(Pixel)) % 4) % 4; ++j) {
            char zero = 0;
            file.write(&zero, 1);
        }
    }

    file.close();
}