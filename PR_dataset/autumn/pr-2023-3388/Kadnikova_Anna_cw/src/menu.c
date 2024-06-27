#include "menu.h"


void print_all(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        for (size_t j = 0; j < text->data[i]->size; j++)
            write(text->data[i]->data[j]);
        write(L'\n');
    }
}

void menu(int input) {
    if (input == L'5') {
        print_help();
        return;
    } 

    Text* text = read_text();
    text = unique(text);
    wchar_t** splitted = split(text->data[0]->data, text->data[0]->size);
    
    switch (input) {
    case L'0':
        print_all(text);
        break;
    case L'1':
        apply_fix_endings(text);
        print_all(text);
        break;
    case L'2':
        if (splitted[1] == NULL) {
            error(L"Error: первое предложение не содержит двух слов!");
        }
        for (size_t i = 0; i < text->size; i++) {
            Sentence* current = text->data[i];
            current->data = find_and_print(current->data, splitted[1], &(current->size));
            current->capacity = current->size+1;
        }
        print_all(text);
        break;
    case L'3':
        text = sort_by_words_count(text);
        print_all(text);
        break;
    case L'4':
        text = filter_longer_than_ten(text);
        print_all(text);
        break;
    case L'9':
        double_word_in_every_sentence(text);
        break;
    }
}
