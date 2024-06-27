#include "options.hpp"
#include "utils.hpp"
#include <bits/getopt_core.h>
#include <bits/getopt_ext.h>
#include <cstddef>
#include <iostream>
#include <stdexcept>

void readPoints(vec2i *res, const char *str)
{
	int ret = std::sscanf(str, "%d.%d.%d.%d.%d.%d",
		&res[0].x, &res[0].y, &res[1].x, &res[1].y, &res[2].x, &res[2].y
	);
	if (ret != 6)
		throw std::runtime_error("invalid points format");
}

void readColor(rgba32 *res, const char *str)
{
	int r, g, b;
	int ret = std::sscanf(str, "%d.%d.%d", &r, &g, &b);
	
	if (ret != 3)
		throw std::runtime_error("invalid color format");

	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		throw std::runtime_error("invalid color range");

	res->r = r;
	res->g = g;
	res->b = b;
	res->a = 255;
}

void readFlag(bool *res, const char *str)
{
	*res = true;
}

void readPoint(vec2i *res, const char *str)
{
	int ret = std::sscanf(str, "%d.%d", &res->x, &res->y);
	if (ret != 2)
		throw std::runtime_error("invalid point format");
}

void readInt(int *res, const char *str)
{
	int ret = std::sscanf(str, "%d", res);
	if (ret != 1)
		throw std::runtime_error("invalid int format");
}

void readFloat(float *res, const char *str)
{
	int ret = std::sscanf(str, "%f", res);
	if (ret != 1)
		throw std::runtime_error("invalid float format");
}

void readString(std::string *res, const char *str)
{
	*res = str;
}

constexpr int bit(int option)
{
	return 1 << (option - OPTIONS_OFFSET);
}

FunctionInfo functions[] = {
	{ processTriangleOption, true, true, bit(OPTION_POINTS) | bit(OPTION_COLOR) | bit(OPTION_THICKNESS) },
	{ processBiggestRectOption, true, true, bit(OPTION_OLD_COLOR) | bit(OPTION_NEW_COLOR) },
	{ processCollageOption, true, true, bit(OPTION_NUMBER_X) | bit(OPTION_NUMBER_Y) },
	{ processLineOption, true, true, bit(OPTION_START) | bit(OPTION_END) | bit(OPTION_THICKNESS) | bit(OPTION_COLOR) },
	{ processBlankOption, true, true, 0 },
	{ processHelpOption, false, false, 0 },
	{ processInfoOption, true, false, 0},
	{ processPavingOption, true, true, bit(OPTION_LEFT_UP) | bit(OPTION_RIGHT_DOWN) },
	{ processOutsideRectOption, true, true, bit(OPTION_LEFT_UP) | bit(OPTION_RIGHT_DOWN) | bit(OPTION_COLOR) }
};

