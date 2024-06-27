#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <assert.h>


#pragma pack(push, 1)
typedef struct {
    uint16_t signature;
    uint32_t filesize;
    uint32_t reserved;
    uint32_t offset;

    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitcount;
    uint32_t compression;
    uint32_t imagesize;
    uint32_t xresolution;
    uint32_t yresolution;
    uint32_t ncolors;
    uint32_t colors_important;
} bmp_info_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_t;

#pragma pack(pop)

typedef struct {
    bmp_info_t info;
    rgb_t *data;
} image_t;

void print_help()
{
    puts(
        "usage: cw OPTIONS\n"
        "options:\n"
        "    -h | --help:           print help message\n"
        "    -i | --info:           print image info\n"
        "    -M | --component_mean: set pixel color to the mean of the components\n"
        "    -m | --component_min:  set pixel color to the minimum of the components\n"
        "    -с | --contrast:       set pixel color to the formula\n"
        "    -I | --input:          input image\n"
        "    -O | --output:         output image\n"
        "    -a | --alpha:          alpha\n"
        "    -b | --beta:           beta\n"
    );
}


int load_image(image_t *image, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fputs("File not found. Try to add: --input filename.bmp\n", stderr);
        print_help();
        return 0;
    }

    fread(&image->info, 1, sizeof(bmp_info_t), fp);
    if (image->info.signature != 0x4D42) {
        fputs("error: invalid signature. Try another format (bmp)\n", stderr);
        print_help();
        return 0;
    }

    if (image->info.bitcount != 24) {
        fprintf(stderr, "error: invalid bitcount (%d != 24). Try another picture\n", image->info.bitcount);
        print_help();
        return 0;
    }

    if (image->info.compression != 0) {
        fputs("error: compression is unsupported.\n", stderr);
        print_help();
        return 0;
    }

    fseek(fp, image->info.offset, SEEK_SET);

    image->data = (rgb_t*)malloc(sizeof(rgb_t) * image->info.width * image->info.height);
    if (image->data == NULL) {
        fprintf(stderr, "error: malloc failed. Try again.\n");
        fclose(fp);
        return 0;
    }

    int n_padding = (4 - ((image->info.width * sizeof(rgb_t)) % 4)) % 4;
    for (uint32_t y = 0; y < image->info.height; y++) {
        fread(&image->data[y * image->info.width], 1, sizeof(rgb_t) * image->info.width, fp);
        fseek(fp, n_padding, SEEK_CUR);
    }

    fclose(fp);
    return 1;
}

void unload_image(image_t *image)
{
    free(image->data);
}

int save_image(image_t *image, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fputs("error: failed to open file. Try again\n", stderr);
        return 0;
    }

    image->info.offset = sizeof(bmp_info_t);
    fwrite(&image->info, 1, sizeof(bmp_info_t), fp);

    char padding[4] = { '\0', '\0', '\0', '\0' };
    int n_padding = (4 - ((image->info.width * sizeof(rgb_t)) % 4)) % 4;

    for (int y = 0; y < image->info.height; y++) {
        fwrite(&image->data[y * image->info.width], 1, sizeof(rgb_t) * image->info.width, fp);
        fwrite(padding, 1, n_padding, fp);
    }


    fclose(fp);
    return 1;
}


const char shortopts[] = "hiMmcI:O:a:b:";
struct option longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"info", no_argument, NULL, 'i'},
    {"component_mean", no_argument, NULL, 'M'},
    {"component_min", no_argument, NULL, 'm'},
    {"contrast", no_argument, NULL, 'c'},
    {"input", required_argument, NULL, 'I'},
    {"output", required_argument, NULL, 'O'},
    {"alpha", required_argument, NULL, 'a'},
    {"beta", required_argument, NULL, 'b'},
    {NULL, 0, NULL, 0}
};

void set_pixel_color_to_component_mean(image_t *image)
{
    for (uint32_t x = 0; x < image->info.width; ++x) {
        for (uint32_t y = 0; y < image->info.height; ++y) {
            rgb_t *pixel = &image->data[x + y * image->info.width];
            pixel->r = (pixel->r + pixel->g + pixel->b) / 3;
            pixel->g = pixel->r;
            pixel->b = pixel->r;
        }
    }
}

