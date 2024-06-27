#include "../include/work.h"

void read_png_file(char *file_name, Png *image) {
    int x,y;
    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        printf("Invalid file name: %s\n", file_name);
        exit(10);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)){
        printf("File %s is not recognized as a PNG\n", file_name);
        exit(11);
    }

    /* initialize stuff */
    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("png_create_read_struct failed\n");
        exit(10);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("png_create_info_struct failed\n");
        exit(10);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io\n");
        exit(10);
    }

    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);

    png_read_info(image->png_ptr, image->info_ptr);

    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during read_image\n");
        exit(10);
    }

    image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    for (y = 0; y < image->height; y++)
        image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));

    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}


void write_png_file(char *file_name, Png *image) {
    int x,y;
    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        printf("File %s could not be opened\n", file_name);
        exit(10);
    }

    /* initialize stuff */
    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf("png_create_write_struct failed\n");
        exit(10);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf("png_create_info_struct failed\n");
        exit(10);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during init_io\n");
        exit(10);
    }

    png_init_io(image->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing header\n");
        exit(10);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during writing bytes\n");
        exit(10);
    }

    png_write_image(image->png_ptr, image->row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf("Error during end of write\n");
        exit(10);
    }

    png_write_end(image->png_ptr, NULL);

    /* cleanup heap allocation */
    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}

void changeColor(png_byte* tmp, RGB color) {
    tmp[0] = color.r;
    tmp[1] = color.g;
    tmp[2] = color.b;
}

/*Задание №1*/
int check(int x, int y, int W, int H){
    return x >= 0 && x < W && y >= 0 && y < H;
}
 
