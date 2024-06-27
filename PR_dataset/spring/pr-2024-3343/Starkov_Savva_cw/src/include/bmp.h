#ifndef BMP_H
#define BMP_H

#pragma pack(push,1)
// Структура заголовка файла BMP
typedef struct {
    uint16_t signature;         // Сигнатура файла ('BM' для BMP)
    uint32_t file_size;         // Размер файла в байтах
    uint16_t reserved1;         // Зарезервировано (должно быть 0)
    uint16_t reserved2;         // Зарезервировано (должно быть 0)
    uint32_t offset;            // Смещение до начала данных изображения
    uint32_t header_size;       // Размер этой структуры заголовка (обычно 40 байт)
    int32_t width;              // Ширина изображения в пикселях
    int32_t height;             // Высота изображения в пикселях
    uint16_t planes;            // Количество плоскостей (должно быть 1)
    uint16_t bit_count;         // Количество бит на пиксель (1, 4, 8, 16, 24 или 32)
    uint32_t compression;       // Тип сжатия (0 - без сжатия)
    uint32_t image_size;        // Размер изображения в байтах (может быть 0 для некоторых типов изображений)
    int32_t x_pixels_per_meter; // Горизонтальное разрешение в пикселях на метр
    int32_t y_pixels_per_meter; // Вертикальное разрешение в пикселях на метр
    uint32_t colors_used;       // Количество цветов в палитре (0 для максимально возможного)
    uint32_t colors_important;  // Количество "важных" цветов (0 означает все)
} BMPFileHeader;

#pragma pack(pop)
// Структура цвета

// Структура BMP файла, объединяющая заголовок файла и заголовок изображения
typedef struct {
    BMPFileHeader file_header;  // Заголовок файла
    std::vector<uint8_t> data;       // Данные изображения
} BMPImage;



struct Pixel
{
    uint8_t *red;
    uint8_t *green;
    uint8_t *blue;

};


struct OptionFlags
{
    bool infoFlag = false;
    bool helpFlag = false;
    bool component_sumFlag = false;
    bool inverseFlag = false;
    bool shiftFlag = false;
    bool axisFlag = false;
    std::string axisfield;
    bool stepFlag = false;
    int stepValue;
    bool hsvFlag = false;
    std::string filenameinput;
    std::string filenameoutput;
    std::string color;

};



#endif