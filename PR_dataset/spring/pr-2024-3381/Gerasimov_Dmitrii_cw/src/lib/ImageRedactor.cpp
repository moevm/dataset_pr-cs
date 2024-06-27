#include "../include/ImageRedactor.hpp"

ImageRedactor::ImageRedactor(ImageReader &image) : image(image) {}

void ImageRedactor::copy(Vector2i left_up, Vector2i right_down, Vector2i dest)
{
    if (left_up.x > right_down.x || left_up.y > right_down.y)
        throw std::runtime_error("Wrong area to copy");
    auto buf{std::make_unique<Color[]>((right_down.x - left_up.x + 2) *
                                       (right_down.y - left_up.y + 2))};
    size_t cnt = 0;
    for (int64_t i = left_up.x; i <= right_down.x; i++)
    {
        for (int64_t j = left_up.y; j <= right_down.y; j++)
        {
            buf[cnt++] = image.get_pixel({i, j});
        }
    }
    cnt = 0;
    for (int64_t i = dest.x; i <= dest.x + (right_down.x - left_up.x); i++)
    {
        for (int64_t j = dest.y; j <= dest.y + (right_down.y - left_up.y); j++)
        {
            image.put_pixel({i, j}, buf[cnt++]);
        }
    }
}

void ImageRedactor::replace(Color color_old, Color color_new)
{
    for (int64_t i = 0; i < image.get_size().x; i++)
    {
        for (int64_t j = 0; j < image.get_size().y; j++)
        {
            if (image.get_pixel({i, j}) == color_old)
                image.put_pixel({i, j}, color_new);
        }
    }
}

void ImageRedactor::draw(Drawable &obj)
{
    obj.draw(image);
}

void ImageRedactor::ornament(OrnametType t, int64_t count, int64_t thickness,
                             Color color)
{
    switch (t)
    {
        case OrnametType::rectangle:
            draw_rect(count, thickness, color);
            break;
        case OrnametType::circle:
            draw_circle(color);
            break;
        case OrnametType::semicircles:
            draw_semicircles(count, thickness, color);
            break;
        default:
            break;
    }
}

void ImageRedactor::draw_semicircles(int64_t count, int64_t thickness,
                                     Color color)
{
    auto [dx, dy] = image.get_size();
    dx = dx % count == 0 ? dx / count : (int64_t(dx / count) + 1);
    dy = dy % count == 0 ? dy / count : (int64_t(dy / count) + 1);
    int64_t r1 = dx % 2 == 0 ? (dx) / 2 : (dx - 1) / 2;
    int64_t r2 = dy % 2 == 0 ? (dy) / 2 : (dy - 1) / 2;
    Vector2i p1{r1, 0};
    Vector2i p2{0, r2};
    for (size_t i = 0; i < count; i++)
    {
        Circle c(p1, r1, color, thickness);
        draw(c);
        Circle c1(p1 + Vector2i{0, image.get_size().y}, r1, color, thickness);
        draw(c1);
        Circle c2(p2, r2, color, thickness);
        draw(c2);
        Circle c21(p2 + Vector2i{image.get_size().x, 0}, r2, color, thickness);
        draw(c21);
        p1.x += dx;
        p2.y += dy;
    }
}

void ImageRedactor::draw_rect(int64_t count, int64_t thickness, Color color)
{
    // int64_t r = thickness % 2 == 0 ? (thickness) / 2 : (thickness - 1) / 2;
    Vector2i p1{thickness, thickness},
        p2{image.get_size() - Vector2i{thickness + 1, thickness + 1}};

    for (size_t i = 0; i < count; i++)
    {
        Rectangle rect(p1, p2, color, thickness);
        draw(rect);
        p1 = p1 + Vector2i{thickness, thickness} * 2;
        p2 = p2 - Vector2i{thickness, thickness} * 2;
    }
}

void ImageRedactor::draw_circle(Color color)
{
    auto [cx, cy] = image.get_size();
    cx = cx % 2 == 0 ? (cx) / 2 : (cx - 1) / 2;
    cy = cy % 2 == 0 ? (cy) / 2 : (cy - 1) / 2;
    Circle c({cx, cy},
             (cx < cy ? cx : cy) +
                 ((cx + cy) % 2 == 0 ? (cx + cy) / 2 : ((cx + cy) - 1) / 2),
             color, cx + cy);
    draw(c);
}

int64_t ImageRedactor::check_line(Vector2i pos, Vector2i offset,
                                  Vector2i offset_to_c, Color color)
{
    int64_t res = 0;
    for (; image.get_pixel(pos + offset * res, color == Color::Black
                                                   ? Color::White
                                                   : Color::Black) == color &&
           image.get_pixel(pos + offset * res + offset_to_c,
                           color == Color::Black ? Color::White
                                                 : Color::Black) != color;
         res++)
    {
    }
    return res;
}

void ImageRedactor::filled_rects(Color color, Color b_color, int64_t thickness)
{
    std::vector<Rectangle> rects;
    for (int64_t j = 0; j < image.get_size().y; j++)
    {
        for (int64_t i = 0; i < image.get_size().x; i++)
        {
            if (image.get_pixel({i, j}) == color &&
                image.get_pixel({i - 1, j}, color == Color::Black
                                                ? Color::White
                                                : Color::Black) != color &&
                image.get_pixel({i, j - 1}, color == Color::Black
                                                ? Color::White
                                                : Color::Black) != color)
            {
                int64_t a = check_line({i, j}, {1, 0}, {0, -1}, color);
                int64_t b = check_line({i, j}, {0, 1}, {-1, 0}, color);
                int64_t c = check_line({i + a - 1, j}, {0, 1}, {1, 0}, color);
                int64_t d = check_line({i, j + b - 1}, {1, 0}, {0, 1}, color);
                if (a == d && b == c)
                {
                    rects.push_back(
                        Rectangle{{i, j}, {i + a, j + b}, b_color, thickness});
                }
            }
        }
    }
    for (auto &i : rects)
    {
        draw(i);
    }
}

void ImageRedactor::rhombus(Color color){
    Line l1({image.get_size().x/2,0},{image.get_size().x-1,image.get_size().y/2},color,1);
    draw(l1);
    Line l2({image.get_size().x-1,image.get_size().y/2},{image.get_size().x/2,image.get_size().y-1},color,1);
    draw(l2);
    Line l3({image.get_size().x/2,image.get_size().y-1},{0,image.get_size().y/2},color,1);
    draw(l3);
    Line l4({0,image.get_size().y/2},{image.get_size().x/2,0},color,1);
    draw(l4);
    for(int64_t i = 1;i<image.get_size().y-1;i++){
        bool f = 0;
        for(int64_t j = 0;j<image.get_size().x;j++){
            if(image.get_pixel({j,i},Color::White==color?Color::Black:Color::White)==color){
                if(f){
                    break;
                }
                f = 1;
                image.put_pixel({j+1,i},color);
                j++;
            }else if(f){
                image.put_pixel({j,i},color);
            }
        }
    }
}
