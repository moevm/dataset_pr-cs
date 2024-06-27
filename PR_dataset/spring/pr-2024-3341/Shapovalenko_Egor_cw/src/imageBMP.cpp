#include "imageBMP.h"

#include <iostream>

void ie::throwError(const char *message, int exit_code)
{
    printf("%s\n", message);
    exit(exit_code);
}

ie::ImageBMP::ImageBMP() = default;

ie::ImageBMP::~ImageBMP() = default;

int ie::ImageBMP::getWidth()
{
    return Width;
}

int ie::ImageBMP::getHeight()
{
    return Height;
}

void ie::ImageBMP::allocateMemmoryForPixels()
{
    bitmap = (RGB**)malloc(Height*sizeof(RGB*));

    for (int i = 0; i < Height; i++) {
        bitmap[i] = (RGB*)malloc((Width*sizeof(RGB)+3)&(-4));
    }
}

void ie::ImageBMP::freeMemmoryForPixels()
{
    for (int i = 0; i < Height; i++) {
        free(bitmap[i]);
    }
    free(bitmap);
}

void ie::ImageBMP::clearPixels()
{
   for (int i = 0; i < Height; i++) {
        for(int j = 0; j < Width; j++){
            bitmap[i][j].r = 0;
            bitmap[i][j].g = 0;
            bitmap[i][j].b = 0;
        }
    }
}

bool ie::checkFileFormat(unsigned char *signature, unsigned int compression,
    unsigned short bits_per_pixel)
{
    return ((signature[0] == 0x4d && signature[1] == 0x42) || (signature[0] == 0x42 && signature[1] == 0x4d))
        && compression == 0 && bits_per_pixel == 24;
}

void ie::ImageBMP::showImageInfo()
{
    printf("BMPHeader\n");
    printf("Signature:\t%x\n",*((short int*)bmph.signature));
    printf("File size:\t%u\n",bmph.file_size);
    printf("Reserved 1:\t%x\n",*((short int*)bmph.reserved1));
    printf("Reserved 2:\t%x\n",*((short int*)bmph.reserved2));
    printf("Pixel offset:\t%u\n", bmph.pixel_offset);
    printf("\n");

    printf("DIBHeader\n");
    printf("Header size:\t%u\n",dibh.byte_count);
    printf("Width:\t%u\n",dibh.width);
    printf("Height:\t%u\n",dibh.height);
    printf("Color planes:\t%hu\n",dibh.color_planes);
    printf("Bits per pixel:\t%hu\n",dibh.bits_per_pixel);
    printf("Compression:\t%u\n",dibh.compression);
    printf("Image size:\t%u\n",dibh.image_size);
    printf("yPixels per meter:\t%u\n",dibh.pwidth);
    printf("xPixels per meter:\t%u\n",dibh.pheight);
    printf("Colors in color table:\t%u\n",dibh.color_count);
    printf("Important color count:\t%u\n",dibh.important_color_count);
}

void ie::ImageBMP::readImageFromFile(const char *input_file_name)
{
    FILE* fin = fopen(input_file_name, "rb");

    if (!fin) {
        throwError("Error: file could not be opened.", FILE_ERROR);
    }

    fread(&bmph, sizeof(BMPHeader), 1, fin);
    fread(&dibh, sizeof(DIBHeader), 1, fin);

    if (!checkFileFormat(bmph.signature, dibh.compression,
        dibh.bits_per_pixel)) {
        fclose(fin);
        throwError("Error: wrong file format.", FILE_ERROR);
    }

    fseek(fin, bmph.pixel_offset, SEEK_SET);

    Width = (int)(dibh.width);
    Height = (int)(dibh.height);

    allocateMemmoryForPixels();

    for (int i = 0; i < Height; i++) {
        fread(bitmap[Height -i -1], 1, (Width*sizeof(RGB)+3)&(-4), fin);
    }
        
    fclose(fin);
}

void ie::ImageBMP::writeImageToFile(const char *output_file_name)
{
    FILE* fout = fopen(output_file_name, "wb");

    dibh.width = (unsigned int)Width;
    dibh.height = (unsigned int)Height;

    fwrite(&bmph, 1, sizeof(BMPHeader), fout);
    fwrite(&dibh, 1, sizeof(DIBHeader), fout);

    fseek(fout, bmph.pixel_offset, SEEK_SET);

    for (int i = 0; i < Height; i++) {
        fwrite(bitmap[Height -i -1], 1, (Width*sizeof(RGB)+3)&(-4), fout);
    }

    freeMemmoryForPixels();
        
    fclose(fout);
}

bool ie::ImageBMP::checkCoordsValidity(int x, int y)
{
    return (x >= 0 && x < Width && y >= 0 && y < Height);
}

void ie::ImageBMP::clear()
{
    clearPixels();
}

