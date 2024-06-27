#include "functions_13.h"

void delete_sentence(Text* text, int num_of_sent) {
    int len = text->count_sent;
    free(text->pr_sent[num_of_sent]);
    for(int i = num_of_sent; i<len-1; i++) {
        text->pr_sent[i] = text->pr_sent[i+1];
    }
    text->count_sent--;
    text->pr_sent[len-1] = NULL;
}

void delete_repeat_sentence(Text* text) {
    int len = text->count_sent;
    int i = 0;
    while(i<len) {
        int j = 0;
        while(j<i) {
            if(!wcscasecmp(text->pr_sent[i]->sentence, text->pr_sent[j]->sentence)) {
                delete_sentence(text, i);
                len--;
                i--;
                break;
            }
            j++;
        }
        i++;
    }
}

void replace_highnoon_and_midnight(Text* text) {
    int len = text->count_sent;
    wchar_t* str1 = L"high noon";   //9
    wchar_t* str1_replace = L"полдень";  //7
    wchar_t* str2 = L"полночь";  //7
    wchar_t* str2_replace = L"midnight"; //8
    for(int i = 0; i<len; i++) {
        wchar_t* pr_str1 = wcsstr(text->pr_sent[i]->sentence, str1);
        while(pr_str1 != NULL) {
            int len_sent = text->pr_sent[i]->len_sent;
            wchar_t* buffer = (wchar_t*)calloc(len_sent, sizeof(wchar_t));
            wcsncpy(buffer, text->pr_sent[i]->sentence, len_sent-wcslen(pr_str1));
            wcscat(buffer, str1_replace);
            wcscat(buffer, pr_str1+wcslen(str1));
            wcscpy(text->pr_sent[i]->sentence, buffer);
            free(buffer);
            text->pr_sent[i]->len_sent-=2;
            pr_str1 = wcsstr(text->pr_sent[i]->sentence, str1);
        }
	wchar_t* pr_str2 = wcsstr(text->pr_sent[i]->sentence, str2);
        while(pr_str2 != NULL) {
            int len_sent = text->pr_sent[i]->len_sent;
            wchar_t* buffer = (wchar_t*)calloc(len_sent+2, sizeof(wchar_t));
            wcsncpy(buffer, text->pr_sent[i]->sentence, len_sent-wcslen(pr_str2));
            wcscat(buffer, str2_replace);
            wcscat(buffer, pr_str2+7);  //7-длина str2
            free(text->pr_sent[i]->sentence);
            text->pr_sent[i]->sentence = (wchar_t*)malloc((len_sent+2)*sizeof(wchar_t));
            wcscpy(text->pr_sent[i]->sentence, buffer);
            free(buffer);
            text->pr_sent[i]->len_sent++;
            pr_str2 = wcsstr(text->pr_sent[i]->sentence, str2);
        }
    }
}

wchar_t* find_first_word(Sentence* sentence) {
    int len = sentence->len_sent;
    int len_word = 0;
    for(int i = 0; i<len; i++) {
        if(sentence->sentence[i] != L' ' && sentence->sentence[i] != L',' && sentence->sentence[i] != L'.') {
            len_word++;
        } else {
            break;
        }
    }
    wchar_t* first_word = (wchar_t*)malloc((len_word+1)*sizeof(wchar_t));
    for(int i = 0; i<len_word; i++) {
        first_word[i] = sentence->sentence[i];
    }
    first_word[len_word] = L'\0';
    return first_word;
}


wchar_t* find_last_word(Sentence* sentence) {
    int len = sentence->len_sent;
    int len_word = 0;
    for(int i = len-2; i>=0; i--) {
        if(sentence->sentence[i] == L' ' || sentence->sentence[i] == L',') {
            break;
        }
        len_word++;
        if(len_word == len-1) {
            break;
        }
    }
    wchar_t* last_word = (wchar_t*)malloc((len_word+1)*sizeof(wchar_t));
    wchar_t* buf = sentence->sentence + len - len_word - 1;
    wcsncpy(last_word, buf, len_word);
    last_word[len_word] = L'\0';
    return last_word;
 }

void remove_some_sentences(Text* text) {
    int len = text->count_sent;
    int i = 0;
    while(i<len) {
        wchar_t* first_word = find_first_word(text->pr_sent[i]);
        wchar_t* last_word = find_last_word(text->pr_sent[i]);
        if(!wcscmp(first_word, last_word)) {
            delete_sentence(text, i);
            i--;
            len--;
        }
        i++;
        free(first_word);
        free(last_word);
    }
}

