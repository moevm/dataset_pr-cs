/**
 * @file messages.h
 * @brief Заголовочный файл, содержащий определения структур и классов.
 */

#pragma once
/**
 * @brief Error code for file not found.
 */
#define ERR_FILE_NOT_FOUND 40

/**
 * @brief Error code for incorrect file format.
 */
#define ERR_INCORRECT_FILE_FORMAT 41

/**
 * @brief Error code for file write error.
 */
#define ERR_FILE_WRITE_ERROR 42

/**
 * @brief Error code for invalid argument.
 */
#define ERR_INVALID_ARGUMENT 43

/**
 * @brief Error code for insufficient arguments.
 */
#define ERR_INSUFFICIENT_ARGUMENTS 45

const std::string hello_message = "Course work for option 5.2, created by Egor Grebnev.";
/**
 * @brief Message for invalid BMP file.
 */
const std::string invalid_bmp_message = "Invalid bmp file!";

/**
 * @brief Message when input file is same as output file.
 */
const std::string same_input_output_message = "Input file is the same as output file!";

/**
 * @brief Success message.
 */
const std::string success_message = "Success!";

/**
 * @brief Warning for requested mirror operation.
 */
const std::string mirror_warning = "=Mirror operation requested!=";

/**
 * @brief Warning for requested color replace operation.
 */
const std::string color_replace_warning = "=Color replace operation requested!=";

/**
 * @brief Warning for requested image split operation.
 */
const std::string image_split_warning = "=Image split operation requested=";

/**
 * @brief Warning for requested image copy operation.
 */
const std::string image_copy_warning = "=Image copy operation requested=";

// OPERATIONS

/**
 * @brief Error for invalid color format.
 */
const std::string invalid_color_format_error = "Invalid color format";

/**
 * @brief Error when color is out of range [0-255].
 */
const std::string invalid_color_range_error = "Color out of range [0-255] got: ";

/**
 * @brief Error for invalid coordinate format.
 */
const std::string invalid_coordinate_format_error = "Invalid coordinate format";

/**
 * @brief Error for invalid argument for certain operation.
 */
const std::string invalid_argument_error = "Invalid argument for ";

/**
 * @brief Warning for unexpected option.
 */
const std::string unexpected_option_warning = "Unexpected option: ";

// BMP

/**
 * @brief Error when failed to open input BMP file.
 */
const std::string open_bmp_error = "Failed to open input BMP file: ";

/**
 * @brief Error when BMP file header is invalid.
 */
const std::string invalid_header_error = "BMP file header is invalid: ";

/**
 * @brief Error for invalid BMP file signature.
 */
const std::string invalid_signature_error = "Invalid BMP file signature";

/**
 * @brief Error for invalid BMP dimensions.
 */
const std::string invalid_dimensions_error = "Invalid BMP dimensions";

/**
 * @brief Warning for invalid BMP bits per pixel.
 */
const std::string invalid_bpp_warning = "Invalid BMP bits per pixel, output image may be incorrect";

/**
 * @brief Error for unsupported BMP compression type.
 */
const std::string unsupported_compression_error = "Unsupported BMP compression type";

/**
 * @brief Error for invalid BMP image size.
 */
const std::string invalid_image_size_error = "Invalid BMP image size, output image may be incorrect";

/**
 * @brief Warning for trying to access color outside image bounds.
 */
const std::string access_outside_bounds_warning = "Trying to access color outside image bounds";

/**
 * @brief Warning for trying to set color outside image bounds.
 */
const std::string set_outside_bounds_warning = "Trying to set color outside image bounds";

/**
 * @brief Error for invalid mirror axis specified.
 */
const std::string invalid_mirror_axis_error = "Invalid mirror axis specified";

/**
 * @brief Error for invalid split parameters.
 */
const std::string invalid_split_parameters_error = "Invalid split parameters";

/**
 * @brief Error when copying region exceeds destination image boundaries.
 */
const std::string copy_exceeds_bounds_error = "Copying region exceeds destination image boundaries.";

/**
 * @brief Error when failed to create output BMP file.
 */
const std::string failed_create_output_file = "Failed to create output BMP file: ";

