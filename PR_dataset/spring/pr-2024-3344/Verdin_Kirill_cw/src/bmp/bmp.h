#pragma once
#include <string>
#include <vector>
#include <string>
#include <iostream>

#pragma pack(push, 1)
struct BitMapFileHeader
{
	uint16_t signature;
	uint32_t filesize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t pixelArrOffset;
};

struct BitmapInfoHeader
{
	uint32_t header_size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitsPerPixel;
	uint32_t compression;
	uint32_t image_size;
	uint32_t x_pixels_per_meter;
	uint32_t y_pixels_per_meter;
	uint32_t colors_in_color_table;
	uint32_t important_color_count;
};

struct RGB
{
	uint8_t b;
	uint8_t g;
	uint8_t r;

	bool operator==(RGB other)
	{
		return this->b == other.b && this->g == other.g && this->r == other.r;
	}
	bool operator!=(RGB other)
	{
		return !(*this==other);
	}
};

struct Coordinates
{
	int x0;
	int y0;
	int x1;
	int y1;
};

struct Circle
{
	int x0;
	int y0;
	int r;
};

#pragma pack(pop)

class BMP
{
public:
	BMP();
	BMP(const char *input_path);

	void read(const char *input_path);
	void write(const char *output_path);
	void print_info_of_pixels();
	void print_file_header();
	void print_info_header();

	void rgbfilter(std::string component_name, uint8_t component_value);

	void draw_circle(Circle c, RGB color, int thickness);
	void draw_circle(Circle c, RGB color, int thickness, RGB fill_color);
	void draw_line(Coordinates coordinates, int thickness, RGB color);
	void draw_circle_line(Circle c, RGB color);

	void split(int number_x, int number_y, int thickness, RGB color);

	void change_pixels_of_field(RGB color, Coordinates coordinates);
	
	void filled_rects(RGB color, int thickness, RGB border_color);

	void rhombus(RGB color);

protected:
	BitmapInfoHeader info_header;
	BitMapFileHeader file_header;
	std::vector<std::vector<RGB>> pixels;
	int padding_size;

	Coordinates *check_rect(int x0, int y0, RGB color);
	bool check_border_of_rect(Coordinates coordinates, RGB color);
	bool check_line(int x0, int x1, int y, RGB color);
	bool check_border(Coordinates coordinates, RGB color);

	void read_headers(std::ifstream &bmp_file);
	void read_pixels(std::ifstream &bmp_file);

	void write_headers(std::ofstream &out_file);
	void write_pixels(std::ofstream &out_file);
	void set_color_of_pixel(RGB color, int x, int y);
	void set_component_value_of_pixel(std::string component_name, uint8_t component_value, RGB *pixel);
	void fill_circle(Circle c, RGB color);
	std::vector<int> coordinates_split(int num, int len_axis);
	std::vector<std::vector<int>> free_border_data(RGB color);
};