void set_pixel_color_to_component_min(image_t *image)
{
    for (uint32_t x = 0; x < image->info.width; ++x) {
        for (uint32_t y = 0; y < image->info.height; ++y) {
            rgb_t *pixel = &image->data[x + y * image->info.width];
            uint8_t min = pixel->r;
            if (pixel->g < min) min = pixel->g;
            if (pixel->b < min) min = pixel->b;

            pixel->r = min;
            pixel->g = min;
            pixel->b = min;
        }
    }
}

void set_pixel_color_to_formula(image_t *image, float alpha, int beta)
{
    for (uint32_t x = 0; x < image->info.width; ++x) {
        for (uint32_t y = 0; y < image->info.height; ++y) {
            rgb_t *pixel = &image->data[x + y * image->info.width];
            int new_r = (int)(pixel->r * alpha + beta);
            int new_g = (int)(pixel->g * alpha + beta);
            int new_b = (int)(pixel->b * alpha + beta);
            
            
            if(new_r >255){
                new_r = 255;
            }
            if(new_g >255){
                new_g = 255;
            }
            if(new_b >255){
                new_b = 255;
            }
            
            if(new_r <0){
                new_r = 0;
            }
            if(new_g <0){
                new_g = 0;
            }
            if(new_b <0){
                new_b = 0;
            }
            
            pixel->r = new_r;
            pixel->g = new_g;
            pixel->b = new_b;
        }
    }
}

void print_image_info(image_t *image)
{
    printf(
        "width:       %d\n"
        "height:      %d\n"
        "planes:      %d\n"
        "bitcount:    %d\n"
        "compression: %d\n"
        "xresolution: %d\n"
        "yresolution: %d\n"
        "ncolors:     %d\n"
        "colors_important: %d",
        (int)image->info.width, (int)image->info.height, (int)image->info.planes,
        (int)image->info.bitcount, (int)image->info.compression, (int)image->info.xresolution,
        (int)image->info.yresolution, (int)image->info.ncolors, (int)image->info.colors_important
    );
}

int main(int argc, char **argv)
{
    puts("Course work for option 3.5, created by Kurkina Polina\n");
    int opt = getopt_long(argc, argv, shortopts, longopts, NULL);
    int function = 0;
    const char *input = NULL;
    const char *output = "out.bmp";
    
    float alpha;
    int beta;
    int scan_a;
    int scan_b;

    
    while (opt != -1) {
        if (opt == '?') {
            fputs("error: invalid option.\n", stderr);
            print_help();
            return 40;
        }

        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 'i':
                function = opt;
                break;
            case 'M':
                function = opt;
                break;
            case 'm':
                function = opt;
                break;
            case 'c':
                function = opt;
                break;
            case 'I':
                input = optarg;
                break;
            case 'O':
                output = optarg;
                break;
            case 'a':
                scan_a = sscanf(optarg, "%f", &alpha);
                break;
            case 'b':
                scan_b = sscanf(optarg, "%d", &beta);
                break;
        }

        opt = getopt_long(argc, argv, shortopts, longopts, NULL);
    }

    if (input == NULL && optind >= argc) {
        fputs("error: no input file specified. Try to add: --input filename.bmp.\n", stderr);
        print_help();
        return 41;
    }

    if (input == NULL)
        input = argv[optind];

    if (function == 0) {
        fputs("error: no function specified. Try to add: -m or -M.\n", stderr);
        print_help();
        return 42;
    }

    image_t image;
    if (!load_image(&image, input)){
        fputs("error: image is not loaded. Try again or change the image.\n", stderr);
        print_help();
        return 43;
    }
       

    switch (function) {
        case 'i':
            print_image_info(&image);
            break;
        case 'M':
            set_pixel_color_to_component_mean(&image);
            break;
        case 'm':
            set_pixel_color_to_component_min(&image);
            break;
        case 'c':
            if(scan_b<1 || scan_a<1){
                fputs("error: no alpha or beta specified. alpha has to be >0, beta has to be int.\n", stderr);
                print_help();
                return 44;
            }
            if(alpha<=0){
                fputs("error: invalid alpha. alpha has to be float and >0.\n", stderr);
                print_help();
                return 44;
            }
            set_pixel_color_to_formula(&image, alpha, beta);
            break;
    }

    if (function != 'i' && !save_image(&image, output)){
        fputs("error: image is not saved. Try again.\n", stderr);
        print_help();
        return 43;
    }
        

    unload_image(&image);
    return 0;
}