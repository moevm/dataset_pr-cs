#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#pragma pack (push, 1)
typedef struct BmpFileHead {
  unsigned short signature;
  unsigned int filesize;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int pixelArrOffset;
} BmpFileHead;

typedef struct BmpInfoHead {
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
} BmpInfoHead;


typedef struct RGB {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} RGB;

#pragma pack (pop)


void print_file_header(BmpFileHead header){
  printf("signature:\t%x (%hu)\n", header.signature, header.signature);
  printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);

  printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
  printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);

  printf("pixelArrOffset:\t%x (%u)\n\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BmpInfoHead header){
  printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);

  printf("width: \t%x (%u)\n", header.width, header.width);
  printf("height: \t%x (%u)\n", header.height, header.height);

  printf("planes: \t%x (%hu)\n", header.planes, header.planes);

  printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);

  printf("compression:\t%x (%u)\n", header.compression, header.compression);

  printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
  printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
  printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);

  printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
  printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

void print_help(){
  puts("-h, --help  call help table");
  puts("--info  information about input image");
  puts("-i, --input  set input image");
  puts("-o, --output  set output image");
  puts("--inverse  set inveresion of color in some area\n");
  puts("\t--left_up  set left up coordinates of the area");
  puts("\t--right_down  set right down coordinates of the area\n");
  puts("--gray  change the color channel of some area to gray\n");
  puts("\t--left_up  set left up coordinates of the area");
  puts("\t--right_down  set right down coordinates of the area\n");
  puts("--resize  resize the image from the edges\n");
  puts("\t--left  set the resize value for left edge");
  puts("\t--right  set the resize value for right edge");
  puts("\t--above  set the resize value for upper edge");
  puts("\t--below  set the resize value for lower edge");
}


RGB **read_bmp(char* file_name, BmpFileHead* bmfh, BmpInfoHead* bmif){
  FILE* f;
  
  if((f = fopen(file_name, "rb")) != NULL){
  
  if(fread(bmfh, 1, sizeof(BmpFileHead), f) && fread(bmif, 1, sizeof(BmpInfoHead), f)){
    unsigned int height = bmif->height;
    unsigned int width = bmif->width;

    int pad = (4 - (width* 3) % 4) % 4;

    if (bmif->bitsPerPixel != 24 || bmfh->signature != 0x4D42 || bmif->compression != 0){
      printf("Error (40): File is not a bmp format\n");
      exit(40);
    }
 
    RGB **arr_pix = malloc(height * sizeof(RGB*));

    fseek(f, bmfh->pixelArrOffset, SEEK_SET);
  
    for(int i = 0; i < height; i++){
      arr_pix[height - 1 - i] = malloc(width * sizeof(RGB) + pad);
      fread(arr_pix[height - 1 - i], 1, width * sizeof(RGB) + pad, f);

    }
  
    fclose(f);
    return arr_pix;

  } else {
    printf("Error (40): Wrong input file option\n");
    exit(40);
  }
} else {
  printf("Error (40): Wrong input file option\n");
  exit(40);
}

}

void write_bmp(char* file_name, RGB **arr_pix, int height, int width, BmpFileHead* bmfh, BmpInfoHead* bmif){
  
  FILE *f = fopen(file_name, "wb");
  
  fwrite(bmfh, 1, sizeof(BmpFileHead), f);
  fwrite(bmif, 1, sizeof(BmpInfoHead), f);

  int pad = (4 - (width* 3) % 4) % 4;

  fseek(f, bmfh->pixelArrOffset, SEEK_SET);
  
  for(int i = 0; i < height; i++){
    fwrite(arr_pix[height - 1 - i], 1, (width) * sizeof(RGB) + pad, f);
  }
  
  fclose(f);
}


void borders_check(BmpInfoHead* bmif, int* left, int* right, int* up, int* down){

  int H = bmif->height;
  int W = bmif->width;

  if (*left >= W)
    *left = W - 1;
  if (*right >= W)
    *right = W - 1;
  if (*up >= H)
    *up = H - 1;
  if (*down >= H)
    *down = H - 1;

  if (*left < 0)
    *left = 0;
  if (*right < 0)
    *right = 0;
  if (*up < 0)
    *up = 0;
  if (*down < 0)
    *down = 0;
}

void set_inverse(BmpInfoHead* bmif, RGB*** arr_pix_ptr, int left, int up, int right, int down){
  RGB** arr_pix = *(arr_pix_ptr);

  borders_check(bmif, &left, &right, &up, &down);

  for (int i = up; i <= down; i++){
    for (int j = left; j <= right; j++){
      arr_pix[i][j].b = 255 - arr_pix[i][j].b;
      arr_pix[i][j].g = 255 - arr_pix[i][j].g;
      arr_pix[i][j].r = 255 - arr_pix[i][j].r;
    }
  }
}

int round_gray(double sum_bgr){
  double round = sum_bgr - (int)sum_bgr;

  if (round <= 0.5)
    round = 0;
  else
    round = 1;

  return (int)sum_bgr + (int)round;
}

