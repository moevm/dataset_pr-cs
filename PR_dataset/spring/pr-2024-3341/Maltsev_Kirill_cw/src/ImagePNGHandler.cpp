/**
 * @file ImagePNGHandler.cpp
 * @brief Implementation of main methods for ImagePNGHandler class (getFlags, handleFlags, ...)
 * @version 0.1.0
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ImagePNGHandler.h"
#include "ImageEditor.h"
#include <string>
#include <algorithm>


ImagePNGHandler::ImagePNGHandler() :
    image_png_()
{}

ie::ImagePNG& ImagePNGHandler::getImagePNG()
{
    return image_png_;
}

void ImagePNGHandler::showImageInfo(std::string input_file_name)
{
    image_png_.readImageFromFile(input_file_name.c_str());
    image_png_.showInfo();
}

void ImagePNGHandler::drawCircle(std::string input_file_name, std::string output_file_name,
    int x0, int y0, int radius, int thickness, ie::ColorRGBA color, bool fill, ie::ColorRGBA fill_color)
{
    image_png_.readImageFromFile(input_file_name.c_str());
    image_png_.drawCircle(x0, y0, radius, thickness, color, fill, fill_color);
    image_png_.writeImageToFile(output_file_name.c_str());
}

void ImagePNGHandler::aplyRGBFilterOnImage(std::string input_file_name, std::string output_file_name, 
    int component_idx, int component_value)
{
    image_png_.readImageFromFile(input_file_name.c_str());
    image_png_.rgbaFilter(component_idx, component_value);
    image_png_.writeImageToFile(output_file_name.c_str());
}

void ImagePNGHandler::SplitImage(std::string input_file_name, std::string output_file_name, 
    int number_x, int number_y, int thickness, ie::ColorRGBA color)
{
    image_png_.readImageFromFile(input_file_name.c_str());

    for (int y = image_png_.getHeight() / number_y; y < image_png_.getHeight(); y += std::max(1, image_png_.getHeight() / number_y)) {
        for (int i = 0; i <= thickness/2; i++) {
            image_png_.drawBresenhamLine(0, y-i, image_png_.getWidth()-1, y-i, color);
            image_png_.drawBresenhamLine(0, y+i, image_png_.getWidth()-1, y+i, color);
        }
    }
    
    for (int x = image_png_.getWidth() / number_x; x < image_png_.getWidth(); x += std::max(1, image_png_.getWidth() / number_x)) {
        for (int i = 0; i <= thickness/2; i++) {
            image_png_.drawBresenhamLine(x-i, 0, x-i, image_png_.getHeight()-1, color);
            image_png_.drawBresenhamLine(x+i, 0, x+i, image_png_.getHeight()-1, color);
        }
    }
    
    image_png_.writeImageToFile(output_file_name.c_str());
}

void ImagePNGHandler::drawSquaredLines(std::string input_file_name, std::string output_file_name, 
    int left, int up, int side_size, int thickness, ie::ColorRGBA color, bool fill, ie::ColorRGBA fill_color)
{
    image_png_.readImageFromFile(input_file_name.c_str());

    image_png_.drawPolygon(
        {
            {left, up},
            {left+side_size, up},
            {left+side_size, up+side_size},
            {left, up+side_size},
        },
        thickness, color, fill, fill_color);

    image_png_.drawLine(left, up, left+side_size, up+side_size, thickness, color);
    image_png_.drawLine(left+side_size, up, left, up+side_size, thickness, color);

    image_png_.writeImageToFile(output_file_name.c_str());
}

void ImagePNGHandler::drawOutsideOrnament(std::string input_file_name, std::string output_file_name, 
    int thickness, ie::ColorRGBA color)
{
    ie::ImagePNG image_png_src;
    image_png_src.readImageFromFile(input_file_name.c_str());

    image_png_.setSize(image_png_src.getWidth() + 2 * thickness, image_png_src.getHeight() + 2 * thickness);
    image_png_.floodFill(0, 0, color);
    image_png_.paste(image_png_src, thickness, thickness);

    image_png_.writeImageToFile(output_file_name.c_str());
}