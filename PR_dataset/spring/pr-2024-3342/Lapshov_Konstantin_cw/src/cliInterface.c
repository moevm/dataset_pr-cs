#include "cliInterface.h"

Option
getCliFlagsInfo(int argc, char *argv[]) {
    Option options = {};
    options.outputFileName = "out.bmp";

    const char* shortOptions = "hi:o:";
    const struct option longOptions[] = {
        {"help", no_argument, NULL, 'h'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"inverse_circle", no_argument, NULL, 400},
        {"trim", no_argument, NULL, 401},
        {"triangle", no_argument, NULL, 402},
        {"line", no_argument, NULL, 403},
		{"rhombus", no_argument, NULL, 416},
        {"center", required_argument, NULL, 404},
        {"radius", required_argument, NULL, 405},
        {"left_up", required_argument, NULL, 406},
        {"right_down", required_argument, NULL, 407},
        {"points", required_argument, NULL, 408},
        {"thickness", required_argument, NULL, 409},
        {"color", required_argument, NULL, 410},
        {"fill", no_argument, NULL, 411},
        {"fill_color", required_argument, NULL, 412},
        {"start", required_argument, NULL, 413},
        {"end", required_argument, NULL, 414},
        {"info", no_argument, NULL, 415},
        {NULL, 0, NULL, 0}
    };


    if (argc == 1) {
        options.hasHelpOpt = 1;
        printHelp();
        exit(EXIT_SUCCESS);
    }

    int res;
    while ((res = getopt_long(argc, argv, shortOptions, longOptions, NULL)) != -1) {
        switch (res) {
            //Флаги проверки информации о файле
            case 'h':
                options.hasHelpOpt = true;
                break;
            case 'i':
                options.inputFileName = optarg;
                options.hasInputOpt = true;
                break;
            case 'o':
                options.outputFileName = optarg;
                options.hasOutputOpt = true;
                break;

            //Флаги проверки функции
            case 400:
                if(options.hasTrimOpt || options.hasTriangleOpt || options.hasLineOpt || options.hasInfoOpt || options.hasRhombusOpt) {
                    showError("Only one function can be choosed!", ARGUMENTS_FAILURE);
                }
                options.hasInverseCircleOpt = true;
                break;
            case 401:
                if(options.hasInverseCircleOpt || options.hasTriangleOpt || options.hasLineOpt || options.hasInfoOpt || options.hasRhombusOpt) {
                    showError("Only one function can be choosed!", ARGUMENTS_FAILURE);
                }
                options.hasTrimOpt = true;
                break;
            case 402:
                if(options.hasTrimOpt || options.hasInverseCircleOpt || options.hasLineOpt || options.hasInfoOpt || options.hasRhombusOpt) {
                    showError("Only one function can be choosed!", ARGUMENTS_FAILURE);
                }
                options.hasTriangleOpt = true;
                break;
            case 403:
                if(options.hasTrimOpt || options.hasTriangleOpt || options.hasInverseCircleOpt || options.hasInfoOpt || options.hasRhombusOpt) {
                    showError("Only one function can be choosed!", ARGUMENTS_FAILURE);
                }
                options.hasLineOpt = true;
                break;
            case 416:
                if(options.hasTrimOpt || options.hasTriangleOpt || options.hasInverseCircleOpt || options.hasInfoOpt || options.hasLineOpt) {
                    showError("Only one function can be choosed!", ARGUMENTS_FAILURE);
                }
                options.hasRhombusOpt = true;
                break;

            //Флаги проверки аргументов функции
            case 404:
                options.center = getPointValue(optarg);
                options.hasCenterOpt = true;
                break;
            case 405:
                options.radius = getNonNegativeNumber(optarg);
                options.hasRadiusOpt = true;
                break;
            case 406:
                options.leftUp = getPointValue(optarg);
                options.hasLeftUpOpt = true;
                break;
            case 407:
                options.rightDown = getPointValue(optarg);
                options.hasRightDownOpt = true;
                break;
            case 408:
                options.points = getPointsValue(optarg);
                options.hasPointsOpt = true;
                break;
            case 409:
                options.thickness = getNonNegativeNumber(optarg);
                options.hasThicknessOpt = true;
                break;
            case 410:
                options.color = getRGBValue(optarg);
                options.hasColorOpt = true;
                break;
            case 411:
                options.hasFillOpt = true;
                break;
            case 412:
                options.fillColor = getRGBValue(optarg);
                options.hasFillColorOpt = true;
                break;
            case 413:
                options.start = getPointValue(optarg);
                options.hasStartOpt = true;
                break;
            case 414:
                options.end = getPointValue(optarg);
                options.hasEndOpt = true;
                break;
            case 415:
                options.hasInfoOpt = true;
                break;
            default:
                showError("Unknown option or missing argument", ARGUMENTS_FAILURE);
        }
    }

    //Проверка на наличие функции
    if(!options.hasHelpOpt && !options.hasInfoOpt && !options.hasInverseCircleOpt && !options.hasTrimOpt && !options.hasTriangleOpt && !options.hasLineOpt && !options.hasRhombusOpt) {
        showError("No function is selected!", ARGUMENTS_FAILURE);
    }

    if(options.hasHelpOpt) {
        printHelp();
        exit(EXIT_SUCCESS);
    }

    //Проверка на наличие флагов у inverse_circlea
    if(options.hasInverseCircleOpt && (!options.hasCenterOpt || !options.hasRadiusOpt)) {
        showError("Not enough flags in --inverse_circle!", ARGUMENTS_FAILURE);
    }

    //Проверка на наличие флагов у trim
    if(options.hasTrimOpt && (!options.hasLeftUpOpt || !options.hasRightDownOpt)) {
        showError("Not enough flags in --trim!", ARGUMENTS_FAILURE);
    }

    //Проверка на наличие флагов у triangle
    if(options.hasTriangleOpt) {
        if(options.hasFillOpt && !options.hasFillColorOpt) {
            showError("If there is a --fill flag, then it must be --fill_color!", ARGUMENTS_FAILURE);
        }
        if(!options.hasPointsOpt || !options.hasThicknessOpt || !options.hasColorOpt) {
            showError("Not enough flags in --triangle!", ARGUMENTS_FAILURE);
        }
    }

    //Проверка на наличие флагов у line
    if(options.hasLineOpt && (!options.hasStartOpt || !options.hasEndOpt || !options.hasThicknessOpt || !options.hasColorOpt)) {
        showError("Not enough flags in --line!", ARGUMENTS_FAILURE);
    }

	//Проверка на наличие флагов у rhombus
    if(options.hasRhombusOpt && !options.hasColorOpt) {
        showError("Not enough flags in --rhombus!", ARGUMENTS_FAILURE);
    }

    //Проверка на наличие имени ыходного файла
    if(!options.hasInputOpt) {
        if(optind == argc - 1) {
            options.inputFileName = argv[argc - 1];
            options.hasInputOpt = true;
        }else if (optind < argc - 1) {
            showError("Too many arguments!", ARGUMENTS_FAILURE);
        } else {
            if(!options.hasHelpOpt) {
                showError("There is no name of the input file!", ARGUMENTS_FAILURE);
            }
        }
    }else {
        if (optind <= argc - 1) {
            showError("Too many arguments!", ARGUMENTS_FAILURE);
        }
    }

    //Проверка на схожесть имен входного и выходного файлов
    if(options.hasOutputOpt && options.hasInputOpt) {
        if (strcmp(options.inputFileName, options.outputFileName) == 0) {
            showError("Input and output files can't have the same name!", ARGUMENTS_FAILURE);
        }
    }


    return options;
}


