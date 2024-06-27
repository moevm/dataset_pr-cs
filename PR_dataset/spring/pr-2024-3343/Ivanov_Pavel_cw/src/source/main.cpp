#include "../include/functions.h"

void hsv(PICInfo& info){
    for (unsigned int i = 0; i < size_image - 2; i+=3) {
    float r = info.pixels[i+2] / 255.0f;
    float g = info.pixels[i+1] / 255.0f;
    float b = info.pixels[i] / 255.0f;

    float max = fmax(r, fmax(g, b));
    float min = fmin(r, fmin(g, b));
    v = static_cast<int>(max * 100);

    float delta = max - min;
    if (delta < 0.00001f) {
        s = 0;
        h = 0;
        return;
    }

    if (max > 0.0f) {
        s = static_cast<int>((delta / max) * 100);
    } else {
        s = 0;
        h = 0;
        return;
    }

    if (r >= max) {
        h = static_cast<int>(60 * ((g - b) / delta));
    } else if (g >= max) {
        h = static_cast<int>(60 * (2.0f + (b - r) / delta));
    } else {
        h = static_cast<int>(60 * (4.0f + (r - g) / delta));
    }

    if (h < 0) {
        h += 360;
    }

    info.pixels[i] = uint8_t(h);
    info.pixels[i+1] = uint8_t(s);
    info.pixels[i+2] = uint8_t(v);
    }
}

int main(int argc, char* argv[]){
    cli_parse(argc, argv);
}
