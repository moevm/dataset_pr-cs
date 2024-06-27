#include "one_class.h"
#include <unordered_map>
#include "../other/messages.h"
#include <cmath>


void Image::line(int x1, int y1, int x2, int y2, Color color, int thickness)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    Circle circ = {{x2, y2}, thickness / 2, 1, color, false, color};
    circle(circ);

    while(x1 != x2 || y1 != y2) 
   {
        circ.center = {x1, y1};
        circle(circ);
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void Image::rectangle(Rectangle & rect)
{
    int x1 = rect.left_up[0] < rect.right_down[0] ? rect.left_up[0] : rect.right_down[0];
    int x2 = rect.left_up[0] < rect.right_down[0] ? rect.right_down[0] : rect.left_up[0];
    int y1 = rect.left_up[1] < rect.right_down[1] ? rect.left_up[1] : rect.right_down[1];
    int y2 = rect.left_up[1] < rect.right_down[1] ? rect.right_down[1] : rect.left_up[1];

    for (int y = y1 + rect.thickness / 2; y <= y2 - rect.thickness / 2; y++)
    {
        for (int x = x1 + rect.thickness / 2; x <= x2 - rect.thickness / 2; x++)
        {
            if (y >= 0 && y < bm_height && x >= 0 && x < bm_width)
            {
                bm_data[y][x] = rect.fill_color;
            }
        }
    }

    line(x1, y1, x1, y2, rect.color, rect.thickness); //право
    line(x2, y1, x2, y2, rect.color, rect.thickness); //лево
    line(x1, y1, x2, y1, rect.color, rect.thickness); //верх
    line(x1, y2, x2, y2, rect.color, rect.thickness); //низ


}

void Image::circle(Circle & circ)
{
    int xc = circ.center[0];
    int yc = circ.center[1];
    int x1 = xc - circ.radius, x2 = xc + circ.radius, y1 = yc - circ.radius, y2 = yc + circ.radius;

    if (circ.fill == 1)
    {
        for (int y = y1; y <= y2; y++)
        {
            for (int x = x1; x <= x2; x++)
            {
                if ((y - yc)*(y - yc) + (x - xc)*(x - xc) <= circ.radius*circ.radius && check_cords(x, y)) {
                    bm_data[y][x] = circ.fill_color;
                }
            }
        }
    }

    for (int k = -circ.thickness / 2 - circ.thickness % 2; k <= circ.thickness / 2 + circ.thickness % 2; k++)
    {
        int x = 0;
        int r = circ.radius + k;
        int y = r;
        int d = 1 - 2 * r;
        int error = 0;

        while (y >= 0) {
            if (check_cords(xc + x, yc + y)) //вторая четверть
            {
                bm_data[yc + y][xc + x] = circ.color;   
            }
            if (check_cords(xc + x, yc + y - 1) && (check_cords(xc + x, yc + y - 2) && bm_data[yc + y - 2][xc + x] == circ.color))
            {
                bm_data[yc + y - 1][xc + x] = circ.color;
            }
            if (check_cords(xc + x, yc - y)) //первая четверть
            {
                bm_data[yc - y][xc + x] = circ.color;
            }
            if (check_cords(xc + x, yc - y + 1) && check_cords(xc + x, yc - y + 2) && bm_data[yc - y + 2][xc + x] == circ.color)
            {
                bm_data[yc - y + 1][xc + x] = circ.color;
            }
            if (check_cords(xc - x, yc + y)) //третья четрверть
            {
                bm_data[yc + y][xc - x] = circ.color;
            }
            if (check_cords(xc - x, yc + y - 1) && check_cords(xc - x, yc + y - 2) && bm_data[yc + y - 2][xc - x] == circ.color)
            {
                bm_data[yc + y - 1][xc - x] = circ.color;
            }
            if (check_cords(xc - x, yc - y)) //четвертая четверть
            {
                bm_data[yc - y][xc - x] = circ.color;
            }
            if (check_cords(xc - x, yc - y + 1) && (check_cords(xc - x, yc - y + 2) && bm_data[yc - y + 2][xc - x] == circ.color))
            {
                bm_data[yc - y + 1][xc - x] = circ.color;
            }
            error = 2 * (d + y) - 1;
            if (d < 0 && error <= 0)
            {
                ++x;
                d += 2 * x + 1;
                continue;
            }
            if(d > 0 && error > 0) {
                --y;
                d += 1 - 2 * y;
                continue;
		    }
             ++x;
            d += 2 * (x - y);
            --y;
        }
        
    }

}


void Image::rotate (Rotate & rot) 
{
    rot.left_up[0] = rot.left_up[0] >= bm_width ? bm_width - 1 : rot.left_up[0];
    rot.left_up[1] = rot.left_up[1] >= bm_height ? bm_height - 1 : rot.left_up[1];
    rot.right_down[0] = rot.right_down[0] >= bm_width ? bm_width - 1 : rot.right_down[0];
    rot.right_down[1] = rot.right_down[1] >= bm_height ? bm_height - 1 : rot.right_down[1];

    if (rot.left_up[0] > rot.right_down[0])
    {
        int tmp = rot.left_up[0];
        rot.left_up[0] = rot.right_down[0];
        rot.right_down[0] = tmp;
    }
    if (rot.left_up[1] > rot.right_down[1])
    {
        int tmp = rot.left_up[1];
        rot.left_up[1] = rot.right_down[1];
        rot.right_down[1] = tmp;
    }
    int x1 = rot.left_up[0];
    int y1 = rot.left_up[1];
    int x2 = rot.right_down[0];
    int y2 = rot.right_down[1];


    int h = y2 - y1;
    int w = x2 - x1;


    int p1 = abs(w - h) % 2 == 0 ? abs(w - h) / 2 : (abs(w - h) / 2) + 1;

    std::vector<std::vector<Color>> temp(w, std::vector<Color>(h));
    if (rot.angle == 90)
    {
        int xn, yn;

        xn = w >= h ? p1 + x1 : x1 - p1;
        yn = w >= h ? y1 - p1 : y1 + p1;
        
        if (w % 2 == 1 && h % 2 == 0 && w > h)
        {
            xn--;
            yn++;
        }
        else if (w % 2 == 0 && h % 2 == 1 && h > w)
        {
            xn++;
            yn--;
        }


        for (int i = 0; i < w; i++) 
        {
            for (int j = 0; j < h; j++)
            {
                if (check_cords(x2 - i - 1, y1 + j))
                {
                    temp[i][j] = bm_data[y1 + j][x2 - i - 1];
                }
            }
        }
        for (int i = 0; i < w; i++) 
        {
            for (int j = 0; j < h; j++)
            {
                
                if (check_cords(xn + j, yn + i))
                {
                    bm_data[yn+i][xn+j] = temp[i][j];
                }
            }
        }
        
        
    }
    else if (rot.angle == 270)
    {
        int xn, yn;
        
        xn = w >= h ? p1 + x1 : x1 - p1;
        yn = w >= h ? y1 - p1 : y1 + p1;

        if (w % 2 == 1 && h % 2 == 0 && w > h)
        {
            xn--;
            yn++;
        }
        else if (w % 2 == 0 && h % 2 == 1 && h > w)
        {
            xn++;
            yn--;
        }

        for (int i = 0; i < w; i++) 
        {
            for (int j = 0; j < h; j++)
            {
                if (check_cords(x1 + i, y2 - j - 1))
                {
                    temp[i][j] = bm_data[y2 - j - 1][x1 + i];
                }
            }
        }
        
        for (int i = 0; i < w; i++) 
        {
            for (int j = 0; j < h; j++)
            {
                
                if (check_cords(xn + j, yn + i))
                {
                    bm_data[yn + i][xn + j] = temp[i][j];
                }
            }
        }
    
    }
    else if (rot.angle == 180)
    {
        std::vector<std::vector<Color>> tmp(h, std::vector<Color>(w));
        for (int y = 0; y < h; y++) 
        {
            for (int x = 0; x < w; x++)
            {
                if (check_cords(x2 - x - 1, y1 + y))
                {
                    tmp[y][x] = bm_data[y1 + y][x2 - x - 1];
                }
            }
        }
        for (int y = 0; y < tmp.size() / 2; y++)
        {
            std::swap(tmp[y], tmp[tmp.size() - y - 1]);
        }
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                if (check_cords(x1 + x, y1 + y))
                {
                    bm_data[y1 + y][x1 + x] = tmp[y][x];
                }
            }
        }
    }
}

