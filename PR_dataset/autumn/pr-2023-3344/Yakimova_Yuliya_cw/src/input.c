#include "input.h"

void print_sent(struct Text *text, int i) {
    if (!wcscmp(text->sentences_arr[i]->words_arr[0], L"") && text->sentences_arr[i]->word_counter == 1) return;
    for (int j = 0; j < text->sentences_arr[i]->word_counter-1; j++)
    {
        wprintf(L"%ls", text->sentences_arr[i]->words_arr[j]);
        if (text->sentences_arr[i]->seps_arr[j] == L'!')
        {
            wprintf(L", ");
        }
        else
        {
            wprintf(L"%lc", text->sentences_arr[i]->seps_arr[j]);
        }
    }
    wprintf(L"%ls.\n", text->sentences_arr[i]->words_arr[text->sentences_arr[i]->word_counter-1]);
}

void print_text(struct Text *text)
{
    for (int i = 0; i < text->sent_counter; i++)
    {
        print_sent(text, i);
    }
}

int compare_sents(wchar_t *sent1, wchar_t *sent2)
{
    for (;; sent1++, sent2++)
    {
        int result = towlower(*sent1) - towlower(*sent2);
        if (result != 0 || !*sent1)
            return result;
    }
    return 0;
}

int sent_in_sentences(wchar_t** sentences, wchar_t* sent, int sent_counter) {
    if (sent_counter == 0) return 0;

    for (int i = 0; i < sent_counter; i++)
    {
        if (wcslen(sentences[i]) != wcslen(sent)) continue;
        if (compare_sents(sentences[i], sent) == 0) return 1;
    }
    return 0;
}

void search_seps(wchar_t *sentence, struct Text *text)
{
    text->sentences_arr[text->sent_counter]->seps_arr = malloc(sizeof(wchar_t));

    unsigned sep_counter = 0;
    for (int i = 0; i < wcslen(sentence); i++)
    {
        if (sentence[i] == L',' && sentence[i + 1] == L' ')
        {
            text->sentences_arr[text->sent_counter]->seps_arr[sep_counter++] = L'!';
            i += 1;
        }
        else if (sentence[i] == L',' || sentence[i] == L' ')
        {
            text->sentences_arr[text->sent_counter]->seps_arr[sep_counter++] = sentence[i];
        }
        text->sentences_arr[text->sent_counter]->seps_arr = realloc(text->sentences_arr[text->sent_counter]->seps_arr, sizeof(wchar_t) * (sep_counter + 1));
    }
    text->sentences_arr[text->sent_counter]->sep_counter = sep_counter;
}

void read_text(struct Text *text) {
    //Выделение памяти для поля структурной переменной text - массива предложений sentences_arr
    text->sentences_arr = malloc(sizeof(struct Sentence *));
    //Создание указателя на массив предложений
    wchar_t **sentences = malloc(sizeof(wchar_t *));
    //Создание переменных prev_ch(предыдущий символ) и end_of_text_flag
    wchar_t prev_ch;
    unsigned end_of_text_flag = 0;
    
    while (1) {
        wchar_t *sent = malloc(sizeof(wchar_t));
        unsigned ch_counter = 0;
        wchar_t ch = L'\0';
        
        while (ch != L'.' && end_of_text_flag != 2) {
            prev_ch = ch;
            ch = getwchar();

            if (ch == L'.') continue;

            if ((ch == L' ' || ch == L'\t') && ch_counter == 0) continue;
            if (prev_ch == L' ' && ch == L' ') continue;

            if (prev_ch != L'\n' && ch == L'\n') continue;
            if (prev_ch == L'\n' && ch == L'\n')
            {
                end_of_text_flag += 2;
                continue;
            }
            
            sent[ch_counter++] = ch;
            sent = realloc(sent, (ch_counter + 1) * sizeof(wchar_t));
        }
        sent[ch_counter] = '\0';
        
        if (end_of_text_flag == 2 && ch_counter == 0) {
            free(sent);
            break;
        }
        
        if (!(sent_in_sentences(sentences, sent, text->sent_counter))) {
            text->sentences_arr[text->sent_counter] = malloc(sizeof(struct Sentence));
            search_seps(sent, text);
            text->sentences_arr[text->sent_counter]->sent_len = ch_counter;
            sentences[text->sent_counter++] = sent;
            sentences = realloc(sentences, sizeof(wchar_t*) * (text->sent_counter + 1));
            text->sentences_arr = realloc(text->sentences_arr, (text->sent_counter + 1) * sizeof(struct Sentence*));
        } else {
            free(sent);
        }
    }
    //выделение памяти для поля sentence структурной переменной sentences_arr
    for (int j = 0; j < text->sent_counter; j++) {
        text->sentences_arr[j]->sentence = malloc(sizeof(wchar_t) * (text->sentences_arr[j]->sent_len + 1));
        wcscpy(text->sentences_arr[j]->sentence, sentences[j]);
    }
    for (int i = 0; i < text->sent_counter; i++)
    {
        unsigned word_counter = 0;
        text->sentences_arr[i]->words_arr = malloc(sizeof(wchar_t*));

        wchar_t *pt;
        wchar_t *pch = wcstok(sentences[i], L" ,", &pt);
        while (pch != NULL)
        {
            text->sentences_arr[i]->words_arr[word_counter] = pch;
            word_counter++;
            pch = wcstok(NULL, L" ,", &pt);
            text->sentences_arr[i]->words_arr = realloc(text->sentences_arr[i]->words_arr, sizeof(wchar_t*) * (word_counter + 1));
        }
        text->sentences_arr[i]->word_counter = word_counter;
        free(pt);
        free(pch);
    }

    free(sentences);
}