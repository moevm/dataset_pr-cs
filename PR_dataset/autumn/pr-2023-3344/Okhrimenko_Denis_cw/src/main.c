#include "base_library.h"
#include "printF_text.h"
#include "input.h"
#include "text_to_words.h"
#include "find_middle_time_and_translate.h"
#include "compare.h"
#include "find_dates.h"
#include "delete_same_words_sent.h"
#include "is_happened.h"
#include "foo.h"

int main()
{
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.15, created by Denis Okhrimenko.\n");
    size_t option = -1;
    text_t* text;
    text_t* _words;
    // goto_choice:
    wscanf(L"%ld", &option);
    switch(option)
    {
        case(0):
        {
            // if(text != NULL){
            //     wprintf(L"Текст был введён ранее, выберите другую опцию\n");
            //     goto goto_choice;
            //     }
            text = read_text();
            printF_text(text);
            // goto goto_choice;
            break;
        }
        case(1):
        {
            text = read_text();
            find_middle_time_and_translate(text);
            printF_text(text);
            break;
        }
        case(2):
        {
            text = read_text();
            _words = text_to_words(text);
            find_dates(_words);
            break;
        }
        case(3):
        {
            text = read_text();
            delete_same_words_sent(text);
            printF_text(text);
            break;
        }
        case(4):
        {
            text = read_text();
            _words = text_to_words(text);
            is_happened(_words);
            break;
        }
        case(5):
        {
            printOptions();
            // goto goto_choice;
            return 0;
        }
	case(9):
        {
            text = read_text(text);
            foo(text);
            break;
        }
        default: 
            printError(L"Неверный ввод Выбора опции");
    }
    cleanUpMemory(text);
    return 0;
}
