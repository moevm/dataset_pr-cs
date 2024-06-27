#include "image_processing.h"


void set_color(Png *image, int x, int y, RGB color) {
  if (x < 0 || y < 0 || x >= image->width || y >= image->height)
    return;

  png_bytep px = &(image->row_pointers[y][x * PX_SIZE]);
  px[RED] = color.r;
  px[GREEN] = color.g;
  px[BLUE] = color.b;
}

RGB get_color(Png *image, int x, int y) {
  RGB color;

  png_bytep px = &(image->row_pointers[y][x * PX_SIZE]);
  color.r = px[RED];
  color.g = px[GREEN];
  color.b = px[BLUE];

  return color;
}

int max(int a, int b){
  return a > b ? a : b;
}

int min(int a, int b){
  return a < b ? a : b;
}

void change_coords(COORD* left_up, COORD* right_down){
  int x_change, y_change;
  if (right_down->x < left_up->x){
    x_change = right_down->x;
    right_down->x = left_up->x;
    left_up->x = x_change;
  }
  if (right_down->y < left_up->y){
    y_change = right_down->y;
    right_down->y = left_up->y;
    left_up->y = y_change;
  }
}

int check_in_pic(Png* image, int x, int y){
  return (x >= 0 && x < image->width && y >= 0 && y < image->height);
}

int valid_circle(int radius, int thickness, bool fill_flag, RGB* color, bool fill, int circle){
    if(radius <= 0 || thickness <= 0){
    	return 0;
    }
    if ((circle == 4 && !fill_flag && !fill) || (circle == 6 && fill_flag && fill) || (circle == 5 && !fill_flag && fill)) {
        return 1;
    }
    return 0;
}

int check_on_circle_line(int x, int y, int x0, int y0, int radius, int thickness){
    int flag1 = (x-x0)*(x-x0) + (y-y0)*(y-y0) <= (radius+(thickness)/2)*(radius+(thickness)/2);
    int flag2 = (x-x0)*(x-x0) + (y-y0)*(y-y0) >= (max(0, radius-(thickness)/2))*(max(0, radius-(thickness)/2));
    return flag1 && flag2;
}

int check_in_circle(int x, int y, int x0, int y0, int radius, int thickness)
{
    int flag = (x-x0)*(x-x0) + (y-y0)*(y-y0) <= (radius-thickness/2)*(radius-thickness/2);
    return flag;
}

void draw_circle(Png* image, COORD center_coords, int radius, int thickness, int fill_flag, RGB color, RGB fill_color){
  int x0 = center_coords.x;
  int y0 = center_coords.y;
    for (int y = max(0, y0-radius-thickness/2); y <= min(image->height-1, y0+radius+thickness/2); y++) {
        for (int x = max(0, x0-radius-thickness/2); x <= min(image->width-1, x0+radius+thickness/2); x++) {
            if (fill_flag && check_in_circle(x, y, x0, y0, radius, thickness)) {
                set_color(image, x, y, fill_color);
            }
            if (check_on_circle_line(x, y, x0, y0, radius, thickness)) {
                set_color(image, x, y, color);
            }
        }
    }
}

void swap(Png* image, int x1, int y1, int x2, int y2){
  RGB color1;
  RGB color2;

  color1 = get_color(image, x1, y1);
  color2 = get_color(image, x2, y2);

  set_color(image, x2, y2, color1);
  set_color(image, x1, y1, color2);
}

void set_area(int height, int width, COORD* left_up, COORD* right_down) {
  left_up->x = max(0, left_up->x);
  left_up->x = min(width-1, left_up->x);

  left_up->y = max(0, left_up->y);
  left_up->y = min(height-1, left_up->y);

  right_down->x = max(0, right_down->x);
  right_down->x = min(width-1, right_down->x);

  right_down->y = max(0, right_down->y);
  right_down->y = min(height-1, right_down->y);
}

void mirror_x(Png* image, COORD left_up, COORD right_down){
  set_area(image->height, image->width, &left_up, &right_down);

  int diff = right_down.x - left_up.x;

  for (int y = left_up.y; y < right_down.y; y++){
    int n = 0;
    for (int x = left_up.x; x <= left_up.x+(diff-1)/2; x++){
      if (check_in_pic(image, left_up.x+diff-n, y)){
        swap(image, x, y, left_up.x+diff-n, y);
      }
      n++;
    }
  }
}

