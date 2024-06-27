#include "../include/functions.h"
#include "../include/bmp.h"
#include <string>
#include <math.h>
#include "../include/helps.h"

using namespace std;

void inverse_all(BMPImage &image_data) {

    for (uint32_t i = 0; i < image_size; i++) {
        image_data.data.at(i) = ~image_data.data[i];
        /* code */
    }

}



void component_max(BMPImage& image_data, std::string color){
    if (color != RED && color != GREEN && color != BLUE) {
        std::cerr << MESSAGE_WrongColor << std::endl;
        exit(ERR_WRONGCOLOR);
        return;
    }


    size_t image_size = image_data.data.size();
    for (size_t i = 0; i < image_size -3; i += 3) {
        uint8_t max = 255;
        //bgr
        if (color == "blue") {
            int sum = image_data.data[i+1] + image_data.data[i+2];
            image_data.data[i] = static_cast<uint8_t>((sum > max) ? max : sum);
        } else if (color == "green") {
            int sum = image_data.data[i] + image_data.data[i+2];
            image_data.data[i+1] = static_cast<uint8_t>((sum > max) ? max : sum);
        } else if (color == "red") {
            int sum = image_data.data[i] + image_data.data[i+1];
            image_data.data[i+2] = static_cast<uint8_t>((sum > max) ? max : sum);
        }
    }
}

