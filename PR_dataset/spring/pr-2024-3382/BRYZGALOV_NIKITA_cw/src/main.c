#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

#pragma pack (push, 1)

typedef struct BitmapFileHeader {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader; 

typedef struct BitmapInfoHeader {
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

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGB;

#pragma pack(pop)


typedef struct BMP {
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    RGB ** canvas;
} BMP;


// for CLI processing
struct Input {
    char input_file[1024];
    char output_file[1024];

    // task flag
    char flag_info;
    char flag_help;
    char flag_rectangle;
    char flag_circle;
    char flag_ornament;
    char flag_rotation;
    char flag_paving;

    // task properties
    int x0, y0;
    int x1, y1;
    int thickness;
    RGB color;
    char fill;
    RGB fill_color;
    int xc, yc;
    int radius;
    int count;
    int pattern; 
    int angle;

    // initialization check
    char flag_left_up;
    char flag_right_down;
    char flag_thickness;
    char flag_color;
    char flag_fill_color;
    char flag_center;
    char flag_radius;
    char flag_count;
    char flag_angle;
    char flag_pattern;
};



// read and save
BMP read_BMP(char * file_name);
void save_BMP(char * file_name, BMP image);

// additionall
void set_pixel(BMP image, int x, int y, RGB color);
void fill_left(BMP image, int x, int y, RGB color);
void fill_right(BMP image, int x, int y, RGB color);
unsigned int height(BMP image);
unsigned int width(BMP image);

// CLI_processing
struct Input CLI_processing(int argc, char ** argv);

//data checking
int all_data_rectangle(struct Input task);
int all_data_circle(struct Input task);
int all_data_ornament(struct Input task);
int all_data_rotate(struct Input task);
int all_data_paving(struct Input task);

// figures
void draw_rect(BMP image, int x0, int y0, int x1, int y1, int thickness, RGB color, char fill, RGB fill_color);
void draw_simple_circle(BMP image, int xc, int yc, int radius, RGB color);
void draw_circle(BMP image, int xc, int yc, int radius, int thickness, RGB color, char fill, RGB fill_color);

// rotate
void rotate(BMP image, int x0, int y0, int x1, int y1, int angle);

// paving
void paving(BMP image, int x0, int y0, int x1, int y1);


// ornament
void draw_ornament(BMP image, int count, int thickness, RGB color, int pattern);
void draw_rect_pattern(BMP image, int count, int thickness, RGB color);
void draw_circle_pattern(BMP image, int count, int xc, int yc, int radius, int thickness, RGB color);
void draw_semicircle_pattern(BMP image, int count, int thickness, RGB color);

// info
void print_file_header(BitmapFileHeader header);
void print_info_header(BitmapInfoHeader header);
void print_info(BMP image);
void print_help();

int main(int argc, char ** argv) {
    printf("Course work for option 5.1, created by Bryzgalov Nikita.\n");
    struct Input task = CLI_processing(argc, argv);
    char * input_file = task.input_file;
    char * output_file = task.output_file;
    BMP image;

    if (task.flag_info || task.flag_rectangle || task.flag_circle || task.flag_rotation || task.flag_ornament || task.flag_paving) {
        image = read_BMP(input_file);
    }

    if (task.flag_info) {
        print_info(image);
        
    } else if (all_data_rectangle(task)) {
        draw_rect(image, task.x0, height(image) - task.y1 - 1, task.x1, height(image) - task.y0 - 1, task.thickness, task.color, task.fill, task.fill_color);

    } else if (all_data_circle(task)) {
        draw_circle(image, task.xc, height(image) - task.yc - 1, task.radius, task.thickness, task.color, task.fill, task.fill_color);
    
    } else if (all_data_paving(task)) {
        paving(image, task.x0, task.y1, task.x1, task.y0);
        
    } else if (all_data_rotate(task)) {
        rotate(image, task.x0, task.y1, task.x1, task.y0, task.angle);

    } else if (all_data_ornament(task)) {
        draw_ornament(image, task.count, task.thickness, task.color, task.pattern);

    } else if (task.flag_help) {
        print_help();

    } else {
        print_help();
    }


    if (task.flag_info || task.flag_rectangle || task.flag_circle || task.flag_rotation || task.flag_ornament || task.flag_paving) {
        save_BMP(output_file, image);
    }
    return 0;
}


BMP read_BMP(char * file_name) {
    FILE * f = fopen(file_name, "rb");
    if (!f){
        printf("File not found\n");
        exit(41);
    }
    BMP image;
    fread(&image.bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&image.bmih, 1, sizeof(BitmapInfoHeader), f);
    if (image.bmih.headerSize != 40 || image.bmih.bitsPerPixel != 24 || image.bmfh.signature != 0x4D42 || image.bmih.compression != 0) {
        printf("This bmp format is not supported by the program\n");
        exit(41);
    }
    unsigned int W = width(image);
    unsigned int H = height(image);
    image.canvas = calloc(1, H * sizeof(RGB*));
    for (int i = 0; i < H; i ++) {
        image.canvas[i] = calloc(1, W * sizeof(RGB) + (4 - (W * sizeof(RGB)) % 4) % 4);
        fread(image.canvas[i], 1, W * sizeof(RGB) + (4 - (W * sizeof(RGB)) % 4) % 4, f);
    }
    fclose(f);
    return image;
} 


void save_BMP(char * file_name, BMP image) {
    FILE * f = fopen(file_name, "wb");
    fwrite(&image.bmfh, 1, sizeof(BitmapFileHeader), f);
    fwrite(&image.bmih, 1, sizeof(BitmapInfoHeader), f);
    unsigned int W = width(image);
    unsigned int H = height(image);
    for (int i = 0; i < H; i ++) {
        fwrite(image.canvas[i], 1, W * sizeof(RGB) + (4 - (W * sizeof(RGB)) % 4) % 4, f);
    }
    fclose(f);
}


void set_pixel(BMP image, int x, int y, RGB color) {
    if (x >= 0 && y >= 0 && x < width(image) && y < height(image)) {
        image.canvas[y][x].r = color.r;
        image.canvas[y][x].g = color.g;
        image.canvas[y][x].b = color.b;
    }
}


void draw_rect(BMP image, int x0, int y0, int x1, int y1, int thickness, RGB color, char fill, RGB fill_color) {
    int W = width(image);
    int H = height(image);
    if (fill) {
        for (int x = max(x0 + 1, 0); x <= min(x1, W - 1); x ++) {
            for (int y = max(y0 + 1, 0); y <= min(y1, H - 1); y ++) {
                set_pixel(image, x, y, fill_color);
            }
        }
    }
    int rad = thickness / 2;
    int d = max(1, round(sqrt(10 + rad) - 3));

    // down
    if (y0 + rad >= 0) {
        for (int x = x0; x <= x1; x += d)
            draw_simple_circle(image, x, y0, rad, color);
    }

    // up  
    if (y1 - rad < H) {
        for (int x = x0; x <= x1; x += d)
            draw_simple_circle(image, x, y1, rad, color);
    }

    // left
    if (x0 + rad >= 0) {
        for (int y = y0; y <= y1; y += d)
            draw_simple_circle(image, x0, y, rad, color);
    }

    // right  
    if (x1 - rad < W) {
        for (int y = y0; y <= y1; y += d)
            draw_simple_circle(image, x1, y, rad, color);
    }
}


void draw_rect_pattern(BMP image, int count, int thickness, RGB color) {
    unsigned int H = height(image);
    unsigned int W = width(image);
    int x0 = 0, y0 = 0;
    int x1 = W - 1, y1 = H - 1;

    for (int i = 0; i < count; i ++) {
        for (int x = x0; x <= x1; x ++) {
            for (int i = 0; i < thickness; i ++) {
                set_pixel(image, x, y0 + i, color);
                set_pixel(image, x, y1 - i, color);
            }
        }
        for (int y = y0; y <= y1; y ++) {
            for (int i = 0; i < thickness; i ++) {
                set_pixel(image, x0 + i, y, color);
                set_pixel(image, x1 - i, y, color);
            }
        }        
        //draw_rect(image, x0, y0, x1, y1, thickness, color, 0, color);
        x0 += thickness * 2;
        x1 -= thickness * 2;
        y0 += thickness * 2;
        y1 -= thickness * 2;
    }
}


void draw_simple_circle(BMP image, int xc, int yc, int radius, RGB color) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        for (int i = y; i >= x; i --) {
            set_pixel(image, xc + x, yc + i, color);
            set_pixel(image, xc + x, yc - i, color);
            set_pixel(image, xc - x, yc + i, color);
            set_pixel(image, xc - x, yc - i, color);
            set_pixel(image, xc + i, yc + x, color);
            set_pixel(image, xc + i, yc - x, color);
            set_pixel(image, xc - i, yc + x, color);
            set_pixel(image, xc - i, yc - x, color);
        }

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y --;
        }
        x ++;
    }
}


