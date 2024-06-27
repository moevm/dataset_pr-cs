#include "bmp.h"
#include <fstream>
#include <iostream>
#include <cmath>

std::ostream &operator<<(std::ostream &o, const RGB& color)
{
	o << unsigned(color.r) << '\t' << unsigned(color.g) << '\t' << unsigned(color.b) << '\n';
	return o;
}

BMP::BMP()
{

}

BMP::BMP(const char *input_path)
{
	read(input_path);
}

void BMP::read(const char *input_path)
{
	std::ifstream bmp_file{input_path, std::ios_base::binary};

	if (!bmp_file)
	{
		std ::cout << "the file could not be opened or the file path was specified incorrectly\n";
		exit(44);
	}
	read_headers(bmp_file);
	if (file_header.signature != 0x4D42 || info_header.bitsPerPixel != 24 || info_header.compression != 0)
	{
		std::cerr << "Wrong file\n";
		exit(45);
	}
	read_pixels(bmp_file);
	bmp_file.close();
}

void BMP::read_headers(std::ifstream &bmp_file)
{
	bmp_file.read((char *)&file_header, sizeof(BitMapFileHeader));
	bmp_file.read((char *)&info_header, sizeof(BitmapInfoHeader));
}

void BMP::read_pixels(std::ifstream &bmp_file)
{
	padding_size = (info_header.width * sizeof(RGB)) % 4;
	if (padding_size)
		padding_size = 4 - padding_size;
	bmp_file.seekg(file_header.pixelArrOffset, bmp_file.beg);
	unsigned int H = info_header.height;
	unsigned int W = info_header.width;
	std::vector<std::vector<RGB>> pixels_data(info_header.height, std::vector<RGB>(info_header.width));
	for (size_t i = 0; i < H; i++)
	{	
		bmp_file.read((char*)(pixels_data[H - i - 1].data()), W * sizeof(RGB) + padding_size);
	}
	pixels = pixels_data;
}

void BMP::write(const char *output_path)
{
	std::ofstream output_file{output_path, std::ios_base::binary};

	write_headers(output_file);
	write_pixels(output_file);
	output_file.close();
}

void BMP::write_headers(std::ofstream &out_file)
{
	out_file.write((char *)&file_header, sizeof(BitMapFileHeader));
	out_file.write((char *)&info_header, sizeof(BitmapInfoHeader));
}

void BMP::write_pixels(std::ofstream &out_file)
{
	unsigned int H = info_header.height;
	unsigned int W = info_header.width;
	for (size_t i = 0; i < H; i++)
	{
		out_file.write((char *)pixels[H - i - 1].data(), (W * sizeof(RGB)) + padding_size);
	}
}

void BMP::rgbfilter(std::string component_name, uint8_t component_value)
{
	for (size_t y = 0; y < info_header.height; y++)
		for (size_t x = 0; x < info_header.width; x++)
			set_component_value_of_pixel(component_name, component_value, &pixels[y][x]);
}

void BMP::set_component_value_of_pixel(std::string component_name, uint8_t component_value, RGB *pixel)
{
	if (component_name == "red")
		pixel->r = component_value;
	else if (component_name == "green")
		pixel->g = component_value;
	else if (component_name == "blue")
		pixel->b = component_value;
}

void BMP::draw_circle(Circle c, RGB color, int thickness)
{
	if (thickness == 1)
	{
		draw_circle_line(c, color);
		return;
	}
	int x = 0;
	int y = c.r;
	int d = 1 - 2 * c.r;
	int error = 0;
	int radius_of_fill_circle = thickness % 2 ? thickness / 2 : (thickness + 1) / 2;
	while (y >= x)
	{
		fill_circle({c.x0 + x, c.y0 + y, radius_of_fill_circle}, color);
		fill_circle({c.x0 - x, c.y0 + y, radius_of_fill_circle}, color);
		fill_circle({c.x0 + x, c.y0 - y, radius_of_fill_circle}, color);
		fill_circle({c.x0 - x, c.y0 - y, radius_of_fill_circle}, color);
		fill_circle({c.x0 + y, c.y0 + x, radius_of_fill_circle}, color);
		fill_circle({c.x0 - y, c.y0 + x, radius_of_fill_circle}, color);
		fill_circle({c.x0 + y, c.y0 - x, radius_of_fill_circle}, color);
		fill_circle({c.x0 - y, c.y0 - x, radius_of_fill_circle}, color);
		error = 2 * (d + y) - 1;

		if (d < 0 && error <= 0)
			d += 2 * ++x + 1;
		else if (d > 0 && error >= 0)
			d -= 2 * --y + 1;
		else
			d += 2 * (++x - --y);
	}
}

void BMP::draw_circle(Circle c, RGB color, int thickness, RGB fill_color)
{
	fill_circle(c, fill_color);
	draw_circle(c, color, thickness);
}

