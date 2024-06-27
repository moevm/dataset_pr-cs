#include "input.h"
struct Sentence null = {NULL,0};
struct Sentence read_sentence(){
    wchar_t* str = (wchar_t*)malloc(sizeof(wchar_t));
    wchar_t c = getwchar();
    while (c==L'\t' || c==L' ' || c == L'\v' || c==L'.'){
        c = getwchar();
    }
    if (c == L'\n'){
        c = getwchar();
        if (c == L'\n'){
            free(str);
            return null;
        }
    }
    if (c ==L'.'){
        c = getwchar();
        if (c == L'\n'){
            c = getwchar();
            if (c == L'\n'){
                free(str);
                return null;
            }
        }
    }
    int mem = 1;
    int len = 0;
    while (c != L'.'){
        if (len +2>= mem){
            mem *= MEM_STEP;
            str = (wchar_t*)realloc(str, mem*sizeof(wchar_t));
        }
        str[len++] = c;
        if (len>= 2 && str[len-2] == L'\n' && str[len-1] == L'\n'){
            break;
        }
        c = getwchar();
    }

    if (len >= 2 && str[len-2] == L'\n' && str[len-1] == L'\n'){
        str[len-2] = L'.';
        str[len-1] = L'\0';
        len = -1;
    }
    else{
        str[len] = L'.';
        str[len+1] = L'\0';
    }
    struct Sentence input_sentence ={str,len};
    return input_sentence;
}
struct Text read_text(){
    wchar_t** our_txt = (wchar_t**)malloc(sizeof(wchar_t*));
    struct Sentence ptr = read_sentence();
    if (ptr.size_sent == 0 && ptr.str == NULL){
        wprintf(L"Error: Пустой текст\n");
        free(ptr.str);
        free(our_txt);
        struct Text zero = {NULL, 0};
        return zero;
    }
    int mem = 1;
    int i = 0;
    while(1){
        if (ptr.size_sent == 0){
            free(ptr.str);
            break;
        }
        if (i +2>= mem){
            mem *= MEM_STEP;
            our_txt = (wchar_t**)realloc(our_txt, mem*sizeof(wchar_t*));
        }
        if (ptr.size_sent == -1){
            our_txt[i++] = wcsdup(ptr.str);
            free(ptr.str);
            break;

        }
        our_txt[i++] = wcsdup(ptr.str);
        free(ptr.str);
        ptr = read_sentence();

    }

    struct Text final_txt;
    final_txt.sentences = our_txt;
    final_txt.size = i;
    return final_txt;
}
