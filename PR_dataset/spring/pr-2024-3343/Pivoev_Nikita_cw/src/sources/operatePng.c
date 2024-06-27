#include "../include/operatePng.h"

void read_png_file(char *file_name, Png *image) {
    png_byte header[8];

    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        printf("Cannot read file: %s!\n", file_name);
        exit(40);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        printf("Probably, %s is not a png!\n", file_name);
        exit(41);
    }

    /* проверка сигнатуры png*/
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("Error in png structure!\n");
        exit(40); 
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("Error in png info-structure!\n");
        exit(40);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io!\n");
        exit(40);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    /* чтение файла */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during read_image!\n");
        exit(40);
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (int y = 0; y < image->height; ++y)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}


void write_png_file(char *file_name, Png *image) {
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        printf("Cannot read file: %s!\n", file_name);
        exit(40);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("Error in creating png structure!\n");
        exit(40);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("Error in png info-structure!\n");
        exit(40); 
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io!\n");
        exit(40);
    }

    png_init_io(image->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during header writing!\n");
        exit(40);
    }
    /* Настройка png изображения */
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
    png_write_info(image->png_ptr, image->info_ptr);


    /* Запись байтов */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing bytes!\n");
        exit(40);
    }

    png_write_image(image->png_ptr, image->row_pointers);

    /* Конец записи */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during end of writing!\n");
        exit(40);
    }

    png_write_end(image->png_ptr, NULL);

    /* Очистка памяти */
    for (int y = 0; y < image->height; ++y)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}

void setColor(png_byte* ptr, RGB color) {
    ptr[0] = color.r;
    ptr[1] = color.g;
    ptr[2] = color.b;
}

/*Задание 1 --copy*/
void copyArea(Png* image, OptParams* opt) {
    int color = 3;
    int currentY = 0;
    int currentX = 0;
    int sizeY = opt->copy_down - opt->copy_up;
    int sizeX = opt->copy_right - opt->copy_left;
    RGB canvas[sizeY][sizeX];

    /*Копирование области*/
    for (int y = opt->copy_up; y < opt->copy_down; ++y) {
        png_byte* row = image->row_pointers[y];

        for (int x = opt->copy_left; x < opt->copy_right; ++x) {
            png_byte* ptr = &(row[x * color]);
            canvas[currentY][currentX].r = ptr[0];
            canvas[currentY][currentX].g = ptr[1];
            canvas[currentY][currentX++].b = ptr[2];
        }
        currentX = 0;
        ++currentY;
    }

    /*Закраска*/
    for (int y = 0; y < sizeY; y++) {
        png_byte* row = image->row_pointers[opt->copy_dest_up + y];
        if (opt->copy_dest_up + y > image->height - 1)
            break;

        for (int x = 0; x < sizeX; x++) {
            if (opt->copy_dest_left + x > image->width - 1)
                break;
            png_byte* ptr = &(row[(opt->copy_dest_left + x) * color]);
            setColor(ptr, canvas[y][x]);
        }        

    }
}

/*Задание 2 --color_replace*/
void replaceColor(Png* image, OptParams* opt) {
    int color = 3;
    for (int y = 0; y < image->height; ++y) {
        png_byte *row = image->row_pointers[y];

        for (int x = 0; x < image->width; ++x) {
            png_byte* ptr = &(row[x * color]);

            if (opt->old_color.r == ptr[0] && opt->old_color.g == ptr[1] && opt->old_color.b == ptr[2])
                setColor(ptr, opt->new_color);
        }
    }
}

