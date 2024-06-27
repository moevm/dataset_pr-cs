#include "../headers/additional_funcs.hpp"

#include <iostream>

void swapRgb(Rgb *rgb, int red, int green, int blue) {
    rgb->red = (unsigned char) red;
    rgb->green = (unsigned char) green;
    rgb->blue = (unsigned char) blue;
}

void print_help() {
    std::cout << "Course work for option 5.1, created by Aleksandr Galkin." << std::endl;
    std::cout << "\x1b[1;29;31mIMAGE FUNCTIONS HELP \x1b[0m" << std::endl;
    std::cout
            << "\x1b[1;29;33mFirst tip. To call any function you need to type flags which this function takes (\x1b[1;35m--<flag> or -<f> if short flag exists\x1b[1;29;33m) \x1b[0m"
            << std::endl;
    std::cout << "\x1b[7;32m LIST OF FUNCTIONS WITH FLAGS THAT THEY TAKE \x1b[0m" << std::endl;
    std::cout << "\x1b[7;38m 1. Draw rectangle (calls with flag \x1b[0m" << "\x1b[7;1;38m--rectangle\x1b[0m"
              << "\x1b[7;38m or \x1b[7;1;38m-r\x1b[7;38m)\x1b[0m" << std::endl;
    std::cout << "\x1b[3;38m    Flags for rectangle function: \x1b[0m" << std::endl;
    std::cout
            << "\x1b[3;38m     set coordinates of left upper corner:    \x1b[7;1;38mf lag --left_up\x1b[7;38m (or \x1b[7;1;38m-l\x1b[7;38m), as argument takes coordinates in format X.Y\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;38m     set coordinates of right down corner:    \x1b[7;1;38m flag --right_down\x1b[7;38m (or \x1b[7;1;38m-r\x1b[7;38m), as argument takes coordinates in format X.Y\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;38m     set thickness of rectangle outline:      \x1b[7;1;38m flag --thickness\x1b[7;38m (or \x1b[7;1;38m-t\x1b[7;38m), as argument takes integer value greater than 0\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;38m     set color of rectangle outline:          \x1b[7;1;38m flag --color\x1b[7;38m (or \x1b[7;1;38m-c\x1b[7;38m), as argument takes string in format 'RRR.GGG.BBB'\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;38m     will rectangle be filled or not:         \x1b[7;1;38m flag --fill\x1b[7;38m (or \x1b[7;1;38m-f\x1b[7;38m), if flag is set, it will be filled else will not\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;38m     color of filling if rectangle is filled: \x1b[7;1;38m flag --fill_color\x1b[7;38m, as argument takes string in format 'RRR.GGG.BBB'\x1b[0m\n"
            << std::endl;
    std::cout << "\x1b[7;36m 2. Draw ornament (calls with flag \x1b[0m" << "\x1b[7;1;36m--ornament\x1b[0m"
              << "\x1b[7;36m or \x1b[7;1;36m-O\x1b[7;36m)\x1b[0m" << std::endl;
    std::cout << "\x1b[3;36m    Flags for ornament function: \x1b[0m" << std::endl;
    std::cout
            << "\x1b[3;36m     choose pattern of drawn ornament: \x1b[7;1;36m flag --pattern\x1b[7;38m (or \x1b[7;1;36m-p\x1b[7;36m), as argument takes one of following strings: 'rectangle', 'circle' or 'semicircles'\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;36m     set color of ornament:            \x1b[7;1;36m flag --color\x1b[7;38m (or \x1b[7;1;36m-c\x1b[7;36m), as argument takes string in format 'RRR.GGG.BBB'\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;36m     set thickness of ornament:        \x1b[7;1;36m flag --thickness\x1b[7;38m (or \x1b[7;1;36m-t\x1b[7;36m), argument - integer value greater than 0 (may be omitted if pattern is circle)\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;36m     set count of pattern fragments:   \x1b[7;1;36m flag --count\x1b[7;38m, as argument takes integer greater than 0 (may be omitted if pattern is circle)\x1b[0m\n"
            << std::endl;
    std::cout << "\x1b[7;34m 3. Rotate field of image (calls with flag \x1b[0m" << "\x1b[7;1;34m--rotate)\x1b[0m"
              << std::endl;
    std::cout << "\x1b[3;34m    Flags for rotate function: \x1b[0m" << std::endl;
    std::cout
            << "\x1b[3;34m     set coordinates of left upper corner: \x1b[7;1;34m flag --left_up\x1b[7;34m (or \x1b[7;1;34m-l\x1b[7;34m), as argument takes coordinates in format X.Y\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;34m     set coordinates of right down corner: \x1b[7;1;34m flag --right_down\x1b[7;34m (or \x1b[7;1;34m-r\x1b[7;34m), as argument takes coordinates in format X.Y\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;34m     set angle of rotation:                \x1b[7;1;38m flag --angle, as argument takes integer value in degrees: [90, 180, 270]\x1b[0m\n"
            << std::endl;
    std::cout << "\x1b[7;35m 4. Draw circle (calls with flag \x1b[0m" << "\x1b[7;1;35m--circle)\x1b[0m\x1b[0m"
              << std::endl;
    std::cout << "\x1b[3;35m    Flags for circle function: \x1b[0m" << std::endl;
    std::cout
            << "\x1b[3;35m     set coordinates of circle's center:   \x1b[7;1;35m flag --center, as argument takes coordinates in format X.Y\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;35m     set radius of circle:                 \x1b[7;1;35m flag --radius\x1b[7;38m, as argument takes integer value greater than 0\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;35m     set thickness of circle's outline:    \x1b[7;1;35m flag --thickness\x1b[7;35m (or \x1b[7;1;35m-t\x1b[7;35m), as argument takes integer value greater than 0\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;35m     set color of circle's outline:        \x1b[7;1;35m flag --color\x1b[7;35m (or \x1b[7;1;35m-c\x1b[7;35m), as argument takes string in format 'RRR.GGG.BBB'\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;35m     will circle be filled or not:         \x1b[7;1;35m flag --fill\x1b[7;35m (or \x1b[7;1;35m-f\x1b[7;35m), if flag is set, it will be filled else will not\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;35m     color of filling if circle is filled: \x1b[7;1;35m flag --fill_color\x1b[7;35m, as argument takes string in format 'RRR.GGG.BBB'\x1b[0m\n"
            << std::endl;
    std::cout << "\x1b[3;37m Additional flags:\x1b[0m" << std::endl;
    std::cout << "\x1b[3;37m     --help or -h: prints this message\x1b[0m" << std::endl;
    std::cout << "\x1b[3;37m     --info: prints info about bitmap\x1b[0m" << std::endl;
    std::cout
            << "\x1b[3;37m     --input or -i: reads bitmap from file given as argument (if flag isn't set, program will try to read file with name from last argument)\x1b[0m"
            << std::endl;
    std::cout
            << "\x1b[3;37m     --output or -o: writes bitmap to file given as argument (if flag isn't set, program will write file to out.bmp)\x1b[0m"
            << std::endl;
}

