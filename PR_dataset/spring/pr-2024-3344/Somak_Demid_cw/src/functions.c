#include "functions.h"
#include "secondary_func.h"

void description(void){
    printf("Course work for option 5.4, created by Demid Somak.\n");
    printf("\nВспомогательные функции:\n\n\
            -h, -help - справка, которую вы видите сейчас\n\n\
            -info - подробная информация об изображении\n\n\
            -i, -input - задаёт имя входного изображения\n\n\
            -o, -output - задаёт имя выходного изображения\n\n");
    printf("Функции по обработке изображений:\n\n\
            --inverse - инверсирование цвета заданной области\n\
                --left_up - верхняя левая координата области\n\
                --right_down - правая нижняя координата области\n\
            --gray - трансформация в Ч/Б заданной области\n\
                --left_up - верхняя левая координата области\n\
                --right_down - правая нижняя координата области\n\
            --resize - Изменение размера изображения с его обрезкой или расширением\n\
                --left, --right, --above, --below - количество измененых пикселей с определенной стороны(>0 - расширение, <0 - обрезка)\n\
                --color - цвет расширенной области\n\
            --line - рисование отрезка\n\
                --start, --end - координаты начала и конца отрезка\n\
                --thickness - ширина отрезка\n\
                --color - цвет отрезка\n");
}


void drawpixel(Rgb **arr, int W, int H,int y, int x, Rgb color) {
    if (!(x < 0 || y < 0 || x >= W || y >=  H)) {
        arr[y][x] = color;
    }
}


void inverse(Image * img,int lu_x, int lu_y, int rd_x, int rd_y){
    int H = img->bmih.height;
    int W = img->bmih.width;

    if(lu_x > rd_x && lu_y > rd_y){
        swap_int(&lu_x, &rd_x);
        swap_int(&lu_y, &rd_y);
    }


    if(rd_x > W) rd_x = W;
    if(rd_y > H) rd_y = H;
    if(lu_x < 0) lu_x = 0;
    if(lu_y < 0) lu_y = 0;

    for(int i = lu_y; i < rd_y; i++){
        for(int j = lu_x; j < rd_x; j++){
            img->pixels[i][j].r = 255 - img->pixels[i][j].r;
            img->pixels[i][j].g = 255 - img->pixels[i][j].g;
            img->pixels[i][j].b = 255 - img->pixels[i][j].b;
        }
    }
}

void black_white(Image *img,int lu_x, int lu_y, int rd_x, int rd_y){
    int H = img->bmih.height;
    int W = img->bmih.width;

    if(lu_x > rd_x && lu_y > rd_y){
        swap_int(&lu_x, &rd_x);
        swap_int(&lu_y, &rd_y);
    }

    if(rd_x > W) rd_x = W;
    if(rd_y > H) rd_y = H;
    if(lu_x < 0) lu_x = 0;
    if(lu_y < 0) lu_y = 0;

    for(int i = lu_y; i < rd_y; i++){
        for(int j = lu_x; j < rd_x; j++){
            int brightness = round((int)img->pixels[i][j].r * 0.299 + (int)img->pixels[i][j].g * 0.587 + (int)img->pixels[i][j].b * 0.114);
            brightness = (brightness > 255) ? 255 : (brightness < 0) ? 0 : brightness;
            img->pixels[i][j].r = brightness;
            img->pixels[i][j].g = brightness;
            img->pixels[i][j].b = brightness;
        }
    }
}

void resize(Image * img, char side[], int distance,Rgb color){
    Rgb ** new_arr;
    if(!strcmp(side, "below")){
        if (distance > 0){
            unsigned int H = img->bmih.height + distance;
            unsigned int W = img->bmih.width;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < H - distance; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    new_arr[i][j] = img->pixels[i][j];
                }
            }
            for(int i = H-distance; i < H; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    drawpixel(new_arr,W,H,i,j,color);
                }
            }
            img->bmih.height = H;
            img->bmih.imageSize += distance * row_len(img->bmih.width);
            img->bmfh.filesize += distance * row_len(img->bmih.width);
        }else{
            unsigned int H = img->bmih.height + distance;
            unsigned int W = img->bmih.width;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < H; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    new_arr[i][j] = img->pixels[i][j];
                }
            }
            img->bmih.height = H;
            img->bmih.imageSize += distance * row_len(img->bmih.width);
            img->bmfh.filesize += distance * row_len(img->bmih.width);
        }
    }else if (!strcmp(side, "above")){
        if (distance > 0){
            unsigned int H = img->bmih.height + distance;
            unsigned int W = img->bmih.width;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < distance; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    drawpixel(new_arr,W,H,i,j,color);
                }
            }
            for(int i = distance; i < H; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    new_arr[i][j] = img->pixels[i - distance][j];
                }
            }
            img->bmih.height = H;
            img->bmih.imageSize += distance * row_len(img->bmih.width);
            img->bmfh.filesize += distance * row_len(img->bmih.width);
        }else{
            unsigned int H = img->bmih.height;
            unsigned int W = img->bmih.width;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = (-1)*distance; i < H; i++){
                new_arr[i+distance] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    new_arr[i+distance][j] = img->pixels[i][j];
                }
            }
            img->bmih.height = H + distance;
            img->bmih.imageSize += distance * row_len(img->bmih.width);
            img->bmfh.filesize += distance * row_len(img->bmih.width);
        }        
    }else if (!strcmp(side, "left")){
        if (distance > 0){
            unsigned int H = img->bmih.height;
            unsigned int W = img->bmih.width + distance;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < H; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < distance; j++){
                    drawpixel(new_arr,W,H,i,j,color);
                }
                for(int j = distance; j < W; j++){
                    new_arr[i][j] = img->pixels[i][j-distance];
                }
            }
            img->bmih.width = W;
            img->bmih.imageSize += H * row_len(distance);
            img->bmfh.filesize += H * row_len(distance);
        }else{
            unsigned int H = img->bmih.height;
            unsigned int W = img->bmih.width;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < H; i++){
                new_arr[i] = malloc(row_len(W+distance));
                for(int j = (-1)*distance; j < W; j++){
                    new_arr[i][j+distance] = img->pixels[i][j];
                }
            }
            img->bmih.width = W + distance;
            img->bmih.imageSize += (-1)*(H * row_len((-1)*distance));
            img->bmfh.filesize += (-1)*(H * row_len((-1)*distance));
        }        
    }else if (!strcmp(side, "right")){
        if (distance > 0){
            unsigned int H = img->bmih.height;
            unsigned int W = img->bmih.width + distance;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < H; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W - distance; j++){
                    new_arr[i][j] = img->pixels[i][j];
                }
                for(int j = W - distance; j < W; j++){
                    drawpixel(new_arr,W,H,i,j,color);
                }
            }
            img->bmih.width = W;
            img->bmih.imageSize += H * row_len(distance);
            img->bmfh.filesize += H * row_len(distance);
        }else{
            unsigned int H = img->bmih.height;
            unsigned int W = img->bmih.width + distance;
            new_arr = malloc(H * sizeof(Rgb*));
            for(int i = 0; i < H; i++){
                new_arr[i] = malloc(row_len(W));
                for(int j = 0; j < W; j++){
                    new_arr[i][j] = img->pixels[i][j];
                }
            }
            img->bmih.width = W;
            img->bmih.imageSize += (-1)*(H * row_len((-1)*distance));
            img->bmfh.filesize += (-1)*(H * row_len((-1)*distance));
        }        
    }
    img->pixels = new_arr;
}