/*Задание 3 --ornament*/
void createOrnament(Png* image, OptParams* opt) {
    int color = 3;
    switch (opt->ornament_pattern) {
    case 0: { //rectangle
        int start;
        int maxY = 0;
        int maxX = 0;
        
        //обработка линий
        for (int y = 0; y < image->height; ++y) {
            int yValue = y / opt->thickness;
            if (y > image->height / 2)
                yValue = (image->height - 1 - y) / opt->thickness;

            start = opt->thickness * yValue;
            for (int x = start; x < image->width - start; ++x) {
                png_byte* ptr = &(image->row_pointers[y][x * color]);
                
                if (yValue % 2 == 0 && yValue / (opt->ornament_count * 2) < 1) {
                    setColor(ptr, opt->color);
                    if (y < image->height / 2)
                        maxY = yValue;
                }
            }
        }

        //обработка рядов
        for (int x = 0; x < image->width; ++x) {
            int xValue = x / opt->thickness;
            if (x > image->width / 2)
                xValue = (image->width -1 - x) / opt->thickness;
            
            start = opt->thickness * xValue;
            for (int y = start; y < image->height - start; ++y) {
                png_byte* ptr = &(image->row_pointers[y][x * color]);

                if (xValue % 2 == 0 && xValue / (opt->ornament_count * 2) < 1) {
                    setColor(ptr, opt->color);
                    if (x < image->width / 2)
                        maxX = xValue;
                }
            }
        }
    
        break;
    }
    case 1: { //circle
        int centerY = image->height / 2;
        int centerX = image->width / 2;
        int radius = (centerX > centerY) ? centerY : centerX;

        for (int y = 0; y < image->height; ++y) {
            png_byte* row = image->row_pointers[y];

            for (int x = 0 ; x < image->width; ++x) {
                png_byte* ptr = &(row[x * color]);
                if (sqrt(pow(x - centerX, 2) + pow(y - centerY, 2)) > radius)
                    setColor(ptr, opt->color);
            }
        }
        break;
    }

    case 2: { //semicircles
        double width = (double)(image->width - opt->ornament_count * opt->thickness) / (opt->ornament_count * 2);
        double height = (double)(image->height - opt->ornament_count * opt->thickness) / (opt->ornament_count * 2);
        int radiusX = ceil(width);
        int radiusY = ceil(height);

        int count = 0;
        int middleX[opt->ornament_count * 4];
        int middleY[opt->ornament_count * 4];

        /*Поиск центров полуокружностей*/
        /*Верхние центры*/
        int current =  opt->thickness / 2 + radiusX - 1;
        for (int i = 0; i < opt->ornament_count; ++i) {
            middleX[count] = current;
            middleY[count++] = 0;
            current += radiusX + opt->thickness + radiusX;
        }

        /*Левые центры*/
        current = opt->thickness / 2 + radiusY - 1;
        for (int i = 0; i < opt->ornament_count; ++i) {
            middleX[count] = 0;
            middleY[count++] = current;
            current += radiusY + opt->thickness + radiusY;
        }

        /*Правые центры*/
        current = opt->thickness / 2 + radiusY - 1;
        for (int i = 0; i < opt->ornament_count; ++i) {
            middleX[count] = image->width - 1;
            middleY[count++] = current;
            current += radiusY + opt->thickness + radiusY;
        }

        /*Нижние центры*/
        current = opt->thickness / 2 + radiusX - 1;
        for (int i = 0; i < opt->ornament_count; ++i) {
            middleX[count] = current;
            middleY[count++] = image->height - 1;
            current += radiusX + opt->thickness + radiusX;
        }


        /*Закраска*/
        for (int y = 0; y < image->height; ++y) {
            png_byte* row = image->row_pointers[y];

            for (int x = 0 ; x < image->width; ++x) {
                png_byte* ptr = &(row[x * color]);
                
                for (int i = 0; i < opt->ornament_count*4; ++i) {
                    int length = sqrt(pow(x - middleX[i], 2) + pow(y - middleY[i], 2));
                    
                    if ((middleX[i] == 0 || middleX[i] == image->width - 1) && length >= radiusY && length <= radiusY + opt->thickness)
                        setColor(ptr, opt->color);
                    
                    if ((middleY[i] == 0 || middleY[i] == image->height - 1) && length >= radiusX && length <= radiusX + opt->thickness)
                        setColor(ptr, opt->color);
                }
            }
        }
        break;
    }

    default:
        break;
    }
}

