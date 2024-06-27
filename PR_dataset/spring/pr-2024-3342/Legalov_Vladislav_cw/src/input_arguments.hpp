#pragma once
#include <iostream>
#include <cstring>
#include <getopt.h>

#include "image.hpp"


class arguments{
public:
	bool ishelp;
	bool isinfo;
	bool isfill;
	int number;
	int x1;
	int x2;
	int y1;
	int y2;
	int length;
	int thickness;
	int type_exchange;
	int color[3];
	int fill_color[3];
	char* input_path;
	char* output_path;

	arguments();
	~arguments();
};


arguments *getarguments(int argc, char** argv);
