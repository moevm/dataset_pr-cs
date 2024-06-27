#include "actions.h"
#include "math.h"


Rgb **def_task(Rgb **arr, float alpha, int beta, int H, int W){
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            int R = floor(alpha * arr[i][j].r + beta);
            int G = floor(alpha * arr[i][j].g + beta);
            int B = floor(alpha * arr[i][j].b + beta);
            if(R > 255){
                R = 255;
            }
            if(G>255){
                G = 255;
            }
            if(B > 255){
                B = 255;
            }
            //printf("%f %d %f %f - %f\n",alpha, beta, (alpha * arr[i][j].r), (alpha * arr[i][j].r)+beta, floor(alpha * arr[i][j].r + beta));
            arr[i][j].r = R;
            arr[i][j].g = G;
            arr[i][j].b = B;

        }
    }
    return arr;
}


Rgb **change_red_chanel(Rgb **arr, int H, int W, int r){
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            arr[i][j].r = r;
        }
    }
    return arr;
}

Rgb **change_green_chanel(Rgb **arr, int H, int W, int g){
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            arr[i][j].g = g;
        }
    }
    return arr;
}

Rgb **change_blue_chanel(Rgb **arr, int H, int W, int b){
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            arr[i][j].b = b;
        }
    }
    return arr;
}


void swap_int(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
} 


void draw_circle(Rgb **arr, int H, int W, int dot_x, int dot_y, int thickness, int* color) {
    
    if (dot_x < 0 || dot_x > W || dot_y < 0 || dot_y > H || thickness <= 0) {
        // fprintf(stderr, "Coords are not correct\n");
        // exit(41);
        return;
    }

    int radius = (thickness % 2 == 0) ? thickness / 2 : (thickness - 1) / 2;

    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                if (dot_y + y >= 0 && dot_y + y < H && dot_x + x >= 0 && dot_x + x < W) {
                    arr[dot_y + y][dot_x + x].r = *(color);
                    arr[dot_y + y][dot_x + x].g = *(color + 1);
                    arr[dot_y + y][dot_x + x].b = *(color + 2);
                }
            }
        }
    }
}




void draw_line(Rgb **arr, int H, int W, int x0, int y0, int x1, int y1, int thickness, int *color, int flag){
    y0=H-y0;
    y1=H-y1;
    if (x0 < 0 || y0 > H || x1 < 0 || y1 > H || thickness <= 0){
        fprintf(stderr, "Coords are not correct\n");
        //printf("\n%d %d %d %d %d %d\n", x0, y0, x1, y1, H, W);
        exit(41);
        return;
    }
    //printf("Y\n");

    // if(x0>W){
    //     x0=W;
    // }
    // if(y0>H){
    //     y0=H;
    // }
    
    //printf("%d %d %d %d H-%d W-%d\n", x0, x1, y0, y1, H, W);
    if (x0 > W || y0 > H){
        return;
    }
    // вертикальная линия
    if(x1>W){
        x1=W;
    }
    if(y1>H){
        y1=H;
    }

    int side = 1;
    // if(thickness % 2 != 0){
    //     thickness = thickness-1;
    // }
    // if (thickness == 0){
    //     thickness = 2;
    // }
    if(y0 < 0){
        y0=0;
    }
    // if(y1 < 0){
    //     y1 = 0;
    // }
    //printf("%d %d %d %d H-%d W-%d\n", x0, x1, y0, y1, H, W);
    if (x0 == x1){
        if (y0 > y1){
            swap_int(&y0, &y1);
        }
        for (int y = y0; y <= y1; y++){
            draw_circle(arr, H, W, x0, y, thickness, color);
        }
        // горизонтальная линия
    }
    else if (y0 == y1){
        if (x0 > x1){
            swap_int(&x0, &x1);
        }
        for (int x = x0; x <= x1; x++){
            draw_circle(arr, H, W, x, y0, thickness, color);
        }
    }
}

void fill_sq(Rgb **arr, int start_x, int start_y, int lenght_line, int *colors, int H, int W){
    //printf("%d %d", start_y, start_y-lenght_line);
    for (int i = start_x; i < start_x+lenght_line; i++){
        for (int j = start_y; j > start_y-lenght_line; j--){
            if(i >= 0 && j < H && i < W && j>=0){
                arr[j][i].r = colors[0];
                arr[j][i].g = colors[1];
                arr[j][i].b = colors[2];
            }
        }
    }
}


void draw_diags(Rgb **arr, int H, int W, int start_x, int start_y, int end_x, int end_y, int thickness, int *color){

    start_y = H-start_y;
    end_y = H-end_y;

    if(start_y>H){
        return;
    }

    // if(end_x > W){
    //     end_x = W;
    // }
    // if(end_y > H){
    //     end_y = H;
    // }

    int dx = abs(end_x - start_x);
    int dy = abs(end_y - start_y);
    int sx = start_x < end_x ? 1 : -1;
    int sy = start_y < end_y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    int x = start_x;
    int y = start_y;
    //printf("\n%d %d\n", start_y, end_y);
    
    //somwhere here maybe i should change
    while (x != end_x || y != end_y){
        if (x >= 0 && x < W && y >= 0 && y < H){
            // arr[y][x].r = color[0];
            // arr[y][x].g = color[1];
            // arr[y][x].b = color[2];

            draw_circle(arr, H, W, x, y, thickness, color);
        
        }

        e2 = err;
        if (e2 > -dx){
            err -= dy;
            x += sx;
        }
        if (e2 < dy){
            err += dx;
            y += sy;
        }
    }
}

