#pragma once

#include "../bmp/bmp.h"
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

struct input_data
{
	string function = "";
	string input_path;
	string output_path = "output.bmp";
	RGB color;
	RGB border_color;
	RGB fill_color;
	int thickness = 0;
	Circle circle;
	bool fill = false;
	string component_name = "";
	int component_value = -1;
	int number_x = -1;
	int number_y = -1;
};


void throw_exception(string message, int exit_code);
void print_map(unordered_map<string, string>);
unordered_map<string, string> input(int argc, char **argv);
vector<int> parse_input(string str, void(*func)(int));
vector<int> parse_input(string str);
void check_rgb_value(int value);
vector<string> split(string str, char ch);
int custom_stoi(string str);
void check_positive(int val);

input_data *check_input(unordered_map<string, string> input);
void check_component_name(string str);
void print_help();