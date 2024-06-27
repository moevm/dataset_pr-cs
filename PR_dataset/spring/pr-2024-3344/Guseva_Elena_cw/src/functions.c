#include "functions.h"
//1 func
void draw_pixel(BMPFile *img, int x, int y, rgb color) {
    if (!(x < 0 || y < 0 || x >= img->bmih.width || y >= img->bmih.height)) {
        img->data[y][x] = color;
    }
}

void fill_circle(BMPFile *img, int x0, int y0, int r, rgb color) {
    int x = 0;
    int y = r;
    int delta = 3 - 2 * y;
    while (y >= x) {
        draw_pixel(img, x0 + x, y0 + y, color);
        draw_pixel(img, x0 + x, y0 - y, color);
        draw_pixel(img, x0 - x, y0 + y, color);
        draw_pixel(img, x0 - x, y0 - y, color);
        draw_pixel(img, x0 + y, y0 + x, color);
        draw_pixel(img, x0 + y, y0 - x, color);
        draw_pixel(img, x0 - y, y0 + x, color);
        draw_pixel(img, x0 - y, y0 - x, color);
        delta += delta < 0 ? 4 * x + 6 : 4 * (x - y--) + 10;
        ++x;
    }
    for (int y = -r; y <= r; y++) {
        if ((y0+y)<0 || (y0+y)>=img->bmih.height){
            continue;
        }
        for (int x = -r; x <= r; x++) {
            if (((x0+x)>=0) && ((x0+x)<img->bmih.width)&& (x * x + y * y <= r * r)) {
                draw_pixel(img, x0 + x, y0 + y, color);
            }
        }
    }
}

