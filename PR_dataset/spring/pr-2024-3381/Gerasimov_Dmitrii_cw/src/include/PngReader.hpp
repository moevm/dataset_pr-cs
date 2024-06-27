#pragma once

#include "Color.hpp"
#include "ImageReader.hpp"
#include "Vector2i.hpp"
#include <png.h>
#include <stdexcept>
#include <string>

class PngReader : public ImageReader
{
private:
    png_byte pngType;
    png_byte color_type;
    png_byte bit_depth;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    Color **image;

    void read_png(std::string path);
    void write_png(std::string path);

public:
    PngReader(std::string input = "ornament_image.png",
              std::string output = "out.png");
    Vector2i get_size() const override;
    void load(std::string path) override;
    void save(std::string path) override;
    void load() override;
    void save() override;
    void put_pixel(Vector2i coord, Color col) override;
    Color get_pixel(Vector2i coord, Color def = Color{}) const override;
    uint8_t get_depth() const;

    ~PngReader() override;
};