#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#pragma pack(push, 1)

typedef struct
{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)

#define ROUND(x) ((int)((x) + 0.5))

#define ERROR_UNSUPPORTED_FILE_FORMAT 40
#define ERROR_UNSUPPORTED_BMP_FORMAT 41
#define ERROR_MEMORY_ALLOCATION_FAILED 42
#define ERROR_FAILED_TO_OPEN_FILE 43
#define ERROR_UNEXPECTED_ARGUMENT 44
#define ERROR_INVALID_COLOR_COMPONENT 45
#define ERROR_INVALID_OPTION_OR_MISSING_ARGUMENT 46
#define ERROR_SPECIFY_INPUT_FILE 47
#define ERROR_INPUT_OUTPUT_SAME 48
#define ERROR_COMPONENT_NAME_REQUIRED 49
#define ERROR_COMPONENT_NAME_USAGE 50
#define ERROR_INPUT_FILE_CANNOT_BE_OPENED 51

#define MSG_UNSUPPORTED_FILE_FORMAT "Unsupported file format: not BMP.\n"
#define MSG_UNSUPPORTED_BMP_FORMAT "Unsupported BMP format: must be 24 bits per pixel.\n"
#define MSG_MEMORY_ALLOCATION_FAILED "Memory allocation failed.\n"
#define MSG_FAILED_TO_OPEN_FILE "Failed to open input/output file.\n"
#define MSG_UNEXPECTED_ARGUMENT "The argument '%s' is unexpected for the specified flag.\n"
#define MSG_INVALID_COLOR_COMPONENT "Invalid color component. It should be 'red', 'green' or 'blue'.\n"
#define MSG_INVALID_OPTION_OR_MISSING_ARGUMENT "Invalid option or missing option argument.\n"
#define MSG_SPECIFY_INPUT_FILE "You need to specify the input file.\n"
#define MSG_INPUT_OUTPUT_SAME "The names of the input and output files must be different.\n"
#define MSG_COMPONENT_NAME_REQUIRED "You must specify the component name when using --component_max_image.\n"
#define MSG_COMPONENT_NAME_USAGE "--component_name can only be used with --component_max_image.\n"
#define MSG_INPUT_FILE_CANNOT_BE_OPENED "The input file could not be opened: %s\n"

void handle_error(FILE *f, const char *msg, int error_code)
{
    fprintf(stderr, "%s", msg);
    if (f != NULL)
    {
        fclose(f);
    }
    exit(error_code);
}

