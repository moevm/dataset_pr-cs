#include "main.h"

void print_PNG_info(Png * image)
{
    printf("	Информация об изображении:\n");
    printf("    Ширина изображения: %d\n", image -> width);
    printf("    Высота изображения: %d\n", image -> height);
    printf("    Тип цвета: %u\n", image -> color_type);
    printf("    Глубина цвета: %u\n", image -> bit_depth);
    printf("    Каналы: %u\n", image -> channels);
}

void print_help()
{   
   	printf("Course work for option 4.18, created by Timoshuk Evgenii\n"
        	   "Добро пожаловать в обработчик bmp изображений!\n"
               "Это программа с CLI для редактирования изображений в формате PNG!\n"
               "Поддерживаются файлы с глубиной цвета 8 бит, RGB, RGBa.\n"
               "Инструкция по работе программы.\n"
               "Важно! За один цикл программа может выполнить одно их последующих действий:\n"
               "- вывести основную информацию о файле;\n"
               "- инверсия цвета по области равной заданной окружности;\n"
               "- обрезка изображения;\n"
               "- нарисовать отрезок по заданным координатам, с толщиной и цветом;\n"
               "Для работы неоходимо терминал в папке с кодом и ввести ""./cw"" с последующими пользовательскими командами\n"
               "КЛЮЧ          ДЛИННАЯ ВЕРСИЯ         АРГУМЕНТЫ               ОПИСАНИЕ\n"
               "-h            --help                                         -помощь по программе\n"
               "-f            --info                                         -информация о файле\n"
               "-I            --inverse_circle    -C -r                      -инверсия цвета по области равной заданной окружности\n"
               "-l            --line              -s -e -c -t                -рисование линии\n"
               "-T            --trim              -L -R                      -расширение или обрезка изображения\n"
               "-i            --input                                        -имя обрабатываемого файла\n"
               "-o            --output                                       -имя обработанного файла\n"
               "АРГУМЕНТ      ДЛИННАЯ ВЕРСИЯ        ТИП                      ОПИСАНИЕ\n"
               "-с            --color               3 целых числа от 0 до 255 через точку, красная, зеленая, синяя компонента соответственно\n"
               "-t            --thickness           целое числа, толщина линии\n"
               "-s            --start               два целых числа через точку, начало рисовании линии\n"
               "-e            --end                 два целых числа через точку, конец рисовании линии\n"      
               "-L            --left_up             два целых числа через точку, координаты начало инверсии_цвета изображения\n"           
               "-R            --right_down          два целых числа через точку, координаты конца инверсии_цвета изображения\n"           
        ); 
}

void panic(const char *message){
	printf("%s\n", message);
	exit(EXIT_CODE);
}
void clise_file(FILE *fp, const char *errorMessage){
	panic(errorMessage);
	fclose(fp);
}

int circle_calculate_func(int start_x, int start_y, int end_x, int end_y, int radius)
{
    return ((start_x - end_x) * (start_x - end_x) + (start_y - end_y) * (start_y - end_y)) <= (radius*radius);
}

