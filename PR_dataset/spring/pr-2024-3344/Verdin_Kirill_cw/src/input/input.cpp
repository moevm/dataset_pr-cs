#include <iostream>
#include <getopt.h>
#include <cstring>
#include <sstream>
#include "input.h"

using std::cout;

unordered_map<string, string> input(int argc, char **argv)
{	
	string last_arg = argv[argc - 1];
	unordered_map<string, string> input;

	const option long_optinons[] = {

		{"filled_rects", no_argument, nullptr, 1},
		{"color", required_argument, nullptr, 1},
		{"border_color", required_argument, nullptr, 1},
		{"thickness", required_argument, nullptr, 1},

		{"circle", no_argument, nullptr, 1},
		{"center", required_argument, nullptr, 1},
		{"radius", required_argument, nullptr, 1},
		{"color", required_argument, nullptr, 1},
		{"thickness", required_argument, nullptr, 1},
		{"fill", no_argument, nullptr, 1},
		{"fill_color", required_argument, nullptr, 1},

		{"rgbfilter", no_argument, nullptr, 1},
		{"component_name", required_argument, nullptr, 1},
		{"component_value", required_argument, nullptr, 1},

		{"split", no_argument, nullptr, 1},
		{"number_x", required_argument, nullptr, 1},
		{"number_y", required_argument, nullptr, 1},
		{"thickness", required_argument, nullptr, 1},
		{"color", required_argument, nullptr, 1},

		{"rhombus", no_argument, nullptr, 1},
		{"color", required_argument, nullptr, 1},

		{"input", required_argument, nullptr, 1},

		{"output", required_argument, nullptr, 1},

		{"info", no_argument, nullptr, 1},

		{"help", no_argument, nullptr, 1}};
	int index = -1;
	int rez = 0;
	while ((rez = getopt_long(argc, argv, "i:o:h", long_optinons, &index)) != -1)
	{
		opterr = 0;
		// if (!rez)
		// 	throw_exception("Unknown flag", 42);

		if (rez == 'i')
		{
			string arg(optarg);
			input.insert({"i", arg});
		}

		if (rez == 'o')
		{
			string arg(optarg);
			input.insert({"o", arg});
		}

		if (rez == 'h')
		{
			input.insert({"h", ""});
		}

		if (rez == '?')
		{
			throw_exception("Unknown flag", 43);
		}

		if (long_optinons[index].has_arg == no_argument)
		{
			input.insert({long_optinons[index].name, ""});
		}

		if (long_optinons[index].has_arg == required_argument)
		{
			string arg(optarg);
			input.insert({long_optinons[index].name, arg});
		}
	}

	if (input.find("input") == input.end() && input.find("i") == input.end())
	{
		for (auto v : input)
		{
			if (v.second == last_arg)
				throw_exception("Enter input path of file", 44);
		}
		input.insert({"input", last_arg});
	}
	return input;
}

void throw_exception(string message, int exit_code)
{
	std::cerr << message << '\n';
	exit(exit_code);
}


void print_map(unordered_map<string, string> dict)
{
	for (const auto v : dict)
	{
		cout << v.first << " " << v.second << "\n";
	}
}

