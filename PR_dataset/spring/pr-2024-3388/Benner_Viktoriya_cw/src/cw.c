
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_OF_THREE(a, b, c) MAX(MAX(a, b), c)
#define MIN_OF_THREE(a, b, c) MIN(MIN(a, b), c)
#define MAX_COMPONENT_FLOAT_VALUE 255.0

#define HELP                                                                                                                                 \
  "Course work for option 3.1, created by Viktoriya Benner.\n(1)Заменяет все "                                                    \
  "пиксели одного заданного цвета на другой цвет. Флаг для выполнения данной " \
  "операции: `--color_replace`. Функционал определяется:\nЦвет, который "                           \
  "требуется заменить. Флаг `--old_color` (цвет задаётся строкой "                                   \
  "`rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. "                               \
  "пример `--old_color 255.0.0` задаёт красный цвет)\nЦвет на который "                                  \
  "требуется заменить. Флаг `--new_color` (работает аналогично флагу "                           \
  "`--old_color`)\n(2)Установить все компоненты пикселя как максимальную из "                 \
  "них. Флаг для выполнения данной операции: `--component_max`. Т.е. если "                          \
  "пиксель имеет цвет (100, 150, 200), то после применения операции цвет "                      \
  "будет (200, 200, 200)"

#define DEFAULT_OUTPUT_BMP "out.bmp"

#define LONG_OPT_FLAG 0
#define NO_ARG_VAL ':'
#define UNKNOWN_ARG '?'

#define SHORT_INPUT_ARG 'i'
#define SHORT_OUTPUT_ARG 'o'
#define SHORT_HELP_ARG 'h'
#define SHORT_OPTIONS "i:o:h"

#define INPUT_ARG "input"
#define OUTPUT_ARG "output"
#define HELP_ARG "help"
#define INFO_ARG "info"
#define COLOR_REPLACE_ARG "color_replace"
#define COMPONENT_MAX_ARG "component_max"
#define OLD_COLOR_ARG "old_color"
#define NEW_COLOR_ARG "new_color"
#define NO_ARG_VAL_ERROR "Error: argument required value\n"
#define UNKNOWN_ARG_ERROR "Error: unknown argument\n"
#define NO_INPUT_FILE_ARG_ERROR "Error: not geted input-file\n"
#define ARG_VAL_ERROR "Error: argument(s) value is not correct\n"
#define SELECTED_FUNCTIONS_COUNT_ERROR                                         \
  "Error: selected funtions count not equal 1"

#define ERROR_CODE 40

#pragma pack(push, 1)

typedef struct BitmapFileHeader {
  unsigned short signature;
  unsigned int file_size;
  unsigned short first_reserved;
  unsigned short second_reserved;
  unsigned int pixel_arr_offset;
} bmp_file_header_t;

typedef struct BitmapInfoHeader {
  unsigned int header_size;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bits_per_pixel;
  unsigned int compression;
  unsigned int image_size;
  unsigned int x_pixels_per_meter;
  unsigned int y_pixels_per_meter;
  unsigned int colors_in_color_table;
  unsigned int important_color_count;
} bmp_info_header_t;

typedef struct Rgb {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} rgb_t;

#pragma pack(pop)

typedef struct Image {
  bmp_file_header_t *file_header;
  bmp_info_header_t *info_header;
  rgb_t **pixels;
} img_t;

typedef struct Arguments {
  int info_flag;
  char *input_file;
  char *output_file;

  int component_max;
  int color_replace;

  int old_color_f;
  int new_color_f;
  rgb_t old_color;
  rgb_t new_color;

  int hsv;
} args_t;

char *strdup(char *src) {
  char *str;
  char *p;
  int len = 0;

  while (src[len])
    len++;
  str = malloc((len + 1) * sizeof(char));
  p = str;
  while (*src)
    *p++ = *src++;
  *p = '\0';
  return str;
}

void print_file_header(bmp_file_header_t header) {
  printf("signature:\t%x (%hu)\n", header.signature, header.signature);
  printf("filesize:\t%x (%u)\n", header.file_size, header.file_size);
  printf("reserved1:\t%x (%hu)\n", header.first_reserved,
         header.first_reserved);
  printf("reserved2:\t%x (%hu)\n", header.second_reserved,
         header.second_reserved);
  printf("pixelArrOffset:\t%x (%u)\n", header.pixel_arr_offset,
         header.pixel_arr_offset);
}

void print_info_header(bmp_info_header_t header) {
  printf("headerSize:\t%x (%u)\n", header.header_size, header.header_size);
  printf("width:     \t%x (%u)\n", header.width, header.width);
  printf("height:    \t%x (%u)\n", header.height, header.height);
  printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
  printf("bitsPerPixel:\t%x (%hu)\n", header.bits_per_pixel,
         header.bits_per_pixel);
  printf("compression:\t%x (%u)\n", header.compression, header.compression);
  printf("imageSize:\t%x (%u)\n", header.image_size, header.image_size);
  printf("xPixelsPerMeter:\t%x (%u)\n", header.x_pixels_per_meter,
         header.x_pixels_per_meter);
  printf("yPixelsPerMeter:\t%x (%u)\n", header.y_pixels_per_meter,
         header.y_pixels_per_meter);
  printf("colorsInColorTable:\t%x (%u)\n", header.colors_in_color_table,
         header.colors_in_color_table);
  printf("importantColorCount:\t%x (%u)\n", header.important_color_count,
         header.important_color_count);
}

