#ifndef CWOPTIONS_C
#define CWOPTIONS_C

#include "../cwoptions/cwoptions.h"

static int arg_to_int(const char *arg)
{
	if (arg == NULL)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	int num;
	int read = sscanf(arg, "%d", &num);

	if (read != 1)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	return num;
}
static Coord_t arg_to_coord(const char *arg)
{
	if (arg == NULL)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	int x, y;
	int read = sscanf(arg, "%d.%d", &x, &y);

	if (read != 2)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	return (Coord_t){x, y};
}

static RGB_t arg_to_rgb(const char *arg)
{
	if (arg == NULL)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	int r, g, b;
	int read = sscanf(arg, "%d.%d.%d", &r, &g, &b);

	if (read != 3)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	} 

	return (RGB_t){r, g, b};
}

static float arg_to_float(const char *arg)
{
	if (arg == NULL)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	float f;
	int read = sscanf(arg, "%f", &f);

	if (read != 1)
	{
		throw_error(INVALID_OPTION_ARGUMENT_ERROR_MSG, INVALID_OPTION_ARGUMENT_ERROR_RET_VAL);
	}

	return f;
}

struct Config *init_config()
{
	struct Config *config = (struct Config *)calloc(1, sizeof(struct Config));

	if (config == NULL)
	{
		throw_error(MEMORY_ERROR_MSG, MEMORY_ERROR_RET_VAL);
	}

	config->input_file = (char *)calloc(128, sizeof(char));
	config->output_file = (char *)calloc(128, sizeof(char));
	config->line = (struct Line_config *)calloc(1, sizeof(struct Line_config));
	config->inverse_circle = (struct Inverse_circle_config *)calloc(1, sizeof(struct Inverse_circle_config));
	config->trim = (struct Trim_config *)calloc(1, sizeof(struct Trim_config));
	config->contrast = (struct Contrast_config *)calloc(1, sizeof(struct Contrast_config));

	if (config->input_file == NULL ||
        config->output_file == NULL ||
		config->line == NULL ||
		config->inverse_circle == NULL ||
		config->trim == NULL ||
		config->contrast == NULL)
	{
		throw_error(MEMORY_ERROR_MSG, MEMORY_ERROR_RET_VAL);	
	}

	return config;
}

void destroy_config(struct Config *config)
{
	if (config != NULL)
	{
		if (config->input_file != NULL)
		{
			free(config->input_file);
		}

		if (config->output_file != NULL)
		{
			free(config->output_file);
		}

		if (config->line != NULL)
		{
			free(config->line);
		}

		if (config->inverse_circle != NULL)
		{
			free(config->inverse_circle);
		}

		if (config->trim != NULL)
		{
			free(config->trim);
		}

		if (config->contrast != NULL)
		{
			free(config->contrast);
		}
	}
}

bool big_flag_is_set(const struct Config* config)
{ 
	if (config->flag_line)
	{
		return true;
	}

	if (config->flag_inverse_circle)
	{
		return true;
	}

	if (config->flag_trim)
	{
		return true;
	}

	if (config->flag_contrast)
	{
		return true;
	}

	return false;
}

struct Config *get_options(int argc, char **argv)
{
	const char *short_options = "ho:i:";

