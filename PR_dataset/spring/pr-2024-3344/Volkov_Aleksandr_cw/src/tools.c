#include "tools.h"
#define M_PI 3.14159265358979323846

image *rectangle(selection *slct, uint stroke_width, color *stroke, color *fill) 
{
    // Заполнение прямоугольника цветом fill
    pixel *pix = read_selection(slct);
    while (pix) {
        if (pix->pos->x > slct->start->x + stroke_width / 2 && 
        pix->pos->x < slct->end->x - stroke_width / 2 &&
        pix->pos->y > slct->start->y + stroke_width/2 &&
        pix->pos->y < slct->end->y - stroke_width / 2) {
            put_pixel(pix, fill);
            free_pixel(&pix);
        } else {
            put_pixel(pix, stroke);
            free_pixel(&pix);
        }
        pix = read_selection(NULL);
    }

    // Отрисовка границы прямоугольника
    for (uint i = 0; i < (stroke_width + 2) / 2; i++) {
        // Верхняя граница
        for (uint x = slct->start->x - i; x <= slct->end->x + i; x++) {
            put_pixel(get_pixel(slct->img, x, slct->start->y - i), stroke);
            put_pixel(get_pixel(slct->img, x, slct->end->y + i), stroke);
        }

        // Левая и правая границы
        for (uint y = slct->start->y - i; y <= slct->end->y + i; y++) {
            put_pixel(get_pixel(slct->img, slct->start->x - i, y), stroke);
            put_pixel(get_pixel(slct->img, slct->end->x + i, y), stroke);
        }
    }

    return slct->img;
}

image* rectangle_for_ornament(selection* slct, uint stroke_width, color* stroke, color* fill)
{
    pixel* pix = read_selection(slct);
    while (pix){
        if (
            ((pix->pos->x - slct->start->x) < stroke_width)
          ||((pix->pos->y - slct->start->y) < stroke_width)
          ||((slct->end->x - pix->pos->x) < stroke_width)
          ||((slct->end->y - pix->pos->y) < stroke_width)
        ){
            put_pixel(pix, stroke);
        } else if (fill) {
            put_pixel(pix, fill);
        }
        free_pixel(&pix);
        pix = read_selection(NULL);
    }
    return slct->img;
}


// Разделение изображения на N M частей
image *split(image *img, uint N, uint M, uint stroke_width, color *stroke)
{
    if (N > img->width || M > img->height)
        return NULL;

    uint part_width = img->width / N;
    uint part_height = img->height / M;

    // Вертикальные линии:
    for (int i = 1; i < N; i++) {
        uint x = i * part_width;
        if (x > img->width - stroke_width / 2) {
            x = img->width - stroke_width / 2;
        }

        point *start = init_point(x - stroke_width / 2, 0);
        point *end = init_point(x + stroke_width / 2, img->height);
        rectangle_for_ornament(init_selection(img, start, end), stroke_width, stroke, stroke);
    }

    // Горизонтальные линии:
    for (int i = 1; i < M; i++) {
        uint y = i * part_height;
        if (y > img->height - stroke_width / 2) {
            y = img->height - stroke_width / 2;
        }
        point *start = init_point(0, y - stroke_width / 2);
        point *end = init_point(img->width, y + stroke_width / 2);
        rectangle_for_ornament(init_selection(img, start, end), stroke_width, stroke, stroke);
    }

    return img;
}

// Рисование окружности
void draw_circle(image* img, int center_x, int center_y, int radius, int thickness, color* color) {
    int outer_radius = radius + thickness / 2; // Внешний радиус
    int inner_radius = radius - thickness / 2; // Внутренний радиус

    for (int x = center_x - outer_radius + 1; x < center_x + outer_radius; ++x) {
        for (int y = center_y - outer_radius + 1; y < center_y + outer_radius; ++y) {
            // Вычисляем квадрат расстояния от текущего пикселя до центра окружности
            int distance_squared = (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y);
            
            // Проверяем, находится ли текущий пиксель в пределах толщины окружности
            if (distance_squared >= inner_radius * inner_radius && distance_squared <= outer_radius * outer_radius) {
                pixel* pix = get_pixel(img, x, y);
                if (pix) put_pixel(pix, color);
            }
        }
    }
}

