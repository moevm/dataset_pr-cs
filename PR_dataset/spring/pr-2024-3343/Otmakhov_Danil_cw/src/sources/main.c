#include "bmp.h"
#include "errors.h"


int main(int argc, char *argv[])
{
    puts(hello_message);

    CommandLineOptions* options = parseCommandLine(argc, argv);
    BMP* bmp_file = readBMPFile(options->input);
    //BMP* bmp_file = readBMPFile("images/input_1.bmp");

    if (options->info) {
        printBMPFileInfo(bmp_file);
        exit(EXIT_SUCCESS);
    }

    if (options->colorReplace)
        colorReplace(bmp_file, options);

    if (options->rgbFilter)
        rgbFilter(bmp_file, options);

    if (options->split)
        split(bmp_file, options);

    if (options->binarization)
        binarization(bmp_file, options);

    //RGB** buf_left = copy(bmp_file, 0, 0, 100 - 1, bmp_file->bmihdr.height - 1);

    //paste(bmp_file, bmp_file->bmihdr.width - 100, 0, buf_left, bmp_file->bmihdr.height, 100);

    writeBMPFile(options->output, bmp_file);
    //writeBMPFile("out.bmp", bmp_file);
    free(options);
    freeBMPFile(bmp_file);


    return 0;
}
