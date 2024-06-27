#include "processing_data.h"

void swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int more_zero(int arg) 
{
  if (arg == 0) return 1;
  return 0;
}

void check_axis(char* optarg)
{
  if(strcmp(optarg, "x") != 0 && strcmp(optarg, "y") != 0) {
    printf("Invalid syntax axis, can only be x or y\n");
    exit(41);
  }
}

void another_arguments(char* arg, char* name)
{
    if(arg != NULL){
        if(!strstr(arg,"--")){
            fprintf(stderr,"%s don't have arguments\n",name);
            exit(44);
        }
    }
}

void check_bmp(char* name)
{
    regex_t regex;
    int reti = regcomp(&regex, "^\\S+\\.?[A-Za-z]*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    };
    reti = regexec(&regex, name, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "Error, it's not bmp file!\n");
        exit(41);
    }
}

void check_coord(char* coords)
{
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+\\.\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    reti = regexec(&regex, coords, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "Incorrect coordinates\nUse <value>.<value>\n");
        exit(41);
    }

}

void more_then_zero(int arg)
{
  if (arg <= 0) {
    printf("Incorrect value\nThickness || radius can be more then zero\n");
    exit(41);
  }
}

void less_then(int arg)
{
  if (arg <= -1) {
    printf("Incorrect value\nNum_y || num_x can be less then zero\n");
    exit(41);
  }
}

void check_digit(char * distance)
{
    regex_t regex;
    int reti = regcomp(&regex, "^\\-?[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    };
    reti = regexec(&regex, distance, 0, NULL, 0);
    if (reti) {
        fprintf(stderr, "Incorrect form of value\n");
        exit(41);
    }
}

int* parse_color(char* color) 
{
    int* result = malloc(3 * sizeof(int));
    char* copy_color = strdup(color);
    char* token = strtok(copy_color, ".");
    for(int i = 0; i < 3; i++){
        result[i] = atoi(token);
        token = strtok(NULL, ".");
    }
    free(copy_color);
    return result;
}

void check_color(char *color) 
{
    regex_t regex;
    int reti = regcomp(&regex, "^[0-9]+\\.[0-9]+\\.[0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Regex's error for color\n");
        exit(1);
    }

    reti = regexec(&regex, color, 0, NULL, 0);
    if (reti){
        fprintf(stderr, "Incorrect form of color\nUse --color <value>.<value>.<value>\n");
        exit(41);
    }

    int *color_rgb = parse_color(color);
    if (color_rgb[0] > 255 || color_rgb[1] > 255 || color_rgb[2] > 255 || color_rgb[0] < 0 || color_rgb[1] < 0 ||color_rgb[2] < 0) {
        free(color_rgb);
        fprintf(stderr, "Incorrect form of color\nUse --color <0-255>.<0-255>.<0-255>\n");
        exit(41);
    }
    free(color_rgb);
}

Arguments get_arguments(int argc, char* argv[]) 
{
  Arguments args = {.out_name = "out.bmp", .in_name = NULL, .fill = 0};

  int opt;
  int long_index;
  static struct option long_options[] = {
      {"input", required_argument, NULL, 'i'},
      {"output", required_argument, NULL, 'o'},
      {"info", no_argument, NULL, 'I'},
      {"help", no_argument, NULL, 'h'},
      {"collage", no_argument, NULL, 'c'},
      {"number_y", required_argument, NULL, 'q'},
      {"number_x", required_argument, NULL, 'w'},
      {"mirror", no_argument, NULL, 'm'},
      {"axis", required_argument, NULL, 'e'},
      {"left_up", required_argument, NULL, 't'},
      {"right_down", required_argument, NULL, 'y'},
      {"pentagram", no_argument, NULL, 'p'},
      {"center", required_argument, NULL, 'a'},
      {"radius", required_argument, NULL, 's'},
      {"thickness", required_argument, NULL, 'u'},
      {"color", required_argument, NULL, 'd'},
      {"rect", no_argument, NULL, 'r'},
      {"fill", no_argument, NULL, 'f'},
      {"fill_color", required_argument, NULL, 'g'},
      {"rhombus", no_argument, NULL, 'z'},
      {NULL, 0, NULL, 0}};

  opt = getopt_long(argc, argv, "i:o:Ihcmprq:w:e:y:a:s:u:d:f:g:", long_options, &long_index);

  while (opt != -1) {
    switch (opt) {
        case 'i':
            check_bmp(optarg);
            args.in_name = optarg;
            args.in_flag = 1;
            break;
        case 'o':
            args.out_name = optarg;
            args.out_flag = 1;
            break;
        case 'I':
            args.flag_info = 1;
            break;
        case 'h':
            another_arguments(argv[optind], "--help");
            args.flag_help = 1;
            printInfo();
            exit(0);
        case 'c':
            another_arguments(argv[optind], "--collage");
            args.flag_collage = 1;
            break;
        case 'm':
            another_arguments(argv[optind], "--mirror");
            args.flag_mirror = 1;
            break;
        case 'p':
            another_arguments(argv[optind], "--pentagram");
            args.flag_pentagram = 1;
            break;
        case 'r':
            another_arguments(argv[optind], "--rect");
            args.flag_rect = 1;
            break;
        case 'z':
            another_arguments(argv[optind], "--rhombus");
            args.flag_rhombus = 1;
            break;
        case 'q':
            check_digit(optarg);
            less_then(atoi(optarg));
            args.flag_num_y = 1;
            args.num_y = atoi(optarg);
            break;
        case 'w':
            check_digit(optarg);
            less_then(atoi(optarg));
            args.flag_num_x = 1;
            args.num_x = atoi(optarg);
            break;
        case 'e':
            check_axis(optarg);
            args.flag_axis = 1;
            if (strcmp(optarg, "x") == 0) { 
              args.axis = 120;
            } else args.axis = 121;
            break;
        case 't':
            check_coord(optarg);
            args.flag_left_up = 1;
            sscanf(optarg, "%d.%d", &args.left_up.x, &args.left_up.y);
            break;
        case 'y':
            check_coord(optarg);
            args.flag_right_down = 1;
            sscanf(optarg, "%d.%d", &args.right_down.x, &args.right_down.y);
            break;
        case 'a':
            check_coord(optarg);
            args.flag_center = 1;
            sscanf(optarg, "%d.%d", &args.center[0], &args.center[1]);
            break;
        case 's':
            check_digit(optarg);
            more_then_zero(atoi(optarg));
            args.flag_radius = 1;
            args.radius = atoi(optarg);
            break;
        case 'u':
            check_digit(optarg);
            more_then_zero(atoi(optarg));
            args.flag_thickness = 1;
            args.thickness = atoi(optarg);
            break;
        case 'd':
            check_color(optarg);
            args.flag_color = 1;
            sscanf(optarg, "%hhu.%hhu.%hhu", &args.color.red, &args.color.green, &args.color.blue);
            break;
        case 'f':
            another_arguments(argv[optind], "--fill");
            args.fill = 1;
            break;
        case 'g':             
            check_color(optarg);
            args.flag_fill_color = 1;
            sscanf(optarg, "%hhu.%hhu.%hhu", &args.fill_color.red, &args.fill_color.green, &args.fill_color.blue);
            break;
        default:    
            printf("Invalid argument\n");
            exit(41);
        }
        opt = getopt_long(argc, argv, "i:o:Ihcmprq:w:e:y:u:a:s:d:f:g:", long_options, &long_index);
    }
  return args;
}

