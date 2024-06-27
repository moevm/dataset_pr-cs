#include "bmp_image_class.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(unsigned char b, unsigned char g, unsigned char r) : b(b), g(g), r(r) {}

bool Color::operator==(const Color &other) {
  return (b == other.b && g == other.g && r == other.r);
}

BmpImage::BmpImage(const char *path) {
  read(path);
}

BmpImage::BmpImage(int width, int height, Color color) {
  // Set information about file
  file_header_.id[0] = 'B';
  file_header_.id[1] = 'M';
  const int
      kPaddingAmount = (k_image_memory_block - (info_header_.width * k_color_size % k_image_memory_block)) % k_image_memory_block;
  file_header_.file_size = k_file_header_size + k_info_header_size + info_header_.width * info_header_.height * 3
      + kPaddingAmount * info_header_.height;
  file_header_.pixel_offset = k_file_header_size + k_info_header_size;

  info_header_.header_size = k_info_header_size;
  info_header_.planes = 1;
  info_header_.bits_per_pixel = 24;
  info_header_.width = width;
  info_header_.height = height;

  colors_.resize(height, std::vector<Color>(width, color));
}

Color BmpImage::get_color(int x, int y) const {
  if (x < 0 || y < 0 || x >= get_width() || y >= get_height())
    throw BmpImageError(bmp_image_errors::k_error_get_pixel, x, y);
  return colors_[y][x];
}

int BmpImage::get_width() const {
  return info_header_.width;
}

int BmpImage::get_height() const {
  return info_header_.height;
}

std::vector<std::vector<Color>> BmpImage::get_colors() const {
  return colors_;
}

void BmpImage::set_color(int x, int y, const Color &color) {
  if (x < 0 || y < 0 || x >= get_width() || y >= get_height()) return;
  colors_[y][x].b = color.b;
  colors_[y][x].g = color.g;
  colors_[y][x].r = color.r;
}

void BmpImage::set_colors(std::vector<std::vector<Color>> newColors) {
  colors_ = newColors;
}

void BmpImage::read(const char *path) {
  std::ifstream file;
  file.exceptions(std::ifstream::badbit | std::ifstream::failbit); // ifstream exceptions turn on
  file.open(path, std::ios::in | std::ios::binary);

  file.read(reinterpret_cast<char *>(&file_header_), k_file_header_size);

  if (file_header_.id[0] != 'B' && file_header_.id[1] != 'M')
    throw BmpImageError(bmp_image_errors::k_error_not_bmp_image);

  file.read(reinterpret_cast<char *>(&info_header_), file_header_.pixel_offset - k_file_header_size);

  if (info_header_.planes != 1)
    throw BmpImageError(bmp_image_errors::k_error_planes);
  else if (info_header_.compression)
    throw BmpImageError(bmp_image_errors::k_error_comp);
  else if (info_header_.bits_per_pixel != 24)
    throw BmpImageError(bmp_image_errors::k_error_bits);

  colors_.resize(info_header_.height, std::vector<Color>(info_header_.width));
  const int
      padding_amount = (k_image_memory_block - (info_header_.width * k_color_size % k_image_memory_block)) % k_image_memory_block;

  for (int y = info_header_.height - 1; y >= 0; y--) { // inversion of BMP
    for (size_t x = 0; x < info_header_.width; x++) {
      Color color;
      file.read(reinterpret_cast<char *>(&color), k_color_size);
      colors_[y][x].b = color.b;
      colors_[y][x].g = color.g;
      colors_[y][x].r = color.r;
    }
    file.ignore(padding_amount);
  }
  file.close();
}

void BmpImage::export_image(const char *path) {
  std::ofstream file;
  file.exceptions(std::ofstream::badbit | std::ofstream::failbit);

  file.open(path, std::ios::out | std::ios::binary);

  unsigned char padding_color[3] = {0, 0, 0};
  const int
      padding_amount = (k_image_memory_block - (info_header_.width * k_color_size % k_image_memory_block)) % k_image_memory_block;

  file.write(reinterpret_cast<char *>(&file_header_), k_file_header_size);
  file.write(reinterpret_cast<char *>(&info_header_), file_header_.pixel_offset - k_file_header_size);

  for (int y = info_header_.height - 1; y >= 0; y--) { // inversion of BMP
    for (int x = 0; x < info_header_.width; x++) {
      Color current_color = get_color(x, y);
      file.write(reinterpret_cast<char *>(&current_color), k_color_size);
    }
    file.write(reinterpret_cast<char *>(padding_color), padding_amount);
  }

  file.close();
}

void BmpImage::print_info() const {
  printf("----HEADER (%lu)----\n", sizeof(file_header_));
  printf("id: %c%c\n", file_header_.id[0], file_header_.id[1]);
  printf("filesize: %d\n", file_header_.file_size);
  printf("unused: %c%c%c%c\n",
         file_header_.unused[0],
         file_header_.unused[1],
         file_header_.unused[2],
         file_header_.unused[3]);
  printf("pixelOffset: %d\n", file_header_.pixel_offset);

  printf("----INFO (%lu)----\n", sizeof(info_header_));
  printf("header size: %d\n", info_header_.header_size);
  printf("width: %d\n", info_header_.width);
  printf("height: %d\n", info_header_.height);
  printf("planes: %d\n", info_header_.planes);
  printf("bitsPerPixel: %d\n", info_header_.bits_per_pixel);
  printf("compression: %d\n", info_header_.compression);
  printf("compressionSize: %d\n", info_header_.compression_size);
  printf("xPixelsPerMeter: %d\n", info_header_.x_pixels_per_meter);
  printf("yPixelsPerMeter: %d\n", info_header_.y_pixels_per_meter);
  printf("totalColors: %d\n", info_header_.total_colors);
  printf("importantColors: %d\n", info_header_.important_colors);
}

