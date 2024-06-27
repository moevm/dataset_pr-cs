#include "core.hpp"

BmpSystem::Bmp::Bmp(const char *inputPathFile)
{
    fileHeader = new BitmapFileHeader;
    infoHeader = new BitmapInfoHeader;

    std::ifstream file(inputPathFile, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Failed to open file" << std::endl;
        exit(40);
    }

    file.read(reinterpret_cast<char *>(fileHeader), sizeof(BitmapFileHeader));
    if (fileHeader->signature != 0x4D42)
    {
        std::cout << "It isn't a bmp file" << std::endl;
        exit(40);
    }

    file.read(reinterpret_cast<char *>(infoHeader), sizeof(BitmapInfoHeader));
    {
        if (infoHeader->bitPerPixel != 24 || infoHeader->size != 40)
        {
            std::cout << "Picture aren't supported" << std::endl;
            exit(40);
        }
    }

    dataPixels = new Rgb* [infoHeader->height];
    int8_t padding = (4 - (infoHeader->width * sizeof(Rgb)) % 4) % 4;
    for (int32_t i = 0; i < infoHeader->height; i++)
    {
        dataPixels[i] = new Rgb[infoHeader->width];
        file.read(reinterpret_cast<char *>(dataPixels[i]), infoHeader->width * sizeof(Rgb));
        file.seekg(padding, std::ios::cur);
    }

    file.close();
}

void BmpSystem::Bmp::writeBmp(const char *outputPathFile)
{
    std::ofstream file(outputPathFile, std::ios::binary);
    file.write(reinterpret_cast<char *>(fileHeader), sizeof(BitmapFileHeader));
    file.write(reinterpret_cast<char *>(infoHeader), sizeof(BitmapInfoHeader));
    int8_t padding = (4 - (infoHeader->width * sizeof(Rgb)) % 4) % 4;
    for (int32_t i = 0; i < infoHeader->height; i++)
    {
        file.write(reinterpret_cast<char *>(dataPixels[i]), infoHeader->width * sizeof(Rgb));
        file.write("0", padding);
    }

    file.close();
}

void BmpSystem::Bmp::printFileInfo()
{
    std::cout << "signature: " << fileHeader->signature << std::endl;
    std::cout << "file size: " << fileHeader->fileSize << std::endl;
    std::cout << "pixelArrOffset: " << fileHeader->pixelArrOffset << std::endl;

    std::cout << "size: " << infoHeader->size << std::endl;
    std::cout << "width: " << infoHeader->width << std::endl;
    std::cout << "height: " << infoHeader->height << std::endl;
    std::cout << "planes: " << infoHeader->planes << std::endl;
    std::cout << "bitPerPixel: " << infoHeader->bitPerPixel << std::endl;
    std::cout << "compression: " << infoHeader->compression << std::endl;
    std::cout << "imageSize: " << infoHeader->imageSize << std::endl;
    std::cout << "importantColorCount: " << infoHeader->importantColorCount << std::endl;
}

void printInstruction()
{
    std::cout << "Это программа реализовывает функционал по обработке bmp-файла\n"
              << "Поддерживаются файлы с глубиной цвета в 24 бита\n"
              << "Доступные флаги:\n"
              << "\t-d/--info \tПечатает информацию об изображении\n"
              << "\t-i/--input \tЗадает имя входного изображения\n"
              << "\t-o/--output \tЗадает имя выходного изображения\n\n"
              << "Инверсия цвета в заданной области. Флаг для выполнения данной операции: `-I/--inverse`\n"
              << "\t-L/--left_up \t\tЗадает координаты левого верхнего угла\n"
              << "\t-R/--right_down \tЗадает координаты правого нижнего угла\n\n"
              << "Преобразовать в Ч/Б изображение. Флаг для выполнения данной операции: `-g/--gray`\n"
              << "\tФлаги такие же, как в инверсии\n\n"
              << "Изменение размера изображения. Флаг для выполнения данной операции: `-p/--resize`\n"
              << "\t-l/--left || -r/--right || -a/--above || -b/--below \t Cтороны изменения размера\n"
              << "\t-c/--color \tЦвет фона при расширении изображения\n";
}


std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    if (token == "")
    {
        std::cout << "Вы неправильно ввели координату" << std::endl;
        exit(40);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void BmpSystem::Bmp::setPixel(int x, int y, BmpSystem::Rgb color) {
    if (x < 0 || x >= infoHeader->width || y < 0 || y >= infoHeader->height) {
        exit(40);
    }
    y = infoHeader->height - 1 - y;
    dataPixels[y][x] = color;
}

bool BmpSystem::Bmp::isCorrectSize(Side side)
{
    if (side.left < 0 || side.right < 0 || side.above < 0 || side.below < 0)
    {
        if (abs(side.left) >= infoHeader->width || abs(side.right) >= infoHeader->width || abs(side.above) >= infoHeader->height || abs(side.below) >= infoHeader->height)
        {
            std::cout << "Вы не можете обрезать больше чем сама картинка" << std::endl;
            exit(40);
        }
    }

    else if (side.left > 3000 || side.right > 3000 || side.above > 3000 || side.below > 3000)
    {
        std::cout << "Вы не можете увеличить изображение на столько" << std::endl;
        exit(40);
    }

    return true;
}

void BmpSystem::Bmp::replaceCoord(Coordinates* coord)
{
    int16_t temp = 0;

    if (coord->leftX < 0)
    {
        coord->leftX = 0;
    }
    if (coord->rightX < 0)
    {
        coord->rightX = 0;
    }
    if (coord->leftY < 0)
    {
        coord->leftY = 0;
    }
    if (coord->rightY < 0)
    {
        coord->rightY = 0;
    }

    if (coord->leftX > coord->rightX)
    {
        temp = coord->leftX;
        coord->leftX = coord->rightX;
        coord->rightX = temp;
    }
    if (coord->leftY > coord->rightY)
    {
        temp = coord->leftY;
        coord->leftY = coord->rightY;
        coord->rightY = temp;
    }
}