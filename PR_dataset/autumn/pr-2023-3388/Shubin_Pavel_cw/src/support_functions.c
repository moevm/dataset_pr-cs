#include "support_functions.h"

void memory_clean (struct Text *text) {
    for (int i = 0; i < text->amount_of_sentences; i++) {
        free(text->sentences[i]->sentence);
        free(text->sentences[i]);
    }
    free(text->sentences); 
}


struct Word* create_struct_word (wchar_t *token, int len) {
    wchar_t *pntr_to_word = wcsdup(token);
    struct Word *word = malloc(sizeof(struct Word));
    word->word = pntr_to_word;
    word->len = len;
    return word;
}


void record_words (struct Text *text) {
    for (int i = 0; i < text->amount_of_sentences; i++) {
        int mem_size = START_SIZE;
        wchar_t *curr_sentence = text->sentences[i]->sentence;
        wchar_t temp_sent[wcslen(curr_sentence) + 1];
        wcscpy(temp_sent, curr_sentence);
        struct Word **word_pnt = malloc(mem_size * sizeof(struct Word*));
        struct Word *temp_word;
        int j = 0;
        wchar_t *tok_buf;
        wchar_t *token = wcstok(curr_sentence, L" ,.", &tok_buf);
        while (token != NULL) {
            if (j >= mem_size - 1) {
                mem_size += START_SIZE;
                struct Word **old_word_pnt = realloc(word_pnt, mem_size * sizeof(struct Word *));
                if (old_word_pnt == NULL) {
                    wprintf(MEMORY_ERROR);
                    free(word_pnt);
                    exit(3);
                }else {
                    word_pnt = old_word_pnt;
                }
            }
            temp_word = create_struct_word(token, (int)wcslen(token));
            word_pnt[j++] = temp_word;
            token = wcstok(NULL, L" ,.", &tok_buf);
        }
        text->sentences[i]->words = word_pnt;
        text->sentences[i]->amount_of_words = j;
        wcscpy(text->sentences[i]->sentence, temp_sent);
    }
}


void delete_sentence (struct Text *text, int number_of_sentence) {
    struct Sentence *deleted_sentence = text->sentences[number_of_sentence];
    memmove(&text->sentences[number_of_sentence], &text->sentences[number_of_sentence + 1], sizeof(struct Sentence *) * (text->amount_of_sentences - number_of_sentence - 1));
    free(deleted_sentence);
    text->amount_of_sentences = text->amount_of_sentences - 1;
}


void delete_empty_sentences (struct Text *text) {
    int i = 0;
    while (i < text->amount_of_sentences) {
        if (text->sentences[i]->amount_of_words == 0) {
            delete_sentence(text, i);
        } else {
            i += 1;
        }
    }
}


void delete_equal_sentences (struct Text *text) {
    for (int i = 0; i < text->amount_of_sentences; i++) {
        int j = i + 1;
        while (j < text->amount_of_sentences) {
            if (wcscasecmp(text->sentences[i]->sentence, text->sentences[j]->sentence) == 0) {
                delete_sentence(text, j);
            } else {
                j += 1;
            }
        }
    }
}


wchar_t* word_to_str (struct Word *word) {
    wchar_t *str = malloc((word->len + 1) * sizeof(wchar_t));
    wcsncpy(str, word->word, word->len);
    str[word->len] = L'\0';
    return str;
}


int is_digit (wchar_t *str) {
    int tmp = 0;
    for (int i = 0; str[i]; i++) {
        if (iswdigit(str[i])) {
            tmp += 1;
        }
    }
    if (tmp == wcslen(str)) {
        return 1;
    }
    return 0;
}


int cnt_sum_of_coodes_of_first_word (struct Sentence *sentence) {
    int sum = 0;
    for (int i = 0; i < sentence->words[0]->len; i++) {
        sum += (int)sentence->words[0]->word[i];
    }
    return sum;
}


int compare_sentences (const void *first_sentence,const void *second_sentence) {
    int sum_for_first = cnt_sum_of_coodes_of_first_word((*(struct Sentence **) first_sentence));
    int sum_for_second = cnt_sum_of_coodes_of_first_word((*(struct Sentence **) second_sentence));
    return (sum_for_first - sum_for_second);
}


void insert_word (wchar_t *sentence, int ind, wchar_t *word) {
    int new_size = wcslen(sentence) + wcslen(word);
    for (int i = (int)wcslen(sentence) + 1; i >= ind; i--) {
        sentence[i + wcslen(word)] = sentence[i + 1];
    }
    for (int i = 0; word[i]; i++) {
        sentence[ind + i] = word[i];
    }
    sentence[new_size] = 0;
}


int is_consonant (wchar_t ch) {
    wchar_t consonants[] = L"qwrtpsdfghjklzxcvbnmйцкнгшщзхъфвпрлджчсмтб";
    for (int i = 0; consonants[i]; i++) {
        if (towlower(ch) == consonants[i]) {
            return 1;
        }
    }
    return 0;
}


int word_have_three_consonants (wchar_t *word) {
    size_t word_len = wcslen(word);
    if (word_len < 3) return 0;
    for (int i = 0; i < word_len; i++) {
        if (is_consonant(word[i]) && is_consonant(word[i + 1]) && is_consonant(word[i + 2])) {
            return 1;
        }
    }
    return 0;
}


void print_help () {
    wprintf(L"0. Вывод текста с первичной обработкой;\n");
    wprintf(L"1. Посчет и вывод в минутах количества секунд встречающихся в тексте. Количество секунд задается в виде подстроки <число> sec.;\n");
    wprintf(L"2. Сортировка предложений по увеличению сумм кодов символов первого слова в предложении;\n");
    wprintf(L"3. Замена символов '%', '#' и '@' на <percent>, <решетка> и (at) соответственно;\n");
    wprintf(L"4. Удаление всех предложений, заканчивающихся на слово с тремя согласными подряд;\n");
    wprintf(L"5. Вывод информации о функциях.\n");
}

void output_text (struct Text *text) {
    for (int i = 0; i < text->amount_of_sentences; i++) {
        wchar_t* str = text->sentences[i]->sentence;
        for (int j = 0; j < wcslen(str); j++)
            fputwc(str[j], stdout);
        fputwc(L'\n', stdout);
    }
    if (text->amount_of_sentences != 0) {
        printf("\n");
    }
}
