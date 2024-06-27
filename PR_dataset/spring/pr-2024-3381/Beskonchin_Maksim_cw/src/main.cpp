#include <getopt.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <png.h>
#define PRINT_HEADING() cout << "Course work for option 4.18, created by Beskonchin Maksim.\n\n";
using namespace std;
int setNumberFunc = -1;
struct PngOptLine{
    int x0;
    int y0;
    int x1;
    int y1;
    int r;
    int g;
    int b;
    int thickness;
    int count = 0;
};
struct PngOptInverse{
    int x;
    int y;
    int radius;
    int count = 0;
};
struct PngOptTrim{
    int x0;
    int y0;
    int x1;
    int y1;
    int count = 0;
};
struct PngOptGamma{
    float value;
    int count = 0;
};
struct PngOpt{
    PngOptLine line;
    PngOptInverse inverse;
    PngOptTrim trim;
    PngOptGamma gamma;
};
struct PngImage{
    int width, height, channels, number_of_passes;
    png_byte colorType;
    png_byte bitDepth;
    png_structp pngPtr;
    png_infop infoPtr;
    //png_bytep *rowPointers;
    vector<png_bytep> rowPointers;
};
void error_handling(int x){
    switch (x) {
        case 0:
            cout << "Error" << endl;
            break;
        case 1:
            cout << "Not enough arguments!" << endl;
            break;
        case 2:
            cout << "Invalid input!" << endl;
            break;
        case 3:
            cout << "Invalid input! (Function color_replace)" << endl;
            break;
        case 4:
            cout << "Invalid input! (Function rgbfilter)" << endl;
            break;
        case 5:
            cout << "Invalid input! (Function split)" << endl;
            break;
        case 6:
            cout << "Failed to save PNG!" << endl;
            break;
        case 7:
            cout << "Invalid input! Input name can't be like output name!" << endl;
            break;
        case 8:
            cout << "Invalid input! Don't use --help/-h with other flags!" << endl;
            break;
        case 9:
            cout << "Invalid input! Error flag: -o" << endl;
            break;
        case 10:
            cout << "Invalid input! Error flag: -i" << endl;
            break;
        case 11:
            cout << "Invalid input! You can use only 1 flag like: -a,-b,-c and their long forms!" << endl;
            break;
        case 12:
            cout << "Invalid input! Unkown flag!" << endl;
            break;
    }
    exit(40);
}

void set_flag(PngOpt& storage,char c)
{
    if (c >= 'd' && c <= 'g'){
        if(c == 'd'){
            if(sscanf(optarg,"%d.%d", &storage.line.x0, &storage.line.y0) != 2){
                error_handling(0);
            }
            else storage.line.count += 1;}
        if(c == 'e'){
            if(sscanf(optarg,"%d.%d", &storage.line.x1, &storage.line.y1) != 2){
                error_handling(0);
            }
            else storage.line.count += 1;}

        if(c == 'f'){
            if(sscanf(optarg,"%d.%d.%d", &storage.line.r, &storage.line.g, &storage.line.b) != 3){
                error_handling(0);
            }
            else if(storage.line.r < 0 or storage.line.g < 0 or storage.line.b < 0){
                error_handling(0);
            }
            else storage.line.count += 1;}
        if(c == 'g'){
            if(sscanf(optarg,"%d", &storage.line.thickness)!=1){
                error_handling(0);
            }
            else if (storage.line.thickness < 0){
                error_handling(0);
            }
            else storage.line.count += 1;}}

    else if (c == 'j' || c == 'k'){
        if(c == 'j'){
            if(sscanf(optarg,"%d.%d", &storage.inverse.x, &storage.inverse.y) != 2){
                error_handling(0);
            }
            else storage.inverse.count += 1;}
        if(c == 'k'){
            if(sscanf(optarg,"%d", &storage.inverse.radius)!=1){
                error_handling(0);
            }
            else if (storage.inverse.radius < 0){
                error_handling(0);
            }
            else storage.inverse.count += 1;}
    }

    else if (c == 'l' || c == 'm'){
        if(c == 'l'){
            if(sscanf(optarg,"%d.%d", &storage.trim.x0, &storage.trim.y0) != 2){
                error_handling(0);
            }
            else storage.trim.count += 1;}
        if(c == 'm'){
            if(sscanf(optarg,"%d.%d", &storage.trim.x1, &storage.trim.y1) != 2){
                error_handling(0);
            }
            else storage.trim.count += 1;}
    }
    if(c == 'r'){
        if(sscanf(optarg,"%f", &storage.gamma.value) != 1){
            error_handling(0);
        }
        else if (storage.gamma.value < 0){
            error_handling(0);
        }
        else storage.gamma.count += 1;}
}

