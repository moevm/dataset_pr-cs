#include "../include/PngReader.hpp"

void PngReader::load(std::string path)
{
    this->inputFile = path;
    this->load();
}

void PngReader::load()
{
    read_png(this->inputFile);
    if (pngType != PNG_COLOR_TYPE_RGB)
    {
        throw std::runtime_error(
            "Wrong image Pixel type. Supported types: RGB.");
    }
}

void PngReader::save(std::string path)
{
    this->outputFile = path;
    this->save();
}

void PngReader::save()
{
    write_png(this->outputFile);
}

PngReader::PngReader(std::string input, std::string output)
    : ImageReader(input, output)
{
}

Vector2i PngReader::get_size() const
{
    return size;
}

void PngReader::put_pixel(Vector2i coord, Color col)
{
    if (!check(coord)) return;
    image[coord.y][coord.x] = col;
};

Color PngReader::get_pixel(Vector2i coord, Color def) const
{
    if (!check(coord)) return def;
    return image[coord.y][coord.x];
};

PngReader::~PngReader()
{
    for (size_t i = 0; i < size.y; i++)
    {
        delete[] image[i];
    }
    delete[] image;
}

uint8_t PngReader::get_depth() const
{
    return bit_depth;
}

void PngReader::read_png(std::string path)
{
    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp)
    {
        throw std::runtime_error("Cannot read file: " + path);
    }
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        throw std::runtime_error("Probably, " + path + " is not a png\n");
    }
    this->png_ptr =
        png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!this->png_ptr)
    {
        throw std::runtime_error("Error in png structure\n");
    }
    this->info_ptr = png_create_info_struct(this->png_ptr);
    if (!this->info_ptr)
    {
        throw std::runtime_error("Error in png info-structure\n");
    }
    if (setjmp(png_jmpbuf(this->png_ptr)))
    {
    }
    png_init_io(this->png_ptr, fp);
    png_set_sig_bytes(this->png_ptr, 8);
    png_read_info(this->png_ptr, this->info_ptr);
    this->size.x = png_get_image_width(this->png_ptr, this->info_ptr);
    this->size.y = png_get_image_height(this->png_ptr, this->info_ptr);
    this->color_type = png_get_color_type(this->png_ptr, this->info_ptr);
    this->bit_depth = png_get_bit_depth(this->png_ptr, this->info_ptr);
    this->number_of_passes = png_set_interlace_handling(this->png_ptr);
    png_read_update_info(this->png_ptr, this->info_ptr);
    this->pngType = png_get_color_type(png_ptr, info_ptr);
    this->image = new Color *[this->size.y];
    for (size_t i = 0; i < this->size.y; i++)
    {
        this->image[i] = new Color[this->size.x];
    }
    png_read_image(this->png_ptr, (png_bytepp)this->image);

    png_destroy_read_struct(&png_ptr, &info_ptr, &info_ptr);
    png_destroy_info_struct(png_ptr, &info_ptr);
}

void PngReader::write_png(std::string path)
{
    FILE *fp = fopen(path.c_str(), "wb");
    if (!fp)
    {
        throw std::runtime_error("Cannot read file: " + path);
    }
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        throw std::runtime_error("Cannot create png structure");
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        throw std::runtime_error("Cannot create png info-structure");
    }
    if (setjmp(png_jmpbuf(png_ptr)))
    {
    }
    png_init_io(png_ptr, fp);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        throw std::runtime_error("Error while header writing");
    }
    png_set_IHDR(png_ptr, info_ptr, size.x, size.y, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
    }
    png_write_image(png_ptr, (png_bytepp)image);
    if (setjmp(png_jmpbuf(png_ptr)))
    {
    }
    png_write_end(png_ptr, NULL);
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    png_destroy_info_struct(png_ptr, &info_ptr);
}