void set_gray(BmpInfoHead* bmif, RGB*** arr_pix_ptr, int left, int up, int right, int down){
  RGB** arr_pix = *(arr_pix_ptr);

  borders_check(bmif, &left, &right, &up, &down);

  double sum_bgr;

  for (int i = up; i < down; i++){
    for (int j = left; j < right; j++){

      sum_bgr = arr_pix[i][j].b * 0.114 + arr_pix[i][j].g * 0.587 + arr_pix[i][j].r * 0.299;
      sum_bgr = round_gray(sum_bgr);

      arr_pix[i][j].b = sum_bgr;
      arr_pix[i][j].g = sum_bgr;
      arr_pix[i][j].r = sum_bgr;
    }
  }
}

void binarization(BmpInfoHead* bmif, RGB*** arr_pix_ptr, int threshold){
  RGB** arr_pix = *(arr_pix_ptr);
  int R = 0;
  int G = 0;
  int B = 0;

  for (int i = 0; i < bmif->height; i++){
    for (int j = 0; j < bmif->width; j++){
      R = arr_pix[i][j].r;
      G = arr_pix[i][j].g;
      B = arr_pix[i][j].b;

      if ((R+G+B) >= threshold){
        arr_pix[i][j].r = 255;
        arr_pix[i][j].g = 255;
        arr_pix[i][j].b = 255;
      } else {
        arr_pix[i][j].r = 0;
        arr_pix[i][j].g = 0;
        arr_pix[i][j].b = 0;
      }
    }
  }
}

void image_resize(RGB*** arr, char side, int resize, RGB color, BmpInfoHead *bmih, BmpFileHead *bmfh) {

    unsigned int W = bmih->width;
    unsigned int H = bmih->height;

    unsigned int new_W = W;
    unsigned int new_H = H;

    if (side == 'l' || side == 'r') {
        if (resize < 0 && -1*resize > W){
            printf("Resize is greater then image width\n");
            exit(43);
        }
        new_W = W + resize;

    } else if (side == 'a' || side == 'b') {
        if (resize < 0 && -1*resize > H){
            printf("Resize is greater then image width\n");
            exit(43);
        }
         new_H = H + resize;
    }

    int pad = (4 - new_W * sizeof(RGB) % 4) % 4;

    RGB** new_arr = (RGB**)malloc(new_H * sizeof(RGB*));

    for (int i = 0; i < new_H; i++) {
        new_arr[i] = (RGB*)malloc(new_W * sizeof(RGB) + pad);
    }

    if (side == 'l') {
        for (int y = 0; y < H; y++) {
            for (int x = new_W - 1; x >= resize && x >= 0; x--) {
                new_arr[y][x] = (*arr)[y][x - resize];
            }
        }

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < resize; x++) {
                new_arr[y][x] = color;
            }
        }
    }

    else if (side == 'r') {
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W && x < new_W; x++) {
                new_arr[y][x] = (*arr)[y][x];
            }
        }

        for (int y = 0; y < H; y++) {
            for (int x = W; x < new_W; x++) {
                new_arr[y][x] = color;
            }
        }
     }

    else if (side == 'b') {
         for (int y = 0; y < H && y < new_H; y++) {
             for (int x = 0; x < W; x++) {
                 new_arr[y][x] = (*arr)[y][x];
             }
         }
         
        for (int y = H; y < new_H; y++) {
            for (int x = 0; x < W; x++) {
                new_arr[y][x] = color;
            }
        }
    }

    else if (side == 'a') {
        for (int y = new_H - 1; y >= resize && y >= 0; y--) {
            for (int x = 0; x < W; x++) {
                new_arr[y][x] = (*arr)[y - resize][x];
            }
        }

        for (int y = 0; y < resize; y++) {
            for (int x = 0; x < W; x++) {
                new_arr[y][x] = color;
            }
        }
    }

    bmih->width = new_W;
    bmih->height = new_H;
    
    // change image headers
    int new_size = new_H * (new_W * sizeof(RGB) + pad);    
    bmfh->filesize = bmfh->filesize - bmih->imageSize + new_size;
    bmih->imageSize = new_size;

    for (int i = 0; i < H; i++) {
        free((*arr)[i]);
    }
    free(*arr);

    *arr = new_arr;
}


