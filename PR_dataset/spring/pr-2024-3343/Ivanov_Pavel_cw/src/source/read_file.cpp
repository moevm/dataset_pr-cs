#include "../include/functions.h"
unsigned int size_image;

PICInfo read(const string& file_name){
    BMPHeader header{};

    ifstream file_in(file_name, ios::binary);
    if(!file_in.is_open()){
        cerr << "Can't open file" << endl;
        exit(40);
    }

    file_in.read(reinterpret_cast<char*>(&header), sizeof(header));

    if(header.Type[0] != 'B' or header.Type[1] != 'M'){
        cerr << "Incorrect file format" << endl;
        exit(40);
    }
    if(header.BitCount != 24){
        cerr << "Bit per pixel must be equal 24" << endl;
        exit(40);
    }
    if (header.Width <= 0 || header.Height <= 0) {
        cerr << "Incorrect size of image" << endl;
        exit(40);
    }
    if (header.Compression != 0) {
        cerr << "Compression must be equal 0" << endl;
        exit(40);
    }

    int bytes_per_pixel = header.BitCount / 8;
    int bytes_per_row = ((header.Width * bytes_per_pixel + 3) / 4) * 4;
    size_image = header.Height * bytes_per_row;


    vector<uint8_t> pixels;
    pixels.resize(size_image);
    file_in.seekg(header.OffsetBits, iostream::beg);
    file_in.read(reinterpret_cast<char*>(pixels.data()), size_image);

    PICInfo info{header, pixels};
    file_in.close();

    return info;
}