void fill_circle(Image *img, int x0, int y0, int rad,Rgb color) {
    unsigned int H = img->bmih.height;
    unsigned int W = img->bmih.width;
    int x = 0;
    int y = rad;
    int delta = 3 - 2 * y;
    int error = 0;
    while (y >= x) {
        drawpixel(img->pixels,W,H, y0 + y, x0 + x,color);
        drawpixel(img->pixels,W,H, y0 - y, x0 + x,color);
        drawpixel(img->pixels,W,H, y0 + y, x0 - x,color);
        drawpixel(img->pixels,W,H, y0 - y, x0 - x,color);
        drawpixel(img->pixels,W,H, y0 + x, x0 + y,color);
        drawpixel(img->pixels,W,H, y0 - x, x0 + y,color);
        drawpixel(img->pixels,W,H, y0 + x, x0 - y,color);
        drawpixel(img->pixels,W,H, y0 - x, x0 - y,color);
        delta += delta < 0 ? 4 * x + 6 : 4 * (x - y--) + 10;
        ++x;
    }
    for (int y = -rad; y <= rad; y++) {
        if ((y0+y)<0 || (y0+y)>=H){
            continue;
        }
        for (int x = -rad; x <= rad; x++) {
            if (((x0+x) >= 0) && ((x0+x) < W) && (x * x + y * y <= rad * rad)) {
                drawpixel(img->pixels,W,H, y0 + y, x0 + x,color);
            }
        }
    }
}

void drawThickLine(Image *img, int x1, int y1, int x2, int y2, int thickness, Rgb color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int e2;
    int x = x1;
    int y = y1;

    while (x != x2 || y != y2) {
        if (thickness % 2 == 0) {
            fill_circle(img, x, y, thickness / 2, color);
        } else if (thickness == 1) {
            fill_circle(img, x, y, 0, color);
        } else {
            fill_circle(img, x, y, (thickness + 1) / 2, color);
        }
        e2 = 90 * err;
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
void fillRhombus(Image *img,int x1, int y1,Rgb color,int side){
    if (side == 0){
        
        for(int j = x1; j < img->bmih.width/2; j++){
            drawpixel(img->pixels, img->bmih.width,img->bmih.height,y1, j,color);
        }
        
    }else if(side == 1){

        for(int j = img->bmih.width/2; j < x1; j++){
            drawpixel(img->pixels, img->bmih.width,img->bmih.height,y1, j,color);
        }
        
    }
}
void Rhombusline(Image *img, int x1, int y1, int x2, int y2, Rgb color,char* side){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int e2;
    int x = x1;
    int y = y1;

    while (x != x2 || y != y2) {
        drawpixel(img->pixels, img->bmih.width,img->bmih.height,y, x,color);
        if (!strcmp(side, "right")){
            fillRhombus(img, x,y, color,1);
        }else if(!strcmp(side, "left")){
            fillRhombus(img, x,y, color,0);
        }
        e2 = 90 * err;
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

void drawRhombus(Image *img, Rgb color){
    unsigned int H = img->bmih.height;
    unsigned int W = img->bmih.width;
    coords above_dot = {.x = 0,.y = H/2};
    coords below_dot = {.x = W,.y = H/2};
    coords right_dot = {.x = W/2,.y = H};
    coords left_dot = {.x = W/2,.y = 0};
    Rhombusline(img,above_dot.x,above_dot.y,right_dot.x,right_dot.y,color,"left");
    Rhombusline(img,right_dot.x,right_dot.y,below_dot.x,below_dot.y,color,"right");
    Rhombusline(img,below_dot.x,below_dot.y,left_dot.x,left_dot.y,color,"right");
    Rhombusline(img,left_dot.x,left_dot.y,above_dot.x,above_dot.y,color,"left");
}
