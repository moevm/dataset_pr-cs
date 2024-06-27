#include "io.h"


void panic(char *msg) {
    fprintf(stderr, ERROR_TEMPLATE, msg);
    exit(40);
}


TaskConfig* read_args(int argc, char** argv) {
    TaskConfig* config = get_args(argc, argv);
    if (CHECK_FLAG(FLAG_UNKNOWN_ARGUMENT)) panic(UNKNOWN_ARGUMENT_ERROR);
    if (CHECK_FLAG(FLAG_NO_COMMAND)) panic(NO_COMMAND_ERROR);
    if (CHECK_FLAG(FLAG_MANY_COMMAND)) panic(MANY_COMMANDS_ERROR);
    if (CHECK_FLAG(FLAG_NO_ARGUMENT_VALUE)) panic(NO_ARGUMENT_VALUE_ERROR);
    if (CHECK_FLAG(FLAG_NO_INPUT_FILE)) panic(NO_INPUT_FILE_ERROR);
    
    if (config->error_flag == 0) parse_args(config);
    if (CHECK_FLAG(FLAG_INVALID_ARGUMENT)) panic(ARGUMENT_VALUE_ERROR);
    if (CHECK_FLAG(FLAG_NO_REQUIRED_ARG)) panic(NO_REQUIRED_ARG_ERROR);
    if (CHECK_FLAG(FLAG_EQ_INPUT_OUTPUT)) panic(SAME_FILES_ERROR);

    return config;
}


Image* read_png(string* filename) {
    FILE *file = fopen(filename->data, "rb");
    if (!file) panic(FILE_OPEN_ERROR);

    Image* img = img_from_file(file);
    fclose(file);

    switch (img->error_flag) {
        case FLAG_WRONG_SINGATURE:
        case FLAG_FAIL_CREATE_PNG_STRUCT:
        case FLAG_FAIL_CREATE_INFO_STRUCT:
            panic(WRONG_FILETYPE_ERROR);
            break;
        case FLAG_FAIL_READ_HEADER:
        case FLAG_ERROR_READ_FILE:
        case FLAG_ERROR_READ_DATA:
            panic(FILE_READ_ERROR);
            break;
        case FLAG_WRONG_BIT_DEPTH:
        case FLAG_WRONG_CHANNELS:
            panic(INAPPRORIATE_IMAGE_ERROR);
            break;
    }

    return img;
}


void save_png(Image* img, string* filename) {
    FILE *file = fopen(filename->data, "wb");
    if (!file) panic(FILE_OPEN_ERROR);

    img = img_to_file(img, file);
    fclose(file);

    switch (img->error_flag) {
        case FLAG_FAIL_CREATE_PNG_STRUCT:
        case FLAG_FAIL_CREATE_INFO_STRUCT:
            panic(INTERNAL_LIBRARY_ERROR);
            break;
        case FLAG_FAIL_WRITE_HEADER:
        case FLAG_ERROR_WRITE_FILE:
        case FLAG_ERROR_WRITE_DATA:
            panic(FILE_WRITE_ERROR);
            break;
    }
}


void print_info(Image* img) {
    printf("Width: %d\nHeight: %d\nChannels count: %d\nBit_depth: %d\n",
            img->width, img->height, img->channels, img->bit_depth);
}


Image* process_image(TaskConfig* config, Image* img) {
    Point** pptr = config->params;
    Color** cptr = config->params;
    string** sptr = config->params;
    uint16_t** iptr = config->params;

    switch (config->task_flag) {
    case TASKCODE_INFO: {
        print_info(img);
        return NULL;
    } case TASKCODE_CIRC: {
        Point* center = pptr[hash(str_from_buffer(ARGNAME_CENTER))];
        uint16_t* radius = iptr[hash(str_from_buffer(ARGNAME_RADIUS))];
        uint16_t* thickness = iptr[hash(str_from_buffer(ARGNAME_THICKNESS))];
        Color* color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];

        Color fill_color = {0, 0, 0};
        if (config->fill_flag)
            fill_color = *cptr[hash(str_from_buffer(ARGNAME_FILL_COLOR))];
    
        return draw_circle(img,
                           rgb_to_rgba(color->r, color->g, color->b),
                           center->x,
                           center->y,
                           *thickness,
                           *radius,
                           config->fill_flag,
                           rgb_to_rgba(fill_color.r, fill_color.g, fill_color.b));
    } case TASKCODE_RGBF: {
        string* component_name = sptr[hash(str_from_buffer(ARGNAME_COMPNAME))];
        uint16_t* component_value = iptr[hash(str_from_buffer(ARGNAME_COMPVALUE))];
        return component_set(img, component_name->data,
                                  *component_value);
    } case TASKCODE_SPLT: {
        uint16_t* number_x = iptr[hash(str_from_buffer(ARGNAME_NUMBERX))];
        uint16_t* number_y = iptr[hash(str_from_buffer(ARGNAME_NUMBERY))];
        uint16_t* thickness = iptr[hash(str_from_buffer(ARGNAME_THICKNESS))];
        Color* color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];
        return draw_split(img, *number_x, *number_y, *thickness, rgb_to_rgba(color->r, color->g, color->b));
    } case TASKCODE_SQRL: {
        Point* left_up = pptr[hash(str_from_buffer(ARGNAME_LEFT_UP))];
        uint16_t* side_size = iptr[hash(str_from_buffer(ARGNAME_SIDE_SIZE))];
        uint16_t* thickness = iptr[hash(str_from_buffer(ARGNAME_THICKNESS))];
        Color* color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];

        Color fill_color = {0, 0, 0};
        if (config->fill_flag)
            fill_color = *cptr[hash(str_from_buffer(ARGNAME_FILL_COLOR))];

        return draw_square(img, left_up->x, left_up->y, *side_size,
                           rgb_to_rgba(color->r, color->g, color->b), *thickness,
                           config->fill_flag, rgb_to_rgba(fill_color.r, fill_color.g, fill_color.b));
    }
    case TASKCODE_RMBS: {
        Color* color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];

        return draw_rhombus(img, rgb_to_rgba(color->r, color->g, color->b));
    }
    }
}