void read_image(const char * filename, Png * image)
{
    FILE * fp = fopen(filename, "rb");

    if (!fp) {
        panic(ERROR_MESSAGE);
    }

    unsigned char header[PNG_SIGNATURE_BYTES];
    if (fread(header, 1, PNG_SIGNATURE_BYTES, fp) != PNG_SIGNATURE_BYTES) {
        clise_file(fp, ERROR_MESSAGE);
        
    }

    int is_png = !png_sig_cmp(header, 0, PNG_SIGNATURE_BYTES);
    if (!is_png) {
        clise_file(fp, ERROR_MESSAGE);
        
    }

    image -> png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image -> png_ptr) {
       clise_file(fp, ERROR_READ);
    }

    image -> info_ptr = png_create_info_struct(image -> png_ptr);
    
    if (!image -> info_ptr) {
        clise_file(fp, ERROR_INFORMATION);
    }

    png_init_io(image -> png_ptr, fp);
    png_set_sig_bytes(image -> png_ptr, PNG_SIGNATURE_BYTES);
    png_read_info(image -> png_ptr, image -> info_ptr);

    image -> width = png_get_image_width(image -> png_ptr, image -> info_ptr);
    image -> height = png_get_image_height(image -> png_ptr, image -> info_ptr);
    image -> bit_depth = png_get_bit_depth(image -> png_ptr, image -> info_ptr);
    image -> color_type = png_get_color_type(image -> png_ptr, image -> info_ptr);
    image -> channels = png_get_channels(image -> png_ptr, image -> info_ptr);
    image -> row_pointers = (png_bytep *)malloc(image -> height * sizeof(png_bytep));

    for (int i = 0; i < image -> height; i++) {
        image -> row_pointers[i] = (png_byte *)malloc(png_get_rowbytes(image -> png_ptr, image -> info_ptr));
    }

    png_read_image(image -> png_ptr, image -> row_pointers);
    fclose(fp);
}

void write_image(const char * filename, Png * image)
{
    FILE * fp = fopen(filename, "wb");
    if (!fp) {
        panic(ERROR_OPEN);
    }
    image -> png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image -> png_ptr) {
        clise_file(fp, ERROR_WRITE);
    }

    image -> info_ptr = png_create_info_struct(image -> png_ptr);
    if (!image -> info_ptr) {
       clise_file(fp, ERROR_INFORMATION);
       
    }
    
    png_init_io(image -> png_ptr, fp);
    png_set_IHDR(image -> png_ptr, image -> info_ptr, image -> width, image -> height, image -> bit_depth, image -> color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(image -> png_ptr, image -> info_ptr);
    png_write_image(image -> png_ptr, image -> row_pointers);
    png_write_end(image -> png_ptr, NULL);
    fclose(fp);
}

void set_pixel(Png * image, int start_x, int start_y, int * color)
{
    if (start_x < 0 || start_y < 0 || start_x >= image -> width || start_y >= image -> height) {
        return;
    }
    png_bytep row = image -> row_pointers[start_y];
    png_bytep pixel = &row[start_x * image -> channels];
    pixel[0] = color[0];
    pixel[1] = color[1];
    pixel[2] = color[2];
          
}

void set_inverse_pixel(Png * image, int start_x, int start_y)
{
    if (start_x < 0 || start_y < 0 || start_x >= image -> width || start_y >= image -> height) {
        return;
    }
    png_bytep row = image -> row_pointers[start_y];
    png_bytep pixel = &row[start_y * image -> channels]; 
    pixel[0] = 255 - pixel[0];
    pixel[1] = 255 - pixel[1];
    pixel[2] = 255 - pixel[2];
}

void draw_inverse_circle (Png * image, int end_x, int end_y, int radius) 
{
	for (int i = end_y - radius - 1; i < end_y + radius + 1; i++) 
	        { 
	            for (int j = end_x - radius - 1; j <= end_x + radius + 1; j++) 
	            { 
	                if (circle_calculate_func(j, i, end_x, end_y, radius)) 
	                { 
	                    set_inverse_pixel(image, j, i);
	                } 
	            } 
	        } 
	    
	        set_inverse_pixel(image, end_x, end_y + radius); 
	        set_inverse_pixel(image, end_x, end_y - radius); 
	        set_inverse_pixel(image, end_x + radius, end_y); 
	        set_inverse_pixel(image, end_x - radius, end_y); 
}
void draw_circle_pixels(Png *image, int x, int y, int end_x, int end_y, int *color) {
    set_pixel(image, end_x + x, end_y + y, color);
    set_pixel(image, end_x + x, end_y - y, color);
    set_pixel(image, end_x - x, end_y + y, color);
    set_pixel(image, end_x - x, end_y - y, color);
    set_pixel(image, end_x + y, end_y + x, color);
    set_pixel(image, end_x + y, end_y - x, color);
    set_pixel(image, end_x - y, end_y + x, color);
    set_pixel(image, end_x - y, end_y - x, color);
}