const char* short_options = "habcd:e:f:g:j:k:l:m:i:o:zpr:";
const struct option long_options[] = {
        { "help", no_argument, NULL, 'h' },
        { "line", no_argument, NULL, 'a' },
        { "inverse_circle", no_argument, NULL, 'b' },
        { "trim", no_argument, NULL, 'c' },
        { "start", required_argument, NULL, 'd' },
        { "end", required_argument, NULL, 'e' },
        { "color", required_argument, NULL, 'f' },
        { "thickness", required_argument, NULL, 'g' },
        { "center", required_argument, NULL, 'j' },
        { "radius", required_argument, NULL, 'k' },
        { "left_up", required_argument, NULL, 'l' },
        { "right_down", required_argument, NULL, 'm' },
        { "input", required_argument, NULL, 'i' },
        { "output", required_argument, NULL, 'o' },
        { "gamma", no_argument, NULL, 'p' },
        { "value", required_argument, NULL, 'r' },
        { "info", no_argument, NULL, 'z' },
        { NULL, 0, NULL, '\0' }
};

void func_help() {
    PRINT_HEADING();
    cout <<"\nSynopsis:"<< endl;
    cout << "(1) Drawing a segment. Flag to perform this operation: --line.\n"
            "    The segment is defined by:\n"
            "   - start coordinates. Flag --start, the value is specified in the\n"
            "     format x.y, where x is the x coordinate, y is the y coordinate\n"
            "   - end coordinates. Flag --end (similar to the --start flag)\n"
            "   - colour. Flag --color (colour is specified by the string rrrr.ggg.bbb, where rrrr/ggg/bbb\n"
            "     are numbers specifying the colour component. example --color 255.0.0 specifies red colour)\n"
            "   - thickness. Flag --thickness. Accepts a number greater than 0 as input\n\n";

    cout << "(2) Invert the colours in the specified circle. Flag to perform this operation: --inverse_circle.\n"
            "    The circle is defined by:\n"
            "   - coordinates of its centre and radius. Flags --center and --radius.\n"
            "     The value of the flag  --center is set in the format x.y,\n"
            "     where x is the x-axis coordinate, y is the y-axis coordinate.\n"
            "     Flag --radius Flag accepts a number greater than 0 as input\n\n";

    cout << "(3) Image Cropping. Flag to perform this operation: --trim.\n"
            "    It is required to trim the image by the specified area.\n"
            "    The area is defined by:\n"
            "   - Coordinates of the upper left corner. Flag --left_up, the value is specified\n"
            "     in the format left.up, where left is the x-coordinate, up is the y-coordinate\n"
            "   - Coordinates of the lower right corner.  Flag --right_down, the value is specified\n"
            "     in the format right.down, where right is the x-coordinate, down is the y-coordinate\n";


}