	const struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"input", required_argument, NULL, 'i'},
		{"output", required_argument, NULL, 'o'},
		{"info", no_argument, NULL, INFO_OPT},
		{"line", no_argument, NULL, LINE_OPT},
		{"inverse_circle", no_argument, NULL, INVERSE_CIRCLE_OPT},
		{"trim", no_argument, NULL, TRIM_OPT},
		{"start", required_argument, NULL, START_OPT},
		{"end", required_argument, NULL, END_OPT},
		{"color", required_argument, NULL, COLOR_OPT},
		{"thickness", required_argument, NULL, THICKNESS_OPT},
		{"center", required_argument, NULL, CENTER_OPT},
		{"radius", required_argument, NULL, RADIUS_OPT},
		{"left_up", required_argument, NULL, LEFT_UP_OPT},
		{"right_down", required_argument, NULL, RIGHT_DOWN_OPT},
		{"contrast", no_argument, NULL, CONTRAST_OPT},
		{"alpha", required_argument, NULL, ALPHA_OPT},
		{"beta", required_argument, NULL, BETA_OPT},
		{NULL, no_argument, NULL, 0}
	};

	struct Config *config = init_config();

	int opt, option_index = -1;
	char *last_argument = (char *)malloc((MAX_FILENAME_LEN + 1) * sizeof(char));

	if (last_argument == NULL)
	{
		throw_error(MEMORY_ERROR_MSG, MEMORY_ERROR_RET_VAL);
	}

	strncpy(last_argument, argv[argc - 1], MAX_FILENAME_LEN);

	while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'h':
			{
				if (config->flag_help)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->flag_help = true;
			}
			break;

			case 'o':
			{
				if (strlen(config->output_file) != 0)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				strncpy(config->output_file, optarg, MAX_FILENAME_LEN);
			}
			break;

			case 'i':
			{
				if (strlen(config->input_file) != 0)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				strncpy(config->input_file, optarg, MAX_FILENAME_LEN);
			}
			break;

			case INFO_OPT:
			{
				if (config->flag_info)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->flag_info = true;
			}
			break;

			case LINE_OPT:
			{
				if (big_flag_is_set(config))
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->flag_line = true;
			}
			break;

			case INVERSE_CIRCLE_OPT:
			{
				if (big_flag_is_set(config))
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->flag_inverse_circle = true;
			}
			break;

			case TRIM_OPT:
			{
				if (big_flag_is_set(config))
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->flag_trim = true;
			}
			break;

			case CONTRAST_OPT:
			{
				if (big_flag_is_set(config))
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->flag_contrast = true;
			}
			break;

			case START_OPT:
			{
				if (config->line->flag_start)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->line->start = arg_to_coord(optarg);
				config->line->flag_start = true;
			}
			break;

			case END_OPT:
			{
				if (config->line->flag_end) {
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->line->end = arg_to_coord(optarg);
				config->line->flag_end = true;
			}
			break;

			case COLOR_OPT:
			{
				if (config->line->flag_color)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->line->color = arg_to_rgb(optarg);
				config->line->flag_color = true;
			}
			break;

			case THICKNESS_OPT:
			{
				if (config->line->flag_thickness)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->line->thickness = arg_to_int(optarg);
				config->line->flag_thickness = true;
			}
			break;

			case CENTER_OPT:
			{
				if (config->inverse_circle->flag_center)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->inverse_circle->center = arg_to_coord(optarg);
				config->inverse_circle->flag_center = true;
			}
			break;

			case RADIUS_OPT:
			{
				if (config->inverse_circle->flag_radius)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->inverse_circle->radius = arg_to_int(optarg);
				config->inverse_circle->flag_radius = true;
			}
			break;

			case LEFT_UP_OPT:
			{
				if (config->trim->flag_left_up)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->trim->left_up = arg_to_coord(optarg);
				config->trim->flag_left_up = true;
			}
			break;

			case RIGHT_DOWN_OPT:
			{
				if (config->trim->flag_right_down)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->trim->right_down = arg_to_coord(optarg);
				config->trim->flag_right_down = true;
			}
			break;

			case ALPHA_OPT:
			{
				if (config->contrast->flag_alpha)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->contrast->alpha = arg_to_float(optarg);
				config->contrast->flag_alpha = true;
			}
			break;

			case BETA_OPT:
			{
				if (config->contrast->flag_beta)
				{
					throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
				}
				config->contrast->beta = arg_to_int(optarg);
				config->contrast->flag_beta = true;
			}
			break;

			case '?':
			default:
			{
				throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
			}
		}
		option_index = -1;
	}

	if (strlen(config->input_file) == 0)
	{
		if (optind == argc - 1 && strncmp(argv[optind], last_argument, MAX_FILENAME_LEN + 1) == 0)
		{
			strcpy(config->input_file, last_argument);
		}
		else if (optind < argc)
		{
			throw_error(OPTION_ERROR_MSG, OPTION_ERROR_RET_VAL);
		}
	}

	return config;
}


#endif