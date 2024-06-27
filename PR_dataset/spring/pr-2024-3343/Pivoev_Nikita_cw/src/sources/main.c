#include "../include/main.h"

int main(int argc, char** argv) {
    OptParams* opt = parseCommandLine(argc, argv);
    checkExtraArgs(opt);

    Png image;
    read_png_file(opt->input, &image);

    if (opt->info)
        printInfo(&image);

    if (opt->copy) {
        checkCopy(&image, opt);
        copyArea(&image, opt);
    }

    if (opt->color_replace) {
        checkReplace(&image, opt);
        replaceColor(&image, opt);
    }

    if (opt->ornament) {
        checkOrnament(&image, opt);
        createOrnament(&image, opt);
    }

    if (opt->filled_rects) {
        checkRects(&image, opt);
        fillRects(&image, opt);
    }

    if (opt->outside_ornament) {
        checkOutside(&image, opt);
        fillOutside(&image, opt);
    }

    write_png_file(opt->output, &image);
    free(opt);
    return 0;
}