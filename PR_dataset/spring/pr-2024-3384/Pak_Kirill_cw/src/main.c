#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#pragma pack(push, 1)

typedef struct {
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;

    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t xpermeter;
    uint32_t ypermeter;
    uint32_t colors_used;
    uint32_t important_colors;
} bmp_header_t;

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} rgb_t;

typedef struct {
    bmp_header_t info;
    rgb_t **data;
} image_t;

#pragma pack(pop)

typedef struct {
    int x;
    int y;
} vec2_t;

int load_image(image_t *image, char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fputs("Failed to open file\n", stderr);
        return 0;
    }

    fread(&image->info, 1, sizeof(bmp_header_t), fp);

    if (image->info.signature != 'B' + ((int)'M' << 8)) {
        fputs("Invalid signature\n", stderr);
        fclose(fp);
        return 0;
    }

    if (image->info.compression != 0 || image->info.bits_per_pixel != 24 || image->info.planes != 1)
    {
        fputs("Invalid format\n", stderr);
        fclose(fp);
        return 0;
    }

    image->data = (rgb_t**)malloc(sizeof(rgb_t*) * image->info.height);
    if (image->data == NULL) {
        fputs("Failed to allocate memory\n", stderr);
        fclose(fp);
        return 0;
    }

    int padding = (4 - ((image->info.width * sizeof(rgb_t) % 4))) % 4;

    fseek(fp, image->info.data_offset, SEEK_SET);
    for (int y = 0; y < image->info.height; y++) {
        image->data[y] = (rgb_t*)malloc(sizeof(rgb_t) * image->info.width + padding);
        if (image->data[y] == NULL) {
            fputs("Failed to allocate memory\n", stderr);
            
            for (int i = 0; i < y; i++)
                free(image->data[i]);
            free(image->data);

            fclose(fp);
            return 0;
        }

        fread(image->data[y], 1, sizeof(rgb_t) * image->info.width + padding, fp);
    }

    for (int y = 0; y < image->info.height / 2; y++) {
        rgb_t *tmp = image->data[y];
        image->data[y] = image->data[image->info.height - y - 1];
        image->data[image->info.height - y - 1] = tmp;
    }

    fclose(fp);
    return 1;
}

int save_image(image_t *image, char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fputs("Failed to open file\n", stderr);
        return 0;
    }

    fwrite(&image->info, 1, sizeof(bmp_header_t), fp);
    fseek(fp, image->info.data_offset, SEEK_SET);

    int padding = (4 - ((image->info.width * sizeof(rgb_t) % 4))) % 4;

    for (int y = 0; y < image->info.height; y++) {
        fwrite(image->data[image->info.height - y - 1], 1, sizeof(rgb_t) * image->info.width + padding, fp);
    }

    fclose(fp);
    return 1;
}

void free_image(image_t *image)
{
    for (int y = 0; y < image->info.height; y++) {
        free(image->data[y]);
    }
    free(image->data);
}

const char shortopts[] = "hiLmpbs:e:c:t:a:l:r:C:R:I:O:T:";

struct option longopts[] = {
    { "help", 0, NULL, 'h' },
    { "info", 0, NULL, 'i' },
    { "line", 0, NULL, 'L' },
    { "mirror", 0, NULL, 'm' },
    { "pentagram", 0, NULL, 'p' },
    {"binarization" , 0 ,NULL , 'b'},
    {"shift" , 0 , NULL , '>'},

    { "start", 1, NULL, 's' },
    { "end", 1, NULL, 'e' },
    { "color", 1, NULL, 'c' },
    { "thickness", 1, NULL, 't' },

    { "axis", 1, NULL, 'a' },
    { "left_up", 1, NULL, 'l' },
    { "right_down", 1, NULL, 'r' },
    
    { "center", 1, NULL, 'C' },
    { "radius", 1, NULL, 'R' },