void Options::readFromArgv(int argc, char **argv)
{
	this->bits = 0;
	this->bias = 0.f;
	this->func = nullptr;

	static struct option longopts[] = {
		{     "points", 1, NULL, OPTION_POINTS },
		{      "color", 1, NULL, OPTION_COLOR },
		{       "fill", 0, NULL, OPTION_FILL },
		{ "fill_color", 1, NULL, OPTION_FILL_COLOR },
		{  "old_color", 1, NULL, OPTION_OLD_COLOR },
		{  "new_color", 1, NULL, OPTION_NEW_COLOR },
		{   "number_x", 1, NULL, OPTION_NUMBER_X },
		{   "number_y", 1, NULL, OPTION_NUMBER_Y },
		{      "start", 1, NULL, OPTION_START },
		{        "end", 1, NULL, OPTION_END },
		{  "thickness", 1, NULL, OPTION_THICKNESS },
		{       "bias", 1, NULL, OPTION_BIAS },
		{     "output", 1, NULL, OPTION_OUTPUT },
		{      "input", 1, NULL, OPTION_INPUT },
		{    "left_up", 1, NULL, OPTION_LEFT_UP },
		{ "right_down", 1, NULL, OPTION_RIGHT_DOWN },

		{     "triangle", 0, NULL, OPTION_FUNC_TRIANGLE },
		{ "biggest_rect", 0, NULL, OPTION_FUNC_BIGGEST_RECT },
		{      "collage", 0, NULL, OPTION_FUNC_COLLAGE },
		{         "line", 0, NULL, OPTION_FUNC_LINE },
		{        "blank", 0, NULL, OPTION_FUNC_BLANK },
		{         "help", 0, NULL, OPTION_FUNC_HELP },
		{         "info", 0, NULL, OPTION_FUNC_INFO },
		{       "paving", 0, NULL, OPTION_FUNC_PAVING },
		{ "outside_rect", 0, NULL, OPTION_FUNC_OUTSIDE_RECT },
		{           NULL, 0, NULL,   0 }
	};

	static char optstring[] = "p:c:fF:x:y:s:e:t:b:o:TRCLBhi";

	int arg = getopt_long(argc, argv, optstring, longopts, NULL);
	while (arg != -1) {
		if (arg == '?')
			throw std::runtime_error("invalid option");

		switch (arg) {
			case 'p': arg = OPTION_POINTS; break;
			case 'c': arg = OPTION_COLOR; break;
			case 'f': arg = OPTION_FILL; break;
			case 'F': arg = OPTION_FILL_COLOR; break;
			case 'x': arg = OPTION_NUMBER_X; break;
			case 'y': arg = OPTION_NUMBER_Y; break;
			case 's': arg = OPTION_START; break;
			case 'e': arg = OPTION_END; break;
			case 't': arg = OPTION_THICKNESS; break;
			case 'b': arg = OPTION_BIAS; break;
			case 'o': arg = OPTION_OUTPUT; break;
			case 'T': arg = OPTION_FUNC_TRIANGLE; break;
			case 'R': arg = OPTION_FUNC_BIGGEST_RECT; break;
			case 'C': arg = OPTION_FUNC_COLLAGE; break;
			case 'L': arg = OPTION_FUNC_LINE; break;
			case 'B': arg = OPTION_FUNC_BLANK; break;
			case 'h': arg = OPTION_FUNC_HELP; break;
			case 'i': arg = OPTION_FUNC_INFO; break;
			default:
				break;
		}

		bool is_option = true;
		switch (arg) {
			case OPTION_INPUT: readString(&this->input, optarg); break;
			case OPTION_OUTPUT: readString(&this->output, optarg); break;
			case OPTION_POINTS: readPoints(this->points, optarg); break;
			case OPTION_COLOR: readColor(&this->color, optarg); break;
			case OPTION_FILL: readFlag(&this->fill, optarg); break;
			case OPTION_FILL_COLOR: readColor(&this->fill_color, optarg); break;
			case OPTION_OLD_COLOR: readColor(&this->old_color, optarg); break;
			case OPTION_NEW_COLOR: readColor(&this->new_color, optarg); break;
			case OPTION_NUMBER_X: readInt(&this->number_x, optarg); break;
			case OPTION_NUMBER_Y: readInt(&this->number_y, optarg); break;
			case OPTION_START: readPoint(&this->start, optarg); break;
			case OPTION_END: readPoint(&this->end, optarg); break;
			case OPTION_THICKNESS: readInt(&this->thickness, optarg); break;
			case OPTION_BIAS: readFloat(&this->bias, optarg); break;
			case OPTION_LEFT_UP: readPoint(&this->left_up, optarg); break;
			case OPTION_RIGHT_DOWN: readPoint(&this->right_down, optarg); break;

			default:
				is_option = false;
				break;
		}

		if (is_option) {
			this->bits |= bit(arg);
		}
		else if (this->func != nullptr) {
			throw std::logic_error("more than one function specified");
		}
		else {
			this->func = &functions[arg - OPTIONS_FUNC_OFFSET];
		}

		arg = getopt_long(argc, argv, optstring, longopts, NULL);
	}

	if (this->func == nullptr)
		throw std::runtime_error("no function specified");

	if (this->input == "" && this->func->do_read) {
		if (optind >= argc)
			throw std::runtime_error("missing filename");
		this->input = argv[optind];
	}
	
	if (this->func->do_write && this->output.empty()) {
		this->output = "out.png";
		this->bits |= bit(OPTION_OUTPUT);
	}
}
