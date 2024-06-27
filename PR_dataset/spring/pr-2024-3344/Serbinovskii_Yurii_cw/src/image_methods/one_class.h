#pragma once

#include <string>
#include "../other/structs.h"
#include <vector>
#include <iostream>

class Image
{
public:
    Image()
        : bm_data(0), bm_width(0), bm_height(0) {}
    
    void readBMP(std::string & path, std::string & function_to_run);
    void exportBMP(std::string & path);

    int check_cords(int x, int y)
    {
        if (x < bm_width && y < bm_height && y >= 0 && x >= 0)
        {
            return 1;
        }
        return 0;
    }
    void rectangle(Rectangle & rect);
    void circle(Circle & circ);
    void rotate(Rotate & rot);
    void ornament(Ornament & orn);
    void something(Smth & smth);
    void line(int x1, int y1, int x2, int y2, Color color, int thickness);

    unsigned long width() {return bm_width;}
    unsigned long height() {return bm_width;}
private:
    std::vector<std::vector<Color>> bm_data;

    
    FileHeader fileHeader;
    InfoHeader infoHeader;
    
    uint32_t bm_width;
    uint32_t bm_height;
    

};
