#include "../include/checkErr.h"

const char* inputError = "Error: Invalid input<3"; //41
const char* outputError = "Error: Invalid output<3"; //42
const char* multipyFuncError = "Error: More than one function were called<3"; //43
const char* argsError = "Error: Invalid args<3"; //44
const char* colorError = "Error: Invalid color<3"; //45
const char* typeError = "Error: Invalid type<3"; //46
const char* thicknessError = "Error: Invalid thickness<3"; //47
const char* fileTypeError = "Error: Invalid type of file<3"; //48

void throwError(const char* message, int error) {
    printf("%s\n", message);
    exit(error);
}

void checkExtraArguments(Parametrs* par){
    int flag = 0;
    if(par->square == true || par->side_size != -1 || par->thickness != -1 || par->fill != false || par->fill_color.r != -1){
        flag = 1;
    }
    if(par->exchange == true || par->right != -1 || par->down != -1 || par->exchange_type != -1){
        if(flag != 0){
            throwError(argsError, 44);
        }
        flag = 2;
    }
    if(par->freq_color == true){
        if(flag != 0){
            throwError(argsError, 44);
        }
        flag = 3;
    }
    if(par->color.r != -1){
        if(flag == 2){
            throwError(argsError, 44);
        }
    }
    if(par->left != -1){
        if(flag == 3){
            throwError(argsError, 44);
        }
    }
}

void checkColor(RGB color) {
    if (color.r > 255 || color.g > 255 || color.b > 255){
        throwError(colorError, 45);
    }
    if (color.r < 0 || color.g < 0 || color.b < 0){
        throwError(colorError, 45);
    }
}

void checkFreq(Png* image, Parametrs* par){
    checkColor(par->color);
}

void checkSquare(Png* image, Parametrs* par){
    if(par->left == -1 || par->up == -1 || par->side_size == -1 || par->thickness == -1 || par->color.r == -1){
        throwError(argsError, 44);
    }
    if(par->thickness <= 0){
        throwError(thicknessError, 47);
    }
    checkColor(par->color);
    if(par->fill){
        checkColor(par->fill_color);
    }
}

void checkExchange(Png* image, Parametrs* par){
    if(par->left == -1 || par->up == -1 || par->right == -1 || par->down == -1 || par->exchange_type == -1){
        throwError(argsError, 44);
    }
    if(par->left < 0){
        par->left = 0;
    }
    if(par->up < 0){
        par->up = 0;
    }
    if(par->right < par->left){
        throwError(argsError, 44);
    }
    if(par->down < par->up){
        throwError(argsError, 44);
    }
    if(par->exchange_type < 0 || par->exchange_type > 2){
        throwError(typeError, 46);
    }
}

void checkContrast(Png* image, Parametrs* par){
    if(par->alpha == -1 || par->beta == -1){
        throwError(argsError, 44);
    }
    // if(par->alpha < 0 || par->alpha > 1){
    //     par->alpha = 1.0;
    // }
}