/**
 * @brief Error for invalid copy region or destination parameters.
 */
const std::string invalid_copy_region = "Invalid copy region or destination parameters";

// Help message descriptions

/**
 * @brief Usage description of the program.
 */
const std::string help_usage_description = "Usage: program_name [options] filename";

/**
 * @brief Start of the description of options.
 */
const std::string help_usage_start = "Options: ";

/**
 * @brief Description of --mirror option.
 */
const std::string mirror_option_description = "  --mirror               Mirror operation";

/**
 * @brief Description of --axis option.
 */
const std::string axis_option_description = "  --axis <value>         Axis of operation";

/**
 * @brief Description of --left_up option.
 */
const std::string left_up_option_description = "  --left_up <x.y>        Coordinates of left-up corner";

/**
 * @brief Description of --right_down option.
 */
const std::string right_down_option_description = "  --right_down <x.y>     Coordinates of right-down corner";

/**
 * @brief Description of --dest_left_up option.
 */
const std::string dest_left_up_option_description = "  --dest_left_up <x.y>   Coordinates of destination left-up corner";

/**
 * @brief Description of --old_color option.
 */
const std::string old_color_option_description = "  --old_color <r.g.b>    Old color to replace";

/**
 * @brief Description of --new_color option.
 */
const std::string new_color_option_description = "  --new_color <r.g.b>    New color to replace with";

/**
 * @brief Description of --color option.
 */
const std::string color_option_description = "  --color <r.g.b>        Color of line";

/**
 * @brief Description of --copy option.
 */
const std::string copy_option_description = "  --copy                 Copy operation";

/**
 * @brief Description of --color_replace option.
 */
const std::string color_replace_option_description = "  --color_replace        Color replace operation";

/**
 * @brief Description of --split option.
 */
const std::string split_option_description = "  --split                Split operation";

/**
 * @brief Description of --number_x option.
 */
const std::string number_x_option_description = "  --number_x <value>     Number of elements along x-axis";

/**
 * @brief Description of --number_y option.
 */
const std::string number_y_option_description = "  --number_y <value>     Number of elements along y-axis";

/**
 * @brief Description of --thickness option.
 */
const std::string thickness_option_description = "  --thickness <value>    Thickness of operation";

/**
 * @brief Description of --output option.
 */
const std::string output_option_description = "  -o, --output <file>    Output file";

/**
 * @brief Description of --input option.
 */
const std::string input_option_description = "  -i, --input <file>     Input file";

/**
 * @brief Description of --help option.
 */
const std::string help_option_description = "  -h, --help             Display this information";

// Info message

/**
 * @brief Signature of the file message.
 */
const std::string signature_message = "Signature: ";

/**
 * @brief File size message.
 */
const std::string file_size_message = "File size: ";

/**
 * @brief Data offset message.
 */
const std::string data_offset_message = "Data offset: ";

/**
 * @brief Header size message.
 */
const std::string header_size_message = "Header size: ";

/**
 * @brief Image dimensions message.
 */
const std::string image_dimensions_message = "Image dimensions: ";

/**
 * @brief Bits per pixel message.
 */
const std::string bits_per_pixel_message = "Bits per pixel: ";

/**
 * @brief Compression message.
 */
const std::string compression_message = "Compression: ";

/**
 * @brief Image size message.
 */
const std::string image_size_message = "Image size: ";

/**
 * @brief Pixels per meter message for X axis.
 */
const std::string pixels_per_meter_x_message = "Pixels per meter (X axis): ";

/**
 * @brief Pixels per meter message for Y axis.
 */
const std::string pixels_per_meter_y_message = "Pixels per meter (Y axis): ";

/**
 * @brief Colors used message.
 */
const std::string colors_used_message = "Colors used: ";

/**
 * @brief Important colors message.
 */
const std::string important_colors_message = "Important colors: ";

/**
 * @brief Error message for the usage of two incompatible functions.
 */
const std::string double_function_use_err = "Incompatible functions";

/**
 * @brief Error message for too many arguments provided.
 */
const std::string too_many_args_err = "Too many arguments";
