#include "../include/functions.h"

void write(PICInfo& info, const string& file_name){
    ofstream file_out(file_name, ios::binary);
    if(!file_out){
        cerr << "Can't make file" << endl;
        exit(40);
    }

    file_out.write(reinterpret_cast<char*>(&info.header), sizeof(info.header));
    file_out.seekp(info.header.OffsetBits, ios::beg);
    file_out.write(reinterpret_cast<char*>(info.pixels.data()), size_image);

    file_out.close();
}