void mirror_y(Png* image, COORD left_up, COORD right_down){
  set_area(image->height, image->width, &left_up, &right_down);
  RGB* color = (RGB *)malloc(sizeof(RGB) * (right_down.x - left_up.x));

  int n = 0;
  int diff = right_down.y - left_up.y;

  int i = 0;
  for (int x = left_up.x; x < right_down.x; x++){
    if (check_in_pic(image, x, right_down.y)){
      color[i]=get_color(image, x, right_down.y);
      i++;
    }
  }

  for (int y = left_up.y; y <= left_up.y+(diff-1)/2; y++){
    for (int x = left_up.x; x < right_down.x; x++){
      if (check_in_pic(image, x, left_up.y+diff-n)){
        swap(image, x, y, x, left_up.y+diff-n);
      }
    }
    n++;
  }

  i = 0;
  for (int x = left_up.x; x < right_down.x; x++){
    if (check_in_pic(image, x, right_down.y)){
      set_color(image, x, right_down.y, color[i]);
      i++;
    }
  }
}

void copy_pic(Png* image, COORD left_up, COORD right_down, COORD dest_left_up){
  set_area(image->height, image->width, &left_up, &right_down);

  RGB pixel;
  int diff_x = dest_left_up.x - left_up.x;
  int diff_y = dest_left_up.y - left_up.y;

  RGB** pixel_row_pointer = (RGB **)malloc(sizeof(RGB *) * (right_down.y - left_up.y + 1));
  for (int y = 0; y < right_down.y - left_up.y + 1; y++) {
    pixel_row_pointer[y] = (RGB *)malloc(sizeof(RGB) * (right_down.x - left_up.x));
  }
  
  for (int y = left_up.y; y < right_down.y; y++){
    for (int x = left_up.x; x < right_down.x; x++){
      if (check_in_pic(image, x+diff_x, y+diff_y)){
        pixel = get_color(image, x, y);
        pixel_row_pointer[y - left_up.y][x - left_up.x] = pixel;
      }
    }
  }
  
  for (int y = left_up.y; y < right_down.y; y++){
    for (int x = left_up.x; x < right_down.x; x++){
      if (check_in_pic(image, x+diff_x, y+diff_y)){
        set_color(image, x+diff_x, y+diff_y, pixel_row_pointer[y - left_up.y][x - left_up.x]);
      }
    }
  }
}

void contrast(Png* image, float alpha, int beta){
  RGB old;
  RGB new;

  for (int y = 0; y < image->height; y++){
    for (int x = 0; x < image->width; x++){
      old = get_color(image, x, y);
      new.r = (int)floorf(old.r*alpha + beta);
      new.g = (int)floorf(old.g*alpha + beta);
      new.b = (int)floorf(old.b*alpha + beta);
      if (new.r>255){
        new.r=255;
      }
      if (new.g>255){
        new.g=255;
      }
      if (new.b>255){
        new.b=255;
      }
      set_color(image, x, y, new);
    }
  }
}

void info(Png* image){
    printf("Info about PNG image:\n\
    width, height: %d, %d\n\
    color_type: %d\n\
    bit_depth: %d\n", image->width, image->height, image->color_type, image->bit_depth);
}

void choose_func(Png image, int flag, OPTS* options){
    switch(flag){
        case 1:
        if (!valid_circle(options->radius, options->thickness, options->fill_flag, &(options->color), options->fill, options->circle)) {
            exit(Error_args);
        }
        draw_circle(&image, options->center_coords, options->radius, options->thickness, options->fill_flag, options->color, options->fill_color);
        break;
        case 2:
        if (options->mirror != 3) {
            exit(Error_args);
        }
        change_coords(&(options->left_up_coords), &(options->right_down_coords));
        if (!strcmp(options->axis, "x")){
            mirror_x(&image, options->left_up_coords, options->right_down_coords);
        }
        else {
            mirror_y(&image, options->left_up_coords, options->right_down_coords);
        }
        break;
        case 3:
        if (options->copy != 3) {
            exit(Error_args);
        }
        change_coords(&(options->left_up_coords), &(options->right_down_coords));
        copy_pic(&image, options->left_up_coords, options->right_down_coords, options->dest_left_up_coords);
        break;
        case 4:
        if (options->contr != 2){
            exit(Error_args);
        }
        contrast(&image, options->alpha, options->beta);
        break;
        default:
        if (options->info_flag){
            info(&image);
            exit(0);
        }
    }
}