void drawingLine(coords start, coords end, rgb color, unsigned int thickness, BMPFile* img) {
    int x1 = start.x;
    int y1 = start.y;
    fill_circle(img, end.x, end.y ,1, color);
    int x2 = end.x;
    int y2 = end.y;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int e2;
    int x = x1;
    int y = y1;
    while (x != x2 || y != y2) {
        draw_pixel(img,x,y,color);
        //if( (x < img->bmih.width && y < img->bmih.height && x >= 0 && y >= 0) || (x + (thickness / 2) < img->bmih.width && y + (thickness / 2) < img->bmih.height && x + (thickness / 2) >= 0 && y + (thickness / 2)>= 0) || (x - (thickness / 2) < img->bmih.width && y - (thickness / 2) < img->bmih.height && x - (thickness / 2) >= 0 && y - (thickness / 2)>= 0)){
            if (thickness % 2 == 0) {
                fill_circle(img, x, y, thickness / 2, color);
            } else if (thickness == 1) {
                fill_circle(img, x, y, 0, color);
            } else {
                fill_circle(img, x, y, (thickness + 1) / 2, color);
            }
        //}
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void fill_zone(int i, int j, rgb color, rgb fill_color, BMPFile* img) {//img->data массив пикселей
    if (!check_coords(i, j, img->bmih) || checkColor(img->data[i][j], color) || checkColor(img->data[i][j], fill_color)) { return; }
    img->data[i][j] = fill_color;
    fill_zone(i + 1, j, color, fill_color, img);
    fill_zone(i - 1, j, color, fill_color, img);
    fill_zone(i, j + 1, color, fill_color, img);
    fill_zone(i, j - 1, color, fill_color, img);
}
int isInsideArea(coords polygonPoints[], int nAngle, coords point) {
    int i, j, c = 0;
    for (i = nAngle / 3, j = nAngle - 1; i < nAngle; j = i++) {
        if (((polygonPoints[i].y > point.y) != (polygonPoints[j].y > point.y)) &&
            (point.x - 1 < (polygonPoints[j].x - polygonPoints[i].x) * (point.y - polygonPoints[i].y ) / (polygonPoints[j].y - polygonPoints[i].y) + polygonPoints[i].x))
            c = !c;
    }
    return c;
}    
int isInsideArea1(coords polygonPoints[], int nAngle, coords point){    
    int i, j, c = 0;
    for (i = 0, j = nAngle - 1; i < nAngle / 2; j = i++) {
        if (((polygonPoints[i].y > point.y) != (polygonPoints[j].y > point.y)) &&
            (point.x < (polygonPoints[j].x - polygonPoints[i].x) * (point.y - polygonPoints[i].y ) / (polygonPoints[j].y - polygonPoints[i].y) + polygonPoints[i].x ))
            c = !c;
    }
    return c;
}
bool checkColor(rgb a1, rgb a2){
    if(a1.blue == a2.blue && a1.green == a2.green && a1.red == a2.red){
        return true;
    } else{
        return false;
    }
}

bool check_coords(int y, int x, BitmapInfoHeader data){
    return !(y < 0 || y >= data.height || x < 0 || x >= data.width);
}

void swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void drawingRectangle(rectangle data, BMPFile* img) {
    coords left_top = data.start;
    coords right_top = {data.start.x, data.end.y};
    coords left_bottom = {data.end.x, data.start.y};
    coords right_bottom = data.end;

    if (data.start.x > data.end.x) {
        swap(&data.start.x, &data.end.x);
    }
    if (data.start.y > data.end.y) {
        swap(&data.start.y, &data.end.y);
    }

    if (data.filled == 1) {
        for (int y = data.start.y; y < data.end.y + 1; y++) {
            for (int x = data.start.x; x < data.end.x + 1; x++) {
                draw_pixel(img, x, y, data.fill_color);
            }
        }
    }

    drawingLine(left_top, right_top, data.color, data.thickness, img);
    drawingLine(left_bottom, left_top, data.color, data.thickness, img);
    drawingLine(right_top, right_bottom, data.color, data.thickness, img);
    drawingLine(right_bottom, left_bottom, data.color, data.thickness, img);

    
}


void drawingHexagon(hexagon data, BMPFile* img) {
    coords l1 = {data.centre.x - (data.radius / 2), data.centre.y + data.radius * sqrt(3.0) / 2};
    coords l2 = {data.centre.x + (data.radius / 2), data.centre.y + data.radius * sqrt(3.0) / 2};
    coords l3 = {data.centre.x + data.radius, data.centre.y};
    coords l4 = {data.centre.x + (data.radius / 2), data.centre.y - data.radius * sqrt(3.0) / 2};
    coords l5 = {data.centre.x - (data.radius / 2), data.centre.y - data.radius * sqrt(3.0) / 2};
    coords l6 = {data.centre.x - data.radius, data.centre.y};
    coords polygon[6] = {l1, l2, l3, l4, l5, l6}; 
    if (data.filled == 1) {
        // Fill the first part of the hexagon
        for (int y = l4.y; y < l1.y; y++) {
            for (int x = l6.x; x < l3.x; x++) {
                coords point = {x, y};
                if (isInsideArea(polygon, 6, point)) {
                    draw_pixel(img, x, y, data.fill_color);
                }
            }
        }
        // Fill the other part of the hexagon
        for (int y = l4.y; y < l1.y; y++) {
            for (int x = l6.x; x < l3.x; x++) {
                coords point = {x, y};
                if (isInsideArea1(polygon, 6, point)) {
                    draw_pixel(img, x, y, data.fill_color);
                }
            }
        }
    }
    drawingLine(l1, l2, data.color, data.thickness, img);
    drawingLine(l2, l3, data.color, data.thickness, img);
    drawingLine(l3, l4, data.color, data.thickness, img);
    drawingLine(l4, l5, data.color, data.thickness, img);
    drawingLine(l5, l6, data.color, data.thickness, img);
    drawingLine(l6, l1, data.color, data.thickness, img);
}
void copy_and_paste_area(BMPFile* img, coords start, coords end, coords dest_start) {
    if (start.x > end.x) {
        swap(&start.x, &end.x);
    }
    if (start.y > end.y) {
        swap(&start.y, &end.y);
    }
    if(start.x < 0) start.x = 0;
    if(start.y < 0) start.y = 0;
    if(start.x >= img->bmih.width) start.x = img->bmih.width - 1;
    if(start.y >= img->bmih.height) start.y = img->bmih.height - 1;

    if(end.x < 0) end.x = 0;
    if(end.y < 0) end.y = 0;
    if(end.x >= img->bmih.width) end.x = img->bmih.width - 1;
    if(end.y >= img->bmih.height) end.y = img->bmih.height - 1;

    if(dest_start.x < 0) dest_start.x = 0;
    if(dest_start.y < 0) dest_start.y = 0;
    if(dest_start.x >= img->bmih.width) dest_start.x = img->bmih.width - 1;
    if(dest_start.y >= img->bmih.height) dest_start.y = img->bmih.height - 1;

    int width = end.x - start.x;
    int height = end.y - start.y;
 
    // Создаем временный буфер для хранения скопированной области
    rgb** temp_buffer = (rgb**)malloc(sizeof(rgb*) * height);
    if (!temp_buffer) {
        printf("Memory allocation failed.\n");
        return;
    }
    for (int i = 0; i < height; i++) {
        temp_buffer[i] = (rgb*)malloc(sizeof(rgb) * width);
        if (!temp_buffer[i]) {
            printf("Memory allocation failed.\n");
            // Освобождаем ранее выделенную память
            for (int j = 0; j < i; j++) {
                free(temp_buffer[j]);
            }
            free(temp_buffer);
            return;
        }
    }

    // Копируем область изображения во временный буфер
    for (int y = start.y; y < end.y; y++) {
        for (int x = start.x; x < end.x; x++) {
            if( y < img->bmih.height &&  x < img->bmih.width)   {
                temp_buffer[y - start.y][x - start.x] = img->data[y][x];
            }
        }

   }

    // Вставляем скопированную область в указанное место в изображении
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(dest_start.y + y < img->bmih.height && dest_start.x + x < img->bmih.width)   {
                img->data[dest_start.y + y][dest_start.x + x] = temp_buffer[y][x];
            }
        }
    }

    // Освобождаем временный буфер
    for (int i = 0; i < height; i++) {
        free(temp_buffer[i]);
    }
    free(temp_buffer);
}


