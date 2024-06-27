#include "../headers/rotate_func.hpp"

Rgb **copy(Rgb **source, std::pair<int, int> leftUp, std::pair<int, int> rightDown, BitmapInfoHeader *info) {
    int height = rightDown.second - leftUp.second, width = rightDown.first - leftUp.first;
//    height += height % 2, width += width % 2;
    Rgb **copy = new Rgb *[height];
    for (int i = 0; i < height; i++)
        copy[i] = new Rgb[width];
    for (int i = 0; i < height && i + leftUp.second < info->height; ++i)
        for (int j = 0; j < width && j + leftUp.first < info->width; ++j)
//            copy[i][j] = {255,255,255};
            copy[height - i - 1][j] = source[info->height - i - leftUp.second - 1][j + leftUp.first];
    return copy;
}

void Bmp::full_right_angle() {
    Rgb **copy = new Rgb *[info->width];
    for (int j = 0; j < info->width; j++) {
        copy[j] = new Rgb[info->height];
        for (int i = 0; i < info->height; i++)
            copy[j][i] = data[info->height - i - 1][j];
    }
    std::swap(info->width, info->height);
    this->padding = (int) (4 - ((info->width * 3) % 4)) % 4;
    data = copy;
}

void Bmp::field_right_angle(std::pair<int, int> leftUp, std::pair<int, int> rightDown) {
    Rgb **imgCopy = copy(this->data, leftUp, rightDown, info);
    int height = rightDown.second - leftUp.second, width = rightDown.first - leftUp.first;
    std::pair<int, int> center = {(rightDown.first + leftUp.first) / 2, (rightDown.second + leftUp.second) / 2};
//    std::cout << height << " " << width << " " << center.first << " " << center.second << std::endl;
//    std::cout<<center.second - width / 2 << " " << center.first - height / 2 << " " << center.first + height / 2 << " " << center.second + width / 2 << std::endl;
//    save_copy_for_check(data, leftUp, rightDown, info, header);
//    std::cout<<width << " " << height << std::endl;
    int startX = center.second - width / 2, endX = center.second + width / 2;
    int startY = center.first  - height / 2, endY = center.first  + height / 2;
    for (int i = startX; i <= endX && i < (int) info->height; ++i) {
        for (int j = startY; j <= endY && j < (int) info->width; ++j) {
            if (j >= 0 && i >= 0 && j - startY < height &&i - startX < width) {
                int one = j - startY, two = i - startX;
                data[info->height - (i+1)][j] = imgCopy[height - (one+1)][width - two - 1];
            }
        }
    }
    delete[] imgCopy;
}

void Bmp::straight_angle(std::pair<int, int> leftUp, std::pair<int, int> rightDown) {
    Rgb **imgCopy = copy(this->data, leftUp, rightDown, info);
    int height = rightDown.second - leftUp.second, width = rightDown.first - leftUp.first;
    std::pair<int, int> center = {(rightDown.first + leftUp.first + 1) / 2, (rightDown.second + leftUp.second + 1) / 2};
    int startX = std::max(center.first - (width + 1) / 2, 0), endX = std::max(center.first + width / 2, 0),
            startY = std::max(center.second - (height + 1) / 2, 0), endY = std::max(center.second + height / 2, 0);
    for (int i = startX; i <= endX && i < info->width; ++i)
        for (int j = startY; j <= endY && j <= info->height; ++j)
            if (i - startX >= 0 && j - startY >= 0 && j - startY < height && i - startX < width) {
                data[info->height - j - 1][i] = imgCopy[j - startY][width - (i - startX) - 1];
            }
    delete[] imgCopy;
}