int readPngFile(const char *filename, PngImage &image){

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        cout << "Error opening PNG file.";
        return 1;
    }

    unsigned char sig[8];
    fread(sig, 1, 8, fp);
    if (png_sig_cmp(sig, 0, 8)) {
        // Файл не является PNG
        fclose(fp);
        cout << "Error the open file is not in PNG format.";
        return 1;
    }

    image.pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image.pngPtr) {
        fclose(fp);
        return 1;
    }

    image.infoPtr = png_create_info_struct(image.pngPtr);
    if (!image.infoPtr) {
        png_destroy_read_struct(&image.pngPtr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 1;
    }

    if (setjmp(png_jmpbuf(image.pngPtr))) {
        png_destroy_read_struct(&image.pngPtr, &image.infoPtr, NULL);
        fclose(fp);
        return 1;
    }

    png_init_io(image.pngPtr, fp);
    png_set_sig_bytes(image.pngPtr, 8);
    png_read_info(image.pngPtr, image.infoPtr);

    image.width = png_get_image_width(image.pngPtr, image.infoPtr);
    image.height = png_get_image_height(image.pngPtr, image.infoPtr);
    image.colorType = png_get_color_type(image.pngPtr,image.infoPtr);
    image.bitDepth = png_get_bit_depth(image.pngPtr, image.infoPtr);
    image.number_of_passes = png_set_interlace_handling(image.pngPtr);
    image.channels = png_get_channels(image.pngPtr, image.infoPtr);

    png_read_update_info(image.pngPtr, image.infoPtr);
//    image.rowPointers = (png_bytep *)malloc(sizeof(png_bytep) * image.height);
//    for (int y = 0; y < image.height; y++) {
//        image.rowPointers[y] = (png_byte *)malloc(png_get_rowbytes(image.pngPtr, image.infoPtr));
//    }
//    png_read_image(image.pngPtr, image.rowPointers);
    image.rowPointers.resize(image.height);
    for (int y = 0; y < image.height; y++) {
        image.rowPointers[y] = (png_bytep)malloc(png_get_rowbytes(image.pngPtr, image.infoPtr));
    }

    png_read_image(image.pngPtr, image.rowPointers.data());
    fclose(fp);
    return 0;
}

void printInfo(PngImage &image){
    cout << "Image width: " << image.width << endl;
    cout << "Image height: " << image.height << endl;
    cout << "Color type: " << int(image.colorType) << endl;
    cout << "Color depth: " << int(image.bitDepth)<< endl;
}

void drawPixel(PngImage &image, int x, int y, int thickness, int r, int g, int b) {
    int half_thickness = thickness / 2;
    int startX = max(0, x - half_thickness);
    int endX = min(image.width - 1, x + half_thickness);
    int startY = max(0, y - half_thickness);
    int endY = min(image.height - 1, y + half_thickness);

    for (int yy = startY; yy <= endY; ++yy) {
        for (int xx = startX; xx <= endX; ++xx) {
            int index = xx * image.channels;
            image.rowPointers[yy][index] = r;
            image.rowPointers[yy][index + 1] = g;
            image.rowPointers[yy][index + 2] = b;
        }
    }
}

