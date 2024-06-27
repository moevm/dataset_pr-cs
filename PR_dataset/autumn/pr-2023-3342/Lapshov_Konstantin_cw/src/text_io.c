#include "text_io.h"

int check_similar_sen(struct Text text, struct Sentence sen){
    int is_similar = 0;

    if(text.quantity_of_sentences != 0){
        for (int i = 0; i < text.quantity_of_sentences; i++) {

            if(text.sentences[i].quantity_of_words == sen.quantity_of_words){
                int count_of_similar_word = 0;

                for (int j = 0; j < text.sentences[i].quantity_of_words; j++) {
                    if(text.sentences[i].words[j].quantity_of_letters == sen.words[j].quantity_of_letters){

                        if(wcsncmp(
                                text.sentences[i].words[j].punctuation,
                                sen.words[j].punctuation,
                                text.sentences[i].words[j].quantity_of_punctuation
                                ) == 0
                                ){
                            int k;
                            for (k = 0; k < text.sentences[i].words[j].quantity_of_letters; ++k) {
                                if(towlower(text.sentences[i].words[j].letters[k]) != towlower(sen.words[j].letters[k])){
                                    break;
                                }
                            }
                            if(k == text.sentences[i].words[j].quantity_of_letters){
                                count_of_similar_word++;
                            }
                        }
                    }
                }
                if(count_of_similar_word == text.sentences[i].quantity_of_words){
                    is_similar = 1;
                }
            }
        }
    }

    if(is_similar){
        return 0;
    }

    return 1;
}

void input_text(struct Text* text){
    wchar_t symbol = getwchar();
    wchar_t last_symbol;

    struct Sentence curr_sen = create_sentence();
    struct Word curr_word = create_word();

    while(1){
        if(symbol == L'\n' && last_symbol == L'\n'){
            break;
        }

        if(check_for_end_of_word(curr_word, symbol, last_symbol)){
            add_word(&curr_sen, curr_word);
            curr_word = create_word();
        }


        if(curr_sen.quantity_of_words == 0 && curr_word.quantity_of_letters == 0){
            if(!iswspace(symbol) && symbol != L'.'){
                add_letters(&curr_word, symbol);
            }
        }else{
            add_symbol(&curr_word, symbol);
        }

        if(symbol == L'.'){
            if(curr_word.quantity_of_letters != 0){
                add_word(&curr_sen, curr_word);
                curr_word = create_word();

                if(check_similar_sen(*text, curr_sen)){
                    add_sentence(text, curr_sen);
                } else{
                    free_sentence(curr_sen);
                }

                curr_sen = create_sentence();
            }
        }

        last_symbol = symbol;
        symbol = getwchar();
    }
}



size_t check_for_end_of_word(struct Word word, wchar_t symbol, wchar_t last_symbol){
    size_t is_end = 0;

    if(word.quantity_of_letters != 0) {
        if (!iswspace(symbol) && !iswpunct(symbol)) {
            if(iswspace(last_symbol) || last_symbol == L',' || last_symbol == L'.'){
               is_end = 1;
            }
        }
    }

    return is_end;
}
void add_symbol(struct Word *word, wchar_t symbol){
    if(iswspace(symbol) || symbol == L',' || symbol == L'.'){
        add_punctuation(word, symbol);
    }else{
        add_letters(word, symbol);
    }
}
void free_sentence(struct Sentence sentence){
    for (int i = 0; i < sentence.quantity_of_words; ++i) {
        free(sentence.words[i].letters);
        free(sentence.words[i].punctuation);
    }
    free(sentence.words);
}

void output_text(struct Text text){
    for (int i = 0; i < text.quantity_of_sentences; i++) {
        for (int j = 0; j < text.sentences[i].quantity_of_words; j++) {
            wprintf(L"%ls%ls", text.sentences[i].words[j].letters, text.sentences[i].words[j].punctuation);
        }
        wprintf(L"\n");
    }
}
void free_text(struct Text* text){
    for (int i = 0; i < text->quantity_of_sentences; i++) {
        for (int j = 0; j < text->sentences[i].quantity_of_words; j++) {
            free(text->sentences[i].words[j].letters);
            free(text->sentences[i].words[j].punctuation);
        }
        free(text->sentences[i].words);
    }
    free(text->sentences);
}
void print_reference(){
    wprintf(L"0 - Вывод текста после первичной обязательной обработки\n");
    wprintf(L"1 - Распечатать каждое слово (с учетом регистра), которое встречается минимум три раза в тексте, а также количество вхождений каждого такого слова в текст.\n");
    wprintf(L"2 - Заменить каждый символ цифры на число вхождений данной цифры во всем тексте.\n");
    wprintf(L"3 - Отсортировать слова в предложениях по уменьшению количеству латинских букв в словах.\n");
    wprintf(L"4 - Поменять порядок слов на обратный в предложениях, которые состоят только из кириллических букв.\n");
    wprintf(L"5 - Вывод справки о функциях.\n");
    wprintf(L"9 - Поменять все слова на '(большое слово)', чья длина больше чем длина входного слова\n");
}