void BMP::draw_line(Coordinates coordinates, int thickness, RGB color)
{
	int dx = abs(coordinates.x1 - coordinates.x0);
	int dy = abs(coordinates.y1 - coordinates.y0);
	int sx = coordinates.x0 < coordinates.x1 ? 1 : -1;
	int sy = coordinates.y0 < coordinates.y1 ? 1 : -1;
	int err = dx - dy;
	int e2;
	for (int i = thickness / 2; i > 0; i--)
	{
		fill_circle({coordinates.x1, coordinates.y1, i}, color);
	}
	set_color_of_pixel(color, coordinates.x1, coordinates.y1);
	while (coordinates.x0 != coordinates.x1 || coordinates.y0 != coordinates.y1)
	{
		for (int i = thickness / 2; i > 0; i--)
		{
			fill_circle({coordinates.x0, coordinates.y0, i}, color);
		}
		set_color_of_pixel(color, coordinates.x0, coordinates.y0);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			coordinates.x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			coordinates.y0 += sy;
		}
	}
}

void BMP::split(int number_x, int number_y, int thickness, RGB color)
{	
	if (number_x*thickness >= info_header.width || number_y*thickness >=info_header.height)
	{
		change_pixels_of_field(color, {0, 0, int(info_header.width), int(info_header.height)});
		return;
	}
	
	std::vector<int> coordinates_x = coordinates_split(number_x, info_header.width);
	std::vector<int> coordinates_y = coordinates_split(number_y, info_header.height);
	for (auto v : coordinates_x)
		draw_line({v, 0, v, int(info_header.height) - 1}, thickness, color);
	for (auto v : coordinates_y)
		draw_line({0, v, int(info_header.width) - 1, v}, thickness, color);
}

std::vector<int> BMP::coordinates_split(int num, int len_axis)
{
	std::vector<int> ans;
	for (size_t i = 1; i < num; i++)
	{
		ans.push_back(round(float(len_axis - 1) * i / num));
	}
	return ans;
}

void BMP::change_pixels_of_field(RGB color, Coordinates coordinates)
{
	for (size_t y = coordinates.y0; y < coordinates.y1; y++)
		for (size_t x = coordinates.x0; x < coordinates.x1; x++)
		{
			set_color_of_pixel(color, x, y);
		}
}

void BMP::filled_rects(RGB color, int thickness, RGB border_color)
{
	std::vector<std::vector<int>> free_border_data_array = free_border_data(color);
	std::vector<Coordinates *> coords;
	for (int y = 0; y < info_header.height; y++)
	{
		for (int x = 0; x < info_header.width; x++)
		{
			if (pixels[y][x] != color)
				continue;
			Coordinates *c = new Coordinates;
			if (free_border_data_array[y][x] == 8)
			{
				c->x0 = x;
				c->x1 = x;
				c->y0 = y;
				c->y1 = y;
				coords.push_back(c);
				continue;
			}
			if (free_border_data_array[y][x] == 7)
			{
				bool flag = false;
				for (int x1 = x + 1; x1 < info_header.width; x1++)
				{
					if (free_border_data_array[y][x1] != 6)
					{
						if (free_border_data_array[y][x1] != 7)
						{
							break;
						}
						c->x1 = x1;
						c->y0 = y;
						c->y1 = y;
						c->x0 = x;
						flag = true;
					}
				}
				if (!flag)
					for (int y1 = y + 1; y1 < info_header.height; y1++)
					{
						if (free_border_data_array[y1][x] != 6)
						{
							if (free_border_data_array[y1][x] != 7)
							{
								break;
							}
							c->x1 = x;
							c->y0 = y;
							c->y1 = y1;
							c->x0 = x;
							flag = true;
						}
					}
				if (flag)
					coords.push_back(c);
				else
				{
					delete c;
					continue;
				}
			}
			else if (free_border_data_array[y][x] == 5)
			{
				bool flag = true;
				for (int x1 = x + 1; x1 < info_header.width; x1++)
				{
					if (free_border_data_array[y][x1] != 3)
					{
						if (free_border_data_array[y][x1] == 5)
						{
							c->x1 = x1;
							c->x0 = x;
						}
						else
						{
							flag = false;
						}
						break;
					}
				}
				for (int y1 = y + 1; y1 < info_header.height; y1++)
				{
					if (free_border_data_array[y1][x] != 3)
					{
						if (free_border_data_array[y1][x] == 5)
						{
							c->y1 = y1;
							c->y0 = y;
						}
						else
						{
							flag = false;
						}
						break;
					}
				}
				if (c->y0 + 1 > c->y1 || c->x0 + 1 > c->x1)
					flag = false;
				if (!flag)
					continue;
				for (int x1 = c->x0 + 1; x1 <= c->x1; x1++)
				{
					if (free_border_data_array[c->y1][x1] != 3)
					{
						if (free_border_data_array[c->y1][x1] != 5)
							flag = false;
					}
				}
				for (int y1 = c->y0 + 1; y1 <= c->y1; y1++)
				{
					if (free_border_data_array[y1][c->x1] != 3)
					{
						if (free_border_data_array[y1][c->x1] != 5)
							flag = false;
					}
				}
				if (!flag)
					continue;
				for (int y1 = c->y0 + 1; y1 < c->y1; y1++)
				{
					for (int x1 = c->x0 + 1; x1 < c->x1; x1++)
						if (free_border_data_array[y1][x1])
						{
							flag = false;
							break;
						}
					if (!flag)
						break;
				}
				if (flag)
					coords.push_back(c);
				else
					delete c;
				continue;
			}
		}
	}
	for (auto v : coords)
	{
		// std::cout << v->x0 << '\t' << v->y0 << '\t' << v->x1 << '\t' << v->y1 << '\n';
		draw_line({v->x0 - 1, v->y0 - 1, v->x1 + 1, v->y0 - 1}, thickness, border_color);
		draw_line({v->x0 - 1, v->y1 + 1, v->x1 + 1, v->y1 + 1}, thickness, border_color);
		draw_line({v->x0 - 1, v->y0 - 1, v->x0 - 1, v->y1 + 1}, thickness, border_color);
		draw_line({v->x1 + 1, v->y0 - 1, v->x1 + 1, v->y1 + 1}, thickness, border_color);
	}
}

