#include "../headers/drawing_funcs.hpp"

void Bmp::draw_rectangle(std::pair<int, int> leftUp, std::pair<int, int> rightDown, unsigned int thickness,
                         const char *color, bool fill, const char *fillColor) {
    if (rightDown.first < leftUp.first) std::swap(leftUp.first, rightDown.first);
    if (rightDown.second < leftUp.second) std::swap(leftUp.second, rightDown.second);
//    leftUp.first < 0 ? leftUp.first = 0 : leftUp.first;
//    leftUp.second < 1 ? leftUp.second = 1 : leftUp.second;
    int r, g, b;
    if (sscanf(color, "%3d.%3d.%3d", &r, &g, &b) != 3 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        std::cout << "Wrong color format" << std::endl;
        exit(40);
    }
    int yMax = (int) info->height - leftUp.second - 1, xMax = rightDown.first,
            yMin = (int) info->height - rightDown.second - 1, xMin = leftUp.first;
    if (fill) {
        int fillR, fillG, fillB;
        if (sscanf(fillColor, "%3d.%3d.%3d", &fillR, &fillG, &fillB) != 3 || fillR < 0 || fillR > 255 || fillG < 0 ||
            fillG > 255 || fillB < 0 || fillB > 255) {
            std::cout << "Wrong fill color format" << std::endl;
            exit(40);
        }
        for (int i = xMin; i <= xMax; i++) {
            for (int j = yMin; j <= yMax; j++) {
                if (i >= 0 && j >= 0 && i < info->width && j < info->height)
                    swapRgb(&data[j][i], fillR, fillG, fillB);
            }
        }
    }
    int m = (int) (thickness / 2), n;
    thickness % 2 ? n = m : n = m - 1;
    for (int i = xMin; i < xMax; i++) {
        for (int j = 0; j <= m; j++) {
            if (i >= 0 && i < info->width && yMax - j >= 0 && yMax - j < info->height)
                swapRgb(&data[yMax - j][i], r, g, b);
            if (i >= 0 && i < info->width && yMin + j >= 0 && yMin + j < info->height)
                swapRgb(&data[yMin + j][i], r, g, b);
        }
        for (int j = 0; j <= n; j++) {
            if (i >= 0 && i < info->width && yMax + j >= 0 && yMax + j < info->height)
                swapRgb(&data[yMax + j][i], r, g, b);
            if (i >= 0 && i < info->width && yMin - j >= 0 && yMin - j < info->height)
                swapRgb(&data[yMin - j][i], r, g, b);
        }
    }
    draw_circle(leftUp, n, 1, color, true, color);
    draw_circle(rightDown, n, 1, color, true, color);
    draw_circle(std::make_pair(leftUp.first, rightDown.second), n, 1, color, true, color);
    draw_circle(std::make_pair(rightDown.first, leftUp.second), n, 1, color, true, color);
    for (int i = yMin; i < yMax; i++) {
        for (int j = 0; j <= m; j++) {
            if (i >= 0 && i < info->height && xMin + j >= 0 && xMin + j < info->width)
                swapRgb(&data[i][xMin + j], r, g, b);
            if (i >= 0 && i < info->height && xMax - j >= 0 && xMax - j < info->width)
                swapRgb(&data[i][xMax - j], r, g, b);
        }
        for (int j = 0; j <= n; j++) {
            if (i >= 0 && i < info->height && xMin - j >= 0 && xMin - j < info->width)
                swapRgb(&data[i][xMin - j], r, g, b);
            if (i >= 0 && i < info->height && xMax + j >= 0 && xMax + j < info->width)
                swapRgb(&data[i][xMax + j], r, g, b);
        }
    }
}

void Bmp::draw_circle(std::pair<int, int> center, unsigned int radius, unsigned int thickness, const char *color,
                      bool fill, const char *fillColor) {
    int xMax = (int) info->width, yMax = (int) info->height, r, g, b, fillR, fillG, fillB;
    if (sscanf(color, "%3d.%3d.%3d", &r, &g, &b) != 3 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        std::cout << "Wrong color format" << std::endl;
        exit(40);
    }
    if (fill) {
        if (sscanf(fillColor, "%3d.%3d.%3d", &fillR, &fillG, &fillB) != 3 || fillR < 0 || fillR > 255 || fillG < 0 ||
            fillG > 255 || fillB < 0 || fillB > 255) {
            std::cout << "Wrong fill color format" << std::endl;
            exit(40);
        }
    }
//    clock_t start = clock();
    int startX = center.first - (int) radius - (int) thickness / 2,
            endX = center.first + (int) radius + (int) thickness / 2 + 1,
            startY = center.second - (int) radius - (int) thickness / 2,
            endY = center.second + (int) radius + (int) thickness / 2 + 1;
    for (int i = startX; i < endX; i++)
        for (int j = startY; j < endY; j++) {
            const double dist =
                    (double) (center.first - i) * (center.first - i) + (center.second - j) * (center.second - j);
            if (i >= 0 && j >= 0 && i < xMax && j < yMax) {
                if (fill && dist < radius * radius) swapRgb(&data[yMax - j - 1][i], fillR, fillG, fillB);
                if (sqrt(dist) <= (radius + thickness / 2.0) && sqrt(dist) >= ((int) radius - (int) thickness / 2.0))
                    swapRgb(&data[yMax - j - 1][i], r, g, b);
            }
        }
}

