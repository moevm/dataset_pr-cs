#include "image.h"


Image* img_from_file(FILE* fstream) {
    Image* img = malloc(sizeof(Image));
    img->error_flag = 0;

    png_byte signature[SIGNATURE_SIZE];
    SET_ERROR_FLAG(fread(signature, sizeof(png_byte), SIGNATURE_SIZE, fstream) != SIGNATURE_SIZE, FLAG_ERROR_READ_FILE)

    SET_ERROR_FLAG(png_sig_cmp(signature, 0, SIGNATURE_SIZE), FLAG_WRONG_SINGATURE)

    img->data = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    SET_ERROR_FLAG(!img->data, FLAG_FAIL_CREATE_PNG_STRUCT)

    img->info = png_create_info_struct(img->data);
    SET_ERROR_FLAG(!img->info, FLAG_FAIL_CREATE_INFO_STRUCT)

    SET_ERROR_FLAG(setjmp(png_jmpbuf(img->data)), FLAG_FAIL_READ_HEADER)
    png_init_io(img->data, fstream);
    png_set_sig_bytes(img->data, 8);
    png_read_info(img->data, img->info);

    img->width = png_get_image_width(img->data, img->info);
    img->height = png_get_image_height(img->data, img->info);
    img->bit_depth = png_get_bit_depth(img->data, img->info);
    img->color_type = png_get_color_type(img->data, img->info);
    img->channels = png_get_channels(img->data, img->info);

    SET_ERROR_FLAG(img->bit_depth != CORRECT_BIT_DEPTH, FLAG_WRONG_BIT_DEPTH)

    SET_ERROR_FLAG(img->channels < MIN_CORRECT_CHANNELS, FLAG_WRONG_CHANNELS)
    
    SET_ERROR_FLAG(setjmp(png_jmpbuf(img->data)), FLAG_ERROR_READ_DATA)
    img->rows = malloc(sizeof(png_byte*) * img->height);
    for (int y = 0; y < img->height; y++)
        img->rows[y] = malloc(sizeof(png_byte) * png_get_rowbytes(img->data, img->info));
    png_read_image(img->data, img->rows);

    png_read_end(img->data, img->info);
    return img;
}