// Рамка для изображения
image *frame(image* img, color* color, uint thickness, uint count, int pattern_type) {
    uint width = img->width;
    uint height = img->height;

    switch (pattern_type) {
        case FRAME_RECTANGLE: {
            // Начальные координаты для первого прямоугольника
            uint start_x = 0;
            uint start_y = 0;
            uint rect_width = width;
            uint rect_height = height;

            // Рисуем прямоугольники
            for (uint i = 0; i < count; i++) {
                // Инициализируем выделенную область для текущего прямоугольника
                point *start = init_point(start_x, start_y);
                point *end = init_point(start_x + rect_width - 1, start_y + rect_height - 1);
                selection *slct = init_selection(img, start, end);

                // Рисуем прямоугольник
                rectangle_for_ornament(slct, thickness, color, NULL);

                // Обновляем координаты и размеры для следующего прямоугольника
                start_x += thickness * 2; 
                start_y += thickness * 2; 
                rect_width -= 4 * thickness;
                rect_height -= 4 * thickness;

                free_selection(&slct);
            }
            break;
        }

        case FRAME_CIRCLE: {
            uint radius = MIN(width, height) / 2;
            uint center_x = width / 2;
            uint center_y = height / 2;

            for (uint y = 0; y < height; y++) {
                for (uint x = 0; x < width; x++) {
                    if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) > radius * radius) {
                        pixel* p = get_pixel(img, x, y);
                        put_pixel(p, color);
                    }
                }
            }
            break;
        }

        case FRAME_SEMICIRCLES: {
            int radius_x = ceil(((double)(width / count) / 2.0));
            int radius_y = ceil((double)((height / count) / 2.0));
            
            // Верхняя граница
            for (int i = radius_x; i < width + thickness; i += 2 * radius_x) {
                draw_circle(img, i, 0, radius_x, thickness + 1, color);
            }

            // Нижняя граница
            for (int i = radius_x; i < width + thickness; i += 2 * radius_x) {
                draw_circle(img, i, height, radius_x, thickness + 1, color);
            }

            // Левая граница
            for (int i = radius_y; i < height + thickness; i += 2 * radius_y) {
                draw_circle(img, 0, i, radius_y, thickness + 1, color);
            }

            // Правая граница
            for (int i = radius_y; i < height + thickness; i += 2 * radius_y) {
                draw_circle(img, width, i, radius_y, thickness + 1, color);
            }
            break;
        }

        default:
            // Неверный тип узора
            break;
    }
    return img;
}

// Поворот выделенной области на 90, 180 и 270 градусов
image* turn(selection* slct, int angle) {
    uint width = slct->end->x - slct->start->x;
    uint height = slct->end->y - slct->start->y;

    // Создание нового изображения с измененными размерами
    image* new_img = malloc(sizeof(image));
    if (new_img == NULL) {
        return NULL; // Ошибка выделения памяти
    }
    new_img->width = (angle == 180) ? width : height;
    new_img->height = (angle == 180) ? height : width;
    new_img->color_type = slct->img->color_type;
    new_img->bit_depth = slct->img->bit_depth;
    new_img->bytes = malloc(new_img->height * sizeof(png_bytep));
    if (new_img->bytes == NULL) {
        free(new_img);
        return NULL; // Ошибка выделения памяти
    }

    for (uint i = 0; i < new_img->height; i++) {
        new_img->bytes[i] = malloc(new_img->width * sizeof(png_byte) * 3); 
        if (new_img->bytes[i] == NULL) {
            // Освобождение ранее выделенной памяти
            for (uint j = 0; j < i; j++) {
                free(new_img->bytes[j]);
            }
            free(new_img->bytes);
            free(new_img);
            return NULL; // Ошибка выделения памяти
        }
    }

    // Поворот изображения
    for (uint y = slct->start->y; y < slct->end->y; y++) {
        for (uint x = slct->start->x; x < slct->end->x; x++) {
            uint src_x = x - slct->start->x;
            uint src_y = y - slct->start->y;
            uint dest_x, dest_y;

            // Вычисление новых координат пикселя после поворота
            switch (angle) {
                case 90:
                    dest_x = src_y;
                    dest_y = width - src_x - 1;
                    break;

                case 180:
                    dest_x = width - src_x - 1;
                    dest_y = height - src_y - 1;
                    break;

                case 270:
                    dest_x = height - src_y - 1;
                    dest_y = src_x;
                    break;

                default:
                    // Некорректный угол поворота
                    for (uint i = 0; i < new_img->height; i++) {
                        free(new_img->bytes[i]);
                    }
                    free(new_img->bytes);
                    free(new_img);
                    return NULL;
            }

            // Копирование пикселя в новое место
            memcpy(&new_img->bytes[dest_y][dest_x * 3], &slct->img->bytes[y][x * 3], 3);
        }
    }

    return new_img;
}

