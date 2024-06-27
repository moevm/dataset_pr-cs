//
// Created by niks on 10.05.2024.
//
#include <bits/stdc++.h>
#include <iomanip>
#include "../header/class_bmp.h"

using namespace std;

void BMP::info(){
    cout<< "+---------------------------------------+\n";
    cout<< "|                file header            |\n";
    cout<< "+---------------------------------------+\n";
    cout << "| file type            |" << setw(15)<<"BMP"<<setw(3)<<"|\n"<<setw(0);
    cout << "| file size            |" << setw(15)<<file_header.file_size<<setw(3)<<"|\n"<<setw(0);
    cout << "| file reserved 1      |" << setw(15)<<file_header.reserved1<<setw(3)<<"|\n"<<setw(0);
    cout << "| file reserved 2      |" << setw(15)<<file_header.reserved2<<setw(3)<<"|\n"<<setw(0);
    cout << "| offset data          |" << setw(15)<<file_header.offset_data<<setw(3)<<"|\n"<<setw(0);
    cout<< "+---------------------------------------+\n";
    cout << "\n\n";
    cout<< "+---------------------------------------+\n";
    cout<< "|                info header            |\n";
    cout<< "+---------------------------------------+\n";
    cout << "| size                 |" << setw(15)<<info_header.size<<setw(3)<<"|\n"<<setw(0);
    cout << "| width                |" << setw(15)<<info_header.width<<setw(3)<<"|\n"<<setw(0);
    cout << "| height               |" << setw(15)<<info_header.height<<setw(3)<<"|\n"<<setw(0);
    cout << "| planes               |" << setw(15)<<info_header.planes<<setw(3)<<"|\n"<<setw(0);
    cout << "| bit per pixel        |" << setw(15)<<info_header.bit_count<<setw(3)<<"|\n"<<setw(0);
    cout << "| compression          |" << setw(15)<<info_header.compression<<setw(3)<<"|\n"<<setw(0);
    cout << "| image size           |" << setw(15)<<info_header.image_size<<setw(3)<<"|\n"<<setw(0);
    cout << "| horizontal resolution|" << setw(15)<<info_header.x_resolution<<setw(3)<<"|\n"<<setw(0);
    cout << "| vertical resolution  |" << setw(15)<<info_header.y_resolution<<setw(3)<<"|\n"<<setw(0);
    cout << "| colors used          |" << setw(15)<<info_header.colors<<setw(3)<<"|\n"<<setw(0);
    cout << "| colors important     |" << setw(15)<<info_header.important_colors<<setw(3)<<"|\n"<<setw(0);
    cout<< "+---------------------------------------+\n";
}