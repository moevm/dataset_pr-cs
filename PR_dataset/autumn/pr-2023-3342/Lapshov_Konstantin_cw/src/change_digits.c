#include "change_digits.h"

void change_digits(struct Text *text){
    struct Unique_Word numbers[10] = {
            {L"0", 0},
            {L"1", 0},
            {L"2", 0},
            {L"3", 0},
            {L"4", 0},
            {L"5", 0},
            {L"6", 0},
            {L"7", 0},
            {L"8", 0},
            {L"9", 0},
    };

    get_digit_occurrences(text, numbers);
    change_digit_for_occurrences(text, numbers);
}

//Подсчет кол-ва цифр
void get_digit_occurrences(struct Text *text, struct Unique_Word numbers[]){
    for (int i = 0; i < text->quantity_of_sentences; ++i) {
        struct Sentence *current_sen = &text->sentences[i];
        for (int j = 0; j < current_sen->quantity_of_words; ++j) {
            struct Word *current_word = &current_sen->words[j];
            for (int k = 0; k < current_word->quantity_of_letters; ++k) {
                if(iswdigit(current_word->letters[k])){
                    numbers[get_digit_from_str(current_word->letters[k])].word_count++;
                }
            }
        }
    }
}
//Перестановка цифр на их кол-во вхождений
void change_digit_for_occurrences(struct Text *text, struct Unique_Word numbers[]){
    for (int i = 0; i < text->quantity_of_sentences; ++i) {
        struct Sentence *current_sen = &text->sentences[i];
        for (int j = 0; j < current_sen->quantity_of_words; ++j) {
            struct Word *current_word = &current_sen->words[j];
            for (int k = 0; k < current_word->quantity_of_letters;) {
                if(iswdigit(current_word->letters[k])){
                    //Получение кол-во вхождений
                    size_t count = numbers[get_digit_from_str(current_word->letters[k])].word_count;

                    //Перевод кол-ва в строку
                    wchar_t count_text[256];
                    swprintf(count_text, 256, L"%d", count);

                    //Меняем строку
                    current_word->letters = insert_wchar(current_word->letters, k, count_text);
                    k += wcslen(count_text);
                }else{
                    k++;
                }
            }
        }
    }
}
long get_digit_from_str(wchar_t letter){
    wchar_t tmp_string[2] = {letter, L'\0'};
    long numb = wcstol(tmp_string, NULL, 10);

    return numb;
}
wchar_t* insert_wchar(wchar_t* str, int position, const wchar_t* new_chars) {
    // Подсчет длины исходной строки и новых символов
    size_t original_length = wcslen(str);
    size_t new_chars_length = wcslen(new_chars);

    // Выделяем память под новую строку
    wchar_t* new_str = (wchar_t*)malloc(((original_length + new_chars_length + 1) * sizeof(wchar_t)));

    // Копируем начальную часть строки до вставки
    wmemcpy(new_str, str, position);
    // Копируем новые символы
    wcscpy(new_str + position, new_chars);
    // Копируем оставшуюся часть исходной строки
    wmemcpy(new_str + position + new_chars_length, str + 1 + position, original_length - position + 1);

    free(str);
    return new_str;
}