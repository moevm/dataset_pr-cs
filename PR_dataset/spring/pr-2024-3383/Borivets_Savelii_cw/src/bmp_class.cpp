#include "bmp_class.h"

//Чтение Bitmap
void Bitmap::read_bmp(string filename) {
    FILE* f = fopen(filename.c_str(), "rb");
    if (!f) {
        string filename_add_bmp = filename + ".bmp";
        f = fopen(filename_add_bmp.c_str(), "rb");
        if (!f) {
            cout << "Ошибка: Файл " << filename << " или " << filename_add_bmp << " не найден. Проверьте название файла." << endl;
            exit(ARG_ERR);
        }
    }
    //Чтение заголовка файла
    fread(&bmfh, 1, sizeof(BitmapFileHeader), f);
    if (bmfh.signature != 19778 && bmfh.signature != 16973) {
        cout << "Ошибка: Версия BMP " << hex << bmfh.signature << " не поддерживается. Поддерживаемые форматы 4D42/424D" << endl;
        exit(INCOR_TYPE_ERR);
    }
    //Чтение заголовка изображения
    fread(&bmif, 1, sizeof(BitmapInfoHeader), f);
    //Проверка параметров
    if (bmif.bitsPerPixel != 24) {
        cout << "Ошибка: Количество бит на пиксель должно быть равно 24. Текущее значение: " << bmif.bitsPerPixel << endl;
        exit(INCOR_TYPE_ERR);
    } else if (bmif.compression != 0) {
        cout << "Ошибка: Изображение без сжатия(0). Текущее значение: " << bmif.compression << endl;
        exit(INCOR_TYPE_ERR);
    }
    H = bmif.height;
    W = bmif.width;
    pixels.resize(H, vector<Rgb>(W));
    for (size_t y = 0; y < H; y++) {
        fread(pixels[y].data(), sizeof(Rgb), W, f);
        // Считываем лишние байты на конце строки, если они есть
        int padding = (4 - W * 3 % 4) % 4;
        fseek(f, padding, SEEK_CUR);
    }
    fclose(f);
}

//Запись Bitmap
void Bitmap::write_bmp(string filename){
    FILE *ff = fopen(filename.c_str(), "wb");
    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);
    H = bmif.height;
    W = bmif.width;
    for(size_t y = 0; y < H; y++){
        fwrite(pixels[y].data(), 1, W * sizeof(Rgb) + (4 - W * 3 % 4) % 4, ff);
    }
    fclose(ff);
}

