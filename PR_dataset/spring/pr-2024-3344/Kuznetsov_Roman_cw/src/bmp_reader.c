#include "bmp_reader.h"

BMPfile* loadBMP(char* fname) 
{
  FILE* f = fopen(fname, "rb");
  if (!f) {
    printf("Ошибка загрузки файла '%s'\n", fname);
    exit(0);
  }

  BMPfile* bmp = (BMPfile*)malloc(sizeof(BMPfile));

  /*if (bmp->bmpih.comp != 0 || bmp->bmpih.bits_per_pixel != 24 || (*(unsigned short*)bmp->bmpfh.ID) != 0x4D42) {
    printf("Предоставленная версия bmp-файла неподдерживается программой.\nВведите флаг --help чтобы получить информацию о файле.\n");
    exit(0);
  }*/
  
  fread(&bmp->bmpfh, sizeof(BmpFileHeader), 1, f);
  fread(&bmp->bmpih, sizeof(BmpInfoHeader), 1, f);
  
  bmp->data = (rgb**)malloc(bmp->bmpih.height * sizeof(rgb*));//кол-во строк
  for(unsigned int i = 0; i < bmp->bmpih.height; i++) {
    bmp->data[i] = (rgb*)malloc(bmp->bmpih.width * sizeof(rgb));
  }
  
  readRowByRow(f, bmp);
  
  fclose(f);
  return bmp;
}
//-------------------------------------------------------------------------------
void readRowByRow(FILE* f, BMPfile* bmp)
{
  int bytes_per_pixel = bmp->bmpih.bits_per_pixel / 8; // кол-во байт на пиксель
  int row_size = bytes_per_pixel * bmp->bmpih.width; // размер одной строки пикселей в байтах
  int row_padding = (4 - (row_size % 4)) % 4; // кол-во байт, необходимых для выравнивания
  unsigned int rows_written = 0; // кол-во записанных в память строк
  unsigned char* row = (unsigned char*)malloc(row_size + row_padding); // память для строк изображения с учетом выравнивания
  
  fseek(f, bmp->bmpfh.offset_pixels, SEEK_SET); // переходим к началу изображения
  
  while(rows_written < bmp->bmpih.height) {
    fread(row, row_size + row_padding, 1, f); // считываем строку с учетом выравнивания
    
    for(int i = 0; i < row_size; i += bytes_per_pixel) { // считываем наоборот
      int pixel_index = i / bytes_per_pixel;
      bmp->data[bmp->bmpih.height - 1 - rows_written][pixel_index].red = row[i + 2];
      bmp->data[bmp->bmpih.height - 1 - rows_written][pixel_index].green = row[i + 1];
      bmp->data[bmp->bmpih.height - 1 - rows_written][pixel_index].blue = row[i];
      
    }
    rows_written++;
  }
  free(row);
}
//-------------------------------------------------------------------------------
void writeBMP(char* fname, BMPfile* bmp)
{
  FILE* f = fopen(fname, "wb");
  if (!f) {
    printf("Ошибка загрузки файла \\'%s\\'\n", fname);
    exit(0);
  }
  
  fwrite(&bmp->bmpfh, sizeof(BmpFileHeader), 1, f);
  fwrite(&bmp->bmpih, sizeof(BmpInfoHeader), 1, f);
  
  int bytes_per_pixel = bmp->bmpih.bits_per_pixel / 8; 
  int row_size = bytes_per_pixel * bmp->bmpih.width; 
  int row_padding = (4 - (row_size % 4)) % 4; 
  unsigned int rows_written = 0;
  
  unsigned char* row = (unsigned char*)malloc(row_size + row_padding);
  
  fseek(f, bmp->bmpfh.offset_pixels, SEEK_SET);
  
  while(rows_written < bmp->bmpih.height) {
    for(int i = 0; i < row_size; i += bytes_per_pixel) {
      int pixel_index = i / bytes_per_pixel;
      row[i + 2] = bmp->data[bmp->bmpih.height - 1 - rows_written][pixel_index].red;
      row[i + 1] = bmp->data[bmp->bmpih.height - 1 - rows_written][pixel_index].green;
      row[i] = bmp->data[bmp->bmpih.height - 1 - rows_written][pixel_index].blue;
      
    }
    fwrite(row, row_size + row_padding, 1, f);
    rows_written++;
  }
  free(row);
}
//-------------------------------------------------------------------------------
void freeBMP(BMPfile* bmp)
{
  if (bmp) {
    for(unsigned int i = 0; i < bmp->bmpih.height; i++) free(bmp->data[i]);
    free(bmp->data);
    free(bmp);
  }
}
