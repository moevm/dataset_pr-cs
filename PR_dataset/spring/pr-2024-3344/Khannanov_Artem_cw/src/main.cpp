#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "BMP.hpp"
#include "functions.hpp"
#include "check_functions.hpp"
#include "secondary_functions.hpp"
#include "inputFunctions.hpp"


using namespace std;
//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


int main (int argc, char* argv[]) {
    int isCorrectFile, valuesCount, isCheckCorrect;
    string InputFileName, OutputFileName;
    vector <pair<string, string>> optDict;
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;

    // Считывание данных, первичная проверка ввода
    valuesCount = inputFunction(&optDict, argc, argv);
    if (valuesCount == 0) {
        cerr << "Введите данные для работы программы\n";
        return 40;
    }
    if (optDict[0].first == "h") {
        printHelp();
        return 0;
    }
    // ----------------------

    // Обработка входного файла
    if (argc - 1 > valuesCount) {
        InputFileName = argv[argc - 1];
    } else {
        if (findInputFile(optDict, &InputFileName) == 0) {
            cerr << "Введите название входного файла\n";
            return 40;
        }
    }
    isCorrectFile = checkFileName(InputFileName);
    if (isCorrectFile == 0) {
        cerr << "Введено некорректное имя входного файла\n";
        return 40;
    }
    // -----------------------

    // Обработка выходного файла
    OutputFileName = "out.bmp";
    findOutputFile(optDict, &OutputFileName);
    isCorrectFile = checkFileName(OutputFileName);
    if (isCorrectFile == 0) {
        cerr << "Введено некорректное имя выходного файла\n";
        return 40;
    }
    // -----------------------

    // Проверка входного и выходного файлов на равенство
    if (OutputFileName == InputFileName) {
        cerr << "Входной и выходной файлы должны иметь разные названия\n";
        return 41;
    }
    // -----------------------

    // Создание массива пикселей
    Rgb** arr = readBMP(InputFileName, &bmfh, &bmif);
    if (arr == NULL) return 42;
    // ----------------------

    if (optDict[0].first == "I") {
        print_info_header(bmif);
        cout << "\n";
        print_file_header(bmfh);
        return 0;
    }

    isCheckCorrect = 1;

    bool isComplete = false;
    bool isA = false;
    for (size_t i = 0; i < optDict.size(); i++) {
        if (optDict[i].first == "m") {
            isCheckCorrect = checkMirrorValues(optDict, arr, bmif.height, bmif.width);
            isComplete = true;
            break;

        } else if (optDict[i].first == "c") {
            isCheckCorrect = checkCopyValues(optDict, arr, bmif.height, bmif.width);
            isComplete = true;
            break;

        } else if (optDict[i].first == "r") {
            isCheckCorrect = checkReplaceValues(optDict, arr, bmif.height, bmif.width);
            isComplete = true;
            break;

        } else if (optDict[i].first == "f") {
            isCheckCorrect = checkFilterValues(optDict, arr, bmif.height, bmif.width);
            isComplete = true;
            break;

        } else if (optDict[i].first == "z") {
            isCheckCorrect == checkCircleValues(optDict, arr, bmif.height, bmif.width);
            isComplete = true;
            break;
        } else if (optDict[i].first == "x") {
            isCheckCorrect == checkLineValues(optDict, arr, bmif.height, bmif.width);
            isComplete = true;
            break;
        } else if (optDict[i].first == "p") {
            isCheckCorrect = checkAValues(optDict, arr, bmif, bmfh, OutputFileName);
            isComplete = true;
            isA = true;
            break;
        }
    }

    if (isComplete == false) {
        cerr << "Введены неверные данные\n";
        return 49;
    }

    if (isCheckCorrect == 0) return 43;
    
    if (isA == true && isCheckCorrect != 2) return 0;
    
    writeBMP(OutputFileName, arr, bmif.height, bmif.width, bmfh, bmif);

    return 0;
}
