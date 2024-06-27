#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

int is_latin(wchar_t ch) {
    wchar_t* latin_alphabet = L"abcdefghijklmnopqrstuvwxyz";
    if (wcschr(latin_alphabet, towlower(ch))) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_cyrillic(wchar_t ch) {
    wchar_t* cyrillic_alphabet = L"абвгдеёжзклмнопрстуфхцчшщъыьэюя";
    if (wcschr(cyrillic_alphabet, towlower(ch))) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_special_symbol(wchar_t ch) {
    wchar_t* special_symbol_list = L"№*$#@.,;";
    if (wcschr(special_symbol_list, ch)) {
        return 1;
    }
    else {
        return 0;
    }
}
