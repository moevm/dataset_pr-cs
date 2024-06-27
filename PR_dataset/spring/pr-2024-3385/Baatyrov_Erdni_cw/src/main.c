#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <math.h>

#define FAILURE -1
#define SUCCESS 0
#define EXIT_CW_FAILURE 40
#define EXIT_CW_OK      0

typedef struct bmp_header {
    uint16_t signature;
    uint32_t filesize;
    uint32_t reserved;
    uint32_t data_offset;
} __attribute__((packed)) bmp_header_t;

typedef struct info_header {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter;
    uint32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} __attribute__((packed)) bmp_infoheader_t;

typedef struct {
    uint8_t r, g, b;
} pixel_t;

typedef struct image {
    bmp_infoheader_t info;
    pixel_t *data;
} image_t;

int load_bmp(image_t *image, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "error: failed to open '%s'. %s\n", filename, strerror(errno));
        return FAILURE;
    }

    bmp_header_t header;

    int n_read = fread(&header, 1, sizeof(header), fp);
    if (n_read != sizeof(bmp_header_t)) {
        fprintf(stderr, "error: failed to read bmp header\n");
        fclose(fp);
        return FAILURE;
    }

    n_read = fread(&image->info, 1, sizeof(bmp_infoheader_t), fp);
    if (n_read != sizeof(bmp_infoheader_t)) {
        fprintf(stderr, "error: failed to read bmp info header\n");
        fclose(fp);
        return FAILURE;
    }

    if (header.signature != 0x4D42) {
        fprintf(stderr, "error: invalid bmp signature\n");
        fclose(fp);
        return FAILURE;
    
    }

    if  (image->info.bit_count != 24 || image->info.compression != 0) {
        fprintf(stderr, "error: unsupported bmp format\n");
        fclose(fp);
        return FAILURE;
    }

    fseek(fp, header.data_offset, SEEK_SET);
    
    image->data = (pixel_t*)malloc(sizeof(pixel_t) * image->info.width * image->info.height);
    if (image->data == NULL) {
        fprintf(stderr, "error: not enough memory");
        fclose(fp);
        return FAILURE;
    }
    
    int padd = 4 - (image->info.width * sizeof(pixel_t)) % 4;
    for (int i = 0; i < image->info.height; i++) {
        fread(image->data + (i * image->info.width), 1, sizeof(pixel_t) * image->info.width, fp);
        fseek(fp, padd % 4, SEEK_CUR);
    }

    fclose(fp);
    return SUCCESS;
}

struct option longopts[] = {
    { "help",          0, NULL, 'h' },
    { "info",          0, NULL, 'i' },
    { "color_replace", 0, NULL, 'R' },
    { "component_max", 0, NULL, 'M' },
    { "old_color",     1, NULL, 'o' },
    { "new_color",     1, NULL, 'n' },
    {"contrast",       0, NULL, 'c' },
    {"alpha",          1, NULL, 'a' },
    {"beta",           1, NULL, 'b' },
    { "input",         1, NULL, '>' },
    { "output",        1, NULL, '<' },
    {NULL, 0, NULL, 0}
};

#define OPTION_OLD_COLOR 1
#define OPTION_NEW_COLOR 2
#define OPTIONS_COLOR_REPLACE (OPTION_OLD_COLOR | OPTION_NEW_COLOR)

typedef struct {
    int flags;
    pixel_t old_color;
    pixel_t new_color;
    char *input;
    char *output;
    int function;
    float alpha;
    int beta;
} options_t;

void init_options(options_t *options)
{
    options->flags     = 0;
    options->old_color = (pixel_t) { 0, 0, 0 };
    options->new_color = (pixel_t) { 0, 0, 0 };
    options->input     = NULL;
    options->output    = NULL;
    options->function  = 0;
}

void free_options(options_t *options)
{
    if (options->input)
        free(options->input);
    
    if (options->output)
        free(options->output);
}