void Bmp::field_right_and_straight_angle(std::pair<int, int> leftUp,
                                         std::pair<int, int> rightDown) { //do it to rotate about center
    Rgb **imgCopy = copy(this->data, leftUp, rightDown, info);
    int height = rightDown.second - leftUp.second, width = rightDown.first - leftUp.first;
    std::pair<int, int> center = {(rightDown.first + leftUp.first) / 2, (rightDown.second + leftUp.second) / 2};
//    std::cout << height << " " << width << " " << center.first << " " << center.second << std::endl;
//    std::cout<<center.second - width / 2 << " " << center.first - height / 2 << " " << center.first + height / 2 << " " << center.second + width / 2 << std::endl;
//    save_copy_for_check(data, leftUp, rightDown, info, header);
//    std::cout<<width << " " << height << std::endl;
    int startX = center.second - width / 2, endX = center.second + width / 2;
    int startY = center.first  - height / 2, endY = center.first  + height / 2;
//    std::cout<<startX << " " << endX << std::endl; std::cout<<startY << " " << endY << std::endl;
    for (int i = startX; i <= endX && i < (int) info->height; ++i) {
        for (int j = startY; j <= endY && j < (int) info->width; ++j) {
            if (j >= 0 && i >= 0 && j - startY < height &&i - startX < width) {
                int one = j - startY, two = i - startX;
                data[info->height - (i+1)][j] = imgCopy[one][two];
            }
        }
    }
    delete[] imgCopy;
}

void //cut function for testing my copying
save_copy_for_check(Rgb **source, std::pair<int, int> leftUp, std::pair<int, int> rightDown, BitmapInfoHeader *info,
                    BitmapFileHeader *header) {
    int height = rightDown.second - leftUp.second, width = rightDown.first - leftUp.first;
//    height += height % 2, width += width % 2;
    Rgb **cpy = copy(source, leftUp, rightDown, info);
    std::ofstream file("test.bmp", std::ios::binary);
    BitmapFileHeader new_header = *header;
    BitmapInfoHeader new_info = *info;
    new_info.height = height, new_info.width = width;
    file.write((char *) &new_header, sizeof(BitmapFileHeader));
    file.write((char *) &new_info, sizeof(BitmapInfoHeader));
    int padding = (4 - (new_info.width * sizeof(Rgb) % 4)) % 4;
    for (size_t i = 0; i < height; i++) {
        file.write((char *) cpy[i], width * sizeof(Rgb));
        file.write((char *) "0", padding);
    }
    file.close();
}

void Bmp::check_coordinates(std::pair<int, int> &leftUp, std::pair<int, int> &rightDown) {
    if (leftUp.first > rightDown.first) std::swap(leftUp.first, rightDown.first);
    if (leftUp.second > rightDown.second) std::swap(leftUp.second, rightDown.second);
    leftUp.first < 0 ? leftUp.first = 0 : leftUp.first;
    leftUp.second < 0 ? leftUp.second = 0 : leftUp.second;
    rightDown.first < 0 ? rightDown.first = 0 : rightDown.first;
    rightDown.second < 0 ? rightDown.second = 0 : rightDown.second;
    rightDown.first > info->width - 1 ? rightDown.first = (int) info->width - 1 : rightDown.first;
    rightDown.second > info->height - 1 ? rightDown.second = (int) info->height - 1 : rightDown.second;
}

void Bmp::rotate_image(std::pair<int, int> leftUp, std::pair<int, int> rightDown, int angle) {
    this->check_coordinates(leftUp, rightDown);
    if (leftUp.first > info->width || leftUp.second > info->height || rightDown.first <= 0 || rightDown.second <= 0)
        return;
    switch (angle) {
        case (90):
            if (leftUp.first < 1 && leftUp.second < 1 && rightDown.first >= info->width - 1 &&
                rightDown.second >= info->height - 1) {
                this->full_right_angle();
                return;
            } else {
//                save_copy_for_check(data, leftUp, rightDown, info, header);
                this->field_right_angle(leftUp, rightDown);
                return;
            }
        case (180): {
            this->straight_angle(leftUp, rightDown);
            return;
        }
        case (270):
            if (leftUp.first < 1 && leftUp.second < 1 && rightDown.first >= info->width - 1 &&
                rightDown.second >= info->height - 1) {
                this->straight_angle(leftUp, rightDown);
                this->full_right_angle();
                return;
            } else {
//                save_copy_for_check(data, leftUp, rightDown, info, header);
                this->field_right_and_straight_angle(leftUp, rightDown);
                return;
            }
        default:
            return;
    }
}