    { "input", 1, NULL, 'I' },
    { "output", 1, NULL, 'O' },

    {"threshold" , 1 , NULL, 'T'},
    {"step" , 1 , NULL, 'S'},

    { NULL, 0, NULL, 0 }
};

int read_point(vec2_t *point)
{
    int n = sscanf(optarg, "%d.%d", &point->x, &point->y);
    if (n != 2) {
        fputs("Failed to read point\n", stderr);
        return 0;
    }
    return 1;
}

int read_color(rgb_t *color)
{
    int r, g, b;
    int n = sscanf(optarg, "%d.%d.%d", &r, &g, &b);

    if (n != 3) {
        fputs("Failed to read color\n", stderr);
        return 0;
    }

    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255) {
        fputs("Invalid color range\n", stderr);
        return 0;
    }

    color->r = r;
    color->g = g;
    color->b = b;

    return 1;
}

int read_int(int *val)
{
    int n = sscanf(optarg, "%d", val);
    if (n != 1) {
        fputs("Failed to read number\n", stderr);
        return 0;
    }

    return 1;
}

enum {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_XY
};

int read_axis(int *axis)
{
    if (strcmp(optarg, "x") == 0) {
        *axis = AXIS_X;
        return 1;
    }
    if (strcmp(optarg, "y") == 0) {
        *axis = AXIS_Y;
        return 1;
    }
    if (strcmp(optarg, "xy") == 0) {
        *axis = AXIS_XY;
        return 1;
    }

    fputs("Failed to read axis\n", stderr);
    return 0;
}

#define EXIT_ERROR 40
#define EXIT_OK 0

void print_help_message()
{
    puts(
        "cw options...\n"
        "options are:\n"
        "- --help / -h: print help message\n"
        "- --info / -i: print info about image\n"
        "- --line / -L: draw line\n"
        "- --mirror / -m: mirror part of image\n"
        "- --pentagram / -p: draw pentagram\n"
        "\n"
        "- --start / -s: start of line\n"
        "- --end / -e: end of line\n"
        "- --color / -c: color of line/pentagram\n"
        "- --thickness / -t: thickness of line/pentagram\n"
        "- --axis / -a: axis to mirror\n"
        "- --left_up / -l: left up point of region to mirror\n"
        "- --right_down / -r: right down point of region to mirror\n"
        "- --center / -C: center of pentagram\n"
        "- --radius / -R: radius of pentagram\n"
        "- --input / -I: path to input image\n"
        "- --output / -O: path to output image"
    );
}

typedef struct {
    vec2_t start;
    vec2_t end;
    rgb_t color;
    uint8_t is_color_set;
    int thickness;
    int axis;
    vec2_t left_up;
    vec2_t right_down;
    vec2_t center;
    int radius;
    char *input;
    char *output;
    int threshold;
    int step;
} options_t;

int print_image_info(image_t *image)
{
    printf("width: %d\n", (int)image->info.width);
    printf("height: %d\n", (int)image->info.height);
    printf("planes: %d\n", (int)image->info.planes);
    printf("bits per pixel: %d\n", (int)image->info.bits_per_pixel);
    printf("compression: %d\n", (int)image->info.compression);
    printf("image size: %d\n", (int)image->info.image_size);
    printf("x per meter: %d\n", (int)image->info.xpermeter);
    printf("y per meter: %d\n", (int)image->info.ypermeter);
    printf("colors used: %d\n", (int)image->info.colors_used);
    printf("important colors: %d\n", (int)image->info.important_colors);
    return 1;
}

void set_pixel(image_t *image, int x, int y, rgb_t color)
{
    if (x < 0 || y < 0 || x >= image->info.width || y >= image->info.height)
        return;
    
    image->data[y][x] = color;
}

rgb_t get_pixel(image_t *image, int x, int y) {
    if (x < 0 || y < 0 || x >= image->info.width || y >= image->info.height)
        return (rgb_t) { 0, 0, 0 };

    return image->data[y][x];
}

