#include <stdlib.h>

#include "pngdata.h"
#include "pngfill.h"
#include "pngmnp.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int
is_on_canvas(canvas_t* canvas, int x, int y) {
    if (canvas == NULL) {
        return 0;
    }
    if (canvas->height <= 0 || canvas->width <= 0) {
        return 0;
    }
    if (x < 0 || x > canvas->width - 1) {
        return 0;
    }
    if (y < 0 || y > canvas->height - 1) {
        return 0;
    }
    return 1;
}

int
set_pixel(canvas_t* canvas, color_t* color, int x, int y) {
    if (canvas == NULL || color == NULL) {
        return 44;
    }
    if (!is_on_canvas(canvas, x, y)) {
        return 44;
    }
    png_bytep row = canvas->grid[y];
    png_bytep pixel = &(row[x * BYTES_PER_PIXEL]);
    pixel[0] = color->r;
    pixel[1] = color->g;
    pixel[2] = color->b;
    return 0;
}

color_t*
get_pixel(canvas_t* canvas, int x, int y) {
    if (canvas == NULL) {
        return NULL;
    }
    if (!is_on_canvas(canvas, x, y)) {
        return NULL;
    }
    png_bytep row = canvas->grid[y];
    png_bytep pixel = &(row[x * 3]);
    return create_color(pixel[0], pixel[1], pixel[2]);
}

canvas_t*
copy(canvas_t* canvas, int x0, int y0, int x1, int y1) {
    if (canvas == NULL) {
        return NULL;
    }
    if (!(0 <= x0 && x0 <= canvas->width && 0 <= y0 && y0 <= canvas->height)) {
        return NULL;
    }
    if (!(0 <= x1 && x1 <= canvas->width && 0 <= y1 && y1 <= canvas->height)) {
        return NULL;
    }
    canvas_t* new_canvas = create_canvas(x1 - x0, y1 - y0);
    for (int row = y0; row < y1; ++row) {
        for (int column = x0; column < x1; ++column) {
            color_t* got_color = get_pixel(canvas, column, row);
            if (got_color != NULL) {
                set_pixel(new_canvas, got_color, column - x0, row - y0);
            }
            free(got_color);
        }
    }
    return new_canvas;
}

int
paste(canvas_t* canvas, canvas_t* pasted, color_t* void_color, int x0, int y0) {
    if (canvas == NULL || pasted == NULL) {
        return 44;
    }
    for (int row = y0; row < pasted->height + y0; ++row) {
        for (int column = x0; column < pasted->width + x0; ++column) {
            color_t* got_color = get_pixel(pasted, column - x0, row - y0);
            if (void_color != NULL && color_cmp(got_color, void_color)) {
                free(got_color);
                continue;
            }
            set_pixel(canvas, got_color, column, row);
            free(got_color);
        }
    }
    return 0;
}

int
draw_line(canvas_t* canvas, color_t* color, int x0, int y0, int x1, int y1, int thickness) {
    if (canvas == NULL || color == NULL) {
        return 44;
    }
    if (thickness <= 0) {
        return 44;
    }

    int r = thickness / 2;

    int incline = abs(y1 - y0) - abs(x1 - x0);
    int tmp = 0;
    if (incline > 0) {
        tmp = x0;
        x0 = y0;
        y0 = tmp;
        tmp = x1;
        x1 = y1;
        y1 = tmp;
    }
    if (x0 > x1) {
        tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int diry;
    if (y0 < y1) {
        diry = 1;
    } else {
        diry = -1;
    }
    int y = y0;

    for (int x = x0; x <= x1; ++x) {
        int newx, newy;
        if (incline > 0) {
            newx = y;
            newy = x;
        } else {
            newx = x;
            newy = y;
        }
        if (thickness == 1) {
            set_pixel(canvas, color, newx, newy);
        } else {
            draw_circle(canvas, color, newx, newy, r, 1);
        }
        error -= dy;
        if (error < 0) {
            y += diry;
            error += dx;
        }
    }
    return 0;
}

int
draw_circumference(canvas_t* canvas, color_t* color, int x0, int y0, int radius, int thickness) {
    if (canvas == NULL || color == NULL) {
        return 44;
    }
    if (radius < 0) {
        return 44;
    }
    if (thickness <= 0) {
        return 44;
    }

    int r = thickness / 2;
    int x = radius;
    int y = 0;
    int error = 1 - x;
    while (x >= y) {
        if (thickness == 1) {
            set_pixel(canvas, color, x + x0, y + y0);
            set_pixel(canvas, color, y + x0, x + y0);
            set_pixel(canvas, color, -x + x0, y + y0);
            set_pixel(canvas, color, -y + x0, x + y0);
            set_pixel(canvas, color, -x + x0, -y + y0);
            set_pixel(canvas, color, -y + x0, -x + y0);
            set_pixel(canvas, color, x + x0, -y + y0);
            set_pixel(canvas, color, y + x0, -x + y0);
        } else {
            draw_circle(canvas, color, x + x0, y + y0, r, 1);
            draw_circle(canvas, color, y + x0, x + y0, r, 1);
            draw_circle(canvas, color, -x + x0, y + y0, r, 1);
            draw_circle(canvas, color, -y + x0, x + y0, r, 1);
            draw_circle(canvas, color, -x + x0, -y + y0, r, 1);
            draw_circle(canvas, color, -y + x0, -x + y0, r, 1);
            draw_circle(canvas, color, x + x0, -y + y0, r, 1);
            draw_circle(canvas, color, y + x0, -x + y0, r, 1);
        }

        y++;
        if (error < 0) {
            error += 2 * y + 1;
        } else {
            x--;
            error += 2 * (y - x + 1);
        }
    }
    return 0;
}

int
draw_circle(canvas_t* canvas, color_t* color, int x0, int y0, int radius, int thickness) {
    if (canvas == NULL || color == NULL) {
        return 44;
    }
    if (radius < 0) {
        return 44;
    }
    if (thickness <= 0) {
        return 44;
    }

    int r = thickness / 2;
    draw_circumference(canvas, color, x0, y0, radius, thickness);
    for (int y = y0 - r - radius; y < y0 + 1 + r + radius; ++y) {
        for (int x = x0 - r - radius; x < x0 + 1 + r + radius; ++x) {
            if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= radius * radius) {
                set_pixel(canvas, color, x, y);
            }
        }
    }
    return 0;
}