void draw_circle (Png * image, int end_x, int end_y, int radius, int * color) 
{
    if (radius == 0){
        set_pixel(image, end_x, end_y, color);
        return;
    }

    if(radius == 1 || radius == 2){
        set_pixel(image, end_x, end_y, color);
        set_pixel(image, end_x + 1, end_y, color);
        set_pixel(image, end_x, end_y + 1, color);
        set_pixel(image, end_x - 1, end_y, color);
        set_pixel(image, end_x, end_y-  1, color);

        if(radius==2){
            set_pixel(image, end_x + 1, end_y + 1, color);
            set_pixel(image, end_x + 1, end_y - 1, color);
            set_pixel(image, end_x - 1, end_y + 1, color);
            set_pixel(image, end_x - 1, end_y - 1, color);
            set_pixel(image, end_x + 2, end_y, color);
            set_pixel(image, end_x,end_y + 2, color);
            set_pixel(image, end_x - 2, end_x, color);
            set_pixel(image, end_x, end_y - 2, color);
        }
        return;
    }

    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;

    while (y >= x){
        draw_circle_pixels(image, x, y, end_x, end_y, color);

        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)){
            delta += 2 * (++x) + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)){
            delta -= 2 *(--y) + 1;
            continue;
        }
        delta += 2 * ((++x) - (--y));
    }

    draw_circle(image, end_x, end_y, radius / 2, color);
}

void draw_line(Png * image, int start_x, int start_y, int end_x, int end_y, int thickness, int * color)
{
    int delta_x = abs(end_x - start_x);
    int step_x = start_x < end_x ? 1 : -1;
    int delta_y = abs(end_y - start_y);
    int step_y = start_y < end_y ? 1 : -1;
    int error = delta_x - delta_y;
    int error2;
    draw_circle(image, end_x, end_y, thickness / 2, color);
    while(start_x != end_x || start_y != end_y) {
        draw_circle(image, start_x, start_y, thickness / 2, color);
        error2 = 2 * error;
        if (error2 > -delta_y) {
            error -= delta_y;
            start_x += step_x;
        }
        if (error2 < delta_x) {
            error += delta_x;
            start_y += step_y;
        }
    }
}
void set_contrast_pixel(Png * image, int start_x, int start_y, float alpha, int beta)
{
    if (start_x < 0 || start_y < 0 || start_x >= image -> width || start_y >= image -> height) {
        return;
    }
    png_bytep row = image -> row_pointers[start_y];
    png_bytep pixel = &row[start_x * image -> channels];
    int color_r = floor(alpha*pixel[0] + beta) ;
    int color_g = floor(alpha*pixel[1] + beta) ;
    int color_b = floor(alpha*pixel[2] + beta) ;
    if(color_r < 0){
    	color_r = 0;
    }
    if(color_g < 0){
        color_g= 0;
    }
    if(color_b < 0){
        color_b = 0;
    }
    if(color_r > 255){
        color_r = 255;
    }
    if(color_g > 255){
        color_g = 255;
    }
    if(color_b > 255){
        color_b = 255;
    }
    pixel[0] = color_r;
    pixel[1] = color_g;
    pixel[2] = color_b;
          
}
void contrast_image(Png * image, float alpha, int beta){
	int width = image->width;
	int height = image->height;
	for(int x = 0; x<width; x++){
		for(int y = 0; y<height; y++){
			set_contrast_pixel(image, x,y, alpha, beta);
		}
	}
	
}

void adjust_coordinates(Png *image, int *start_x, int *start_y, int *end_x, int *end_y) {
    int old_width = image->width;
    int old_height = image->height;

    if (*start_x < 0) {
        *start_x = 0;
    }
    if (*end_x < 0) {
        *end_x = 0;
    }
    if (*start_y < 0) {
        *start_y = 0;
    }
    if (*end_y < 0) {
        *end_y = 0;
    }
    if (*start_x >= old_width) {
        *start_x = old_width;
    }
    if (*end_x >= old_width) {
        *end_x = old_width;
    }
    if (*end_y >= old_height) {
        *end_y = old_height;
    }
    if (*start_y >= old_height) {
        *start_y = old_height;
    }
}