void draw_circle(BMP image, int xc, int yc, int radius, int thickness, RGB color, char fill, RGB fill_color) {
    int W = width(image);
    int H = height(image);
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    int rad = thickness / 2;
    
    if (thickness > max(W, H) && (radius - rad)*2 < max(W, H)) {
        for (int i = 0; i < H; i ++) {
            for (int j = 0; j < W; j ++) {
                set_pixel(image, j, i, color);
            }
        }
        if (radius > max(W, H) && fill) {
            if (rad > radius) {
                for (int i = 0; i < H; i ++) {
                    for (int j = 0; j < W; j ++) {
                        set_pixel(image, j, i, fill_color);
                    }
                }
            } else {
                draw_simple_circle(image, xc, yc, radius - rad, fill_color);
            }
        }
        return;
    }

    if (0 <= xc && xc < W && 0 <= yc && yc < H && (radius - rad) > max(W, H) && (!fill))
        return;
        
    if ((0 <= xc + radius - rad && xc + radius - rad < W) || (0 <= xc - radius + rad && xc - radius + rad < W) || (0 <= yc + radius - rad && yc + radius - rad < H) || (0 <= yc - radius + rad && yc - radius + rad < H) && (!fill)) {
        if (thickness > max(W, H)) {
            draw_circle_pattern(image, 0, xc, yc, radius - rad, 0, color);
            return;
        }
    }
    
    if (fill) {
        draw_simple_circle(image, xc, yc, radius + rad, color);
        draw_simple_circle(image, xc, yc, radius - rad, fill_color);
        return;
        
    } else {
        while (x <= y) {
            draw_simple_circle(image, xc + x, yc + y, rad, color);
            draw_simple_circle(image, xc + x, yc - y, rad, color);
            draw_simple_circle(image, xc - x, yc + y, rad, color);
            draw_simple_circle(image, xc - x, yc - y, rad, color);
            draw_simple_circle(image, xc + y, yc + x, rad, color);
            draw_simple_circle(image, xc + y, yc - x, rad, color);
            draw_simple_circle(image, xc - y, yc + x, rad, color);
            draw_simple_circle(image, xc - y, yc - x, rad, color);
    
            if (d < 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y --;
            }
            x ++;
        }
    }
}