void print_help()
{
    fputs(
        "usage: cw [options]\n"
        "function-like options:\n"
        "  --help / -h - print help message\n"
        "  --info / -i - print image info\n"
        "  --color_replace / -R - replace old color with new color\n"
        "  --component_max / -M - set every pixel`s component to its max component\n"
        "regular options:\n"
        "  --new_color / -o RRR.GGG.BBB - color for replacement\n"
        "  --old_color / -o RRR.GGG.BBB - color to be replaced\n"
        "  --input FILENAME - input file\n"
        "  --output FILENAME - output file\n", stdout
    );
}

int print_image_info(image_t *image)
{
    printf("width: %d\n", (int)image->info.width);
    printf("height: %d\n", (int)image->info.height);
    printf("planes: %d\n", (int)image->info.planes);
    printf("bit_count: %d\n", (int)image->info.bit_count);
    printf("compression: %d\n", (int)image->info.compression);
    printf("image_size: %d\n", (int)image->info.image_size);
    printf("x_pixels_per_meter: %d\n", (int)image->info.x_pixels_per_meter);
    printf("y_pixels_per_meter: %d\n", (int)image->info.y_pixels_per_meter);
    printf("colors_used: %d\n", (int)image->info.colors_used);
    printf("colors_important: %d\n", (int)image->info.colors_important);

    return SUCCESS;
}

int str2pixel(char *str, pixel_t *pixel)
{
    int r, g, b;
    int n = sscanf(str, "%d.%d.%d", &r, &g, &b);
    
    if (n != 3) {
        fprintf(stderr, "error: can`t read color\n");
        return FAILURE;
    }

    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 | b > 255) {
        fprintf(stderr, "error: invalid color range\n");
        return FAILURE;
    }

    pixel->r = r;
    pixel->g = g;
    pixel->b = b;
    
    return SUCCESS;
}

int do_option_replace_color(image_t *image, pixel_t old_color, pixel_t new_color)
{
    for (int x = 0; x < image->info.width; x++) {
        for (int y = 0; y < image->info.height; y++) {
            pixel_t pixel = image->data[x + y * image->info.width];
            if (pixel.r == old_color.r && pixel.g == old_color.g && pixel.b == old_color.b)
                image->data[x + y * image->info.width] = new_color;
        }
    }
    return SUCCESS;
}

int do_option_max_component(image_t *image)
{
    for (int x = 0; x < image->info.width; x++) {
        for (int y = 0; y < image->info.height; y++) {
            pixel_t pixel = image->data[x + y * image->info.width];
            int max_component = pixel.r;
            max_component = (pixel.g > max_component) ? pixel.g : max_component;
            max_component = (pixel.b > max_component) ? pixel.b : max_component;

            image->data[x + y * image->info.width] = (pixel_t) { max_component, max_component, max_component };
        }
    }
    return SUCCESS;
}

int save_bmp(image_t *image, char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "error: failed to open '%s'. %s\n", filename, strerror(errno));
        return FAILURE;
    }

    bmp_header_t header = {
        .signature = 0x4D42,
        .reserved = 0,
        .filesize = -1,
        .data_offset = sizeof(bmp_header_t) + sizeof(bmp_infoheader_t)
    };

    fwrite(&header, 1, sizeof(bmp_header_t), fp);
    fwrite(&image->info, 1, sizeof(bmp_infoheader_t), fp);
    
    int padd = 4 - (image->info.width * sizeof(pixel_t)) % 4;
    for (int i = 0; i < image->info.height; i++) {
        fwrite(image->data + (i * image->info.width), 1, sizeof(pixel_t) * image->info.width, fp);
        for (int j = 0; j < padd % 4; j++)
            fputc(0, fp);
    }

    fseek(fp, 0, SEEK_END);
    uint32_t filesize = ftell(fp);
    fseek(fp, 2, SEEK_SET);
    fwrite(&filesize, 1, 4, fp);

    fclose(fp);
    return SUCCESS;
}

