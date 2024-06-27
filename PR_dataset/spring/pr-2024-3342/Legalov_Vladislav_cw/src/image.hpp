#pragma once
#include<iostream>

#pragma pack(push, 1)
struct rgb{
	uint8_t r, g, b;
	rgb();
	rgb(int, int, int);
	int toint();
};
#pragma pack(pop)


class Image{
public:
	uint32_t height, width;
	uint8_t pixelsize;
	uint8_t **bitmap;
	void setpixel(int, int, rgb &);
	rgb *getpixel(int, int);
	bool checkCoordinats(int, int);
	~Image();
};
