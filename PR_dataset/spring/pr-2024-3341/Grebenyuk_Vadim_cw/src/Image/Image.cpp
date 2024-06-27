#include "Image.h"
#include "../Errors.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <png.h>
#include <stdexcept>
#include <vector>

Image::Image(const std::string_view filename) {
    // Open file
    FILE *fp = fopen(filename.data(), "rb");
    if (!fp) IOERROR("file cannot be opened");

    png_byte signature[8];
    if (fread(signature, 1, 8, fp) != 8) IOERROR("file read error");

    if (png_sig_cmp(signature, 0, 8)) IOERROR("NOT A PNG");

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) IOERROR("png_create_read_struct fail");

    info_ptr = png_create_info_struct(png_ptr);

    // error handling
    if (!info_ptr || setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        IOERROR("PNG reading error");
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);

    row_pointers.resize(height);
    for (auto &row : row_pointers)
        row = new png_byte[png_get_rowbytes(png_ptr, info_ptr)];

    png_read_image(png_ptr, row_pointers.data());

    fclose(fp);
}

Image::~Image() {
    // Clean up
    if (png_ptr && info_ptr)
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
}

void Image::write(const std::string_view filename) {
    // Open file
    FILE *fp = fopen(filename.data(), "wb");
    if (!fp) IOERROR("file cannot be written");

    // Initialize write structure
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) IOERROR("png_create_write_struct fail");

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        IOERROR("PNG creation failed");
    }

    png_init_io(png_ptr, fp);
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, row_pointers.data());
    png_write_end(png_ptr, nullptr);
    fclose(fp);
}

void Image::info() {
    std::cout << "PNG file size: " << this->width << "x" << this->height << "\n"
              << "color_type: " << (unsigned int)this->color_type << "\n"
              << "bit_depth: " << (unsigned int)this->bit_depth << "\n"
              << "Valid: " << this->is_valid() << "\n";
}

bool Image::is_valid() {
    return this->color_type == PNG_COLOR_TYPE_RGB && this->bit_depth == 8;
};

void Image::rgbfilter(enum Rgb component, int value) {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            png_byte *pix = &(this->row_pointers[y][x * 3]);
            pix[component] = value;
        }
    }
}

void Image::rotate(Coords coords[2], int angle) {
    using std::min, std::max;
    // coords {left_up, right_down}
    // coords are coords of rectangle two corners to rotat
    int Rwidth = coords[1][0] - coords[0][0];
    int Rheight = coords[1][1] - coords[0][1];
    int centerX = coords[0][0] + Rwidth / 2;
    int centerY = coords[0][1] + Rheight / 2;

    std::vector<png_byte *> buffer;
    buffer.resize(this->height);

    for (auto i = 0; i < this->height; i++) {
        buffer[i] = new png_byte[this->width * 3];
        memcpy(buffer[i], this->row_pointers[i], this->width * 3);
    }
    int oldX = 0, oldY = 0;
    int delta_x = 0, delta_y = 0;
    switch (angle) {
        case 270:
            delta_y = -((1 + Rheight) % 2);
            delta_x = -((1 + Rwidth) % 2);
            if ((Rheight % 2) != (Rwidth % 2))
                delta_x = -(Rwidth % 2);
            break;
        case 180:
            if (!(Rheight % 2 || Rwidth % 2)) {
                delta_x = -1 + (Rheight % 2);
                delta_y = -1 + (Rwidth % 2);
            } else {
                delta_x = -(Rheight % 2);
                delta_y = -(Rwidth % 2);
            }
            break;
        case 90:
            delta_y = -1 + (Rwidth % 2);
            delta_x = -(Rheight % 2);
            if ((Rheight % 2) != (Rwidth % 2))
                delta_x = 0;
            break;
    }
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            switch (angle) {
                case 270:
                    oldX = centerX + (y - centerY);
                    oldY = centerY - (x - centerX);
                    break;
                case 180:
                    oldX = centerX - (x - centerX);
                    oldY = centerY - (y - centerY);
                    break;
                case 90:
                    oldX = centerX - (y - centerY);
                    oldY = centerY + (x - centerX);
                    break;
            }
            if ((oldX < 0 || oldY < 0 || oldX >= this->width || oldY >= this->height) ||
                (oldY < coords[0][1] || oldY >= coords[1][1] || oldX < coords[0][0] || oldX >= coords[1][0]))
                continue;
            if (y + delta_y >= 0 && x + delta_x >= 0) {
                png_byte *old_pix = &(this->row_pointers[oldY][oldX * 3]);
                png_byte *buf_pixel = &(buffer[y + delta_y][(x + delta_x) * 3]);
                std::copy(old_pix, old_pix + 3, buf_pixel);
            }
        }
    }

    for (int i = 0; i < this->height; ++i) {
        delete[] this->row_pointers[i];
        this->row_pointers[i] = buffer[i];
    }
}