Bmp::Bmp(const char *filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << filename << " not found" << std::endl;
        exit(41);
    } else {
        this->header = new BitmapFileHeader;
        this->info = new BitmapInfoHeader;
        file.read(reinterpret_cast<char *>(this->header), sizeof(BitmapFileHeader));
        file.read(reinterpret_cast<char *>(this->info), sizeof(BitmapInfoHeader));
        if (header->signature != 0x4D42) {
            std::cout << "Not a bitmap file" << std::endl;
            exit(41);
        }
        if (info->bitsPerPixel != 24) {
            std::cout << "Not a 24-bit bitmap file" << std::endl;
            exit(41);
        }
    }
    data = new Rgb *[this->info->height];
    padding = (int) (4 - this->info->width * 3 % 4) % 4;
    for (size_t i = 0; i < this->info->height; i++) {
        data[i] = new Rgb[this->info->width];
        file.read(reinterpret_cast<char *>(data[i]), (this->info->width) * sizeof(Rgb));
        file.ignore(padding);
    }
    file.close();
}

void Bmp::get_info() {
    std::cout << "Signature: " << header->signature << std::endl;
    std::cout << "File size: " << header->fileSize << std::endl;
    std::cout << "Reserved 1: " << header->reserved1 << std::endl;
    std::cout << "Reserved 2: " << header->reserved2 << std::endl;
    std::cout << "Bitmap offset: " << header->pixelArrOffset << std::endl;
    std::cout << "Header size: " << info->headerSize << std::endl;
    std::cout << "Width: " << info->width << std::endl;
    std::cout << "Height: " << info->height << std::endl;
    std::cout << "Planes: " << info->planes << std::endl;
    std::cout << "Bits per pixel:" << info->bitsPerPixel << std::endl;
    std::cout << "Compression: " << info->compression << std::endl;
    std::cout << "Image size: " << info->imageSize << std::endl;
    std::cout << "X pixels per meter: " << info->xPixelsPerMeter << std::endl;
    std::cout << "Y pixels per meter: " << info->yPixelsPerMeter << std::endl;
    std::cout << "Colors used: " << info->colorsInColorTable << std::endl;
    std::cout << "Important colors: " << info->importantColorCount << std::endl;
}