void paving(BMP image, int x0, int y0, int x1, int y1) {
    int W = width(image);
    int H = height(image);
    int left_x, down_y, right_x, up_y, region_H, region_W;
    RGB color;
    region_H = max(y0, y1) - min(y0, y1);
    region_W = max(x0, x1) - min(x0, x1);
    int d = 1;
    
    if (region_H ==0) {
        region_H = 1;
        d = 0;
    }
        
    if (region_W == 0)
        region_W = 1;

    y0 = height(image) - y0 - 1;
    y1 = height(image) - y1 - 1;
    
    left_x = min(x0, x1);
    right_x = max(x0, x1);
    down_y = min(y0, y1);
    up_y = max(y0, y1);

    RGB ** region = malloc(region_H * sizeof(RGB*));
    for (int i = 0; i < region_H; i ++) {
        region[i] = malloc(region_W * sizeof(RGB));
        for (int j = 0; j < region_W; j ++) {
            region[i][j] = image.canvas[down_y + i + d][left_x + j];
        }
    }
    
    int count_x = W / region_W;
    if (W % region_W)
        count_x ++;
        
    int count_y = H / region_H;
    if (H % region_H)
        count_y ++;
    
    int start_x;
    int start_y;
    
    for (int i = 0; i < count_y; i ++) {
        start_x = 0;
        start_y = height(image) - i * region_H - 1;
        for (int j = 0; j < count_x; j ++) {
            start_x = j * region_W;
            
            for (int y = 0; y < region_H; y ++) {
                for (int x = 0; x < region_W; x ++) {
                    color = region[y][x];
                    set_pixel(image, start_x + x, start_y - (region_H - y - 1), color);
                }
            }

        }
    }
    
    for (int i = 0; i < region_H; i ++)
        free(region[i]);
    free(region);
}

