#include "utils.h"

void set_pixel(image *img, int x, int y, int color[3]) {
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        img->data[y][x * 3] = color[0];
        img->data[y][x * 3 + 1] = color[1];
        img->data[y][x * 3 + 2] = color[2];
    }
}

int check_colors(char** parts) {
    int color1 = atoi(parts[0]);
    int color2 = atoi(parts[1]);
    int color3 = atoi(parts[2]);

    if(color1 >= 0 && color1 <= 255 && color2 >= 0 && color2 <= 255 && color3 >= 0 && color3 <= 255) {
        return 1;
    } else {
        return 0;
    }
}

bool is_png_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, input_file_error);
        exit(40);
    }
    
    unsigned char header[8];
    fread(header, 1, 8, file);
    fclose(file);

    return !png_sig_cmp(header, 0, 8);
}

char** split_string(char* str){
    const char* delimiter = ".";
    char** result = malloc(2 * sizeof(char*));
    char* token = strtok(str, delimiter);
    int i = 0;
    while (token != NULL) {
        result[i] = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(result[i], token);
        token = strtok(NULL, delimiter);
        i++;
    }
    return result;
}

int is_num(char *n) {
    int i;
    for (i = 0; i < strlen(n); i++) {
        if (isdigit(n[i])) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

bool has_dot(char* str) {
    while (*str) {
        if (*str == '.') {
            return true;
        }
        str++;
    }
    return false;
}

void sort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

typedef struct {
    int x;
    int y;
} Point;

void flood_fill(image *img, int x, int y, int fill_color[3], int boundary_color[3]) {
    if (x < 0 || x >= img->width || y < 0 || y >= img->height) {
        return;
    }

    int current_color[3];
    get_pixel(img, x, y, current_color);

    if (compare_colors(current_color, boundary_color) || compare_colors(current_color, fill_color)) {
        return;
    }

    Point *stack = (Point *)malloc(sizeof(Point) * img->width * img->height);
    int stack_size = 0;
    
    stack[stack_size++] = (Point){x, y};

    while (stack_size > 0) {
        Point p = stack[--stack_size];
        int px = p.x;
        int py = p.y;

        set_pixel(img, px, py, fill_color);

        if (px + 1 < img->width) {
            get_pixel(img, px + 1, py, current_color);
            if (!compare_colors(current_color, boundary_color) && !compare_colors(current_color, fill_color)) {
                stack[stack_size++] = (Point){px + 1, py};
            }
        }

        if (px - 1 >= 0) {
            get_pixel(img, px - 1, py, current_color);
            if (!compare_colors(current_color, boundary_color) && !compare_colors(current_color, fill_color)) {
                stack[stack_size++] = (Point){px - 1, py};
            }
        }

        if (py + 1 < img->height) {
            get_pixel(img, px, py + 1, current_color);
            if (!compare_colors(current_color, boundary_color) && !compare_colors(current_color, fill_color)) {
                stack[stack_size++] = (Point){px, py + 1};
            }
        }

        if (py - 1 >= 0) {
            get_pixel(img, px, py - 1, current_color);
            if (!compare_colors(current_color, boundary_color) && !compare_colors(current_color, fill_color)) {
                stack[stack_size++] = (Point){px, py - 1};
            }
        }
    }

    free(stack);
}

void get_pixel(image *img, int x, int y, int color[3]) {
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        color[0] = img->data[y][x * 3];
        color[1] = img->data[y][x * 3 + 1];
        color[2] = img->data[y][x * 3 + 2];
    } else {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
    }
}


int compare_colors(int color1[3], int color2[3]) {
    for (int i = 0; i < 3; i++) {
        if (color1[i] != color2[i]) {
            return 0;
        }
    }
    return 1;
}

int draw_line(image *img, int x00, int y00, int x11, int y11, int color[3], int width)
{
    for (int i = 0; i < width; i++)
    {
        int x0, x1, y0, y1;
        if (abs(x11 - x00) < abs(y11 - y00)) {
            x0 = x00 + i;
            x1 = x11 + i;
            y1 = y11 + width/2;
            y0 = y00 + width/2;
        } else {   
            x0 = x00 + width/2;
            x1 = x11 + width/2;
            y1 = y11 + i;
            y0 = y00 + i;
        }
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx, sy;
        if (x0 < x1) {
            sx = 1;
        } else {
            sx = -1;
        }
        if (y0 < y1) {
            sy = 1;
        } else {
            sy = -1;
        }
        int err = dx - dy;
        while (1)
        {
            png_bytep row = img->data[y0];
            png_bytep px = &(row[x0 * 3]);
            set_pixel(img, x0, y0, color);
            // px[0] = color[0];
            // px[1] = color[1];
            // px[2] = color[2];
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }
    return 0;
}

void draw_circle(image *img, int center_x, int center_y, int radius, int color[3]) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                set_pixel(img, center_x + x, center_y + y, color);
            }
        }
    }
}

int draw_line2(image *img, int x00, int y00, int x11, int y11, int color[3], int width)
{
    const int dx = abs(x11 - x00);
    const int dy = abs(y11 - y00);
    const int signx = x00 < x11 ? 1 : -1;
    const int signy = y00 < y11 ? 1 : -1;
    int error = dx - dy;
    draw_circle(img, x11, y11, width / 2, color);
    while(x00 != x11 || y00 != y11) 
    {
        draw_circle(img, x00, y00, width / 2, color);
    
        int error2 = error * 2;
        if(error2 > -dy) 
        {
            error -= dy;
            x00 += signx;
        }
        if(error2 < dx) 
        {
            error += dx;
            y00 += signy;
        }
    }
}