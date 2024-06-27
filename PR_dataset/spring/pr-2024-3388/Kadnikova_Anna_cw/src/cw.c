#include "image.h"
#include "io.h"
#include "parser.h"
#include "str.h"

int main(int argc, char** argv) {
    TaskConfig* config = read_args(argc, argv);
    if (config->task_flag == TASKCODE_HELP) {
        printf(HELP_MESSAGE);
        return 0;
    }

    Image* input_img = read_png(config->input_filename);
    Image* output_img = process_image(config, input_img);

    if (output_img != NULL) {
        if (output_img->error_flag != 0) panic(ARGUMENT_VALUE_ERROR);
        save_png(output_img, config->output_filename);
    }

    return 0;
}