int
draw_rectangle(canvas_t* canvas, color_t* color, color_t* fill_color, int x0, int y0, int x1, int y1, int thickness) {
    if (canvas == NULL || color == NULL) {
        printf("Error: Null pointer to canvas or color.\n");
        return 44;
    }
    if (thickness <= 0) {
        printf("Error: Thickness is less than 1.\n");
        return 44;
    }

    int r = thickness / 2;

    int lx0 = MIN(x0, x1);
    int ly0 = MIN(y0, y1);
    int lx1 = MAX(x0, x1);
    int ly1 = MAX(y0, y1);

    int dx0 = lx0;
    int dy0 = ly0;
    int dx1 = dx1;
    int dy1 = dy1;
    for (int i = -r; i < 1 + r; ++i) {
        int tx0 = lx0 + i;
        int ty0 = ly0 + i;
        int tx1 = lx1 - i;
        int ty1 = ly1 - i;
        draw_line(canvas, color, tx0, ty0, tx1, ty0, 1);
        draw_line(canvas, color, tx1, ty0, tx1, ty1, 1);
        draw_line(canvas, color, tx0, ty1, tx1, ty1, 1);
        draw_line(canvas, color, tx0, ty0, tx0, ty1, 1);
    }

    if (fill_color != NULL) {
        int nx0 = lx0 + 1 + r;
        int ny0 = ly0 + 1 + r;
        int nx1 = lx1 - 1 - r;
        int ny1 = ly1 - 1 - r;
        while (nx0 <= nx1 && ny0 <= ny1) {
            draw_rectangle(canvas, fill_color, NULL, nx0, ny0, nx1, ny1, 1);
            ++nx0;
            ++ny0;
            --nx1;
            --ny1;
        }
        fill(canvas, fill_color, color, (x0 + x1) / 2, (y0 + y1) / 2);
    }
    return 0;
}

int
split(canvas_t* canvas, color_t* color, int number_x, int number_y, int thickness) {
    if (canvas == NULL || color == NULL) {
        printf("Error: Null pointer to canvas or color.\n");
        return 44;
    }
    if (number_x <= 1 || number_y <= 1) {
        printf("Error: Number of parts by X or Y axis is less than 2.\n");
        return 44;
    }
    if (thickness <= 0) {
        printf("Error: Thickness is less than 1.\n");
        return 44;
    }

    int shift_x = (canvas->width - (number_x - 1) * thickness) / (number_x);
    int shift_y = (canvas->height - (number_y - 1) * thickness) / (number_y);
    if (shift_x <= 0) {
        shift_x = 1;
    }
    if (shift_y <= 0) {
        shift_y = 1;
    }

    for (size_t i = 1; i < number_x; ++i) {
        int x = i * shift_x + (i - 1) * thickness;
        for (size_t ik = 0; ik < thickness; ++ik) {
            draw_line(canvas, color, x + ik, 0, x + ik, canvas->height, 1);
        }
    }
    for (size_t j = 1; j < number_y; ++j) {
        int y = j * shift_y + (j - 1) * thickness;
        for (size_t jk = 0; jk < thickness; ++jk) {
            draw_line(canvas, color, 0, y + jk, canvas->width, y + jk, 1);
        }
    }
    return 0;
}

