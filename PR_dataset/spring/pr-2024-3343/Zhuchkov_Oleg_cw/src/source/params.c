#include <params.h>


void print_help(){
    printf("Course work for option 4.21, created by Zhuchkov Oleg.\n"
    "-h --help: Display parameters information\n"
    "-i --input: Name of the input png. REQUIRED (if not using --input put the filename at the end of command line)\n"
    "-o --output: Name for the output png. out.png by default\n"
    "--info: Display png information\n"
    "--rect: Draw a rectangle\n"
    "--hexagon: Draw a hexagon\n"
    "--copy: Copy a rectangular area\n"
    "--left_up: First corner of an area (for rectangle and copy)\n"
    "--right_down: Second corner of an area\n"
    "--center: Center of the hexagon\n"
    "--radius: Radius of the hexagon\n"
    "--thickness: Thickness of drawn figures\n"
    "--color: Color of drawn figures\n"
    "--fill: Fill drawn shape\n"
    "--fill_color: Color to fill drawn shape\n"
    "Coords format: x.y Color format: r.g.b\n");
}

void init_params(params_t* params){
    params->input = NULL;
    params->output = "out.png";
    params->info = false;
    params->help = false;
    params->rect = false;
    params->left_up_x = -1;
    params->left_up_y = -1;
    params->right_down_x = -1;
    params->right_down_y = -1;
    params->thickness = -1;
    params->color.r = -1;
    params->color.g = -1;
    params->color.b = -1;
    params->fill = false;
    params->fill_color.r = -1;
    params->fill_color.g = -1;
    params->fill_color.b = -1;
    params->hexagon = false;
    params->center_x = -1;
    params->center_y = -1;
    params->radius = -1;
    params->copy=false;
    params->dest_left_up_x=-1;
    params->dest_left_up_y=-1;
    params->color_input=false;
    params->fcolor_input=false;
    params->blur = false;
    params->size = -1;
}

void raise_arg_error(){
    puts("Incorrect or missing argument(s)!");
    exit(42);
}

void parse_coords(char* arg, int* x, int* y){
    char xx[30], yy[30];
    int i=0, j=0, l=0;
    while (arg[i] != '\0'){
        if (arg[i]== '.'){
            xx[l] = '\0';
            if (j==1) raise_arg_error();
            j++;
            i++;
            l = 0;
            continue;
        }
        if ((arg[i]>'9'||arg[i]<'0')&&arg[i]!='-') raise_arg_error();
        if (j==0){
            xx[l] = arg[i];
        }
        else{
            yy[l] = arg[i];
        }
        i++;
        l++;
    }
    yy[l] = '\0';
    if(strlen(xx) == 0 || strlen(yy) == 0) raise_arg_error();
    *x = strtol(xx,NULL,10);
    *y = strtol(yy,NULL,10);
}

void parse_rgb(char* arg, rgb_t* rgb){
    char r[30], g[30], b[30];
    int i=0, j=0, l=0;
    while (arg[i] != '\0'){
        if (arg[i]== '.'){
            if (j==2) raise_arg_error();
            if (j==1){
                g[l] = '\0';
            }
            if (j==0){
                r[l] = '\0';
            }
            j++;
            i++;
            l=0;
            continue;
        }
        if (arg[i]>'9'||arg[i]<'0') raise_arg_error();
        if (j==0){
            r[l] = arg[i];
        }
        if (j==1){
            g[l] = arg[i];
        }
        else
            b[l] = arg[i];
        i++;
        l++;
    }
    b[l] = '\0';
    if (strlen(r) == 0 || strlen(g) == 0 || strlen(b) == 0) raise_arg_error();
    int rr = strtol(r,NULL,10);
    int gg = strtol(g,NULL,10);
    int bb = strtol(b,NULL,10);
    if (rr > 255 || gg > 255 || bb > 255) raise_arg_error();
    *rgb = int_to_rgb(rr,gg,bb);
}

void parse_params(params_t* optparams, int argc, char** argv){
    opterr = 0;
    static struct option options[] = {
        {"input", 1, NULL, 'i'},
        {"output", 1, NULL, 'o'},
        {"info", 0, NULL, 400},
        {"help", 0, NULL, 'h'},
        {"rect", 0, NULL, 401},
        {"left_up", 1, NULL, 402},
        {"right_down", 1, NULL, 403},
        {"thickness", 1, NULL, 404},
        {"color", 1, NULL, 405},
        {"fill", 0, NULL, 406},
        {"fill_color", 1, NULL, 407},
        {"hexagon", 0, NULL, 408},
        {"center", 1, NULL, 409},
        {"radius", 1, NULL, 410},
        {"copy", 0, NULL, 411},
        {"dest_left_up", 1, NULL, 412},
        {"blur", 0, NULL, 413},
        {"size", 1, NULL, 414},
        {0,0,0,0}
    };
    int c = 1;
    int arg;
    while(c != -1){
        c = getopt_long(argc, argv, "hi:o:",options,NULL);
        if (c == -1) break;
        switch (c){
            case 'h':{
                optparams->help = true;
                break;}
            case 'i':{
                optparams->input = optarg;
                break;
                }
            case 'o':{
                optparams->output = optarg;
                break;
                }
            case 400:{
                optparams->info = true;
                break;
                }
            case 401:{
                optparams->rect = true;
                break;
                }
            case 402:{
                parse_coords(optarg, &(optparams->left_up_x), &(optparams->left_up_y));
                break;
            }
            case 403:{
                parse_coords(optarg, &(optparams->right_down_x), &(optparams->right_down_y));
                break;
            }
            case 404:{
                arg = strtol(optarg, NULL, 10);
                if (arg <= 0) raise_arg_error();
                optparams->thickness = arg;
                break;
            }
            case 405:{
                parse_rgb(optarg, &(optparams->color));
                optparams->color_input=true;
                break;
            }
            case 406:{
                optparams->fill = true;
                break;
            }
            case 407:{
                parse_rgb(optarg, &(optparams->fill_color));
                optparams->fcolor_input=true;
                break;
            }
            case 408:{
                optparams->hexagon = true;
                break;
            }
            case 409:{
                parse_coords(optarg, &(optparams->center_x), &(optparams->center_y));
                break;
                }
            case 410:{
                arg = strtol(optarg, NULL, 10);
                if (arg <= 0) raise_arg_error();
                optparams->radius = arg;
                break;
            }
            case 411:{
                optparams->copy = true;
                break;
            }
            case 412:{
                parse_coords(optarg, &(optparams->dest_left_up_x), &(optparams->dest_left_up_y));
                break;
            }
            case 413:{
                optparams->blur = true;
                break;
            }
            case 414:{
                arg = strtol(optarg, NULL, 10);
                if (arg <= 0) raise_arg_error();
                optparams->size = arg;
                break;
            }
            case '?':{
                raise_arg_error();
                break;
            }
            default:{
                raise_arg_error();
                break;
            }
        }
    }
    if (optparams->help){
        print_help();
        exit(0);
    }
    if (optparams->input == NULL && optind == argc - 1) 
    {
        optparams->input = calloc(strlen(argv[argc - 1]) + 1, sizeof(char));
        strncpy(optparams->input, argv[argc - 1], strlen(argv[argc - 1]) + 1);
    }
    if (optparams->input == NULL){
        puts("No input file!");
        exit(49);
    };

}