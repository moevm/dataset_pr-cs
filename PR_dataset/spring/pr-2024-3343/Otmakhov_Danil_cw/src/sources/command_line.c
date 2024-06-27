#include "command_line.h"
#include "errors.h"


void printHelp()
{
    printf("%s\n"
        "Flags:\n"
        "  -h --help: Вывод справочной информации;\n"
        "  -i --input: Имя входного файла;\n"
        "  -o --output: Имя выходного файла;\n"
        "  --info: Вывод информации об изображении;\n\n"
        "  --color_replace: Заменяет все пиксели одного заданного цвета на другой цвет;\n"
        "  --old_color: Цвет, который требуется заменить;\n"
        "  --new_color: Цвет, на который требуется заменить;\n\n"
        "  --rgbfilter: Фильтр rgb-компонент;\n"
        "  --component_name: Какую компоненту требуется изменить;\n"
        "  --component_value: На какое значение ее требуется изменить;\n\n"
        "  --split: Разделяет изображение на N*M частей;\n"
        "  --number_x: Количество частей по “оси” Y;\n"
        "  --number_y: Количество частей по “оси” X;\n"
        "  --thickness: Толщина линии;\n"
        "  --color: Цвет линии.\n", hello_message);
}


RGB convertStringToRGB(char* color_string)
{
    int r, g, b;
    sscanf(color_string, "%d.%d.%d", &r, &g, &b);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        raiseError(incorrect_rgb_format, ERROR_INVALID_ARGUMENT);
    RGB color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}


CommandLineOptions* initOptions()
{
    CommandLineOptions* options = (CommandLineOptions*)calloc(1, sizeof(CommandLineOptions));

    options->input = NULL;
    options->output = "out.bmp";
    options->info = false;

    options->colorReplace = false;

    options->rgbFilter = false;

    options->split = false;

    options->binarization = false;

    return options;
}


