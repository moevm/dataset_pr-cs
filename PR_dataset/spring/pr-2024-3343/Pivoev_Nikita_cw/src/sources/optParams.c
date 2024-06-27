#include "../include/optParams.h"

OptParams* initOptParams(OptParams* opt) {
    opt->input = NULL;
    opt->output = NULL;
    opt->info = false;

    opt->copy = false;
    opt->copy_left = -1;
    opt->copy_up = -1;
    opt->copy_right = -1;
    opt->copy_down = -1;
    opt->copy_dest_left = -1;
    opt->copy_dest_up = -1;

    opt->color_replace = false;
    opt->old_color.r = opt->old_color.g = opt->old_color.b = -1;
    opt->new_color.r = opt->new_color.g = opt->new_color.b = -1;

    opt->ornament = false;
    opt->ornament_pattern = -1;
    opt->ornament_count = -1;

    opt->filled_rects = false;
    opt->rects_border_color.r = opt->rects_border_color.g = opt->rects_border_color.b = -1;

    opt->color.r = opt->color.g = opt->color.b = -1;
    opt->thickness = -1;

    opt->outside_ornament = false;
    return opt;
}

void printHelp() {
    printf("Course work for option 5.16, created by Pivoev Nikita.\n"
        "Usage: ./cw [FLAGS]\n\n"
        "Flags:\n"
        "-h --help: Вывод справочной информации.\n"
        "-i --input: Изменение входного файла.\n"
        "-o --output: Изменение выходного файла.\n"
        "--info: Вывод информации о изображении.\n\n"
        "--copy: Копирование области.\n"
        "--left_up: Координаты левого верхнего угла изображения.\n"
        "--right_down: Координаты правого нижнего угла изображения.\n"
        "--dest_left_up: Координаты левого верхнуго угла области-назначения.\n\n"
        "--color_replace: Замена цвета всех пикселей на другой.\n"
        "--old_color: Старый цвет для замены.\n"
        "--new_color: Новый цвет для замены.\n\n"
        "--ornament: Создание рамки в виде узора.\n"
        "--pattern: Тип узора.\n"
        "--color: Цвет узора.\n"
        "--thickness: Ширина.\n"
        "--count: Количество узоров.\n\n"
        "--filled_rects: Поиск всех залитых прямоугольников заданного цвета.\n"
        "--color: Цвет искомых прямоугольников.\n"
        "--border_color: Цвет линии обводки.\n"
        "--thickness: Толщина линии для обводки.\n\n"
        "--outside_ornament: Добавление рамки вокруг изображения.\n"
        "--thickness: Толщина рамки.\n"
        "--color: Цвет рамки.\n");
}

void printInfo(Png* image) {
    printf("Image settings:\n"
    "Height: %d.\n" 
    "Width: %d.\n"
    "Color type: %d.\n",
    image->height, image->width, image->color_type);
}

char** parseArgs(char* arg, int size) {
    char** parsedArgs = malloc(sizeof(char*)*50);
    for (int i = 0; i < size; ++i)
        parsedArgs[i] = malloc(strlen(arg));
        
    int currentLength = 0;
    int currentElement = 0;
    for (int i = 0; i < strlen(arg); ++i) {
        if (arg[i-1] == '.' && i > 0) {
            parsedArgs[currentElement++][currentLength-1] = '\0';
            currentLength = 0;
        }
        parsedArgs[currentElement][currentLength++] = arg[i];
    }
    parsedArgs[currentElement][currentLength] = '\0';
    return parsedArgs;
}

