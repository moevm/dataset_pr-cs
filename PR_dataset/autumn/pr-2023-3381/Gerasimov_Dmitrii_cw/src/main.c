#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "dyn_array.h"
#include "sentence_processing.h"
#include "textio.h"

#define INFO L"Course work for option 5.11, created by Dmitrii Gerasimov.\n"
#define ERR_TEXT L"Error: Wrong option.\n"

int main(){
    setlocale(LC_CTYPE, "");
    void (*options_arr[])(vector*) = {option0,option1,option2,option3,option4};
    wprintf(INFO);
    int n;
    wscanf(L"%d",&n);
    getwchar();
    if(!(0<=n && n<=5 || n==9)){
        wprintf(ERR_TEXT);
        return 0;
    }
    if(n==5)
        option5();
    if(n==9){
        size_t len = 0;
        while(getwchar()!='\n'){
            len++;
        }
        //wprintf(L"   %d\n",len);
        vector* text = read_text();
        option9(text,len);
        print_text(text);
        free_text(text);
        exit(0);
    }
    vector* text = read_text();
    options_arr[n](text);
    print_text(text);
    free_text(text);
    return 0;
}