CommandLineOptions* parseCommandLine(int argc, char* argv[])
{
    opterr = 0;

    if (argc == 1) {
        printHelp();
        exit(EXIT_SUCCESS);
    }

    const char* short_options = "i:o:h";
    const struct option long_options[] = {
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 256},
        {"color_replace", no_argument, NULL, 257},
        {"old_color", required_argument, NULL, 258},
        {"new_color", required_argument, NULL, 259},
        {"rgbfilter", no_argument, NULL, 260},
        {"component_name", required_argument, NULL, 261},
        {"component_value", required_argument, NULL, 262},
        {"split", no_argument, NULL, 263},
        {"number_x", required_argument, NULL, 264},
        {"number_y", required_argument, NULL, 265},
        {"thickness", required_argument, NULL, 266},
        {"color", required_argument, NULL, 267},
        {"binarization", no_argument, NULL, 268},
        {"threshold", required_argument, NULL, 269},
        {NULL, 0, NULL, 0}
	};

    CommandLineOptions* options = initOptions();

    int res = 0;
    while ((res = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch(res)
        {
            case 'i':
                if (!optarg || optarg[0] == '-'){
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                }
                options->input = optarg;
                break;
            case 'o':
                if (!optarg || optarg[0] == '-'){
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                }
                options->output = optarg;
                break;
            case 'h':
                printHelp();
                exit(EXIT_SUCCESS);
                break;
            case 256:
                if (options->colorReplace || options->rgbFilter || options->split)
                    raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
                options->info = true;
                break;
            case 257:
                if (options->info)
                    raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
                if (!options->rgbFilter && !options->split)
                    options->colorReplace = true;
                else
                    raiseError(multiple_function_request, ERROR_MULTIPLE_FUCTION_REQUEST);
                break;
            case 258:
                if (!optarg || optarg[0] == '-') {
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                }
                options->oldColor = optarg;
                break;
            case 259:
                if (!optarg || optarg[0] == '-') {
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                }
                options->newColor = optarg;
                break;
            case 260:
                if (options->info)
                    raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
                if (!options->colorReplace && !options->split && !options->binarization)
                    options->rgbFilter = true;
                else
                    raiseError(multiple_function_request, ERROR_MULTIPLE_FUCTION_REQUEST);
                break;
            case 261:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                options->componentName = optarg;
                break;
            case 262:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                sscanf(optarg, "%hhu", &options->componentValue);
                break;
            case 263:
                if (options->info)
                    raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
                if (!options->colorReplace && !options->rgbFilter && !options->binarization)
                    options->split = true;
                else
                    raiseError(multiple_function_request, ERROR_MULTIPLE_FUCTION_REQUEST);
                break;
            case 264:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                options->numberX = strtol(optarg, NULL, 10);
                break;
            case 265:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                options->numberY = strtol(optarg, NULL, 10);
                break;
            case 266:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                options->thickness = strtol(optarg, NULL, 10);
                break;
            case 267:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                options->color = optarg;
                break;
            case 268:
                if (options->info)
                    raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
                if (!options->colorReplace && !options->rgbFilter && !options->binarization)
                    options->binarization = true;
                else
                    raiseError(multiple_function_request, ERROR_MULTIPLE_FUCTION_REQUEST);
                break;
            case 269:
                if (!optarg || optarg[0] == '-')
                    raiseError(missing_required_argument, ERROR_MISSING_REQUIRED_ARGUMENT);
                options->threshold = strtol(optarg, NULL, 10);;
                break;
            default:
                raiseError(unknown_option, ERROR_UNKNOWN_OPTION);
                break;
        }
    }

    if (!options->input) {
        if (optind == argc - 1)
            options->input = argv[optind];
        else
            raiseError(input_file_not_found, ERROR_INVALID_ARGUMENT);
    }

    if (!strcmp(options->input, options->output))
        raiseError(same_input_and_output_files, ERROR_INVALID_ARGUMENT);

    int task_number = 0;

    if (options->colorReplace || options->oldColor || options->newColor) {
        if (task_number != 0)
            raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
        task_number = 1;
    }

    if (options->rgbFilter || options->componentName || options->componentValue) {
        if (task_number != 0)
            raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
        task_number = 2;
    }

    if (options->split || options->numberX || options->numberY || options->thickness || options->color) {
        if (task_number != 0)
            raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
        task_number = 3;
    }

    if (options->binarization || options->threshold) {
        if (task_number != 0)
            raiseError(unexpected_option, ERROR_UNEXPECTED_OPTION);
        task_number = 4;
    }

    int options_cnt;

    if (task_number == 1) {
        options_cnt = 0;

        if (options->colorReplace) options_cnt++;
        if (options->oldColor) options_cnt++;
        if (options->newColor) options_cnt++;

        if (options_cnt != 3)
            raiseError(missing_required_option, ERROR_MISSING_REQUIRED_OPTION);
    }

    if (task_number == 2) {
        options_cnt = 0;

        if (options->rgbFilter) options_cnt++;
        if (options->componentName) options_cnt++;
        if (options->componentValue) options_cnt++;

        if (options_cnt != 3)
            raiseError(missing_required_option, ERROR_MISSING_REQUIRED_OPTION);
    }

    if (task_number == 3) {
        options_cnt = 0;

        if (options->split) options_cnt++;
        if (options->numberX) options_cnt++;
        if (options->numberY) options_cnt++;
        if (options->thickness) options_cnt++;
        if (options->color) options_cnt++;

        if (options_cnt != 5)
            raiseError(missing_required_option, ERROR_MISSING_REQUIRED_OPTION);
    }

    if (task_number == 4) {
        options_cnt = 0;

        if (options->binarization) options_cnt++;
        if (options->threshold) options_cnt++;

        if (options_cnt != 2)
            raiseError(missing_required_option, ERROR_MISSING_REQUIRED_OPTION);
    }

    return options;
}
