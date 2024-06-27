#include "data_processing.h"
#include "structs_libraries.h"
#include "general_functions.h"
#include "output_functions.h"


int main()
{
    setlocale(LC_CTYPE, "");
    struct Text text;
    struct Sentence * sentences_array;
    int chosen_function;
    wprintf(COURSE_WORK_INFO);
    chosen_function = read_number();
    process_chosen_function(chosen_function, &sentences_array, &text);
    clean_memory(sentences_array, &text);
    return 0;
}