ie::Color ie::ImageBMP::getColor(int x, int y)
{   
    if (!checkCoordsValidity(x, y)) {
        return {0, 0, 0};
    }
    ie:Color color;
    color.r = bitmap[y][x].r;
    color.g = bitmap[y][x].g;
    color.b = bitmap[y][x].b;

    return color;
}

void ie::ImageBMP::setColor(int x, int y, Color color)
{
    if (!checkCoordsValidity(x, y)) {
        return;
    }
    bitmap[y][x].r = color.r;
    bitmap[y][x].g = color.g;
    bitmap[y][x].b = color.b;
}

bool checkOnCircleLine(int x, int y, int x0, int y0, int radius, int thickness)
{
    bool flag1 = (x-x0)*(x-x0) + (y-y0)*(y-y0) <= (radius+thickness/2)*(radius+thickness/2);
    bool flag2 = (x-x0)*(x-x0) + (y-y0)*(y-y0) >= (std::max(0, radius-thickness/2))*(std::max(0, radius-thickness/2));
    return flag1 && flag2;
}

bool checkInCircle(int x, int y, int x0, int y0, int radius, int thickness)
{
    bool flag = (x-x0)*(x-x0) + (y-y0)*(y-y0) <= (radius-thickness/2)*(radius-thickness/2);
    return flag;
}

