#include "input_system.h"
#include <getopt.h>
#include <iostream>


using namespace std;

Arguments::Arguments()
{
    x0 = 0;
    x1 = 0;
    x2 = 0;
    y0 = 0;
    y1 = 0;
    y2 = 0;

    opt_number = 0;
    thickness = -1;
    number_x = 0;
    number_y = 0;

    old_color = new int[4];

    if (old_color == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    old_color[0] = 0;
    old_color[1] = 0;
    old_color[2] = 0;
    old_color[3] = 255;

    new_color = new int[4];

    if (new_color == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    new_color[0] = 0;
    new_color[1] = 0;
    new_color[2] = 0;
    new_color[3] = 255;

    fill_color = new int[4];

    if (fill_color == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    fill_color[0] = 0;
    fill_color[1] = 0;
    fill_color[2] = 0;
    fill_color[3] = 255;

    color = new int[4];

    if (color == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 255;

    is_fill = false;
    is_help = false;
    is_info = false;

    input_img_path = "";
    output_img_path = "output.png";
}

Arguments::~Arguments()
{
    delete[] old_color;
    delete[] new_color;
    delete[] fill_color;
    delete[] color;
}

Arguments* readArguments(int argc, char** argv)
{
    Arguments* args = new Arguments();

    if (args == NULL)
            {
                cout << "Memory error\n";
                exit(45);
            }

    args->input_img_path = argv[argc - 1];

    const char* short_opts = "vhf:TRCLp:t:c:FI:o:O:N:y:x:s:e:";

    int opt;
    const struct option long_opts[] ={
            {"rhombus",no_argument,NULL,'v'},
            {"help", no_argument, NULL, 'h'},
            {"info", required_argument,NULL,'f'},
            {"triangle", no_argument,NULL,'T'},
            {"biggest_rect", no_argument,NULL,'R'},
            {"collage", no_argument,NULL,'C'},
            {"line", no_argument,NULL, 'L'},
            {"points", required_argument, NULL, 'p' },
            {"thickness", required_argument, NULL, 't' },
            {"color", required_argument, NULL, 'c' },
            {"fill", no_argument, NULL, 'F' },
            {"fill_color", required_argument, NULL, 'I' },
            {"output", required_argument, NULL, 'o' },
            {"input", required_argument, NULL, 'i' },
            {"old_color", required_argument, NULL, 'O' },
            {"new_color", required_argument, NULL, 'N' },
            {"number_y", required_argument, NULL, 'y' },
            {"number_x", required_argument, NULL, 'x' },
            {"start", required_argument, NULL, 's' },
            {"end", required_argument, NULL, 'e' }
    };

    while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1)
    {
        switch (opt)
        {   
            
            case 'h':
            {
                args->is_help = true;
                break;
            }
            case 'f':
            {
                args->is_info = true;
                break;
            }
            case 'T':
            {
                args->opt_number = 1;
                break;
            }
            case 'v':
            {
                args->opt_number = 5;
                
                break;
            }
            case 'R':
            {
                args->opt_number = 2;
                break;
            }
            case 'C':
            {
                args->opt_number = 3;
                break;
            }
            case 'L':
            {
                args->opt_number = 4;
                break;
            }
            case 'p':
            {
                int n = sscanf(optarg, "%d.%d.%d.%d.%d.%d", &args->x0, &args->y0, &args->x1, &args->y1,&args->x2, &args->y2);
                if (n != 6)
                {
                    cout << "Invalid points format\n";
                    exit(41);
                }
                break;
            }
            case 't':
            {
                int n = sscanf(optarg, "%f", &args->thickness);
                if(n==1)
                {
                    if(args->thickness <= 0)
                    {
                        cout << "Invalid thickness value\n";
                        exit(42);
                    }
                }
                else
                {
                    cout << "Invalid thickness format\n";
                    exit(41);
                }
                break;
            }
            case 'c':
            {
                int n = sscanf(optarg, "%d.%d.%d", &args->color[0], &args->color[1], &args->color[2]);
                if (n == 3)
                {
                    if(!(args->color[0] >= 0 && args->color[0] <= 255 && args->color[1] >= 0 && args->color[1] <= 255 && args->color[2] >= 0 && args->color[2] <= 255))
                    {
                        cout << "Invalid color values";
                        exit(42);
                    }
                }
                else
                {
                    cout << "Invalid color format\n";
                    exit(41);
                }
                break;
            }
            case 'F':
            {
                args->is_fill = true;
                break;
            }
            case 'I':
            {
                int n = sscanf(optarg, "%d.%d.%d", &args->fill_color[0], &args->fill_color[1], &args->fill_color[2]);
                if (n == 3)
                {
                    if(!(args->fill_color[0] >= 0 && args->fill_color[0] <= 255 && args->fill_color[1] >= 0 && args->fill_color[1] <= 255 && args->fill_color[2] >= 0 && args->fill_color[2] <= 255))
                    {
                        cout << "Invalid color values";
                        exit(42);
                    }

                }
                else
                {
                    cout << "Invalid color format\n";
                    exit(41);
                }
                break;
            }
            case 'o':
            {
                args->output_img_path = optarg;
                break;
            }
            case 'i':
            {
                args->input_img_path = optarg;
                break;
            }
            case 'O':
            {
                int n = sscanf(optarg, "%d.%d.%d", &args->old_color[0], &args->old_color[1], &args->old_color[2]);
                if (n == 3)
                {
                    if(!(args->old_color[0] >= 0 && args->old_color[0] <= 255 && args->old_color[1] >= 0 && args->old_color[1] <= 255 && args->old_color[2] >= 0 && args->old_color[2] <= 255))
                    {
                        cout << "Invalid color values";
                        exit(42);
                    }
                }
                else
                {
                    cout << "Invalid color format\n";
                    exit(41);
                }
            }
            case 'N':
            {
                int n = sscanf(optarg, "%d.%d.%d", &args->new_color[0], &args->new_color[1], &args->new_color[2]);
                if (n == 3)
                {
                    if(!(args->new_color[0] >= 0 && args->new_color[0] <= 255 && args->new_color[1] >= 0 && args->new_color[1] <= 255 && args->new_color[2] >= 0 && args->new_color[2] <= 255))
                    {
                        cout << "Invalid color values";
                        exit(42);
                    }
                }
                else
                {
                    cout << "Invalid color format\n";
                    exit(41);
                }
                break;
            }
            case 'y':
            {
                int n = sscanf(optarg,"%d",&args->number_y);
                if(n!=1)
                {
                    cout << "Invalid int value";
                    exit(41);
                }
                if(args->number_y<1)
                {
                    cout << "Invalid number_y value";
                    exit(42);
                }

                break;
            }
            case 'x':
            {

                int n = sscanf(optarg,"%d",&args->number_x);
                if(n!=1)
                {
                    cout << "Invalid int value";
                    exit(41);
                }
                if(args->number_x<1)
                {
                    cout << "Invalid number_x value";
                    exit(42);
                }

                break;
            }case 's':
            {
                int n = sscanf(optarg, "%d.%d",&args->x1, &args->y1);
                if (n != 2)
                {
                    cout << "Invalid points format\n";
                    exit(41);
                }
                break;
            }
            case 'e':
            {
                int n = sscanf(optarg, "%d.%d", &args->x0, &args->y0);
                if (n != 2)
                {
                    cout << "Invalid points format\n";
                    exit(41);
                }
                break;

            }
            default:
            {
                cout << "Unknown flag\n";
                exit(43);
            }
        }
    }

    return args;

}