void read_bmp_headers(FILE *f, BitmapFileHeader *bmfh, BitmapInfoHeader *bmif)
{
    fread(bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(bmif, sizeof(BitmapInfoHeader), 1, f);

    if (bmfh->signature != 0x4D42) // Проверка сигнатуры "BM"
    {
        handle_error(f, MSG_UNSUPPORTED_FILE_FORMAT, ERROR_UNSUPPORTED_FILE_FORMAT);
    }

    if (bmif->bitsPerPixel != 24)
    {
        handle_error(f, MSG_UNSUPPORTED_BMP_FORMAT, ERROR_UNSUPPORTED_BMP_FORMAT);
    }
}

void process_image_row(FILE *f, FILE *ff, int width, int padding, void (*process_pixel)(Rgb *, char, float, int), char component, float alpha, int beta)
{
    Rgb *row = (Rgb *)malloc(width * sizeof(Rgb));
    if (!row)
    {
        handle_error(NULL, MSG_MEMORY_ALLOCATION_FAILED, ERROR_MEMORY_ALLOCATION_FAILED);
    }

    fread(row, sizeof(Rgb), width, f);
    if (process_pixel)
    {
        for (int j = 0; j < width; j++)
        {
            process_pixel(&row[j], component, alpha, beta);
        }
    }
    fwrite(row, sizeof(Rgb), width, ff);
    fseek(f, padding, SEEK_CUR);
    fwrite("\0\0\0", 1, padding, ff);

    free(row);
}

void convert_pixel_to_grayscale(Rgb *pixel, char component, float alpha, int beta)
{
    int gray = ROUND((int)pixel->r * 0.299 + (int)pixel->g * 0.587 + (int)pixel->b * 0.114);
    gray = (gray > 255) ? 255 : (gray < 0) ? 0
                                           : gray;
    pixel->r = gray;
    pixel->g = gray;
    pixel->b = gray;
}

void set_max_component(Rgb *pixel, char component, float alpha, int beta)
{
    if (component == 'r')
        pixel->r = 255;
    else if (component == 'g')
        pixel->g = 255;
    else if (component == 'b')
        pixel->b = 255;
}

void contrast(Rgb *pixel, char component, float alpha, int beta)
{
    int new_r = (int)(alpha * (pixel->r)) + beta;
    int new_g = (int)(alpha * (pixel->g)) + beta;
    int new_b = (int)(alpha * (pixel->b)) + beta;

    pixel->r = (unsigned char)((new_r > 255) ? 255 : (new_r < 0) ? 0
                                                                 : new_r);
    pixel->b = (unsigned char)((new_b > 255) ? 255 : (new_b < 0) ? 0
                                                                 : new_b);
    pixel->g = (unsigned char)((new_g > 255) ? 255 : (new_g < 0) ? 0
                                                                 : new_g);
}

void write_bmp(char *input_file, char *output_file, int gray_flag, char component, int component_flag, int contrast_flag, float alpha, int beta, BitmapFileHeader bmfh, BitmapInfoHeader bmif)
{
    FILE *f = fopen(input_file, "rb");
    FILE *ff = fopen(output_file, "wb");

    if (!f || !ff)
    {
        handle_error(NULL, MSG_FAILED_TO_OPEN_FILE, ERROR_FAILED_TO_OPEN_FILE);
    }

    fwrite(&bmfh, sizeof(BitmapFileHeader), 1, ff);
    fwrite(&bmif, sizeof(BitmapInfoHeader), 1, ff);

    fseek(f, bmfh.pixelArrOffset, SEEK_SET);

    int padding = (4 - (bmif.width * 3) % 4) % 4;

    void (*process_pixel)(Rgb *, char, float, int) = NULL;
    if (gray_flag)
    {
        process_pixel = convert_pixel_to_grayscale;
    }
    else if (component_flag)
    {
        process_pixel = set_max_component;
    }
    else if (contrast_flag)
    {
        process_pixel = contrast;
    }

    for (int i = 0; i < bmif.height; i++)
    {
        process_image_row(f, ff, bmif.width, padding, process_pixel, component, alpha, beta);
    }

    fclose(f);
    fclose(ff);
}

void print_file_header(BitmapFileHeader header)
{
    printf("signature:\t\t%04x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t\t%08x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t\t%04x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t\t%04x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%08x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header)
{
    printf("headerSize:\t\t%08x (%u)\n", header.headerSize, header.headerSize);
    printf("width:\t\t\t%08x (%u)\n", header.width, header.width);
    printf("height:\t\t\t%08x (%u)\n", header.height, header.height);
    printf("planes:\t\t\t%04x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%04x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%08x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t\t%08x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%08x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%08x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%08x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%08x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void print_help()
{
    printf("Course work for option 3.4, created by Veronika Maiskaya.\n");
    printf("Options:\n");
    printf("  -i, --input FILE       Input file name\n");
    printf("  -o, --output FILE      Output file name (default: out.bmp)\n");
    printf("  --gray             Convert image to grayscale\n");
    printf("  --component_max_image  Set maximum component value for the specified color\n");
    printf("  --component_name COLOR   Specify the color component (red, green, or blue)\n");
    printf("  --info             Print information about the BMP file\n");
    printf("  -h, --help             Display this help message\n");
}

void handle_input_option(int argc, char *argv[], char *optarg, char **input_file)
{
    *input_file = optarg;
    if (optind < argc && argv[optind][0] != '-')
    {
        fprintf(stderr, MSG_UNEXPECTED_ARGUMENT, argv[optind]);
        exit(ERROR_UNEXPECTED_ARGUMENT);
    }
}

void handle_output_option(char *optarg, char **output_file)
{
    *output_file = optarg;
}

void handle_help_option()
{
    print_help();
    exit(0);
}

void handle_info_option(int argc, char *argv[], int *info_flag)
{
    *info_flag = 1;
    if (optind < argc && argv[optind][0] != '-')
    {
        fprintf(stderr, MSG_UNEXPECTED_ARGUMENT, argv[optind]);
        exit(ERROR_UNEXPECTED_ARGUMENT);
    }
}

void handle_gray_option(int argc, char *argv[], int *gray_flag)
{
    *gray_flag = 1;
    if (optind < argc && argv[optind][0] != '-')
    {
        fprintf(stderr, MSG_UNEXPECTED_ARGUMENT, argv[optind]);
        exit(ERROR_UNEXPECTED_ARGUMENT);
    }
}

void handle_component_max_image_option(int *component_flag)
{
    *component_flag = 1;
}

void handle_component_name_option(char *optarg, char *component)
{
    if (strcmp(optarg, "red") == 0 || strcmp(optarg, "green") == 0 || strcmp(optarg, "blue") == 0)
    {
        *component = (optarg[0] == 'r') ? 'r' : (optarg[0] == 'g') ? 'g'
                                                                   : 'b';
    }
    else
    {
        handle_error(NULL, MSG_INVALID_COLOR_COMPONENT, ERROR_INVALID_COLOR_COMPONENT);
    }
}

void handle_contrast_option(int argc, char *argv[], int *contrast_flag)
{
    *contrast_flag = 1;
    if (optind < argc && argv[optind][0] != '-')
    {
        fprintf(stderr, MSG_UNEXPECTED_ARGUMENT, argv[optind]);
        exit(ERROR_UNEXPECTED_ARGUMENT);
    }
}

void handle_alpha_option(char *optarg, float *alpha)
{
    *alpha = atof(optarg);
    if (*alpha < 0)
    {
        exit(ERROR_INVALID_OPTION_OR_MISSING_ARGUMENT);
    }
}

void handle_beta_option(char *optarg, int *beta)
{
    *beta = atoi(optarg);
}

void parse_command_line_arguments(int argc, char *argv[], char **input_file, char **output_file, int *gray_flag, int *info_flag, char *component, int *component_flag, int *contrast_flag, float *alpha, int *beta)
{
    static struct option long_options[] = {
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"gray", no_argument, 0, 0},
        {"component_max_image", no_argument, 0, 0},
        {"component_name", required_argument, 0, 0},
        {"info", no_argument, 0, 0},
        {"help", no_argument, 0, 'h'},
        {"contrast", no_argument, 0, 0},
        {"alpha", required_argument, 0, 0},
        {"beta", required_argument, 0, 0},
        {0, 0, 0, 0}};

    int option_index = 0;
    int c;
    while ((c = getopt_long(argc, argv, "i:o:h", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'i':
            handle_input_option(argc, argv, optarg, input_file);
            break;
        case 'o':
            handle_output_option(optarg, output_file);
            break;
        case 'h':
            handle_help_option();
            break;
        case 0:
            if (strcmp(long_options[option_index].name, "info") == 0)
            {
                handle_info_option(argc, argv, info_flag);
            }
            else if (strcmp(long_options[option_index].name, "gray") == 0)
            {
                handle_gray_option(argc, argv, gray_flag);
            }
            else if (strcmp(long_options[option_index].name, "component_max_image") == 0)
            {
                handle_component_max_image_option(component_flag);
            }
            else if (strcmp(long_options[option_index].name, "component_name") == 0)
            {
                handle_component_name_option(optarg, component);
            }
            else if (strcmp(long_options[option_index].name, "contrast") == 0)
            {
                handle_contrast_option(argc, argv, contrast_flag);
            }
            else if (strcmp(long_options[option_index].name, "alpha") == 0)
            {
                handle_alpha_option(optarg, alpha);
            }
            else if (strcmp(long_options[option_index].name, "beta") == 0)
            {
                handle_beta_option(optarg, beta);
            }
            break;
        default:
            handle_error(NULL, MSG_INVALID_OPTION_OR_MISSING_ARGUMENT, ERROR_INVALID_OPTION_OR_MISSING_ARGUMENT);
        }
    }

    if (*input_file == NULL && optind < argc)
    {
        *input_file = argv[optind];
    }

    if (*input_file == NULL)
    {
        handle_error(NULL, MSG_SPECIFY_INPUT_FILE, ERROR_SPECIFY_INPUT_FILE);
    }

    if (*output_file != NULL && strcmp(*input_file, *output_file) == 0)
    {
        handle_error(NULL, MSG_INPUT_OUTPUT_SAME, ERROR_INPUT_OUTPUT_SAME);
    }

    if (*component_flag && !*component)
    {
        handle_error(NULL, MSG_COMPONENT_NAME_REQUIRED, ERROR_COMPONENT_NAME_REQUIRED);
    }

    if (!*component_flag && *component)
    {
        handle_error(NULL, MSG_COMPONENT_NAME_USAGE, ERROR_COMPONENT_NAME_USAGE);
    }
}

void process_bmp_file(char *input_file, char *output_file, int gray_flag, int info_flag, char component, int component_flag, int contrast_flag, float alpha, int beta)
{
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;

    FILE *f = fopen(input_file, "rb");
    if (!f)
    {
        handle_error(NULL, MSG_INPUT_FILE_CANNOT_BE_OPENED, ERROR_INPUT_FILE_CANNOT_BE_OPENED);
    }

    read_bmp_headers(f, &bmfh, &bmif);

    if (info_flag)
    {
        print_file_header(bmfh);
        print_info_header(bmif);
        fclose(f);
        return;
    }

    write_bmp(input_file, output_file, gray_flag, component, component_flag, contrast_flag, alpha, beta, bmfh, bmif);
    fclose(f);
}

int main(int argc, char *argv[])
{
    char *input_file = NULL;
    char *output_file = "out.bmp";
    int gray_flag = 0, info_flag = 0;
    char component = 0;
    int component_flag = 0;
    float alpha = 0;
    int beta = 0;
    int contrast_flag = 0;

    parse_command_line_arguments(argc, argv, &input_file, &output_file, &gray_flag, &info_flag, &component, &component_flag, &contrast_flag, &alpha, &beta);
    process_bmp_file(input_file, output_file, gray_flag, info_flag, component, component_flag, contrast_flag, alpha, beta);

    return 0;
}
