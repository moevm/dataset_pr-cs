#include "structures.h"
#include "info_functions.h"
#include "flags_processing.h"
#include "bmp_functions.h"

int main(int argc, char* argv[]){
    printf("Course work for option 4.12, created by Rustam Abdusalamov\n");
    Parameters param;
    parse_command_line(argc, argv, &param);
    BMP* picture = read_BMP(param.input_name);
    if (param.info){
        print_file_header(picture->bmfh);
        print_info_header(picture->bmih);
    }
    if (param.rgb_filter)
        rgb_filter(param.component_name, param.component_value, picture);
    if (param.rotate)
        rotate(picture, param.left, param.up, param.right, param.down, param.angle);
    if (param.squared_lines)
        squared_lines(picture, param.left, param.up, param.side_size, param.thickness, *(param.color), param.fill, (param.fill_color));
    if (param.square_rhombus)
        square_rhombus(picture, param.left, param.up, param.side_size, param.fill_color);
    write_BMP(param.output_name, picture);
    return 0;
}