int drawLine(PngImage &image, PngOptLine &storage) {
    int dx = abs(storage.x1 - storage.x0);
    int dy = abs(storage.y1 - storage.y0);
    int sx = storage.x0 < storage.x1 ? 1 : -1;
    int sy = storage.y0 < storage.y1 ? 1 : -1;
    int err = dx - dy;
    int x = storage.x0;
    int y = storage.y0;

    while (true) {
        drawPixel(image, x, y, storage.thickness, storage.r, storage.g, storage.b);

        if (x == storage.x1 && y == storage.y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    return 0;
}


int inverseCircleColors(PngImage &image,PngOptInverse& storage) {
    int radius = storage.radius;
    int centerX = storage.x;
    int centerY = storage.y;

    // Проверяем, что координаты центра и радиус находятся в пределах изображения
    if (centerX + radius < 0 || centerY + radius < 0 || centerX - radius >= image.width || centerY - radius>= image.height || radius <= 0) {
        cout << "Error: Invalid circle coordinates or radius." << endl;
        return 1;
    }

    int radiusSquared = radius * radius;

    // Проходим по каждому пикселю изображения
    for (int y = centerY- radius -10; y < image.height; ++y) {
        for (int x = centerX - radius -10; x < image.width; ++x) {
            if (x < 0 || y < 0 || x >= image.width || y >= image.height){
                continue;
            }
            // Вычисляем расстояние от текущего пикселя до центра окружности
            int distanceSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distanceSquared <= radiusSquared) {
                // Инвертируем цвет пикселя путем вычитания значения каждого канала из 255
                for (int c = 0; c < image.channels; ++c) {
                    image.rowPointers[y][x * image.channels + c] = 255 - image.rowPointers[y][x * image.channels + c];
                }
            }
        }
    }
    return 0;
}

int trimPngFile(const char *filename, PngOptTrim& storage,PngImage &image) {

    int x1 = storage.x0;
    int y1 = storage.y0;
    int x2 = storage.x1;
    int y2 = storage.y1;

    // Обеспечиваем, что координаты в правильном порядке
    int leftX = min(x1, x2);
    int rightX = max(x1, x2);
    int topY = min(y1, y2);
    int bottomY = max(y1, y2);

    // Убедимся, что координаты находятся внутри границ изображения
    leftX = max(0, min(leftX, image.width));
    rightX = max(0, min(rightX, image.width));
    topY = max(0, min(topY, image.height));
    bottomY = max(0, min(bottomY, image.height));

    // Проверка на корректность границ
    if (leftX >= rightX || topY >= bottomY) {
        cout << "Invalid crop coordinates." << endl;
        return 1;
    }

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        cout << "Error opening file for writing." << endl;
        return 1;
    }

    image.pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image.pngPtr) {
        fclose(fp);
        return 1;
    }

    image.infoPtr = png_create_info_struct(image.pngPtr);
    if (!image.infoPtr) {
        png_destroy_write_struct(&image.pngPtr, NULL);
        fclose(fp);
        return 1;
    }

    if (setjmp(png_jmpbuf(image.pngPtr))) {
        png_destroy_write_struct(&image.pngPtr, &image.infoPtr);
        fclose(fp);
        return 1;
    }

    png_init_io(image.pngPtr, fp);

    if (setjmp(png_jmpbuf(image.pngPtr))) {
        png_destroy_write_struct(&image.pngPtr, &image.infoPtr);
        fclose(fp);
        return 1;
    }

    int newWidth = rightX - leftX;
    int newHeight = bottomY - topY;

    png_set_IHDR(image.pngPtr, image.infoPtr, newWidth, newHeight, image.bitDepth, image.colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image.pngPtr, image.infoPtr);

    for (int y = topY; y < bottomY; ++y) {
        png_write_row(image.pngPtr, image.rowPointers[y] + leftX * png_get_channels(image.pngPtr, image.infoPtr));
    }

    png_write_end(image.pngPtr, NULL);
    fclose(fp);
    png_destroy_write_struct(&image.pngPtr, &image.infoPtr);

    return 0;
}

int savePngFile(const char *filename, PngImage &image) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        cout << "Error opening file for writing.";
        return 1;
    }

    image.pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image.pngPtr) {
        fclose(fp);
        return 1;
    }

    image.infoPtr = png_create_info_struct(image.pngPtr);
    if (!image.infoPtr ) {
        fclose(fp);
        return 1;
    }

    if (setjmp(png_jmpbuf(image.pngPtr))) {
        fclose(fp);
        return 1;
    }

    png_init_io(image.pngPtr, fp);
    if (setjmp(png_jmpbuf(image.pngPtr))) {
        fclose(fp);
        return 1;
    }
    png_set_IHDR(image.pngPtr, image.infoPtr , image.width, image.height, image.bitDepth, image.colorType, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    if (png_get_color_type(image.pngPtr, image.infoPtr) == PNG_COLOR_TYPE_PALETTE) {
        png_color palette[256];
        png_set_PLTE(image.pngPtr, image.infoPtr, palette, 256);
    }
    png_write_info(image.pngPtr, image.infoPtr);
    png_write_image(image.pngPtr, image.rowPointers.data());
    png_write_end(image.pngPtr, NULL);
    fclose(fp);
    return 0;
}

