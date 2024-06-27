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
    } case TASKCODE_COPY: {
        Point* src_up = pptr[hash(str_from_buffer(ARGNAME_SRC_UP))];
        Point* src_down = pptr[hash(str_from_buffer(ARGNAME_SRC_DOWN))];
        Point* dest_up = pptr[hash(str_from_buffer(ARGNAME_DEST_UP))];
        return copy_area(img, src_up->x, src_up->y, src_down->x, src_down->y, dest_up->x, dest_up->y);
    } case TASKCODE_REPL: {
        Color* old_color = cptr[hash(str_from_buffer(ARGNAME_OLD_COLOR))];
        Color* new_color = cptr[hash(str_from_buffer(ARGNAME_NEW_COLOR))];
        return color_replace(img, rgb_to_rgba(old_color->r, old_color->g, old_color->b),
                                  rgb_to_rgba(new_color->r, new_color->g, new_color->b));
    } case TASKCODE_ORNM: {
        string* pattern = sptr[hash(str_from_buffer(ARGNAME_PATTERN))];
        Color* color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];
        uint16_t* thickness = iptr[hash(str_from_buffer(ARGNAME_THICKNESS))];
        uint16_t* count = iptr[hash(str_from_buffer(ARGNAME_COUNT))];
        return make_border(img, pattern->data, rgb_to_rgba(color->r, color->g, color->b), *thickness, *count);
    } case TASKCODE_RECT: {
        Color* rect_color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];
        Color* border_color = cptr[hash(str_from_buffer(ARGNAME_BORDER_COLOR))];
        uint16_t* border_thickness = iptr[hash(str_from_buffer(ARGNAME_THICKNESS))];
        return frame_rectangles(img,
                                rgb_to_rgba(rect_color->r, rect_color->g, rect_color->b),
                                rgb_to_rgba(border_color->r, border_color->g, border_color->b),
                                *border_thickness);
    } case TASKCODE_OUTO: {
        Color* color = cptr[hash(str_from_buffer(ARGNAME_COLOR))];
        uint16_t* thickness = iptr[hash(str_from_buffer(ARGNAME_THICKNESS))];
        return outline_image(img, rgb_to_rgba(color->r, color->g, color->b), *thickness);
    }
    }
}
