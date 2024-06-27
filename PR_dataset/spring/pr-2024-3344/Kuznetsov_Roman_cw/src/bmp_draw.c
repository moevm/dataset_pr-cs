#include "processing_bmp.h"

void romb(BMPfile* bmp, rgb color) 
{
  coord up = {bmp->bmpih.width / 2, 0};
  coord left = {0, bmp->bmpih.height / 2};
  coord down = {bmp->bmpih.width / 2, bmp->bmpih.height};
  coord right = {bmp->bmpih.width, bmp->bmpih.height / 2};
  coord up2 = {bmp->bmpih.width / 2, 0};
  coord left2 = {0, bmp->bmpih.height / 2};
  coord down2 = {bmp->bmpih.width / 2, bmp->bmpih.height};
  coord right2 = {bmp->bmpih.width, bmp->bmpih.height / 2};

  drawingLine(bmp, up, left, 1, color);
  drawingLine(bmp, left, down, 1, color);
  drawingLine(bmp, up, right, 1, color);
  drawingLine(bmp, right, down, 1, color);
  drawingLine(bmp, left, right, 1, color);
  drawingLine(bmp, up, down, 1, color);
  
  for (int y = 0; y < left.y; y++) { 
    up.y += 1;
    left.x += 1;
    drawingLine(bmp, up, left,1, color);
  }
  for (int y = 0; y < left.y; y++) { 
    up2.y += 1;
    right.x -= 1;
    drawingLine(bmp, up2, right, 1, color);
  }
  for (int y = left.y / 2; y < bmp->bmpih.height; y++) { 
    left2.x += 1;
    down.y -= 1;
    drawingLine(bmp, left2, down, 1, color);
  }
  for (int y = left.y / 2; y < bmp->bmpih.height; y++) { 
    right2.x -= 1;
    down2.y -= 1;
    drawingLine(bmp, right2, down2, 1, color);
  }
}

void drawPixel(BMPfile* bmp, int x, int y, rgb color)
{
  if (!(x < 0 || y < 0 || x >= (int)bmp->bmpih.width || y >= (int)bmp->bmpih.height)) 
    bmp->data[y][x] = color;
}

void drawThickness(BMPfile *bmp, int x, int y, int thickness, rgb color) 
{
  int W = bmp->bmpih.width;
  int H = bmp->bmpih.height;
  //итерируемся по диапазону, который охватывает пиксели с учетом толщины
  for (int j = -thickness / 2; j <= thickness / 2; j++) { //половина толщины в стороны
    for (int i = -thickness / 2; i <= thickness / 2; i++) {
      //находится ли текущий пиксель в пределах изображения
      if (!(x + i < 0 || y + j < 0 || x + i >= W || y + j >= H)) {
        //если текущий пиксель в пределах толщины добавляем 
        if (i * i + j * j <= (thickness / 2) * (thickness / 2)) bmp->data[y + j][x + i] = color;
}}}}

void drawingLine(BMPfile* bmp, coord start, coord end, int thickness, rgb color) 
{
  int x = start.x;
  int y = start.y;
    
  int x_end = end.x;
  int y_end = end.y;
    
  int dx = abs(x_end - x); //разница по оси x и y между начальной и конечной точкой
  int dy = abs(y_end - y);
    
  int orient_x = x < x_end ? 1 : -1; //направление движения по осям x и y
  int orient_y = y < y_end ? 1 : -1;
    
  int error = dx - dy; //переменную для отслеживания ошибки(отклонение по курсу)
  int error2;
    
  while (x != x_end || y != y_end) {
      drawPixel(bmp, x, y, color);
      if ((x < (int)bmp->bmpih.width && y < (int)bmp->bmpih.height && x >= 0 && y >= 0) || (x + (thickness / 2) < (int)bmp->bmpih.width && 
        y + (thickness / 2) < (int)bmp->bmpih.height && x + (thickness / 2) >= 0 && y + (thickness / 2)>= 0) || (x - (thickness / 2) < (int)bmp->bmpih.width && 
        y - (thickness / 2) < (int)bmp->bmpih.height && x - (thickness / 2) >= 0 && y - (thickness / 2)>= 0)) {  
        if (thickness % 2 == 0) drawThickness(bmp, x, y, thickness, color);
        else if (thickness == 1) drawPixel(bmp, x, y, color);
        else drawThickness(bmp, x, y, thickness + 1, color);
      }  
      error2 = 2 * error;
      //ошибка и перемещение по оси х
      if (error2 > -dy) {
        error -= dy;
        x += orient_x;
      }
      //ошибка и перемещение по оси у
      if (error2 < dx) {
        error += dx;
        y += orient_y;
}}}

void drawRectangle(BMPfile* bmp, coord left_up, coord right_down, int thickness, rgb color, int fill, rgb fill_color)
{
  coord left_down = {left_up.x, right_down.y};
  coord right_up = {right_down.x, left_up.y};
    
  if (fill == 1) {
    for (int y = left_up.y; y < right_down.y + 1; y++) {
      for (int x = left_up.x; x < right_down.x + 1; x++) drawPixel(bmp, x, y, fill_color);
  }}
    
  drawingLine(bmp, left_up, right_up, thickness, color);
  drawingLine(bmp, left_down, left_up, thickness, color);
  drawingLine(bmp, right_up, right_down, thickness, color);
  drawingLine(bmp, right_down, left_down, thickness, color);
}


void drawCircle(BMPfile* bmp, int x, int y, int r, int thickness, rgb color) 
{
  int x0 = r;
  int y0 = 0;
  int error = 1 - r;

  while (x0 >= y0) {
    // пиксели для текущего радиуса с учетом толщины линии
    drawThickness(bmp, x + x0, y + y0, thickness, color);
    drawThickness(bmp, x + y0, y + x0, thickness, color);
    drawThickness(bmp, x - y0, y + x0, thickness, color);
    drawThickness(bmp, x - x0, y + y0, thickness, color);
    drawThickness(bmp, x - x0, y - y0, thickness, color);
    drawThickness(bmp, x - y0, y - x0, thickness, color);
    drawThickness(bmp, x + y0, y - x0, thickness, color);
    drawThickness(bmp, x + x0, y - y0, thickness, color);

    // координаты и ошибка
    if (error <= 0) {
      y0 += 1;
      error += 2 * y0 + 1;
    }
    if (error > 0) {
      x0 -= 1;
      error -= 2 * x0 + 1;
    }
  }
}

void drawPentagram(BMPfile* bmp, int x, int y, int r, int thickness, rgb color)
{
  drawCircle(bmp, x, y, r, thickness, color);
  coord nodes[5];

  for (int i = 0; i < 5; i++) {
    double angle = (2 * 3.1415 / 5) * i + -3.1415 / 5;
    nodes[i].x = round(x + r * sin(angle));
    nodes[i].y = round(y + r * cos(angle));
  }

  for (int i = 0; i < 5; i++) drawingLine(bmp, nodes[i], nodes[(i + 2) % 5], thickness, color); // здесь nodes[(i+ 1) % 5] для пятиугольника
}