Image* img_from_data(png_byte** buffer,
                     uint32_t width,
                     uint32_t height,
                     png_byte channels) {
    Image* img = malloc(sizeof(Image));
    img->error_flag = 0;

    img->data = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    SET_ERROR_FLAG(!img->data, FLAG_FAIL_CREATE_PNG_STRUCT)

    img->info = png_create_info_struct(img->data);
    SET_ERROR_FLAG(!img->info, FLAG_FAIL_CREATE_INFO_STRUCT)

    SET_ERROR_FLAG(img->channels < MIN_CORRECT_CHANNELS, FLAG_WRONG_CHANNELS)
    int color_type = (channels == MIN_CORRECT_CHANNELS) ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_RGB_ALPHA;

    png_set_IHDR(img->data, img->info, width, height,
        CORRECT_BIT_DEPTH, color_type, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_set_rows(img->data, img->info, buffer);
    
    return img;
}


Image* img_to_file(Image* img, FILE* fstream) {
    img->error_flag = 0;

    img->data = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    SET_ERROR_FLAG(!img->data, FLAG_FAIL_CREATE_PNG_STRUCT)

    img->info = png_create_info_struct(img->data);
    SET_ERROR_FLAG(!img->info, FLAG_FAIL_CREATE_INFO_STRUCT)

    SET_ERROR_FLAG(setjmp(png_jmpbuf(img->data)), FLAG_ERROR_WRITE_FILE)
    png_init_io(img->data, fstream);

    SET_ERROR_FLAG(setjmp(png_jmpbuf(img->data)), FLAG_FAIL_WRITE_HEADER)
    png_set_IHDR(img->data, img->info,
                 img->width, img->height,
                 img->bit_depth, img->color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(img->data, img->info);

    SET_ERROR_FLAG(setjmp(png_jmpbuf(img->data)), FLAG_ERROR_WRITE_DATA)
    png_write_image(img->data, img->rows);

    png_write_end(img->data, img->info);
    return img;
}


void copy_pixel(Image* source, png_byte** dest_rows,
                int64_t src_x, int64_t src_y,
                int64_t dest_x, int64_t dest_y) {
    int64_t channels = source->channels;
    for (int64_t channel = 0; channel < channels; channel++)
        dest_rows[dest_y][dest_x * channels + channel] = source->rows[src_y][src_x * channels + channel];
}


Image* copy_area(Image* input,
                 int64_t source_up_x, int64_t source_up_y,
                 int64_t source_down_x, int64_t source_down_y,
                 int64_t destination_up_x, int64_t destination_up_y) {
    png_byte** new_rows = malloc(sizeof(png_byte*) * input->height);
    size_t row_size = sizeof(png_byte) * png_get_rowbytes(input->data, input->info);
    for (int y = 0; y < input->height; y++) {
        new_rows[y] = malloc(row_size);
        memcpy(new_rows[y], input->rows[y], row_size);
    }

    for (int64_t src_x = source_up_x; src_x <= source_down_x; src_x++) {
        for (int64_t src_y = source_up_y; src_y <= source_down_y; src_y++) {
            int64_t dest_x = destination_up_x + (src_x - source_up_x);
            int64_t dest_y = destination_up_y + (src_y - source_up_y);

            if (IN_RANGE(src_x, 0, input->width-1)  &&
                IN_RANGE(src_y, 0, input->height-1) &&
                IN_RANGE(dest_x, 0, input->width-1) &&
                IN_RANGE(dest_y, 0, input->height-1)) 
                copy_pixel(input, new_rows, src_x, src_y, dest_x, dest_y);
        }
    }

    input->rows = new_rows;
    return input;
}


uint32_t get_pixel(Image* img, int64_t x, int64_t y) {
    uint32_t result = 0;
    png_byte** data = img->rows;
    int64_t channels = img->channels;

    for (int64_t channel = 0; channel < channels; channel++)
        result = (result << CORRECT_BIT_DEPTH) + data[y][x * channels + channel];

    if (img->channels == MIN_CORRECT_CHANNELS) result = (result << CORRECT_BIT_DEPTH) + 0xFF;
    return result;
}


void set_pixel(Image* img,
               int64_t x,
               int64_t y,
               uint32_t color) {
    if (!IN_RANGE(x, 0, img->width - 1) || !IN_RANGE(y, 0, img->height - 1)) return;

    int64_t channels = img->channels;
    for (int64_t channel = 0; channel < channels; channel++)
        img->rows[y][x * channels + channel] = (color >> (MIN_CORRECT_CHANNELS * CORRECT_BIT_DEPTH - CORRECT_BIT_DEPTH * channel)) % 0x100;
}


uint32_t rgb_to_rgba(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}


Image* color_replace(Image* input, uint32_t old, uint32_t new) {
    for (int64_t x = 0; x < input->width; x++) {
        for (int64_t y = 0; y < input->height; y++) {
            uint32_t cursor_color = get_pixel(input, x, y);
            if (cursor_color == old) set_pixel(input, x, y, new);
        }
    }

    return input;
}


Image* border_rectangle(Image* input,
                        uint32_t color,
                        uint16_t thickness,
                        uint16_t index) {
    int64_t shift = 2 * index * thickness;
    for (int64_t diag = 0; diag < thickness; diag++) {
        for (int64_t x = shift + diag; x < input->width - (shift + diag); x++) {
            for (int64_t y = shift + diag; y < input->height - (shift + diag); y++) {
                if ((x == (shift + diag)) ||
                    (y == (shift + diag)) ||
                    (x == (input->width - (shift + diag))-1) ||
                    (y == (input->height - (shift + diag))-1))
                        set_pixel(input, x, y, color);
            }
        }
    }

    return input;
}


Image* border_circle(Image* input,
                     uint32_t color) {
    double center_x = input->width / 2.;
    double center_y = input->height / 2.;
    double radius = fmin(center_x, center_y);

    for (int64_t x = 0; x < input->width; x++) {
        for (int64_t y = 0; y < input->height; y++) {
            if (isgreater(pow(x - center_x, 2) + pow(y - center_y, 2), pow(radius, 2)))
                set_pixel(input, x, y, color);
        }
    }

    return input;
}


Image* draw_circle(Image* input,
                   uint32_t color,
                   int64_t center_x,
                   int64_t center_y,
                   uint32_t thickness,
                   uint32_t radius) {
    for (int64_t x = center_x - radius - thickness; x <= center_x + radius + thickness; x++) {
        for (int64_t y = center_y - radius - thickness; y <= center_y + radius + thickness; y++) {
            if (isgreater(pow(x - center_x, 2) + pow(y - center_y, 2), pow(radius, 2)) &&
                isless(pow(x - center_x, 2) + pow(y - center_y, 2), pow(radius + thickness, 2)))
                    set_pixel(input, x, y, color);
        }
    }

    return input;
}


Image* border_semicircles(Image* input,
                          uint32_t color,
                          uint16_t thickness,
                          uint16_t count) {
    uint32_t radius_w = ceil((input->width / (2. * count)) - thickness / 2.);
    uint32_t radius_h = ceil((input->height / (2. * count)) - thickness / 2.);

    for (uint16_t index = 0; index < count; index++) {
        input = draw_circle(input, color, radius_w * (2 * index + 1) + thickness * index + thickness / 2, 0, thickness, radius_w);
        input = draw_circle(input, color, radius_w * (2 * index + 1) + thickness * index+ thickness / 2, input->height, thickness, radius_w);
        input = draw_circle(input, color, 0, radius_h * (2 * index + 1) + thickness * index+ thickness / 2, thickness, radius_h);
        input = draw_circle(input, color, input->width, radius_h * (2 * index + 1) + thickness * index+ thickness / 2, thickness, radius_h);
    }

    return input;
}

Image* make_border(Image* input,
                   char* pattern,
                   uint32_t color,
                   uint16_t thickness,
                   uint16_t count) {
    if (strcmp(pattern, "rectangle") == 0) {
        for (uint16_t index = 0; index < count; index++)
            input = border_rectangle(input, color, thickness, index);
        return input;
    } else if (strcmp(pattern, "circle") == 0) {
        return border_circle(input, color);
    } else if (strcmp(pattern, "semicircles") == 0) {
        return border_semicircles(input, color, thickness, count);
    }
    
    input->error_flag |= FLAG_ERROR_READ_DATA;
    return input;
}


bool find_rectangle(Image* input,
                    uint32_t color,
                    int64_t left,
                    int64_t up,
                    int64_t width,
                    int64_t height) {
    for (int64_t x = left; x <= left + width; x++) {
        for (int64_t y = up; y <= up + height; y++) {
            if (get_pixel(input, x, y) != color)
                return false;
        }
    }

    return true;
}


Image* draw_rectangle(Image* input,
                      uint32_t color,
                      int64_t left,
                      int64_t up,
                      int64_t width,
                      int64_t height,
                      uint32_t thickness) {
    for (int64_t diag = 0; diag < thickness; diag++) {
        if (diag > 0) {
            left += 1;
            up += 1;
            width -= 2;
            height -= 2;
        }
        for (int64_t x = left; x <= left + width; x++) {
            set_pixel(input, x, up, color);
            set_pixel(input, x, up + height, color);
        }

        for (int64_t y = up; y <= up + height; y++) {
            set_pixel(input, left, y, color);
            set_pixel(input, left + width, y, color);
        }
    }

    return input;
}


void set_box_mark(bool** buffer,
                  int64_t left,
                  int64_t up,
                  int64_t width,
                  int64_t height) {
    for (int64_t x = left; x <= left + width; x++) {
        for (int64_t y = up; y <= up + height; y++)
            buffer[y][x] = false;
    }
}


Image* frame_rectangles(Image* input,
                        uint32_t color,
                        uint32_t border_color,
                        uint16_t thickness) {
    bool** buffer = malloc(sizeof(bool*) * input->height);
    for (int64_t y = 0; y < input->height; y++) {
        buffer[y] = malloc(sizeof(bool) * input->width);
        memset(buffer[y], true, sizeof(bool) * input->width);
    }

    for (int64_t x = 0; x < input->width; x++) {
        for (int64_t y = 0; y < input->height; y++) {
            if (buffer[y][x] && (get_pixel(input, x, y) == color)) {
                int64_t width = 1;
                int64_t height = 1;

                while ((width + 1 < input->width - x) && (get_pixel(input, x + width + 1, y) == color)) width++;
                while ((height + 1 < input->height - y) && find_rectangle(input, color, x, y, width, height + 1)) height++;
                
                if ((width > 1) && (height > 1)) {
                    input = draw_rectangle(input, border_color, x, y, width, height, thickness);
                    set_box_mark(buffer, x, y, width, height);
                }
            }
        }
    }

    return input;
}

Image* outline_image(Image* input,
                     uint32_t color,
                     uint16_t thickness) {
    size_t new_rows_count = input->height + thickness * 2;
    size_t old_row_length = input->channels * input->width;
    size_t new_row_length = old_row_length + input->channels * thickness * 2;
    png_byte** new_rows = malloc(sizeof(png_byte*) * new_rows_count);
    for (int y = 0; y < new_rows_count; y++)
        new_rows[y] = malloc(sizeof(png_byte) * new_row_length);
    for (int y = 0; y < input->height; y++)
        memcpy(new_rows[thickness + y] + input->channels * thickness, input->rows[y], sizeof(png_byte) * old_row_length);

    input->rows = new_rows;
    input->width = input->width + thickness * 2;
    input->height = input->height + thickness * 2;

    for (size_t y = 0; y < thickness; y++) {
        for (size_t x = 0; x < input->width; x++) {
            set_pixel(input, x, y, color);
            set_pixel(input, x, input->height - y - 1, color);
        }
    }

    for (size_t x = 0; x < thickness; x++) {
        for (size_t y = 0; y < input->height; y++) {
            set_pixel(input, x, y, color);
            set_pixel(input, input->width - x - 1, y, color);
        }
    }

    return input;
}
