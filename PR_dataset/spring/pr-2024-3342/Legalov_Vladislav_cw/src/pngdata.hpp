#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<zlib.h>
#include "image.hpp"


const uint8_t SINATUREPNG[8] = {0x89, 0x50, 0x4E, 0x47 , 0x0D, 0x0A, 0x1A, 0x0A};
#define IHDR 1380206665
#define IEND 1145980233
#define IDAT 1413563465
#define PLTE 1163152464
#define IDATSIZE 8192


uint32_t reversebyte(uint32_t x);
void checkpointer(void*);

class dataPNG{
public:
	class Chunck{
	public:
		uint32_t length;
		uint32_t name;
		uint32_t crc;
		uint8_t *data;
		Chunck();
		Chunck(uint32_t, uint32_t, uint8_t*);
		int setFromfile(FILE *);
		void writeInFile(FILE *);
		uint32_t calcCRC();
	};
	std::vector<Chunck> chuncks;
	uint32_t width, height;
	uint8_t depth, colortype;
	uint8_t interlace, pixelsize;
	uint8_t *palette;
	uint32_t palettesize;
	int readPNG(FILE *);
	Image* decodImage();
	int updateData(Image &);
	int writePNG(FILE *);
	void printdata();
	~dataPNG();
private:
	uint64_t sizedata();
	int uncompressdata(uint8_t*&, uint64_t&);
	int compressdata(uint8_t*&, uint64_t&);
	uint8_t** fillimage(uint8_t*, uint64_t);
	void recon(uint8_t **, uint8_t, uint64_t, uint64_t);
	uint8_t paethPredictor(int, int, int);
	void fillFromPalette(uint8_t **&);
};




