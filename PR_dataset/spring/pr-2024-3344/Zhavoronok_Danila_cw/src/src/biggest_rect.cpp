#include "../include/biggest_rect.h"

struct Rectangle
{
    position pos;
    int width, height;
    int area()
    {
        return width * height;
    }
};

bool is_surrounded(RGB *image, int w, int h, const Rectangle &rect, const RGB &oldColor)
{
    int rows = h;
    int cols = w;

    // Check top and bottom borders
    for (int j = rect.pos.x; j < rect.pos.x + rect.width; ++j)
    {
        if (rect.pos.y > 0 && image[(rect.pos.y - 1) * w + j] == oldColor)
            return false;
        if (rect.pos.y + rect.height < rows && image[(rect.pos.y + rect.height) * w + j] == oldColor)
            return false;
    }

    // Check left and right borders
    for (int i = rect.pos.y; i < rect.pos.y + rect.height; ++i)
    {
        if (rect.pos.x > 0 && image[i * w + rect.pos.x - 1] == oldColor)
            return false;
        if (rect.pos.x + rect.width < cols && image[i * w + rect.pos.x + rect.width] == oldColor)
            return false;
    }

    return true;
}

void find_and_recolor_biggest_rect(RGB *image, int w, int h, const RGB &oldColor, const RGB &newColor)
{
    Rectangle biggest_rect = {{0, 0}, 0, 0};

    std::vector<std::vector<int>> height(h, std::vector<int>(w, 0));
    std::vector<std::vector<int>> width(h, std::vector<int>(w, 0));

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (image[i * w + j] == oldColor)
            {
                height[i][j] = (i == 0) ? 1 : height[i - 1][j] + 1;
                width[i][j] = (j == 0) ? 1 : width[i][j - 1] + 1;

                int minWidth = width[i][j];
                for (int k = 0; k < height[i][j]; ++k)
                {
                    minWidth = std::min(minWidth, width[i - k][j]);
                    int area = (k + 1) * minWidth;
                    if (area > biggest_rect.area())
                    {
                        Rectangle potential_rect = {{j - minWidth + 1, i - k}, minWidth, k + 1};
                        if (is_surrounded(image, w, h, potential_rect, oldColor))
                        {
                            biggest_rect = potential_rect;
                        }
                    }
                }
            }
        }
    }

    if (biggest_rect.area() > 0)
    {
        for (int i = biggest_rect.pos.y; i < biggest_rect.pos.y + biggest_rect.height; ++i)
        {
            for (int j = biggest_rect.pos.x; j < biggest_rect.pos.x + biggest_rect.width; ++j)
            {
                image[i * w + j] = newColor;
            }
        }
    }
}
