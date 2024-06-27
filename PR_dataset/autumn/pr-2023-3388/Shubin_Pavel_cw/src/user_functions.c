    #include "user_functions.h"

int cnt_num_of_secs (struct Text text) {
    int sum = 0;
    for (int i = 0; i < text.amount_of_sentences; i++) {
        struct Sentence *curr_sentence = text.sentences[i];
        for (int j = 1; j < curr_sentence->amount_of_words; j++) {
            wchar_t *curr_word = word_to_str(curr_sentence->words[j]);
            if (wcscmp(curr_word, L"sec") == 0) {
                wchar_t *curr_numb = word_to_str(curr_sentence->words[j - 1]);
                if (is_digit(curr_numb)) {
                    sum += wcstol(curr_numb, NULL, 10);
                }
                free(curr_numb);
            }
            free(curr_word);
        }
    }
    return sum;
}


void sort_by_codes_of_first_words (struct Text *text) {
    qsort(text->sentences, text->amount_of_sentences, sizeof(struct Sentence *), compare_sentences);
}


void replace_option_chars (struct Text *text) {
    for (int i = 0; i < text->amount_of_sentences; i++) {
        wchar_t *curr_sentence = text->sentences[i]->sentence;
        int memory = (int)wcslen(curr_sentence) + 2;
        int cnt_for_signs = 0;
        for (int j = 0; curr_sentence[j]; j++) {
            if (curr_sentence[j] == L'%' || curr_sentence[j] == L'#') {
                memory += 9;
                cnt_for_signs += 1;
            }
            if (curr_sentence[j] == L'@') {
                memory += 4;
                cnt_for_signs += 1;
            }
        }
        wchar_t *old_curr_sent = realloc(curr_sentence, memory * sizeof(wchar_t));
        if (old_curr_sent == NULL) {
            fwprintf(stderr, L"Ошибка перераспределения памяти.\n");
            exit(4);
        } else {
            text->sentences[i]->sentence = old_curr_sent;
        }
        curr_sentence = text->sentences[i]->sentence;
        while (cnt_for_signs > 0) {
            wchar_t *pnt;
            if ((pnt = wcschr(curr_sentence, L'%')) != NULL) {
                insert_word(curr_sentence, (int) (pnt - curr_sentence), PERCENT);
                cnt_for_signs -= 1;
            }
            if ((pnt = wcschr(curr_sentence, L'#')) != NULL) {
                insert_word(curr_sentence, (int) (pnt - curr_sentence), SHARP);
                cnt_for_signs -= 1;
            }
            if ((pnt = wcschr(curr_sentence, L'@')) != NULL) {
                insert_word(curr_sentence, (int) (pnt - curr_sentence), AT);
                cnt_for_signs -= 1;
            }
        }
    }
}


void delete_sentences_with_three_consonants_in_last_word (struct Text *text) {
    int i = 0;
    while (i < text->amount_of_sentences) {
        if (word_have_three_consonants(word_to_str(text->sentences[i]->words[text->sentences[i]->amount_of_words - 1]))) {
            delete_sentence(text, i);
        } else {
            i += 1;
        }
    }
}

void palindrome_sentence_func(struct Text *text){
    for(int i = 0; i < text->amount_of_sentences; i++){
        int flag = 0;
        wchar_t *only_symbols = (wchar_t*)malloc((wcslen(text->sentences[i]->sentence)+1)*sizeof(wchar_t));

        if (only_symbols == NULL){
            perror("Ошибка выделения памяти");
            exit(EXIT_FAILURE);
        }

        int only_symbols_index = 0;

        for(int j = 0; j < wcslen(text->sentences[i]->sentence); j++){
            if(iswalpha(text->sentences[i]->sentence[j])){
                only_symbols[only_symbols_index++] = text->sentences[i]->sentence[j];
            }
        }
        only_symbols[only_symbols_index] = L'\0';
        int cnt = wcslen(only_symbols) - 1;

        for(int j = 0; j < wcslen(only_symbols)/2; j++){
            if(towlower(only_symbols[j]) != towlower(only_symbols[cnt])){
                flag = 1;
                break;
            }
            cnt--;
        }
        if (flag == 0){
            wprintf(L"%ls\n", text->sentences[i]->sentence);
        }
        free(only_symbols);
    }
}


