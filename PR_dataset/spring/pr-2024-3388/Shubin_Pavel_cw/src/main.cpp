#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <vector>
#include <getopt.h>
#include <string>

#define ERROR_COLOR "Invalid color, must be 0-255"
#define ERROR_NUMBER_ARGS "Invalid number of arguments"
#define ERROR_INVALID_COLOR_ARGS "Not enough color args"
#define ERROR_NO_START_COORDS "No start coords"
#define ERROR_NO_END_COORDS "No end coords"
#define ERROR_INVALID_THICKNESS "Invalid thickness"
#define ERROR_NO_LEFT_UP_COORDS "No left_up coords"
#define ERROR_NO_RIGHT_DOWN_COORDS "No right_down coords"
#define ERROR_NO_PENTAGRAM_CENTER_COORDS "No pentagram center coords"
#define ERROR_INVALID_RADIUS "Missing or invalid radius"
#define ERROR_INVALID_SIZE "Invalid size"
#define ERROR_INPUT_OUTPUT_SAME "Input and output name are the same"
#define ERROR_THICKNESS_NOT_SET "Thickness not set"
#define ERROR_MISSING_AXIS "Missing axis"
#define ERROR_SIGNATURE "Invalid file signature"
#define ERROR_BMP_FORMAT "Invalid BMP format"
#define ERROR_OFFSET "Invalid pixel offset"
#define ERROR_HEADER_SIZE "Invalid header size"
#define ERROR_HELP "Could not open file"
#define CORRECT_SIGNATURE 0x4D42
#define CORRECT_BITS 24
#define CORRECT_OFFSET 54
#define CORRECT_HEADER_SIZE 40
#define CORRECT_COMPRESSION 0
#define CORRECT_PLANES 1
#define CORRECT_COLOR_COUNT 3
#define CORRECT_COORDS_COUNT 2
#define ERROR 1
#define SUCCESS 0
#define INPUT_OUTPUT_ERROR_CODE 40
#define AXIS_ERROR_CODE 41
#define MIRROR_COORDS_ERROR_CODE 42
#define START_COORDS_ERROR_CODE 43
#define END_COORDS_ERROR_CODE 44
#define SIZE_ERROR_CODE 45
#define P_CENTER_ERROR_CODE 46
#define RADIUS_ERROR_CODE 47
#define THICKNESS_ERROR_CODE 48
#define COLOR_ERROR_CODE 49
#define INVALID_AXIS '\0'