int
ornament(canvas_t* canvas, color_t* color, int function, int count, int thickness) {
    if (canvas == NULL || color == NULL) {
        printf("Error: Null pointer to canvas or color.\n");
        return 44;
    }
    if (function != 1 && function != 2 && function != 3) {
        printf("Error: Unsupported pattern.\n");
        return 44;
    }
    if (function == 1) { //rectangles
        if (count <= 0 || thickness <= 0) {
            printf("Error: Thickness or count is less than 1.\n");
            return 44;
        }
        for (size_t i = 1; i < count + 1; ++i) {
            int x0 = (i - 1) * 2 * thickness;
            int y0 = x0;
            int x1 = canvas->width - x0 - 1;
            int y1 = canvas->height - y0 - 1;
            if (x0 <= x1 && y0 <= y1) {
                draw_rectangle(canvas, color, NULL, x0, y0, x1, y1, 1);
                draw_rectangle(canvas, color, NULL, x0 + thickness - 1, y0 + thickness - 1, x1 - thickness + 1,
                               y1 - thickness + 1, 1);
                fill(canvas, color, NULL, (x0 + x0 + thickness - 1) / 2, (y0 + y0 + thickness - 1) / 2);
            }
        }
    } else if (function == 2) { //circles
        int width = canvas->width;
        int height = canvas->height;
        canvas_t* new_canvas = create_canvas(width, height);
        fill_canvas(new_canvas, color);
        color_t* void_color = create_void_color(color);

        int radius = MIN(width, height) / 2;
        draw_circle(new_canvas, void_color, width / 2, height / 2, radius, 1);

        paste(canvas, new_canvas, void_color, 0, 0);
        free(void_color);
        free_canvas(new_canvas);
    } else { //semicircles
        if (count <= 0 || thickness <= 0) {
            printf("Error: Thickness or count is less than 1.\n");
            return 44;
        }
        int r_x = (canvas->width / count) / 2;
        int r_y = (canvas->height / count) / 2;
        if (r_x <= 0) {
            r_x = 10;
        }
        if (r_y <= 0) {
            r_y = 10;
        }
        for (size_t i = 0; i < count; ++i) {
            int x = (2 * i + 1) * (r_x + 1);
            draw_circumference(canvas, color, x, 1, r_x, thickness);
            draw_circumference(canvas, color, x, canvas->height - 1, r_x, thickness);
        }
        for (size_t j = 0; j < count; ++j) {
            int y = (2 * j + 1) * (r_y + 1);
            draw_circumference(canvas, color, 1, y, r_y, thickness);
            draw_circumference(canvas, color, canvas->width - 1, y, r_y, thickness);
        }
    }
    return 0;
}

int
rotate(canvas_t* canvas, int x0, int y0, int x1, int y1, int angle) {
    if (canvas == NULL) {
        printf("Error: Null pointer to canvas.\n");
        return 44;
    }
    if (angle != 90 && angle != 180 && angle != 270) {
        printf("Error: Unexpected angle.\n");
        return 44;
    }
    if (x0 == x1 || y0 == y1) {
        printf("Error: Bad rotation area.\n");
        return 44;
    }
    if (!(0 <= x0 && x0 <= canvas->width && 0 <= y0 && y0 <= canvas->height)) {
        printf("Error: Rotation area is not on canvas.\n");
        return 44;
    }
    if (!(0 <= x1 && x1 <= canvas->width && 0 <= y1 && y1 <= canvas->height)) {
        printf("Error: Rotation area is not on canvas.\n");
        return 44;
    }

    int cr_x0 = MIN(x0, x1);
    int cr_y0 = MIN(y0, y1);
    int cr_x1 = MAX(x0, x1);
    int cr_y1 = MAX(y0, y1);

    canvas_t* new_canvas = copy(canvas, cr_x0, cr_y0, cr_x1, cr_y1);
    int src_width = new_canvas->width;
    int src_height = new_canvas->height;
    int count = angle / 90;
    for (size_t i = 0; i < count; ++i) {
        int width, height;
        if (i % 2 == 0) {
            width = src_height;
            height = src_width;
        } else {
            width = src_width;
            height = src_height;
        }
        canvas_t* rotated = create_canvas(width, height);
        for (int row = 0; row < new_canvas->height; ++row) {
            for (int column = 0; column < new_canvas->width; ++column) {
                color_t* got_color = get_pixel(new_canvas, column, row);
                set_pixel(rotated, got_color, row, new_canvas->width - 1 - column);
                free(got_color);
            }
        }
        free_canvas(new_canvas);
        new_canvas = rotated;
    }

    int paste_x = (cr_x1 + cr_x0) / 2 - new_canvas->width / 2;
    int paste_y = (cr_y1 + cr_y0) / 2 - new_canvas->height / 2;

    paste(canvas, new_canvas, NULL, paste_x, paste_y);

    free_canvas(new_canvas);
    return 0;
}

int
outside_ornament(image_t* image, color_t* color, int thickness) {
    if (image == NULL) {
        printf("Error: Null pointer to image.\n");
        return 44;
    }
    if (image->canvas == NULL || color == NULL) {
        printf("Error: Null pointer to canvas or color.\n");
        return 44;
    }
    if (thickness <= 0) {
        printf("Error: Thickness is less than 1.\n");
        return 44;
    }
    canvas_t* new_canvas = create_canvas(image->canvas->width + 2 * thickness, image->canvas->height + 2 * thickness);
    fill_canvas(new_canvas, color);
    paste(new_canvas, image->canvas, NULL, thickness, thickness);
    free_canvas(image->canvas);
    image->canvas = new_canvas;
    return 0;
}