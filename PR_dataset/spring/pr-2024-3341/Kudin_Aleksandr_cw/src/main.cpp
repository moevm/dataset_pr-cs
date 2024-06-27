#include <iostream>
#include <getopt.h>
#include "ImageProcessor.h"
#include "UtilityFunctions.h"
#include "Options.h"

static struct option keys[] = {
    {"help", no_argument, 0, 'h'},
    {"output", required_argument, 0, 'o'},
    {"input", required_argument, 0, 'i'},
    {"info", no_argument, 0, 'd'},
    {"squared_lines", no_argument, 0, 's'},
    {"rgbfilter", no_argument, 0, 'e'},
    {"rotate", no_argument, 0, 'r'},
    {"contrast", no_argument, 0, 'k'},
    {"alpha", required_argument, 0, 'l'},
    {"beta", required_argument, 0, 'b'},
    {"left_up", required_argument, 0, 'u'},
    {"right_down", required_argument, 0, 'q'},
    {"side_size", required_argument, 0, 'z'},
    {"thickness", required_argument, 0, 't'},
    {"color", required_argument, 0, 'c'},
    {"fill", no_argument, 0, 'f'},
    {"fill_color", required_argument, 0, 'g'},
    {"component_name", required_argument, 0, 'n'},
    {"component_value", required_argument, 0, 'v'},
    {"angle", required_argument, 0, 'a'},
    {0, 0, 0, 0}
};

bool findUnknownKey(int argc, char *argv[]) {
    int keyIndex;
    int opt;
    char** argvCopy = new char*[argc];
    for (int i = 0; i < argc; ++i) {
        size_t len = strlen(argv[i]) + 1;
        argvCopy[i] = new char[len];
        strncpy(argvCopy[i], argv[i], len);
    }
    while (true) {
        opt = getopt_long(argc, argvCopy, "io:h", keys, &keyIndex);
        if (opt == -1) {
            opt = 0;
            break;
        }
        switch (opt) {
            case '?':
                optind = 1;
                return true;
                break;
        }
    }
    optind = 1;
    return false;
}

bool processCommand(BitmapFileHeader& header, BitmapInfoHeader &infoHeader, Rgb** &pixelArray, int argc, char* argv[], std::string &outputName, std::string &inputName) {
    int opt;
    int keyIndex;
    opterr = 0;
    bool validFileName = false;
    bool squaredLines = false;
    bool rgbFilter = false;
    bool rotate = false;
    bool contrast = false;
    bool printInfo = false;
    int count = 0;
    char** argvCopy = new char*[argc];
    for (int i = 0; i < argc; ++i) {
        size_t len = strlen(argv[i]) + 1;
        argvCopy[i] = new char[len];
        strncpy(argvCopy[i], argv[i], len);
    }
    if (argc == 1) outputHelp();
    while (true) {
        opt = getopt_long(argc, argvCopy, "ho:iredsk", keys, &keyIndex);
        if (opt == -1) {
            opt = 0;
            break;
        }
        switch (opt) {
            case 'h':
                outputHelp();
                break;
            case 'o':
                if (ImageProcessor::checkValidName(optarg)) outputName = optarg;
                break;
            case 'i':
                if (ImageProcessor::checkValidName(optarg)) {
                    if (ImageProcessor::readBmp(optarg, header, infoHeader, pixelArray)) validFileName = true;
                    inputName = optarg;
                }
                break;
            case 'd':
                printInfo = true;
                break;
            case 's':
                squaredLines = true;
                count++;
                break;
            case 'e':
                rgbFilter = true;
                count++;
                break;
            case 'r':
                rotate = true;
                count++;
                break;
            case 'k':
                contrast = true;
                count++;
                break;
        }
    }
    if (printInfo) {
        if (validFileName) outputInfo(infoHeader);
        else {
            std::cout << "Error: the input file name is invalid or the input file is corrupted" << std::endl;
            exit(41);
        }
    }
    optind = 1;
    if (count > 1) {
        std::cout << "Error: too many arguments" << std::endl;
        exit(41);
    }
    else {
        if (validFileName) {
            if (squaredLines) ImageProcessor::processSquareWithDiagonalsCommand(infoHeader, pixelArray, argc, argv);
            if (rgbFilter) ImageProcessor::processRGBFilter(infoHeader, pixelArray, argc, argv);
            if (rotate) ImageProcessor::processRotate(infoHeader, pixelArray, argc, argv);
            if (contrast) ImageProcessor::processContrast(infoHeader, pixelArray, argc, argv);
        }
        else if (squaredLines || rgbFilter || rotate || contrast) {
            std::cout << "Invalid input file name" << std::endl;
            exit(41);
        }
    }
    return validFileName;
}

int main(int argc, char* argv[]) {
    BitmapFileHeader header;
    BitmapInfoHeader infoHeader;
    Rgb** pixelArray;
    std::string outputName = "out.bmp";
    std::string inputName = "";

    description();
    if (findUnknownKey(argc, argv)) {
        std::cout << "Error: unknown key provided\n";
        exit(41);
    }

    if (processCommand(header, infoHeader, pixelArray, argc, argv, outputName, inputName)) {
        if (outputName == inputName) {
            std::cout << "Error: the names of the input and output files are the same\n";
            exit(41);
        } else {
            ImageProcessor::writeBmp(outputName, header, infoHeader, pixelArray);
        }
    }
    return 0;
}
