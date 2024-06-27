#include "png_class.h"


Png::Png() {
    width = 0;
    height = 0;
    color_type = 0;
    bit_depth = 0;
    channels = 0;
    png_ptr = NULL;
    info_ptr = NULL;
    row_pointers = NULL;
}


Png::~Png() {
    for (int i = 0; i < height; i++) {
        delete[] row_pointers[i];
    }
    delete[] row_pointers;
    if (png_ptr != NULL) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    }
}

void Png::print_png_info() {
    std::cout << "Image Width: " << width << '\n';
    std::cout << "Image Height: " << height << '\n';
    std::cout << "Image Bit Depth: " << bit_depth << '\n';
    std::cout << "Image Channels: " << channels << '\n';
    if (color_type == PNG_COLOR_TYPE_RGB) {
        std::cout << "Image Color Type: RGB\n";
    } else {
        std::cout << "Image Color Type: RGB_A\n";
    }
}

Png* Png::create_collage(int size_x, int size_y) {
    Png* new_image = new Png();

    if (new_image == NULL)
            {
               std :: cout << "Memory error\n";
                exit(45);
            }


    new_image->width = size_x * this->width;
    new_image->height = size_y * this->height;
    new_image->color_type = this->color_type;
    new_image->bit_depth = this->bit_depth;
    new_image->channels = this->channels;

    new_image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    new_image->info_ptr = png_create_info_struct(new_image->png_ptr);

    png_read_update_info(new_image->png_ptr, new_image->info_ptr);

    new_image->row_pointers = (png_byte**) new png_byte*[new_image->height];
    if (new_image->row_pointers == NULL)
            {
                std::cout << "Memory error\n";
                exit(45);
            }
    for (int y = 0; y < new_image->height; y++) {
        new_image->row_pointers[y] = new png_byte[(png_get_rowbytes(this->png_ptr, this->info_ptr) / this->width) * new_image->width];
        if (new_image->row_pointers[y] == NULL)
            {
                std::cout << "Memory error\n";
                exit(45);
            }
    }

    for (int y = 0; y < this->height*size_y; y+=this->height) {
        for (int x = 0; x < this->width*size_x; x+=this->width) {
            this->insert_image(new_image, x, y);
        }
    }

    return new_image;
}

void Png::rhombus(int color[])
{
    
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            if(float(abs(x-this->width/2))/float(this->width/2)+float(abs(y-this->height/2))/((this->height/2)) <= 1)
            {
                if(this->is_point_in_image(x,y))
                {
                    this->set_pixel(x,y,color);
                }
            }
        }
        
    }
    

}

void Png::recolor_biggest_rect(int old_color[], int new_color[]) {
    int max_area = 0;
    int max_rect_cords[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int current_wight = 0;
            while (check_pixel_color(x + current_wight, y, old_color)) {
                current_wight++;
            }

            int current_height = 0;
            while (check_pixel_color(x, y + current_height, old_color)) {
                current_height++;
            }

            if (max_area < current_wight * current_height) {
                if (is_rect_filled(x, y, x + current_wight, y + current_height, old_color)) {
                    max_area = current_wight * current_height;
                    max_rect_cords[0] = x;
                    max_rect_cords[1] = y;
                    max_rect_cords[2] = x + current_wight;
                    max_rect_cords[3] = y + current_height;
                }
            }
        }
    }

    if (max_area > 1) {
        fill_rect(max_rect_cords[0], max_rect_cords[1], max_rect_cords[2], max_rect_cords[3], new_color);
    } else
    {
        std::cout << "Rect not found\n";
    }
}

void Png::draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color[], float thickness, bool is_fill, int fill_color[]) {

    if (fill_color == NULL) {
        int def_arr[] = { 0, 0, 0, 255 };
        fill_color = def_arr;
    }

    if (is_fill) {
        fill_triangle(x0, y0, x1, y1, x2, y2, fill_color);
    }

    draw_line(x0, y0, x1, y1, color, thickness);
    draw_line(x1, y1, x2, y2, color, thickness);
    draw_line(x2, y2, x0, y0, color, thickness);
}

