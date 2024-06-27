/**
 * @file bmp.cpp
 * @brief Реализация методов класса BMP для работы с изображениями в формате
 * BMP.
 */

#include "bmp.hpp"
#include "logger.hpp"
#include "messages.hpp"

BMP::BMP(const std::string& fileName)
: header()
, pixel_data()
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) { Logger::exit(ERR_FILE_NOT_FOUND, open_bmp_error + fileName); }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (!validate_header())
    {
        file.close();
        Logger::exit(ERR_INCORRECT_FILE_FORMAT, invalid_header_error + fileName);
    }

    const uint32_t bytesPerPixel = header.bitsPerPixel / 8;
    const uint32_t rowSize = ((header.width * bytesPerPixel + 3) / 4) * 4;
    const uint32_t imageSize = rowSize * header.height;

    pixel_data.resize(imageSize);

    file.seekg(header.dataOffset, std::ios_base::beg);

    file.read(reinterpret_cast<char*>(pixel_data.data()), imageSize);

    file.close();
}

bool BMP::validate_header() const
{
    if (std::strncmp(header.signature, "BM", 2) != 0)
    {
        Logger::exit(ERR_INCORRECT_FILE_FORMAT, invalid_signature_error);
        return false;
    }

    if (header.width <= 0 || header.height <= 0)
    {
        Logger::exit(ERR_INCORRECT_FILE_FORMAT, invalid_dimensions_error);
        return false;
    }

    if (header.bitsPerPixel != 24) { Logger::warn(invalid_bpp_warning); }

    if (header.compression != 0)
    {
        Logger::exit(ERR_INCORRECT_FILE_FORMAT, unsupported_compression_error);
        return false;
    }

    return true;
}

bool BMP::is_valid() const { return !pixel_data.empty(); }

