#include "TextRead.h"

struct Text TextRead(){
    setlocale(LC_ALL, "");
    int nflag = 0;
    struct Text T;
    T.txt = (struct Sentence**)malloc(sizeof(struct Sentence*));
    int flag_tchk = 1;
    wchar_t *str = malloc(sizeof(wchar_t));
    int kol_pred = 0;
    wchar_t c;


    for (int i = 0; (c = getwchar()); i++)
{
         if(flag_tchk && ((c == '\t') || (c == ' ')))
        {i --; continue;}
        else if (c == L'\n' && !nflag)
        {
            nflag = 1;
        if(!flag_tchk)
            {
             str[i] = c;
             str = realloc(str, sizeof(wchar_t) * (i + 3));
             i ++;
            }
        i--;
             continue;
        }

        else if (c == L'\n' && nflag)
        {
        
        if (!flag_tchk)
        {   
            i --;
            str[i] = L'.';
            str[i + 1] = L'\0';
            T.txt = (struct Sentence**)realloc(T.txt, (kol_pred+1)*sizeof(struct Sentence*));
            T.txt[kol_pred] = malloc(sizeof(struct Sentence));
            T.txt[kol_pred]->str = str;
            T.txt[kol_pred]->l = i+1;
                kol_pred++;
            str = malloc(sizeof(wchar_t));
        }
        if (kol_pred == 0)
            wprintf(L"Error: Текст не был введён\n");
        break;
        }


        flag_tchk = 0;
        nflag = 0;
        str[i] = c;
        str = realloc(str, sizeof(wchar_t) * (i + 3));
        if (c == L'.')
        {
            flag_tchk = 1;
            str[i + 1] = L'\0';
            T.txt = (struct Sentence**)realloc(T.txt, (kol_pred+1)*sizeof(struct Sentence*));
            T.txt[kol_pred] = malloc(sizeof(struct Sentence));
            T.txt[kol_pred]->str = str;
            T.txt[kol_pred]->l = i+1;
                kol_pred++;
            str = malloc(sizeof(wchar_t));
            i = -1;
        }
        
        
    }
    free(str);
    T.l = kol_pred;
    return T;
}