void Bmp::drawOrnament(const char *pattern, const char *color, size_t thickness, size_t count) {
    int r, g, b, k = 0;
    if (sscanf(color, "%3d.%3d.%3d", &r, &g, &b) != 3 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        std::cout << "Wrong color format" << std::endl;
        exit(40);
    };
    if (strcmp(pattern, "rectangle") == 0) {
        2 * thickness > std::max(info->height, info->width) ? thickness = std::max(info->height, info->width) / 2
                                                            : thickness;
        (count + count - 1) * thickness > std::min(info->height / 2, info->width / 2) ?
                count = (std::min(info->height / 2, info->width / 2) / 2 - 1) / (thickness) + 1 : count;
        while (k < 2 * count) {
            for (size_t i = 0; i < info->height - 2 * k * thickness; i++)
                for (size_t j = 0; j < thickness; j++) {
                    swapRgb(&data[i + k * thickness][j + k * thickness], r, g, b);
                    swapRgb(&data[i + k * thickness][info->width - k * thickness - j - 1], r, g, b);
                }
            for (size_t i = 0; i < info->width - 2 * k * thickness; i++)
                for (size_t j = 0; j < thickness; j++) {
                    swapRgb(&data[info->height - 1 - j - k * thickness][i + k * thickness], r, g, b);
                    swapRgb(&data[j + k * thickness][i + k * thickness], r, g, b);
                }
            k += 2;
        }
    } else if (strcmp(pattern, "circle") == 0) {
        size_t radius = std::min(info->height / 2, info->width / 2);
        std::pair<size_t, size_t> center = {info->width / 2, info->height / 2};
        for (int i = 0; i < info->width; i++) {
            for (int j = 0; j < info->height; j++) {
                if ((center.first - i) * (center.first - i) + (center.second - j) * (center.second - j) >=
                    radius * radius)
                    swapRgb(&data[j][i], r, g, b);
            }
        }
    } else if (strcmp(pattern, "semicircles") == 0) {
        size_t radiusX = ceil((double) info->width / (2.0 * (double) count));
        size_t radiusY = ceil((double) info->height / (2 * (double) count));
        char col[12];
        sprintf(col, "%d.%d.%d", r, g, b);
        for (size_t i = radiusY;
             i < info->height + 2 * radiusY + thickness; i += 2 * (radiusY)) {
            draw_circle(std::pair<int, int>(0, i), radiusY, thickness, col, false, nullptr);
            draw_circle(std::pair<int, int>(info->width - 1, i), radiusY, thickness, col, false, nullptr);
        }
        for (size_t i = radiusX;
             i < info->width + 2 * radiusX + thickness; i += 2 * (radiusX)) {
            draw_circle(std::pair<int, int>(i, 0), radiusX, thickness, col, false, nullptr);
            draw_circle(std::pair<int, int>(i, info->height - 1), radiusX, thickness, col, false, nullptr);
        }
    } else if (strcmp(pattern, "koch") == 0) {
        thickness > std::min(info->width - 9, info->height - 9) ? thickness = std::min(info->width, info->height) - 9: thickness;
        int x1 = (int) 10 + thickness;
        int y1 = (int) info->height - 9 - thickness;
        int x2 = info->width - (int) 9 - thickness;
        int y2 = (int) 10 + thickness;
        koch(x1, y2, x1, y1 / 3, thickness, color, count, 1);
        koch(x1, y1 / 3, x1, y1 * 2 / 3, thickness, color, count, 1);
        koch(x1, y1 * 2 / 3, x1, y1, thickness, color, count, 1);
        koch(x2, y2, x2, y1 / 3, thickness, color, count, -1);
        koch(x2, y1 / 3, x2, y1 * 2 / 3, thickness, color, count, -1);
        koch(x2, y1 * 2 / 3, x2, y1, thickness, color, count, -1);
        koch(x1, y2, x2 / 3, y2, thickness, color, count, -1);
        koch(x2 / 3, y2, x2 * 2 / 3, y2, thickness, color, count, -1);
        koch(x2 * 2 / 3, y2, x2, y2, thickness, color, count, -1);
        koch(x1, y1, x2 / 3, y1, thickness, color, count, 1);
        koch(x2 / 3, y1, x2 * 2 / 3, y1, thickness, color, count, 1);
        koch(x2 * 2 / 3, y1, x2, y1, thickness, color, count, 1);
    }
}

