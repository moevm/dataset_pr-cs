#include "output.h"
void output(struct Text *text){
    if(text->num_of_sent==0){
        wprintf(L"Error: пустой текст\n");
    }
    for(int i=0; i<text->num_of_sent; ++i){
        if(text->sentences[i]->str!=NULL)
        wprintf(L"%S", text->sentences[i]->str);
    }
}
