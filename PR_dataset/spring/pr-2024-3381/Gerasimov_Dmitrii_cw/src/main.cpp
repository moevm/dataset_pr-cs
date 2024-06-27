#include "./include/Circle.hpp"
#include "./include/Color.hpp"
#include "./include/ImageReader.hpp"
#include "./include/ImageRedactor.hpp"
#include "./include/Line.hpp"
#include "./include/PngReader.hpp"
#include "./include/Rectangle.hpp"

#include <getopt.h>
#include <iostream>

using namespace std;

#define ARGUMENT_ERR 40
#define IMAGE_ERR 41
#define REDACTOR_ERR 42

int main(int argc, char **argv)
{
    const char *s_opt = "Ihi:o:Cl:r:d:RO:n:up:c:t:k:fb:H";
    struct option l_opt[] = {{"info", no_argument, NULL, 'I'},
                             {"help", no_argument, NULL, 'h'},
                             {"input", required_argument, NULL, 'i'},
                             {"output", required_argument, NULL, 'o'},

                             {"copy", no_argument, NULL, 'C'},
                             {"left_up", required_argument, NULL, 'l'},
                             {"right_down", required_argument, NULL, 'r'},
                             {"dest_left_up", required_argument, NULL, 'd'},

                             {"color_replace", no_argument, NULL, 'R'},
                             {"old_color", required_argument, NULL, 'O'},
                             {"new_color", required_argument, NULL, 'n'},

                             {"ornament", no_argument, NULL, 'u'},
                             {"pattern", required_argument, NULL, 'p'},
                             {"color", required_argument, NULL, 'c'},
                             {"thickness", required_argument, NULL, 't'},
                             {"count", required_argument, NULL, 'k'},

                             {"filled_rects", no_argument, NULL, 'f'},
                             {"border_color", required_argument, NULL, 'b'},

                             {"rhombus",no_argument,NULL,'H'},

                             {0, 0, 0, 0}};
    int opt_ind = 0;
    int c;
    string input = "0";
    string output = "out.png";
    short comm = 100;
    Vector2i left_up;
    Vector2i right_down;
    Vector2i dest_left_up;
    Color color;
    Color color2;
    ImageRedactor::OrnametType pattern;
    int64_t thickness = 0;
    int64_t count = 0;
    int arr[] = {0, 0, 0, 0, 0};
    while ((c = getopt_long(argc, argv, s_opt, l_opt, &opt_ind)) != -1)
    {
        switch (c)
        {
            case 'I':
                comm = 4;
                break;
            case 'h':
                comm = 5;
                break;
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case 'C':
                comm = 0;
                arr[0]++;
                break;
            case 'l':
                if (sscanf(optarg, "%ld.%ld", &left_up.x, &left_up.y) != 2)
                {
                    std::cout
                        << "Error: wrong coordinates format. Run with '--help' "
                           "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[0]++;
                break;
            case 'r':
                if (sscanf(optarg, "%ld.%ld", &right_down.x, &right_down.y) !=
                    2)
                {
                    std::cout
                        << "Error: wrong coordinates format. Run with '--help' "
                           "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[0]++;
                break;
            case 'd':
                if (sscanf(optarg, "%ld.%ld", &dest_left_up.x,
                           &dest_left_up.y) != 2)
                {
                    std::cout
                        << "Error: wrong coordinates format. Run with '--help' "
                           "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[0]++;
                break;
            case 'R':
                comm = 1;
                arr[1]++;
                break;
            case 'b':
                arr[3]++;
                arr[1]--;
                [[fallthrough]];
            case 'n':
                if (sscanf(optarg, "%hhd.%hhd.%hhd", &color2.r, &color2.g,
                           &color2.b) != 3)
                {
                    std::cout << "Error: wrong color format. Run with '--help' "
                                 "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[1]++;
                break;
            case 'u':
                comm = 2;
                arr[2]++;
                break;
            case 'p':
                if (string(optarg) == "rectangle")
                    pattern = ImageRedactor::OrnametType::rectangle;
                else if (string(optarg) == "circle")
                    pattern = ImageRedactor::OrnametType::circle;
                else if (string(optarg) == "semicircles")
                    pattern = ImageRedactor::OrnametType::semicircles;
                else
                {
                    std::cout
                        << "Error: wrong pattern format. Run with '--help' "
                           "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[2]++;
                break;
            case 'H':
                comm =  6;
                arr[4]++;
                break;
            case 'c':
                arr[2]++;
                arr[3]++;
                arr[4]++;
                arr[1]--;
                [[fallthrough]];
            case 'O':
                if (sscanf(optarg, "%hhd.%hhd.%hhd", &color.r, &color.g,
                           &color.b) != 3)
                {
                    std::cout << "Error: wrong color format. Run with '--help' "
                                 "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[1]++;
                break;
            case 't':
                if (sscanf(optarg, "%ld", &thickness) != 1 && thickness > 0)
                {
                    std::cout
                        << "Error: wrong thickness format. Run with '--help' "
                           "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[2]++;
                arr[3]++;
                break;
            case 'k':
                if (sscanf(optarg, "%ld", &count) != 1 && count > 0)
                {
                    std::cout << "Error: wrong count format. Run with '--help' "
                                 "flag for more information\n"; // ERROR
                    return ARGUMENT_ERR;
                }
                arr[2]++;
                break;
            case 'f':
                comm = 3;
                arr[3]++;
                break;
            case '?':
                std::cout << "Error: unknown flag. Run with '--help' flag for "
                             "more information\n"; // ERROR
                return ARGUMENT_ERR;
                break;
            default:
                break;
        }
    }

    if (optind < argc)
    {
        input = argv[optind++];
        while (optind < argc)
            cout << "Unknown argument ignored: " << argv[optind++] << '\n';
    }


    if (comm == 5 || argc == 1)
    {
        cout << "Course work for option 5.16, created by Dmitrii Gerasimov\n";
        if (argc > 2)
        {
            cout << "Too many arguments for '--help' flag. Some arguments was "
                    "ignored.\n";
        }
        cout << "Options:\n";

        cout << " Global:\n";

        cout << "  -h --help: print help tip.\n";
        cout << "  -I --info: print image info.\n";
        cout << "  -i --input: type input file.\n";
        cout << "  -o --output: type output file.\n";

        cout << " Image processing functions:\n";
        cout << " (1) -C --copy: copy image area. Args:\n";
        cout << "      -l --left_up: left up corner of source area.\n";
        cout << "      -r --right_down: right_down corner of source area.\n";
        cout
            << "      -d --dest_left_up: left up corner of destination area.\n";

        cout << " (2) -R --color_replace: replace all pixels with specified "
                "color to another. Args:\n";
        cout << "      -O --old_color: color to find.\n";
        cout << "      -n --new_color: color to replace.\n";

        cout << " (3) -u --ornament: draws ornament with specified parameters "
                "on image. Args:\n";
        cout << "      -p --pattern: ornament pattern(circle, rectangle or "
                "semicirles).\n";
        cout << "      -c --color: color of ornament.\n";
        cout << "      -t --thickness: thickness of ornament.\n";
        cout << "      -k --count: count of circles for 'semicircles' pattern "
                "and rectangles for 'rectangle' pattern.\n";

        cout << " (4) -f --filled_rects: outlines all rectangles of the "
                "specified color. Args:\n";
        cout << "      -c --color: color of rectangles to find.\n";
        cout << "      -b --border_color: color of outline.\n";
        cout << "      -t --thickness: thickness of outline.\n";

        cout << "Note: all coordinates must be in format 'x.y' and all colors "
                "must be in format 'rrr.ggg.bbb'\n";
        return 0;
    }

    if (input == "0")
    {
        std::cout << "Error: no input file specified. Run with '--help' flag "
                     "for more information\n"; // ERROR
        return ARGUMENT_ERR;
    }

    if (input == output)
    {
        std::cout
            << "Error: input and output file must be different files.\n"; // ERROR
        return ARGUMENT_ERR;
    }

    PngReader image{input, output};
    try
    {
        image.load();
    }
    catch (const exception &e)
    {
        std::cout << "Error while reading image:\n" << e.what() << '\n';
        return IMAGE_ERR;
    }

    if (comm == 4)
    {
        if (argc != 3)
        {
            cout << "Too many arguments for '--info' flag. Some arguments was "
                    "ignored.\n";
        }
        cout << "File info:\n";
        cout << "Name: " + input + '\n';
        cout << "Width: " << image.get_size().x << '\n';
        cout << "Height: " << image.get_size().y << '\n';
        cout << "Mode: RGB\n";
        cout << "Bit depth: " << int(image.get_depth()) << '\n';
        return 0;
    }

    ImageRedactor redactor{image};

    switch (comm)
    {
        case 0:
            if (arr[0] != 4)
            {
                std::cout << "Error: too few arguments for '--copy' flag. Run "
                             "with '--help' flag for more information\n";
                return ARGUMENT_ERR;
            }
            if (arr[1] != 0 || arr[2] != 0 || arr[3] != 0 && arr[4]!=0)
            {
                std::cout << "Too many arguments for '--copy' flag. Some "
                             "arguments was ignored.\n";
                return ARGUMENT_ERR;
            }
            try
            {
                redactor.copy(left_up, right_down, dest_left_up);
            }
            catch (const exception &e)
            {
                cout << "Error while image processing:\n" << e.what() << '\n';
                return REDACTOR_ERR;
            }
            break;
        case 1:
            if (arr[1] != 3)
            {
                std::cout
                    << "Error: too few arguments for '--color_replace' flag. "
                       "Run with '--help' flag for more information\n";
                return ARGUMENT_ERR;
            }
            if (arr[0] != 0 || arr[2] != 0 || arr[3] != 0 && arr[4]!=0)
            {
                std::cout << "Too many arguments for '--color_replace' flag. "
                             "Some arguments was ignored.\n";
                return ARGUMENT_ERR;
            }
            try
            {
                redactor.replace(color, color2);
            }
            catch (const exception &e)
            {
                cout << "Error while image processing:\n" << e.what() << '\n';
                return REDACTOR_ERR;
            }
            break;
        case 2:
            if (arr[2] != 5)
            {
                std::cout << "Error: too few arguments for '--ornament' flag. "
                             "Run with '--help' flag for more information\n";
                return ARGUMENT_ERR;
            }
            if (arr[0] != 0 || arr[1] != 0 || arr[3] != 2 && arr[4]!=1)
            {
                std::cout << "Too many arguments for '--ornament' flag. Some "
                             "arguments was ignored.\n";
                return ARGUMENT_ERR;
            }
            try
            {
                redactor.ornament(pattern, count, thickness, color);
            }
            catch (const exception &e)
            {
                cout << "Error while image processing:\n" << e.what() << '\n';
                return REDACTOR_ERR;
            }
            break;
        case 3:
            if (arr[3] != 4)
            {
                std::cout
                    << "Error: too few arguments for '--filled_rects' flag. "
                       "Run with '--help' flag for more information\n";
                return ARGUMENT_ERR;
            }
            if (arr[0] != 0 || arr[1] != 0 || arr[2] != 2 && arr[4]!=1)
            {
                std::cout << "Too many arguments for '--filled_rects' flag. "
                             "Some arguments was ignored.\n";
                return ARGUMENT_ERR;
            }
            try
            {
                redactor.filled_rects(color, color2, thickness);
            }
            catch (const exception &e)
            {
                cout << "Error while image processing:\n" << e.what() << '\n';
                return REDACTOR_ERR;
            }
            break;
        case 6:
            if (arr[4] != 2)
            {
                std::cout
                    << "Error: too few arguments for '--rhombus' flag. "
                       "Run with '--help' flag for more information\n";
                return ARGUMENT_ERR;
            }
            if (arr[0] != 0 || arr[1] != 0 || arr[2] != 1 && arr[3] != 1)
            {
                std::cout << "Too many arguments for '--filled_rects' flag. "
                             "Some arguments was ignored.\n";
                return ARGUMENT_ERR;
            }
            try
            {
                redactor.rhombus(color);
            }
            catch (const exception &e)
            {
                cout << "Error while image processing:\n" << e.what() << '\n';
                return REDACTOR_ERR;
            }
            break;
        default:
            cout << "Error: No one option choosed. " << comm << '\n';
            return ARGUMENT_ERR;
            break;
    }
    try
    {
        image.save();
    }
    catch (const std::exception &e)
    {
        cout << "Error while saving image:\n" << e.what() << '\n';
        return IMAGE_ERR;
    }


    return 0;
}
