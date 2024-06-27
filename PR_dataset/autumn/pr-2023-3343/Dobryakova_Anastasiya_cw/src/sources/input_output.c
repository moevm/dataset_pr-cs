#include "../include/input_output.h"
  
void print_help(){
    wprintf(L"0 - вывод текста после первичной обязательной обработки;\n");
    wprintf(L"1 - печать каждого слова (с учетом регистра), которое встречается минимум три раза в тексте, а также количество вхождений каждого такого слова в текст;\n");
    wprintf(L"2 - замена каждого символа цифры на число вхождений данной цифры во всем тексте;\n");
    wprintf(L"3 - сортировка слов в предложениях по уменьшению количества латинских букв в словах;\n");
    wprintf(L"4 - смена порядка слов на обратный в предложениях, которые состоят только из кириллических букв;\n");
    wprintf(L"5 - вывод справки о функциях, которые реализует программа.\n");
    wprintf(L"8 - вывод суммы чисел в каждом предложении.\n");
}

Text input_text(){
    Text text;
    int end_counter = 0;
    text.sentences = malloc(sizeof(Sentence));
    int text_size = 0;
    int text_buffer = 1;
    while(1){
        Sentence current_sentence = input_sentence(&end_counter);
        int equal_sentence = 0;
        for(int i = 0; i < text_size; ++i){
            if(wcscasecmp(current_sentence.chars, text.sentences[i].chars) == 0){
                equal_sentence=1;
                break;
            }
        }
        if (end_counter == 2) break;
        else end_counter = 0;
        if (equal_sentence == 1) continue;
        wchar_t* tok_buffer;
        if(wcstok(wcsdup(current_sentence.chars), L" ,.", &tok_buffer) == NULL) continue;
        text.sentences[text_size] = current_sentence;
        text_size++;
        text.size = text_size;
        if (text_size == text_buffer){
            text_buffer *= 2;
            text.sentences = realloc(text.sentences, sizeof(Sentence) * text_buffer);
        }
    }
    if (text.sentences[0].chars == NULL){
        fwprintf(stderr, L"Error: Неверный ввод данных.\n");
        exit(0);
    }
    return text;
}

Sentence input_sentence(int* end_counter){
    Sentence sentence;
    sentence.chars = malloc(sizeof(wchar_t) + 1);
    int sentence_size = 0;
    int sentence_buffer = 1;
    wchar_t current_char;
    int first_char = 1;
    do{
        current_char = getwchar();
        if (current_char == L'\n'){
            (*end_counter)++;
            if ((*end_counter) == 2){
                break;
            }
            continue;
        }
        if (first_char && iswspace(current_char)) continue;
        first_char = 0;
        sentence.chars[sentence_size++] = current_char;
        if (sentence_size == sentence_buffer) {
            sentence_buffer *= 2;
            sentence.chars = realloc(sentence.chars, sizeof(wchar_t) * sentence_buffer);
        }
    } while (current_char != L'.');
    sentence.chars[sentence_size] = L'\0';
    sentence.size = sentence_size;
    return sentence;
}

void print_text(Text text){
    for (int i = 0; i < text.size; i++){
        wprintf(L"%ls\n", text.sentences[i].chars);
    }
    wprintf(L"\n");
}