void drawCircle(Png* image ,int x0, int y0, int radius, RGB color){
    int D = 3 - 2 * radius;
    int x = 0;
    int y = radius;
	int W = image->width;
	int H = image->height;
    while (x <= y) {
		if (check(x+x0,y+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[y+y0][(x+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(y+x0,x+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[x+y0][(y+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(-y+x0,x+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[x+y0][(-y+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(-x+x0, y+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[y+y0][(-x+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(-x+x0,-y+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[-y+y0][(-x+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(-y+x0,-x+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[-x+y0][(-y+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(y+x0,-x+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[-x+y0][(y+x0) * 3]);
            changeColor(ptr, color);
        }
 
		if (check(x+x0,-y+y0,W,H)) {
            png_byte* ptr = &(image->row_pointers[-y+y0][(x+x0) * 3]);
            changeColor(ptr, color);
        }
		if (D < 0) {
            D += 4 * x + 6;
            x++;
        } else {
            D += 4 * (x - y) + 10;
            x++;
            y--;
        }
    }
}
 
void drawLine(Png* image, int x1, int y1, int x2, int y2, int line_thickness, RGB color){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int h = image->height;
    int w = image->width;
    while(1){
        if (y1 >= 0 && y1 <= h && x1 >= 0 && x1 <= w){
            if (line_thickness == 1){
                png_byte* ptr = &(image->row_pointers[y1][x1 * 3]);
				changeColor(ptr, color);
            }   
        }
 
        if(line_thickness > 1 && x1 - (line_thickness/2) < w && y1 - (line_thickness/2) < h && x1 + (line_thickness/2) >= 0 && y1 + (line_thickness/2) >= 0){
            drawCircle(image, x1, y1, line_thickness/2 ,color);
        }

        if (x1 == x2 && y1 == y2){
            break;
        }
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Square(Png* image, Parametrs* par){
	int x0=par->left;
	int x1=x0 + par->side_size;
    int y0=par->up;
	int y1=y0 + par->side_size;

	drawLine(image, x0, y0, x1, y0, par->thickness, par->color);
    drawLine(image, x0, y1, x1, y1, par->thickness, par->color);
    drawLine(image, x1, y0, x1, y1, par->thickness, par->color);
    drawLine(image, x0, y0, x0, y1, par->thickness, par->color);
    if(par->fill){
        int i = y0+par->thickness/2;
        while(i > 0 && i < image->height && i <= y1-par->thickness/2){
            png_byte* row = image->row_pointers[i];
            int j = x0+par->thickness/2;
            while (j > 0 && j < image->width && j <= x1-par->thickness/2){
                png_byte* ptr = &(row[j * 3]);
                changeColor(ptr, par->fill_color);
                j++;  
            }
            i++;  
        }
    }
}

/*Задание №2*/
void swapAreas(Png* image, Rectangle* first, Rectangle* second) {
    RGB canvas1[first->y1-first->y0][first->x1-first->x0];
    RGB canvas2[second->y1-second->y0][second->x1-second->x0];
    for (int y = first->y0; y < first->y1; y++) {
        png_byte* row = image->row_pointers[y];
        for (int x = first->x0; x < first->x1; x++) {
            png_byte* ptr = &(row[x * 3]);
            canvas1[y-first->y0][x-first->x0].r = ptr[0];
            canvas1[y-first->y0][x-first->x0].g = ptr[1];
            canvas1[y-first->y0][x-first->x0].b = ptr[2];   
        }
    }
 
    for (int y = second->y0; y < second->y1; y++) {
        png_byte* row = image->row_pointers[y];
        for (int x = second->x0; x < second->x1; x++) {
            png_byte* ptr = &(row[x * 3]);
            canvas2[y-second->y0][x-second->x0].r = ptr[0];
            canvas2[y-second->y0][x-second->x0].g = ptr[1];
            canvas2[y-second->y0][x-second->x0].b = ptr[2];
        }
    }
 
    for (int y = 0; y < image->height; y++) {
        png_byte* row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte* ptr = &(row[x * 3]);
            if (y >= first->y0 && y < first->y1 && x >= first->x0 && x < first->x1) {
                ptr[0] = canvas2[y-first->y0][x-first->x0].r;
                ptr[1] = canvas2[y-first->y0][x-first->x0].g;
                ptr[2] = canvas2[y-first->y0][x-first->x0].b;
            }
            if (y >= second->y0 && y < second->y1 && x >= second->x0 && x < second->x1) {
                ptr[0] = canvas1[y-second->y0][x-second->x0].r;
                ptr[1] = canvas1[y-second->y0][x-second->x0].g;
                ptr[2] = canvas1[y-second->y0][x-second->x0].b;
           }
       }
    }
}
 
void Exchange(Png* image, Parametrs* par){
    int width = par->right-par->left;
    int height = par->down-par->up;
    if(width%2 != 0)
        par->right = par->right - 1;
        width = par->right-par->left;
    if(height%2 != 0)
        par->down = par->down - 1;
        height = par->down-par->up;

    Rectangle rectLeftUp;
    Rectangle rectLeftDown;
    Rectangle rectRightUp;
    Rectangle rectRightDown;
 
    rectLeftUp.x0 = par->left;
    rectLeftUp.y0 = par->up;
    rectLeftUp.x1 = par->right - (width / 2);
    rectLeftUp.y1 = par->down - (height / 2);
 
    rectLeftDown.x0 = par->left;
    rectLeftDown.y0 = par->down - (height / 2);
    rectLeftDown.x1 = par->right - (width / 2);
    rectLeftDown.y1 = par->down;
 
    rectRightUp.x0 = par->right - (width / 2);
    rectRightUp.y0 = par->up;
    rectRightUp.x1 = par->right;
    rectRightUp.y1 = par->down - (height / 2);
 
    rectRightDown.x0 = par->right - (width / 2);
    rectRightDown.y0 = par->down - (height / 2);
    rectRightDown.x1 = par->right;
    rectRightDown.y1 = par->down;
 
    switch (par->exchange_type)
    {
    case 0:{ //clockwise
        swapAreas(image, &rectLeftUp, &rectLeftDown);
        swapAreas(image, &rectLeftDown, &rectRightDown);
        swapAreas(image, &rectRightDown, &rectRightUp);
        break;
    }
    case 1:{ //counterclockwise
        swapAreas(image, &rectLeftUp, &rectRightUp);
        swapAreas(image, &rectRightUp, &rectRightDown);
        swapAreas(image, &rectRightDown, &rectLeftDown);
        break;
    }
    case 2:{ //diagonals
        swapAreas(image, &rectLeftUp, &rectRightDown);
        swapAreas(image, &rectLeftDown, &rectRightUp);
        break;
    }
    default:
        break;
    }
}

/*Задание №3*/
void FreqColor(Png* image, Parametrs* par){
    int color = 3;
    int*** colors = calloc(256, sizeof(int**));
    for(int i = 0; i < 256; i++){
        colors[i] = calloc(256, sizeof(int*));
        for(int j = 0; j < 256; j++){
            colors[i][j] = calloc(256, sizeof(int));
        }
    }
    for (int y = 0; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];
        for (int x = 0; x < image->width; ++x) {
            png_byte* ptr = &(row[x * color]);
            colors[ptr[0]][ptr[1]][ptr[2]]++;
        }
    }
    RGB old_color;
    int maxColor = 0;
    for(int r = 0; r < 256; r++){
        for(int g = 0; g < 256; g++){
            for(int b = 0; b < 256; b++){
                if(colors[r][g][b] > maxColor){
                    maxColor = colors[r][g][b];
                    old_color.r = r;
                    old_color.g = g;
                    old_color.b = b;
                }
            }
        }
    }
    for (int y = 0; y < image->height; ++y) {
        png_byte* row = image->row_pointers[y];
        for (int x = 0; x < image->width; ++x) {
            png_byte* ptr = &(row[x * color]);
            if (old_color.r == ptr[0] && old_color.g == ptr[1] && old_color.b == ptr[2])
                changeColor(ptr, par->color);
        }
    }
}

/*Задание №4*/
void Contrast(Png* image, Parametrs* par){
    double alpha = par->alpha;
    int beta = par->beta;
    for(int y = 0; y < image->height; y++){
        png_byte* row = image->row_pointers[y];
        for(int x = 0; x  < image->width; x++){
            png_byte* ptr = &(row[x * 3]);
            int a = floor((double)(alpha * (double)ptr[0])) + beta;
            int b = floor((double)(alpha * (double)ptr[1])) + beta;
            int c = floor((double)(alpha * (double)ptr[2])) + beta;
            if(a > 255)
                a = 255;
            if(b > 255)
                b = 255;
            if(c > 255)
                c = 255;
            ptr[0] = a;
            ptr[1] = b;
            ptr[2] = c;
        }
    }
}