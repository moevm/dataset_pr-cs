#include "image.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cstdint>
#include <ios>
#include <new>
#include <png.h>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <system_error>

#define CW_HEADER_CHECK_LEN 8

void Image::init()
{
	memset(this, 0, sizeof(Image));
}

void Image::deinit()
{
	if (this->rows != nullptr) {
		for (uint32_t i = 0; i < this->height; i++) {
			if (this->rows[i] != nullptr)
				free(this->rows[i]);
		}
		free(this->rows);
	}

    if (png_info != nullptr)
        png_destroy_info_struct(this->png_struct, &this->png_info);

	if (png_endinfo != nullptr)
		png_destroy_info_struct(this->png_struct, &this->png_endinfo);

    if (png_struct != nullptr)
        png_destroy_read_struct(&this->png_struct, nullptr, nullptr);
}

void Image::reset()
{
	this->deinit();
	this->init();
}

Image::Image() 
{
	this->init();
}

Image::~Image()
{
	this->deinit();
}

class CFILE {
private:
	FILE *fp;
public:
	CFILE() : fp(nullptr) {}
	CFILE(FILE *fp) : fp(fp) {}

	~CFILE()
	{
		if (fp != nullptr)
			fclose(fp);
	}

	operator FILE*() { return fp; }
	inline bool is_open() { return fp != nullptr; }
};

class CWriteStruct {
private:
	png_structp png_ptr;
public:
	CWriteStruct() : png_ptr(nullptr) {}
	CWriteStruct(png_structp png_ptr) : png_ptr(png_ptr) {}
	
	~CWriteStruct()
	{
		if (png_ptr != nullptr)
			png_destroy_write_struct(&png_ptr, nullptr);
	}

	operator png_structp() { return png_ptr; }
};

void Image::load(const char *const filename)
{	
	int bits_per_pixel;
	unsigned char header[CW_HEADER_CHECK_LEN];
	
	if (this->rows != nullptr)
		this->reset();

    CFILE fp = fopen(filename, "rb");
    if (!fp.is_open()) {
        this->reset();
		throw std::runtime_error(std::string(std::strerror(errno)) + " (" + filename + ")");
	}

	fread(header, 1, CW_HEADER_CHECK_LEN, fp);
	if (png_sig_cmp(header, 0, 8) != 0) {
        this->reset();
		throw std::logic_error("not a png file");
	}

	this->png_struct = png_create_read_struct(
		PNG_LIBPNG_VER_STRING,
		(png_voidp)this,
        NULL,
		NULL
	);
    if (this->png_struct == nullptr) {
        this->reset();
		throw std::logic_error("png_create_read_struct failed");
    }

    this->png_info = png_create_info_struct(this->png_struct);
    if (this->png_info == NULL) {
        this->reset();
		throw std::logic_error("png_create_info_struct failed");
    }

	png_init_io(this->png_struct, fp);
	png_set_sig_bytes(this->png_struct, CW_HEADER_CHECK_LEN);

    png_read_info(this->png_struct, this->png_info);
	png_get_IHDR(
		this->png_struct, this->png_info,
		&this->width, &this->height,
		&this->bit_depth, &this->color_type,
		nullptr, nullptr, nullptr
	);

	this->n_channels = png_get_channels(this->png_struct, this->png_info);

    bits_per_pixel = this->bit_depth * this->n_channels;
	this->rows = (uint8_t**)malloc(sizeof(uint8_t*) * this->height);

    if (this->rows == nullptr) {
		this->reset();
		throw std::bad_alloc();
    }

	memset(this->rows, 0, sizeof(uint8_t*) * this->height);

	for (int i = 0; i < this->height; i++) {
		this->rows[i] = (uint8_t*)malloc((this->width * bits_per_pixel + 7) / 8);

        if (this->rows[i] == nullptr) {
            this->reset();
			throw std::bad_alloc();
        }
	}

    png_read_image(this->png_struct, this->rows);
	png_read_end(this->png_struct, this->png_endinfo);
}

void Image::save(const char *const filename)
{
	CFILE fp = fopen(filename, "wb");
	if (fp == nullptr)
		throw std::runtime_error(std::string(std::strerror(errno)) + " (" + filename + ")");

	CWriteStruct png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png == nullptr)
		throw std::runtime_error("png_create_write_struct failed");

	if (setjmp(png_jmpbuf(png)))
		throw std::runtime_error("internal libpng error");

	png_init_io(png, fp);

	png_color_8p sig_bit;
    if (png_get_sBIT(png, this->png_info, &sig_bit))
        png_set_shift(png, sig_bit);

	png_write_info(png, this->png_info);
	png_write_image(png, this->rows);
	png_write_end(png, NULL);
}

void *Image::getPixelAddr(vec2i coord)
{
	if (coord.x < 0 || coord.y < 0 || coord.x >= width || coord.y >= height)
		return nullptr;

	int row_offset = bit_depth * n_channels / 8 * coord.x;
	return rows[coord.y] + row_offset;
}

void Image::setPixel(vec2i coord, rgba32 color)
{
	void *addr = getPixelAddr(coord);
	if (addr == NULL)
		return;

	memcpy(addr, &color, bit_depth * n_channels / 8);
}

rgba32 Image::getPixel(vec2i coord)
{
	void *addr = getPixelAddr(coord);
	if (addr == NULL)
		return rgba32(0x00000000);

	rgba32 color(0xFFFFFFFF);
	memcpy(&color, addr, bit_depth * n_channels / 8);
	return color;
}

void Image::resize(uint32_t width, uint32_t height)
{
	if (height < this->height) {
		for (uint32_t i = height; i < this->height; i++)
			free(this->rows[i]);
	}

	uint8_t **new_rows = (uint8_t**)realloc(this->rows, height * sizeof(uint8_t*));
    if (new_rows == nullptr)
        throw std::bad_alloc();
	this->rows = new_rows;

	for (uint32_t i = 0; i < std::min(this->height, height); i++) {
		uint8_t *new_row = (uint8_t*)realloc(
			this->rows[i],
			width * sizeof(uint8_t) * n_channels * bit_depth / 8
		);

		if (new_row == nullptr)
			throw std::bad_alloc();
		this->rows[i] = new_row;
	}

	if (this->height < height)
		memset(this->rows + this->height, 0, (height - this->height) * sizeof(uint8_t*));

	for (uint32_t i = this->height; i < height; i++) {
		this->rows[i] = (uint8_t*)malloc(
			width * sizeof(uint8_t) * n_channels * bit_depth / 8
		);

        if (this->rows[i] == nullptr)
			throw std::bad_alloc();
	}

	this->width  = width;
	this->height = height;

	png_set_IHDR(
		this->png_struct,
		this->png_info,
		this->width, this->height,
		this->bit_depth,
		this->color_type,
		png_get_interlace_type(this->png_struct, this->png_info),
		png_get_compression_type(this->png_struct, this->png_info),
		png_get_filter_type(this->png_struct, this->png_info)
	);
}