void rotate(BMP image, int x0, int y0, int x1, int y1, int angle) {
    if (angle%90 != 0) {
        printf("The degree measure of an angle must be a multiple of 90\n");
        exit(41);
    }
    int left_x, down_y, right_x, up_y, xc, yc, X, Y, region_H, region_W;
    RGB color;
    region_H = max(y0, y1) - min(y0, y1);
    region_W = max(x0, x1) - min(x0, x1);
    xc = (x0 + x1) / 2;
    yc = (y0 + y1) / 2;

    int start_x = xc - region_H / 2;
    int start_y = height(image) - (yc - region_W / 2) - 1;
    y0 = height(image) - y0 - 1;
    y1 = height(image) - y1 - 1;
    
    left_x = min(x0, x1);
    right_x = max(x0, x1);
    down_y = min(y0, y1);
    up_y = max(y0, y1);

    RGB ** region = malloc(region_H * sizeof(RGB*));
    for (int i = 0; i < region_H; i ++) {
        region[i] = malloc(region_W * sizeof(RGB));
        for (int j = 0; j < region_W; j ++) {
            region[i][j] = image.canvas[down_y + i + 1][left_x + j];
        }
    }
    
    if ((angle - 180) % 360 == 0) {
        // 180
        for (int y = up_y; y > down_y; y --) {
            for (int x = left_x; x < right_x; x ++) {
                color = region[(up_y - y)][region_W - (x - left_x) - 1];
                set_pixel(image, x, y, color);
            }
        }
    } else {
        if ((angle - 90) % 360 == 0) {
            for (int y = 0; y < region_W; y ++) {
                for (int x = 0; x < region_H; x ++) {
                    color = region[x][y];
                    set_pixel(image, start_x + (region_H - x - 1), start_y - (region_W - y - 1), color);
                }
            }
            
        } else {
            for (int y = 0; y < region_W; y ++) {
                for (int x = 0; x < region_H; x ++) {
                    color = region[x][y];
                    set_pixel(image, start_x + x, start_y - y, color);
                }
            }
        }
    }

    for (int i = 0; i < region_H; i ++)
        free(region[i]);
    free(region);
}


void fill_left(BMP image, int x, int y, RGB color) {
    if (y >= 0 && y < height(image)) {
        for (int i = 0; i < x; i ++) {
            set_pixel(image, i, y, color);
        }
    }
}

void fill_right(BMP image, int x, int y, RGB color) {
    if (y >= 0 && y < height(image)) {
        for (int i = x + 1; i < width(image); i ++) {
            set_pixel(image, i, y, color);
        }
    }
}


void draw_circle_pattern(BMP image, int count, int xc, int yc, int radius, int thickness, RGB color) {
    int left_x, right_x, up_y, down_y, x, y, d;
    unsigned int W = width(image);
    unsigned int H = height(image);

    left_x = xc - radius;
    right_x = xc + radius;
    up_y = yc + radius;
    down_y = yc - radius;
    draw_rect(image, 0, 0, left_x, H, 0, color, 1, color);
    draw_rect(image, right_x, 0, W, H, 0, color, 1, color);
    draw_rect(image, left_x, 0, right_x, down_y, 0, color, 1, color);
    draw_rect(image, left_x, up_y, right_x, H, 0, color, 1, color);

    x = 0;
    y = radius;
    d = 3 - 2 * radius;
    while (x <= y) {
        fill_right(image, xc + x, yc + y, color);
        fill_right(image, xc + x, yc - y, color);
        fill_left(image, xc - x, yc + y, color);
        fill_left(image, xc - x, yc - y, color);
        fill_right(image, xc + y, yc + x, color);
        fill_right(image, xc + y, yc - x, color);
        fill_left(image, xc - y, yc + x, color);
        fill_left(image, xc - y, yc - x, color);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y --;
        }
        x ++;
    }
}


