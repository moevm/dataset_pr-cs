#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "structures.h"
#include "double_en.h"
#include "cmp_sents.h"

struct Sentence* read_sentence(){
    int size = 0;
    wchar_t *buf = calloc(1, sizeof(wchar_t));
    wchar_t symbol = L' ';
    wchar_t prev_symbol = L'0';
    int checkbox = 0;
    while(iswspace(symbol)){
		symbol = getwchar();
        if((symbol == L'\n')&&(prev_symbol == L'\n')){
            checkbox = 1;
            break;
        }
        prev_symbol = symbol;
	}
    if(checkbox == 1){
        buf = realloc(buf, 3*sizeof(wchar_t));
        buf[0] = L'\n';
        buf[1] = L'\n';
        buf[2] = L'\0';
        struct Sentence *sentence = calloc(1, sizeof(struct Sentence));
        sentence->str = buf;
        sentence->size = -1;
        return sentence;
    } 
    else{
        if(symbol == L'.') {
            buf = realloc(buf, 2*sizeof(wchar_t));
            buf[0] = L'/';
            buf[1] = L'\0';
            struct Sentence *sentence = calloc(1, sizeof(struct Sentence));
            sentence->str = buf;
            sentence->size = -2;
        } else {
            while((symbol != L'.')) {
                if(size == 0) {
			        symbol = symbol;
		        }
                else{
                    symbol = getwchar();
		        }
		        buf[size] = symbol;
		        size++;
		        buf = realloc(buf, (size + 1)*sizeof(wchar_t));
                if((symbol == L'\n')&&(prev_symbol == L'\n')) {
                    break;
                }
		        prev_symbol = symbol;
            }
            buf[size]= L'\0';
            struct Sentence *sentence = calloc(1, sizeof(struct Sentence));
            sentence->str = buf;
            sentence->size = size;
            return sentence;
            }
        }
}

struct Text read_text(){
    int size = 0;
    struct Sentence** text= calloc(1, sizeof(struct Sentence*));
    int n=0;
    struct Sentence* sentence;
    int checkbox = 0;
    int flag;
    int dublicate;
    while(checkbox != 1){
        flag = 0;
        sentence = read_sentence();
        if(double_en(sentence->str)){
            if(n == 0) wprintf(L"The text is entered incorrectly.\n");
            checkbox = 1;
        }
        else{
                for(int i = 0; i < n; i++){
                    dublicate = cmp_sents(sentence->str, text[i]->str);
                    if(dublicate == 1) {
                        dublicate = 0;
                        flag = 1;
                        break;
                    }
                }
                if(flag != 1){
                    text = (struct Sentence**) realloc(text, (n + 1)*sizeof(struct Sentence*));
                    size += sentence->size;
                    text[n] = sentence;
                    n++;
                }
        }
    }
    struct Text txt;
    txt.size = size;
    txt.sents = text;
    txt.n = n;
    return txt;
}