/*Задание 4 --filled_rects*/
void fillRects(Png* image, OptParams* opt) {
    int color = 3;
    int canvas[image->height][image->width];

    /*Замена всех нужных цветов на 1, остальных на 0*/
    for (int y = 0; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];

        for (int x = 0 ; x < image->width; ++x) {
            png_byte* ptr = &(row[x * color]);
            if (opt->color.r == ptr[0] && opt->color.g == ptr[1] && opt->color.b == ptr[2])
                canvas[y][x] = 1;
            else
                canvas[y][x] = 0;
        }
    }
    
    /*Увеличивание счётчика поданного цвета, если сверху него такой же цвет*/
    for (int y = 1; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];

        for (int x = 0 ; x < image->width; ++x) {
            png_byte* ptr = &(row[x * color]);
            if (canvas[y][x] == 1)
                canvas[y][x] += canvas[y-1][x];
        }
    }


    for (int y = 0; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];

        for (int x = 0 ; x < image->width; ++x) {
            png_byte* ptr = &(row[x * color]);
            if (canvas[y][x] > 0) {
                
                int check = 1;
                int sizeY = 0;
                int currentY = y;
                int sizeX = 0;
                int currentX = x;

                /*Вычисление размеров прямоугольника*/
                while (canvas[currentY][currentX] > 0) {
                    ++sizeX;
                    if (currentX == image->width - 1)
                        break;

                    ++currentX;
                }
                --currentX;

                while (canvas[currentY][currentX] > 0) {
                    ++sizeY;
                    if (currentX == image->height - 1)
                        break;

                    ++currentY;
                }
                --currentY;
                
                /*Проверка нижних пикселей прямоугольника*/
                /*Ввиду особенности алгоритма проверка других пикселей не нужно*/
                for (int i = 0; i < sizeX - 1; ++i) {
                    if (currentX - 1 == 0)
                        continue;

                    if (canvas[currentY][currentX] != canvas[currentY][currentX-1])
                        check = 0;
                    --currentX;
                }

                currentY = currentY - sizeY + 1;
                --currentX;
                --currentY;

                /*Проверка на обособленность прямоугольника сверху и снизу*/
                for (int i = 0; i < sizeX + 1; ++i) {
                    if (!(currentY < 0 || currentX < 0 || currentX > image->width - 1)) {
                        if (canvas[currentY][currentX] > 0)
                            check = 0;
                    }

                    if (!(currentY > image->height - 1 || currentX < 0 || currentX > image->width - 1)) {
                        if (canvas[currentY + sizeY + 1][currentX] > 0)
                            check = 0;
                    }
                    ++currentX;
                }
                
                
                currentX = currentX - sizeX - 1;
                ++currentY;

                /*Проверка на обособленность прямоугольника слева и справа*/
                for (int i = 0; i < sizeY + 1; ++i) {
                    if (!(currentY < 0 || currentX < 0 || currentY > image->height - 1)) {
                        if (canvas[currentY][currentX] > 0)
                            check = 0;
                    }

                    if (!(currentY > image->height - 1 || currentY < 0 || currentX > image->width - 1)) {
                        if (canvas[currentY][currentX + sizeX + 1] > 0)
                            check = 0;
                    }
                    ++currentY;
                }

                if (currentY != 0) {
                    if (canvas[y-1][x] > 0)
                        check = 0;
                }
                --currentY;

                /*Закраска*/
                if (check) {
                    --sizeX;
                    --sizeY;
                    int x0 = x - opt->thickness;
                    int y0 = y - opt->thickness;
                    int x1 = x + sizeX + opt->thickness;
                    int y1 = y + sizeY + opt->thickness;

                    for (int i = y0; i <= y1 && i < image->height; ++i) {
                        png_byte* row = image->row_pointers[i];
                        
                        for (int j = x0; j <= x1 && j < image->width; ++j) {
                            canvas[i][j] = -1;
                            png_byte* ptr = &(row[j * color]);

                            if (i < 0 || j < 0) {
                                continue;
                            }

                            if ((j < x) || (j > x + sizeX) || (i < y) || (i > y + sizeY))
                                setColor(ptr, opt->rects_border_color);
                        }
                    }
                }
            }
        }
    }
}

void fillOutside(Png* image, OptParams* opt) {
    RGB canvas[image->height][image->width];
    for (int y = 0; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];
        
        for (int x = 0; x < image->width; ++x) {
            png_byte* ptr = &(row[x * 3]);
            canvas[y][x].r = ptr[0];
            canvas[y][x].g = ptr[1];
            canvas[y][x].b = ptr[2];
        }
    }

    image->height += opt->thickness * 2;
    image->width += opt->thickness * 2;

    image->row_pointers = malloc(sizeof(png_bytep) * image->height);
    for (int y = 0; y < image->height; ++y)
        image->row_pointers[y] = malloc(3 * image->width + 1000);

    for (int y = 0; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];
        
        for (int x = 0; x < image->width; ++x) {
            png_byte* ptr = &(row[x * 3]);
            if (x < opt->thickness || y < opt->thickness || x >= image->width - opt->thickness || y >= image->height - opt->thickness) {
                setColor(ptr, opt->color);
            }
            else {
                ptr[0] = canvas[y-opt->thickness][x-opt->thickness].r;
                ptr[1] = canvas[y-opt->thickness][x-opt->thickness].g;
                ptr[2] = canvas[y-opt->thickness][x-opt->thickness].b;
            }
        }
    }
    
}