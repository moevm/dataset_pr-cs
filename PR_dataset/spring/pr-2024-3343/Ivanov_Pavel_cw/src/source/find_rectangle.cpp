#include "../include/functions.h"

int* size_of_rectangle = new int[2];

void draw_frame(int rw, int col, int height, int length, int thickness, PICInfo& info, int* border_color){
    int x0 = rw - thickness;
    int y0 = col - thickness;
    int x1 = rw + height + thickness;
    int y1 = col + length + thickness;
    int bord_red = border_color[0];
    int bord_green = border_color[1];
    int bord_blue = border_color[2];

    for(int x = x0; x < x1; ++x){
        for(int y = y0; y < y1; ++y){
            if(x < 0 or y < 0 or x >= info.header.Height or y >= info.header.Width){
                continue;
            }
            if((x < rw or (x >= rw + height)) or (y < col or (y >= col + length))){
                Pixel px = get_pixel(info, x, y);
                *px.red = bord_red;
                *px.green = bord_green;
                *px.blue = bord_blue;
            }
        }
    }
}

bool check_inside(int row_start, int column_start, int row_stop, int column_stop, int red, int green, int blue, PICInfo& info){
    for (int row = row_start; row <= row_stop; ++row){
        for (int column = column_start; column <= column_stop; ++column) {
            Pixel px = get_pixel(info, row, column);
            if(*px.blue != blue or *px.green != green or *px.red != red) {
                return false;
            }
        }
    }
    return true;
}

bool check_rectangle(PICInfo& info, int row, int column, int red, int green, int blue){
    if(row == info.header.Height - 1 or column == info.header.Width - 1){
        return false;
    }
    if(row != 0) {
        Pixel top_px = get_pixel(info, row - 1, column);
        if(*top_px.red == red and *top_px.green == green and *top_px.blue == blue){
            return false;
        }
    }
    Pixel bottom_px{};
    Pixel next_frame_px{};
    Pixel diagonal_top_px{};
    int length = 0;
    int height = 0;
    int temp_row = row;
    int temp_column = column;

    //обход верхней стороны
    do{
        if(temp_column == info.header.Width - 1){
            length++;
            break;
        }
        bottom_px = get_pixel(info, row + 1, temp_column);
        next_frame_px = get_pixel(info, row, temp_column + 1);
        if(row != 0){
            diagonal_top_px = get_pixel(info, row - 1, temp_column + 1);
            if (*diagonal_top_px.red == red and *diagonal_top_px.green == green and *diagonal_top_px.blue == blue) {
                return false;
            }
        }
        if(*bottom_px.red != red or *bottom_px.green != green or *bottom_px.blue != blue){
            return false;
        }
        length++;
        temp_column++;
    }while(*next_frame_px.blue == blue and *next_frame_px.green == green and *next_frame_px.red == red);
    if(length <= 1){
        return false;
    }
    //левый диагональный пиксель
    if(row != 0 and column != 0){
        Pixel left_diagonal = get_pixel(info, row - 1, column - 1);
        if(*left_diagonal.red == red and *left_diagonal.green == green and *left_diagonal.blue == blue){
            return false;
        }
    }

    //обход левой стороны
    if(column != 0) {
        Pixel top_px = get_pixel(info, row, column - 1);
        if(*top_px.red == red and *top_px.green == green and *top_px.blue == blue){
            return false;
        }
    }
    do{
        if(temp_row == info.header.Height - 1){
            height++;
            break;
        }
        bottom_px = get_pixel(info, temp_row, column + 1);
        next_frame_px = get_pixel(info, temp_row + 1, column);
        if(column != 0) {
            diagonal_top_px = get_pixel(info, temp_row + 1, column - 1);
            if(*diagonal_top_px.red == red and *diagonal_top_px.green == green and *diagonal_top_px.blue == blue){
                return false;
            }
        }
        if(*bottom_px.red != red or *bottom_px.green != green or *bottom_px.blue != blue){
            return false;
        }
        height++;
        temp_row++;
    }while(*next_frame_px.red == red and *next_frame_px.green == green and *next_frame_px.blue == blue);
    if(height <= 1){
        return false;
    }

    //обход нижней стороны
    temp_row = row + height - 1;
    temp_column = column;
    int down_length = 0;
    Pixel top_px{};
    Pixel diagonal_down_px{};

    if(temp_row != info.header.Height - 1){
        bottom_px = get_pixel(info, temp_row + 1, column);
        if (*bottom_px.red == red and *bottom_px.green == green and *bottom_px.blue == blue) {
            return false;
        }
    }
    do{
        if(temp_column == info.header.Width - 1){
            down_length++;
            break;
        }
        top_px = get_pixel(info, temp_row - 1, temp_column);
        next_frame_px = get_pixel(info, temp_row, temp_column + 1);
        if(temp_row != info.header.Height - 1){
            diagonal_down_px = get_pixel(info, temp_row + 1, temp_column + 1);
            if (*diagonal_down_px.red == red and *diagonal_down_px.green == green and *diagonal_down_px.blue == blue) {
                return false;
            }
        }
        if(*top_px.red != red or *top_px.green != green or *top_px.blue != blue){
            return false;
        }
        down_length++;
        temp_column++;
    }while(*next_frame_px.blue == blue and *next_frame_px.green == green and *next_frame_px.red == red);
    if(down_length != length){
        return false;
    }

    //обход правой стороны
    temp_row = row;
    temp_column = column + length - 1;
    int right_height = 0;

    if(temp_column != info.header.Width - 1){
        top_px = get_pixel(info, row, temp_column + 1);
        if (*top_px.red == red and *top_px.green == green and *top_px.blue == blue){
            return false;
        }
    }
    do{
        if(temp_row == info.header.Height - 1){
            right_height++;
            break;
        }
        bottom_px = get_pixel(info, temp_row, temp_column - 1);
        next_frame_px = get_pixel(info, temp_row + 1, temp_column);
        if(temp_column != info.header.Width - 1) {
            diagonal_top_px = get_pixel(info, temp_row + 1, temp_column + 1);
            if (*diagonal_top_px.red == red and *diagonal_top_px.green == green and *diagonal_top_px.blue == blue) {
                return false;
            }
        }
        if(*bottom_px.red != red or *bottom_px.green != green or *bottom_px.blue != blue){
            return false;
        }
        right_height++;
        temp_row++;
    }while(*next_frame_px.red == red and *next_frame_px.green == green and *next_frame_px.blue == blue);
    if(right_height != height){
        return false;
    }

    //проверка пикселей внутри прямоугольника
    if(!check_inside(row, column, row + height - 1, column + length - 1, red, green, blue, info)){
        return false;
    }

    size_of_rectangle[0] = height;
    size_of_rectangle[1] = length;

    return true;
}

void find_rectangle(PICInfo& info, int* rect_color, int thickness, int* border_color){
    int rect_red = rect_color[0];
    int rect_green = rect_color[1];
    int rect_blue = rect_color[2];
    for(int rw = 0; rw < info.header.Height; ++rw){
        for(int col = 0; col < info.header.Width; ++col){
            Pixel px = get_pixel(info, rw, col);
            if(*px.blue == rect_blue and *px.green == rect_green and *px.red == rect_red){
                if(check_rectangle(info, rw, col, rect_red, rect_green, rect_blue)){
                    draw_frame(rw, col, size_of_rectangle[0], size_of_rectangle[1], thickness, info, border_color);
                }
            }
        }
    }
}