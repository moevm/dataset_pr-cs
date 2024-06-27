#include "args_parsing.h"

OPTS init_options(){
    OPTS new_opts;
    new_opts.flag = 0;
    new_opts.circle = 0;
    new_opts.copy = 0;
    new_opts.mirror = 0;
    new_opts.contr = 0;

    new_opts.radius = 0;
    new_opts.thickness = 0;
    new_opts.alpha = 0;
    new_opts.beta = 0;

    new_opts.fill_flag = false;
    new_opts.fill = false;
    new_opts.input_flag = false;
    new_opts.info_flag = false;

    return new_opts;
}

bool is_correct_component(int val) {
  if (val >= 0 && val <= 255)
    return true;

  return false;
}

int count_dots(char* arg){
  int i, j = 0;
  for (i = 0; i < strlen(arg); i++){
    if (arg[i] == '.'){
      j++;
    }
  }
  return j;
}

void are_coordinates(char *arg, COORD* coords) {
  char check[10];

  if (count_dots(arg) != 1){
    exit(Error_args);
  }

  char *tmp = strtok(arg, ".");
  coords->x= atoi(tmp);

  sprintf(check,"%d",coords->x);
  if (strcmp(tmp, check))
    exit(Error_args);

  tmp = strtok(NULL, ".");

  if (tmp == NULL)
    exit(Error_args);

  coords->y= atoi(tmp);

  sprintf(check,"%d",coords->y);
  if (strcmp(tmp, check))
    exit(Error_args);

  tmp = strtok(NULL, ".");
  if (tmp!=NULL)
    exit(Error_args);
}

int to_number(char* arg){
  int number;
  char check[10];
  number = atoi(arg);

  sprintf(check,"%d",number);
  if (strcmp(arg, check))
    exit(Error_args);

  return number;
}

void to_color(char* arg, RGB* color){
  char check[10];

  if (count_dots(arg) != 2){
    exit(Error_args);
  }

  char *tmp = strtok(arg, ".");
  color->r = atoi(tmp);

  sprintf(check,"%d",color->r);
  if (strcmp(tmp, check) || (is_correct_component(color->r)==0))
    exit(Error_args);

  tmp = strtok(NULL, ".");
  color->g = atoi(tmp);

  sprintf(check,"%d",color->g);
  if (strcmp(tmp, check) || (is_correct_component(color->g)==0))
    exit(Error_args);

  tmp = strtok(NULL, ".");

  if (tmp == NULL)
    exit(Error_args);

  color->b = atoi(tmp);

  sprintf(check,"%d",color->b);
  if (strcmp(tmp, check) || (is_correct_component(color->b)==0))
    exit(Error_args);

  tmp = strtok(NULL, ".");
  if (tmp!=NULL)
    exit(Error_args);
}

bool is_axis(char* arg) {
  if (strcasecmp(arg, "x") && strcasecmp(arg, "y")) {
    exit(Error_args);
  }
  return true;
}

bool invalid_file(char* path_i, char* path_o){
  return !strcmp(path_i, path_o);
}

void help(){
    printf("PNG image processing functions:\n\
    Drawing a circle. Flag to perform this operation: `--circle`.\n\
    Reflection of a specified area. Flag to perform this operation: `--mirror`.\n\
    Copy a specified area. Flag to perform this operation: `--copy`.\n");
}

void args_parsing(int argc, char** argv, char* path_i, char* path_o, OPTS* options, int* flag){

    char* last_argument;
    last_argument = strdup(argv[argc-1]);

    const char short_options[] = "hi:o:";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'I'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"circle", no_argument, NULL, 'c'},
        {"mirror", no_argument, NULL, 'm'},
        {"copy", no_argument, NULL, 'k'},
        {"center", required_argument, NULL, 'R'},
        {"radius", required_argument, NULL, 'r'},
        {"color", required_argument, NULL, 'C'},
        {"thickness", required_argument, NULL, 't'},
        {"axis", required_argument, NULL, 'a'},
        {"left_up", required_argument, NULL, 'u'},
        {"right_down", required_argument, NULL, 'd'},
        {"fill", no_argument, NULL, 'f'},
        {"fill_color", required_argument, NULL, 'F'},
        {"dest_left_up", required_argument, NULL, 'U'},
        {"contrast", no_argument, NULL, 'K'},
        {"alpha", required_argument, NULL, 'A'},
        {"beta", required_argument, NULL, 'B'},
        {NULL, no_argument, NULL, 0}
    };

    int opt, index = -1;
    while ((opt = getopt_long(argc, argv, short_options, long_options, &index)) != -1) {
        switch(opt) {
        case 'h': 
            help();
            exit(0);
        case 'I': 
            options->info_flag = true;
            break;
        case 'i':
            strcpy(path_i, optarg);
            break;
        case 'o': 
            strcpy(path_o, optarg);
            break;
        
        case 'c':
            options->flag = 1;
            break;
        case 'm':
            options->flag = 2;
            break;
        case 'k':
            options->flag = 3;
            break;
        case 'K':
            options->flag = 4;
            break;

        case 'R': 
            are_coordinates(optarg, &(options->center_coords));
            options->circle++;
            break;
        case 'r': 
            options->radius = to_number(optarg);
            options->circle++;
            break;
        case 'C': 
            to_color(optarg, &(options->color));
            options->circle++;
            break;
        case 't': 
            options->thickness = to_number(optarg);
            options->circle++;
            break;
        case 'f': 
            options->fill_flag = true;
            options->circle++;
            break;
        case 'F': 
            to_color(optarg, &(options->fill_color));
            options->fill = true;
            options->circle++;
            break;
        
        case 'a': 
            options->axis = optarg;
            if (is_axis(options->axis)) options->mirror++;
            break;
        case 'u': 
            are_coordinates(optarg, &(options->left_up_coords));
            options->mirror++; options->copy++;
            break;
        case 'd': 
            are_coordinates(optarg, &(options->right_down_coords));
            options->mirror++; options->copy++;
            break;

        case 'U': 
            are_coordinates(optarg, &(options->dest_left_up_coords));
            options->copy++;
            break;

        case 'A':
            options->alpha = atof(optarg);
            options->contr++;
            break;
        case 'B':
            options->beta = to_number(optarg);
            options->contr++;
            break;

        default: 
            exit(Invalid_flag);

        }
        index = -1;
    }
    *flag = options->flag;

    if (optind == argc-1 && strcmp(argv[optind], last_argument) == 0 && !options->input_flag) {
        strcpy(path_i, last_argument);
    } else if (optind <= argc-1) {
        exit(Too_many_args);
    }

    if (invalid_file(path_i, path_o)){
        exit(Invalid_file);
    }


}