void BMP::print_info_of_pixels()
{
	for (size_t y = 5; y < 10; y++)
	{
		for (size_t x = 0; x < info_header.width; x++)
		{
			std::cout << unsigned(pixels[y][x].r) << "\t" << unsigned(pixels[y][x].g) << "\t" << unsigned(pixels[y][x].b) << '\n';
		}
	}
}

void BMP::set_color_of_pixel(RGB color, int x, int y)
{
	if (x < 0 || x >= info_header.width || y < 0 || y >= info_header.height)
		return;
	if (color.r <= 255)
	{
		pixels[y][x].r = color.r;
	}
	if (color.b <= 255)
	{
		pixels[y][x].b = color.b;
	}
	if (color.g <= 255)
	{
		pixels[y][x].g = color.g;
	}
}

void BMP::draw_circle_line(Circle c, RGB color)
{
	int x = 0;
	int y = c.r;
	int d = 3 - 2 * y;
	while (y >= x)
	{
		set_color_of_pixel(color, c.x0 + x, c.y0 + y);
		set_color_of_pixel(color, c.x0 - x, c.y0 + y);
		set_color_of_pixel(color, c.x0 + x, c.y0 - y);
		set_color_of_pixel(color, c.x0 - x, c.y0 - y);
		set_color_of_pixel(color, c.x0 + y, c.y0 + x);
		set_color_of_pixel(color, c.x0 - y, c.y0 + x);
		set_color_of_pixel(color, c.x0 + y, c.y0 - x);
		set_color_of_pixel(color, c.x0 - y, c.y0 - x);
		x++;
		if (d < 0)
		{
			d += (4 * x) + 6;
		}
		else
		{
			d += 4 * (x - y) + 10;
			y--;
		}
	}
}

void BMP::fill_circle(Circle c, RGB color)
{
	draw_circle_line(c, color);

	for (int y = -c.r; y <= c.r; y++)
	{
		if (y + c.y0 < 0 || y + c.y0 > info_header.height)
			continue;
		for (int x = -c.r; x <= c.r; x++)
		{
			if (x + c.x0 < 0 || x + c.x0 >= info_header.width)
				continue;
			if (x * x + y * y <= c.r * c.r)
				set_color_of_pixel(color, c.x0 + x, c.y0 + y);
		}
	}
}

std::vector<std::vector<int>> BMP::free_border_data(RGB color)
{
	std::vector<std::vector<int>> free_border_data_array(info_header.height, std::vector<int>(info_header.width, 0));
	for (int y = 0; y < info_header.height; y++)
	{
		for (int x = 0; x < info_header.width; x++)
		{
			if (pixels[y][x] == color)
			{
				if ((y + 1 == info_header.height || y - 1 < 0) && (x + 1 == info_header.width || x - 1 < 0))
					free_border_data_array[y][x] = 5;
				else if (y + 1 == info_header.height || y - 1 < 0 || x + 1 == info_header.width || x - 1 < 0)
					free_border_data_array[y][x] = 3;
				if (y + 1 < info_header.height && pixels[y + 1][x] != color)
					free_border_data_array[y][x] += 1;
				if (y - 1 >= 0 && pixels[y - 1][x] != color)
					free_border_data_array[y][x] += 1;
				if (x + 1 < info_header.width && pixels[y][x + 1] != color)
					free_border_data_array[y][x] += 1;
				if (x - 1 >= 0 && pixels[y][x - 1] != color)
					free_border_data_array[y][x] += 1;
				if (y + 1 < info_header.height && x + 1 < info_header.width && pixels[y + 1][x + 1] != color)
					free_border_data_array[y][x] += 1;
				if (y + 1 < info_header.height && x - 1 >= 0 && pixels[y + 1][x - 1] != color)
					free_border_data_array[y][x] += 1;
				if (y - 1 >= 0 && x + 1 < info_header.width && pixels[y - 1][x + 1] != color)
					free_border_data_array[y][x] += 1;
				if (y - 1 >= 0 && x - 1 >= 0 && pixels[y - 1][x - 1] != color)
					free_border_data_array[y][x] += 1;
			}
		}
	}
	return free_border_data_array;
}