img_t *read_bmp(char *input_file) {
  rgb_t **pixels;
  bmp_file_header_t *file_header = malloc(sizeof(bmp_file_header_t));
  bmp_info_header_t *info_header = malloc(sizeof(bmp_info_header_t));
  img_t *img = malloc(sizeof(img_t));
  int aligment;

  FILE *f = fopen(input_file, "rb");

  if (!f) {
    printf("File not found");
    exit(ERROR_CODE);
  }

  fread(file_header, 1, sizeof(bmp_file_header_t), f);
  fread(info_header, 1, sizeof(bmp_info_header_t), f);

  if (info_header->bits_per_pixel != 24) {
    printf("Not correct bmp file");
    exit(ERROR_CODE);
  }

  pixels = malloc(info_header->height * sizeof(rgb_t *));
  aligment = (4 - (info_header->width * sizeof(rgb_t)) % 4) % 4;
  for (int i = info_header->height - 1; i >= 0; i--) {
    pixels[i] = malloc(info_header->width * sizeof(rgb_t) + aligment);
    fread(pixels[i], 1, info_header->width * sizeof(rgb_t) + aligment, f);
  }

  fclose(f);

  img->file_header = file_header;
  img->info_header = info_header;
  img->pixels = pixels;

  return img;
}

void write_bmp(char *output_file, img_t *img) {
  int aligment;

  FILE *f = fopen(output_file, "wb");
  fwrite(img->file_header, 1, sizeof(bmp_file_header_t), f);
  fwrite(img->info_header, 1, sizeof(bmp_info_header_t), f);

  if (!f) {
    printf("File not found\n");
    exit(ERROR_CODE);
  }

  aligment = (4 - (img->info_header->width * sizeof(rgb_t)) % 4) % 4;
  for (int i = img->info_header->height - 1; i >= 0; i--)
    fwrite(img->pixels[i], 1,
           img->info_header->width * sizeof(rgb_t) + aligment, f);

  fclose(f);
}

void change_color(img_t *img, rgb_t old_color, rgb_t new_color) {
  for (int i = 0; i < img->info_header->height; i++) {
    for (int j = 0; j < img->info_header->width; j++) {
      if (img->pixels[i][j].r == old_color.r &&
          img->pixels[i][j].g == old_color.g &&
          img->pixels[i][j].b == old_color.b) {
        img->pixels[i][j] = new_color;
      }
    }
  }
}

void change_color_to_max(img_t *img) {
  for (int i = 0; i < img->info_header->height; i++) {
    for (int j = 0; j < img->info_header->width; j++) {
      unsigned char max_color = img->pixels[i][j].r > img->pixels[i][j].g
                                    ? img->pixels[i][j].r
                                    : img->pixels[i][j].g;
      max_color =
          max_color > img->pixels[i][j].b ? max_color : img->pixels[i][j].b;

      img->pixels[i][j].r = max_color;
      img->pixels[i][j].g = max_color;
      img->pixels[i][j].b = max_color;
    }
  }
}

rgb_t get_color(char *color_str, int *flag) {
  int tmp_color[3];
  *flag = 0;
  *flag += sscanf(optarg, "%d.%d.%d", &tmp_color[0], &tmp_color[1],
                  &tmp_color[2]) != 3;
  for (int i = 0; i < 3; i++)
    *flag += !(tmp_color[i] <= 255 && tmp_color[i] >= 0);
  return (rgb_t){tmp_color[2], tmp_color[1], tmp_color[0]};
}


void rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b, float *h, float *s, float *v)
{
    uint8_t max = MAX_OF_THREE(r, g, b);
    float maxf = max / MAX_COMPONENT_FLOAT_VALUE;
    uint8_t min = MIN_OF_THREE(r, g, b);
    float minf = min / MAX_COMPONENT_FLOAT_VALUE;
    float delta_r = ((maxf - (r / MAX_COMPONENT_FLOAT_VALUE)) / (maxf - minf));
    float delta_g = ((maxf - (g / MAX_COMPONENT_FLOAT_VALUE)) / (maxf - minf));
    float delta_b = ((maxf - (b / MAX_COMPONENT_FLOAT_VALUE)) / (maxf - minf));
    *s = (maxf < 0.0001) ? 0 : (maxf - minf) / maxf;
    *v = maxf;

    if ((*s * 100.0) < 0.1) {
        *h = 0;
        return;
    }
    else if (r == max) {
        if (g == min) {
            *h = 5 + delta_b;
        }
        else {
            *h = 1 - delta_g;
        }
    }
    else if (g == max) {
        if(b == min) {
            *h = 1 + delta_r;
        }
        else {
            *h = 3 - delta_b;
        }
    }
    else if (b == max && r == min) {
        *h = 3 + delta_g;
    }
    else {
        *h = 5 - delta_r;
    }

    *h = MIN(*h * 60, 360);
}

