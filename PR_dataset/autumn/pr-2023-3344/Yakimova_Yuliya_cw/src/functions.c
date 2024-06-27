#include "functions.h" 

void find_palindroms(struct Text *text) {
    for (int i = 0; i < text->sent_counter; i++) {
        int pal_counter = 0;
        
        for (int j = 0; j < text->sentences_arr[i]->word_counter; j++) {
            wchar_t *word = text->sentences_arr[i]->words_arr[j];
            size_t word_len = wcslen(word);
            int pal_flag = 1;
            
            for (int k = 0; k < word_len / 2; k++) {
                if (towlower(word[k]) != towlower(word[word_len - k - 1])) {
                    pal_flag = 0;
                }
            }
            if (pal_flag) pal_counter++;
        }
        
        print_sent(text, i);
        
        if (pal_counter == 0) {
            wprintf(L"Кто-то потерял все палиндромы.\n");
        }
        else if (pal_counter == text->sentences_arr[i]->word_counter) {
            wprintf(L"Палиндромы на месте!\n");
        }
        else {
            wprintf(L"Чего-то не хватает.\n");
        }
    }
}

void replace_spec_symbols(struct Text *text) {
    wchar_t *spec_syms = L".,;!@#$^&*()";
    wchar_t *add_str = L">special symbol<";
    wchar_t *new_sentence;
    
    for (int i = 0; i < text->sent_counter; i++) {
        new_sentence = malloc(sizeof(wchar_t) * (text->sentences_arr[i]->sent_len + 10));
        new_sentence[0] = L'\0';
        
        for (int j = 0; j < text->sentences_arr[i]->sent_len; j++) {
            if (wcschr(spec_syms, text->sentences_arr[i]->sentence[j])) {
                new_sentence = realloc(new_sentence, sizeof(wchar_t) * (wcslen(new_sentence) + wcslen(add_str) + 10));
                wcscat(new_sentence, add_str);
            } else {
                int len = wcslen(new_sentence);
                new_sentence = realloc(new_sentence, sizeof(wchar_t) * (len + 2));
                new_sentence[len] = text->sentences_arr[i]->sentence[j];
                new_sentence[len + 1] = L'\0';
            }
        }
        free(text->sentences_arr[i]->sentence); 
        text->sentences_arr[i]->sentence = new_sentence;
        wprintf(L"%ls%ls\n", text->sentences_arr[i]->sentence, L".");
    }
}

void sort_sents(struct Text *text) {
    int count_latin_letters(wchar_t *sentence) {
        int count = 0;
    
        for (int i = 0; i < wcslen(sentence); i++) {
            if (isalpha((char)sentence[i])) {
                count++;
            }
        }
        return count;
    }
    
    int compare_sents(const void* sentenceA, const void* sentenceB) {

        const struct Sentence* sentence_one = *(const struct Sentence**)sentenceA;
        const struct Sentence* sentence_two = *(const struct Sentence**)sentenceB;
    
        return -(count_latin_letters(sentence_one->sentence) - count_latin_letters(sentence_two->sentence));
    }
    
    qsort(text->sentences_arr, text->sent_counter, sizeof(struct Sentence*), compare_sents);
    
    for(int i = 0; i < text->sent_counter; i++) {
        wprintf(L"%ls\n", text->sentences_arr[i]->sentence);
    }
}

void delete_sents(struct Text *text) {
    for (int i = 0; i < text->sent_counter; i++) {
        int flag = 0;
        
        for (int j = 0; j < text->sentences_arr[i]->word_counter; j++) {
            int latin = 0;
            int cyr = 0;
            
            for (int k = 0; k < wcslen(text->sentences_arr[i]->words_arr[j]); k++) {
                wchar_t sym = text->sentences_arr[i]->words_arr[j][k];
                if (iswalpha(sym)) {
                    if (sym >= L'a' && sym <= L'z' || sym >= L'A' && sym <= L'Z') {
                        latin = 1;
                    } else if (sym >= L'а' && sym <= L'я' || sym >= L'А' && sym <= L'Я') {
                        cyr = 1;
                    }
                }
            }
            
            if (latin && cyr) {
                flag = 1;
                break;
            }
        }
        
        if (flag == 1) {
            free(text->sentences_arr[i]);
            
            for (int x = i; x < text->sent_counter - 1; x++) {
                text->sentences_arr[x] = text->sentences_arr[x+1];
            }
            text->sent_counter--;
        }
    }
}

void print_words(struct Text *text, wchar_t *str) {
    wchar_t new_s[25];
    
    for (int i = 0; i < text->sent_counter; i++) {
        for (int j = 0; j < text->sentences_arr[i]->word_counter; j++) {
            wcscpy(new_s, str);
            int flag = 0;
            
            for (int x = 0; x < wcslen(text->sentences_arr[i]->words_arr[j]); x++) {
                
                if (wcschr(new_s, towlower(text->sentences_arr[i]->words_arr[j][x])) == NULL) {
                    flag++;
                    break;
                }

            } 

            if (!flag) {
                wprintf(L"%ls\n", text->sentences_arr[i]->words_arr[j]);
            }
        }
    }
}