void fill_circle(image_t *image, vec2_t center, int radius, rgb_t color)
{
    int xmin = center.x - radius;
    int xmax = center.x + radius;
    int ymin = center.y - radius;
    int ymax = center.y + radius;

    if (xmin < 0) xmin = 0;
    if (ymin < 0) ymin = 0;
    if (xmax >= image->info.width) xmax = image->info.width - 1;
    if (ymax >= image->info.height) ymax = image->info.height - 1;

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            if ((x - center.x)*(x - center.x) + (y - center.y)*(y - center.y) <= radius*radius)
                set_pixel(image, x, y, color);
        }
    }
}

void draw_line(image_t *image, vec2_t start, vec2_t end, int thickness, rgb_t color)
{
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    if (abs(dx) > abs(dy)) {
        int stepx = dx < 0 ? -1 : 1;
        for (int x = start.x; x != end.x; x += stepx) {
            float y = start.y + (x - start.x) * dy / (float)dx;
            fill_circle(image, (vec2_t) { x, y }, thickness / 2, color);
        }
    }
    else {
        int stepy = dy < 0? -1 : 1;
        for (int y = start.y; y != end.y; y += stepy) {
            float x = start.x + (y - start.y) * dx / (float)dy;
            fill_circle(image, (vec2_t) { x, y }, thickness / 2, color);
        }
    }

    fill_circle(image, (vec2_t) { end.x, end.y }, thickness / 2, color);
}

int draw_line_option(image_t * image, options_t *opts)
{
    if (opts->start.x == INT_MAX && opts->start.y == INT_MAX) {
        fputs("Start point not specified\n", stderr);
        return 0;
    }
    if (opts->end.x == INT_MAX && opts->end.y == INT_MAX) {
        fputs("End point not specified\n", stderr);
        return 0;
    }
    if (opts->is_color_set == 0) {
        fputs("Color not specified\n", stderr);
        return 0;
    }
    if (opts->thickness == INT_MAX || opts->thickness <0) {
        fputs("Thickness not specified\n", stderr);
        return 0;
    }
    if (opts->thickness < 0) {
        fputs("Thickness should be greater than zero\n", stderr);
        return 0;
    }

    draw_line(image, opts->start, opts->end, opts->thickness, opts->color);
    return 1;
}

int mirror_image(image_t *image, options_t *opts)
{
    if (opts->axis == INT_MAX) {
        fputs("Axis not specified\n", stderr);
        return 0;
    }
    if (opts->left_up.x == INT_MAX && opts->left_up.y == INT_MAX) {
        fputs("Left up corner not specified\n", stderr);
        return 0;
    }
    if (opts->right_down.x == INT_MAX && opts->right_down.y == INT_MAX) {
        fputs("Right down corner not specified\n", stderr);
        return 0;
    }

    int x0 = opts->left_up.x;
    int y0 = opts->left_up.y;
    int x1 = opts->right_down.x;
    int y1 = opts->right_down.y;
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (dx < 0 || dy < 0) {
        fputs("Invalid region specified\n", stderr);
        return 0;
    }

    if (opts->axis == AXIS_X) {
        for (int y = 0; y <= dy; y++) {
            for (int x = 0; x <= dx/2; x++) {
                rgb_t tmp = get_pixel(image, x0 + x, y0 + y);
                set_pixel(image, x0 + x, y0 + y, get_pixel(image, x1 - x, y0 + y));
                set_pixel(image, x1 - x, y0 + y, tmp);
            }
        }
    }
    else {
        for (int y = 0; y <= dy/2; y++) {
            for (int x = 0; x <= dx; x++) {
                rgb_t tmp = get_pixel(image, x0 + x, y0 + y);
                set_pixel(image, x0 + x, y0 + y, get_pixel(image, x0 + x, y1 - y));
                set_pixel(image, x0 + x, y1 - y, tmp);
            }
        }
    }
}

