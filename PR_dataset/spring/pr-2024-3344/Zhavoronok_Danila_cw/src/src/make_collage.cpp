#include "../include/make_collage.h"

RGB *make_collage(RGB *pixels, int w, int h, int N, int M, int &cw, int &ch)
{
    cw = w * N;
    ch = h * M;

    RGB *collage = new RGB[cw * ch];
    for (int i = 0; i < ch; i++)
    {
        for (int j = 0; j < cw; j++)
        {
            int pixelsI = i % h;
            int pixelsJ = j % w;

            collage[i * cw + j] = pixels[pixelsI * w + pixelsJ];
        }
    }

    return collage;
}