Point
getPointValue(char* string) {
    int arr[2];
    int index = 0;
    Point new_point = {};

    if(string[0] == '.' || string[strlen(string) - 1] == '.') {
        showError("Input data error!", DATA_FAILURE);
    }

    char* token = strtok(string, ".");
    while(token != NULL && index < 2) {
        arr[index] = atoi(token);

        token = strtok(NULL, ".");
        index++;
    }

    if(token != NULL || index != 2) {
        showError("Input data error!", DATA_FAILURE);
    }

    new_point.x = arr[0];
    new_point.y = arr[1];

    return new_point;
}

RGB
getRGBValue(char* string){
    int arr[3];
    int index = 0;
    RGB new_color = {};

    if(string[0] == '.' || string[strlen(string) - 1] == '.') {
        showError("Input data error!", DATA_FAILURE);
    }

    char* token = strtok(string, ".");
    while(token != NULL && index < 3) {
        arr[index] = atoi(token);
        if(arr[index] > 255 || arr[index] < 0) {
            showError("Input data error!", DATA_FAILURE);
        }

        token = strtok(NULL, ".");
        index++;
    }

    if(token != NULL || index != 3) {
        showError("Input data error!", DATA_FAILURE);
    }

    new_color.r = arr[0];
    new_color.g = arr[1];
    new_color.b = arr[2];

    return new_color;
}


