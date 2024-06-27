#include "my_lib.h"

void replace_0_9(struct Text *text){
    //setlocale(LC_ALL,"");
    ch digit[][20]={L"ноль",L"один",L"два",L"три",L"четыре",L"пять",L"шесть",L"семь",L"восемь",L"девять"};
    for(int j=0;j<text->cnt_sen;++j){
            ch* tmp=wcsdup(text->txt[j].snt);
            if(tmp == NULL)error(2);
            for(int i=0;i<wcslen(tmp);++i){
                if(iswdigit(tmp[i])){
                    if(tmp[i+1] == '.'||tmp[i+1] == ','||tmp[i+1] == ' '|| tmp[i+1]=='\0'){
                        tmp = realloc(tmp,sizeof(ch)*(wcslen(tmp)+1+wcslen(digit[tmp[i]-L'0'])));
                        if(tmp == NULL)error(2);
                        int size_cpy = wcslen(&tmp[i]);
                        wmemmove(&tmp[i+wcslen(digit[tmp[i]-L'0'])],&tmp[i+1],size_cpy);
                        wmemmove(&tmp[i],digit[tmp[i]-L'0'],wcslen(digit[tmp[i]-L'0']));
                    }
                }
            }
            wprintf(L"%S\n",tmp);
            free(tmp);
    }
}
