#include "function_params.h"
#include "errors.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

params_t* parse_command_line(int argc, char* argv[])
{
    params_t* params = (params_t*)malloc(sizeof(params_t));
    int opt, count;
    const char* short_options = "hi:o:";
    const struct option long_options[] = {
        { "help", 0, NULL, 'h' },
        { "info", 0, NULL, 271 },
        { "input", 1, NULL, 'i' },
        { "output", 1, NULL, 'o' },
        { "inverse_circle", 0, NULL, 256 },
        { "trim", 0, NULL, 257 },
        { "triangle", 0, NULL, 258 },
        { "line", 0, NULL, 259 },
        { "center", 1, NULL, 260 },
        { "radius", 1, NULL, 261 },
        { "left_up", 1, NULL, 262 },
        { "right_down", 1, NULL, 263 },
        { "points", 1, NULL, 264 },
        { "thickness", 1, NULL, 265 },
        { "color", 1, NULL, 266 },
        { "fill", 0, NULL, 267 },
        { "fill_color", 1, NULL, 268 },
        { "start", 1, NULL, 269 },
        { "end", 1, NULL, 270 },

        { "circle_pixel", 0, NULL, 272 },
        { "size", 1, NULL, 273 },
        { "circle_color", 1, NULL, 274 },
        { NULL, 0, NULL, 0 },
    };

    opt = 0;
    opterr = 0;
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (opt) {
        case 'i':
            params->input_file = optarg;
            break;
        case 'o':
            params->output_file = optarg;
            break;
        case 'h':
            print_help();
            exit(EXIT_SUCCESS);
            break;
        case 271:
            params->info = 1;
            break;

        case 272:
            params->circle_pixel = 1;
            break;
        case 273:
            count = sscanf(optarg, "%d", &params->size);
            check_sscanf(count, 1);
            break;
        case 274:
            count = sscanf(optarg, "%hhu.%hhu.%hhu", &params->circle_color.r, &params->circle_color.g, &params->circle_color.b);
            check_sscanf(count, 3);
            break;

        case 256:
            params->inverse_circle = 1;
            break;
        case 257:
            params->trim = 1;
            break;
        case 258:
            params->triangle = 1;
            break;
        case 259:
            params->line = 1;
            break;
        case 260:
            count = sscanf(optarg, "%d.%d", &params->p0.x, &params->p0.y);
            check_sscanf(count, 2);
            break;
        case 261:
            count = sscanf(optarg, "%u", &params->circle_r);
            check_sscanf(count, 1);
            break;
        case 262:
            count = sscanf(optarg, "%d.%d", &params->p0.x, &params->p0.y);
            check_sscanf(count, 2);
            break;
        case 263:
            count = sscanf(optarg, "%d.%d", &params->p1.x, &params->p1.y);
            check_sscanf(count, 2);
            break;
        case 264:
            count = sscanf(optarg, "%d.%d.%d.%d.%d.%d", &params->p0.x, &params->p0.y, &params->p1.x, &params->p1.y, &params->p2.x, &params->p2.y);
            check_sscanf(count, 6);
            break;
        case 265:
            count = sscanf(optarg, "%u", &params->thickness);
            check_sscanf(count, 1);
            break;
        case 266:
            count = sscanf(optarg, "%hhu.%hhu.%hhu", &params->color.r, &params->color.g, &params->color.b);
            check_sscanf(count, 3);
            break;
        case 267:
            params->fill = 1;
            break;
        case 268:
            count = sscanf(optarg, "%hhu.%hhu.%hhu", &params->fill_color.r, &params->fill_color.g, &params->fill_color.b);
            check_sscanf(count, 3);
            break;
        case 269:
            count = sscanf(optarg, "%d.%d", &params->p0.x, &params->p0.y);
            check_sscanf(count, 2);
            break;
        case 270:
            count = sscanf(optarg, "%d.%d", &params->p1.x, &params->p1.y);
            check_sscanf(count, 2);
            break;
        case '?':
            raise_error("incorrect option value", OPTION_ERR);
            break;
        default:
            break;
        }
    }

    if (params->inverse_circle + params->trim + params->triangle + params->line > 1) {
        raise_error("incorrect call funtion", CALL_FLAG_ERR);
    }
    if (!params->input_file) {
        params->input_file = argv[argc - 1];
    }
    if (!params->output_file) {
        params->output_file = "out.bmp";
    }
    return params;
}