void Bmp::koch(int x1, int y1, int x2, int y2, unsigned int thickness, const char *color, int count, int i) {
    int x21 = (int) (x1 + (x2 - x1) / 3), y21 = (int) (y1 + (y2 - y1) / 3);
    double l = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double h = (l / (sqrt(3) * 2.0));
    int x22 = (x2 + x1) / 2 + (int) (i * h * (y2 - y1) / l), y22 = (y1 + y2) / 2 - (int) (i * h * (x2 - x1) / l);
    int x23 = (int) (x1 + 2 * (x2 - x1) / 3), y23 = (int) (y1 + 2 * (y2 - y1) / 3);
    if (count == 0 || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x21 < 0 || y21 < 0 || x22 < 0 || y22 < 0 || x23 < 0 ||
        y23 < 0) {
        draw_line(std::make_pair(x1, y1), std::make_pair(x2, y2), thickness, color);
        return;
    }
    koch(x21, y21, x22, y22, thickness, color, count - 1, i);
    koch(x22, y22, x23, y23, thickness, color, count - 1, i);
    koch(x1, y1, x21, y21, thickness, color, count - 1, i);
    koch(x23, y23, x2, y2, thickness, color, count - 1, i);
}

void Bmp::fill_circle(std::pair<int, int> center, int radius, const char *color) {
    int fillR, fillG, fillB;
    if (sscanf(color, "%3d.%3d.%3d", &fillR, &fillG, &fillB) != 3 || fillR < 0 || fillR > 255 || fillG < 0 ||
        fillG > 255 || fillB < 0 || fillB > 255) {
        std::cout << "Wrong fill color format" << std::endl;
        exit(40);
    }
    for (int i = std::max(0, center.first - radius); i < std::min(center.first + radius + 1, (int) info->width); ++i) {
        for (int j = std::max(0, center.second - radius); j < std::min(center.second + radius + 1, (int) info->height); ++j) {
            if ((i - center.first) * (i - center.first) + (j - center.second) * (j - center.second) <= radius * radius) {
                swapRgb(&data[info->height - j - 1][i], fillR, fillG, fillB);
            }
        }
    }
}

void
Bmp::draw_line(std::pair<int, int> leftUp, std::pair<int, int> rightDown, unsigned int thickness, const char *color) {
//    leftUp.first < 0 ? leftUp.first = 0 : leftUp.first; // remove that useless checks if you will draw on image
//    leftUp.second < 0 ? leftUp.second = 0 : leftUp.second;
//    rightDown.first < 0 ? rightDown.first = 0 : rightDown.first;
//    rightDown.second < 0 ? rightDown.second = 0 : rightDown.second;
    int r, g, b, x1 = leftUp.first, x2 = rightDown.first, y1 = leftUp.second, y2 = rightDown.second;
    if (sscanf(color, "%3d.%3d.%3d", &r, &g, &b) != 3 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        std::cout << "Wrong color format" << std::endl;
        exit(40);
    };
    const int dx = std::abs(x2 - x1);
    const int dy = std::abs(y2 - y1);
    const int signX = x2 > x1 ? 1 : -1;
    const int signY = y2 > y1 ? 1 : -1;
    uint32_t radius = thickness / 2;
    int err = dx - dy;
    fill_circle(std::make_pair(x2,y2),(int) radius, color);
//    draw_circle(std::pair<int, int>(x2, y2), radius, 1, color, true, color); //change thickness to 0
    while (x1 != x2 || y1 != y2) {
        fill_circle(std::make_pair(x1,y1),(int) radius, color);
//        draw_circle(std::pair<int, int>(x1, y1), radius, 1, color, true, color); //change thickness to 0
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += signX;
        }
        if (e2 < dx) {
            err += dx;
            y1 += signY;
        }
    }
}

void Bmp::draw_snowflake(std::pair<int, int> leftUp, std::pair<int, int> rightDown, unsigned int thickness,
                         const char *color, int count) {
    int x1 = (int) (rightDown.first - leftUp.first + 1) / 2, y1 = leftUp.second, y2 = rightDown.second;
    y2 -= (int) ((y2 - y1 + 1) * sqrt(3) / 6);
    int y3 = y2;
    int x2 = x1 - (int) (sqrt(3) * (y2 - y1 + 1) / 4), x3 = x1 + (int) (sqrt(3) * (y2 - y1 + 1) / 4);
    koch(x1, y1, x2, y2, thickness, color, count, -1);
    koch(x2, y2, x3, y3, thickness, color, count, -1);
    koch(x3, y3, x1, y1, thickness, color, count, -1);
}