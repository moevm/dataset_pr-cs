#include "headers/structuresDefinition.hpp"
#include "headers/additional_funcs.hpp"
#include "headers/drawing_funcs.hpp"
#include "headers/rotate_func.hpp"
#include "headers/options.hpp"
#include <sstream>

int main(int argc, char *argv[]) {
    int chosen_function = 0;
    int option = getopt_long(argc, argv, smallOpts, options, nullptr);
    std::string input_filename = argv[argc - 1];
    std::string output_filename = "out.bmp";
    std::pair<int, int> leftUp, rightDown, center;
    bool leftUpDefined = false, rightDownDefined = false, centerDefined = false;
    int thickness = 0, radius = 0, count = 0, angle = 0, num;
    bool radiusDefined = false, thicknessDefined = false, countDefined = false, angleDefined = false, numDefined = false;
    std::string color, fillColor, pattern;
    bool is_filled = false;
    if (option == -1) {
        print_help();
        return 0;
    }
    for (; option != -1; option = (getopt_long(argc, argv, smallOpts, options, nullptr))) {
        switch (option) {
            case 'h':
                print_help();
                return 0;
            case 'R':
                chosen_function = 1;
                break;
            case 'C':
                chosen_function = 2;
                break;
            case 'O':
                chosen_function = 3;
                break;
            case 's':
                chosen_function = 4;
                break;
            case 'g':
                chosen_function = 5;
                break;
            case 'i':
                input_filename = optarg;
                break;
            case 'o':
                output_filename = optarg;
                break;
            case 'l': {
                std::stringstream ss(optarg);
                char c;
                if (ss >> leftUp.first >> c >> leftUp.second) {
                    if (ss.eof()) {
                        leftUpDefined = true;
                        break;
                    }
                } else {
                    std::cout << "Wrong leftUp format: " << optarg << std::endl;
                    return 46;
                }
                break;
            }
            case 'r': {
                std::stringstream ss(optarg);
                char c;
                if (ss >> rightDown.first >> c >> rightDown.second) {
                    if (ss.eof()) {
                        rightDownDefined = true;
                        break;
                    }
                } else {
                    std::cout << "Wrong rightDown format: " << optarg << std::endl;
                    return 46;
                }
                break;
            }
            case 't':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        std::cout << "Wrong input format" << std::endl;
                        return 46;
                    }
                }
                thickness = std::stoi(optarg);
                if (thickness < 1) {
                    std::cout << "Thickness must be greater than 0" << std::endl;
                    return 47;
                }
                thicknessDefined = true;
                break;
            case 'c':
                color = optarg;
                break;
            case 'f':
                is_filled = true;
                break;
            case 'F':
                fillColor = optarg;
                break;
            case 'a': {
                std::stringstream ss(optarg);
                char c;
                if (ss >> center.first >> c >> center.second) {
                    if (ss.eof()) {
                        centerDefined = true;
                        break;
                    }
                } else {
                    std::cout << "Wrong input format" << std::endl;
                    return 46;
                }
                break;
            }
            case 'd':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        std::cout << "Wrong input format" << std::endl;
                        return 46;
                    }
                }
                radius = std::stoi(optarg);
                if (radius < 1) {
                    std::cout << "Radius must be greater than 0" << std::endl;
                    return 47;
                }
                radiusDefined = true;
                break;
            case 'p':
                pattern = optarg;
                if (pattern != "rectangle" && pattern != "circle" && pattern != "semicircles" && pattern != "koch") {
                    std::cout << "Wrong pattern : [" << pattern << "]" << std::endl;
                    return 48;
                }
                break;
            case 'n':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        std::cout << "Wrong input format" << std::endl;
                        return 46;
                    }
                }
                count = std::stoi(optarg);
                if (count < 1) {
                    std::cout << "Count must be greater than 0" << std::endl;
                    return 47;
                }
                countDefined = true;
                break;
            case 'u':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        std::cout << "Wrong input format" << std::endl;
                        return 46;
                    }
                }
                angle = std::stoi(optarg);
                if (angle != 90 && angle != 180 && angle != 270) {
                    std::cout << "Wrong angle" << std::endl;
                    return 47;
                }
                angleDefined = true;
                break;
            case 'Z':
                chosen_function = 6;
                break;
            case 'N':
                for (int i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        std::cout << "Wrong input format" << std::endl;
                        return 46;
                    }
                }
                num = std::stoi(optarg);
                if(num<1){
                    std::cout<<"Wrong compression"<<std::endl;
                    return 46;
                }
                numDefined = true;
                break;
            default:
                std::cout << "Unknown option: " << argv[optind - 1] << std::endl;
                return 45;
        }
    }
    Bmp input(input_filename.c_str());
    switch (chosen_function) {
        case 1:
            if (!leftUpDefined) {
                std::cout << "Left up corner not defined" << std::endl;
                return 49;
            }
            if (!rightDownDefined) {
                std::cout << "Right down corner not defined" << std::endl;
                return 49;
            }
            if (!thicknessDefined) {
                std::cout << "Thickness not defined" << std::endl;
                return 49;
            }
            if (color.empty()) {
                std::cout << "Color not defined" << std::endl;
                return 49;
            }
            if (is_filled && fillColor.empty()) {
                std::cout << "Fill flag is true, but fill color not defined" << std::endl;
                return 49;
            }
            input.draw_rectangle(leftUp, rightDown, thickness, color.c_str(), is_filled, fillColor.c_str());
            break;
        case 2:
            if (!centerDefined) {
                std::cout << "Center not defined" << std::endl;
                return 49;
            }
            if (!radiusDefined) {
                std::cout << "Radius not defined" << std::endl;
                return 49;
            }
            if (color.empty()) {
                std::cout << "Color not defined" << std::endl;
                return 49;
            }
            if (is_filled && fillColor.empty()) {
                std::cout << "Fill flag is true, but fill color not defined" << std::endl;
                return 49;
            }
            if (!thicknessDefined) {
                std::cout << "Thickness not defined" << std::endl;
                return 49;
            }
            input.draw_circle(center, radius, thickness, color.c_str(), is_filled, fillColor.c_str());
            break;
        case 3:
            if (pattern.empty()) {
                std::cout << "Pattern not defined" << std::endl;
                return 49;
            }
            if (color.empty()) {
                std::cout << "Color not defined" << std::endl;
                return 49;
            }
            if (pattern != "circle" && !thicknessDefined) {
                std::cout << "Thickness not defined" << std::endl;
                return 49;
            }
            if (pattern != "circle" && !countDefined) {
                std::cout << "Count not defined" << std::endl;
                return 49;
            }
            input.drawOrnament(pattern.c_str(), color.c_str(), thickness, count);
            break;
        case 4:
            if (!angleDefined) {
                std::cout << "Angle not defined" << std::endl;
                return 49;
            }
            if (!leftUpDefined) {
                std::cout << "Left up corner not defined" << std::endl;
                return 49;
            }
            if (!rightDownDefined) {
                std::cout << "Right down corner not defined" << std::endl;
                return 49;
            }
            input.rotate_image(leftUp, rightDown, angle);
            break;
        case 5:
            input.get_info();
            return 0;
        case 6:
            if(!numDefined){
                std::cout<<"scale not defined"<<std::endl;
                return 49;
            }
            input.compress(num);
            break;
        default:
            std::cout << "Unknown function" << std::endl;
            return 47;
    }
    input.save(output_filename.c_str());
    return 0;
}