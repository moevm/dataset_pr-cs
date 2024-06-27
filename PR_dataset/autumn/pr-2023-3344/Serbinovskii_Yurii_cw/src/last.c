#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


wchar_t* big_word(int first_len, wchar_t* sent) {
    wchar_t big_str[16] = L"(большое слово)"; 
    wchar_t* sent_cp = malloc((wcslen(sent)+1)*sizeof(wchar_t));
    wcscpy(sent_cp, sent);
    wchar_t* buffer;
    wchar_t* word = wcstok(sent_cp, L" ,.\n\t", &buffer);
    wchar_t* new_sent = malloc(sizeof(wchar_t));
    int new_index = 0;
    int sent_index = 0;

    while (word != NULL) {
        while (iswspace(sent[sent_index]) || sent[sent_index] == L',') {
            new_sent = realloc(new_sent, (new_index+1)*sizeof(wchar_t));
            new_sent[new_index++] = sent[sent_index++];
        }
        if (wcslen(word) <= first_len) {
            for (int i = 0; i < wcslen(word); i++) {
                new_sent = realloc(new_sent, (new_index+1)*sizeof(wchar_t));
                new_sent[new_index++] = word[i];
                sent_index++;
            }
        }
        else {
            for (int i = 0; i < 15; i++) {
                new_sent = realloc(new_sent, (new_index+1)*sizeof(wchar_t));
                new_sent[new_index++] = big_str[i];
            }
            sent_index += wcslen(word);
        }
        word = wcstok(NULL, L" ,.\n\t", &buffer);
    }
    new_sent = realloc(new_sent, (new_index+1)*sizeof(wchar_t));
    new_sent[new_index++] = L'.';
    new_sent = realloc(new_sent, (new_index+1)*sizeof(wchar_t));
    new_sent[new_index++] = L'\n';
    new_sent = realloc(new_sent, (new_index+1)*sizeof(wchar_t));
    new_sent[new_index++] = L'\0';
    return new_sent;
}