void draw_sq(Rgb **arr, int start_x, int start_y, int lenght_line, int H, int W, int thickness, int *color, int fill, int *fill_color, int thick){
    if(fill){
        fill_sq(arr, start_x, H-start_y, lenght_line, fill_color, H, W);
    }
    draw_line(arr, H, W, start_x, start_y, start_x + lenght_line, start_y, thickness, color, 0);
    draw_line(arr, H, W, start_x, start_y, start_x, start_y + lenght_line, thickness, color, 1);

    draw_line(arr, H, W, start_x, start_y + lenght_line, start_x + lenght_line, start_y + lenght_line, thickness, color, 1);
    draw_line(arr, H, W, start_x + lenght_line, start_y, start_x + lenght_line, start_y + lenght_line, thickness, color, 0);

    draw_diags(arr, H, W, start_x, start_y, start_x+lenght_line, start_y+lenght_line, thick, color);
    draw_diags(arr, H, W, start_x+lenght_line, start_y, start_x, start_y+lenght_line, thick, color);

}


Rgb** turned_copy(Rgb **arr, int H, int W, int start_x, int start_y, int end_x, int end_y, int angle){
    int x = 0;
    int y = 0;

    int Verticals = 0; // how much lines
    int Horizontal = 0; // how long 1 line in horizontal

    if(angle == 90){
        Verticals = end_x-start_x+3; // turned matrix reading at right-up position to right-down pos
        Horizontal = end_y-start_y+3;
    }else if (angle == 180){
        Verticals = end_y-start_y+3; // turned M reading at right-down pos to left-down pos
        Horizontal = end_x-start_x+3;
    }else if (angle = 270){
        Verticals = end_x-start_x+3;
        Horizontal = end_y-start_y+3;
    }
    

    Rgb **arr_t = (Rgb **)malloc(Verticals* sizeof(Rgb *)); // make turned matrix
    for (int i = 0; i < Verticals; i++) {
        arr_t[i] = (Rgb *)malloc(Horizontal * sizeof(Rgb));
    }
    //printf("%d %d %d %d,  H=%d W=%d\n",  start_x, start_y, end_x, end_y, H, W);

    start_y = H-start_y; // translate y chords, because it's inverted
    end_y = H-end_y;
    //printf("%d %d %d %d  Vert=%d Horiz=%d\n",  start_x, start_y, end_x, end_y, Verticals, Horizontal);
    //exit(41);

    switch (angle){
    case 90:               //turned matrix reading at right-up position to right-down pos

        for(int i=end_x-1; i>=start_x-1;i--){
            for(int j=start_y-1;j>=end_y-1;j--){
                if(j < H && j>=0 && x < W && x >= 0){
                    arr_t[y][x] = arr[j][i];
                }
                //printf("%d %d, j=%d, i=%d, x=%d, y=%d, H=%d, W=%d\n", arr_t[y][x].r, arr[j][i].r, j, i, x, y, H, W);
                x=x+1;
            }
            y=y+1;
            x=0;
        }

        break;
    case 180:              // turned matrix reading at right-down to left-down pos
        for(int i=end_x-1; i>=start_x-1;i--){ // -1 fish test
            for(int j=end_y;j<=start_y;j++){
                //printf("%d %d, j=%d, i=%d, x=%d, y=%d, H=%d, W=%d\n", arr[j][i].r, arr[j][i].r, j, i, x, y, H, W);
                arr_t[y][x] = arr[j][i];
                y=y+1;
            }
            x=x+1;
            y=0;
        }
        break;
    case 270: // left-down to left-up

        for(int i=start_x; i<=end_x;i++){
            for(int j=end_y;j<=start_y;j++){
                arr_t[y][x] = arr[j][i];
                x=x+1;
            }
            y=y+1;
            x=0;
        }
        //printf("End");
        break;

    default:
        break;
    }
    return arr_t;
}