input_data *check_input(unordered_map<string, string> input)
{	
	vector<vector<string>> samples = {
		{"filled_rects", "color", "border_color", "thickness"},
		{"circle", "center", "radius", "thickness", "color", "fill", "fill_color"},
		{"rgbfilter", "component_name", "component_value"},
		{"split", "number_x", "number_y", "color", "thickness"},
		{"rhombus", "color"}};
	input_data *tmp;
	int is_input_data = 1;
	tmp = new input_data;
	string input_path;
	string output_path = "output.bmp";
	if (input.find("input") != input.end())
	{	
		input_path = input["input"];
	}
	else if (input.find("i") != input.end())
	{
		input_path = input["i"];
	}

	if (input.find("output") != input.end())
	{	
		output_path = input["output"];
	}
	else if (input.find("o") != input.end())
	{
		output_path = input["o"];
	}
	if (input_path == output_path)
		throw_exception("input path and output path are same", 44);

	for (auto v : samples)
	{	
		is_input_data = 1;
		for (auto w : v)
		{
			if (input.find(w) == input.end() && w != "fill_color" && w != "fill")
			{
				is_input_data = -1;
				delete tmp;
				// cout << w << '\n';
				tmp = new input_data;
				break;
			}
			if (w == "color")
			{
				vector<int> color = parse_input(input[w], check_rgb_value);
				if (color.size() != 3)
					throw_exception(input[w] + " not requaries to the template of flag "  + w, 42);
				tmp->color.r = color[0];
				tmp->color.g = color[1];
				tmp->color.b = color[2];
			}
			else if (w == "border_color")
			{
				vector<int> border_color = parse_input(input[w], check_rgb_value);
				if (border_color.size() != 3)
					throw_exception(input[w] + " not requaries to the template \"X.X.X\" of flag " + w, 42);
				tmp->border_color.r = border_color[0];
				tmp->border_color.g = border_color[1];
				tmp->border_color.b = border_color[2];
			}
			else if (w == "thickness")
			{
				tmp->thickness = custom_stoi(input[w]);
				check_positive(tmp->thickness);
			}
			else if (w == "center")
			{
				vector<int> coordinates = parse_input(input[w]);
				if (coordinates.size() != 2)
					throw_exception(input[w] + " not requaries to the template \"X.X\" of flag " + w, 42);
				tmp->circle.x0 = coordinates[0];
				tmp->circle.y0 = coordinates[1];
			}
			else if (w == "radius")
			{
				tmp->circle.r = custom_stoi(input[w]);
				check_positive(tmp->circle.r);
			}
			else if (w == "fill_color" && input.find(w) != input.end())
			{
				vector<int> fill_color = parse_input(input[w], check_rgb_value);
				if (fill_color.size() != 3)
					throw_exception(input[w] + " not requaries to the template \"X.X.X\" of flag " + w, 42);
				tmp->fill_color.r = fill_color[0];
				tmp->fill_color.g = fill_color[1];
				tmp->fill_color.b = fill_color[2];
			}
			else if (w == "component_name")
			{
				check_component_name(input[w]);
				tmp->component_name = input[w];
			}
			else if (w == "component_value")
			{
				tmp->component_value = custom_stoi(input[w]);
				check_rgb_value(tmp->component_value);
			}
			else if (w == "number_x")
			{
				tmp->number_x = custom_stoi(input[w]);
				check_positive(tmp->number_x + 1);
			}
			else if (w == "number_y")
			{
				tmp->number_y = custom_stoi(input[w]);
				check_positive(tmp->number_y + 1);
			}
			else if (w == "fill" && input.find(w)!=input.end())
			{	
				// cout << w;
				tmp->fill = true;
			}
		}
		if(is_input_data == 1)
			break;
	}
	string function;
	for (size_t i = 0; i<samples.size(); i++)
	{
		if(input.find(samples[i][0]) != input.end())
			function = samples[i][0];
	}
	if (is_input_data == -1)
	{
		throw_exception("the " + function + " function accepts other flags", 44);
	}
	tmp->function = function;
	tmp->input_path = input_path;
	tmp->output_path = output_path;
	return tmp;
}
vector<int> parse_input(string str, void(*func)(int))
{
	vector<int> output;
	vector<string> array = split(str, '.');
	for (size_t i = 0; i < array.size(); i++)
	{	
		int t = custom_stoi(array[i]);
		func(t);	
		output.push_back(t);
	}
	return output;
}

vector<int> parse_input(string str)
{
	vector<int> output;
	vector<string> array = split(str, '.');
	for (size_t i = 0; i < array.size(); i++)
	{	
		int t = custom_stoi(array[i]);
		output.push_back(t);
	}
	return output;
}

void check_rgb_value(int val)
{
	if (val < 0 || val > 255)
		throw_exception("The value of color must be in range [0, 255]", 41);
}

vector<string> split(string str, char ch)
{
	std::istringstream ss(str);
	string token;
	vector<string> array;
	while (getline(ss, token, ch))
		array.push_back(token);
	return array;
}

int custom_stoi(string str)
{
	int n;
	try
	{
		n = std::stoi(str);
	}
	catch (const std::exception &e)
	{	
		throw_exception("The value must be integer", 41);
	}
	return n;
}

void check_positive(int val)
{
	if (val < 0)
		throw_exception("The value must be >= 0", 40);
}

void check_component_name(string str)
{	
	if (str != "red" && str != "blue" && str != "green")
		throw_exception("Value must be red, green or blue", 40);
}

void print_help()
{
	cout << "Course work for option 5.8, created by Kirill Verdin.\n";
	cout << "Options:\n\n"
	"--input/-i - enter path of input file\n"
	"--output/-o - enter path of output file\n\n"
	"--info - print info about image\n\n"
	"--help/-h - print list of functions\n\n"
	"--filled_rects - find all rectangles of the certain color\n"
	"--color <r.g.b> - color of rectangles\n"
	"--border_color <r.g.b> - border_color of rectangles\n"
	"--thickness - thickness of border line of rectange\n\n"
	"--circle - draw circle\n"
	"--center <x.y> - coordinates of the center of circle\n"
	"--radius - radius of circle\n"
	"--color <r.g.b> - color of border of circle\n"
	"--thickness - thickness of border line\n"
	"--fill - fill/not fill circle\n"
	"--fill_color <r.g.b> color of circle\n\n"
	"--rgbfilter - change the value of 1 component of color for whole image\n"
	"--component_name <red/green/blue> - name of RGB component that would change\n"
	"--component_value -- value of RGB component\n\n"
	"--split - split image on x*y parts\n"
	"--number_x - number of parts on axis y\n"
	"--number_y - number of parts on axis x\n"
	"-thickness - thickness of line\n"
	"--color <r.g.b> - color of line\n";
}