RGB BMP::get_color(int x, int y) const
{
    if (x < 0 || x >= header.width || y < 0 || y >= header.height) return RGB();

    const uint32_t bytesPerPixel = header.bitsPerPixel / 8;
    const uint32_t bytesPerRow = (bytesPerPixel * header.width + 3) & ~3;
    const uint32_t index = ((header.height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);

    return RGB(pixel_data[index + 2], pixel_data[index + 1], pixel_data[index]);
}

void BMP::set_color(int x, int y, const RGB& newColor)
{
    if (x < 0 || x >= header.width || y < 0 || y >= header.height) return;

    const uint32_t bytesPerPixel = header.bitsPerPixel / 8;
    const uint32_t bytesPerRow = (bytesPerPixel * header.width + 3) & ~3;
    const uint32_t index = ((header.height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);

    pixel_data[index] = newColor.blue;
    pixel_data[index + 1] = newColor.green;
    pixel_data[index + 2] = newColor.red;
}
void BMP::initialize(int32_t width, int32_t height)
{
    // Clear header
    std::memset(&header, 0, sizeof(header));
    std::strcpy(header.signature, "BM");

    // Calculate bytes per pixel and row size
    const uint32_t bytesPerPixel = 3; // 24 bits per pixel
    const uint32_t rowSize = ((width * bytesPerPixel + 3) / 4) * 4; // Align row size to 4 bytes
    const uint32_t imageSize = rowSize * height;

    // Fill BMP header
    header.fileSize = sizeof(BMPHeader) + imageSize;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = 40; // BITMAPINFOHEADER size
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bitsPerPixel = 24; // 24 bits per pixel
    header.compression = 0; // No compression
    header.imageSize = imageSize;
    header.xPixelsPerMeter = 2835; // 72 DPI
    header.yPixelsPerMeter = 2835; // 72 DPI
    header.colorsUsed = 0; // Use all colors
    header.colorsImportant = 0; // All colors are important

    // Allocate pixel data and initialize to black
    pixel_data.assign(imageSize, 0);
}

void BMP::color_replace(const RGB& old_color, const RGB& new_color)
{
    for (int y = 0; y < header.height; y++)
    {
        for (int x = 0; x < header.width; x++)
        {
            RGB current_color = get_color(x, y);
            if (current_color.red == old_color.red && current_color.green == old_color.green && current_color.blue == old_color.blue) { set_color(x, y, new_color); }
        }
    }
}

void BMP::mirror(const std::string& axis, const Coordinate& left_up, const Coordinate& right_down)
{
    int width = right_down.x - left_up.x;
    int height = right_down.y - left_up.y;

    if (axis != "x" && axis != "y") { Logger::exit(ERR_INVALID_ARGUMENT, invalid_mirror_axis_error); }

    if (axis == "x")
    {
        for (int y = left_up.y; y <= right_down.y; ++y)
        {
            for (int x = left_up.x; x < left_up.x + width / 2; ++x)
            {
                int mirroredX = right_down.x - (x - left_up.x);
                RGB tempColor = get_color(x, y);
                set_color(x, y, get_color(mirroredX, y));
                set_color(mirroredX, y, tempColor);
            }
        }
    }
    else if (axis == "y")
    {
        for (int y = left_up.y; y < left_up.y + height / 2; ++y)
        {
            for (int x = left_up.x; x <= right_down.x; ++x)
            {
                int mirroredY = right_down.y - (y - left_up.y);
                RGB tempColor = get_color(x, y);
                set_color(x, y, get_color(x, mirroredY));
                set_color(x, mirroredY, tempColor);
            }
        }
    }
}


void BMP::split(int number_x, int number_y, int thickness, const RGB& color)
{
    if ((number_x <= 0 || number_x > header.width) || (number_y <= 0 || number_y > header.height) || (thickness <= 0 || thickness > header.width)) { Logger::exit(ERR_INVALID_ARGUMENT, invalid_split_parameters_error); }

    int gap;

    for (int i = 1; i < number_y; i++)
    {
        gap = header.height / number_y;
        for (int x = 0; x < header.width; x++)
        {
            for (int y = 0; y < thickness; y++) { set_color(x, i * gap + y, color); }
        }
    }

    for (int i = 1; i < number_x; i++)
    {
        gap = header.width / number_x;
        for (int x = 0; x < thickness; x++)
        {
            for (int y = 0; y < header.height; y++) { set_color(i * gap + x, y, color); }
        }
    }
}


void BMP::copy(const Coordinate& src_left_up, const Coordinate& src_right_down, const Coordinate& dest_left_up)
{
    int src_x_min = std::min(src_left_up.x, src_right_down.x);
    int src_x_max = std::max(src_left_up.x, src_right_down.x);
    int src_y_min = std::min(src_left_up.y, src_right_down.y);
    int src_y_max = std::max(src_left_up.y, src_right_down.y);

    for (int x = src_x_min; x <= src_x_max; x++)
    {
        for (int y = src_y_min; y <= src_y_max; y++) { set_color(dest_left_up.x + (x - src_x_min), dest_left_up.y + (y - src_y_min), get_color(x, y)); }
    }
}
void BMP::save(const std::string& fileName)
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        Logger::exit(ERR_FILE_WRITE_ERROR, failed_create_output_file + fileName);
        return;
    }

    const uint32_t bytesPerPixel = header.bitsPerPixel / 8;
    const uint32_t rowSize = ((header.width * bytesPerPixel + 3) / 4) * 4;

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.seekp(header.dataOffset, std::ios::beg);
    for (int y = 0; y < header.height; ++y) { file.write(reinterpret_cast<const char*>(pixel_data.data() + y * rowSize), rowSize); }

    file.close();
}

void BMP::get_info() const
{
    Logger::log(signature_message + std::string(header.signature, 2));
    Logger::log(file_size_message + std::to_string(header.fileSize) + " bytes");
    Logger::log(data_offset_message + std::to_string(header.dataOffset) + " bytes");
    Logger::log(header_size_message + std::to_string(header.headerSize) + " bytes");
    Logger::log(image_dimensions_message + std::to_string(header.width) + "x" + std::to_string(header.height));
    Logger::log(bits_per_pixel_message + std::to_string(header.bitsPerPixel));
    Logger::log(compression_message + std::to_string(header.compression));
    Logger::log(image_size_message + std::to_string(header.imageSize) + " bytes");
    Logger::log(pixels_per_meter_x_message + std::to_string(header.xPixelsPerMeter));
    Logger::log(pixels_per_meter_y_message + std::to_string(header.yPixelsPerMeter));
    Logger::log(colors_used_message + std::to_string(header.colorsUsed));
    Logger::log(important_colors_message + std::to_string(header.colorsImportant));
}
