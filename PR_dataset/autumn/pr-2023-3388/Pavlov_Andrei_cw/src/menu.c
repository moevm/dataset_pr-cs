#include "menu.h"


void print_all(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        for (size_t j = 0; j < text->data[i]->size; j++)
            write(text->data[i]->data[j]);
        write(L'\n');
    }
}

void menu(int input) {
    if (input == 5) {
        print_help();
        return;
    } else if (input == 9) {
        int a = 0;
        a += 2;
    } else if (!(input >= 0) || !(input <= 4)) panic(L"Error: there is no such command!");

    Text* text = read_text();
    text = save_only_unique(text, wcsincmp);

    switch (input) {
    case 0:
        print_all(text);
        break;
    case 1:
        find_and_print(text, find_times, print_times);
        break;
    case 2:
        apply(text, delete_big_latin);
        print_all(text);
        break;
    case 3:
        text = sort(text, calc_cyrillic_diff);
        print_all(text);
        break;
    case 4:
        text = filter(text, have_spec_symbols);
        print_all(text);
        break;
    case 9:
        apply(text, copy_words);
        print_all(text);
        break;
    }
}