int pngzahi(PngImage& image, PngOptGamma& storage) {
            for (int yy = 0; yy < image.height; yy++) {
                png_bytep row = image.rowPointers[yy];
                for (int xx = 0; xx < image.width; xx++) {
                    int index = xx * image.channels;
                    row[index] = floorf((powf(row[index]/255.0, storage.value))  * 255.0);
                    row[index + 1] = floorf((powf(row[index+1]/255.0, storage.value))  * 255.0);
                    row[index + 2] = floorf((powf(row[index+2]/255.0, storage.value))  * 255.0);
                    //(powf(row[index]/255, storage.value)  * 255);
                }
    }
    return 0;
}
int main(int argc, char* argv[]){
    if (argc == 1) {
        func_help();
        return 0;
    }
    int opt;
    bool infoPNG = false;

    PngOpt storage;
    string namePNG = "";
    string outnamePNG = "";

    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch (opt) {
            case 'h': {
                if (argc > 2) {
                    error_handling(8);
                }
                func_help();
                return 0;
            }
            case 'z': {
                infoPNG = true;
                break;
            }
            case 'o': {
                if (outnamePNG != "" || optarg == NULL) {
                    error_handling(9);
                }
                outnamePNG = optarg;
                break;
            }
            case 'i': {
                if (namePNG != "" || optarg == NULL) {
                    error_handling(10);
                }
                namePNG = optarg;
                break;
            }
            case 'a':{
                if (setNumberFunc != -1) {
                    error_handling(11);
                }
                setNumberFunc = 0;
                break;
            }
            case 'b':{
                if (setNumberFunc != -1) {
                    error_handling(11);
                }
                setNumberFunc = 1;
                break;
            }
            case 'c': {
                if (setNumberFunc != -1) {
                    error_handling(11);
                }
                setNumberFunc = 2;
                break;
            }
            case 'p': {
                if (setNumberFunc != -1) {
                    error_handling(11);
                }
                setNumberFunc = 3;
                break;
            }

            case '?': {
                error_handling(12);
            }
            default:
                set_flag( storage, opt);
                break;
        };
    }

    if ((setNumberFunc != -1 || outnamePNG != "") && infoPNG) {
        error_handling(2);
    }
    if (namePNG == "") {
        namePNG = argv[argc - 1];
    }
    if (namePNG == outnamePNG) {
        error_handling(7);
    }
    // Считывание изображения
    PngImage image;
    if (readPngFile(namePNG.c_str(), image)) {
        error_handling(0);
    }
    if (infoPNG) {
        printInfo(image);
        return 0;
    }
    if (setNumberFunc == -1) {
        error_handling(2);
    }
    // Обработка функций
    if (setNumberFunc == 0) {
        if(storage.line.count != 4){
            error_handling(1);
        }
        if (drawLine(image, storage.line)) {
            error_handling(3);
        }
    } else if (setNumberFunc == 1) {
        if(storage.inverse.count != 2){
            error_handling(1);
        }
        if (inverseCircleColors(image, storage.inverse)) {
            error_handling(4);
        }
    } else if (setNumberFunc == 2) {
        if(storage.trim.count != 2){
            error_handling(1);
        }
        if (trimPngFile(outnamePNG.c_str(),storage.trim, image)) {
            error_handling(5);
        }
    }
    else if (setNumberFunc == 3) {
        if(storage.gamma.count != 1){
            error_handling(1);
        }
        if (pngzahi(image, storage.gamma)) {
            error_handling(5);
        }
    }


    if(setNumberFunc != 2){
        if (savePngFile(outnamePNG.c_str(), image)) {
            error_handling(6);
        }}
    return 0;
}