void draw_cicle(image_t *image, vec2_t center, int R, int r, rgb_t color)
{
    int xmin = center.x - R;
    int xmax = center.x + R;
    int ymin = center.y - R;
    int ymax = center.y + R;

    if (xmin < 0) xmin = 0;
    if (ymin < 0) ymin = 0;
    if (xmax >= image->info.width) xmax = image->info.width - 1;
    if (ymax >= image->info.height) ymax = image->info.height - 1;

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            int is_inside_big =
                (x - center.x)*(x - center.x) + (y - center.y)*(y - center.y) <= R*R;
            int is_outside_small =
                (x - center.x)*(x - center.x) + (y - center.y)*(y - center.y) >= r*r;
            
            if (is_inside_big && is_outside_small)
                set_pixel(image, x, y, color);
        }
    }
}

int draw_pentagram(image_t *image, options_t *opts)
{
    if (opts->center.x == INT_MAX && opts->center.y == INT_MAX) {
        fputs("Center not specified\n", stderr);
        return 0;
    }
    if (opts->radius == INT_MAX) {
        fputs("Radius not specified\n", stderr);
        return 0;
    }
    if (opts->radius <= 0) {
        fputs("Radius shoud be greater than zero\n", stderr);
        return 0;
    }
    if (opts->thickness == INT_MAX || opts->thickness < 0 ) {
        fputs("Thickness not specified\n", stderr);
        return 0;
    }
    if (opts->thickness < 0) {
        fputs("Thickness should be greater than zero\n", stderr);
        return 0;
    }
    if (opts->is_color_set == 0) {
        fputs("Color not specified\n", stderr);
        return 0;
    }

    vec2_t points[5];

    for (int i = 0; i < 5; i++) {
        float phi = M_PI/2 + (M_PI / 5) * (2*i+3/2);
        points[i].x = opts->center.x + opts->radius * cosf(phi);
        points[i].y = opts->center.y + opts->radius * sinf(phi);
    }

    for (int i = 0; i < 5; i++) {
        draw_line(image, points[i], points[(i + 2) % 5], opts->thickness, opts->color);
    }

    draw_cicle(image, opts->center, opts->radius + opts->thickness / 2, opts->radius - opts->thickness / 2, opts->color);
    return 1;
}


int do_binarization(image_t *image, options_t *opts){
    if (opts->threshold == -1){
        fputs("threshold not specified\n", stderr);
        return 0;
    }

    rgb_t black={0,0,0};
    rgb_t white={255,255,255};

    for ( int x=0;x<image->info.width; x++){
        for (int y=0; y<image->info.height;y++){
            rgb_t color =get_pixel(image , x, y);
            int sum =color.r+color.g+color.b;

            if (sum< opts->threshold){
                set_pixel(image,x,y,black);
            }
            else{
                set_pixel(image,x,y,white);
            }
        
        }
    }
    return 1;
}

int do_shift(image_t *image,options_t *opts){
    if(opts->step == -1){
       fputs("step not specified\n", stderr); 
       return 0;
    }

    if (opts->axis == INT_MAX){
        fputs("axis not specified\n", stderr); 
        return 0;
    }

    rgb_t **copy = malloc(sizeof(rgb_t *) * image->info.height);
    for (int i= 0 ;i < image->info.height; i++){
        copy[i]=malloc(sizeof(rgb_t)* image->info.height);
    }

    for(int y=0; y<image->info.height ; y++){
        for(int x=0; x< image->info.width ;  x++){
           copy[y][x]=image->data[y][x];
        }
    }

    opts->step=-opts->step;

    for(int y=0; y<image->info.height ; y++){
        for(int x=0; x< image->info.width ; x++){
            if(opts->axis==AXIS_X){
                image->data[y][x]=copy[y][(x-opts->step/2)%image->info.width];
            }
            else if(opts->axis==AXIS_Y){
                image->data[y][x]=copy[(y-opts->step/2)%image->info.height][x];
            }
            else{
                image->data[y][x]=copy[(y-opts->step/2)%image->info.height][(x-opts->step/2) % image->info.width];
            }

        }
    }

    for (int i=0; i<image->info.height; i++){
        free(copy[i]);
    }
    free(copy);
    return 1;
}