void replace_part(Rgb **arr, Rgb **arr_t, int start_x, int start_y, int end_x, int end_y, int H, int W){
    int x = 0;
    int y = 0;// ДОБАВИТЬ ОГРАНИЧЕНИЯ ПО end_y


    //printf("\nx1-%d y1-%d x2-%d y2-%d  H=%d W=%d   - delta = %d\n\n",  start_x+x, H-start_y-y-1, end_x-x+1, H-end_y+y, H, W, x);

    if(end_y >= H){
        end_y = H;
    }
    if(start_y < 0){
        start_y = 0;
    }
    // if(end_x > W){
    //     end_x = W;
    // }
    //printf("\nx1-%d y1-%d x2-%d y2-%d  H=%d W=%d   - deltass = %d\n\n",  start_x+x, start_y, end_x-x+1, H-end_y+y, H, W, x);
    //return;
        for(int i=start_x; i<=end_x+1;i++){
            for(int j=H-start_y-1; j>=H-end_y; j--){
                if(i >= 0 && j < H && i < W && j>=0){
                    //printf("%d %d    %d %d\n", y, x, j, i);
                    arr[j][i] = arr_t[y][x];
                    //printf("D\n");
                }
                
                // arr[j][i].r = x;
                // arr[j][i].g = y;
                // arr[j][i].b = 0;
                y = y+1;
            }
            
            x = x+1;
            //printf("%d %d \n", x, y);
            y = 0;
        }
        //printf("\nx1-%d y1-%d x2-%d y2-%d  H=%d W=%d   - delta = %d\n\n",  start_x, H-start_y-1, end_x+1, H-end_y, H, W, x);

}

void turn(Rgb **arr, int H, int W, int start_x, int start_y, int end_x, int end_y, int angle){ //arr[y][x], where x < W, x>=0, y >= 0, y < H

    //printf("%d %d %d %d  H=%d W=%d   - arr = %d",  start_x, start_y, end_x, end_y, H, W, arr[0][680].r);
    // arr[426][0].r = 0;
    // arr[426][0].g = 0;
    // arr[426][0].b = 255;
    
    // exit(41);

    // H = 471;
    // W = 500;

    if(start_x > end_x){
        swap_int(&start_x, &end_x);
        swap_int(&start_y, &end_y);
        //printf("%d %d %d %d\n", start_x, start_y, end_x, end_y);
        if(start_y > end_y){
            fprintf(stderr, "Wrong dots\n");
            exit(41);
        }
    }
    if(start_y > end_y){
        swap_int(&start_x, &end_x);
        swap_int(&start_y, &end_y);
        if(start_x > end_x){
            fprintf(stderr, "Wrong dots\n");
            exit(41);

        }
    }
                        // swap coords

    Rgb **arr_t = turned_copy(arr, H, W, start_x, start_y, end_x, end_y, angle);
    int sq_flag = (end_x-start_x)-(end_y-start_y);

    int lenght_x = end_x-start_x+1; // +1 becouse including end's dot
    int lenght_y = end_y-start_y+1;



    switch (angle)
    {
    case 90:

        if(sq_flag == 0){
            replace_part(arr, arr_t, start_x, start_y-1, end_x-1, end_y, H, W); //done
            break;
        }
        if((lenght_x-lenght_y)%2==0){
            // printf("OFF");
            int x = (lenght_x-lenght_y)/2;
            int y = (lenght_x-lenght_y)/2;
            replace_part(arr, arr_t, start_x+x, start_y-y, end_x-x-2, end_y+y, H, W); //done over
            break;
        }
        if((lenght_x-lenght_y)%2==1){
            // printf("YE");
            int x = abs((lenght_x-lenght_y-1)/2);
            int y = abs((lenght_x-lenght_y-1)/2);
            replace_part(arr, arr_t, start_x+x+2, start_y-y-1, end_x-x-2, end_y+y, H, W); // done BUT start_X + 2
            break;
        }
        if((lenght_x-lenght_y)%2==-1){
            // printf("L");
            int x = abs((lenght_x-lenght_y+1)/2);
            int y = abs((lenght_x-lenght_y+1)/2);
            replace_part(arr, arr_t, start_x-x, start_y+y, end_x+x, end_y-y, H, W); //done
            break;
        }


    case 180:
        replace_part(arr, arr_t, start_x, start_y, end_x-1, end_y+1, H, W); // x without change
        break;

    case 270:
        if(sq_flag == 0){
            replace_part(arr, arr_t, start_x, start_y-1, end_x-1, end_y, H, W);
            break;
        }
        if((lenght_x-lenght_y)%2==0){
            //printf("%d %d-------\n", lenght_x, lenght_y);
            int x = ((lenght_x-lenght_y))/2;
            int y = ((lenght_x-lenght_y))/2;
            //printf("%d %d %d %d  H=%d W=%d   - delta = %d\n",  start_x+x, start_y-y, end_x-x, end_y+y, H, W, x);
            //printf("S");
            
            replace_part(arr, arr_t, start_x+x, start_y-y, end_x-x-2, end_y+y, H, W);
            break;
        }
        if((lenght_x-lenght_y)%2==1){
            
            int x = abs((lenght_x-lenght_y-1)/2);
            int y = abs((lenght_x-lenght_y-1)/2);
            replace_part(arr, arr_t, start_x+x, start_y-y, end_x-x-3, end_y+y, H, W); //done over
            break;
        }
                
        if((lenght_x-lenght_y)%2==-1){

            int x = abs((lenght_x-lenght_y+1)/2);
            int y = abs((lenght_x-lenght_y+1)/2);
            replace_part(arr, arr_t, start_x-x-1, start_y+y+1, end_x+x-3, end_y-y, H, W);
            break;
        }
    default:
        break;
    }
}
