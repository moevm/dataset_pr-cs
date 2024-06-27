#include "input/input.h"
#include "bmp/bmp.h"
#include <iostream>


int main(int argc, char** argv)
{	
	unordered_map<string, string> input_info = input(argc, argv);
	if (input_info.find("help") != input_info.end() || input_info.find("h") != input_info.end())
	{
		print_help();
		if (input_info.size() == 2)
			return 0;
	}
	input_data* data = check_input(input_info);
	BMP image;
	image.read(data->input_path.c_str());
	if(input_info.find("info") != input_info.end())
	{
		image.print_file_header();
		image.print_info_header();
	}
	if (data->function == "filled_rects")
	{
		image.filled_rects(data->color, data->thickness, data->border_color);
	}
	else if (data->function == "circle")
	{	
		if (data->fill)
			image.draw_circle(data->circle, data->color, data->thickness, data->fill_color);

		else
			image.draw_circle(data->circle, data->color, data->thickness);
	}
	else if (data->function == "rgbfilter")
	{
		image.rgbfilter(data->component_name, data->component_value);
	}
	else if (data->function == "split")
	{
		image.split(data->number_x, data->number_y, data->thickness, data->color);
	}
	else if (data->function == "rhombus")
	{
		image.rhombus(data->color);
	}
	image.write(data->output_path.c_str());
	return 0;
}