#pragma pack(push, 1)
typedef struct BitmapFileHeader{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct BitmapInfoHeader{
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

typedef struct Rgb{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;
#pragma pack(pop)

void print_error_msg(const std::string &msg, int exit_code);
void print_help();
void check_color(int red, int green, int blue);

class Argument_Parser{
public:
    std::string input_file_name;
    std::string output_file_name;
    int start_x, start_y, end_x, end_y, size, left_up_x, left_up_y, right_down_x, right_down_y, p_center_x, p_center_y, p_radius;
    int thickness;
    Rgb color;
    char axis;
    bool info, line, pentagram, mirror, blur;

    Argument_Parser();
    void parse(int argc, char *argv[]);
private:
    void parse_color(const char* optarg);
    void parse_coords(const char* optarg, int& x, int& y, const char* error_msg, int error_code);
};
Argument_Parser::Argument_Parser() {
    output_file_name = "out.bmp";
    thickness = -1;
    axis = INVALID_AXIS;
    info = false;
    line = false;
    pentagram = false;
    mirror = false;
    blur = false;
}

void Argument_Parser::parse_color(const char *optarg) {
    int red, green, blue;
    int cnt_color = sscanf(optarg, "%d.%d.%d", &red, &green, &blue);
    if (cnt_color != CORRECT_COLOR_COUNT) {
        print_error_msg(ERROR_INVALID_COLOR_ARGS, COLOR_ERROR_CODE);
    }
    check_color(red, green, blue);
    color.r = static_cast<unsigned char>(red);
    color.g = static_cast<unsigned char>(green);
    color.b = static_cast<unsigned char>(blue);
}
void Argument_Parser::parse_coords(const char *optarg, int &x, int &y, const char *error_msg, int error_code) {
    int cnt_coords = sscanf(optarg, "%d.%d", &x, &y);
    if (cnt_coords != CORRECT_COORDS_COUNT) {
        print_error_msg(error_msg, error_code);
    }
}
void Argument_Parser::parse(int argc, char **argv) {
    int option = 0;
    int ind = 0;
    struct option long_options[]= {
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},
            {"info", no_argument, NULL, 'I'},
            {"help", no_argument, NULL, 'h'},

            {"color", required_argument, NULL, 'c'},
            {"thickness", required_argument, NULL, 't'},

            {"line", no_argument, NULL, 'l'},
            {"start", required_argument, NULL, 's'},
            {"end", required_argument, NULL, 'e'},

            {"mirror", no_argument, NULL, 'm'},
            {"axis", required_argument, NULL, 'a'},
            {"left_up", required_argument, NULL, 'u'},
            {"right_down", required_argument, NULL, 'd'},

            {"pentagram", no_argument, NULL, 'p'},
            {"center", required_argument, NULL, 'C'},
            {"radius", required_argument, NULL, 'r'},

            {"blur", no_argument, NULL, 'b'},
            {"size", required_argument, NULL, 'S'},
            {0, 0, 0, 0}
    };
    std::string flags = "Ihlmpbi:o:c:t:s:e:a:u:d:C:r:S:";
    option = getopt_long(argc, argv, flags.c_str(), long_options, &ind);
    while(option!=-1){
        switch (option) {
            case 'i':
                input_file_name = optarg;
                break;
            case 'o':
                output_file_name = optarg;
                break;
            case 'c':
                parse_color(optarg);
                break;
            case 'I':
                info = true;
                break;
            case 'h':
                print_help();
                exit(SUCCESS);
            case 'l':
                line = true;
                break;
            case 'm':
                mirror = true;
                break;
            case 'p':
                pentagram = true;
                break;
            case 's':
                parse_coords(optarg, start_x, start_y, ERROR_NO_START_COORDS, START_COORDS_ERROR_CODE);
                break;
            case 'e':
                parse_coords(optarg, end_x, end_y, ERROR_NO_END_COORDS, END_COORDS_ERROR_CODE);
                break;
            case 't':
                thickness = atoi(optarg);
                if(thickness <=0){
                    print_error_msg(ERROR_INVALID_THICKNESS, THICKNESS_ERROR_CODE);
                }
                break;
            case 'a':
                axis = optarg[0];
                break;
            case 'u':
                parse_coords(optarg, left_up_x, left_up_y, ERROR_NO_LEFT_UP_COORDS, MIRROR_COORDS_ERROR_CODE);
                break;
            case 'd':
                parse_coords(optarg, right_down_x, right_down_y, ERROR_NO_RIGHT_DOWN_COORDS, MIRROR_COORDS_ERROR_CODE);
                break;
            case 'C':
                parse_coords(optarg, p_center_x, p_center_y, ERROR_NO_PENTAGRAM_CENTER_COORDS, P_CENTER_ERROR_CODE);
                break;
            case 'r':
                p_radius = atoi(optarg);
                if(p_radius <= -1){
                    print_error_msg(ERROR_INVALID_RADIUS, RADIUS_ERROR_CODE);
                }
                break;
            case 'b':
                blur = true;
                break;
            case 'S':
                size = atoi(optarg);
                if(size<=0){
                    print_error_msg(ERROR_INVALID_SIZE, SIZE_ERROR_CODE);
                }
                break;
            default:
                exit(0);
        }
        option = getopt_long(argc, argv, flags.c_str(), long_options, &ind);
    }
}
class BMP{
private:
    BitmapFileHeader* bmfh;
    BitmapInfoHeader* bmif;
    Rgb** array;
    int img_height;
    int img_width;
public:
    BMP(const char* filename);
    ~BMP();
    void check_bmp();
    void save_bmp(const char* file_name);
    void set_pixel(int x, int y, Rgb color);
    void draw_line(int x_start, int y_start, int x_end, int y_end, int thickness, Rgb color);
    void draw_circle(int x_center, int y_center, int radius, Rgb color);
    void draw_pentagram(int cx, int cy, int radius, int thickness,Rgb color);
    void draw_thick_circle(int cx, int cy, int radius, int thickness, Rgb color);
    void print_file_header();
    void print_info_header();
    unsigned int calculate_padding();
    void mirror_part(int left_up_x, int left_up_y, int right_down_x, int right_down_y, char axis);
    std::vector<std::pair<int, int>> calculate_circle_points(int cx, int cy, int radius);
    void blur_image(int size);
};

BMP::BMP(const char* filename) {

    FILE *f = fopen(filename, "rb");
    if(!f){
        printf("Cannot read file: %s\n", filename);
        exit(1);
    }
    bmfh = new BitmapFileHeader();
    bmif = new BitmapInfoHeader();

    fread(this->bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(this->bmif, sizeof(BitmapInfoHeader), 1, f);
    check_bmp();
    img_height = bmif->height;
    img_width = bmif->width;
    unsigned int padding = calculate_padding();
    Rgb **arr = (Rgb**)malloc(img_height * sizeof(Rgb*));
    for(int i = 0; i < img_height; i++){
        arr[i] = (Rgb*)malloc(img_width * sizeof(Rgb) + padding);
        fread(arr[i], 1, (img_width * sizeof(Rgb) + padding),
              f);
    }
    this->array = arr;
    fclose(f);
}

BMP::~BMP(){
    for(unsigned int i = 0; i < this->bmif->height; i++){
        free(this->array[i]);

    free(this->array);
    delete this->bmfh;
    delete this->bmif;
}
}

void print_help() {
    std::ifstream file("help");
    if (!file.is_open()) {
        std::cerr << ERROR_HELP << std::endl;
        exit(ERROR);
    }
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}
unsigned int BMP::calculate_padding(){
    unsigned int padding = (img_width * sizeof(Rgb)) % 4;
    if(padding){
        padding = 4 - padding;
    }
    return padding;
}
void BMP::save_bmp(const char* file_name){
    FILE *ff = fopen(file_name, "wb");
    if(!ff){
        std::cout<<"Could not open file.\n";
        exit(40);
    }
    fwrite(this->bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(this->bmif, 1, sizeof(BitmapInfoHeader), ff);
    unsigned int padding = calculate_padding();
    for(int i = 0; i < img_height; i++){
        fwrite(array[i], 1, (img_width * sizeof(Rgb) + padding),
               ff);
    }
    fclose(ff);
}

void BMP::draw_circle(int x_center, int y_center, int radius, Rgb color) {
    if (radius == 0){
        radius = 1;
    }

    if(radius == 1 || radius == 2){
        set_pixel( x_center, y_center, color);
        set_pixel( x_center + 1, y_center, color);
        set_pixel( x_center, y_center + 1, color);
        set_pixel( x_center - 1, y_center, color);
        set_pixel( x_center, y_center -  1, color);

        if(radius==2){
            set_pixel( x_center + 1, y_center + 1, color);
            set_pixel( x_center + 1, y_center - 1, color);
            set_pixel( x_center - 1, y_center + 1, color);
            set_pixel( x_center - 1, y_center - 1, color);
            set_pixel( x_center + 2, y_center, color);
            set_pixel( x_center,y_center+2, color);
            set_pixel( x_center - 2, y_center, color);
            set_pixel( x_center, y_center - 2, color);
        }

        return;
    }
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while(y >= x) {
        set_pixel(x_center + x, y_center + y, color);
        set_pixel(x_center + x, y_center - y, color);
        set_pixel(x_center - x, y_center + y, color);
        set_pixel(x_center - x, y_center - y, color);
        set_pixel(x_center + y, y_center + x, color);
        set_pixel( x_center + y, y_center - x, color);
        set_pixel( x_center - y, y_center + x, color);
        set_pixel( x_center - y, y_center - x, color);
        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        if(delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
    draw_circle(x_center, y_center, radius/2, color);
}

void BMP::draw_thick_circle(int cx, int cy, int radius, int thickness, Rgb color) {
    std::vector<std::pair<int, int>> points = calculate_circle_points(cx, cy, radius);

    for (auto point : points) {
        draw_circle(point.first, point.second, thickness, color);
    }
}

std::vector<std::pair<int, int>> BMP::calculate_circle_points(int cx, int cy, int radius) {
    std::vector<std::pair<int, int>> points;
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        // Добавляем вектора симметричных точек на окружности
        points.push_back(std::make_pair(cx + x, cy + y));
        points.push_back(std::make_pair(cx + y, cy + x));
        points.push_back(std::make_pair(cx - y, cy + x));
        points.push_back(std::make_pair(cx - x, cy + y));
        points.push_back(std::make_pair(cx - x, cy - y));
        points.push_back(std::make_pair(cx - y, cy - x));
        points.push_back(std::make_pair(cx + y, cy - x));
        points.push_back(std::make_pair(cx + x, cy - y));

        ++y;
        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            --x;
            radiusError += 2 * (y - x + 1);
        }
    }
    return points;
}

void BMP::print_file_header(){
    std::cout<< "Signature: "<< this->bmfh->signature<< std::endl;
    std::cout<<"File size: "<<this->bmfh->filesize<<std::endl;
    std::cout<<"Reserved 1: "<< this->bmfh->reserved1<<std::endl;
    std::cout<<"Reserved 2: "<<this->bmfh->reserved2<<std::endl;
    std::cout<<"PixelArrOffset: "<<this->bmfh->pixelArrOffset<<std::endl;
}

void BMP::print_info_header(){
    std::cout<<"Header Size: "<<this->bmif->headerSize<<std::endl;
    std::cout<<"Width: "<<this->bmif->width<<std::endl;
    std::cout<<"Height: "<<this->bmif->height<<std::endl;
    std::cout<<"Planes: "<<this->bmif->planes<<std::endl;
    std::cout<<"bitsPerPixel: "<<this->bmif->bitsPerPixel<<std::endl;
    std::cout<<"Compression: "<<this->bmif->compression<<std::endl;
    std::cout<<"Image Size: "<<this->bmif->imageSize<<std::endl;
    std::cout<<"xPixelsPerMeter: "<<this->bmif->xPixelsPerMeter<<std::endl;
    std::cout<<"yPixelsPerMeter: "<<this->bmif->yPixelsPerMeter<<std::endl;
    std::cout<<"colorsInColorTable: "<<this->bmif->colorsInColorTable<<std::endl;
    std::cout<<"importantColorCount: "<<this->bmif->importantColorCount<<std::endl;
}

void BMP::mirror_part(int left_up_x, int left_up_y, int right_down_x, int right_down_y, char axis) {
    if(left_up_x > right_down_x){
        std::swap(left_up_x,right_down_x);
    }
    if(left_up_y > right_down_y){
        std::swap(left_up_y, right_down_y);
    }
    if(left_up_x <0){
        left_up_x = 0;
    }
    if(right_down_x > img_width){
        int tmp = right_down_x;
        right_down_x = img_width;
        left_up_x += tmp - img_width;
    }
    if(left_up_y < 0){
        left_up_y = 0;
    }
    if(right_down_y > img_height){
        int tmp = right_down_y;
        right_down_y = img_height;
        left_up_y += tmp - img_height;
    }

    if(axis == 'x'){
        int cnt = (right_down_x - left_up_x)/2;
        for(int i = left_up_y; i < right_down_y; i++){
            for(int j = 0; j < cnt; j++){
                Rgb buf_arr = array[img_height -1- i][right_down_x  - j];
                array[img_height -1 - i][right_down_x  - j] = array[img_height -1 - i][left_up_x + j];
                array[img_height -1 - i][left_up_x + j] = buf_arr;
            }
        }
    }
    if(axis == 'y'){
        int cnt = (right_down_y - left_up_y)/2;
        for(int i = left_up_x; i < right_down_x; i++){
            for(int j = 0; j < cnt; j++){
                Rgb buf_arr = array[img_height - 2- (left_up_y + j)][i];
                array[img_height -2-(left_up_y + j)][i] = array[img_height  -1- (right_down_y - j - 1)][i];
                array[img_height  -1 -(right_down_y- j -1)][i] = buf_arr;
            }
        }
    }
}

void print_error_msg(const std::string &msg, int exit_code) {
    std::cerr<< msg << std:: endl;
    exit(exit_code);
}

void BMP::check_bmp(){
    if(bmfh->signature != CORRECT_SIGNATURE){
        print_error_msg(ERROR_SIGNATURE, ERROR);
    }
    if(bmif->bitsPerPixel != CORRECT_BITS || bmif->compression != CORRECT_COMPRESSION || bmif->planes != CORRECT_PLANES){
        print_error_msg(ERROR_BMP_FORMAT, ERROR);
    }
    if(bmfh->pixelArrOffset != CORRECT_OFFSET){
        print_error_msg(ERROR_OFFSET, ERROR);
    }
    if(bmif->headerSize != CORRECT_HEADER_SIZE){
        print_error_msg(ERROR_HEADER_SIZE, ERROR);
    }
}

void BMP::set_pixel(int x, int y, Rgb color) {
    if(!(x<0 || x >= img_width || y < 0 || y>= img_height)){
        array[img_height-1-y][x] = color;
    }
}
void BMP::draw_pentagram(int cx, int cy, int radius, int thickness,Rgb color) {

    const double PI = 3.141592653589793238463;

    double angle = 2 * PI / 5;

    int x[5], y[5];
    for (int i = 0; i < 5; ++i) {
        x[i] = cx + radius * cos(i * angle + PI *3 / 10);
        y[i] = cy + radius * sin(i * angle + PI *3/ 10);
    }


    for (int i = 0; i < 5; ++i) {
        draw_line(x[i], y[i], x[(i + 2) % 5], y[(i + 2) % 5],thickness, color);
    }
    draw_thick_circle(cx, cy, radius,thickness/2, color);// переработать
}
void BMP::draw_line(int x_start, int y_start, int x_end, int y_end, int thickness, Rgb color) {
    int dx = abs(x_end-x_start);
    int dy = abs(y_end-y_start);
    int sx = x_start < x_end ? 1 : -1;
    int sy = y_start < y_end ? 1 : -1;
    int err = dx - dy;
    draw_circle(x_end, y_end, thickness/2, color);
    while(x_start!= x_end || y_start!=y_end){
        draw_circle(x_start, y_start, thickness/2, color);
        if(thickness!=0){
            draw_circle(x_end, y_end, (thickness/2), color);
        }
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x_start += sx;
        }
        if (err2 < dx) {
            err += dx;
            y_start += sy;
        }
    }
}

void check_color(int red, int green, int blue){
    if(red > 255 || green > 255 || blue > 255 || red < 0 || green < 0 || blue < 0){
        print_error_msg(ERROR_COLOR, 46);
    }
}
void BMP::blur_image(int size) {
    Rgb** new_array = (Rgb**)malloc(img_height*sizeof(Rgb*));
    unsigned int padding = calculate_padding();

    if((size%2)==0){
        size++;
    }
    for(int i = 0; i <img_height; i++){
        new_array[i] = (Rgb*)malloc(img_width*sizeof(Rgb) + padding);
        std::memcpy(new_array[i], this->array[i], img_width*sizeof(Rgb) + padding);
    }

    for(int y=0; y <img_height; y++){
        for(int x = 0; x < img_width; x++){
            int sum_r = 0, sum_g = 0, sum_b = 0;
            for(int s1 = -(size/2); s1 <= (size/2); s1++){
                for(int s2 = -(size/2); s2 <= (size/2); s2++){
                    if(y + s1 >=0 && x+ s2 >= 0 && x + s2 < img_width && y+s1 <img_height){
                        sum_r += new_array[y+s1][x+s2].r;
                        sum_g += new_array[y+s1][x+s2].g;
                        sum_b += new_array[y+s1][x+s2].b;
                    }
                }
            }
            this->array[y][x].r = sum_r / (size) /(size);
            this->array[y][x].g = sum_g/ (size)  /(size);
            this->array[y][x].b = sum_b / (size)/(size) ;
        }
    }
}

void process_flags(BMP* &bmp, Argument_Parser &args) {
    if (args.input_file_name == args.output_file_name) {
        print_error_msg(ERROR_INPUT_OUTPUT_SAME, INPUT_OUTPUT_ERROR_CODE);
    }
    if (args.info) {
        bmp->print_file_header();
        bmp->print_info_header();
        exit(SUCCESS);
    }
    if (args.line) {
        if (args.thickness == -1) {
            print_error_msg(ERROR_THICKNESS_NOT_SET, THICKNESS_ERROR_CODE);
        }
        bmp->draw_line(args.start_x, args.start_y, args.end_x, args.end_y, args.thickness, args.color);
    }
    if (args.pentagram) {
        if (args.thickness == -1) {
            print_error_msg(ERROR_THICKNESS_NOT_SET, THICKNESS_ERROR_CODE);
        }
        bmp->draw_pentagram(args.p_center_x, args.p_center_y, args.p_radius, args.thickness, args.color);
    }
    if (args.mirror) {
        if (args.axis == INVALID_AXIS) {
            print_error_msg(ERROR_MISSING_AXIS, AXIS_ERROR_CODE);
        }
        bmp->mirror_part(args.left_up_x, args.left_up_y, args.right_down_x, args.right_down_y, args.axis);
    }
    if (args.blur) {
        bmp->blur_image(args.size);
    }
    bmp->save_bmp(args.output_file_name.c_str());
}

int main(int argc, char *argv[]) {
    if(argc<2){
        print_error_msg(ERROR_NUMBER_ARGS, ERROR);
    }
    BMP* bmp;
    Argument_Parser args;
    args.parse(argc, argv);
    if (!args.input_file_name.empty()) {
        bmp = new BMP(args.input_file_name.c_str());
    }
    process_flags(bmp, args);
    return SUCCESS;
}