//Вывод заголовка файла
void Bitmap::print_file_header(){
    BitmapFileHeader header = bmfh;
    printf("--------------------===Заголовок файла===--------------------\n");
    printf("Сигнатура файла BMP:\t%x (%hu)\n", header.signature, header.signature);
    printf("Размер файла в байтах:\t%x (%u)\n", header.filesize, header.filesize);
    printf("Зарезервированное поле 1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("Зарезервированное поле 2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("Местонахождение данных растрового массива:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

//Вывод заголовка изображения
void Bitmap::print_info_header(){
    BitmapInfoHeader header = bmif;
    printf("-----------------===Заголовок изображения===-----------------\n");
    printf("Размер данной структуры в байтах:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("Ширина: \t%x (%u)\n", header.width, header.width);
    printf("Высота: \t%x (%u)\n", header.height, header.height);
    printf("Число цветовых плоскостей: \t%x (%hu)\n", header.planes, header.planes);
    printf("Бит на пиксель:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("Метод сжатия:\t%x (%u)\n", header.compression, header.compression);
    printf("Размер изображения:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("Горизонтальное разрешение:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("Вертикальное разрешение:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("Число цветов изображения:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("Число основных цветов:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

unsigned int Bitmap::get_height() {
    return H;
}

unsigned int Bitmap::get_width() {
    return W;
}

//Функция rgbfilter
void Bitmap::rgbfilter(string component_name, unsigned char component_value) {
    switch (component_name[0]) {
        case 'r':
            for (size_t y = 0; y < H; y++) {
                for (size_t x = 0; x < W; x++) {
                    pixels[y][x].r = component_value;
                }
            }
            break;
        case 'g':
            for (size_t y = 0; y < H; y++) {
                for (size_t x = 0; x < W; x++) {
                    pixels[y][x].g = component_value;
                }
            }
            break;
        case 'b':
            for (size_t y = 0; y < H; y++) {
                for (size_t x = 0; x < W; x++) {
                    pixels[y][x].b = component_value;
                }
            }
            break;
    }
}

void Bitmap::pix_puter(int x, int y, Rgb color) {
    if (0 <= x && x < W && 0 <= y && y < H) {
        pixels[y][x] = color;
    }
}

//Функция square
void Bitmap::square(int left, int up, int side_size, int thickness, Rgb color, bool fill, Rgb fill_color) {
    if (side_size > 0 && fill) {
        for (int y = up; up - y < side_size; y--) {
            for(int x = left; x - left < side_size; x++) {
                pix_puter(x, y, fill_color);
            }
        }
    }
    int right = left + side_size, down = up - side_size;
    line(left, up, right, up, thickness, color);
    line(left, up, left, down, thickness, color);
    line(right, up, right, down, thickness, color);
    line(left, down, right, down, thickness, color);
}

//Функция для сохранения части картинки по координатам
vector<vector<Rgb>> Bitmap::part_taker(int left, int up, int right, int down) {
    int height = up - down + 1;
    int width = right - left + 1;
    vector<vector<Rgb>> part(height, vector<Rgb>(width));
    for (int i = 0; down + i <= up; i++) {
        for(int j = 0; left + j <= right; j++) {
            part[i][j] = pixels[down + i][left + j];
        }
    }
    return part;
}

void Bitmap::part_placer(int left, int up, vector<vector<Rgb>> part) {
    for (int i = 0; i < part.size(); i++) {
        for (int j = 0; j < part[i].size(); j++) {
            pix_puter(left + j, up - i, part[part.size() - 1 - i][j]);
        }
    }
}

void Bitmap::exchange(int left, int up, int right, int down, char exchange_type) {
    bool err = false;
    if (left < 0 || left >= W) {
        cout << "Ошибка: Некорректная левая координата(Функция Exchange)" << endl;
        err = true;
    }
    if (up < 0 || up >= H) {
        cout << "Ошибка: Некорректная верхняя координата(Функция Exchange)" << endl;
        err = true;
    }
    if (right < 0 || right >= W) {
        cout << "Ошибка: Некорректная правая координата(Функция Exchange)" << endl;
        err = true;
    }
    if (down < 0 || down >= H) {
        cout << "Ошибка: Некорректная нижняя координата(Функция Exchange)" << endl;
        err = true;
    }
    if (err) {
        exit(ARG_ERR);
    }
    int buf;
    if (left > right) {
        cout << "Предупреждение: Смена координат - при вводе левая координата больше правой" << endl;
        buf = left;
        left = right;
        right = buf;
    }
    if (down > up) {
        cout << "Предупреждение: Смена координат - при вводе нижняя координата больше левой" << endl;
        buf = down;
        down = up;
        up = buf;
    }
    vector<vector<Rgb>> lu_part, ld_part, ru_part, rd_part;
    int part_height = (up - down) / 2 - 1, part_width = (right - left) / 2 - 1;
    map<string, map<char, int>> part_coord {
            {"lu", {
                    {'l', left},
                    {'u', up},
                    {'r', left + part_width},
                    {'d', up - part_height}
            }},
            {"ld", {
                    {'l', left},
                    {'u', up - part_height - 1},
                    {'r', left + part_width},
                    {'d', up - 2 * part_height - 1}
            }},
            {"ru", {
                    {'l', left + part_width + 1},
                    {'u', up},
                    {'r', left + 2 * part_width + 1},
                    {'d', up - part_height}
            }},
            {"rd", {
                    {'l', left + part_width + 1},
                    {'u', up - part_height - 1},
                    {'r', left + 2 * part_width + 1},
                    {'d', up - 2 * part_height - 1}
            }}
    };
    lu_part = part_taker(part_coord["lu"]['l'], part_coord["lu"]['u'], part_coord["lu"]['r'], part_coord["lu"]['d']);//left up
    ld_part = part_taker(part_coord["ld"]['l'], part_coord["ld"]['u'], part_coord["ld"]['r'], part_coord["ld"]['d']);//left down
    ru_part = part_taker(part_coord["ru"]['l'], part_coord["ru"]['u'], part_coord["ru"]['r'], part_coord["ru"]['d']);//right up
    rd_part = part_taker(part_coord["rd"]['l'], part_coord["rd"]['u'], part_coord["rd"]['r'], part_coord["rd"]['d']);//right down
    switch (exchange_type) {
        case 'l': //clockwise = 'l'
            part_placer(part_coord["lu"]['l'], part_coord["lu"]['u'], ld_part);//new left up part
            part_placer(part_coord["ld"]['l'], part_coord["ld"]['u'], rd_part);//new left down part
            part_placer(part_coord["ru"]['l'], part_coord["ru"]['u'], lu_part);//new right up part
            part_placer(part_coord["rd"]['l'], part_coord["rd"]['u'], ru_part);//new right down part
            break;
        case 'o'://counterclockwise - 'o'
            part_placer(part_coord["lu"]['l'], part_coord["lu"]['u'], ru_part);//new left up part
            part_placer(part_coord["ld"]['l'], part_coord["ld"]['u'], lu_part);//new left down part
            part_placer(part_coord["ru"]['l'], part_coord["ru"]['u'], rd_part);//new right up part
            part_placer(part_coord["rd"]['l'], part_coord["rd"]['u'], ld_part);//new right down part
            break;
        case 'i'://diagonals - 'i'
            part_placer(part_coord["lu"]['l'], part_coord["lu"]['u'], rd_part);//new left up part
            part_placer(part_coord["ld"]['l'], part_coord["ld"]['u'], ru_part);//new left down part
            part_placer(part_coord["ru"]['l'], part_coord["ru"]['u'], ld_part);//new right up part
            part_placer(part_coord["rd"]['l'], part_coord["rd"]['u'], lu_part);//new right down part
            break;
    }
}

void Bitmap::freq_color(Rgb new_color) {
    map<string, unsigned int> pix_counter;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            Rgb cur_pix = pixels[i][j];
            string key_color = to_string(cur_pix.r) + '.' + to_string(cur_pix.g) + '.' + to_string(cur_pix.b);
            if (pix_counter.count(key_color)) {
                pix_counter[key_color] += 1;
            } else {
                pix_counter[key_color] = 1;
            }
        }
    }
    string mx_str_color;
    unsigned int mx_cnt_color = 0;
    for (const auto& [key_color, cnt_color] : pix_counter) {
        if (cnt_color >= mx_cnt_color) {
            mx_str_color = key_color;
            mx_cnt_color = cnt_color;
        }
    }
    Rgb mx_rgb_color = color_prove(mx_str_color);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (pixels[i][j].r == mx_rgb_color.r && pixels[i][j].g == mx_rgb_color.g && pixels[i][j].b == mx_rgb_color.b) {
                pix_puter(j, i, new_color);
            }
        }
    }
}

void Bitmap::fill_circle(int Xmid, int Ymid, int r, Rgb color){
    int xmin = Xmid - r;
    int ymin = Ymid - r;
    int xmax = Xmid + r;
    int ymax = Ymid + r;
    for (int y = ymin; y <= ymax; y++){
        for (int x = xmin; x <= xmax; x++){
            if ((x - Xmid) * (x - Xmid) + (y - Ymid) * (y - Ymid) <= r * r){
                pix_puter(x, y, color);
            }
        }
    }
}

void Bitmap::line(int x0, int y0, int x1, int y1, int thickness,  Rgb color) {
    const int deltaX = abs(x1 - x0);
    const int deltaY = abs(y1 - y0);
    const int signX = x0 < x1 ? 1 : -1;
    const int signY = y0 < y1 ? 1 : -1;
    int error = deltaX - deltaY;
    fill_circle(x1, y1, (thickness) / 2, color);
    while (x0 != x1 || y0 != y1)
    {
        fill_circle(x0, y0, (thickness) / 2, color);
        const int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x0 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y0 += signY;
        }
    }
}

void Bitmap::outside_ornament(int thickness, Rgb color) {
    vector<vector<Rgb>> old_img = pixels;
    H += thickness * 2;
    W += thickness * 2;
    bmif.height = H;
    bmif.width = W;
    bmif.imageSize = H * W;
    bmfh.filesize = sizeof(bmif) + sizeof(bmfh) + sizeof(Rgb) * H * W;
    vector<vector<Rgb>> bgr(H, vector<Rgb>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            bgr[i][j] = color;
        }
    }
    pixels = bgr;
    part_placer(thickness, H - 1 - thickness, old_img);
}