void drawVertex(BMPFile* img, coords start, int size, rgb fill_color){
    int x, y;
    x=start.x;
    y=start.y;
    int kat = size/sqrt(2);
    int x0 = x;
    int y0=y+kat;

    img->data[y][x].red = fill_color.red;
    img->data[y][x].green = fill_color.green;
    img->data[y][x].blue = fill_color.blue;

    img->data[y+2*kat][x].red = fill_color.red;
    img->data[y+2*kat][x].green = fill_color.green;
    img->data[y+2*kat][x].blue = fill_color.blue;

    img->data[y+kat][x+kat].red = fill_color.red;
    img->data[y+kat][x+kat].green = fill_color.green;
    img->data[y+kat][x+kat].blue = fill_color.blue;

    img->data[y+kat][x-kat].red = fill_color.red;
    img->data[y+kat][x-kat].green = fill_color.green;
    img->data[y+kat][x-kat].blue = fill_color.blue;
    coords center;
    coords l4;
    center.x = start.x;
    center.y = start.y + size;
    l4.x = center.x - size;
    l4.y = center.y;

    coords a1={x, y};
    coords a2={x+kat, y+kat};
    coords a3={x-kat, y+kat};
    coords a4={x, y+2*kat};
    
    drawingLine(a1, a2, fill_color, 1, img);
    drawingLine(a1, a3, fill_color, 1, img);
    drawingLine(a2, a4, fill_color, 1, img);
    drawingLine(a3, a4, fill_color, 1, img);

    for(int i=0; i<=kat; i++){
        coords b1={x, y+i};
        coords b2={x+kat-i, y+kat};
        coords b3={x-kat+i, y+kat};
        coords b4={x, y+2*kat-i};
        drawingLine(b1, b2, fill_color, 1, img);
        drawingLine(b1, b3, fill_color, 1, img);
        drawingLine(b2, b4, fill_color, 1, img);
        drawingLine(b3, b4, fill_color, 1, img);
    }
    //drawingLine(center, l4, fill_color, 1, img);
}