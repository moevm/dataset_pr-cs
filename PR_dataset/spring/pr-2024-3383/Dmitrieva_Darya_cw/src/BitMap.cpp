#include "BitMap.h"

unsigned short BMP::read_u16(FILE *fp) {
    unsigned short value;
    fread(&value, sizeof(value), 1, fp);
    return value;
}

unsigned int BMP::read_u32(FILE *fp) {
    unsigned int value;
    fread(&value, sizeof(value), 1, fp);
    return value;
}

void BMP::write_u16(unsigned short value, FILE *fp) {
    fwrite(&value, sizeof(value), 1, fp);
}

void BMP::write_u32(unsigned int value, FILE *fp) {
    fwrite(&value, sizeof(value), 1, fp);
}

void BMP::writeBitmapFile(const char* outfilename) {
    FILE *oFile = fopen(outfilename, "wb");
    write_u16(header.signature, oFile);
    write_u32(header.filesize, oFile);
    write_u16(header.reserved1, oFile);
    write_u16(header.reserved2, oFile);
    write_u32(header.pixelArrOffset, oFile);

    write_u32(bmiHeader.headerSize, oFile);
    write_u32(bmiHeader.width, oFile);
    write_u32(bmiHeader.height, oFile);

    write_u16(bmiHeader.planes, oFile);
    write_u16(bmiHeader.bitsPerPixel, oFile);
    write_u32(bmiHeader.compression, oFile);
    write_u32(bmiHeader.imageSize, oFile);
    write_u32(bmiHeader.xPixelsPerMeter, oFile);
    write_u32(bmiHeader.yPixelsPerMeter, oFile);
    write_u32(bmiHeader.colorsInColorTable, oFile);
    write_u32(bmiHeader.importantColorCount, oFile);

    int linePadding = (4 - ((bmiHeader.width * sizeof(Bgr)) % 4)) % 4;
    for (int y = 0; y < bmiHeader.height; y++) {
        for (int x = 0; x < bmiHeader.width; x++) {
            fwrite(&pixels[bmiHeader.height - y - 1][x], sizeof(Bgr), 1, oFile);
        }
        unsigned char tempPadding;
        fwrite(&tempPadding, sizeof(unsigned char), linePadding, oFile);
    }
    fclose(oFile);
}

void BMP::set_color(vector<vector<Bgr> > *vector_name, int y, int x, Bgr color) {
    if (y >= 0 && x>=0 && x<bmiHeader.width && y<bmiHeader.height){
        (*vector_name)[y][x].b = color.b;
        (*vector_name)[y][x].g = color.g;
        (*vector_name)[y][x].r = color.r;
    }
}



int BMP::readBitmapFile(const char *filename) {
    FILE *pFile = fopen(filename, "rb");
    if (pFile == NULL) {
        cout << "Ошибка: Не удалось открыть файл" << endl;
        return 0;
    }
    header.signature = read_u16(pFile);
    if (header.signature != 19778) {
        cout << "Ошибка: программа рабоатет только с BMP" << endl;
        return 0;
    }
    header.filesize = read_u32(pFile);
    header.reserved1 = read_u16(pFile);
    header.reserved2 = read_u16(pFile);
    header.pixelArrOffset = read_u32(pFile);

    bmiHeader.headerSize = read_u32(pFile);
    if (bmiHeader.headerSize != 40) {
        cout << "Ошибка: программа поддерживает только 3-ую версию BMP" << endl;
        return 0;
    }
    bmiHeader.width = read_u32(pFile);
    bmiHeader.height = read_u32(pFile);
    bmiHeader.planes = read_u16(pFile);
    if (bmiHeader.planes != 1) {
        return 0;
    }
    bmiHeader.bitsPerPixel = read_u16(pFile);
    if (bmiHeader.bitsPerPixel != 24) {
        cout << "Ошибка: допустимая глубина цвета - 24 бит" << endl;
        return 0;
    }
    bmiHeader.compression = read_u32(pFile);
    bmiHeader.imageSize = read_u32(pFile);
    bmiHeader.xPixelsPerMeter = read_u32(pFile);
    bmiHeader.yPixelsPerMeter = read_u32(pFile);
    bmiHeader.colorsInColorTable = read_u32(pFile);
    bmiHeader.importantColorCount = read_u32(pFile);

    pixels.resize(bmiHeader.height, vector<Bgr>(bmiHeader.width));
    int linePadding = (4 - ((bmiHeader.width * sizeof(Bgr)) % 4)) % 4;
    for (int y = 0; y < bmiHeader.height; y++) {
        for (int x = 0; x < bmiHeader.width; x++) {
            fread(&pixels[bmiHeader.height - 1 - y][x], sizeof(Bgr), 1, pFile);
        }
        unsigned char tempPadding;
        fread(&tempPadding, sizeof(unsigned char), linePadding, pFile);
    }
    fclose(pFile);
    return 1;
}

