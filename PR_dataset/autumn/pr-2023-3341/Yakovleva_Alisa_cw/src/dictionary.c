#include "dictionary.h"

wchar_t* dictionary_digit(wchar_t key)
{
    switch(key)
    {
        case '0': 
            return L"0";
        case '1':
            return L"1";
        case '2': 
            return L"10";
        case '3': 
            return L"11";
        case '4': 
            return L"100";
        case '5': 
            return L"101";
        case '6': 
            return L"110";
        case '7': 
            return L"111";
        case '8': 
            return L"1000";
        case '9': 
            return L"1001";
    }
}

wchar_t* dictionary_russian_alphabet(wchar_t key)
{
    switch(key)
    {
        case L'а': 
            return L"a";
        case L'б':
            return L"b";
        case L'в': 
            return L"v";
        case L'г': 
            return L"g";
        case L'д': 
            return L"d";
        case L'е': 
            return L"e";
        case L'ё': 
            return L"yo";
        case L'ж': 
            return L"zh";
        case L'з': 
            return L"z";
        case L'и': 
            return L"i";
        case L'й': 
            return L"j";
        case L'к': 
            return L"k";
        case L'л': 
            return L"l";
        case L'м': 
            return L"m";
        case L'н': 
            return L"n";
        case L'о': 
            return L"o";
        case L'п': 
            return L"p";
        case L'р': 
            return L"r";
        case L'с': 
            return L"s";
        case L'т': 
            return L"t";
        case L'у': 
            return L"u";
        case L'ф': 
            return L"f";
        case L'х': 
            return L"x";
        case L'ц': 
            return L"cz";
        case L'ч': 
            return L"ch";
        case L'ш': 
            return L"sh";
        case L'щ': 
            return L"shh";
        case L'ъ': 
            return L"''";
        case L'ы': 
            return L"y'";
        case L'ь': 
            return L"'";
        case L'э': 
            return L"e'";
        case L'ю': 
            return L"yu";
        case L'я': 
            return L"ya";
        default:
            return L".";
    }
}
