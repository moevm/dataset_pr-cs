#include <locale.h>
#include "input_text.h"
#include "process_text.h"
#include "distribute.h"
#include "free_memory.h"

int main()
{
    setlocale(LC_CTYPE, "");
    output_course_work_option();
    int number_function;
    if (check_function_number(&number_function))
    {
        struct Text text = read_text();
        if (!text.sents) return 0;
        process_text(&text);
        distribute(number_function, &text);
        if(number_function != 2) output_text(text);
        free_text(text);
    }
    return 0;
}
