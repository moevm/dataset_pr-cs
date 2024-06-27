#include "../include/functions.h"

void draw_circle(PICInfo& info, int red, int green, int blue){
    int center_row = info.header.Height/2;
    int center_col = info.header.Width/2;
    int radius = min(info.header.Height/2, info.header.Width/2);

    for(int rw = 0; rw < info.header.Height; ++rw){
        for(int col = 0; col < info.header.Width; ++col){
            int k1 = abs(center_row - rw);
            int k2 = abs(center_col - col);
            if((hypot(k1, k2)) > radius){
                Pixel px = get_pixel(info, rw, col);
                *px.blue = blue;
                *px.green = green;
                *px.red = red;
            }
        }
    }
}

void draw_long_line(PICInfo& info, int thickness, int row, int column, int red, int green, int blue){
    for(int rw = row; rw < row+thickness; ++rw){
        for(int col = column; col < info.header.Width - column; ++col){
            Pixel px = get_pixel(info, rw, col);
            *px.blue = blue;
            *px.green = green;
            *px.red = red;
        }
    }
}

void draw_rectangle(PICInfo& info, int thickness, int row, int column, int red, int green, int blue){
    draw_long_line(info, thickness, row, column, red, green, blue);
    for(int rw = row+thickness; rw < info.header.Height - row; ++rw){
        for(int col = column; col < column+thickness; ++col){
            Pixel px = get_pixel(info, rw, col);
            *px.blue = blue;
            *px.green = green;
            *px.red = red;
        }
        for(int col = info.header.Width - row - thickness; col < info.header.Width - row; ++col){
            Pixel px = get_pixel(info, rw, col);
            *px.blue = blue;
            *px.green = green;
            *px.red = red;
        }
    }
    draw_long_line(info, thickness, info.header.Height - row - thickness, column, red, green, blue);
}

void draw(PICInfo& info, int center_x, int center_y, int thickness, int radius,  int red, int green, int blue, const string& dim){
    int radius_square = (int)pow(radius, 2);
    int outer_radius_square = (int)pow(radius + thickness, 2);

    if (dim == "up" or dim == "down"){
        int start = (dim == "up") ? 0 : info.header.Height - 1;
        int stop = (dim == "up") ? radius + thickness : info.header.Height - radius - thickness;
        int step = (dim == "up") ? 1 : -1;
        for(int rw = start; (dim == "up" && rw <= stop) || (dim == "down" && rw >= stop); rw+=step){
            for(int col = 0; col < info.header.Width; ++col){
                int distance_x = abs(center_x - rw);
                int distance_y = abs(center_y - col);

                bool greater_than_radius = (distance_x * distance_x) + (distance_y * distance_y) >= radius_square;
                bool less_than_outer_radius = (distance_x * distance_x) + (distance_y * distance_y) < outer_radius_square;
                if (greater_than_radius && less_than_outer_radius){
                    Pixel px = get_pixel(info, rw, col);
                    *px.blue = blue;
                    *px.green = green;
                    *px.red = red;
                }
            }
        }
    }
    if (dim == "right" or dim == "left"){
        int start = (dim == "left") ? 0 : info.header.Width - 1;
        int stop = (dim == "left") ? radius + thickness : info.header.Width - radius - thickness;
        int step = (dim == "left") ? 1 : -1;
        for(int rw = 0; rw < info.header.Height; ++rw){
            for(int col = start; (dim == "left" && col <= stop) || (dim == "right" && col >= stop); col+=step){
                int distance_x = abs(center_x - rw);
                int distance_y = abs(center_y - col);

                bool greater_than_radius = (distance_x * distance_x) + (distance_y * distance_y) >= radius_square;
                bool less_than_outer_radius = (distance_x * distance_x) + (distance_y * distance_y) < outer_radius_square;
                if (greater_than_radius && less_than_outer_radius){
                    Pixel px = get_pixel(info, rw, col);
                    *px.blue = blue;
                    *px.green = green;
                    *px.red = red;
                }
            }
        }
    }
}

void draw_semicircle(PICInfo& info, int thickness, int count, int red, int green, int blue){
    double temp = ((double)info.header.Width / ((double)count * 2)) - ((double)thickness / 2);
    int horizontal_radius;
    if((info.header.Width % (count*2) != 0) or (thickness % 2 != 0)){
        horizontal_radius = (int)ceil(temp);
    } else {
        horizontal_radius = (int)temp;
    }
    int step = 2 * horizontal_radius + thickness - 1;
    int start = (int)ceil((double)thickness / 2) + horizontal_radius;

    //для ситуаций типа s 255 255 255 4 10 (500x210) при радиусе 23 - останется место, при 24 - поместятся не все
    if((start + ((count - 1) * step) + horizontal_radius + thickness) < info.header.Width){
        horizontal_radius += 1;
        step = 2 * horizontal_radius + thickness - 1;
        start = (int)ceil((double)thickness / 2) + horizontal_radius;
    }

    int column = start;
    for (int i = 0; i < count; ++i) {
        draw(info, 0, column, thickness, horizontal_radius, red, green, blue, "up");
        draw(info, info.header.Height-1, column, thickness, horizontal_radius, red, green, blue, "down");
        column += step;
    }


    double temp_vertical = ((double)info.header.Height / ((double)count * 2)) - ((double)thickness / 2);
    int vertical_radius;
    if((info.header.Height % (count*2) != 0) or (thickness % 2 != 0)){
        vertical_radius = (int)ceil(temp_vertical);
    } else {
        vertical_radius = (int)temp_vertical;
    }
    int step_vertical = 2 * vertical_radius + thickness - 1;
    int start_vertical = (int)ceil((double)thickness / 2) + vertical_radius;

    if((start_vertical + ((count - 1) * step_vertical) + vertical_radius + thickness) < info.header.Height){
        vertical_radius += 1;
        step_vertical = 2 * vertical_radius + thickness - 1;
        start_vertical = (int)ceil((double)thickness / 2) + vertical_radius;
    }

    int row = start_vertical;
    for (int i = 0; i < count; ++i) {
        draw(info, row, 0, thickness, vertical_radius, red, green, blue, "left");
        draw(info, row, info.header.Width-1, thickness, vertical_radius, red, green, blue, "right");
        row += step_vertical;
    }
}


void ornament(PICInfo& info, string& type, int* colors, int thickness, int count) {
    int red = colors[0];
    int green = colors[1];
    int blue = colors[2];

    if (type == "rectangle"){
        int row = 0, column = 0;
        for (int i = 0; i < count; ++i) {
            draw_rectangle(info, thickness, row, column, red, green, blue);
            row += 2*thickness;
            column += 2*thickness;
        }
    }else if (type == "circle"){
        draw_circle(info, red, green, blue);
    }else if (type == "semicircles"){
        draw_semicircle(info, thickness, count, red, green, blue);
    }else{
        cerr << "Incorrect type of ornament" << endl;
        exit(40);
    }

}
