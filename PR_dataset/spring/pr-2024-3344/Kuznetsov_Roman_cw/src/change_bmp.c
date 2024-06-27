#include "processing_bmp.h"

void check_boundary(int* x_min, int* x_max, int* y_min, int* y_max, int W, int H)
{
    if (*x_min < 0 && *y_min < 0) {
        *x_min = 0;
        *y_min = 0;
    } else if (*x_min < 0) {
        *x_min = 0;
    } else if (*y_min < 0) {
        *y_min = 0;
    }

    if (*x_max < 0 && *y_max < 0) {
        *x_max = 0;
        *y_max = 0;
    } else if (*x_max < 0) {
        *x_max = 0;
    } else if (*y_max < 0) {
        *y_max = 0;
    }

    if (*x_min > W) {
        *x_min = W - 1;
    }
    if (*y_min > H) {
        *y_min = H - 1;
    }
    if (*x_max > W) {
        *x_max = W - 1;
    }
    if (*y_max > H) {
        *y_max = H - 1;
    }
}

void mirror(BMPfile* bmp, int axis, coord left_up, coord right_down)
{
  int x_min = left_up.x;
  int y_min = left_up.y;
  int x_max = right_down.x;
  int y_max = right_down.y;
  int W = bmp->bmpih.width;
  int H = bmp->bmpih.height;
  
  check_boundary(&x_min, &x_max, &y_min, &y_max, W, H);
  
  rgb** temp = (rgb**)malloc((H) * sizeof(rgb*));
  if (!temp) {
    printf("Error of allocate height of zone\n");
    exit(0);
  }
  for(int i = 0; i < H; i++) {
    temp[i] = (rgb*)malloc((W) * sizeof(rgb));
    if (!temp[i]) {
      printf("Error of allocate width of zone\n");
      exit(0);
    }
  }
    
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      temp[y][x] = bmp->data[y][x];
    }
  }
  
  if (axis == 121) { //121 (ось y)
    for (int y = y_min; y <= y_max; y++) {
      for (int x = x_max; x >= x_min; x--) {
          bmp->data[y][x] = temp[y_max - y + y_min][x];
      }
    }
  } 
  else if (axis == 120) { //120 (ось x)
    for (int y = y_max; y >= y_min; y--) {
      for (int x = x_min; x <= x_max; x++) {
          bmp->data[y][x] = temp[y][x_max - x + x_min];
      }
    }
  } 
  
  for(int i = 0; i < H; i++) {
    free(temp[i]);
  }
  free(temp);
}

void collage(BMPfile* bmp, int count_y, int count_x) 
{

  int width = bmp->bmpih.width;
  int height = bmp->bmpih.height;

  int new_x = bmp->bmpih.width * count_x;
  int new_y = bmp->bmpih.height * count_y;

  // новое изображение
  BMPfile coll_bmp;
  coll_bmp.bmpfh = bmp->bmpfh;
  coll_bmp.bmpih = bmp->bmpih;
  coll_bmp.bmpih.width = new_x;
  coll_bmp.bmpih.height = new_y;
  coll_bmp.bmpfh.file_size += new_x * new_y * sizeof(rgb);
  coll_bmp.data = (rgb**)malloc(new_y * sizeof(rgb*));

  for (int i = 0; i < new_y; i++) {
    coll_bmp.data[i] = (rgb*)malloc(new_x * sizeof(rgb));
      if (coll_bmp.data[i] == NULL) {
        for (int j = 0; j < i; ++j) free(coll_bmp.data[j]);
          free(coll_bmp.data);
          exit(0);
      }
  }

  for (int i = 0; i < new_y; i++) {
    for (int j = 0; j < new_x; j++) {
      int curr_y = i % height;
      int curr_x = j % width;
      coll_bmp.data[i][j] = bmp->data[curr_y][curr_x];
    }
  }

  // замена исходного изображения
  free(bmp->data[0]);
  free(bmp->data);
  bmp->bmpih = coll_bmp.bmpih;
  bmp->bmpfh = coll_bmp.bmpfh;
  bmp->data = coll_bmp.data;
    
  /*for (int i = 0; i < new_y; i++) free(coll_bmp.data[i]);
  free(coll_bmp.data);*/
}