int main(int argc, char* argv[]) {
  puts("Course work for option 4.5, created by Aleksandr Spiridonov.");

  int optindex = 0;
  int optchar = 0;

  int left = 0;
  int up = 0;
  int right = 0;
  int down = 0;

  int threshold = 0;
  RGB color;

  short info_flag = 0;
  short input_flag = 0;
  short output_flag = 0;

  short inverse_flag = 0;
  short gray_flag = 0;

  short left_up_flag = 0;
  short right_down_flag = 0;

  short resize_flag = 0;

  short bin_flag = 0;
  short threshold_flag = 0;

  short left_flag = 0;
  short right_flag = 0;
  short above_flag = 0;
  short below_flag = 0;
  short color_flag = 0;

  int flag_index = 0;

  char* file_name;
  char* file_name_out;

  RGB** arr_pix;

  BmpFileHead bmfh;
  BmpInfoHead bmif;

  struct option opts[] =
  {
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"info", no_argument, 0, 'f'},
    {"help", no_argument, 0, 'h'},
    {"inverse", no_argument, 0, 'n'},
    {"gray", no_argument, 0, 'g'},
    {"resize", no_argument, 0, 'z'},
    {"binarization", no_argument, 0, 'B'},
    {"threshold", required_argument, 0, 't'},
    {"left_up", required_argument, 0, 'u'},
    {"right_down", required_argument, 0, 'd'},
    {"left", required_argument, 0, 'l'},
    {"right", required_argument, 0, 'r'},
    {"above", required_argument, 0, 'a'},
    {"below", required_argument, 0, 'b'},
    {"color", required_argument, 0, 'c'},
    {0,0,0,0}
  };

  while ((optchar = getopt_long(argc, argv, "hi:o:", opts, &optindex)) != -1){
    switch (optchar){
      case 'i':
        file_name = optarg;
        input_flag = 1;
        flag_index++;
        break;

      case 'h':
        print_help();
        flag_index++;
        break;

      case 'o':
        file_name_out = optarg;
        output_flag = 1;
        flag_index++;
        break;

      case 'f':
        info_flag = 1;
        flag_index++;
        break;

      case 'n':
        inverse_flag = 1;
        flag_index++;
        break;

      case 'g':
        gray_flag = 1;
        flag_index++;
        break;

      case 'z':
        resize_flag = 1;
        flag_index++;
        break;

      case 'B':
        bin_flag = 1;
        flag_index++;
        break;

      case 't':
        threshold_flag = 1;
        if ((sscanf(optarg, "%d", &threshold) != 1)){
          printf("Error (41): Unknown option argument\n");
          exit(41);
        }

        flag_index++;
        break;

      case 'u':
        if ((sscanf(optarg, "%d.%d", &left, &up) != 2)){
          printf("Error (41): Unknown option argument\n");
          exit(41);
        }
        left_up_flag = 1;
        flag_index++;
        break;

      case 'd':
        if ((sscanf(optarg, "%d.%d", &right, &down) != 2)){
          printf("Error (41): Unknown option argument\n");
          exit(41);
        }
        right_down_flag = 1;
        flag_index++;
	break;

      case 'l':
        sscanf(optarg, "%d", &left);
        left_flag = 1;
        flag_index++;
        break;

      case 'r':
        sscanf(optarg, "%d", &right);
        right_flag = 1;
        flag_index++;
        break;

      case 'a':
        sscanf(optarg, "%d", &up);
        above_flag = 1;
        flag_index++;
        break;

      case 'b':
        sscanf(optarg, "%d", &down);
        below_flag = 1;
        flag_index++;
        break;

      case 'c':
        if (sscanf(optarg, "%hhd.%hhd.%hhd", &color.r, &color.g, &color.b) != 3){
            printf("Error (41): Unknown option argument\n");
            exit(41);
        }
        color_flag = 1;
        flag_index++;
        break;

      case '?':
        printf("Error (41): Unknown or incomplete option or option argument\n");
        exit(41);
        break;
    }
  }

  if (!input_flag)
    file_name = argv[argc-1];

  if (!output_flag)
    file_name_out = file_name;


  if (input_flag && (flag_index != argc - 1)){
    arr_pix = read_bmp(file_name, &bmfh, &bmif);

    if (info_flag){
      print_file_header(bmfh);
      print_info_header(bmif);
    }

    if (inverse_flag){
      if (left_up_flag && right_down_flag) {
        set_inverse(&bmif, &arr_pix, left, up, right, down);

      } else {
        printf("Error(41): Unknown option argument");
        exit(41);
      }

    } else if (gray_flag) {
      if (left_up_flag && right_down_flag) {

        set_gray(&bmif, &arr_pix, left, up, right, down);

      } else {
        printf("Error(41): Unknown option argument");
        exit(41);
      }

    } else if (bin_flag) {
      if (threshold_flag) {

        binarization(&bmif, &arr_pix, threshold);

      } else {
        printf("Error(41): Unknown option argument");
        exit(41);
      }

    } else if (resize_flag) {
      if (!color_flag){
        printf("Error(41): incomplete inverse option color argument\n");
        exit(41);
      }

      if (left_flag && color_flag)
        image_resize(&arr_pix, 'l', left, color, &bmif, &bmfh);
      
      if (right_flag && color_flag)
        image_resize(&arr_pix, 'r', right, color, &bmif, &bmfh);

      if (above_flag && color_flag)
        image_resize(&arr_pix, 'a', up, color, &bmif, &bmfh);

      if (below_flag && color_flag)
        image_resize(&arr_pix, 'b', down, color, &bmif, &bmfh);
    }

    write_bmp(file_name_out, arr_pix, bmif.height, bmif.width, &bmfh, &bmif);

    for(int i = 0; i < bmif.height; i++)
      free(arr_pix[i]);

    free(arr_pix);

  }

  return 0;
}