#ifndef STRUCTURES
#define STRUCTURES

#define R_IDX        0
#define G_IDX        1
#define B_IDX        2

#define X_IDX        0
#define Y_IDX        1

#define SIG_BYTES          2
#define RESERVED_1_BYTES   2
#define RESERVED_2_BYTES   2

namespace ie
{
struct Coord
{
    int x;
    int y;
};

struct Color
{
    int r;
    int g;
    int b;

    bool operator==(Color other)
    {
        return (r == other.r) && 
               (g == other.g) && 
               (b == other.b);
    }

    bool operator!=(Color other)
    {
        return !(*this == other);
    }

    void inverse()
    {
        r = 255 - r;
        g = 255 - g;
        b = 255 - b;
    }

    void gray()
    {
        r = (0.299 * r) + (0.587 * g) + (0.114 * b);
        g = (0.299 * r) + (0.587 * g) + (0.114 * b);
        b = (0.299 * r) + (0.587 * g) + (0.114 * b);
    }
};

#pragma pack(push, 1)
struct BMPHeader
{
    unsigned char       signature[SIG_BYTES];
    unsigned int        file_size;
    unsigned char       reserved1[RESERVED_1_BYTES];
    unsigned char       reserved2[RESERVED_2_BYTES];
    unsigned int        pixel_offset;
};
struct DIBHeader
{
    unsigned int       byte_count;
    unsigned int       width;
    unsigned int       height;
    unsigned short     color_planes;
    unsigned short     bits_per_pixel;
    unsigned int       compression;
    unsigned int       image_size;
    unsigned int       pwidth;
    unsigned int       pheight;
    unsigned int       color_count;
    unsigned int       important_color_count;
};
struct RGB
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};
#pragma pack(pop)

}
#endif