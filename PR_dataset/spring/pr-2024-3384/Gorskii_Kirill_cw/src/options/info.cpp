#include "../options.hpp"

#include <iostream>
#include <png.h>

const char *colorTypeAsString(int color_type)
{
    switch (color_type) {
        case PNG_COLOR_TYPE_GRAY: return "grayscale";
        case PNG_COLOR_TYPE_GRAY_ALPHA: return "grayscale+alpha";
        case PNG_COLOR_TYPE_PALETTE: return "palette";
        case PNG_COLOR_TYPE_RGB: return "rgb";
        case PNG_COLOR_TYPE_RGB_ALPHA: return "rgba";
        default:
            return "unknown";
    }
}

std::string filterTypeAsString(int filter_type)
{
    std::string res = "[";

    if (filter_type & PNG_FILTER_NONE)
        res.append("none").append((res.size() == 1) ? "" : ", ");
    if (filter_type & PNG_FILTER_SUB)
        res.append("sub").append((res.size() == 1) ? "" : ", ");
    if (filter_type & PNG_FILTER_UP)
        res.append("up").append((res.size() == 1) ? "" : ", ");
    if (filter_type & PNG_FILTER_AVG)
        res.append("avg").append((res.size() == 1) ? "" : ", ");
    if (filter_type & PNG_FILTER_PAETH)
        res.append("paeth").append((res.size() == 1) ? "" : ", ");

    res += ']';
    return res;
}

const char *compressionTypeAsString(int compression_type)
{
    return (compression_type == PNG_COMPRESSION_TYPE_BASE) ? "base" : "unknown";
}

const char *interlaceTypeAsString(int interlace_type)
{
    switch (interlace_type) {
        case PNG_INTERLACE_NONE: return "none";
        case PNG_INTERLACE_ADAM7: return "adam7";
        case PNG_INTERLACE_LAST: return "last";
        default:
            return "unkown";
    }
}

void processInfoOption(Image &image, Options &opts)
{
    png_infop info = image.getLowLevelPNGInfo();
    png_structp png = image.getLowLevelPNGStruct();

    int filter_type = png_get_filter_type(png, info);
    int compression_type = png_get_compression_type(png, info);
    int interlace_type = png_get_interlace_type(png, info);

    std::cout << "IHDR:\n";
    std::cout << "\twidth: " << image.getWidth() << '\n';
    std::cout << "\theight: " << image.getHeight() << '\n';
    std::cout << "\tbit_depth: " << image.getBitDepth() << '\n';
    std::cout << "\tn_channels: " << image.getChannelsCount() << '\n';
    std::cout << "\tcolor_type: \"" << colorTypeAsString(image.getColorType()) << "\"\n";
    std::cout << "\tfilter_type: " << filterTypeAsString(filter_type) << '\n';
    std::cout << "\tcompression_type: " << compressionTypeAsString(compression_type) << '\n';
    std::cout << "\tinterlace_type: " << interlaceTypeAsString(interlace_type) << '\n';

    int palette_size;
    png_colorp palette;
    png_get_PLTE(png, info, &palette, &palette_size);
    std::cout << "PLTE:\n";
    std::cout << "\tpalette_size: " << palette_size << '\n';

    double gamma;
    png_get_gAMA(png, info, &gamma);
    std::cout << "gAMA:\n";
    std::cout << "\tgamma: " << gamma << '\n';

    png_color_8p sbit;
    png_get_sBIT(png, info, &sbit);
    std::cout << "sBIT:\n";
    std::cout << "\tbit_shift: " << sbit << '\n';

    int n_text;
    png_textp text;
    png_get_text(png, info, &text, &n_text);

    uint32_t dpi_x = png_get_x_pixels_per_inch(png, info);
    uint32_t dpi_y = png_get_y_pixels_per_inch(png, info);

    std::cout << "pHYs:\n";
    std::cout << "\tdpi_x: " << dpi_x << '\n';
    std::cout << "\tdpi_y: " << dpi_y << '\n';
}