#include "errors.h"


const char* input_file_not_found = "No input file!";

const char* same_input_and_output_files = "Input and output files are the same!";

const char* incorrect_file_format = "Incorrect file format!";

const char* can_not_read_the_file = "Can't read the file!";

const char* can_not_write_to_the_file = "Can't write to the file!";

const char* invalid_argument = "Invalid argument!";

const char* missing_required_argument = "Missing required argument!";

const char* missing_required_option = "Missing required option!";

const char* unexpected_option = "Unexpected option!";

const char* multiple_function_request = "Only one function can be called!";

const char* unknown_option = "Unknown option!";

const char* incorrect_rgb_format = "Incorrect RGB format";

const char* invalid_rgb_component_value = "Wrong RGB component value!";

const char* invalid_rgb_component_name = "Companent name must be 'red', 'green' or 'blue'!";

const char* invalid_parts_number = "Wrong parts number!";

const char* invalid_thickness = "Wrong thickness!";

const char* invalid_threshold = "Wrong threshold!";

const char* hello_message = "Course work for option 4.2, created by Otmakhov Danil.";


void raiseError(const char* statement, int exit_code)
{
    fprintf(stderr, "Error: %s\n", statement);
    exit(exit_code);
}