void Image::ornament(Ornament & orn)
{
    if (orn.pattern == "circle")
    {
        double xc = bm_width / 2;
        double yc = bm_height / 2;
        double rad = yc > xc ? xc : yc;

        std::array<double, 2> center{xc, yc};
        for (int y = 0; y < bm_height; y++)
        {
            for (int x = 0; x < bm_width; x++) 
            {
                double hyp = pow(pow(center[0] - x, 2.0) + pow(center[1] - y, 2.0), 0.5);
                if (hyp > rad)
                {
                    bm_data[y][x] = orn.color;
                }
            }
        }
    }
    else if (orn.pattern == "rectangle")
    {
        Rectangle rect{{0, static_cast<int>(bm_height - 1)}, {static_cast<int>(bm_width - 1), 0}, orn.thickness, orn.color, false};
        int y1 = -1;
        int x1 = -1;
        int y2 = bm_height;
        int x2 = bm_width;
        for (int k = 0; k < orn.count; k++)
        {
            for (int i = 0; i < orn.thickness; i++)
            {
                y1++, x1++, y2--, x2--;
                for (int y = y1; y <= y2; y++) {
                    if (check_cords(x1, y)){
                        bm_data[y][x1] = rect.color; //лево
                    }

                    if (check_cords(x2, y)){
                        bm_data[y][x2] = rect.color; //право
                    }
                }


                for (int x = x1; x <= x2; x++) {
                    if (check_cords(x, y1))
                    {
                        bm_data[y1][x] = rect.color; //верх
                    }
                    if (check_cords(x, y2)) {
                        bm_data[y2][x] = rect.color; //низ
                    }
                }
            }
            
            x1 += orn.thickness;
            y1 += orn.thickness;
            x2 -= orn.thickness;
            y2 -= orn.thickness;
            if (x2 < 0 || y2 < 0)
            {
                std::cerr << "Oops, too much rectangles, but it's ok" << std::endl;
                break;
            }
        }
    }

    else if (orn.pattern == "semicircles")
    {
        int wd = bm_width / orn.count;
        int hd = bm_height / orn.count;
        Circle circ({wd / 2, static_cast<int>(bm_height - 1)}, wd / 2, orn.thickness, orn.color, false, {0,0,0});
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[0] += wd + 1;            
        }
        circ.center = {wd / 2, 0};
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[0] += wd + 1;
        }
        circ.center = {0, hd / 2};
        circ.radius = hd / 2;
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[1] += hd + 1;
        }
        circ.center = {static_cast<int>(bm_width - 1), hd / 2};
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[1] += hd + 1;

        }
    }
}

void Image::something(Smth & smth)
{

    std::vector<std::vector<Color>> tmp(bm_height + 2 * smth.thickness, std::vector<Color>(bm_width + smth.thickness * 2));

    for (int y = 0; y < tmp.size(); y++)
    {
        for (int x = 0; x < tmp[0].size(); x++)
        {
            tmp[y][x] = smth.color;
        }
    }

    for (int y = 0; y < bm_height; y++)
    {
        for (int x = 0; x < bm_width; x++)
        {
            tmp[smth.thickness + y][smth.thickness + x] = bm_data[y][x];
        }
    }
    bm_data = std::move(tmp);
}