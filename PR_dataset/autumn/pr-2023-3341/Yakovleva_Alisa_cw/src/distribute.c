#include "distribute.h"

int check_function_number(int* number_function)
{
    if(!wscanf(L"%d", number_function))
    {
        wprintf(L"Error: не удалось считать номер функции.\n");
        return 0;
    }
    if (*number_function < 0 || (*number_function > NUMBER_OF_FUNCTIONS && *number_function != NUMBER_OF_ADDED_FUNCTION)){
        wprintf(L"Error: введён неверный номер функции.\n");
        return 0;
    }
    if (*number_function == 5)
    {
        help();
        return 0;
    }
    return 1;
}

void distribute(int function_number, struct Text* text)
{
    switch (function_number)
    {
        case 1:
            transliteration(*text);
            break;
        case 2:
            output_special_wchar(*text);
            break;
        case 3:
            replace_numbers(*text);
            break;
        case 4:
            delete_sentences_with_odd_numbers(text);
        case 9:
            double_word(*text);
    }
}