Point*
    getPointsValue(char* string) {
    if(string[0] == '.' || string[strlen(string) - 1] == '.') {
        showError("Input data error!", DATA_FAILURE);
    }

    int count = 0;
    int subCount = 0;
    Point* new_points = malloc(sizeof(Point) * 3);
    if(new_points == NULL) showError("Memory allocation error!", MEMORY_ALLOCATION_FAILURE);;


    char* token = strtok(string, ".");

    while(token != NULL && count != 3) {
        if(subCount % 2 == 0) {
            new_points[count].x = atoi(token);
        }else {
            new_points[count].y = atoi(token);
            count++;
        }

        token = strtok(NULL, ".");
        subCount++;
    }

    if(token != NULL || count != 3) {
        showError("Input data error!", DATA_FAILURE);
    }

    return new_points;
}

int
getNonNegativeNumber(char* string) {
    int result = atoi(string);
    if (result <= 0) {
        showError("Input data error!", DATA_FAILURE);
    }

    return result;
}


void
printHelp() {
    printf("Course work for option 5.5, created by Lapshov Konstantin.\n");
    printf("Usage: ./programName [Flags] [InputFileName]\n\n");
    printf("Main flags:\n");
    printf("  -h, --help                             Display this help message\n");
    printf("  --info                                 Print detailed information about the input PNG file\n");
    printf("  -i, --input <filename>                 Specify the name of the input BMP file\n");
    printf("  -o, --output <filename>                Specify the name of the output BMP file [default: out.png]\n");
    printf("  --inverse_circle [--center --radius]   Inverting the colors in a given circle\n");
    printf("                                         Required additional flags\n\n");
    printf("  --trim [--left_up --right_down]        Cropping the image.\n");
    printf("                                         Required additional flags\n\n");
    printf("  --triangle [--points --thickness --color --fill --fill_color]   Drawing a triangle.\n");
    printf("                                                                  Required additional flags\n\n");
    printf("  --line [--start --end --thickness --color]   Drawing a line segment.\n");
    printf("                                               Required additional flags\n\n");
    printf("Additional flags:\n");
    printf("  --center <x.y>                 Coordinates of the center of the circle\n");
    printf("  --radius <value>               The radius of the circle\n");
    printf("  --left_up <x.y>                Coordinates of the up left corner of the image\n");
    printf("  --right_down <x.y>             Coordinates of the bottom right corner of the image\n");
    printf("  --points <x1.y1.x2.y2.x3.y3>   Coordinates of the vertices of the triangle\n");
    printf("  --thickness <value>            The thickness of the line\n");
    printf("  --color <rrr.ggg.bbb>          The color of the line\n");
    printf("  --fill                         Indicates whether a fill is needed\n");
    printf("  --fill_color <rrr.ggg.bbb>     The color of the fill\n");
    printf("  --start <x.y>                  Coordinates of the start of the line\n");
    printf("  --end <x.y>                      Coordinates of the end of the line\n\n");
    printf("Attention! If the --input flag indicating the name of the input file is not specified, then after each main flag (except for the --help and --info flags), at the end, you must specify the name of the input file!\n\n");
}