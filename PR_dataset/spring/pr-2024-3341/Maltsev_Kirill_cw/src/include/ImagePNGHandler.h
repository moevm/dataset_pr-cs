/**
 * @file FlagsHandler.h
 * @brief Header with a description of the ImageHandler class and other structures to work with launch flags
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef IMAGE_PNG_HANDLER_H
#define IMAGE_PNG_HANDLER_H

#include "ImageEditor.h"
#include <string>

/**
 * @brief Class for working with PNG image
 * 
 */
class ImagePNGHandler
{
public:

    /**
     * @brief Construct a new ImagePNGHandler object
     * 
     */
    ImagePNGHandler();
    

    /**
     * @brief Destroy the ImagePNGHandler object
     * 
     */
    ~ImagePNGHandler() = default;


    /**
     * @brief Get the ImagePNG object
     * 
     * @return ie::ImagePNG& the processed PNG image 
     */
    ie::ImagePNG& getImagePNG();


    /**
     * @brief Reads an image from the input file and outputs basic information about it
     * 
     * @param[in] input_file_name 
     */
    void showImageInfo(std::string input_file_name);
    

    /**
     * @brief Reads the image from the input file, draws a circle on it and outputs the image to the output file
     * 
     * @param[in] input_file_name 
     * @param[in] output_file_name 
     * @param[in] x0 
     * @param[in] y0 
     * @param[in] radius 
     * @param[in] thickness 
     * @param[in] color 
     * @param[in] fill 
     * @param[in] fill_color 
     */
    void drawCircle(std::string input_file_name, std::string output_file_name,
        int x0, int y0, int radius, int thickness, ie::ColorRGBA color, bool fill, ie::ColorRGBA fill_color);
    
    /**
     * @brief Reads the image from the input file, aplyes rgb fileter on it and outputs the image to the output file
     * 
     * @param[in] input_file_name 
     * @param[in] output_file_name 
     * @param[in] component_idx 
     * @param[in] component_value 
     */
    void aplyRGBFilterOnImage(std::string input_file_name, std::string output_file_name, 
        int component_idx, int component_value);
    
    /**
     * @brief Reads the image from the input file, splits it into n*m parts and outputs the image to the output file
     * 
     * @param[in] input_file_name 
     * @param[in] output_file_name 
     * @param[in] number_x 
     * @param[in] number_y 
     * @param[in] thickness 
     * @param[in] color 
     */
    void SplitImage(std::string input_file_name, std::string output_file_name, 
        int number_x, int number_y, int thickness, ie::ColorRGBA color);
    
    /**
     * @brief Reads the image from the input file, draws a square with diagonals and outputs the image to the output file
     * 
     * @param[in] input_file_name 
     * @param[in] output_file_name 
     * @param[in] left 
     * @param[in] up 
     * @param[in] side_size 
     * @param[in] thickness 
     * @param[in] color 
     * @param[in] fill 
     * @param[in] fill_color 
     */
    void drawSquaredLines(std::string input_file_name, std::string output_file_name, 
        int left, int up, int side_size, int thickness, ie::ColorRGBA color, bool fill, ie::ColorRGBA fill_color);
    
    /**
     * @brief Reads the image from the input file, draws a frame around the image and outputs the image to the output file
     * 
     * @param[in] input_file_name 
     * @param[in] output_file_name 
     * @param[in] thickness 
     * @param[in] color 
     */
    void drawOutsideOrnament(std::string input_file_name, std::string output_file_name, 
        int thickness, ie::ColorRGBA color);

private:
    ie::ImagePNG image_png_; // the processed PNG image
};

#endif