void draw_semicircle_pattern(BMP image, int count, int thickness, RGB color) {
    unsigned int W = width(image);
    unsigned int H = height(image);
    
    unsigned int vertical_d = H / count;
    if (H % count) 
        vertical_d ++;
    unsigned int vertical_rad = vertical_d / 2;
    if (vertical_d % 2)
        vertical_rad ++;

    unsigned int horizontal_d = W / count;
    if (W % count)
        horizontal_d ++;
    unsigned int horizontal_rad = horizontal_d / 2;
    if (horizontal_d % 2)
        horizontal_rad ++;


    //vertical
    int yc = H - vertical_rad - 2;
    for (int i = 0; i < count; i ++) {
        draw_circle(image, 0, yc, vertical_rad, thickness, color, 0, color);
        draw_circle(image, W - 1, yc, vertical_rad, thickness, color, 0, color);
        yc -= vertical_rad * 2 - 1;
    }

    //horizontal
    int xc = horizontal_rad + 1;
    for (int i = 0; i < count; i ++) {
        draw_circle(image, xc, 0, horizontal_rad, thickness, color, 0, color);
        draw_circle(image, xc, H - 1, horizontal_rad, thickness, color, 0, color);
        xc += horizontal_rad * 2 + 1;
    }
}


void draw_ornament(BMP image, int count, int thickness, RGB color, int pattern) {
    if (pattern == 0) {
        draw_rect_pattern(image, count, thickness, color);
    } else if (pattern == 1) {
        unsigned int W = width(image);
        unsigned int H = height(image);
        int xc = W / 2;
        int yc = H / 2;
        int radius = min(xc, yc);
        draw_circle_pattern(image, count, xc, yc, radius, thickness, color);
    } else {
        draw_semicircle_pattern(image, count, thickness, color);
    }
}


void print_file_header(BitmapFileHeader header) {
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header) {
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width:     \t%x (%u)\n", header.width, header.width);
    printf("height:    \t%x (%u)\n", header.height, header.height);
    printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
} 

void print_info(BMP image) {
    print_file_header(image.bmfh);
    print_info_header(image.bmih);
}

void print_help() {
    FILE * f = fopen("Help", "r");
    if (f) {
        char string[1024];
        while(fgets(string, 100, f) != NULL) {
            printf("%s", string);
        }
        fclose(f);
    } else {
        printf("The project is damaged, the 'Help' file was not found\n");
    }
}

unsigned int height(BMP image) {
    return image.bmih.height;
}

unsigned int width(BMP image) {
    return image.bmih.width;
}


struct Input CLI_processing(int argc, char ** argv) {

    struct Input task = {0};
    task.input_file[0] = '\0';
    task.output_file[0] = '\0';
    if (strstr(argv[argc - 1], ".bmp")) {
        strcpy(task.input_file, argv[argc - 1]);
    }
    strcpy(task.output_file, "out.bmp");

    char * options = "prcfti:o:h";
    struct option long_options[] = {

        // main flags
        {"paving", no_argument, 0, 'p'},
        {"rect", no_argument, 0, 'r'},
        {"circle", no_argument, 0, 'c'},
        {"ornament", no_argument, 0, 'f'},
        {"rotate", no_argument, 0, 't'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {"info", no_argument, 0, 0},

        // task properties
        {"left_up", required_argument, 0, 1},
        {"right_down", required_argument, 0, 2},
        {"thickness", required_argument, 0, 3},
        {"color", required_argument, 0, 4},
        {"fill", no_argument, 0, 5},
        {"fill_color", required_argument, 0, 6},
        {"center", required_argument, 0, 7},
        {"radius", required_argument, 0, 8},
        {"count", required_argument, 0, 9},
        {"angle", required_argument, 0, 10},
        {"pattern", required_argument, 0, 11},

        {0, 0, 0, 0}
	};