// Вставка повёрнутого изображения
image* rotate(image* img, selection* slct, int angle) {
    // Поворот выбранной области
    image* rotated_region = turn(slct, angle);
    if (rotated_region == NULL) {
        return NULL;
    }

    // Создание временной копии изображения
    image* temp_img = copy_image(img);
    if (temp_img == NULL) {
        free_image(&rotated_region);
        return NULL;
    }

    uint start_x = slct->start->x;
    uint start_y = slct->start->y;
    uint end_x = slct->end->x;
    uint end_y = slct->end->y;

    uint p1_x = slct->start->x;
    uint p1_y = slct->start->y;
    uint p2_x = slct->end->x;
    uint p2_y = p1_y;
    uint p3_x = slct->end->x;
    uint p3_y = slct->end->y;
    uint p4_x = p1_x;
    uint p4_y = p3_y;


    // Определение границ для вставки повернутой области
    uint new_start_x, new_start_y, new_end_x, new_end_y;
    double center_x = ((start_x + end_x) / 2.0);
    double center_y = ((start_y + end_y) / 2.0);

    int dx = 0;
    int dy = 0;
    int dxx = 0;
    int dyy = 0;
    double intPartX, fracPartX;
    fracPartX = modf((start_x + end_x) / 2.0, &intPartX);
    double intPartY, fracPartY;
    fracPartY = modf((start_y + end_y) / 2.0, &intPartY);
    
    // Смещение
    if (fracPartX == 0.0 && fracPartY == 0.0) {
        // Оба числа целые
        dx = 0;
        dy = 0;
    } else if (fracPartX == 0.0) {
        // Только X целый
        if (end_x - start_x < end_y - start_y) {
            dx = 0;
            dy = -1;
            dxx = 1;
            dyy = 1;
        } else if (end_x - start_x >= end_y - start_y) {
            dx = 0;
            dy = -1;
            dxx = 1;
            dyy = 1;
        }
    } else if (fracPartY == 0.0) {
        // Только Y целый
        if (img->width <= img->height) {
            dx = 0;
            dy = 1;
        } else if (img->width > img->height) {
            dx = -1;
            dy = 0;
            dxx = 1;
            dyy = 1;
        }
    } else {
        // Оба числа нецелые
        dy = 0;
        dx = 0;
    }

    switch (angle) {
        case 90:
            new_start_x = (uint)ceil((double)(-1 * (p4_y - center_y) + center_x)) + dx;
            new_start_y = (uint)ceil((double)((p4_x - center_x) + center_y)) + dy;
            new_end_x = ((-1 * (p2_y - center_y) + center_x) > img->width) ? img->width : (-1 * (p2_y - center_y) + center_x) + dx + dxx;
            new_end_y = (((p2_x - center_x) + center_y) > img->height) ? img->height : ((p2_x - center_x) + center_y) + dy + dyy;
            break;

        case 180:
            new_start_x = start_x;
            new_start_y = start_y;
            new_end_x = end_x;
            new_end_y = end_y;
            break;

        case 270:
            new_start_x = (uint)ceil((double)(-1 * (p4_y - center_y) + center_x)) + dx;
            new_start_y = (uint)ceil((double)((p4_x - center_x) + center_y)) + dy;
            new_end_x = ((-1 * (p2_y - center_y) + center_x) > img->width) ? img->width: (-1 * (p2_y - center_y) + center_x) + dx + dxx;
            new_end_y = (((p2_x - center_x) + center_y) > img->height) ? img->height: ((p2_x - center_x) + center_y) + dy + dyy; 
            break;
            
        default:
            free_image(&rotated_region);
            free_image(&temp_img);
            return NULL;
    }

    // Вставка повернутой области в исходное изображение
    for (uint y = ((int)new_start_y < 0) ? 0 : new_start_y; y < new_end_y; y++) {
        for (uint x = ((int)new_start_x < 0) ? 0 : new_start_x; x < new_end_x; x++) {
            uint src_x = x - new_start_x;
            uint src_y = y - new_start_y;
            uint dest_x = x;
            uint dest_y = y;
            memcpy(&temp_img->bytes[dest_y][dest_x * 3], &rotated_region->bytes[src_y][src_x * 3], 3);
        }
    }

    
    free_image(&rotated_region);
    free_image(&img);

    return temp_img;
}

image *compress(image *img, int num)
{
    uint new_width = img->width/num;
    uint new_height = img->height/num;
    image *new_img = malloc(sizeof(image));
    if (new_img == NULL)
        return NULL;
    new_img->width = new_width;
    new_img->height = new_height;
    new_img->color_type = img->color_type;
    new_img->bit_depth = img->bit_depth;
    new_img->bytes = malloc(new_img->height * sizeof(png_bytep));
    if (new_img->bytes == NULL) {
        free(new_img);
        return NULL;
    }
    
    for (int i = 0; i < new_img->height; i++) {
        new_img->bytes[i] = malloc(new_img->width * 3 * sizeof(png_bytep));
        if (new_img->bytes[i] == NULL) {
            for (uint j = 0; j < i; j++) {
                free(new_img->bytes[j]);
            }
            free(new_img->bytes);
            free(new_img);
            return NULL;
        }
    }

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            int sum_R = 0;
            int sum_G = 0;
            int sum_B = 0;
            int count = 0;
        
        for (int y = 0; y < num; y++) {
            for (int x = 0; x < num; x++){
                int src_y = i * num + y;
                int src_x = j * num + x;
                if (src_y < img->height && src_x < img->width) {
                    png_bytep src_pixel = img->bytes[src_y] + src_x * 3;
                    sum_R += src_pixel[0];
                    sum_G += src_pixel[1];
                    sum_B += src_pixel[2];
                    count++;
                }
            }
        }

        png_bytep dest_pixel = new_img->bytes[i] + j * 3;
        dest_pixel[0] = sum_R / count;
        dest_pixel[1] = sum_G / count;
        dest_pixel[2] = sum_B / count;
        }
    }
    return new_img;
}