Bmp::~Bmp() {
    for (size_t i = 0; i < this->info->height; i++) {
        delete[] data[i];
    }
    delete[] data;
    delete info;
    delete header;
}

void Bmp::save(const char *output_filename) {
    std::ofstream file(output_filename, std::ios::binary | std::ios::out);
    file.write(reinterpret_cast<const char *>(this->header), sizeof(BitmapFileHeader));
    file.write(reinterpret_cast<const char *>(this->info), sizeof(BitmapInfoHeader));
    for (size_t i = 0; i < this->info->height; i++) {
        file.write(reinterpret_cast<const char *>(data[i]), (this->info->width) * sizeof(Rgb));
        file.write("0", padding);
    }
    file.close();
}

void Bmp::compress(int n) {
    BitmapFileHeader *new_header = new BitmapFileHeader;
    BitmapInfoHeader *new_info = new BitmapInfoHeader;
    new_header->signature = 0x4d42;
    new_header->fileSize = info->width / n * info->height / n * 3 + 54;
    new_header->pixelArrOffset = 54;
    new_header->reserved1 = 0;
    new_header->reserved2 = 0;
    new_info->width = info->width / n;
    new_info->height = info->height / n;
    new_info->bitsPerPixel = 24;
    new_info->imageSize = new_info->width * new_info->height * 3;
    new_info->colorsInColorTable = 0;
    new_info->compression = 0;
    new_info->headerSize = 40;
    new_info->importantColorCount = 0;
    new_info->planes = 1;
    new_info->xPixelsPerMeter = 3780;
    new_info->yPixelsPerMeter = 3780;
    Rgb **new_data = new Rgb *[new_info->height];
    for (int i = 0; i < new_info->height; ++i) new_data[i] = new Rgb[new_info->width];
    for (int i = 0; i < new_info->height; ++i) {
        for (int j = 0; j < new_info->width; ++j) {
            int rSum = 0, gSum = 0, bSum = 0;
            for (int k = 0; k < n && i*n + k < info->height; ++k) {
                for (int l = 0; l < n && j*n + l < info->width; ++l) {
                    rSum += data[info->height - i*n - k - 1][j*n + l].red;
                    gSum += data[info->height - i*n - k - 1][j*n + l].green;
                    bSum += data[info->height - i*n - k - 1][j*n + l].blue;
                }
            }
            new_data[new_info->height - i - 1][j].red = rSum / (n * n);
            new_data[new_info->height - i - 1][j].green = gSum / (n * n);
            new_data[new_info->height - i - 1][j].blue = bSum / (n * n);

        }
    }
    delete[]data;
    data = new_data;
    info = new_info;
    header = new_header;
    padding = (4 - (info->width * 3 % 4)) % 4;
}