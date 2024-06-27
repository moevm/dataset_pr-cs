#ifndef CW_START_DRAW_H
#define CW_START_DRAW_H

void rect(struct Png* image, int* cor1, int *cor2, int thickness, int* color, int fill, int* color_fill);

void hexagon(struct Png* image, int* center, int radius, int thickness, int* color, bool fill, int* color_fill);

void pentagram(struct Png* image, int* center, int radius, int thickness, int* color);

#endif //CW_START_DRAW_H
