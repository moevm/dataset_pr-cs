#include <png_draw.h>


void draw_line(png_t* image, int x0, int y0, int x1, int y1, rgb_t rgb, int thickness){
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int temp;
    bool swap = false;
    if(deltay > deltax){
        temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
        temp = deltax;
        deltax = deltay;
        deltay = temp;
        swap = true;
    }
    if (y0 > y1){
        temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    } 
    int error = 0;
    int deltaerr = (deltay + 1);
    int y = y0;
    int diry = 1;
    if (x0 > x1)
        for (int x = x0; x>=x1; x--){
            if (thickness==1)
                if (swap)
                    set_pixel(image,y,x,rgb);
                else
                    set_pixel(image,x,y,rgb);
            else
                if (swap)
                    fill_circle(image,y,x,rgb,(thickness+1)/2);
                else
                    fill_circle(image,x,y,rgb,(thickness+1)/2);
            error = error + deltaerr;
            if (error >= (deltax + 1))
            {
                y = y + diry;
                error = error - (deltax + 1);
            }
        }
    else
        for (int x = x0; x<=x1; x++){
            if (thickness==1)
                if (swap)
                    set_pixel(image,y,x,rgb);
                else
                    set_pixel(image,x,y,rgb);
            else
                if (swap)
                    fill_circle(image,y,x,rgb,(thickness+1)/2);
                else
                    fill_circle(image,x,y,rgb,(thickness+1)/2);
            error = error + deltaerr;
            if (error >= (deltax + 1))
            {
                y = y + diry;
                error = error - (deltax + 1);
            }
        }
}

void fill_circle(png_t* image, int x0, int y0, rgb_t rgb, int radius){
    if (x0-radius > image->width) return;
    if (y0-radius > image->height) return;
    if (x0+radius < 0) return;
    if (y0+radius < 0) return;
    draw_circle(image, x0, y0, rgb, radius);
    for(int y=-radius; y<=radius; y++){
	if (y0+y < 0) continue;
	if (y0+y > image->height) break;
        for(int x=-radius; x<=radius; x++){
            if(x0+x < 0) continue;
            if (x0+x > image->width) break;
            if(x*x+y*y <= radius*radius)
                set_pixel(image, x0+x, y0+y, rgb);
                }
    }
}

void draw_circle(png_t* image, int x0, int y0, rgb_t rgb, int radius){
    int x = 0;
    int y = radius;
    int delta = 3 - 2 * radius;
    while (y >= x){
        set_pixel(image,x0 + x, y0 + y,rgb);
        set_pixel(image,x0 + x, y0 - y,rgb);
        set_pixel(image,x0 - x, y0 + y,rgb);
        set_pixel(image,x0 - x, y0 - y,rgb);
        set_pixel(image,x0 + y, y0 + x,rgb);
        set_pixel(image,x0 + y, y0 - x,rgb);
        set_pixel(image,x0 - y, y0 + x,rgb);
        set_pixel(image,x0 - y, y0 - x,rgb);
        if (delta < 0) 
            delta = delta + 4*x++ + 6;
        else
            delta = delta + 4*(x++ - y--) + 10; 
    }
}

//Task 1
void draw_rectangle(png_t* image, int x0, int y0, int x1, int y1, rgb_t rgb, int thickness, bool fill, rgb_t fillrgb){
    if (fill) fill_rectangle(image, x0, y0, x1, y1, fillrgb);
    draw_line(image, x0, y0, x1, y0, rgb, thickness);
    draw_line(image, x0, y1, x1, y1, rgb, thickness);
    draw_line(image, x0, y0, x0, y1, rgb, thickness);
    draw_line(image, x1, y0, x1, y1, rgb, thickness);
}

void fill_rectangle(png_t* image, int x0, int y0, int x1, int y1, rgb_t rgb){
    int temp;
    if (x0 > x1){
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
    if (y0 > y1){
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    if (x0 >= image->width) return;
    if (y0 >= image->height) return;
    if (x1 > image->width) x1 = image->width;
    if (y1 > image->height) y1 = image->height;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    for (int x = x0; x<= x1; x++)
        for (int y = y0; y<=y1; y++)
            set_pixel(image, x, y, rgb);
}

//Task 2
void draw_hexagon(png_t* image, int x0, int y0, rgb_t rgb, int radius, int thickness, bool fill, rgb_t rgbfill){
    int x1, y1;
    x1 = x0 - radius / 2;
    y1 = y0 - sqrt(3) / 2 * radius; 
    if (fill) fill_hexagon(image, x0, y0, rgbfill, radius);
    draw_line(image, x1,y1, x0-radius,y0, rgb, thickness);
    draw_line(image, x1,y1, x0*2-x1,y1, rgb, thickness);
    draw_line(image, x0*2-x1,y1, x0+radius,y0, rgb, thickness);
    draw_line(image, x0+radius,y0, x0*2-x1,y0*2-y1, rgb, thickness);
    draw_line(image, x0*2 - x1,y0*2-y1, x1,y0*2-y1, rgb, thickness);
    draw_line(image, x1,y0*2-y1, x0-radius, y0, rgb, thickness);
}

void fill_hexagon(png_t* image, int x0, int y0, rgb_t rgb, int radius){
    int x1, y1, x2, y2;
    x1 = x0 - radius;
    y1 = y0;
    x2 = x0 - radius / 2;
    y2 = y0 - sqrt(3) / 2 * radius;
    fill_rectangle(image, x2, y2, x0 * 2 - x2, y0 * 2 - y2, rgb);
    int deltax = abs(x2- x1);
    int deltay = abs(y2 - y1);
    int error = 0;
    int deltaerr = (deltax + 1);
    int x = x2;
    int dirx = -1;
    for (int y = y2; y<=y1; y++){
        for (int yy = y; yy<=y1; yy++){
            set_pixel(image,x,yy,rgb);
            set_pixel(image,x0*2 - x,yy,rgb);
            set_pixel(image,x,y0*2 - yy,rgb);
            set_pixel(image,x0*2 - x,y0*2 - yy,rgb);
        }
        error = error + deltaerr;
        if (error >= (deltay + 1))
        {
            x = x + dirx;
            error = error - (deltay + 1);
        }
    }
}

//Task 3
void copy_area_to(png_t* image, int x0, int y0, int x1, int y1, int x2, int y2){
    int temp;
    if (x0 > x1){
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
    if (y0 > y1){
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    if (x0 < 0) x0 = 0;
    if (x1 > image->width) x1 = image->width;
    if (y0 < 0) y0 = 0;
    if (y1 > image->height) y1 = image->height;
    rgb_t** rowscp = malloc((y1-y0) * sizeof(rgb_t*));
    for (int y = 0; y<y1-y0;y++){
    	rowscp[y] = malloc((x1-x0)*sizeof(rgb_t));
    	for (int x = 0; x < x1 - x0; x++)
    		if(check_coords(image,x0+x,y0+y)) continue;
    		else rowscp[y][x] = get_pixel(image, x0+x, y0+y);
    }
    for (int x = 0; x < x1 - x0; x++)
        for (int y = 0; y < y1 - y0; y++){
      	    if (check_coords(image,x0+x,y0+y)) continue;
            else set_pixel(image,x2+x,y2+y,rowscp[y][x]);
    }
}
