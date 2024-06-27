#include "menu.h"


void print_all(text_t text, size_t* size, size_t** str_sizes) {
    for (size_t i = 0; i < *size; i++) {
        for (size_t j = 0; j < (*str_sizes)[i]; j++)
            put(text[i][j]);
        put(L'\n');
    }
}

void menu(char input){
    switch (input){
        case '5':
            print_help();
            break;
        default:{
            if (!(input >= '0' && input <= '4') && (input != '9'))
                panic("Error: нет такой команды!");
            size_t  text_size;
            size_t* str_size;
            text_t  text = read_text(&text_size, &str_size);
            text = unique(text, &text_size, &str_size);
            switch (input){
                case '9':
                    text = sort_text(text,text_size);
                    for (size_t i = 0;i < text_size;i++)
                        printf("%s\n",text[i]);
                    break;
                case '0':
                    print_all(text, &text_size, &str_size);
                    break;
                case '1':
                    text = replace_dates(text, &text_size, &str_size);
                    print_all(text, &text_size, &str_size);
                    break;
                case '2':
                    text = color_words(text, &text_size, &str_size);
                    print_all(text, &text_size, &str_size);
                    break;
                case '3':
                    text = delete_with_same_begin_end(text, &text_size, &str_size);;
                    print_all(text, &text_size, &str_size);
                    break;
                case '4':
                    text = sort_by_codes(text, &text_size, &str_size);
                    print_all(text, &text_size, &str_size);
                    break;
                default:
                    panic("Error: нет такой команды!");
            }
        }
    }
}