	int option;
	while ((option = getopt_long(argc, argv, options, long_options, NULL)) != -1) {
        switch (option) {

            case 1:
                if (sscanf(optarg, "%d.%d", &task.x0, &task.y0) == 2)
                    task.flag_left_up = 1;
                break;

            case 2:
                if (sscanf(optarg, "%d.%d", &task.x1, &task.y1) == 2)
                    task.flag_right_down = 1;
                break;

            case 3:
                if (sscanf(optarg, "%d", &task.thickness)) {
                    if (task.thickness < 0) {
                        printf("Negative thickness entered\n");
                        exit(41);
                    }
                    task.flag_thickness = 1;
                }
                break;

            case 4:
                if (sscanf(optarg, "%hhu.%hhu.%hhu", &task.color.r, &task.color.g, &task.color.b) == 3)
                    task.flag_color = 1;
                break;

            case 5:
                task.fill = 1;
                break;

            case 6:
                if (sscanf(optarg, "%hhu.%hhu.%hhu", &task.fill_color.r, &task.fill_color.g, &task.fill_color.b) == 3)
                    task.flag_fill_color = 1;
                break;

            case 7:
                if (sscanf(optarg, "%d.%d", &task.xc, &task.yc) == 2)
                    task.flag_center = 1;
                break;

            case 8:
                if (sscanf(optarg, "%d", &task.radius)) {
                    if (task.radius < 0) {
                        printf("Negative radius entered\n");
                        exit(41);
                    }
                    task.flag_radius = 1;
                }
                break;

            case 9:
                if (sscanf(optarg, "%d", &task.count)) {
                    if (task.count < 0) {
                        printf("Negative count entered\n");
                        exit(41);
                    }
                    task.flag_count = 1;
                }
                break;

            case 10:
                if (sscanf(optarg, "%d", &task.angle))
                    task.flag_angle = 1;
                break;

            case 11:
                if (strstr(optarg, "rectangle")) {
                    task.pattern = 0;
                } else if (strstr(optarg, "semicircles")) {
                    task.pattern = 2;
                } else if (strstr(optarg, "circle")) {
                    task.pattern = 1;
                } else {
                    printf("No such pattern exists\n");
                    exit(41);
                }
                task.flag_pattern = 1;
                break;
                
            case 'p':
                task.flag_paving = 1;
                break;
                
            case 'i':
                strcpy(task.input_file, optarg);
                break;

            case 'o':
                strcpy(task.output_file, optarg);
                break;

            case 'r':
                task.flag_rectangle = 1;
                break;

            case 'c':
                task.flag_circle = 1;
                break;

            case 'f':
                task.flag_ornament = 1;
                break;

            case 't':
                task.flag_rotation = 1;
                break;

            case 'h':
                task.flag_help = 1;
                break;

            case 0:
                task.flag_info = 1;
                break;

            default:
                printf("No such flags exists\n");
                break;
        }
	}

	int count_task = task.flag_info + task.flag_help + task.flag_rectangle + task.flag_circle + task.flag_ornament + task.flag_rotation;
    if (count_task == 0) {
        task.flag_help = 1;
    } else if (count_task > 1) {
        printf("More than one task selected\n");
        exit(41);
    }

    if (task.flag_left_up && task.flag_right_down) {
        int min_x = min(task.x0, task.x1);
        int max_x = max(task.x0, task.x1);
        task.x0 = min_x;
        task.x1 = max_x;
        int min_y = min(task.y0, task.y1);
        int max_y = max(task.y0, task.y1);
        task.y0 = min_y;
        task.y1 = max_y;
    }

    return task;
}


int all_data_rectangle(struct Input task) {
    return (task.flag_rectangle && task.flag_left_up && task.flag_right_down && task.flag_thickness && task.flag_color) 
    && ((task.fill && task.flag_fill_color) || (!task.fill));
}

int all_data_circle(struct Input task) {
    return (task.flag_circle && task.flag_center && task.flag_thickness && task.flag_color) 
    && ((task.fill && task.flag_fill_color) || (!task.fill));
}

int all_data_ornament(struct Input task) {
    return (task.flag_ornament && task.flag_pattern && task.flag_color && task.flag_count && task.flag_thickness);
}

int all_data_rotate(struct Input task) {
    return (task.flag_rotation && task.flag_left_up && task.flag_right_down && task.flag_angle);
}

int all_data_paving(struct Input task) {
    return (task.flag_paving && task.flag_left_up && task.flag_right_down);
}

