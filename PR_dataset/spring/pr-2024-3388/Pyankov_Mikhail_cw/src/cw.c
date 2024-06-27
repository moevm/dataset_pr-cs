#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include<regex.h>
#include<math.h>

#define no_argument            0
#define required_argument      1
#define SIZE 10
#define COMMAND_SIZE 50
#define GROUPS 1
#define LEVELING 4
#define BM 19778
#define BA 16706
#define CI 674115
#define CP 675907 
#define IC 672585
#define PT 676944
#define BITS_PER_PIXEL 24
#define COMPRESSION 0
#define NEW_FILE_NAME "./out.bmp"
#define HELP_MESSAGE "Course work for option LEVELING.6, created by Pyankov Mikhail\nflags:\n\n--line :\n--start %d.%d --end %d.%d --color %d.%d.%d --thickness %d\n\n--inverse_circle :\n--center %d.%d --radius %d\n\n--trim :\n--left_up %d.%d --right_down %d.%d"
#define DEFAULT_MESSAGE "Use flags, for information put flag -h"

#define REG_COORDS "^-?[0-9]+\\.-?[0-9]+$"
#define REG_COORDS_EXTENDED "^-?[0-9]+\\.-?[0-9]+(\\.-?[0-9]+)+$"

#define REG_LINE_COLOR "^[0-9]+\\.[0-9]+\\.[0-9]+$"
#define REG_LINE_COLOR_EXTENDED "^[0-9]+\\.[0-9]+\\.[0-9]+(\\.-?[0-9]+)+$"

#define REG_ONE_ARG "^[0-9]+$"
#define REG_ONE_ARG_EXTENDED "^[0-9]+(\\.-?[0-9]+)+$"

#define FILE_NAME "[0-9A-z~@#\\$\\^-_\\(\\)\\{\\}'`]+\\.[0-9A-z~@#\\$\\^-_\\(\\)\\{\\}'`]+$"

#define INVALID_COMMAND "Invalid command!"
#define EXTENDED_COMMAND_START "Too much args for "
#define EXTENDED_COMMAND_END " flag, only first will be write!"

#define LINE_COMMAND_ERROR "Missed args for --line flag!"
#define INVERSE_CIRCLE_COMMAND_ERROR "Missed args for --inverse_circle flag!"
#define TRIM_COMMAND_ERROR "Missed args for --trim flag!"
#define TRIM_COORDS_ERROR "--trim coords error!"

#define FILE_NAME_FORGOTTEN "Put file_name!"
#define FILE_NAME_ERROR "There is no file with that name!"
#define FILE_TYPE_ERROR "File corrupted!"
#define OUTPUT_FILE_ERROR "Output file name error, default name will be out.BMP!"
#define SAME_INP_OUT_FILES "Input and output files are same!"
#define ERROR_CODE 40

#pragma pack (push, 1)

typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved_first;
    unsigned short reserved_second;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
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
} Rgb;

#pragma pack(pop)