void BMP::INFO(){
    cout<<"Signature - "<<header.signature<<endl;
    cout<<"FileSize - "<<header.filesize<<endl;
    cout<<"Reserved1 - "<<header.reserved1<<endl;
    cout<<"Reserved2 - "<<header.reserved2<<endl;
    cout<<"FileOffsetToPixelArray - "<<header.pixelArrOffset<<endl;
    cout<<"HeaderSize - "<<bmiHeader.headerSize<<endl;
    cout<<"ImageWidth - "<<bmiHeader.width<<endl;
    cout<<"ImageHeight - "<<bmiHeader.height<<endl;
    cout<<"Planes - "<<bmiHeader.planes<<endl;
    cout<<"BitsPerPixel - "<<bmiHeader.bitsPerPixel<<endl;
    cout<<"Compression - "<<bmiHeader.compression<<endl;
    cout<<"ImageSize - "<<bmiHeader.imageSize<<endl;
    cout<<"XpixelsPerMeter - "<<bmiHeader.xPixelsPerMeter<<endl;
    cout<<"YpixelsPerMeter - "<<bmiHeader.yPixelsPerMeter<<endl;
    cout<<"TotalColors - "<<bmiHeader.colorsInColorTable<<endl;
    cout<<"ImportantColors - "<<bmiHeader.importantColorCount<<endl;
}

void BMP::black_and_white(const char* outfilename, int left, int up, int right, int below) {
    left = (left < 0) ? 0 : (left >= bmiHeader.width) ? bmiHeader.width : left;
    up = (up < 0) ? 0 : (up >= bmiHeader.height) ? bmiHeader.height : up;
    right = (right < 0) ? 0 : (right >= bmiHeader.width) ? bmiHeader.width  : right;
    below = (below < 0) ? 0 : (below >= bmiHeader.height) ? bmiHeader.height : below;
    for (int y = min(up, below); y < max(up, below); y++) {
        for (int x = min(left, right); x < max(left, right); x++) {
            int brightness = round((int)pixels[y][x].r * 0.299 + (int)pixels[y][x].g * 0.587 + (int)pixels[y][x].b * 0.114);
            brightness = (brightness > 255) ? 255 : (brightness < 0) ? 0 : brightness;
            pixels[y][x].b = brightness;
            pixels[y][x].g = brightness;
            pixels[y][x].r = brightness;
        }
    }
    writeBitmapFile(outfilename);
}

void BMP::inversion(const char *outfilename, int left, int up, int right, int below) {
    left = (left < 0) ? 0 : (left >= bmiHeader.width) ? bmiHeader.width : left;
    up = (up < 0) ? 0 : (up >= bmiHeader.height) ? bmiHeader.height : up;
    right = (right < 0) ? 0 : (right >= bmiHeader.width) ? bmiHeader.width  : right;
    below = (below < 0) ? 0 : (below >= bmiHeader.height) ? bmiHeader.height : below;
    for (int y = min(up, below); y < max(up, below); y++) {
        for (int x = min(left, right); x < max(left, right) ; x++) {
            pixels[y][x].b = 255 - pixels[y][x].b;
            pixels[y][x].g = 255 - pixels[y][x].g;
            pixels[y][x].r = 255 - pixels[y][x].r;
        }
    }
    writeBitmapFile(outfilename);
}

