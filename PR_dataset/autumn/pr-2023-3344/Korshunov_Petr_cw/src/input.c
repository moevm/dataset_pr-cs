#include <stdlib.h>
#include <wchar.h>
#include "structs.h"
#include "text_processing.h"
#define MEM_STEP 5

SNT *readSentence()
{
    int size = MEM_STEP;
    wchar_t *buf = (wchar_t *)malloc(size * sizeof(wchar_t));
    int n = 0;
    int nlcount = 0;
    wchar_t temp;
    if (!buf)
    {
        wprintf(L"Error: Failed to allocate memory for the sentence.\n");
        exit(0);
    }
    do
    {
        if (n >= size - 2)
        {
            size += MEM_STEP;
            wchar_t *t = (wchar_t *)realloc(buf, size * sizeof(wchar_t));
            if (!t)
            {
                wprintf(L"Error: Failed to allocate memory for the sentence.\n");
                exit(0);
            }
            buf = t;
        }
        temp = getwchar();
        if (temp == L'\n')
        {
            nlcount++;
        }
        else
        {
            nlcount = 0;
        }
        buf[n] = temp;
        n++;
    } while (temp != L'.' && nlcount < 2);
    buf[n] = L'\0';
    SNT *sentence = (SNT *)malloc(sizeof(SNT));
    if (!sentence)
    {
        wprintf(L"Error: Failed to allocate memory for the sentence struct.\n");
        exit(0);
    }
    sentence->sent = buf;
    sentence->size = size * sizeof(wchar_t);
    return sentence;
}

TEXT readText()
{
    int size = MEM_STEP;
    wchar_t skip = getwchar();
    SNT **text = (SNT **)malloc(size * sizeof(SNT *));
    if (!text)
    {
        wprintf(L"Error: Failed to allocate memory for the text.\n");
        exit(0);
    }
    int n = 0;
    SNT *temp;
    int endpoint = 1;
    do
    {
        if (n >= size - 2)
        {
            size += MEM_STEP;
            SNT **t = (SNT **)realloc(text, size * sizeof(SNT *));
            if (!t)
            {
                wprintf(L"Error: Failed to allocate memory for the text.\n");
                exit(0);
            }
            text = t;
        }
        temp = readSentence();
        if (wcsstr(temp->sent, L"\n\n"))
        {
            endpoint--;
            if (wcslen(temp->sent) == 2)
            {
                free(temp->sent);
                free(temp);
                break;
            }
            else
                temp->sent[wcslen(temp->sent) - 2] = L'\0';
            wprintf(L"Warning: you entered a sentence without a dot at the end.\n");
        }
        delFirstSymbols(temp);
        temp->len = wcslen(temp->sent);
        if (delRepeatingSents(temp, text, n) || n == 0)
        {
            text[n] = temp;
            n++;
        }
        else
        {
            free(temp);
        }
    } while (endpoint);
    TEXT txt;
    txt.size = size * sizeof(SNT *);
    txt.sents = text;
    txt.len = n;
    return txt;
}