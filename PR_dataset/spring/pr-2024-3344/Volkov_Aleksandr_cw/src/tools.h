#include "image.h"
#include "draw.h"
#include <math.h>

#define FRAME_RECTANGLE 1
#define FRAME_CIRCLE 2
#define FRAME_SEMICIRCLES 3

image *split(image* img, uint N, uint M, uint stroke_width, color* stroke);
image *rectangle(selection* slct, uint stroke_width, color* stroke, color* fill);
image* rectangle_for_ornament(selection* slct, uint stroke_width, color* stroke, color* fill);
image *frame(image* img, color* color, uint thickness, uint count, int pattern_type);
void draw_circle(image* img, int centerX, int centerY, int radius, int thickness, color* color);
image* turn(selection* slct, int angle);
image* rotate(image* img, selection* slct, int angle);
image *compress(image *img, int num);
