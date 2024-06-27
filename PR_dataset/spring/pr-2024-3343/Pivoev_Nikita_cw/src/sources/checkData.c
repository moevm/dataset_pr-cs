#include "../include/checkData.h"

const char* fileTypeError = "Error: Invalid file type!";
const char* inputError = "Error: input is missing!";
const char* outputIsImputError = "Error: Output matches imput!";

const char* colorError = "Error: Invalid color!";
const char* patternError = "Error: Invalid pattern!";
const char* thicknessError = "Error: Invalid thickness!";
const char* countError = "Error: Invalid pattern count!";

const char* argsError = "Error: Missing required arguments or extra flags given!";
const char* taskError = "Error: More than one task provided!";

void raiseError(const char* message, int error) {
    printf("%s\n", message);
    exit(error);
}

void checkExtraArgs(OptParams* opt) {
    int task = 0;
    
    if (opt->copy == true || opt->copy_left != -1 || opt->copy_up != -1 || opt->copy_right != -1 || opt->copy_down != -1 || opt->copy_dest_left != -1 || opt->copy_dest_up != -1)
        task = 1;

    if (opt->color_replace == true || opt->old_color.r != -1 || opt->new_color.r != -1) {
        if (task != 0)
            raiseError(argsError, 43);
        task = 2;
    }

    if (opt->ornament == true || opt->ornament_pattern != -1 || opt->ornament_count != -1) {
        if (task != 0)
            raiseError(argsError, 43);
        task = 3;
    }

    if (opt->filled_rects == true || opt->rects_border_color.r != -1) {
        if (task != 0)
            raiseError(argsError, 43);
        task = 4;
    }
    
    if (opt->outside_ornament == true) {
        if (task != 0)
            raiseError(argsError, 43);
        task = 5;
    }

    if (opt->color.r != -1 || opt->thickness != -1) {
        if (task == 0 || task == 1 || task == 2)
            raiseError(argsError, 43);
    }
}

void checkCopy(Png* image, OptParams* opt) {
    if (opt->copy_left == -1 || opt->copy_up == -1 || opt->copy_right == -1 || opt->copy_down == -1 || opt->copy_dest_left == -1 || opt->copy_dest_up == -1)
        raiseError(argsError, 43);
        
    if (opt->copy_left < 0)
        opt->copy_left = 0;

    if (opt->copy_left > image->width - 1)
        opt->copy_left = image->width - 1;
    
    if (opt->copy_up < 0)
        opt->copy_up = 0;
    
    if (opt->copy_up > image->height - 1)
        opt->copy_up = image->height - 1;

    if (opt->copy_right < 0)
        opt->copy_right = 0;

    if (opt->copy_right > image->width - 1)
        opt->copy_right = image->width - 1;
    
    if (opt->copy_down < 0)
        opt->copy_down = 0;
    
    if (opt->copy_down > image->height - 1)
        opt->copy_down = image->height - 1;
    
    if (opt->copy_dest_left < 0)
        opt->copy_dest_left = 0;

    if (opt->copy_dest_left > image->width - 1)
        opt->copy_dest_left = image->width - 1;

    if (opt->copy_dest_up < 0)
        opt->copy_dest_up = 0;

    if (opt->copy_dest_up > image->height - 1)
        opt->copy_dest_up = image->height - 1;
    
    if (opt->copy_right < opt->copy_left || opt->copy_down < opt->copy_up) {
        int x = opt->copy_right;
        int y = opt->copy_down;
        opt->copy_right = opt->copy_left;
        opt->copy_down = opt->copy_up;
        opt->copy_left = x;
        opt->copy_up = y;
    }
}

void checkColor(RGB color) {
    if (color.r < 0 || color.g < 0 || color.b < 0)
        raiseError(colorError, 43);
    if (color.r > 255 || color.g > 255 || color.b > 255)
        raiseError(colorError, 43);
}

void checkReplace(Png* image, OptParams* opt) {
    checkColor(opt->old_color);
    checkColor(opt->new_color);
}

void checkOrnament(Png* image, OptParams* opt) {
    if (!(opt->ornament_pattern == 0 || opt->ornament_pattern == 1 || opt->ornament_pattern == 2))
        raiseError(patternError, 43);
    checkColor(opt->color);
    if (opt->thickness <= 0)
        raiseError(thicknessError, 43);
    if (opt->ornament_count <= 0)
        raiseError(countError, 43);
}

void checkRects(Png* image, OptParams* opt) {
    checkColor(opt->color);
    checkColor(opt->rects_border_color);
    if (opt->thickness <= 0)
        raiseError(thicknessError, 43);
}

void checkOutside(Png* image, OptParams* opt) {
    checkColor(opt->color);
    if (opt->thickness <= 0)
        raiseError(thicknessError, 43);
}