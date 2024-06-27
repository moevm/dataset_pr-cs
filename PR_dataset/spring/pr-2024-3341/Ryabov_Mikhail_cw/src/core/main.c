#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

#include "../headers/main.h"
#include "../headers/utils.h"
#include "../headers/draw.h"

struct option main_keys[] = {
        {"info",         no_argument,       NULL, 'I'},
        {"input",        required_argument, NULL, 'i'},
        {"output",       required_argument, NULL, 'o'},
        {"help",         no_argument,       NULL, 'h'},
        {"square",       no_argument,       NULL, 'S'},
        {"left_up",      required_argument, NULL, 'l'},
        {"side_size",    required_argument, NULL, 's'},
        {"thickness",    required_argument, NULL, 't'},
        {"color",        required_argument, NULL, 'C'},
        {"fill",         no_argument,       NULL, 'f'},
        {"fill_color",   required_argument, NULL, 'c'},
        {"exchange",     no_argument,       NULL, 'e'},
        {"right_down",   required_argument, NULL, 'r'},
        {"exchange_type",required_argument, NULL, 'T'},
        {"freq_color",   no_argument,       NULL, 'F'},
        {"gamma",        no_argument,       NULL, 'G'},
        {"value",        required_argument, NULL, 'V'},
        {NULL,           no_argument,       NULL, 0}
};

int main(const int argc, char* argv[])
{
    if(argc == 1)
        callHelp();
    else{
        varOptions* variables = (varOptions*)malloc(sizeof(varOptions));
        int status = getKeys(argc, argv, variables);

        if(variables != NULL)
            callFunctions(status, variables);
        else
            callError(52);

    }
    return 0;
}

void callFunctions(int status, varOptions* var){
    Rgb** newPixels;
    if(status == IS_SQUARE)
    {
        SquareProperty sp = {var->isFillSquare,
                             var->left,
                             var->up,
                             var->sideSize,
                             var->thickness,
                             var->color,
                             var->fillColor};
        newPixels = drawSquare(var->BMPInfo, var->pixels, sp);
    }
    else if(status == IS_EXCHANGE)
        newPixels = exchangeAreas(var->BMPInfo,
                                  var->typeExchange,
                                  var->left,
                                  var->up,
                                  var->right,
                                  var->down,
                                  var->pixels);

    else if(status == IS_FREQ_COLOR)
        newPixels = findAndReplaceColor(var->BMPInfo,
                                        var->pixels,
                                        var->color,
                                        var->inputImage);
    else if(status == IS_GAMMA)
        newPixels = gammedPixels(var->BMPInfo,
                                 var->pixels,
                                 var->value);
    else
        callError(42);
    writeFile(var->outputImage, var->BMPFile, var->BMPInfo, newPixels);
}

int getKeys(const int argc, char* argv[], varOptions* var)
{
    int optIndex;
    if(var == NULL) return  0;
    opterr =                0;
    int isFreqColorFunc =   0;
    int isExchangeFunc =    0;
    int isTypeExchange =    0;
    int isSquareFunc =      0;
    int isThickness =       0;
    int isRightDown =       0;
    int isSideSize =        0;
    int isCallInfo =        0;
    int isLeftUp =          0;
    int isFillColor =       0;
    int isColor =           0;
    int isFill =            0;
    int isGamma =           0;
    int isValue =           0;
    var->inputImage =    NULL;
    var->outputImage =   NULL;
    var->typeExchange =  NULL;
    var->BMPFile = (BitmapFileHeader*)malloc(sizeof(BitmapFileHeader));
    var->BMPInfo = (BitmapInfoHeader*)malloc(sizeof(BitmapInfoHeader));

    int key = getopt_long(argc, argv, "Ii:o:hSl:s:t:C:fc:er:T:FGV:", main_keys, &optIndex);
    while(key != -1)
    {
        //printf("key - %c\n", key);
        switch (key)
        {
            case 'G':
                isGamma = 1;
                break;
            case 'V':
                isValue = 1;
                strToDouble(optarg, &var->value);
                break;
            case 'I':
                isCallInfo = 1;
                break;
            case 'i':
                var->inputImage = optarg;
                break;
            case 'o':
                var->outputImage = optarg;
                break;
            case 'h':
                callHelp();
                break;
            case 'S':
                isSquareFunc = 1;
                break;
            case 'l':
                isLeftUp = 1;
                parseCoords(optarg, &var->left, &var->up);
                break;
            case 's':
                isSideSize = 1;
                strToNum(optarg, &var->sideSize);
                break;
            case 't':
                isThickness = 1;
                strToNum(optarg, &var->thickness);
                break;
            case 'C':
                isColor = 1;
                strToRGB(optarg, &var->color);
                break;
            case 'f':
                isFill = 1;
                break;
            case 'c':
                isFillColor = 1;
                strToRGB(optarg, &var->fillColor);
                break;
            case 'e':
                isExchangeFunc = 1;
                break;
            case 'r':
                isRightDown = 1;
                parseCoords(optarg, &var->right, &var->down);
                break;
            case 'T':
                isTypeExchange = 1;
                var->typeExchange = optarg;
                break;
            case 'F':
                isFreqColorFunc = 1;
                break;
            case '?':
            default:
                callError(41);
        }
        key = getopt_long(argc, argv, "Ii:o:hSl:s:t:C:fc:er:T:FGV:MN:L:", main_keys, &optIndex);
    }
    if(var->inputImage == NULL)
        var->inputImage = argv[argc - 1];
    if(var->outputImage == NULL)
        var->outputImage = "out.bmp";
    if(!strcmp(var->inputImage, var->outputImage))
        callError(44);

    var->pixels = readFile(var->inputImage, var->BMPFile, var->BMPInfo);

    if(isCallInfo) callInfo(var->inputImage, var->BMPFile, var->BMPInfo);

    if(isSquareFunc + isExchangeFunc + isFreqColorFunc + isGamma != 1) callError(42);

    int sumStatusKeys = 0;
    int sumOtherKeys  = 0;

    if(isExchangeFunc)
    {
        sumStatusKeys = isLeftUp + isRightDown + isTypeExchange;
        sumOtherKeys = isSideSize + isThickness + isColor + isFill + isFillColor;
        if(sumOtherKeys != 0 || sumStatusKeys != 3)
            callError(42);
        else
            return IS_EXCHANGE;
    }

    if(isSquareFunc)
    {
        sumStatusKeys = isLeftUp + isSideSize + isThickness + isColor;
        sumOtherKeys = isRightDown + isTypeExchange;
        if(sumOtherKeys != 0 || sumStatusKeys != 4)
            callError(42);
        if(isFill == 1 && isFillColor == 0)
            callError(43);
        if(isFill == 1 && isFillColor == 1)
            var->isFillSquare = 1;
        else
            var->isFillSquare = 0;
        return IS_SQUARE;
    }
    if(isFreqColorFunc)
    {
        sumStatusKeys = isColor;
        sumOtherKeys = isLeftUp + isRightDown + isSideSize + isThickness + isFillColor + isFill + isTypeExchange;
        if(sumOtherKeys != 0 || sumStatusKeys != 1)
            callError(42);
        return IS_FREQ_COLOR;
    }

    if(isGamma)
    {
        sumStatusKeys = isValue;
        sumOtherKeys = isLeftUp + isRightDown + isSideSize + isThickness + isFillColor + isFill + isTypeExchange + isColor;
        if (sumOtherKeys != 0 || sumStatusKeys != 1)
            callError(42);
        return IS_GAMMA;
    }

    return 0;
}