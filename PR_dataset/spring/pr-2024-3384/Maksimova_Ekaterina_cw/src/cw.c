#include "input_output.h"
#include "toolkit.h"
#include "image.h"
#include <getopt.h>

void command_list(Image* image, Config config, int command, int flag_old_color, int flag_new_color, int flag_border_color, int flagcolor, int flag_size){
	switch (command){
            case 1:
            	if (flag_old_color && flag_new_color){
            		change_color(image, config.old_color, config.new_color);
            	}else{
            		fprintf(stderr, "error: no required parameter");
            		exit (40);
            	}
                break;
            case 2:
            	if (!config.pattern){
            		fprintf(stderr, "error: no required parameter");
            		exit (40);
            	}
                else if (strcmp(config.pattern, "rectangle") == 0){
               		if (config.thickness && config.count && config.thickness && flagcolor){
        				rectangle_ornament(image, config.count, config.color, config.thickness);
        			}else{
        				fprintf(stderr, "error: no required parameter");
            			exit (40);
        			}	
    			}
    			else if (strcmp(config.pattern, "circle") == 0){
    				if (flagcolor){
    					circle_ornament(image, config.color);
    				}else{
    					fprintf(stderr, "error: no required parameter");
            			exit (40);
    				}
    			}
    			else if (strcmp(config.pattern, "semicircles") == 0){
    				if (config.thickness && config.count && flagcolor){
    					semicircles_ornament(image, config.thickness, config.count, config.color);
    				}else{
    					fprintf(stderr, "error: no required parameter");
            			exit (40);
    				}
    			}
    			else {
					fprintf(stderr,"error: Unknown pattern\n");
					exit(40);
				}
                break;
            case 3:
            	if ( config.thickness && flagcolor && flag_border_color){
                	find_and_border_rectangle(image, config.thickness, config.color, config.border_color);
                }else{
                	fprintf(stderr,"error: Unknown pattern\n");
					exit(40);
                }
                break;
            case 4:
            	if (flag_size) {
            		blur_image(image, config.size);
            	} else{
    					fprintf(stderr, "error: no required parameter");
            			exit (40);
    			}
            default:
            	break;
    }
}

int main(int argc, char* argv[]) {
	
    if(argc == 1 || argc == 2){ //Запуск без аргументов
        print_help();
        return 0;
    }
    BitmapInfoHeader* bmif = malloc(sizeof(BitmapInfoHeader));  
    BitmapFileHeader* bmfh = malloc(sizeof(BitmapFileHeader));
    char* file_input = "sample.bmp";
    char* file_output = "out.bmp";
  	int flag_old_color = 0;
  	int flag_new_color = 0;
  	int flagcolor = 0;
  	int flag_border_color = 0;
  	int flag_size = 0;
    Config config;
    int command = 0;
    //короткие флаги
    const char* short_options = "hdcrfbi:o:L:N:B:C:P:T:O:s:";

    //соединяем длинные и короткие флаги
    const struct option long_options[] = {
            { "help", no_argument, NULL, 'h' },
            { "data", no_argument, NULL, 'd' },
            { "color_replace", no_argument, NULL, 'c' },
            { "ornament", no_argument, NULL, 'r' },
            { "filled_rects", no_argument, NULL, 'f' },
            { "blur", no_argument, NULL, 'b' },
			{ "input", required_argument, 0, 'i'},
        	{ "output", required_argument, 0, 'o'},
			{ "old_color", required_argument, 0, 'L'},
			{ "new_color", required_argument, 0, 'N'},
			{ "border_color", required_argument, 0, 'B'},
			{ "color", required_argument, 0, 'C'},
			{ "pattern", required_argument, 0, 'P'},
			{ "thickness", required_argument, 0, 'T'},
			{ "count", required_argument, 0, 'O'},
			{ "size", required_argument, 0, 's'},
            { NULL, 0, NULL, 0 }
    };

    int opt;
    int long_option_ind;

    opt = getopt_long(argc, argv,short_options, long_options, &long_option_ind); // возвращает -1, когда прошел по всем ключам
    
    while (opt != -1){
        switch (opt){
            case 'h':
                if(argc == 3){
                    print_help();
                    return 0;
                }else{
                    puts("Некорректный вызов подсказки.");
                    puts("Примеры корректного вызова подсказки:");
                    puts("./a.out (вызов программы без аргументов)");
                    puts("./a.out sample.bmp");
                    puts("./a.out sample.bmp -h");
                    return 0;
                }
                break;
            case 'd':
                if(argc == 3){
                    printFileHeader(*bmfh);
                    printInfoHeader(*bmif);
                    return 0;
                }else{
                    puts("Слишком много аргументов для получения информации об изображении");
                    puts("Пример корректного вызова: ./a.out sample.bmp -d");
                    return 0;
                }
                break;
            case 'c':
                command = 1;
                break;
            case 'r':
            	command = 2;
            	break;
            case 'f':
                command = 3;
                break;
            case 'b':
            	command = 4;
            	break;
            case 'i':
                file_input = malloc(sizeof(char)*(strlen(optarg) + 1));
                file_input = strcpy(file_input, optarg);
                break;
            case 'o':
            	file_output = malloc(sizeof(char)*(strlen(optarg) + 1));
                strcpy(file_output, optarg);
                break;
            case 'L':
            	flag_old_color = 1;
            	config.old_color = get_color_arg(optarg);
                break;
            case 'N':
           		flag_new_color = 1;
                config.new_color = get_color_arg(optarg);
                break;
            case 'B':
            	flag_border_color = 1;
				config.border_color = get_color_arg(optarg);
                break;
            case 'C':
            	flagcolor = 1;
				config.color = get_color_arg(optarg);
                break;
            case 'T':
            	config.thickness = get_number(optarg);
                break;
            case 'P':
		        config.pattern = optarg;
		        break;
            case 'O':
				config.count = get_number(optarg);
                break;
            case 's':
            	flag_size = 1;
            	int size = get_number(optarg);
            	config.size = (size + 1) % 2 + size;
            	break;
            case '?':
                return 0;
            default:
                break;
        }
            
        opt = getopt_long(argc, argv,short_options, long_options, &optind);
    }

    Image image = read_bmp(file_input, bmfh, bmif);

	command_list(&image, config, command, flag_old_color, flag_new_color, flag_border_color, flagcolor, flag_size);
	write_bmp(file_output, &image, *bmfh, *bmif);
   
    return 0;
}
