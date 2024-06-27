#include "image.h"

// Создание структуры color
color *init_color(double R, double G, double B)
{
    if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B > 255)) 
        return NULL;
    color *clr = (color *)calloc(1, sizeof(color));
    clr->R = R;
    clr->G = G;
    clr->B = B;
    return clr;
}

// Создание структуры point
point *init_point(double x, double y)
{
    point *pnt = (point *)calloc(1, sizeof(point));
    pnt->x = x;
    pnt->y = y;
    return pnt;
}

// Создание структуры pixel
pixel *init_pixel(point *pos, png_bytep byte)
{
    pixel *pxl = (pixel *)calloc(1, sizeof(pixel));
    pxl->pos = pos;
    pxl->byte = byte;
    return pxl;
}

// Очистка памяти, выделенной под пиксель
void free_pixel(pixel **pix)
{
    if (pix == NULL || *pix == NULL)
        return;
    if ((*pix)->pos != NULL) {
        free((*pix)->pos);
    }
    free(*pix);
    *pix = NULL;
}

// Создание структуры selection
selection *init_selection(image *img, point *start, point *end)
{
    point *new_start = init_point(MIN(MIN(start->x, end->x), img->width - 1),
                                  MIN(MIN(start->y, end->y), img->height - 1));
    point *new_end = init_point(MIN(MAX(start->x, end->x), img->width - 1),
                                  MIN(MAX(start->y, end->y), img->height - 1));
    selection *slct = (selection *)calloc(1, sizeof(selection));
    slct->start = new_start;
    slct->end = new_end;
    slct->img = img;
    return slct;
}

// Выделение всего изображения
selection *select_all(image *img)
{
    selection *slct = init_selection(img, init_point(0,0), init_point(img->width - 1, img->height - 1));
    return slct;
}

// Освобождение памяти из под выделенной области
void free_selection(selection **slct)
{
    if (slct == NULL || *slct == NULL)
        return;

    if ((*slct)->start != NULL)
        free((*slct)->start);

    if ((*slct)->end != NULL)
        free((*slct)->end);
    free(*slct);
    *slct = NULL;
}

// Создание нового изображения
image *init_image(uint width, uint height, color *clr)
{
    image *img = malloc(sizeof(image));
    img->path = NULL;
    img->width = width;
    img->height = height;
    img->color_type = PNG_COLOR_TYPE_RGB;
    img->bit_depth = 8;
    
    // Выделение памяти под массив байтов
    png_bytepp bytes = (png_bytepp)calloc(height, sizeof(png_bytep));
    for (uint y = 0; y < height; y++) {
        // Выделение памяти под байты для каждого пикселя
        bytes[y] = (png_bytep)calloc(width * 3, sizeof(png_byte));
        for (uint x = 0; x < width; x++) {
            png_bytep byte = bytes[y] + 3 * x;
            if (clr) {
                byte[0] = (png_byte)(MIN(MAX(0, clr->R), 255));
                byte[1] = (png_byte)(MIN(MAX(0, clr->G), 255));
                byte[2] = (png_byte)(MIN(MAX(0, clr->B), 255));
            }
        }
    }
    img->bytes = bytes;
    return img;
}

// Выгрузка изображения из файла
image *load_image(char *path) 
{
    // Открытие файла в двоичном режиме для чтения
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, STR_ERR_OPEN);
        return NULL;
    }

    // Создание структуры для чтения PNG изображения
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        fprintf(stderr, STR_ERR_PNG_STRUCT);
        fclose(f);
        return NULL;
    }

    // Создание структуры для хранения информации о PNG изображении
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fprintf(stderr, STR_ERR_PNG_STRUCT);
        // Освобождение памяти, занятой структурой png_structp
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(f);
        return NULL;
    }

    // Установка точки возврата для обработки ошибок при чтении
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, STR_ERR_READ_PNG);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(f);
        return NULL;
    }

    // Инициализация структуры png_structp для работы с файлом
    png_init_io(png_ptr, f);
    // Чтение информации о PNG изображении в структуру png_info
    png_read_info(png_ptr, info_ptr);

    uint width = png_get_image_width(png_ptr, info_ptr);
    uint height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    if (color_type != PNG_COLOR_TYPE_RGB || bit_depth != 8) {
        fprintf(stderr, STR_ERR_COLOR);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(f);
        return NULL;
    }

    // Выделение памяти под массив байтов (указатели на строки)
    png_bytepp bytes = (png_bytepp)malloc(height * sizeof(png_bytep));
    for (uint y = 0; y < height; y++) {
        // Выделение памяти для каждой строки
        bytes[y] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }

    // Чтение изображения в массив байтов
    png_read_image(png_ptr, bytes);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(f);
    image *img = malloc(sizeof(image));
    img->path = path;
    img->width = width;
    img->height = height;
    img->color_type = color_type;
    img->bit_depth = bit_depth;
    img->bytes = bytes;
    return img;
}