void BMP::fill_circle(int center_x, int center_y, int radius, Bgr color){
    int xmin = max(0, center_x - radius);
    int ymin = max(0, center_y - radius);
    int xmax = min((int)bmiHeader.width - 1, center_x + radius);
    int ymax = min((int)bmiHeader.height - 1, center_y + radius);
    for (int y = ymin; y <= ymax; y++){
        for (int x = xmin; x <= xmax; x++){
            if ((x - center_x)*(x - center_x) + (y - center_y)*(y - center_y) <= radius * radius){
                set_color(&pixels, y, x, color);
            }
        }
    }
}

void BMP::draw_lines_with_thickness(const char* outfilename, int x1, int y1, int x2, int y2, int thickness, Bgr color) {
    const int delta_x = abs(x2 - x1);
    const int delta_y = abs(y2-y1);
    const int sign_x = x1 < x2 ? 1: -1;
    const int sign_y = y1 < y2 ? 1: -1;
    int error = delta_x - delta_y;
    set_color(&pixels, y2, x2, color);
    fill_circle(x2, y2, (thickness + 1)/2, color);
    while(x1!=x2 || y1!=y2){
        set_color(&pixels, y1, x1, color);
        fill_circle(x1, y1, (thickness + 1)/2, color);
        int error2 = error * 2;
        if (error2 > -delta_y){
            error -= delta_y;
            x1+= sign_x;
        }
        if (error2 < delta_x){
            error += delta_x;
            y1 += sign_y;
        }
    }
    writeBitmapFile(outfilename);
}

void BMP::resize(const char* outfilename, string direction, int size, Bgr color) {
    if (direction == "right") {
        if (size < 0 && abs(size) >= bmiHeader.width) {
            cout << "Ошибка: Изображение нельзя обрезать, так как параметр превышает ширину изображения" << endl;
            return;
        }
        for (auto& row : pixels){
            row.resize(row.size()+ size, color);
        }
        bmiHeader.width += size;

    } else if (direction == "left") {
        if (size < 0 && abs(size) >= bmiHeader.width) {
            cout << "Ошибка: Изображение нельзя обрезать, так как параметр превышает ширину изображения" << endl;
            return;
        }
        for (auto& row : pixels){
            if (size <=0){
                row.erase(row.begin(), row.begin() + abs(size));
            }
            else{
                row.insert(row.begin(), size, color);
            }
        }
        bmiHeader.width += size;

    } 
    else if (direction == "below") {
        if (size < 0 && abs(size) >= bmiHeader.height) {
            cout << "Ошибка: Изображение нельзя обрезать, так как параметр превышает высоту изображения" << endl;
            return;
        }
        if (size <= 0){
            for (int i=0; i< abs(size); i++){
                pixels.pop_back();
            }
        }
        else{
            vector<Bgr> NewPixels(bmiHeader.width, color);
            for (int i=0; i<size; i++){
                pixels.push_back(NewPixels);
            }
        }
        bmiHeader.height += size;

    } else if (direction == "above") {
        if (size < 0 && abs(size) >= bmiHeader.height) {
            cout << "Ошибка: Изображение нельзя обрезать, так как параметр превышает высоту изображения" << endl;
            return;
        }
        vector<Bgr> newLine(bmiHeader.width, color);
        if (size > 0){
            for (int i=0; i<size; i++){
                pixels.insert(pixels.begin(), newLine);
            }
        } 
        else {
            pixels.erase(pixels.begin(), pixels.begin() + abs(size));
        }
        bmiHeader.height += size;
    }
    writeBitmapFile(outfilename);
}


void BMP::ornament(const char *outfilename, int thickness, Bgr color){
    vector<vector<Bgr>> NewPixels(bmiHeader.height + 2* thickness, vector<Bgr>(bmiHeader.width + thickness*2, color));
    for (int y = 0; y < bmiHeader.height; y++){
        for (int x = 0; x < bmiHeader.width; x++){
            NewPixels[y + thickness][x + thickness] = pixels[y][x];
        }
    }
    bmiHeader.height += 2* thickness;
    bmiHeader.width += 2*thickness;
    pixels = NewPixels;
    writeBitmapFile(outfilename);
}


