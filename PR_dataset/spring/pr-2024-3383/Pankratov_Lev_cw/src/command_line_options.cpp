#include "command_line_options.hpp"

void processingFlags(int argc, char **argv)
{
    if (argc == 1){
        printInstruction();
        exit(0);
    }

    char shortFlag[] = "di:o:hIL:R:gpl:r:a:b:c:sv:S:f:";

    struct option longFlag[] =
        {
            {"info", no_argument, NULL, 'd'},
            {"input", required_argument, NULL, 'i'},
            {"output", required_argument, NULL, 'o'},
            {"help", no_argument, NULL, 'h'},

            {"inverse", no_argument, NULL, 'I'},
            {"left_up", required_argument, NULL, 'L'},
            {"right_down", required_argument, NULL, 'R'},

            {"gray", no_argument, NULL, 'g'},

            {"resize", no_argument, NULL, 'p'},
            {"left", required_argument, NULL, 'l'},
            {"right", required_argument, NULL, 'r'},
            {"above", required_argument, NULL, 'a'},
            {"below", required_argument, NULL, 'b'},
            {"color", required_argument, NULL, 'c'},

            {"square_rhombus", no_argument, NULL, 's'},
            {"upper_vertex", required_argument, NULL, 'v'},
            {"size", required_argument, NULL, 'S'},
            {"fill_color", required_argument, NULL, 'c'},


            {NULL, 0, NULL, 0}};

    int8_t option = 0, chosenOperation = 0;
    int32_t longIndex = 0;
    std::string inputPathFile;
    std::string outputPathFile = "output.bmp";
    std::pair<bool, bool> isCoord = {false, false};
    bool isColor = false;
    int16_t size = 0;
    Coordinates coord;
    Coord coordinates;
    BmpSystem::Rgb rgb = {0,0,0};
    Side side = {0, 0, 0, 0};
    while ((option = getopt_long(argc, argv, shortFlag, longFlag, &longIndex)) != -1)
    {
        switch (option)
        {
        case 'd':
            if (inputPathFile == "")
            {
                std::cout << "Вы не ввели путь к файлу" << std::endl;
                exit(40);
            }
            chosenOperation = 1;
            break;
        case 'i':
        {
            inputPathFile = optarg;
            break;
        }
        case 'o':
        {
            outputPathFile = optarg;
            break;
        }
        case 'h':
            printInstruction();
            exit(0);
            break;
        case 'I':
        {
            chosenOperation = 2;
            break;
        }
        case 'L':
        {
            auto save = split(optarg, ".");
            try {
                coord.leftX = std::stoi(save[0]);
                coord.leftY = std::stoi(save[1]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            isCoord.first = true;
            break;
        }
        case 'R':
        {
            auto save = split(optarg, ".");
            try {
                coord.rightX = std::stoi(save[0]);
                coord.rightY = std::stoi(save[1]);
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            isCoord.second = true;
            break;
        }
        case 'g':
        {
            chosenOperation = 3;
            break;
        }
        case 'p':
        {
            chosenOperation = 4;
            break;
        }
        case 'l':
        {
            try {
                side.left = std::stoi(optarg);
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }

            break;
        }
        case 'r':
        {
            try {
                side.right = std::stoi(optarg);
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            break;
        }
        case 'a':
        {
            try {
                side.above = std::stoi(optarg);
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            break;
        }
        case 'b':
        {
            try {
                side.below = std::stoi(optarg);
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            break;
        }
        case 'c':
        {
            auto color = split(optarg, ".");
            try {
                if (color.size() != 3)
                {
                    exit(40);
                }
                int red = std::stoi(color[0]);
                int green = std::stoi(color[1]);
                int blue = std::stoi(color[2]);

                if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) {
                    std::cout << "Цветовое значение вне диапазона (0-255)" << std::endl;
                    exit(40);
                }

                rgb.rgbRed = static_cast<uint8_t>(red);
                rgb.rgbGreen = static_cast<uint8_t>(green);
                rgb.rgbBlue = static_cast<uint8_t>(blue);
                isColor = true;
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента: не число" << std::endl;
                exit(40);
            } catch (std::out_of_range& e) {
                std::cout << "Неправильный формат аргумента: число вне диапазона" << std::endl;
                exit(40);
            }
            break;
        }
    
        case 's':
        {
            chosenOperation = 5;
            break;
        }
        case 'v':
        {
            auto save = split(optarg, ".");
            try {
                coordinates.x = std::stoi(save[0]);
                coordinates.y = std::stoi(save[1]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            isCoord.first = true;
            break;
        }
        case 'S':
        {
            try {
                size = std::stoi(optarg);
            } catch (std::invalid_argument& e) {
                std::cout << "Неправильный формат аргумента" << std::endl;
                exit(40);
            }
            if (size <= 0)
            {
                std::cout << "Размер стороны должен быть положительным" << std::endl;
                exit(40);
            }
            break;
        }
        }
    }

    BmpSystem::Bmp bmp(inputPathFile.c_str());
    switch (chosenOperation)
    {
    case 1:
        bmp.printFileInfo();
        exit(0);
        break;

    case 2:
        if (!isCoord.first || !isCoord.second)
        {
            std::cout << "Вы не ввели координаты одного из углов" << std::endl;
            exit(40);
        }
        bmp.replaceCoord(&coord);
        bmp.inverseColorInArea(outputPathFile.c_str(), coord);
        break;
    
    case 3:
        if (!isCoord.first || !isCoord.second)
        {
            std::cout << "Вы не ввели координаты одного из углов" << std::endl;
            exit(40);
        }
        bmp.replaceCoord(&coord);
        bmp.blackAndWhite(outputPathFile.c_str(), coord);
        break;

    case 4:
        if (isColor != true || (side.left == 0 && side.right == 0 && side.above == 0 && side.below == 0))
        {
            std::cout << "Вы не ввели один из аргументов" << std::endl;
            exit(40);
        }
        else
        {
            bmp.resize(outputPathFile.c_str(), side, rgb);
        }
        break;
    
    case 5:
    {
        if (isColor != true || size == 0 || coordinates.x == 0 || coordinates.y == 0)
        {
            std::cout << "Вы не ввели один из аргументов" << std::endl;
            exit(40);
        }
        bmp.drawRomb(outputPathFile.c_str(), coordinates, rgb, size);
        break;
    }
    }

    bmp.writeBmp(outputPathFile.c_str());
}