void trim_and_resize_image(Png *image, int start_x, int start_y, int end_x, int end_y) {
    adjust_coordinates(image, &start_x, &start_y, &end_x, &end_y);

    if (start_x == end_x || start_y == end_y) {
        panic(ERROR_PRUNING);
    }

    int pad_x = start_x < end_x ? start_x : end_x;
    int pad_y = start_y < end_y ? start_y : end_y;

    int new_width = abs(end_x - start_x);
    int new_height = abs(end_y - start_y);

    if (new_width <= 0 || new_height <= 0) {
        panic(ERROR_SIZE);
    }

    for (int x = 0; x < new_width; x++) {
        for (int y = 0; y < new_height; y++) {
            int color[3];
            png_bytep row = image->row_pointers[y + pad_y];
            png_bytep pixel = &row[(x + pad_x) * image->channels];
            color[0] = pixel[0];
            color[1] = pixel[1];
            color[2] = pixel[2];
            set_pixel(image, x, y, color);
        }
    }

    image->width = new_width;
    image->height = new_height;
}

void processOptions(int argc, char *argv[]) {
int opt;
	    int result_assigment = 0;
	    
	    char * output_file = NULL;
	    char * input_file = NULL;
	    
	    int line_flag = 0;
	    int info_flag = 0;
	    int trim_flag = 0;
	    int help_flag = 0;
	    int output_flag = 0;
	    int input_flag = 0;
	    int inverse_circle_flag = 0;
	    int action_flag = 0;
	    int contrast_flag = 0;
	
	    int start_flag = 0;
	    int end_flag = 0;
	    int color_flag = 0;
	    int thickness_flag = 0;
	    int center_flag = 0;
	    int radius_flag = 0;
	    int left_up_flag = 0;
	    int right_down_flag = 0;
	    int alpha_flag = 0;
	    int beta_flag = 0;
	
	    Liner line;
	    Inverser inverser;
	    Data data;
	    Trim trim;
	    Contrast contrast;
	
	    char * opts = SHORT_OPTIONS;
	        static struct option long_options[] = {
	            {OPTION_OUTPUT},
	            {OPTION_INPUT},
	            {OPTION_LINE},
	            {OPTION_START},
	            {OPTION_END},
	            {OPTION_COLOR},
	            {OPTION_THICKNESS},
	            {OPTION_INFO},
	            {OPTION_INVERSE_CIRCLE},
	            {OPTION_CENTER},
	            {OPTION_RADIUS},
	            {OPTION_TRIM},
	            {OPTION_LEFT_UP},
	            {OPTION_RIGHT_DOWN},
	            {OPTION_HELP},
	            {OPTION_CONTRAST},
	            {OPTION_ALPHA},
	            {OPTION_BETA},
	            {VOID_OPTION}
	        };
	        opt = getopt_long(argc, argv, opts, long_options, NULL);
	        while (opt != FINISH_OPTS) {
	        switch (opt) {
	            case SHORT_FLAG_HELP:
	                print_help();
	                return;
	            case SHORT_FLAG_OUTPUT:
	                output_flag++;
	                output_file = optarg;
	                break;
	            case SHORT_FLAG_INPUT:
	                input_flag++;
	                input_file = optarg;
	                break;
	            case SHORT_FLAG_INFO:
	                info_flag++;
	                break;
	            case SHORT_FLAG_LINE:
	                line_flag++;
	                break;
	            case SHORT_FLAG_INVERSE_CIRCLE:
	                inverse_circle_flag++;
	                break;
	            case SHORT_FLAG_TRIM:
	                trim_flag++;
	                break;
	            case SHORT_FLAG_CONTRAST:
	            	contrast_flag++;
	            	break;
	            case SHORT_FLAG_ALPHA:
	           		result_assigment = sscanf(optarg, "%f", &data.alpha);
	           		if (!result_assigment){
	          	        panic("Ошибка: неверная компонента");
	            	}
	            	if(data.alpha <= 0){
	            		panic("Ошибка: Альфа должна быть больше 0");
	            	}
		           	alpha_flag++;
	            	break;
	            case SHORT_FLAG_BETA:
	           		result_assigment = sscanf(optarg, "%d", &data.beta);
	           		if (!result_assigment){
	          	        panic("Ошибка: неверная компонента");
	            	}
		           	beta_flag++;
	            	break;
	            case SHORT_FLAG_START:
	                result_assigment = sscanf(optarg, "%d.%d", &data.start_x, &data.start_y);
	                if (result_assigment != 2){
	                 	panic("Ошибка: неверный формат координат.");
	                }
	                start_flag++;
	                break;
	            case SHORT_FLAG_CENTER:
	                result_assigment = sscanf(optarg, "%d.%d", &data.start_x, &data.start_y);
	                if (result_assigment != 2){
	                  	panic("Ошибка: неверный формат координат.");
	                }
	                center_flag++;
	                break;    
	            case SHORT_FLAG_END:
	                result_assigment = sscanf(optarg, "%d.%d", &data.end_x, &data.end_x);
	                if (result_assigment != 2){
	                  	panic("Ошибка: неверный формат координат.");
	                }
	                end_flag++;
	                break;
	            case SHORT_FLAG_LEFT_UP:
	                result_assigment = sscanf(optarg, "%d.%d", &data.start_x, &data.start_y);
	                if (result_assigment != 2){
	                  	panic("Ошибка: неверный формат координат.");
	                }
	                left_up_flag++;
	                break;
	            case SHORT_FLAG_RIGHT_DOWN:
	                result_assigment = sscanf(optarg, "%d.%d", &data.end_x, &data.end_y);
	                if (result_assigment != 2){
	                	panic("Ошибка: неверный формат координат.");
	                }
	                right_down_flag++;
	                break;
	            case SHORT_FLAG_RADIUS:
	            	result_assigment = sscanf(optarg, "%d", &data.radius);
	            	if (!result_assigment){
	            		panic("Ошибка: неверный радиус");
	            	}
		           	radius_flag++;
	            	break;
	            case SHORT_FLAG_THICKNESS:
	            	result_assigment = sscanf(optarg, "%d", &data.thickness);
					if (!result_assigment){
						panic("Ошибка: неверный формат толщины");
					}
	                thickness_flag++;
	                break;
	            case SHORT_FLAG_COLOR:
					result_assigment = sscanf(optarg, "%d.%d.%d", &data.border_color[0], &data.border_color[1], &data.border_color[2]);
	                if (result_assigment != 3) {
	                   	panic("Ошибка: Неверный формат цвета.");
	                }
	                for (int i = 0; i < 3; i++) {
	                    if (data.border_color[i] < 0 || data.border_color[i] > 255) {
	                        panic("Ошибка: Компонента цвета должна быть в диапазоне 0-255.");
	                    }
	                }
	                color_flag++;
	                break;
	            default:
	                panic("Ошибка: Неверный флаг.");
	           		break;
	        }
	        opt = getopt_long(argc, argv, opts, long_options, NULL);
	    }
	
	    if ((line_flag > 0 && inverse_circle_flag > 0) || (line_flag > 0 && trim_flag > 0) || (trim_flag > 0 && inverse_circle_flag > 0) || (line_flag > 0 && inverse_circle_flag > 0 && trim_flag > 0)) {
	        panic( "Нельзя использовать несколько функций вместе.");
	    }
	
	    if (line_flag > 1 || inverse_circle_flag > 1 || trim_flag > 1 || help_flag > 1 || info_flag > 1 || start_flag > 1 || end_flag > 1 || thickness_flag > 1 || color_flag > 1 || right_down_flag > 1 || radius_flag > 1 || center_flag > 1 || radius_flag > 1 || left_up_flag > 1 || output_flag > 1 || input_flag > 1) {
	        panic("Ошибка: флаги могут быть использованы только один раз");
	    }
	
	    if (optind < argc && input_file == NULL) {
	        if (strcmp(argv[optind], output_file) == 0) {
	            panic("Ошибка: имя входного файла и имя выходного файла не должны совпадать.");
	        }
	        input_file = argv[optind];
	    }
	    
	    if (input_file == NULL) {
	        panic("Ошибка: Входной файл не указан.");
	    }
	
	    if (line_flag || trim_flag || inverse_circle_flag || info_flag || contrast_flag){
	    	action_flag = 1;
	    }
	
	    Png image;
	    read_image(input_file, &image);
	
	    if (info_flag) {
	        print_PNG_info(&image);
	        return;
	    }
	    if (input_flag && output_flag){
	    	if (!action_flag){
	    		panic("Ошибка: не выбрано действие с файлом.");
	    	}
	    	if(contrast_flag){
	    		if(contrast_flag && !(alpha_flag && beta_flag)){
	    			panic("Ошибка: Необходимо указать все параметры для флага --contrast.");
	    		}
	    		contrast.alpha = data.alpha;
	    		contrast.beta = data.beta;
	    		contrast_image(&image, contrast.alpha, contrast.beta);
	    	}
			if (inverse_circle_flag){
				if(inverse_circle_flag && !(center_flag && radius_flag)){
					panic("Ошибка: Необходимо указать все параметры для флага --inverse_circle.");
				}
				if(trim_flag && (end_flag || color_flag || start_flag || thickness_flag || right_down_flag || left_up_flag )){
					panic("Ошибка: Указаны лишние параметры");
				}
				inverser.start_x = data.start_x;
				inverser.start_y = data.start_y;
				inverser.radius = data.radius;
				draw_inverse_circle(&image, inverser.start_x, inverser.start_y, inverser.radius);
			}
	
			if (trim_flag){
				if(trim_flag && !(left_up_flag && right_down_flag)){
					panic("Ошибка: Необходимо указать все параметры для флага --trim.");
				}
				if(trim_flag && (end_flag || color_flag || start_flag || thickness_flag || center_flag || radius_flag )){
					panic("Ошибка: Указаны лишние параметры");
				}
				trim.start_x = data.start_x;
				trim.start_y = data.start_y;
				trim.end_x = data.end_x;
				trim.end_y = data.end_y;
				trim_and_resize_image(&image, trim.start_x, trim.start_y, trim.end_x, trim.end_y);
			}
	
		    if (line_flag) {
		        if (line_flag && !(end_flag && start_flag && thickness_flag && color_flag)) {
		            panic("Ошибка: Необходимо указать все параметры для флага --line.");
		        }
		        if (line_flag && (center_flag || radius_flag || left_up_flag || right_down_flag)) {
		            panic("Ошибка: Указаны лишние параметры");
		        }
		        line.start_x = data.start_x;
		        line.end_x = data.end_x;
		        line.start_y = data.start_y;
		        line.end_y = data.end_y;
		        line.thickness = data.thickness;
		        for (int i = 0; i < 3; i++){
		            line.border_color[i] = data.border_color[i];
		        }
		        if(line.thickness <=0){
		  			panic("Ошибка: Указанная толщина меньше либо равно 0.");
		  		}
		        draw_line(&image, line.start_x, line.start_y, line.end_x, line.end_y, line.thickness, line.border_color);
		    }
		    	
		    write_image(output_file, &image);
		    return;
	    }else{
	    	panic("Ошибка: входной || выходной файл не был указан.");
	    }
    
}

int main(int argc, char * argv[])
{
	processOptions(argc, argv);
	return 0;
}

    
    


