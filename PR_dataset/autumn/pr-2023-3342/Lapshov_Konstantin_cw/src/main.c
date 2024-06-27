#include <locale.h>

#include "structures.h"
#include "text_io.h"

#include "get_unique_words.h"
#include "change_digits.h"
#include "sort_text.h"
#include "change_cyrillic_sentence.h"
#include "change_text.h"

void menu(size_t choice);

int main() {
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.17, created by Lapshov Konstantin.\n");

    size_t choice;
    wscanf(L"%ld", &choice);

    menu(choice);

    return 0;
}
void menu(size_t choice){
    size_t word_length;
    struct Text curr_text = create_text();

    switch (choice) {
        case 0:
            input_text(&curr_text);
            output_text(curr_text);
            free_text(&curr_text);
            break;
        case 1:
            input_text(&curr_text);
            get_unique_words(curr_text);
            free_text(&curr_text);
            break;
        case 2:
            input_text(&curr_text);
            change_digits(&curr_text);
            output_text(curr_text);
            free_text(&curr_text);
            break;
        case 3:
            input_text(&curr_text);
            sort_text(&curr_text);
            output_text(curr_text);
            free_text(&curr_text);
            break;
        case 4:
            input_text(&curr_text);
            change_sentence(&curr_text);
            output_text(curr_text);
            free_text(&curr_text);
            break;
        case 5:
            print_reference();
            break;
        case 9:
            word_length = get_word_length();
            input_text(&curr_text);
            change_text(&curr_text, word_length);
            output_text(curr_text);
            free_text(&curr_text);
            break;
        default:
            wprintf(L"Error: Неверный ввод\n");
            break;
    }
}