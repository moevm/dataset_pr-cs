#include "../include/Parametrs.h"

void Help(){
    printf("Course work for option 4.16, created by Silyaev Ruslan.\n"
        "Usage: ./cw [FLAGS]\n\n"
        "Options:\n"
        "-h --help: Вывод справочной информации.\n"
        "-i --input: Изменение входного файла.\n"
        "-o --output: Изменение выходного файла.\n"
        "--info: Вывод информации изображения.\n\n"
        "--square: Рисование квадрата.\n"
        "--left_up: Координаты левого верхнего угла.\n"
        "--side_size: Размер стороны.\n"
        "--thickness: Толщина линий.\n"
        "--color: Цвет линий.\n"
        "--fill: Залит или нет.\n"
        "--fill_color: Цвет заливки.\n"
        "--exchange: Поменять местами 4 куска области.\n"
        "--left_up: Координаты левого верхнего угла области.\n"
        "--right_down: Координаты правого нижнего угла области.\n"
        "--exchange_type: Способ обмена частей.\n"
        "--freq_color: Находит самый часто встречаемый цвет и заменяет его на другой заданный цвет.\n"
        "--color: Цвет, в который надо перекрасить самый часто встречаемый цвет.\n"
        "--alpha: Число с плавающей точкой, большее нуля, коэффициент изменения контрастности\n"
        "--beta: Целое число, сдвиг контрастности\n"
    );
}

void Info(Png* image){
    printf("Image settings:\n"
    "Width: %d.\n"
    "Height: %d.\n"
    "Color type: %d.\n"
    "Bit depth: %d\n",
    image->width, image->height, image->color_type, image->bit_depth);
}

Parametrs* initParametrs(Parametrs* par) {
    par->input = NULL;
    par->output = NULL;
    par->info = false;

    par->square = false;
    par->left = -1;
    par->up = -1;
    par->side_size = -1;
    par->thickness = -1;
    par->color.r = par->color.g = par->color.b = -1;
    par->fill = false;
    par->fill_color.r = par->fill_color.g = par->fill_color.b = -1;

    par->exchange = false;
    par->right = -1;
    par->down = -1;
    par->exchange_type = -1;

    par->freq_color = false;

    par->contrast = false;
    par->alpha = -1.0;
    par->beta = -1;

    return par;
}

char** toCorrect(char* par, int size){
    char** correctpar = malloc(52 * sizeof(char*));
    for (int i = 0; i < size; i++){
        correctpar[i] = malloc(strlen(par));
    }
    int curlen = 0;
    int curel = 0;
    for (int i = 0; i < strlen(par); i++){
        if (par[i-1] == '.' && i > 0){
            correctpar[curel++][curlen-1] = '\0';
            curlen = 0;
        }
        correctpar[curel][curlen++] = par[i];
    }
    correctpar[curel][curlen] = '\0';
    return correctpar;
}

Parametrs* CLI(int argc, char** argv){
    Parametrs* par = malloc(sizeof(Parametrs));
    initParametrs(par);
    opterr=0;
    const char* short_options = "hi:o:";
    const struct option long_options[] = {
            {"help", 0, NULL, 'h'},
            {"input", 1, NULL, 'i'},
            {"output", 1, NULL, 'o'},
            {"info", 0, NULL, 52},

            {"square", 0, NULL, 510},
            {"left_up", 1, NULL, 511},
            {"side_size", 1, NULL, 512},
            {"thickness", 1, NULL, 513},
            {"color", 1, NULL, 514},
            {"fill", 0, NULL, 515},
            {"fill_color", 1, NULL, 516},

            {"exchange", 0, NULL, 520},
            {"right_down", 1, NULL, 521},
            {"exchange_type", 1, NULL, 522},
            
            {"freq_color", 0, NULL, 530},

            {"contrast", 0, NULL, 540},
            {"alpha", 1, NULL, 541},
            {"beta", 1, NULL, 542},

            {0, 0, 0, 0}
    };

    int res;
    char** args;
    while((res = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
        switch (res)
        {
        case 'h': //--help
            Help();
            break;
        case 'i': //--input
            par->input = optarg;
            break;
        case 'o': //--output
            par->output = optarg;
            break;
        case 52: //--info
            par->info = true;
            break;
        case 510:
            if(par->exchange || par->freq_color || par->contrast){
                throwError(multipyFuncError, 43);
            }
            par->square = true;
            break;
        case 511:
            args = toCorrect(optarg, 2);
            par->left = strtol(args[0], NULL, 10);
            par->up = strtol(args[1], NULL, 10);
            break;
        case 512:
            par->side_size = strtol(optarg, NULL, 10);
            break;
        case 513:
            par->thickness = strtol(optarg, NULL, 10);
            break;
        case 514:
            args = toCorrect(optarg, 3);
            par->color.r = strtol(args[0], NULL, 10);
            par->color.g = strtol(args[1], NULL, 10);
            par->color.b = strtol(args[2], NULL, 10);
            break;
        case 515:
            par->fill = true;
            break;
        case 516:
            args = toCorrect(optarg, 3);
            par->fill_color.r = strtol(args[0], NULL, 10);
            par->fill_color.g = strtol(args[1], NULL, 10);
            par->fill_color.b = strtol(args[2], NULL, 10);
            break;
        case 520:
            if(par->square || par->freq_color || par->contrast){
                throwError(multipyFuncError, 43);
            }
            par->exchange = true;
            break;
        case 521:
            args = toCorrect(optarg, 2);
            par->right = strtol(args[0], NULL, 10);
            par->down = strtol(args[1], NULL, 10);
            break;
        case 522:
            if (strcmp(optarg, "clockwise") == 0)
                par->exchange_type = 0;
            else if (strcmp(optarg, "counterclockwise") == 0)
                par->exchange_type = 1;
            else if (strcmp(optarg, "diagonals") == 0)
                par->exchange_type = 2;
            else
                throwError(typeError, 46);
            break;
        case 530:
            if(par->square || par->exchange || par->contrast){
                throwError(multipyFuncError, 43);
            }
            par->freq_color = true;
            break;
        case 540:
            if(par->square || par->exchange || par->freq_color){
                throwError(multipyFuncError, 43);
            }
            par->contrast = true;
            break;
        case 541:
            par->alpha = strtod(optarg, NULL);
            break;
        case 542:
            par->beta = strtol(optarg, NULL, 10);
            break;
        case '?':
            throwError(argsError, 44);
            break;
        default:
            break;
        }
    }
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))
        exit(0);

    if (par->input == NULL && optind == argc - 1) {
        par->input = malloc(strlen(argv[argc - 1]) + 1);
        strncpy(par->input, argv[argc - 1], strlen(argv[argc - 1]) + 1);
    }

    if (par->input == NULL)
        throwError(inputError, 41);

    if (par->output == NULL) {
        par->output = malloc(strlen("out.png") + 1);
        par->output = "out.png";
    }

    if (strcmp(par->input, par->output) == 0)
        throwError(outputError, 42);

    return par;
}