void free_image(image_t *image)
{
    free(image->data);
}
#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define MIN(A,B) ((A) < (B) ? (A) : (B))
int do_contrast(image_t *image, float alpha, int beta){
    for (int x = 0; x < image->info.width; x++){
        for(int y=0; y < image->info.height; y++){
            pixel_t color = image->data[x + y * image->info.width];
            image->data[x + y * image->info.width].r =  MIN(255, MAX(0, alpha * color.r + beta));
            image->data[x + y * image->info.width].g = MIN(255, MAX(0, alpha * color.g+ beta));
            image->data[x + y * image->info.width].b = MIN(255, MAX(0, alpha * color.b + beta));
        }
    }
}
int main(int argc, char **argv)
{
    puts("Course work for option 3.1, created by Erdni Baatyrov");

    options_t options;
    init_options(&options);

    int opt = getopt_long(argc, argv, "hiRMo:n:", longopts, NULL);
    while (opt != -1) {
        if (opt == '?') {
            fprintf(stderr, "error: invalid option\n");
            exit(EXIT_CW_FAILURE);
        }

        switch (opt) {
            case 'h':
                print_help();
                free_options(&options);
                exit(EXIT_CW_OK);
            case 'i':
            case 'R':
            case 'M':
            case 'c':
                options.function = opt;
                break;
            case 'o':
                if (str2pixel(optarg, &options.old_color) == FAILURE) {
                    free_options(&options);
                    exit(EXIT_CW_FAILURE);
                }
                options.flags |= OPTION_OLD_COLOR;
                break;
            case 'n':
                if (str2pixel(optarg, &options.new_color) == FAILURE) {
                    free_options(&options);
                    exit(EXIT_CW_FAILURE);
                }
                options.flags |= OPTION_NEW_COLOR;
                break;
            case '>':
                options.input = strdup(optarg);
                break;
            case '<':
                options.output = strdup(optarg);
                break;
            case 'a':
                options.alpha = atof(optarg);
                break;
            case  'b':
                options.beta = atoi(optarg);
                break;
        }

        opt = getopt_long(argc, argv, "", longopts, NULL);
    }

    if (options.output == NULL)
        options.output = strdup("out.bmp");

    if (options.input == NULL && optind >= argc) {
        fprintf(stderr, "error: no input file\n");
        free_options(&options);
        exit(EXIT_CW_FAILURE);
    }

    if (options.input == NULL)
        options.input = strdup(argv[optind]);

    if (options.function == 0) {
        fprintf(stderr, "error: function not selected\n");
        free_options(&options);
        exit(EXIT_CW_FAILURE);
    }

    image_t image;
    int ret = load_bmp(&image, options.input);
    if (ret == FAILURE) {
        free_options(&options);
        exit(EXIT_CW_FAILURE);
    }

    switch (options.function) {
        case 'i':
            ret = print_image_info(&image);
            break;
        case 'R':
            if ((options.flags & OPTIONS_COLOR_REPLACE) != OPTIONS_COLOR_REPLACE) {
                fprintf(stderr, "error: not enough arguments\n");
                ret = FAILURE;
            }
            else
                ret = do_option_replace_color(&image, options.old_color, options.new_color);
            break;
        case 'M':
            ret = do_option_max_component(&image);
            break;
        case 'c':
            ret = do_contrast(&image, options.alpha, options.beta);
            break;
    }

    if (ret == FAILURE) {
        free_image(&image);
        free_options(&options);
        exit(EXIT_CW_FAILURE);
    }

    if (options.function != 'i') {
        ret = save_bmp(&image, options.output);
        if (ret == FAILURE) {
            exit(EXIT_CW_FAILURE);
        }
    }

    free_image(&image);
    free_options(&options);
    return EXIT_CW_OK;
}