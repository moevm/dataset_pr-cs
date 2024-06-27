#include "structs.h"
void draw_pixel(BMPFile *img, int x, int y, rgb color);
void fill_circle(BMPFile *img, int x0, int y0, int r, rgb color);
void drawingLine(coords start, coords end, rgb color, unsigned int thickness, BMPFile* img);
bool checkColor(rgb a1, rgb a2);
bool check_coords(int y, int x, BitmapInfoHeader data);
void fill_zone(int i, int j, rgb color, rgb fill_color, BMPFile* img);
int isInsideArea(coords polygonPoints[], int nAngle, coords point);
int isInsideArea1(coords polygonPoints[], int nAngle, coords point);
void fill_rectangle(BMPFile *img, int x0, int y0, rgb color);
void drawingRectangle(rectangle data, BMPFile* img);
void drawingHexagon(hexagon data, BMPFile* img);
void copy_and_paste_area(BMPFile* img, coords start, coords end, coords past_in_area);
void set_pixel(rgb* pix, rgb new_pix);
void drawVertex(BMPFile* img, coords start, int size, rgb fill_color);