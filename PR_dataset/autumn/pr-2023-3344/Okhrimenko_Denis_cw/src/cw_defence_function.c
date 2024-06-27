#include "base_library.h"

void foo(text_t* text)
{
    for(size_t i = 0; i < text->size; ++i){
        wchar_t* cursent = text->data[i]->data;
        size_t top = text->data[i]->size;
        for(int j = top; j != -1; --j){
            if(cursent[j] == L' ' || j == 0){
                if(j == 0){
                    for(int k = 0; cursent[k] != L'.'; ++k){
                        wprintf(L"%lc", cursent[k]);
                    } wprintf(L".");
                    break;
                }
                if(cursent[j - 1] == L','){
                    for(int k = j + 1; cursent[k] != L'.'; ++k){
                        wprintf(L"%lc", cursent[k]);
                    }
                    wprintf(L", ");
                    j--;
                } else {
                    for(int k = j + 1; cursent[k] != L'.'; ++k){
                        wprintf(L"%lc", cursent[k]);
                    }
                    wprintf(L" ");
                }
                cursent[j] = L'.';
            }
        } wprintf(L"\n");
    }
}