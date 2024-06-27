#ifndef CW_DRAWOPTIONS_H
#define CW_DRAWOPTIONS_H

#include <getopt.h>
#include <string>
#include "utils.hpp"

#include "image.hpp"

struct Options;
typedef void (*ProcessOptionFunction)(Image &image, Options &opts);

void processTriangleOption(Image &image, Options &opts);
void processBiggestRectOption(Image &image, Options &opts);
void processCollageOption(Image &image, Options &opts);
void processLineOption(Image &image, Options &opts);
void processBlankOption(Image &image, Options &opts);
void processHelpOption(Image &image, Options &opts);
void processInfoOption(Image &image, Options &opts);
void processPavingOption(Image &image, Options &opts);
void processOutsideRectOption(Image &image, Options &opts);

struct FunctionInfo {
	ProcessOptionFunction ptr;
	bool do_read;
	bool do_write;
	int required_bits;
};

struct Options {
	int bits;
	FunctionInfo *func;

	std::string input;
	std::string output;

	vec2i points[3];
	rgba32 color;
	bool fill;
	rgba32 fill_color;
	rgba32 old_color;
	rgba32 new_color;
	int number_x;
	int number_y;
	vec2i start;
	vec2i end;
	int thickness;
	float bias;

	vec2i left_up;
	vec2i right_down;

    void readFromArgv(int argc, char **argv);
};

enum {
	OPTIONS_OFFSET = 0x100,
	OPTION_INPUT = OPTIONS_OFFSET,
	OPTION_OUTPUT,
	OPTION_POINTS,
	OPTION_COLOR,
	OPTION_FILL,
	OPTION_FILL_COLOR,
	OPTION_OLD_COLOR,
	OPTION_NEW_COLOR,
	OPTION_NUMBER_X,
	OPTION_NUMBER_Y,
	OPTION_START,
	OPTION_END,
	OPTION_THICKNESS,
	OPTION_BIAS,
	OPTION_LEFT_UP,
	OPTION_RIGHT_DOWN,
	
	OPTIONS_FUNC_OFFSET,
	OPTION_FUNC_TRIANGLE = OPTIONS_FUNC_OFFSET,
	OPTION_FUNC_BIGGEST_RECT,
	OPTION_FUNC_COLLAGE,
	OPTION_FUNC_LINE,
	OPTION_FUNC_BLANK,
	OPTION_FUNC_HELP,
	OPTION_FUNC_INFO,
	OPTION_FUNC_PAVING,
	OPTION_FUNC_OUTSIDE_RECT
};

#endif
