#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>
#include "const.h"
#include "str.h"

typedef struct {
    int64_t x;
    int64_t y;
} Point;


typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;


typedef struct {
    uint8_t task_flag;
    bool fill_flag;
    uint8_t error_flag;

    void* params;
    string* input_filename;
    string* output_filename;
} TaskConfig;


TaskConfig* init_config();

uint8_t hash(string* str);

uint8_t bitcount(uint8_t n);

bool check_param(TaskConfig* config, string* key);

void parse_int16(TaskConfig* config, string* key);

void parse_point(TaskConfig* config, string* key);

void parse_color(TaskConfig* config, string* key);

#define NO_REQUIRED_ARG(arg_name) !check_param(config, str_from_buffer(arg_name))

TaskConfig* get_args(int argc, char** argv);

void parse_args(TaskConfig* config);

#endif /* PARSER_H */