void print_file_header(BitmapFileHeader header)
{
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved_first:\t%x (%hu)\n", header.reserved_first, header.reserved_first);
    printf("reserved_second:\t%x (%hu)\n", header.reserved_second, header.reserved_second);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header)
{
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

void extend_command_message(char* command)
{
    char* message = malloc(COMMAND_SIZE);
    strcpy(message, EXTENDED_COMMAND_START);
    strcat(message, command);
    strcat(message, EXTENDED_COMMAND_END);
    puts(message);
}

int check_args(char* optarg, const char* exp, const char* ext_exp)
{
    regex_t regex_compiled;
    regmatch_t group_array[GROUPS];

    regcomp(&regex_compiled, exp, REG_EXTENDED);
    if(regexec(&regex_compiled, optarg, GROUPS, group_array, 0) == 0)
    return 1;
    regcomp(&regex_compiled, ext_exp, REG_EXTENDED);
    if(regexec(&regex_compiled, optarg, GROUPS, group_array, 0) == 0)
    return 2;
    return 0;
}

int check_bmp(char* file_name)
{
    FILE *f = fopen(file_name, "rb");
    BitmapFileHeader bmfh;
	BitmapInfoHeader bmif;
    fread(&bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(&bmif, 1, sizeof(BitmapInfoHeader), f);
    if((bmfh.signature == BM || bmfh.signature == BA || bmfh.signature == CI || bmfh.signature == CP || bmfh.signature == IC || bmfh.signature == PT)
     && bmif.bitsPerPixel == BITS_PER_PIXEL && bmif.compression == COMPRESSION);
    return 1;
    return 0;
}

int check_file_name(char* file_name)
{
    FILE *f = fopen(file_name, "rb");
    if(f == NULL)
    return 0;
    return 1;
}

int check_file_str(char* file_name)
{
    regex_t regex_compiled;
    regmatch_t group_array[GROUPS];

    regcomp(&regex_compiled, FILE_NAME, REG_EXTENDED);
    if(regexec(&regex_compiled, file_name, GROUPS, group_array, 0) == 0)
    return 1;
    return 0;
}

Rgb** read_bmp(char* file_name, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif)
{
    FILE *f = fopen(file_name, "rb");
    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);
    unsigned int img_height = bmif->height;
    unsigned int img_width = bmif->width;
    Rgb** arr = malloc(img_height * sizeof(Rgb*));
    for(int i = 0; i < img_height; i++)
    {
        arr[img_height - i - 1] = malloc(img_width * sizeof(Rgb) + (LEVELING - ((img_width * sizeof(Rgb)) %LEVELING) ) % LEVELING);
        fread(arr[img_height - i - 1], 1, img_width * sizeof(Rgb) + (LEVELING - ((img_width * sizeof(Rgb)) %LEVELING) ) % LEVELING,f);
    }
    fclose(f);
    return arr;
}

int circle_func(int x, int y, int x0, int y0, int r)
{
    return ((x - x0) * (x - x0) + (y - y0) * (y - y0)) < (r*r);
}

void set_pixel(Rgb** arr, int x, int y, int* color, int img_height, int img_width)
{
    if(y >= img_height || y < 0 || x >= img_width || x < 0)
    return;
    arr[y][x].r = *(color);
    arr[y][x].g = *(color + 1);
    arr[y][x].b = *(color + 2);
}

void Circle(Rgb** arr, int X1, int Y1, int* color, int R, int img_height, int img_width)
{
	int x = 0;
    int y = R;
    int delta = 1 - 2 * R;
    int error = 0;
    while (y >= x)
    {
        set_pixel(arr, X1 + x, Y1 + y, color, img_height, img_width);
        set_pixel(arr, X1 + x, Y1 - y, color, img_height, img_width);
        set_pixel(arr, X1 - x, Y1 + y, color, img_height, img_width);
        set_pixel(arr, X1 - x, Y1 - y, color, img_height, img_width);
        set_pixel(arr, X1 + y, Y1 + x, color, img_height, img_width);
        set_pixel(arr, X1 + y, Y1 - x, color, img_height, img_width);
        set_pixel(arr, X1 - y, Y1 + x, color, img_height, img_width);
        set_pixel(arr, X1 - y, Y1 - x, color, img_height, img_width);
        error = 2 * (delta + y) - 1;
        if((delta < 0) && (error <= 0))
        {
            delta += 2 * ++x + 1;
            continue;
        }
            
        if((delta > 0) && (error > 0))
        {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }
}

void draw_line(Rgb** arr, int img_height, int img_width, int x0, int y0, int x1, int y1, int* color, int thickness)
{
    int dx = (x1 - x0 >= 0 ? 1 : -1);
    int dy = (y1 - y0 >= 0 ? 1 : -1);
    int lengthX = abs(x1 - x0);
    int lengthY = abs(y1 - y0);
    int length = (lengthX - lengthY > 0 ? lengthX : lengthY);
    if (length == 0)
    Circle(arr, x0, y0, color, thickness, img_height, img_width);
    int x = x0;
    int y = y0;
    if(lengthY <= lengthX)
    {
        int d = -lengthX;
        length++;
        while (length--)
        {
            if(x >= 0 && y >= 0 && x < img_width && y < img_height);
            Circle(arr, x, y, color, thickness, img_height, img_width);
            x += dx;
            d += 2 * lengthY;
            if(d > 0)
            {
                d -= 2 * lengthX;
                y += dy;
            }
        }
    }
    else
    {
        int d = -lengthY;
        length++;
        while (length--)
        {
            if(x >= 0 && y >= 0 && x < img_width && y < img_height);
            Circle(arr, x, y, color, thickness, img_height, img_width);
            y += dy;
            d += 2 * lengthX;
            if(d > 0)
            {
                d -= 2 * lengthY;
                x += dx;
            }
        }
    }
}

void invert_circle(Rgb** arr, int img_height, int img_width, int x0, int y0, int r)
{
    for(int i = 0; i < img_height; i++)
    {
        for(int j = 0; j < img_width; j++)
        {
            if(circle_func(j, i, x0, y0, r))
            {
                int color[3] = {255 - arr[i][j].r, 255 - arr[i][j].g, 255 - arr[i][j].b};
                set_pixel(arr, j, i, color, img_height, img_width);
            }
        }
    }
}

int rectangle_func(int x, int y, int x0, int y0, int x1, int y1)
{
    return (x >= x0 && y >= y0) && (x <= x1 && y <= y1);
}

Rgb** trim(Rgb** arr, BitmapInfoHeader* bmif, BitmapFileHeader* bmfh, int x0, int y0, int x1, int y1)
{
    int img_height = bmif->height;
    int img_width = bmif->width;

    if(x0 >= x1 || y0 >= y1 || x1 < 0 || y1 < 0 || y0 > img_height || x0 > img_width)
    {
        puts(TRIM_COORDS_ERROR);
        exit(ERROR_CODE);
    }

    x0 = x0 >= 0 ? x0 : 0;
    y0 = y0 >= 0 ? y0 : 0;
    y1 = y1 < img_height ? y1 : img_height;
    x1 = x1 < img_width ? x1 : img_width;
    int new_W = x1 - x0;
    int new_H = y1 - y0;
    Rgb** new_arr = malloc(new_H * sizeof(Rgb *));
    for (int i = 0; i < new_H; i++)
    {
        new_arr[i] = malloc(new_W * sizeof(Rgb) + (LEVELING - ((new_W * sizeof(Rgb)) %LEVELING) ) % LEVELING);
    }
    for(int i = 0; i < img_height; i++)
    {
        for(int j = 0; j < img_width; j++)
        {
            if(rectangle_func(j, i, x0, y0, x1, y1))
            {
                int color[3] = {arr[i][j].r, arr[i][j].g, arr[i][j].b}; 
                set_pixel(new_arr, j - x0, i - y0, color, new_H, new_W);
            }
        }
    }
    bmif->height = new_H;
    bmif->width = new_W;
    bmfh->filesize = (new_H)*((new_W)*sizeof(Rgb) + (LEVELING - ((new_W * sizeof(Rgb)) %LEVELING) ) % LEVELING);
    bmif->imageSize = new_H*new_W;
    return new_arr;
}

void write_bmp(char* file_name, Rgb** arr, int img_height, int img_width, BitmapFileHeader bmfh, BitmapInfoHeader bmif)
{
    FILE *ff = fopen(file_name, "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    for(int i = 0; i < img_height; i++)
    {
        fwrite(arr[img_height - i - 1], 1, img_width * sizeof(Rgb) + (LEVELING - ((img_width * sizeof(Rgb)) %LEVELING) ) % LEVELING, ff);
    }
    fclose(ff);
} 

void romb_draw_line(Rgb** arr, int img_height, int img_width, int x0, int y0, int x1, int y1, int* color, int thickness)
{
    draw_line(arr, img_height, img_width, x0, y0, x1, y1, color, (thickness-1)/2);
    if(thickness % 2 == 0)
    {
        if(fabs((float)(x0 - x1)) <= fabs((float)(y0 - y1)))
        draw_line(arr, img_height, img_width, x0+1, y0, x1+1, y1, color, (thickness-1)/2);
        else
        draw_line(arr, img_height, img_width, x0, y0+1, x1, y1+1, color, (thickness-1)/2);
    }
}

int fill_romb(Rgb** arr, int img_height, int img_width, int xv, int yv, int* color, int** used)
{
    if(xv < img_height && xv >= 0 && yv < img_width && yv >=0 && !used[yv][xv] && !(arr[yv][xv].r == color[0] && arr[yv][xv].g == color[1] && arr[yv][xv].b == color[2]))
    {
        set_pixel(arr, xv, yv, color, img_height, img_width);
        used[yv][xv] = 1;
        return fill_romb(arr, img_height, img_width, xv+1, yv, color, used) || fill_romb(arr, img_height, img_width, xv-1, yv, color, used) ||
        fill_romb(arr, img_height, img_width, xv, yv+1, color, used) || fill_romb(arr, img_height, img_width, xv, yv-1, color, used);
    }
    else
    return 0;
}

void romb(Rgb** arr, int img_height, int img_width, int xv, int yv, int size, int* color)
{
    int thickness = 1;
    double sqrt2 = 1.41421356237;

    double x0 = xv;
    double y0 = yv;

    double x1 = xv-size/sqrt2;
    double y1 = yv+size/sqrt2;

    double x2 = xv;
    double y2 = yv+2*size/sqrt2;

    double x3 = xv+size/sqrt2;
    double y3 = yv+size/sqrt2;


    romb_draw_line(arr, img_height, img_width, x0, y0, x1, y1, color, (thickness-1)/2);
    romb_draw_line(arr, img_height, img_width, x1, y1, x2, y2, color, (thickness-1)/2);
    romb_draw_line(arr, img_height, img_width, x2, y2, x3, y3, color, (thickness-1)/2);
    romb_draw_line(arr, img_height, img_width, x3, y3, x0, y0, color, (thickness-1)/2);

    int** used = malloc(sizeof(int*) * img_height);
    for(int i = 0; i < img_height; i++)
    {
        used[i] = malloc(sizeof(int) * img_width);
    }

    for(int i = 0; i < img_height; i++)
    {
        for(int j = 0; j < img_width; j ++)
        used[i][j] = 0;
    }

    fill_romb(arr, img_height, img_width, xv, yv+2, color, used);
    fill_romb(arr, img_height, img_width, xv, yv+size/sqrt2, color, used);
    fill_romb(arr, img_height, img_width, xv, yv+10, color, used);
}

void coords_init(char* optarg, int* x, int* y, int* flag, int* cnt_commands, char* flag_msg)
{
    if(check_args(optarg, REG_COORDS, REG_COORDS_EXTENDED))
        sscanf(optarg, "%d.%d", x, y);
    if(check_args(optarg, REG_COORDS, REG_COORDS_EXTENDED) == 2)
        extend_command_message(flag_msg);
    if(!check_args(optarg, REG_COORDS, REG_COORDS_EXTENDED))
    {
        puts(INVALID_COMMAND);
        exit(ERROR_CODE);
    }
    *flag = 1;
    *cnt_commands+=2;
}

void one_arg_init(char* optarg, int* x, int* flag, int* cnt_commands, char* flag_msg)
{
    if(check_args(optarg, REG_ONE_ARG, REG_ONE_ARG_EXTENDED))
        sscanf(optarg, "%d", x);
    if(check_args(optarg, REG_ONE_ARG, REG_ONE_ARG_EXTENDED) == 2)
        extend_command_message(flag_msg);
    if(!check_args(optarg, REG_ONE_ARG, REG_ONE_ARG_EXTENDED))
    {
        puts(INVALID_COMMAND);
        exit(ERROR_CODE);
    }
    *flag = 1;
    *cnt_commands+=2;
}

void color_init(char* optarg, int* color, int* flag, int* cnt_commands, char* flag_msg)
{
    if(check_args(optarg, REG_LINE_COLOR, REG_LINE_COLOR_EXTENDED))
        sscanf(optarg, "%d.%d.%d", &color[0], &color[1], &color[2]);
    if(check_args(optarg, REG_LINE_COLOR, REG_LINE_COLOR_EXTENDED) == 2)
        extend_command_message(flag_msg);
    if(!check_args(optarg, REG_LINE_COLOR, REG_LINE_COLOR_EXTENDED) || (color[0] > 255 || color[1] > 255 || color[2] > 255))
    {
        puts(INVALID_COMMAND);
        exit(ERROR_CODE);
    }
    *flag = 1;
    *cnt_commands+=2;
}
void solve(int argc, char** argv)
{
    char* file_name;
    int file_name_flag = 0;
    char* new_file_name = NEW_FILE_NAME;

	BitmapFileHeader bmfh;
	BitmapInfoHeader bmif;
	Rgb** array;

    char *opts = "hls:e:c:t:IC:r:TL:R:o:i:f";
    int longidx;
    struct option longopts[] = 
    {
        {"help", no_argument, NULL, 'h'},
        {"line", no_argument, NULL, 'l'},
        {"start", required_argument, NULL, 's'},
        {"end", required_argument, NULL, 'e'},
        {"color", required_argument, NULL, 'c'},
        {"thickness", required_argument, NULL, 't'},
        {"inverse_circle", no_argument, NULL, 'I'},
        {"center", required_argument, NULL, 'C'},
        {"radius", required_argument, NULL, 'r'},
        {"trim", no_argument, NULL, 'T'},
        {"left_up", required_argument, NULL, 'L'},
        {"right_down", required_argument, NULL, 'R'},
        {"info", no_argument, NULL, 'f'},
        {"output", required_argument, NULL, 'o'},
        {"input", required_argument, NULL, 'i'},
        {"square_rhombus", no_argument, NULL, 'S'},
        {"upper_vertex", required_argument, NULL, 'u'},
        {"size", required_argument, NULL, 'z'},
        {"fill_color", required_argument, NULL, 'F'},
        {NULL, no_argument, NULL, 0 }
    };

    int opt = getopt_long(argc, argv, opts, longopts, &longidx);

    if(argc == 1)
    {
        puts(DEFAULT_MESSAGE);
        exit(0);
    }

    int cnt_commands = 0;

    int info_flag = 0;

    int x0,y0,x1,y1,thickness;
    int color[3];
    int line_flag = 0; int start_flag = 0; int end_flag = 0; int thickness_flag = 0; int color_flag = 0;

    int xc,yc,rad;
    int center_flag = 0; int rad_flag = 0; int inverse_circle_flag = 0;
    
    int xl,yl,xr,yr;
    int left_flag = 0; int right_flag = 0; int trim_flag = 0;

    int rombus_flag = 0;
    int vert_flag = 0;
    int size_flag = 0;
    int fill_flag = 0;
    int fill_color[3];
    int rb_size;
    int xv, yv;

    while(opt != -1)
    {
        switch (opt)
        {
            case('h'):
            {
                puts(HELP_MESSAGE);
                exit(0);
            }
            case('f'):
            {
                info_flag = 1;
                cnt_commands++;
                break;
            }
            case('i'):
            {
                file_name_flag = 1;
                file_name = optarg;
                cnt_commands+=2;
                break;
            }
            case('o'):
            {
                cnt_commands+=2;
                if(check_file_str(optarg))
                {
                    new_file_name = optarg;
                }
                else
                puts(OUTPUT_FILE_ERROR);
                break;
            }
            case('l'):
            {
                line_flag = 1;
                cnt_commands++;
                break;
            }
            case('s'):
            {
                coords_init(optarg, &x0, &y0, &start_flag, &cnt_commands, "--start");
                break;
            }
            case('e'):
            {
                coords_init(optarg, &x1, &y1, &end_flag, &cnt_commands, "--end");
                break;
            }
            case('c'):
            {
                color_init(optarg, color, &color_flag, &cnt_commands, "--color");
                break;
            }
            case('t'):
            {
                one_arg_init(optarg, &thickness, &thickness_flag, &cnt_commands, "--thickness");
                break;
            }
            case('I'):
            {
                inverse_circle_flag = 1;
                cnt_commands++;
                break;
            }
            case('C'):
            {
                coords_init(optarg, &xc, &yc, &center_flag, &cnt_commands, "--center");
                break;
            }
            case('r'):
            {
                one_arg_init(optarg, &rad, &rad_flag, &cnt_commands, "--radius");
                break;
            }
            case('T'):
            {
                trim_flag = 1;
                cnt_commands++;
                break;
            }
            case('L'):
            {
                coords_init(optarg, &xl, &yl, &left_flag, &cnt_commands, "--left_up");
                break;
            }
            case('R'):
            {
                coords_init(optarg, &xr, &yr, &right_flag, &cnt_commands, "--right_down");
                break;
            }
            case('S'):
            {
                rombus_flag = 1;
                break;
                cnt_commands++;
            }
            case('u'):
            {
                coords_init(optarg, &xv, &yv, &vert_flag, &cnt_commands, "--upper_vertex");
                break;
            }
            case('z'):
            {
                one_arg_init(optarg, &rb_size, &size_flag, &cnt_commands, "--size");
                break;
            }
            case('F'):
            {
                color_init(optarg, fill_color, &fill_flag, &cnt_commands, "--color");
                break;
            }
            default:
            {
                puts(INVALID_COMMAND);
                exit(ERROR_CODE);
            }
        }
        opt = getopt_long(argc, argv, opts, longopts, &longidx);
    }

    if(!file_name_flag)
    {
        if(check_file_str(argv[argc-1]) && cnt_commands == argc - 2)
        file_name = argv[argc-1];
        else
        {
            puts(FILE_NAME_FORGOTTEN);
            exit(ERROR_CODE);
        }
    }
    if(!strcmp(file_name, new_file_name))
    {
        puts(SAME_INP_OUT_FILES);
        exit(ERROR_CODE);
    }
    if(!check_file_name(file_name))
    {
        puts(FILE_NAME_ERROR);
        exit(ERROR_CODE);
    }
    if(!check_bmp(file_name))
    {
        puts(FILE_TYPE_ERROR);
        exit(ERROR_CODE);
    }

    array = read_bmp(file_name, &bmfh, &bmif);
    if(info_flag)
    {
        print_file_header(bmfh);
        printf("\n");
        print_info_header(bmif);
    }
    if(line_flag)
    {
        if(start_flag && end_flag && color_flag && thickness_flag)
        {
            draw_line(array, bmif.height, bmif.width, x0, y0, x1, y1, color, (thickness-1)/2);
            if(thickness % 2 == 0)
            {
                if(fabs((float)(x0 - x1)) <= fabs((float)(y0 - y1)))
                draw_line(array, bmif.height, bmif.width, x0+1, y0, x1+1, y1, color, (thickness-1)/2);
                else
                draw_line(array, bmif.height, bmif.width, x0, y0+1, x1, y1+1, color, (thickness-1)/2);
            }
        }
        else
        {
            puts(LINE_COMMAND_ERROR);
            exit(ERROR_CODE);
        }
    }
    if(inverse_circle_flag)
    {
        if(center_flag && rad_flag)
        invert_circle(array, bmif.height, bmif.width, xc, yc, rad);
        else
        {
            puts(INVERSE_CIRCLE_COMMAND_ERROR);
            exit(ERROR_CODE);
        }
    }
    if(trim_flag)
    {
        if(left_flag && right_flag)
        array = trim(array, &bmif, &bmfh, xl, yl, xr, yr);
        else
        {
            puts(INVERSE_CIRCLE_COMMAND_ERROR);
            exit(ERROR_CODE);
        }
    }
    if(rombus_flag)
    {
        if(size_flag && vert_flag && fill_flag)
        {
            romb(array, bmif.height, bmif.width, xv, yv, rb_size, fill_color);
        }
        else
        {
            puts("SQUARE_ERROR!");
            exit(ERROR_CODE);
        }
    }
    if(!info_flag)
    write_bmp(new_file_name, array, bmif.height, bmif.width, bmfh, bmif);
}

int main(int argc, char** argv)
{
    solve(argc, argv);
    exit(0);
}
