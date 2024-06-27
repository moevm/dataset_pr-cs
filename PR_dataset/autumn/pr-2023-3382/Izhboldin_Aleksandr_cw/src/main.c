// base libs
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

// in-project libs
#include "data_processing.h"
#include "error_handle.h"
#include "defence.h"

int main(void)
{
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.10, created by Aleksandr Izhboldin.\n");
    int err = 0;
    int choice = -1;
    wscanf(L"%d\n", &choice);
    switch (choice)
    {
        case (0):
            print_basic_processed_text(&err);
            break;
        case (1): // function 1
            check_text_on_palindromes(&err);
            break;
        case (2): // function 2
            change_special_symbols(&err);
            break;
        case (3): // function 3
            sort_by_latin_letters(&err);
            break;
        case (4): // function 4
            delete_mixed_sentence(&err);
            break;
        case (5): // function 5
            help();
            break;
        case (9): // function 5
            def_task(&err);
            break;
        default:
            err = WRONG_FUNCTION_ERROR;
            my_error(L"Error", &err);
            help();
            return EXIT_SUCCESS;
    }

    if (err)
        my_error(L"Error", &err);

    return EXIT_SUCCESS;
}