void BMP::print_file_header()
{	
	using std::hex;
	using std::dec;
	std::cout << "\nFILE HEADER INFO\n";
    std::cout << "signature:    \t0x" << hex << file_header.signature << " (" << dec << file_header.signature << ")\n";
    std::cout << "filesize:    \t0x" << hex << file_header.filesize << " (" << dec << file_header.filesize << ")\n";
    std::cout << "reserved1:    \t0x" << hex << file_header.reserved1 << " (" << dec << file_header.reserved1 << ")\n";
    std::cout << "reserved2:    \t0x" << hex << file_header.reserved2 << " (" << dec << file_header.reserved2 << ")\n";
    std::cout << "pixelArrOffset:\t0x" << hex << file_header.pixelArrOffset << " (" << dec << file_header.pixelArrOffset << ")\n";
}

void BMP::print_info_header()
{	
	using std::hex;
	using std::dec;
	using std::cout;
	cout << "\nINFO HEADER\n";
    cout << "headerSize:   \t0x" << hex << info_header.header_size << " (" << dec << info_header.header_size << ")\n";
    cout << "width:        \t0x" << hex << info_header.width << " (" << dec << info_header.width << ")\n";
    cout << "height:       \t0x" << hex << info_header.height << " (" << dec << info_header.height << ")\n";
    cout << "planes:       \t0x" << hex << info_header.planes << " (" << dec << info_header.planes << ")\n";
    cout << "bitsPerPixel: \t0x" << hex << info_header.bitsPerPixel << " (" << dec << info_header.bitsPerPixel << ")\n";
    cout << "compression:  \t0x" << hex << info_header.compression << " (" << dec << info_header.compression << ")\n";
    cout << "imageSize:    \t0x" << hex << info_header.image_size << " (" << dec << info_header.image_size << ")\n";
    cout << "xPixelsPerMeter:\t0x" << hex << info_header.x_pixels_per_meter << " (" << dec << info_header.x_pixels_per_meter << ")\n";
    cout << "yPixelsPerMeter:\t0x" << hex << info_header.y_pixels_per_meter << " (" << dec << info_header.y_pixels_per_meter << ")\n";
    cout << "colorsInColorTable:\t0x" << hex << info_header.colors_in_color_table << " (" << dec << info_header.colors_in_color_table<< ")\n";
    cout << "importantColorCount:\t0x" << hex << info_header.important_color_count << " (" << dec << info_header.important_color_count << ")\n";
}

void BMP::rhombus(RGB color)
{
	int cy = info_header.height/2;
	int cx = info_header.width/2;
	Coordinates coords[4] = {{0, cy, cx, 0}, {cx, 0, int(info_header.width), cy}, {int(info_header.width), cy, cx, int(info_header.height)}, {cx, int(info_header.height), 0, cy}};
	draw_line(coords[0], 1, color);
	draw_line(coords[1], 1, color);
	draw_line(coords[2], 1, color);
	// draw_line(coords[3], 1, color);
	float coef[4] = {float(coords[0].y1-coords[0].y0)/(coords[0].x1-coords[0].x0), float(coords[1].y1-coords[1].y0)/(coords[1].x1-coords[1].x0), float(coords[2].y1-coords[2].y0)/(coords[2].x1-coords[2].x0), float(coords[3].y1-coords[3].y0)/(coords[3].x1-coords[3].x0)};
	float b[4] = {coords[0].y1 - coef[0]*coords[0].x1, coords[1].y1 - coef[1]*coords[1].x1, coords[2].y1 - coef[2]*coords[2].x1, coords[3].y1 - coef[3]*coords[3].x1};
	for (int y = 0; y<info_header.height; y++)
	{
		for (int x = 0; x<info_header.width; x++)
		{
			if(y>=x*coef[0]+b[0] && y>=x*coef[1]+b[1] && y<x*coef[2]+b[2] && y<x*coef[3]+b[3])
			{
				set_color_of_pixel(color, x, y);
			}
		}
	}
}