void Png::draw_line(int x0, int y0, int x1, int y1, int color[], float thickness) {

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int signX = (x0 < x1) ? 1 : -1;
    int signY = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {


            fill_circle(x0, y0, thickness, color);


        int err2 = err * 2;

        if (err2 > -dy) {
            err -= dy;
            x0 += signX;
        }
        if (err2 < dx) {
            err += dx;
            y0 += signY;
        }
    }
}

void Png::set_pixel(int x, int y, int color[]) {
    row_pointers[y][x * channels + 0] = color[0];
    row_pointers[y][x * channels + 1] = color[1];
    row_pointers[y][x * channels + 2] = color[2];
    if (color_type == PNG_COLOR_TYPE_RGBA) {
        row_pointers[y][x * channels + 3] = color[3];
    }
}

bool Png::is_point_in_image(int x, int y) {
    return ((x >= 0 && x < width) && (y >= 0 && y < height));
}

bool Png::check_pixel_color(int x0, int y0, int color[]) {
    if (!is_point_in_image(x0, y0)) {
        return false;
    }
    if (color_type == PNG_COLOR_TYPE_RGB) {
        if (row_pointers[y0][x0 * channels + 0] == color[0] && row_pointers[y0][x0 * channels + 1] == color[1] &&
            row_pointers[y0][x0 * channels + 2] == color[2]) {
            return true;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_RGBA) {
        if (row_pointers[y0][x0 * channels + 0] == color[0] && row_pointers[y0][x0 * channels + 1] == color[1] &&
            row_pointers[y0][x0 * channels + 2] == color[2] && row_pointers[y0][x0 * channels + 3] == color[3]) {
            return true;
        }
    }
    return false;
}

void Png::fill_circle(int x0, int y0, float thickness, int color[]) {
    thickness++;
    for (int x = -floor(thickness / 2); x < round(thickness / 2); x++)
    {
        if (x0 + x > this->width || x0+x < 0)
        {
            continue;
        }
        int height = sqrt(floor(thickness / 2) * round(thickness / 2) - x * x);
        for (int y = -height; y < height; y++)
        {

                if (!is_point_in_image(x+x0, y+y0)) {
                    continue;
                }
                if (check_pixel_color(x+x0, y+y0, color)) {
                    continue;
                }
                set_pixel(x+x0, y+y0, color);

        }
    }
}

bool Png::is_point_in_triangle(int x, int y, int x0, int y0, int x1, int y1, int x2, int y2) {
    int a = (x0 - x) * (y1 - y0) - (x1 - x0) * (y0 - y);
    int b = (x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y);
    int c = (x2 - x) * (y0 - y2) - (x0 - x2) * (y2 - y);
    return ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0));
}

void Png::fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color[]) {
    int max_x = std::max(x0, std::max(x1, x2));
    int min_x = std::min(x0, std::min(x1, x2));
    int max_y = std::max(y0, std::max(y1, y2));
    int min_y = std::min(y0, std::min(y1, y2));

    for (int i = min_x; i < max_x; ++i) {
        for (int j = min_y; j < max_y; ++j) {
            if (is_point_in_triangle(i, j, x0, y0, x1, y1, x2, y2)) {
                set_pixel(i, j, color);
            }
        }
    }
}

void Png::insert_image(Png* image, int x0, int y0) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int color_arr[4];

            color_arr[0] = row_pointers[y][x * channels + 0];
            color_arr[1] = row_pointers[y][x * channels + 1];
            color_arr[2] = row_pointers[y][x * channels + 2];
            if (color_type == PNG_COLOR_TYPE_RGBA) {
                color_arr[3] = row_pointers[y][x * channels + 3];
            }
            image->set_pixel(x + x0, y + y0, color_arr);
        }
    }
}

void Png::fill_rect(int x0, int y0, int x1, int y1, int color[]) {
    for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
            set_pixel(x, y, color);
        }
    }
}

bool Png::is_rect_filled(int x0, int y0, int x1, int y1, int color[]) {
    for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
            if (!check_pixel_color(x, y, color)) {
                return false;
            }
        }
    }
    return true;
}