OptParams* parseCommandLine(int argc, char** argv) {
    OptParams* opt = malloc(sizeof(OptParams));
    initOptParams(opt);

    opterr = 0;
    const char* short_options = "hi:o:";
    static struct option long_options[] = {
        {"help", 0, NULL, 'h'},
        {"input", 1, NULL, 'i'},
        {"output", 1, NULL, 'o'},

        {"info", 0, NULL, 310},

        {"copy", 0, NULL, 410},
        {"left_up", 1, NULL, 411},
        {"right_down", 1, NULL, 412},
        {"dest_left_up", 1, NULL, 413},

        {"color_replace", 0, NULL, 420},
        {"old_color", 1, NULL, 421},
        {"new_color", 1, NULL, 422},

        {"ornament", 0, NULL, 430},
        {"pattern", 1, NULL, 431},
        {"count", 1, NULL, 432},
        //color
        //thickness

        {"filled_rects", 0, NULL, 440},
        {"border_color", 1, NULL, 441},
        //color
        //thickness

        {"color", 1, NULL, 450},
        {"thickness", 1, NULL, 451},

        {"outside_ornament", 0, NULL, 460},
        {0, 0, 0, 0}
    };

    int value;
    char** args;
    while ((value = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (value) {
        case 'h': //--help
            printHelp();
            break;
        case 'i': //--input
            opt->input = optarg;
            break;
        case 'o': //--output
            opt->output = optarg;
            break;
        case 310: //--info
            opt->info = true;
            break;

        case 410: //--copy
            if (opt->color_replace || opt->ornament || opt->filled_rects || opt->outside_ornament){
                raiseError(taskError, 44);
            }
            opt->copy = true;
            break;
        case 411: //--left_up
            args = parseArgs(optarg, 2);
            opt->copy_left = strtol(args[0], NULL, 10);
            opt->copy_up = strtol(args[1], NULL, 10);
            break;
        case 412: //--right_down
            args = parseArgs(optarg, 2);
            opt->copy_right = strtol(args[0], NULL, 10);
            opt->copy_down = strtol(args[1], NULL, 10);
            break;
        case 413: //--dest_left_up
            args = parseArgs(optarg, 2);
            opt->copy_dest_left = strtol(args[0], NULL, 10);
            opt->copy_dest_up = strtol(args[1], NULL, 10);
            break;

        case 420: //--color_replace
            if (opt->copy || opt->ornament || opt->filled_rects || opt->outside_ornament) {
                raiseError(taskError, 44);
            }
            opt->color_replace = true;
            break;
        case 421: //--old_color
            args = parseArgs(optarg, 3);
            opt->old_color.r = strtol(args[0], NULL, 10);
            opt->old_color.g = strtol(args[1], NULL, 10); 
            opt->old_color.b = strtol(args[2], NULL, 10);
            break;
        case 422: //--new_color
            args = parseArgs(optarg, 3);
            opt->new_color.r = strtol(args[0], NULL, 10);
            opt->new_color.g = strtol(args[1], NULL, 10); 
            opt->new_color.b = strtol(args[2], NULL, 10); 
            break;

        case 430: //--ornament
            if (opt->copy || opt->color_replace || opt->filled_rects || opt->outside_ornament){
                raiseError(taskError, 44);
            }
            opt->ornament = true;
            break;
        case 431: //--pattern
            if (strcmp(optarg, "rectangle") == 0)
                opt->ornament_pattern = 0;
            else if (strcmp(optarg, "circle") == 0)
                opt->ornament_pattern = 1;
            else if (strcmp(optarg, "semicircles") == 0)
                opt->ornament_pattern = 2;
            else
                raiseError(patternError, 43);
            break;
        case 432: //--count
            opt->ornament_count = strtol(optarg, NULL, 10);
            break;

        case 440: //--filled_rects
            if (opt->copy || opt->color_replace || opt->ornament || opt->outside_ornament) {
                raiseError(taskError, 44);
            }
            opt->filled_rects = true;
            break;
        case 441: //--border_color
            args = parseArgs(optarg, 3);
            opt->rects_border_color.r = strtol(args[0], NULL, 10);
            opt->rects_border_color.g = strtol(args[1], NULL, 10); 
            opt->rects_border_color.b = strtol(args[2], NULL, 10); 
            break;

        case 450: //--color
            args = parseArgs(optarg, 3);
            opt->color.r = strtol(args[0], NULL, 10);
            opt->color.g = strtol(args[1], NULL, 10); 
            opt->color.b = strtol(args[2], NULL, 10); 
            break;
        case 451: //--thickness
            opt->thickness = strtol(optarg, NULL, 10);
            break;
        case 460: //--outside_ornament
            if (opt->copy || opt->color_replace || opt->ornament || opt->filled_rects) {
                raiseError(taskError, 44);
            }
            opt->outside_ornament = true;
            break;

        case '?': //missing args
            raiseError(argsError, 42);
            break;

        default:
            break;
        }
    }
    free(args); 

    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
        exit(0);

    if (opt->input == NULL && optind == argc - 1) {
        opt->input = malloc(strlen(argv[argc - 1]) + 1);
        strncpy(opt->input, argv[argc - 1], strlen(argv[argc - 1]) + 1);
    }

    if (opt->input == NULL)
        raiseError(inputError, 40);
 
    if (opt->output == NULL) {
        opt->output = malloc(strlen("out.png") + 1);
        opt->output = "out.png";
    }

    if (strcmp(opt->input, opt->output) == 0)
        raiseError(outputIsImputError, 40);
    
    return opt;
}