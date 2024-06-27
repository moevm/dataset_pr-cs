#include "../include/main.h"
  
int main(){

    setlocale(LC_ALL, "");

    wprintf(L"Course work for option 5.17, created by Anastasiya Dobryakova.\n");

    int user_choice;
    wscanf(L"%d", &user_choice);

    switch(user_choice){
        case 0:
            print_text(input_text());
            break;

        case 1:
            print_words_count(input_text());
            break;

        case 2:
            print_replace_num(input_text());
            break;

        case 3:
            print_text(sort_words(input_text()));
            break;

        case 4:
            print_text(sort_sentences(input_text()));
            break;

        case 5:
            print_help();
            break;
      
        case 8:
            summ_numbers(input_text());
            break;

        default:
            fwprintf(stderr, L"Error: Неправильная функция. Введите 5 для вывода списка функций.\n");
    }
    return 0;
}
