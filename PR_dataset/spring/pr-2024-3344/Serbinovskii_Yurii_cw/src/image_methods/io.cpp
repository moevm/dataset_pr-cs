#include "one_class.h"
#include <fstream>
#include "../other/messages.h"
#include "../other/structs.h"

void Image::readBMP(std::string & path, std::string & function_to_run) {
    std::ifstream f(path, std::ios::binary);
    if (!f.is_open()) {
        std::cerr << "Failed to open the input file" << std::endl;
        exit(44);
    }

    f.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    f.read(reinterpret_cast<char*>(&infoHeader), sizeof(InfoHeader));
    
    if (fileHeader.type != 0x4D42 || infoHeader.bytesPerPixel != 24 || infoHeader.compression != 0) { 
        std::cerr << WRONG_FILE << std::endl;
        exit(41);
    }



    bm_height = abs(infoHeader.height);
    bm_width = abs(infoHeader.width);


    if (function_to_run == "info")
    {
        std::cout << "File info:\n\
        1) file header size 14\n\
        2) info header size 40\n\
        3) bits per pixel " << infoHeader.bytesPerPixel << "\n\
        4) compression " << infoHeader.compression << "\n\
        5) Width " << bm_width << "\n\
        6) Height " << bm_height << std::endl;
        exit(0);
    }

    bm_data.resize(bm_height);
    for (int y = 0; y < bm_height; y++)
    {
        bm_data[y].resize(bm_width);
    }

    const int padding = ((4 - (bm_width * 3) % 4) % 4);

    for (int y = 0; y < bm_height; y++) {
        for (int x = 0; x < bm_width; x++) {
            uint8_t pixel[3];
            f.read(reinterpret_cast<char*>(pixel), 3);
            bm_data[y][x].r = pixel[0];
            bm_data[y][x].g = pixel[1];
            bm_data[y][x].b = pixel[2];
        }
        f.ignore(padding);
    }
    f.close();

    for (int i = 0; i < bm_data.size() / 2; i++)
    {
        std::swap(bm_data[i], bm_data[bm_data.size()-i-1]);
    }

}

void Image::exportBMP(std::string & path) {
    for (int i = 0; i < bm_data.size() / 2; i++)
    {
        std::swap(bm_data[i], bm_data[bm_data.size()-i-1]);
    }

    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open())
    {
        std::cerr << "Failed to open the output file" << std::endl;
        exit(44);
    }
    infoHeader.height = bm_data.size();
    infoHeader.width = bm_data[0].size();
    f.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    f.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    const int padding = ((4 - (infoHeader.width * 3) % 4) % 4);

    unsigned char bmpPad[3]{0, 0, 0};
    for(int y = 0; y < infoHeader.height; y++)
    {
        for (int x = 0; x < infoHeader.width; x++)
        {
            unsigned char pixel[3];
            pixel[0] = bm_data[y][x].r;
            pixel[1] = bm_data[y][x].g;
            pixel[2] = bm_data[y][x].b;
            f.write(reinterpret_cast<char*>(pixel), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), padding);
    }    
    f.close();
}