void make_hsv(img_t* img){
    float r1, g1, b1, c_max, c_min, delta, h, s, v;
    for (int i = 0; i < img->info_header->height; i++){
        for (int j = 0; j < img->info_header->width; j++){
            rgb_to_hsv(img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b, &h, &s, &v);
            img->pixels[i][j].b = (h*3.14/8);
            img->pixels[i][j].g = (int)(s*MAX_COMPONENT_FLOAT_VALUE);
            img->pixels[i][j].r = (int)(v*MAX_COMPONENT_FLOAT_VALUE);
        }
    }
}

args_t get_args(int argc, char *argv[]) {
  args_t args = {0, NULL, NULL, 0, 0, 0, 0, {0, 0, 0}, {0, 0, 0}, 0};

  struct option long_opts[] = {
      {INPUT_ARG, required_argument, NULL, SHORT_INPUT_ARG},
      {OUTPUT_ARG, required_argument, NULL, SHORT_OUTPUT_ARG},
      {HELP_ARG, no_argument, NULL, SHORT_HELP_ARG},
      {INFO_ARG, no_argument, &(args.info_flag), 1},
      {"hsv", no_argument, &(args.hsv), 1},
      {COLOR_REPLACE_ARG, no_argument, &(args.color_replace), 1},
      {COMPONENT_MAX_ARG, no_argument, &(args.component_max), 1},
      {OLD_COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
      {NEW_COLOR_ARG, required_argument, NULL, LONG_OPT_FLAG},
      {NULL, 0, NULL, 0}};

  int long_idx;
  int opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);
  rgb_t tmp_color;
  int color_flag;
  while (opt != -1) {
    switch (opt) {
    case NO_ARG_VAL: {
      printf(NO_ARG_VAL_ERROR);
      exit(ERROR_CODE);
      break;
    }

    case UNKNOWN_ARG: {
      printf(UNKNOWN_ARG_ERROR);
      exit(ERROR_CODE);
      break;
    }

    case SHORT_HELP_ARG: {
      printf(HELP);
      exit(0);
      break;
    }

    case SHORT_INPUT_ARG: {
      if (optarg)
        args.input_file = strdup(optarg);
      break;
    }

    case SHORT_OUTPUT_ARG: {
      if (optarg)
        args.output_file = strdup(optarg);
      break;
    }

    case LONG_OPT_FLAG: {
      if (!optarg)
        break;

      if (!strcmp(OLD_COLOR_ARG, long_opts[long_idx].name)) {
        tmp_color = get_color(optarg, &color_flag);
        if (color_flag) {
          printf(ARG_VAL_ERROR);
          exit(ERROR_CODE);
        }
        args.old_color = tmp_color;
        args.old_color_f = 1;
        break;
      }

      if (!strcmp(NEW_COLOR_ARG, long_opts[long_idx].name)) {
        tmp_color = get_color(optarg, &color_flag);
        if (color_flag) {
          printf(ARG_VAL_ERROR);
          exit(ERROR_CODE);
        }
        args.new_color = tmp_color;
        args.new_color_f = 1;
        break;
      }
    }

    default: {
      break;
    }
    }
    opt = getopt_long(argc, argv, SHORT_OPTIONS, long_opts, &long_idx);
  }

  if (!args.input_file) {
    if (optind < argc) {
      args.input_file = strdup(argv[argc - 1]);
    } else {
      printf(NO_INPUT_FILE_ARG_ERROR);
      exit(ERROR_CODE);
    }
  }

  if (!args.output_file)
    args.output_file = strdup(DEFAULT_OUTPUT_BMP);

  if (!strcmp(args.input_file, args.output_file)) {
    printf(ARG_VAL_ERROR);
    exit(ERROR_CODE);
  }

  return args;
}

void process(args_t args, img_t *img) {
  if (args.info_flag + args.color_replace + args.component_max + args.hsv != 1) {
    printf(SELECTED_FUNCTIONS_COUNT_ERROR);
    exit(ERROR_CODE);
  }

  if (args.info_flag) {
    print_file_header(*(img->file_header));
    print_info_header(*(img->info_header));
    exit(0);
  }

  if (args.color_replace) {
    if (!args.old_color_f || !args.new_color_f) {
      printf(ARG_VAL_ERROR);
      exit(ERROR_CODE);
    }
    change_color(img, args.old_color, args.new_color);
  }

  if (args.component_max) {
    change_color_to_max(img);
  }

  if (args.hsv){
      make_hsv(img);
  }
}

int main(int argc, char *argv[]) {
  args_t args = get_args(argc, argv);
  img_t *img = read_bmp(args.input_file);
  process(args, img);
  write_bmp(args.output_file, img);
  return 0;
}