void Image::squared_lines(Coords coords, int side_size, int thickness, Color color, bool fill, Color fill_color) {
    using std::max, std::min, std::abs;

    // min_1|   |max_1 -- min_2|   |max_2
    // int min_1 = coords - thickness / 2;
    // int max_1 = coords + thickness / 2 + thickness % 2;
    // int min_2 = coords + side_size - thickness / 2 - thickness % 2;
    // int max_2 = coords + side_size + thickness / 2;
    // clamped
    int x_min_1 = max(0, min(coords[0] - thickness / 2, this->width));
    int y_min_1 = max(0, min(coords[1] - thickness / 2, this->height));
    int x_max_1 = min(this->width, coords[0] + thickness / 2 + thickness % 2);
    int y_max_1 = min(this->height, coords[1] + thickness / 2 + thickness % 2);
    int x_min_2 = max(0, min(coords[0] + side_size - thickness / 2 - thickness % 2, this->width));
    int y_min_2 = max(0, min(coords[1] + side_size - thickness / 2 - thickness % 2, this->height));
    int x_max_2 = min(this->width, coords[0] + side_size + thickness / 2);
    int y_max_2 = min(this->height, coords[1] + side_size + thickness / 2);

    if (fill)
        for (int y = y_min_1; y < y_max_2; y++)
            for (int x = x_min_1; x < x_max_2; x++)
                std::copy(fill_color.begin(), fill_color.end(), &(this->row_pointers[y][x * 3]));

    // horizontal
    for (int y = y_min_1; y < y_max_2; y++) {
        for (int x = x_min_1; x < x_max_1; x++)
            std::copy(color.begin(), color.end(), &(this->row_pointers[y][x * 3]));
        for (int x = x_min_2; x < x_max_2; x++)
            std::copy(color.begin(), color.end(), &(this->row_pointers[y][x * 3]));
    }
    for (int x = x_min_1; x < x_max_2; x++) {
        for (int y = y_min_1; y < y_max_1; y++)
            std::copy(color.begin(), color.end(), &(this->row_pointers[y][x * 3]));
        for (int y = y_min_2; y < y_max_2; y++)
            std::copy(color.begin(), color.end(), &(this->row_pointers[y][x * 3]));
    }

    for (int t = 0; t < thickness + 1 - thickness % 2; t++) {
        int _x = coords[0] + t - thickness / 2;
        for (int i = 0; i < side_size; i++) {
            if (coords[1] + i < this->height &&
                coords[1] + i >= 0) {
                if (_x + i >= 0 &&
                    _x + i - thickness / 2 < this->width)
                    std::copy(color.begin(), color.end(), &(this->row_pointers[coords[1] + i][(_x + i) * 3]));
                if (_x - 1 + side_size - i >= 0 &&
                    _x - 1 + side_size - i < this->width)
                    std::copy(color.begin(), color.end(), &(this->row_pointers[coords[1] + i][(_x + side_size - i - 1) * 3]));
            }
        }
    }
}