// Запись изображения в файл
int save_image(image *img, char *path)
{
    // Открытие файла для записи в бинарном режиме
    FILE *f = fopen(path, "wb");
    if (!f) {
        fprintf(stderr, STR_ERR_OPEN);
        return ERR_OPEN;
    }

    // Создание структуры png_structp для записи PNG-изображения
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        fprintf(stderr, STR_ERR_PNG_STRUCT);
        fclose(f);
        return ERR_PNG_STRUCT;
    }

    // Создание структуры png_info для хранения информации о PNG-изображении
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fprintf(stderr, STR_ERR_PNG_STRUCT);
        fclose(f);
        return ERR_PNG_STRUCT;
    }

    // Установка точки возврата для обработки ошибок при чтении
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, STR_ERR_WRITE_PNG);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(f);
        return ERR_PNGLIB_ERROR;
    }

    // Инициализация структуры png_structp для работы с файлом
    png_init_io(png_ptr, f);
    
    // Установка заголовка PNG изображения
    png_set_IHDR(png_ptr, info_ptr, img->width, img->height, img->bit_depth, 
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    // Запись информации о PNG изображении
    png_write_info(png_ptr, info_ptr);
    // Запись пиксельных данных в массив 
    png_write_image(png_ptr, img->bytes);
    // Завершение процесса записи изображения
    png_write_end(png_ptr, NULL);
    
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(f);
    return 0;

}

// Копирование изображения
image *copy_image(image *img)
{
    image *copy = malloc(sizeof(image));
    copy->path = img->path;
    copy->width = img->width;
    copy->height = img->height;
    copy->color_type = img->color_type;
    copy->bit_depth = img->bit_depth;
    
    png_bytepp bytes = (png_bytepp)malloc(img->height * sizeof(png_bytep));
    for (uint y = 0; y < img->height; y++) {
        bytes[y] = (png_bytep)malloc(img->width * PIXSIZE);
        memcpy(bytes[y], img->bytes[y], img->width * PIXSIZE);
    }
    copy->bytes = bytes;
    return copy;    
}

// Освобождение памяти изображения
void free_image(image **img)
{
    if (img == NULL || *img == NULL)
        return;
    for (uint y = 0; y < (*img)->height; y++) {
        free((*img)->bytes[y]);
    }
    free((*img)->bytes);
    free((*img));
    *img = NULL;
}

// Считывание по пикселям (подобие strtok)
pixel *read_selection(selection *slct)
{
    static uint iter;
    static selection *slct_img = NULL;
    if (slct != NULL) {
        iter = 0;
        slct_img = slct;
    }

    if (slct_img == NULL)
        return NULL;

    uint x1 = slct_img->start->x;
    uint y1 = slct_img->start->y;
    uint x2 = slct_img->end->x;
    uint y2 = slct_img->end->y;
    uint w = x2 - x1 + 1;
    uint h = y2 - y1 + 1;
    if (iter >= w * h)
        return NULL;

    point  *pos = init_point(x1 + iter % w, y1 + iter / w);
    png_bytep byte = (slct_img->img)->bytes[y1 + iter / w] + (x1 + iter % w) * 3; 
    pixel *pxl = init_pixel(pos, byte);
    iter++;
    return pxl;
}
