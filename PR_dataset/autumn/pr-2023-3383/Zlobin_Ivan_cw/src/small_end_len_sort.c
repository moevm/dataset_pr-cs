#include "small_end_len_sort.h"

int compare(const void *a, const void *b){
    return (int)wcslen(*(wchar_t**)b)-(int)wcslen(*(wchar_t**)a);
}

void small_end_sort(struct Text *text){
    len_count(text);
    for(int i=0;i<text->num_of_sent;++i){
        wchar_t **words=malloc(sizeof(wchar_t *)*text->sentences[i]->cnt);
        wchar_t *buff=wcsdup(text->sentences[i]->str);
        wchar_t *pt;
        wchar_t *token=wcstok(buff, L" ,.\n", &pt);
        for(int j=0;token!=NULL;++j){
            words[j]=wcsdup(token);
            token=wcstok(NULL, L" ,.\n", &pt);
        }
        qsort(words, text->sentences[i]->cnt, sizeof(wchar_t*), compare);
        wchar_t **tab = (wchar_t**)malloc(sizeof(wchar_t*)*text->sentences[i]->len);
        for(int j=0;j<text->sentences[i]->len;++j){
            tab[j]=(wchar_t*)malloc(sizeof(wchar_t));
        }
        int it=0;
        int it_tab=0;
        for(int j=0;j<text->sentences[i]->len;++j){
            if(text->sentences[i]->str[j]==L' ' || text->sentences[i]->str[j]==L','){
                tab[it_tab]=(wchar_t*)realloc(tab[it_tab], sizeof(wchar_t)*text->sentences[i]->len);
                it=0;
                while(text->sentences[i]->str[j]==L' ' || text->sentences[i]->str[j]==L','){
                    tab[it_tab][it++]=text->sentences[i]->str[j++];
                }
                tab[it_tab][it]='\0';
                it_tab++;
            }
        }
        int tab_size=it_tab;
        wchar_t *str=(wchar_t*)malloc(sizeof(wchar_t)*(text->sentences[i]->len+1));
	    wchar_t str_end[]={L".\n\0"};
        str[0]=L'\0';
        for(int j=0;j<text->sentences[i]->cnt;++j){
            wcscat(str,words[j]);
            if(j!=text->sentences[i]->cnt-1)
                wcscat(str, tab[j]);
            else
                wcscat(str,str_end);
        }
        free(text->sentences[i]->str);
        text->sentences[i]->str=wcsdup(str);
        free(str); free(buff);
        for(int j=0;j<text->sentences[i]->cnt;++j){
            free(words[j]);
        }
        free(words);
        for(int j=0;j<text->sentences[i]->len;++j){
            free(tab[j]);
        }
        free(tab);
    }
}

