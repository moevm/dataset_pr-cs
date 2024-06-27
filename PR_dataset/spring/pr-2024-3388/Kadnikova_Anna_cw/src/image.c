#include "image.h"

#define RGB_CHANNELS 3
#define BYTE_SHIFT 8
#define SECOND_DEG 2

Image* img_from_file(FILE* fstream) {
    Image* img = malloc(sizeof(Image));
    img->error_flag = 0;

    png_byte signature[8];
    SET_ERROR_FLAG(fread(signature, sizeof(png_byte), 8, fstream) != 8, FLAG_ERROR_READ_FILE)

    SET_ERROR_FLAG(png_sig_cmp(signature, 0, 8), FLAG_WRONG_SINGATURE)

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

    SET_ERROR_FLAG(img->bit_depth != 8, FLAG_WRONG_BIT_DEPTH)

    SET_ERROR_FLAG(img->channels < 3, FLAG_WRONG_CHANNELS)
    
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

    SET_ERROR_FLAG(img->channels < 3, FLAG_WRONG_CHANNELS)
    int color_type = (channels == 3) ? PNG_COLOR_TYPE_RGB : PNG_COLOR_TYPE_RGB_ALPHA;

    png_set_IHDR(img->data, img->info, width, height,
        8, color_type, PNG_INTERLACE_NONE,
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


uint32_t get_pixel(Image* img, int64_t x, int64_t y) {
    uint32_t result = 0;
    png_byte** data = img->rows;
    int64_t channels = img->channels;

    for (int64_t channel = 0; channel < channels; channel++)
        result = (result << BYTE_SHIFT) + data[y][x * channels + channel];

    if (img->channels == RGB_CHANNELS) result = (result << BYTE_SHIFT) + 0xFF;
    return result;
}


void set_pixel(Image* img,
               int64_t x,
               int64_t y,
               uint32_t color) {
    if (!IN_RANGE(x, 0, img->width - 1) || !IN_RANGE(y, 0, img->height - 1)) return;

    int64_t channels = img->channels;
    for (int64_t channel = 0; channel < channels; channel++)
        img->rows[y][x * channels + channel] = (color >> (24 - 8 * channel)) % 0x100;
}


uint32_t rgb_to_rgba(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}



Image* draw_circle(Image* input,
                   uint32_t color,
                   int64_t center_x,
                   int64_t center_y,
                   int32_t thickness,
                   int32_t radius,
                   bool fill,
                   uint32_t fill_color) {
    for (int64_t x = center_x - radius - thickness; x <= center_x + radius + thickness; x++) {
        for (int64_t y = center_y - radius - thickness; y <= center_y + radius + thickness; y++) {
            if (isgreater(pow(x - center_x, SECOND_DEG) + pow(y - center_y, SECOND_DEG), pow(MAX(radius - thickness / 2, 0), SECOND_DEG)) &&
                isless(pow(x - center_x, 2) + pow(y - center_y, 2), pow(radius + thickness / 2, 2)))
                    set_pixel(input, x, y, color);
            if (fill) {
                if (isless(pow(x - center_x, SECOND_DEG) + pow(y - center_y, SECOND_DEG), pow(MAX(radius - thickness / 2, 0), SECOND_DEG)))
                    set_pixel(input, x, y, fill_color);
            }
        }
    }

    return input;
}


Image* color_replace(Image* input, uint32_t mask, uint32_t new) {
    for (int64_t x = 0; x < input->width; x++) {
        for (int64_t y = 0; y < input->height; y++) {
            uint32_t cursor_color = get_pixel(input, x, y);
            cursor_color &= mask;
            cursor_color ^= new;
            set_pixel(input, x, y, cursor_color);
        }
    }

    return input;
}


Image* component_set(Image* input, char* cname, uint16_t cvalue) {
    if (strcmp(cname, "red") == 0) {
        return color_replace(input, (uint32_t)0x00FFFF00, rgb_to_rgba(cvalue, 0, 0));
    } else if (strcmp(cname, "green") == 0) {
        return color_replace(input, (uint32_t)0xFF00FF00, rgb_to_rgba(0, cvalue, 0));
    } else if (strcmp(cname, "blue") == 0) {
        return color_replace(input, (uint32_t)0xFFFF0000, rgb_to_rgba(0, 0, cvalue));
    }
    
    input->error_flag |= FLAG_ERROR_READ_DATA;
    return input;
}

void set_circle_pixels(Image* img, int64_t x_center, int64_t y_center, int64_t x, int64_t y, uint32_t color) {
    set_pixel(img, x_center + x, y_center + y, color);
    set_pixel(img, x_center + x, y_center - y, color);
    set_pixel(img, x_center - x, y_center + y, color);
    set_pixel(img, x_center - x, y_center - y, color);
    set_pixel(img, x_center + y, y_center + x, color);
    set_pixel(img, x_center + y, y_center - x, color);
    set_pixel(img, x_center - y, y_center + x, color);
    set_pixel(img, x_center - y, y_center - x, color);
}

void set_circle_dot_pixels(Image* input, int64_t x_center, int64_t y_center, uint32_t color){
    set_pixel(input, x_center, y_center, color);
    set_pixel(input, x_center + 1, y_center, color);
    set_pixel(input, x_center, y_center + 1, color);
    set_pixel(input, x_center - 1, y_center, color);
    set_pixel(input, x_center, y_center-  1, color);
}

void set_circle_two_dot_pixels(Image* input, int64_t x_center, int64_t y_center, uint32_t color){
    set_pixel(input, x_center + 1, y_center + 1, color);
    set_pixel(input, x_center + 1, y_center - 1, color);
    set_pixel(input, x_center - 1, y_center + 1, color);
    set_pixel(input, x_center - 1, y_center - 1, color);
    set_pixel(input, x_center + 2, y_center, color);
    set_pixel(input, x_center, y_center+2, color);
    set_pixel(input, x_center - 2, y_center, color);
    set_pixel(input, x_center, y_center - 2, color);
}

Image* draw_field_circle(Image* input, int64_t x_center, int64_t y_center, uint32_t radius, uint32_t color) {
    if (radius == 0) radius = 1;

    if (radius == 1 || radius == 2) {
        set_circle_dot_pixels(input, x_center, y_center, color);

        if (radius==2) {
            set_circle_two_dot_pixels(input, x_center, y_center, color);
        }

        return input;
    }
   
    int64_t x = 0;
    int64_t y = radius;
    int64_t delta = 1 - 2 * radius;
    int64_t error = 0;

    while (y >= x) {
        set_circle_pixels(input, x_center, y_center, x, y, color);
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * (++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * (--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }

    return draw_field_circle(input, x_center, y_center, radius/2, color);
}


Image* draw_line(Image* input,
                 uint32_t color,
                 uint16_t thickness,
                 int64_t x_start,
                 int64_t y_start,
                 int64_t x_end,
                 int64_t y_end) {
    int64_t delta_x = abs(x_end - x_start);
    int64_t delta_y = abs(y_end - y_start);
    int64_t sign_x = x_start < x_end ? 1 : -1;
    int64_t sign_y = y_start < y_end ? 1 : -1;
    int64_t second_error;
    int64_t first_error = delta_x - delta_y;

    input = draw_field_circle(input, x_end, y_end, thickness/1.5, color);
    while(x_start != x_end || y_start != y_end) {
        input = draw_field_circle(input, x_start, y_start, thickness/1.5, color);
        second_error = first_error * 2;
        if (second_error > -delta_y) {
            first_error -= delta_y;
            x_start += sign_x;
        }
        if (second_error < delta_x) {
            first_error += delta_x;
            y_start += sign_y;
        }
    }

    return input;
}


Image* draw_split(Image* input,
                  uint16_t count_x,
                  uint16_t count_y,
                  uint16_t thickness,
                  uint32_t color) {
    int64_t area_y_size = ((int64_t)input->height - thickness * (count_x - 1)) / count_x;
    int64_t y_shift = ((int64_t)input->height - (area_y_size + (count_x - 1) * (thickness + area_y_size))) / 2;
    int64_t area_x_size = ((int64_t)input->width - thickness * (count_y - 1)) / count_y;
    int64_t x_shift = ((int64_t)input->width - (area_x_size + (count_y - 1) * (thickness + area_x_size))) / 2;

    if (area_y_size < 0 || area_x_size < 0)
        return draw_rectangle(input, 0, 0,
                              input->width, input->height,
                              color, 1,
                              true, color);

    for (uint16_t index = 0; index < count_x - 1; index++)
        input = draw_line(input, color, thickness,
                          0, y_shift + area_y_size + index * (thickness + area_y_size),
                          input->width, y_shift + area_y_size + index * (thickness + area_y_size));
    
    for (uint16_t index = 0; index < count_y - 1; index++)
        input = draw_line(input, color, thickness,
                          x_shift + area_x_size + index * (thickness + area_x_size), 0,
                          x_shift + area_x_size + index * (thickness + area_x_size), input->height);
    
    return input;
}


Image* draw_rectangle(Image* input,
                      int64_t left,
                      int64_t up,
                      int64_t width,
                      int64_t height,
                      uint32_t color,
                      uint16_t thickness,
                      bool fill,
                      uint32_t fill_color) {
    int64_t diag = 0;                    
    while (width > 0 && height > 0) {
        if (diag >= thickness) {
            if (!fill) break;
            color = fill_color;
        }

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

        diag++;
    }

    return input;
}


Image* draw_square(Image* input,
                   int64_t left,
                   int64_t up,
                   int64_t side,
                   uint32_t color,
                   uint16_t thickness,
                   bool fill,
                   uint32_t fill_color) {
    input = draw_rectangle(input, left - thickness / 2, up - thickness / 2,
                           side, side,
                           color, thickness,
                           fill, fill_color);
    input = draw_line(input, color, thickness,
                      left + thickness / 2, up + thickness / 2,
                      left + side - thickness / 2, up + side - thickness / 2);
    input = draw_line(input, color, thickness,
                      left + side - thickness / 2, up + thickness / 2,
                      left + thickness / 2, up + side - thickness / 2);
    return input;
}

Image* draw_rhombus(Image* input,
                    uint32_t color) {
    double semiwidth = input->width / 2.;
    double semiheight = input->height / 2.;

    for (int64_t x = 0; x < input->width; x++) {
        for (int64_t y = 0; y < input->height; y++) {
            if (islessequal((fabs(x - semiwidth) / semiwidth) + (fabs(y - semiheight) / semiheight), 1.))
                set_pixel(input, x, y, color);
        }
    }

    return input;
}