Pixel get_pixel(BMPImage &info, int y, int x) {
    int bytesPerPixel = info.file_header.bit_count / 8;
    int bytesPerRow = (bytesPerPixel * info.file_header.width + 3) & ~3;
    int index = ((info.file_header.height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);

    return Pixel{&(info.data.at(index + 2)), &(info.data.at(index + 1)), &(info.data.at(index))};
}

void set_pixel(BMPImage &info, int y, int x, Pixel pixel) {
    if (y >= info.file_header.height || y < 0 || x < 0 || x >= info.file_header.width) {
        return;
    }

    int bytesPerPixel = info.file_header.bit_count / 8;
    int bytesPerRow = (bytesPerPixel * info.file_header.width + 3) & ~3;
    int index = ((info.file_header.height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);
    info.data.at(index + 2) = *pixel.red;
    info.data.at(index + 1) = *pixel.green;
    info.data.at(index) = *pixel.blue;
}

void set_pixel(BMPImage &info, int y, int x, Pixel pixel, std::vector<uint8_t> &new_data) {
    if (y >= info.file_header.height || y < 0 || x < 0 || x >= info.file_header.width) {
        return;
    }

    int bytesPerPixel = info.file_header.bit_count / 8;
    int bytesPerRow = (bytesPerPixel * info.file_header.width + 3) & ~3;
    int index = ((info.file_header.height - 1 - y) * bytesPerRow) + (x * bytesPerPixel);
    new_data.at(index + 2) = *pixel.red;
    new_data.at(index + 1) = *pixel.green;
    new_data.at(index) = *pixel.blue;
}


void shift_x(BMPImage &info, int shiftvalue) {
    vector<uint8_t> data_new(info.data);
    for (int y = 0; y < info.file_header.height; ++y) {
        for (int x = 0; x < info.file_header.width; ++x) {
            if (x >= shiftvalue) {

                Pixel pixel_new = get_pixel(info, y, x - shiftvalue);
                set_pixel(info, y, x, pixel_new, data_new);

            } else {

                Pixel pixel_new = get_pixel(info, y, info.file_header.width - shiftvalue + x);
                set_pixel(info, y, x, pixel_new, data_new);
            }


        }
    }
    info.data = data_new;

}

void shift_y(BMPImage &info, int shiftvalue) {
    vector<uint8_t> data_new(info.data);
    for (int y = 0; y < info.file_header.height; ++y) {
        for (int x = 0; x < info.file_header.width; ++x) {
            if (y>=shiftvalue) {

                Pixel pixel_new = get_pixel(info, y - shiftvalue, x);
                set_pixel(info, y, x, pixel_new, data_new);

            } else {
                Pixel pixel_new = get_pixel(info, info.file_header.height-shiftvalue+y, x);
                set_pixel(info, y, x, pixel_new, data_new);

            }


        }
    }
    info.data = data_new;
}

void shift_func(BMPImage &info, int shiftvalue, std::string axisfield) {
    if (axisfield == "x") {
        vector<uint8_t> data_new(info.data);
        for (int y = 0; y < info.file_header.height; ++y) {
            for (int x = 0; x < info.file_header.width; ++x) {
                if (x >= shiftvalue) {

                    Pixel pixel_new = get_pixel(info, y, x - shiftvalue);
                    set_pixel(info, y, x, pixel_new, data_new);

                } else {

                    Pixel pixel_new = get_pixel(info, y, info.file_header.width - shiftvalue + x);
                    set_pixel(info, y, x, pixel_new, data_new);
                }


            }
        }
        info.data = data_new;

    }

    if (axisfield == "y") {
        vector<uint8_t> data_new(info.data);
        for (int y = 0; y < info.file_header.height; ++y) {
            for (int x = 0; x < info.file_header.width; ++x) {
                if (y>=shiftvalue) {

                    Pixel pixel_new = get_pixel(info, y - shiftvalue, x);
                    set_pixel(info, y, x, pixel_new, data_new);

                } else {
                    Pixel pixel_new = get_pixel(info, info.file_header.height-shiftvalue+y, x);
                    set_pixel(info, y, x, pixel_new, data_new);

                }


            }
        }
        info.data = data_new;

    }

    if (axisfield == "xy") {
        shift_x(info,shiftvalue);
        shift_y(info,shiftvalue);


    }


}

bool validateShift(OptionFlags &flags) {
    if ((flags.axisFlag || flags.shiftFlag || flags.stepFlag) == 1) {
        return true;
    } else {
        return false;
        std::cerr << "shift goes wrong!" << std::endl;
        exit(40);
    }

}


void rgb2hsv(uint8_t r, uint8_t g, uint8_t b, float& h, float& s, float& v) {
    float r_f = r / 255.0f;
    float g_f = g / 255.0f;
    float b_f = b / 255.0f;

    float cmax = std::max(r_f, std::max(g_f, b_f));
    float cmin = std::min(r_f, std::min(g_f, b_f));
    float diff = cmax - cmin;

    if (diff == 0) {
        h = 0;
    } else if (cmax == r_f) {
        h = 60 * ((g_f - b_f) / diff) + (g_f < b_f ? 360 : 0);
    } else if (cmax == g_f) {
        h = 60 * ((b_f - r_f) / diff) + 120;
    } else {
        h = 60 * ((r_f - g_f) / diff) + 240;
    }

    if (cmax == 0) {
        s = 0;
    } else {
        s = diff / cmax;
    }

    v = cmax;
}



void hsvconvert(BMPImage &info){
    std::vector<uint8_t> data =  info.data;

    for (int y = 0; y < info.file_header.height; ++y) {
        for (int x = 0; x < info.file_header.width; ++x) {
            Pixel pixel = get_pixel(info,y, x);
            float h, s, v;
            rgb2hsv(*pixel.red,*pixel.green, *pixel.blue, h,s,v);
            *pixel.blue = static_cast<uint8_t>(h*255/360);
            *pixel.green = static_cast<uint8_t>(s*255);
            *pixel.red = static_cast<uint8_t>(v*255);
            set_pixel(info,y,x,pixel);
        }
    }
}







//void ImageProcessor::gray(Picture &picture, Coordinate leftUp, Coordinate rightDown){
//    std::vector<uint8_t> data =  picture.data;
//
//    for (int y = leftUp.y; y <= rightDown.y; ++y) {
//        for (int x = leftUp.x; x <= rightDown.x; ++x) {
//            Color pixel = picture.getPixel(x, y);
//            uint8_t grayValue = std::round(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);
//            picture.setPixel(x, y, Color(grayValue, grayValue, grayValue));
//        }
//    }
//}
//



