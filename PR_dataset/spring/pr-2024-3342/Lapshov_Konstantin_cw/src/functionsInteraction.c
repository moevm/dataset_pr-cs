#include "functionsInteraction.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void
swapInt(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}
void
setPixel(BMP *bmp, Point point, RGB color){
    bmp->img[bmp->bmih.biHeight - point.y - 1][point.x] = color;
}
RGB
getInvertPixelColor(BMP *bmp, Point point) {
    RGB pixel = bmp->img[bmp->bmih.biHeight - point.y - 1][point.x];
    RGB invertPixel = {255 - pixel.b, 255 - pixel.g, 255 - pixel.r};

    return invertPixel;
}


void
fillCircle(BMP *bmp, Point center, int radius, RGB color, bool invert) {
    if(!invert) radius = (int)floor(radius/2);

    for(int x = -radius; x < radius; x++) {
        if (center.x + x > bmp->bmih.biWidth || center.x +x < 0) continue;

		int height = sqrt(radius*radius - x*x);
        for (int y = -height; y < height; y++) {
            Point pointForFill = {x+center.x, y+center.y};
            if(pointInImage(bmp->bmih, pointForFill)) {
                if (invert) color = getInvertPixelColor(bmp, pointForFill);
                setPixel(bmp, pointForFill, color);
            }
        }
    }
}


bool
pointInImage(BitmapInfoHeader bmif, Point point) {
    if(point.x < 0 || point.y < 0 || point.x >= bmif.biWidth || point.y >= bmif.biHeight) {
        return false;
    }
    return true;
}


void
line(BMP *bmp, Point start, Point end, int thickness, RGB color){
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int signX = (start.x < end.x) ? 1 : -1;
    int signY = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

    while (start.x != end.x || start.y != end.y) {
        if(thickness == 1) {
            if(pointInImage(bmp->bmih, start)) {
                setPixel(bmp, start, color);
            }else {
                break;
            }
        }else {
            fillCircle(bmp, start, thickness, color, false);
        }
        int err2 = err * 2;

        if(err2 > -dy) {
            err -= dy;
            start.x += signX;
        }
        if(err2 < dx) {
            err += dx;
            start.y += signY;
        }
    }
}


int
checkCoordsInTriangle(Point cords, Point firstPoint, Point secondPoint, Point thirdPoint) {
    int res1 = (firstPoint.x - cords.x) * (secondPoint.y-firstPoint.y) - (secondPoint.x - firstPoint.x) * (firstPoint.y - cords.y);
    int res2 = (secondPoint.x - cords.x) * (thirdPoint.y-secondPoint.y) - (thirdPoint.x - secondPoint.x) * (secondPoint.y - cords.y);
    int res3 = (thirdPoint.x - cords.x) * (firstPoint.y-thirdPoint.y) - (firstPoint.x - thirdPoint.x) * (thirdPoint.y - cords.y);

    return (res1 > 0 && res2 > 0 && res3 > 0) || (res1 < 0 && res2 < 0 && res3 < 0);
}


void
triangle(BMP *bmp, Point* points, int thickness, RGB color, int fill, RGB fill_color) {
    Point firstPoint = points[0];
    Point secondPoint = points[1];
    Point thirdPoint = points[2];

    if(fill) {
        for(int i = MIN(firstPoint.y, MIN(secondPoint.y, thirdPoint.y)); i < MAX(firstPoint.y, MAX(secondPoint.y, thirdPoint.y)); i++) {
            for(int j = MIN(firstPoint.x, MIN(secondPoint.x, thirdPoint.x)); j < MAX(firstPoint.x, MAX(secondPoint.x, thirdPoint.x)); j++) {
                Point pointForFill = {j, i};
                if(checkCoordsInTriangle(pointForFill, firstPoint, secondPoint, thirdPoint)) {
                    if(pointInImage(bmp->bmih, pointForFill)) setPixel(bmp, pointForFill, fill_color);
                }
            }
        }
    }

    line(bmp, firstPoint, secondPoint, thickness, color);
    line(bmp, firstPoint, thirdPoint, thickness, color);
    line(bmp, secondPoint, thirdPoint, thickness, color);
}


void
trim(BMP* bmp, Point leftUp, Point rightDown) {
	if(rightDown.x < leftUp.x) swapInt(&leftUp.x, &rightDown.x);
    if(leftUp.y > rightDown.y) swapInt(&leftUp.y, &rightDown.y);

    if(leftUp.x < 0) leftUp.x = 0;
    if(leftUp.y < 0) leftUp.y = 0;
    if(rightDown.x > bmp->bmih.biWidth) rightDown.x = bmp->bmih.biWidth;
    if(rightDown.y > bmp->bmih.biHeight) rightDown.y = bmp->bmih.biHeight;

    int new_height = rightDown.y - leftUp.y;
    int new_width = rightDown.x - leftUp.x;

    if(new_height <= 0 || new_width <= 0) {
        showError("Wrong coordinates!", ARGUMENTS_FAILURE);
    }

    // Создания нового массива пикселей с учетом предоставленных данных
    RGB **new_arr = createArrayOfPixels(new_height, new_width);

    for(int i = leftUp.y; i < rightDown.y; i++) {
        for (int j = leftUp.x; j < rightDown.x; j++) {
            new_arr[new_height - (i - leftUp.y) - 1][j - leftUp.x] = bmp->img[bmp->bmih.biHeight - i - 1][j];
        }
    }

    //Очистка старого массива
    freeArrayOfPixels(bmp);

    //Работа со структурой файла с учетом новых данных
    bmp->bmih.biHeight = new_height;
    bmp->bmih.biWidth = new_width;

    bmp->bmih.biImageSize = 3 * new_width * new_height + (new_height * (new_width % 4));
    bmp->bmfh.bfSize = bmp->bmfh.bfArrOffset + bmp->bmih.biImageSize;
    bmp->img = new_arr;
}

void rhomb(BMP *bmp, RGB color) {
    size_t height = bmp->bmih.biHeight;
    size_t width = bmp->bmih.biWidth;

    Point one = {width/2, 0};
    Point two = {width/2, height};
    Point three = {-1, height/2};
    Point four = {width, height/2};

    Point pointsOne[3] = {one, two, three};
    Point pointsTwo[3] = {one, two, four};
    triangle(bmp, pointsOne, 1, color, true, color);
    triangle(bmp, pointsTwo, 1, color, true, color);
}



void
choiceTask(BMP *bmp, Option option) {
    if(option.hasInfoOpt) {
        printInfo(*bmp);
        exit(EXIT_SUCCESS);
    }
    if(option.hasInverseCircleOpt) {
        RGB fakeColor = {0, 0, 0};
        fillCircle(bmp, option.center, option.radius, fakeColor, true);
    }
    if(option.hasTrimOpt) {
        trim(bmp, option.leftUp, option.rightDown);
    }
    if(option.hasTriangleOpt) {
        triangle(bmp, option.points, option.thickness, option.color, option.hasFillOpt, option.fillColor);
        //Освобождение массива точек
        free(option.points);
    }
    if(option.hasLineOpt) {
        line(bmp, option.start, option.end, option.thickness, option.color);
    }
    if(option.hasRhombusOpt) {
        rhomb(bmp, option.color);
    }
}