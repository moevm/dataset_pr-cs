#include "input_text.h"

int chek_end_of_text(wchar_t *buf, int* number_stop, int* sentence_length)
{
    if(buf[0] == '\n' && *number_stop)
        return 1;
    else if(buf[0] == '\n') *number_stop = 1;
    else *number_stop = 0;
    (*sentence_length)--;
    return 0;
}

void resize_sentence(wchar_t *buf, int* size)
{
    (*size)+=MEM_STEP;
    wchar_t *new_buf = (wchar_t *)realloc(buf, (*size)*sizeof(wchar_t));
    if(!new_buf)
        wprintf(L"Error: не удалось выделить дополнительную память для предложения.\n");
    buf = new_buf;
}

struct Sentence* read_sentence()
{
    int size = MEM_STEP;
    wchar_t *buf = (wchar_t *)malloc(size*sizeof(wchar_t));
    if(!buf)
    {
        wprintf(L"Error: не удалось выделить память для предложения.\n");
        return NULL;
    }
    int sentence_length = -1, number_stop = 0;
    wchar_t current_wchar;
    do
    {
        sentence_length++;
        if (sentence_length > 0 && iswspace(buf[0]) && chek_end_of_text(buf, &number_stop, &sentence_length)) break;
        if(sentence_length == size-1) resize_sentence(buf, &size);
        current_wchar = getwchar();
        buf[sentence_length] = current_wchar;
    }while(current_wchar != '.');
    buf[sentence_length + 1] = END_STRING;
    struct Sentence* sentence = (struct Sentence*)malloc(sizeof(struct Sentence));
    if(!sentence)
    {
        wprintf(L"Error: не удалось выделить память для структуры предложения.\n");
        return NULL;
    }
    sentence->str = buf;
    sentence->size = size;
    return sentence;
}

struct Text read_text()
{
    int size = MEM_STEP;
    struct Sentence** sents = (struct Sentence**)malloc(size*sizeof(struct Sentence*));
    if(!sents)
        wprintf(L"Error: не удалось выделить память для предложений.\n");
    int number_sentences = 0;
    struct Sentence* temp_sentence = read_sentence();
    while(temp_sentence->str[0] != '\n' && sents)
    {
        if(number_sentences == size)
        {
            size+=MEM_STEP;
            struct Sentence** new_sents = (struct Sentence**)realloc(sents, size*sizeof(struct Sentence*));
            if(!new_sents)
            {
                wprintf(L"Error: не удалось выделить дополнительную память для предложений.\n");
                break;
            }
            sents = new_sents;
        }
        if(!temp_sentence)
        {
            for(int i = 0; i < number_sentences; i++)
                free(sents[i]);
            sents = NULL;
            break;
        }
        sents[number_sentences] = temp_sentence;
        number_sentences++;
        temp_sentence = read_sentence();
    }
    free(temp_sentence);
    struct Text text;
    text.sents = sents;
    text.number_sentences = number_sentences;
    return text;
}
