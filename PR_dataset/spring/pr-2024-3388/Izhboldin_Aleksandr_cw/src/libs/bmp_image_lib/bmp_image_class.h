#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "bmp_image_errors.h"

const int k_file_header_size = 14;
const int k_info_header_size = 40;
const int k_color_size = 3;
const int k_image_memory_block = 4;

// alignment in memory
#pragma pack(push, 1)
struct Color {
  unsigned char b, g, r;

  Color();

  Color(unsigned char b, unsigned char g, unsigned char r);

  ~Color() = default;

  bool operator ==(const Color &other);
};

struct BmpFileHeader { // size 14 bytes
  unsigned char id[2];
  int32_t file_size;
  unsigned char unused[4];
  int32_t pixel_offset;
  BmpFileHeader() = default;
  ~BmpFileHeader() = default;
};

struct BmpInfoHeader {
  //base
  int32_t header_size;
  int32_t width;
  int32_t height;
  int16_t planes;
  int16_t bits_per_pixel;
  // 3 ver
  int32_t compression;
  int32_t compression_size;
  int32_t x_pixels_per_meter;
  int32_t y_pixels_per_meter;
  int32_t total_colors;
  int32_t important_colors;
  // 4 ver
  int32_t red_mask;
  int32_t green_mask;
  int32_t blue_mask;
  int32_t alpha_mask;
  int32_t cs_type;
  unsigned char endpoints[36];
  int32_t gamma_red;
  int32_t gamma_green;
  int32_t gamma_blue;
  // 5 ver
  int32_t intent;
  int32_t profile_data;
  int32_t profile_size;
  int32_t reserved;

  BmpInfoHeader() = default;
  ~BmpInfoHeader() = default;
};
#pragma pack(pop)

class BmpImage {
 public:
  explicit BmpImage(const char *path);
  BmpImage(int width, int height, Color color = Color());
  ~BmpImage() = default;

  // Getters
  Color get_color(int x, int y) const;
  int get_width() const;
  int get_height() const;
  std::vector<std::vector<Color>> get_colors() const;

  // Setters
  void set_color(int x, int y, const Color &color);
  void set_colors(std::vector<std::vector<Color>> newColors);

  void export_image(const char *path);
  void print_info() const;

 protected:
 private:
  void read(const char *path);
  BmpFileHeader file_header_{};
  BmpInfoHeader info_header_{};
  std::vector<std::vector<Color>> colors_;
};
