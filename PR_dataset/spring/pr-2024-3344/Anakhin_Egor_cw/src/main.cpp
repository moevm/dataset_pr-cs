#include <unordered_map>
#include <string>

#include "input_functions/check_args_amount.h"
#include "input_functions/process_flags.h"
#include "input_functions/validate_args.h"
#include "print_functions.h"
#include "consts.h"
#include "images_functions/getFileInfo.h"
#include "images_functions/color_replace.h"
#include "images_functions/imageStructs.h"
#include "images_functions/new_file.h"
#include "images_functions/copy_part.h"
#include "images_functions/mirror.h"
#include "images_functions/split.h"
#include "input_functions/flag_utils.h"
#include "images_functions/shift.h"
// #include "check_args_amount.h"


int main(int argc, char** argv) {

    std::vector<std::vector<Pixel>> bitArr;
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::string functionName;

    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printHelp();
        return 0;
    }
    if (argc < 2) {
        std::cout << "Please enter flags\n";
        std::cout << USE_HELP;
        return 41;
    }

    std::unordered_map<std::string, std::string> argsMap = getParams(argc, argv);
    functionName = findFunctionName(argc, argv);
    std::string functionToCall = findFunctionToRun(functionName, argsMap);

    if (functionToCall == "incorrect") {
        return 41;
    }
    if (!validateArgs(functionToCall, argsMap)) {
        std::cout << "Please use flags correctly\n";
        return 41;
    }

    try {
        bitArr = readBMP(argsMap[INPUT], header, infoHeader);
    } catch(const std::runtime_error& e) {
        std::cout << e.what();
        return 0;
    }

    try {
        if (functionToCall == INFO) {
            printFileInfo(infoHeader);
            return 0;
        }

        if (functionToCall == COLOR_REPLACE) {
            changeColors(infoHeader, bitArr, argsMap);
        }

        if (functionToCall == COPY) {
            copyPartOfImage(infoHeader, bitArr, argsMap);
        }

        if (functionToCall == MIRROR) {
            mirror(infoHeader, bitArr, argsMap);       
        }

        if (functionToCall == SPLIT) {
            split(infoHeader, bitArr, argsMap);
        }

        if (functionToCall == "shift") {
            shift(infoHeader, bitArr, argsMap);
        }

        writeBMP(argsMap["output"], header, infoHeader, bitArr);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "Program didn't finished successfully\n";
        exit(41);
    }

    return 0;
}