int main(int argc, char **argv)
{
    puts("Course work for option 4.8, created by Pak Kirill");
    int func = 0;

    options_t opts;

    opts.start = (vec2_t) { INT_MAX, INT_MAX };
    opts.end = (vec2_t) { INT_MAX, INT_MAX };
    opts.color = (rgb_t) { 0, 0, 0 };
    opts.is_color_set = 0;
    opts.thickness = INT_MAX;
    opts.axis = INT_MAX;
    opts.left_up = (vec2_t) { INT_MAX, INT_MAX };
    opts.right_down = (vec2_t) { INT_MAX, INT_MAX };
    opts.center = (vec2_t) { INT_MAX, INT_MAX };
    opts.radius = INT_MAX;
    opts.input = NULL;
    opts.output = "out.bmp";
    opts.threshold=-1;
    opts.step=-1;
    
    int opt = getopt_long(argc, argv, shortopts, longopts, NULL);
    while (opt != -1) {
        if (opt == '?') {
            fputs("Unknown option\n", stderr);
            return EXIT_ERROR; 
        }

        int is_ok = 1;

        switch (opt) {
            case 'h':
                print_help_message();
                return EXIT_OK;
            case 'i':
            case 'L':
            case 'm':
            case 'p':
            case 'b':
            case '>':
                func = opt;
                break;
            case 's':
                is_ok = read_point(&opts.start);
                break;
            case 'e':
                is_ok = read_point(&opts.end);
                break;
            case 'c':
                is_ok = read_color(&opts.color);
                opts.is_color_set = 1;
                break;
            case 't':
                is_ok = read_int(&opts.thickness);
                break;
            case 'a':
                is_ok = read_axis(&opts.axis);
                break;
            case 'l':
                is_ok = read_point(&opts.left_up);
                break;
            case 'r':
                is_ok = read_point(&opts.right_down);
                break;
            case 'C':
                is_ok = read_point(&opts.center);
                break;
            case 'R':
                is_ok = read_int(&opts.radius);
                break;
            case 'I':
                opts.input = optarg;
                break;
            case 'O':
                opts.output = optarg;
                break;
            case 'T':
                is_ok =read_int(&opts.threshold);
                break;
            case 'S':
                is_ok =read_int(&opts.step);
                break;
        }
    
        if (!is_ok)
            return EXIT_ERROR;

        opt = getopt_long(argc, argv, shortopts, longopts, NULL);
    }

    if (func == 0) {
        fputs("Func not specified\n", stderr);
        return EXIT_ERROR;
    }

    if (opts.input == NULL) {
        if (optind >= argc) {
            fputs("No input image specified\n", stderr);
            return EXIT_ERROR;
        }
        opts.input = argv[optind];
    }

    image_t image;
    if (!load_image(&image, opts.input))
        return EXIT_ERROR;
    
    int is_ok = 1;
    switch (func) {
        case 'i':
            print_image_info(&image);
            break;
        case 'L':
            is_ok = draw_line_option(&image, &opts);
            break;
        case 'm':
            is_ok = mirror_image(&image, &opts);
            break;
        case 'p':
            is_ok = draw_pentagram(&image, &opts);
            break;
        case 'b':
            is_ok =do_binarization(&image,&opts);
            break;
        case '>':
            is_ok =do_shift(&image,&opts);
            break;
    }

    if (func != 'i') {
        is_ok = save_image(&image, opts.output);
        if (!is_ok) {
            free_image(&image);
            return EXIT_ERROR;
        }
    }

    free_image(&image);
}