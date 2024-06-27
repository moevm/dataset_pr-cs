
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include "include/input.h"
#include "include/utils.h"
#include "include/rgb.h"
#include "include/biggest_rect.h"
#include "include/make_collage.h"
#include "include/draw_line.h"
#include "include/draw_triangle.h"

#include <stdlib.h>
#include <string>

int main(int argc, char **argv)
{
    auto input_data = input(argc, argv);
    auto function_to_exec = get_function_to_exec(input_data);
    // std::cout << function_to_exec << '\n';

    if (function_to_exec == "help")
    {
        print_help();
        return 0;
    }

    std::string inputPath = input_data["input"].values[0];
    std::string outputPath = "output.png";
    if (contains(input_data, "output"))
    {
        outputPath = input_data["output"].values[0];
    }
    int width = 0, height = 0;
    RGB *image = reinterpret_cast<RGB *>(stbi_load(inputPath.c_str(), &width, &height, NULL, 3));
    if (width == 0 || height == 0)
    {
        throw_exception("File provided as input is not a PNG image.", 45);
    }

    if (function_to_exec == "triangle")
    {
        triangle tri = parse_input(input_data["points"].values[0], no_check, 6);
        const auto &thickness = parse_input(input_data["thickness"].values[0], check_N_val, 1);
        RGB color = parse_input(input_data["color"].values[0], check_rgb_val, 3);
        bool fill = contains(input_data, "fill");
        RGB fill_color = parse_input(contains(input_data, "fill_color") ? input_data["fill_color"].values[0] : "0.0.0", check_rgb_val, 3);

        draw_triangle(image, width, height, tri, thickness[0], color, fill, fill_color);

        stbi_write_png(outputPath.c_str(), width, height, 3, image, width * 3);
    }
    else if (function_to_exec == "biggest_rect")
    {
        const RGB oc = parse_input(input_data["old_color"].values[0], check_rgb_val, 3);
        const RGB nc = parse_input(input_data["new_color"].values[0], check_rgb_val, 3);

        find_and_recolor_biggest_rect(image, width, height, oc, nc);

        stbi_write_png(outputPath.c_str(), width, height, 3, image, width * 3);
    }
    else if (function_to_exec == "collage")
    {
        const auto &N = parse_input(input_data["number_x"].values[0], check_N_val, 1);
        const auto &M = parse_input(input_data["number_y"].values[0], check_N_val, 1);
        int cw, ch;
        RGB *collage = make_collage(image, width, height, N[0], M[0], cw, ch);
        stbi_write_png(outputPath.c_str(), cw, ch, 3, collage, cw * 3);
    }
    else if (function_to_exec == "line")
    {
        RGB color = parse_input(input_data["color"].values[0], check_rgb_val, 3);
        position start = parse_input(input_data["start"].values[0], no_check, 2);
        position end = parse_input(input_data["end"].values[0], no_check, 2);

        const auto &thickness = parse_input(input_data["thickness"].values[0], check_N_val, 1);

        draw_line(image, width, height, start, end, thickness[0], color);

        stbi_write_png(outputPath.c_str(), width, height, 3, image, width * 3);
    }
    else if (function_to_exec == "rhombus")
    {
        RGB color = parse_input(input_data["color"].values[0], check_rgb_val, 3);

        int divided_width = width / 2;
        int divided_height = height / 2;

        auto tri1 = triangle({0, divided_height}, {width - 1, divided_height}, {divided_width, 0});
        auto tri2 = triangle({0, divided_height}, {width - 1, divided_height}, {divided_width, height - 1});

        draw_triangle(image, width, height, tri1, 1, color, true, color);
        draw_triangle(image, width, height, tri2, 1, color, true, color);

        stbi_write_png(outputPath.c_str(), width, height, 3, image, width * 3);
    }

    return 0;
}
