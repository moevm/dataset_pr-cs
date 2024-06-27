#include <getopt.h>
#include <fstream>
#include <iostream>
#include <memory>
#include "../include/bmp/BMP.hpp"
#include "../include/bmp/exceptions.hpp"
#include "help.hpp"
#include "parsers.hpp"
#include "options.hpp"

#define EXIT_UNRECOGNIZED_OPTION 40
#define EXIT_INVALID_OPTION_ARGUMENT 41
#define EXIT_MISSING_OPTION_ARGUMENT 42
#define EXIT_MISSING_FUNCTION_OPTION 43
#define EXIT_MULTIPLE_FUNCTION_SELECTION 44
#define EXIT_NO_INPUT_FILE 45
#define EXIT_BMP_ERROR 46
#define EXIT_BMP_HEADER_FIELD_VALUE_NOT_SUPPORTED 47
#define EXIT_FILE_STREAM_ERROR 48
#define EXIT_UNRECOGNIZED_ERROR 49

#define DEFAULT_OUTPUT_FILE "out.bmp"


int main(int argc, char *argv[]) {
    std::cout << "Course work for option 5.2, created by Daniil Egunov" << std::endl;

    auto selectedFunction = Function::HELP;
    DrawOptions options;

    std::string inputFile;
    std::string outputFile = DEFAULT_OUTPUT_FILE;

    opterr = 0;

    int option_index;
    int res;
    while (true) {
        res = getopt_long(argc, argv, short_options, long_options, &option_index);
        if (res == -1)
            break;

        try {
            switch (res) {
                case 'h': {
                    printHelp();
                    exit(EXIT_SUCCESS);
                }
                case 'I': {
                    if (selectedFunction != Function::HELP) {
                        std::cerr << "Cannot specify more than one function" << std::endl;
                        exit(EXIT_MULTIPLE_FUNCTION_SELECTION);
                    }
                    selectedFunction = Function::INFO;
                    break;
                }
                case 'M': {
                    if (selectedFunction != Function::HELP) {
                        std::cerr << "Cannot specify more than one function" << std::endl;
                        exit(EXIT_MULTIPLE_FUNCTION_SELECTION);
                    }
                    selectedFunction = Function::MIRROR;
                    break;
                }
                case 'C': {
                    if (selectedFunction != Function::HELP) {
                        std::cerr << "Cannot specify more than one function" << std::endl;
                        exit(EXIT_MULTIPLE_FUNCTION_SELECTION);
                    }
                    selectedFunction = Function::COPY;
                    break;
                }
                case 'R': {
                    if (selectedFunction != Function::HELP) {
                        std::cerr << "Cannot specify more than one function" << std::endl;
                        exit(EXIT_MULTIPLE_FUNCTION_SELECTION);
                    }
                    selectedFunction = Function::COLOR_REPLACE;
                    break;
                }
                case 'S': {
                    if (selectedFunction != Function::HELP) {
                        std::cerr << "Cannot specify more than one function" << std::endl;
                        exit(EXIT_MULTIPLE_FUNCTION_SELECTION);
                    }
                    selectedFunction = Function::SPLIT;
                    break;
                }
                case 'O': {
                    if (selectedFunction != Function::HELP) {
                        std::cerr << "Cannot specify more than one function" << std::endl;
                        exit(EXIT_MULTIPLE_FUNCTION_SELECTION);
                    }
                    selectedFunction = Function::OUTSIDE_ORNAMENT;
                    break;
                }
                case 'i': {
                    inputFile = optarg;
                    break;
                }
                case 'o': {
                    outputFile = optarg;
                    break;
                }
                case 'a': {
                    options.axis = parseAxis(optarg);
                    break;
                }
                case 'f': {
                    options.left_up = parsePoint2D(optarg);
                    break;
                }
                case 's': {
                    options.right_down = parsePoint2D(optarg);
                    break;
                }
                case 'd': {
                    options.dest_left_up = parsePoint2D(optarg);
                    break;
                }
                case 'p': {
                    options.old_color = parseRGB(optarg);
                    break;
                }
                case 'n': {
                    options.new_color = parseRGB(optarg);
                    break;
                }
                case 'x': {
                    options.number_x = parseSplitNumber(optarg);
                    break;
                }
                case 'y': {
                    options.number_y = parseSplitNumber(optarg);
                    break;
                }
                case 't': {
                    options.thickness = parseThickness(optarg);
                    break;
                }
                case 'c': {
                    options.color = parseRGB(optarg);
                    break;
                }
                case ':': {
                    std::cerr << "Option " << argv[optind - 1] << " requires an argument" << std::endl;
                    exit(EXIT_MISSING_OPTION_ARGUMENT);
                }
                case '?':
                default: {
                    std::cerr << "Found unknown option " << argv[optind - 1] << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_INVALID_OPTION_ARGUMENT);
        }
    }

    if (optind < argc && inputFile.empty()) {
        inputFile = argv[optind];
    }

    if (selectedFunction != Function::HELP) {
        if (inputFile.empty()) {
            std::cerr << "No file selected" << std::endl;
            exit(EXIT_NO_INPUT_FILE);
        }
        std::cout << "Input file: " << inputFile << std::endl;
        std::cout << "Output file: " << outputFile << std::endl;
    }

    try {
        switch (selectedFunction) {
            case Function::HELP: {
                printHelp();
                exit(EXIT_SUCCESS);
            }
            case Function::INFO: {
                if (options.axis || options.left_up || options.right_down ||
                    options.dest_left_up || options.old_color || options.new_color || options.number_x ||
                    options.number_y || options.thickness || options.color) {
                    std::cerr << "Unrecognized options for info" << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
                BMP image(inputFile);
                image.printInfo();
                break;
            }
            case Function::MIRROR: {
                if (!(options.axis && options.left_up && options.right_down)) {
                    std::cerr << "Missing options for mirror" << std::endl;
                    exit(EXIT_MISSING_FUNCTION_OPTION);
                }
                if (options.dest_left_up || options.old_color || options.new_color || options.number_x ||
                    options.number_y || options.thickness || options.color) {
                    std::cerr << "Unrecognized options for mirror" << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
                BMP image(inputFile);
                std::cout << "Mirroring " << inputFile << "..." << std::endl;
                image.mirror(*options.axis, *options.left_up, *options.right_down);
                image.writeToFile(outputFile);
                break;
            }
            case Function::COPY: {
                if (!(options.left_up && options.right_down && options.dest_left_up)) {
                    std::cerr << "Missing options for copy" << std::endl;
                    exit(EXIT_MISSING_FUNCTION_OPTION);
                }
                if (options.axis || options.old_color || options.new_color || options.number_x ||
                    options.number_y || options.thickness || options.color) {
                    std::cerr << "Unrecognized options for copy" << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
                BMP image(inputFile);
                std::cout << "Copying " << inputFile << "..." << std::endl;
                image.copy(*options.left_up, *options.right_down, *options.dest_left_up);
                image.writeToFile(outputFile);
                break;
            }
            case Function::COLOR_REPLACE: {
                if (!(options.old_color && options.new_color)) {
                    std::cerr << "Missing options for color replace" << std::endl;
                    exit(EXIT_MISSING_FUNCTION_OPTION);
                }
                if (options.axis || options.left_up || options.right_down || options.dest_left_up ||
                    options.number_x || options.number_y || options.thickness || options.color) {
                    std::cerr << "Unrecognized options for color replace" << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
                BMP image(inputFile);
                std::cout << "Color replacing " << inputFile << "..." << std::endl;
                image.replaceColor(*options.old_color, *options.new_color);
                image.writeToFile(outputFile);
                break;
            }
            case Function::SPLIT: {
                if (!(options.number_x && options.number_y && options.thickness && options.color)) {
                    std::cerr << "Missing options for split" << std::endl;
                    exit(EXIT_MISSING_FUNCTION_OPTION);
                }
                if (options.axis || options.left_up || options.right_down ||
                    options.dest_left_up || options.old_color || options.new_color) {
                    std::cerr << "Unrecognized options for split" << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
                BMP image(inputFile);
                std::cout << "Splitting " << inputFile << "..." << std::endl;
                image.split(*options.number_x, *options.number_y, *options.color, *options.thickness);
                image.writeToFile(outputFile);
                break;
            }
            case Function::OUTSIDE_ORNAMENT: {
                if (!(options.thickness && options.color)) {
                    std::cerr << "Missing options for split" << std::endl;
                    exit(EXIT_MISSING_FUNCTION_OPTION);
                }
                if (options.axis || options.left_up || options.right_down ||
                    options.dest_left_up || options.old_color || options.new_color ||
                    options.number_x || options.number_y) {
                    std::cerr << "Unrecognized options for split" << std::endl;
                    exit(EXIT_UNRECOGNIZED_OPTION);
                }
                BMP image(inputFile);
                std::cout << "Outside ornament " << inputFile << "..." << std::endl;
                image.outsideOrnament(*options.thickness, *options.color);
                image.writeToFile(outputFile);
                break;
            }
        }
    } catch (const UnsupportedBMPHeaderFieldValueError &err) {
        std::cerr << err.what() << std::endl;
        exit(EXIT_BMP_HEADER_FIELD_VALUE_NOT_SUPPORTED);
    } catch (const BMPError &err) {
        std::cerr << err.what() << std::endl;
        exit(EXIT_BMP_ERROR);
    } catch (const std::fstream::failure &err) {
        std::cerr << err.what() << std::endl;
        exit(EXIT_FILE_STREAM_ERROR);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        exit(EXIT_UNRECOGNIZED_ERROR);
    }
    exit(EXIT_SUCCESS);
}
