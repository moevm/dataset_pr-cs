#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <complex>
#include <getopt.h>

using std::cin;
using std::cout;
using std::dec;
using std::endl;
using std::hex;
using std::stoi;
using std::string;
using std::unordered_map;

#pragma pack(push, 1)
struct BitmapFileHeader
{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
};

struct BitmapInfoHeader
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
};

struct Rgb
{
    unsigned char b;
    unsigned char g;
    unsigned char r;

    size_t hash() const
    {
        return r ^ (g << 8) ^ (b << 16);
    }

    bool operator==(const Rgb &other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }
};

#pragma pack(pop)

namespace std
{
    // Специализация std::hash для Rgb
    template <>
    struct hash<Rgb>
    {
        size_t operator()(const Rgb &color) const
        {
            return color.hash();
        }
    };
}

struct Config
{
	string name_out;
	string name_in;
	int name_out_in;
	int name_in_in;
	int info;

	int rgb_filter;
	string rgb_name;
	int rgb_name_in;
	int rgb_val;
	int rgb_val_in;

	int square;
	int sq_lu[2];
	int sq_lu_in;
	int sq_side;
	int sq_side_in;
	int sq_thickness;
	int sq_thickness_in;
	Rgb sq_color;
	int sq_color_in;
	int sq_fill;
	Rgb sq_fill_color;
	int sq_fill_color_in;

	int exchange;
	int ex_lu[2];
	int ex_lu_in;
	int ex_rd[2];
	int ex_rd_in;
	string ex_type;
	int ex_type_in;

	int frequent;
	Rgb freq_color;
	int freq_color_in;
    
	int outside;
	Rgb outside_color;
	int outside_thickness;
};

#endif