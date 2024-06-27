#ifndef CW_IMAGE_HPP
#define CW_IMAGE_HPP

#include "utils.hpp"
#include <png.h>

class Image
{
protected:
    uint32_t width;
    uint32_t height;
    
    int bit_depth;
    int n_channels;
    int color_type;

    png_structp png_struct;
    png_infop   png_info;
    png_infop   png_endinfo;

    uint8_t **rows;

    void *getPixelAddr(vec2i coord);
    void drawThinLine(vec2i start, vec2i end, rgba32 color);

    void init();
    void deinit();
    void reset();
public:
    enum class Error {
        None,
        OpenFile,
        PNG
    };

    Image();
    ~Image();

    void load(const char *const filename);
    void save(const char *const filename);

    void   setPixel(vec2i coord, rgba32 color);
    rgba32 getPixel(vec2i coord);
    
    inline uint32_t getWidth() { return width; }
    inline uint32_t getHeight() { return height; }
    inline uint32_t getBitDepth() { return bit_depth; }
    inline uint32_t getChannelsCount() { return n_channels; }
    inline uint32_t getColorType() { return color_type; }
	inline uint8_t **getRows() { return rows; }

    inline png_structp getLowLevelPNGStruct() { return png_struct; }
    inline png_infop   getLowLevelPNGInfo()   { return png_info; }   

    void resize(uint32_t width, uint32_t height);

    void fillCircle(vec2i center, float radius, rgba32 color);
    void fillCircle(vec2f center, float radius, rgba32 color);
    void fillTriangle(vec2i p1, vec2i p2, vec2i p3, rgba32 color, float bias);
    void fillTriangle(vec2f p1, vec2f p2, vec2f p3, rgba32 color, float bias);
    void fillRect(rect2i rect, rgba32 color);
    void drawLine(vec2i start, vec2i end, rgba32 color, int thickness);
    void drawTriangle(vec2i p1, vec2i p2, vec2i p3, rgba32 color, int thickness);        
};

#endif