void ie::ImageBMP::drawBresenhamCircle(int x0, int y0, int radius, Color color)
{
    int D = 3 - 2 * radius;
    int x = 0;
    int y = radius;
    while (x <= y) {
        setColor(x+x0, y+y0, color);
        setColor(y+x0, x+y0, color);
        setColor(-y+x0, x+y0, color);
        setColor(-x+x0, y+y0, color);
        setColor(-x+x0, -y+y0, color);
        setColor(-y+x0, -x+y0, color);
        setColor(y+x0, -x+y0, color);
        setColor(x+x0, -y+y0, color);

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

void ie::ImageBMP::drawCircle(int x0, int y0, int radius, int thickness, 
    Color color, bool fill, Color fill_color)
{
    for (int y = std::max(0, y0-radius-thickness/2); y <= std::min(Height-1, y0+radius+thickness/2); y++) {
        for (int x = std::max(0, x0-radius-thickness/2); x <= std::min(Width-1, x0+radius+thickness/2); x++) {
            if (fill && checkInCircle(x, y, x0, y0, radius, thickness)) {
                setColor(x, y, fill_color);
            }
            if (checkOnCircleLine(x, y, x0, y0, radius, thickness)) {
                setColor(x, y, color);
            }
        }
    }

    drawBresenhamCircle(x0, y0, radius-thickness/2, color);
    drawBresenhamCircle(x0, y0, radius+thickness/2, color);
}

void ie::ImageBMP::drawLineLow(int x0, int y0, int x1, int y1, 
    int thickness, Color color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (thickness == 1) {
            setColor(x, y, color);
        } else {
            drawCircle(x, y, thickness/2, 1, color, true, color);
        }

        if (D > 0) {
            y += yi;
            D += 2 * (dy - dx);
        } else {
            D += 2 * dy;
        }
    }
}

void ie::ImageBMP::drawLineHigh(int x0, int y0, int x1, int y1, 
    int thickness, Color color)
{

    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;
    for (int y = y0; y <= y1; y++) {
        if (thickness == 1) {
            setColor(x, y, color);
        } else {
            drawCircle(x, y, thickness/2, 1, color, true, color);
        }

        if (D > 0) {
            x += xi;
            D += 2 * (dx - dy);
        } else {
            D += 2 * dx;
        }
    }
}

void ie::ImageBMP::drawLine(int x0, int y0, int x1, int y1, 
    int thickness, Color color)
{
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        drawLineLow(x0, y0, x1, y1, thickness, color);
    } else {
        if (y0 > y1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        drawLineHigh(x0, y0, x1, y1, thickness, color);
    }
}

void ie::ImageBMP::setSize(int width, int height)
{
    Width = width;
    Height = height;
    
    allocateMemmoryForPixels();
    
    clear();
}

ie::ImageBMP ie::ImageBMP::copy(int x0, int y0, int x1, int y1)
{
    if (x0 > x1) {
        std::swap(x0, x1);
    }
    if (y0 > y1) {
        std::swap(y0, y1);
    }

    ImageBMP copy_image;
    copy_image.setSize(x1-x0+1, y1-y0+1);
    for (int y = 0; y < copy_image.getHeight(); y++) {
        for (int x = 0; x < copy_image.getWidth(); x++) {
            copy_image.setColor(x, y, getColor(x + x0, y + y0));
        }
    }
    return copy_image;
}

void ie::ImageBMP::borderRectangles(Color rectangles_color, Color border_color, int thickness)
{
    int current_area, max_current_area;
    int a, b;
    int x0, y0, x1, y1;
    int a_max, b_max;
    int already_found;
    std::vector<Coord> found_rectangles;

    for(int x = 0; x < Width; x++) {
        for(int y = 0; y < Height; y++) {
            already_found = 0;
            for (int i = 0; i < found_rectangles.size(); i+=2) {
                if (found_rectangles[i].x <= x && x <= found_rectangles[i+1].x
                    && found_rectangles[i].y <= y && y <= found_rectangles[i+1].y) {
                        already_found = 1;
                        break;
                    }
            }

            if (already_found) {
                continue;
            }
            
            if(getColor(x, y) == rectangles_color && getColor(x-1, y) != rectangles_color && getColor(x, y-1) != rectangles_color){
                b_max = Height;
                max_current_area = 0;
                a = 0, b = 0;
                while((x+a < Width) && getColor(x+a, y) == rectangles_color){
                    while((y+b < Height) && getColor(x+a, y+b) == rectangles_color){
                        current_area += a+1;
                        b++;
                        if(b > b_max)
                            break;
                    }
                    if(current_area > max_current_area){
                        max_current_area = current_area;
                        a_max = a;
                        b_max = b - 1;
                    }
                    current_area = 0;
                    b = 0;
                    a++;
                }

                x0 = x, y0 = y;
                x1 = x+a_max, y1 = y+b_max;

                found_rectangles.push_back({x0, y0});
                found_rectangles.push_back({x1, y1});
                
                drawLine(x0, y0, x1, y0, thickness, border_color);
                drawLine(x0, y0, x0, y1, thickness, border_color);
                drawLine(x0, y1, x1, y1, thickness, border_color);
                drawLine(x1, y0, x1, y1, thickness, border_color);
            }
        }
    }
}

void ie::ImageBMP::concatBMP(ImageBMP& second_image_bmp, int axis, Color fill_color)
{
    int new_width, new_height, max_width, max_height, min_width, min_height;

    max_width = std::max(Width, second_image_bmp.getWidth());
    max_height = std::max(Height, second_image_bmp.getHeight());

    min_width = std::min(Width, second_image_bmp.getWidth());
    min_height = std::min(Height, second_image_bmp.getHeight());

    if (axis == 0) {
        new_width = Width + second_image_bmp.getWidth();
        new_height = max_height;
    } else {
        new_width = max_width;
        new_height = Height + second_image_bmp.getHeight();
    }

    ImageBMP copy_image = copy(0, 0, Width-1, Height-1);
    
    setSize(new_width, new_height);

    if (axis == 0) {
        int new_x;
        for (int y = 0; y < max_height; y++, new_x = 0) {
            for (int x = 0; x < min_width; x++, new_x += 2) {
                if (copy_image.checkCoordsValidity(x, y)) {
                    setColor(new_x, y, copy_image.getColor(x, y));
                } else {
                    setColor(new_x, y, fill_color);
                }

                if (second_image_bmp.checkCoordsValidity(x, y)) {
                    setColor(new_x + 1, y, second_image_bmp.getColor(x, y));
                } else {
                    setColor(new_x + 1, y, fill_color);
                }
            }
            for (int x = min_width; x < max_width; x++, new_x++){
                if (copy_image.checkCoordsValidity(x, y)) {
                    setColor(new_x, y, copy_image.getColor(x, y));
                } else if (second_image_bmp.checkCoordsValidity(x, y)) {
                    setColor(new_x, y, second_image_bmp.getColor(x, y));
                } else {
                    setColor(new_x, y, fill_color);
                }
            }
        } 
    } else {
        int new_y;
        for (int x = 0; x < max_width; x++, new_y = 0) {
            for (int y = 0; y < min_height; y++, new_y += 2) {
                if (copy_image.checkCoordsValidity(x, y)) {
                    setColor(x, new_y, copy_image.getColor(x, y));
                } else {
                    setColor(x, new_y, fill_color);
                }

                if (second_image_bmp.checkCoordsValidity(x, y)) {
                    setColor(x, new_y + 1, second_image_bmp.getColor(x, y));
                } else {
                    setColor(x, new_y + 1, fill_color);
                }
            }
            for (int y = min_height; y < max_height; y++, new_y++){
                if (copy_image.checkCoordsValidity(x, y)) {
                    setColor(x, new_y, copy_image.getColor(x, y));
                } else if (second_image_bmp.checkCoordsValidity(x, y)) {
                    setColor(x, new_y, second_image_bmp.getColor(x, y));
                } else {
                    setColor(x, new_y, fill_color);
                }
            }
        } 
    }
}

void ie::ImageBMP::rgbFilter(int component_idx, int component_value)
{
    if (component_idx == R_IDX) {
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                bitmap[y][x].r = component_value;
            }
        }
    } else if (component_idx == G_IDX) {
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                bitmap[y][x].g = component_value;
            }
        }
    } else if (component_idx == B_IDX) {
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                bitmap[y][x].b = component_value;
            }
        }
    }
}