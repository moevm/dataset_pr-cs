#include "read_t.h"
#include "struct.h"
#include "del_extra.h"

Sentence *read_s() {
    int N_words = 10;
    int element = 0;
    int length = 0;
    wchar_t symbol;
    wchar_t *string;
    string = (wchar_t*)malloc(N_words * sizeof(wchar_t));
    wmemset(string, 0x00, N_words);
    symbol = getwchar();
    
    if (symbol == L'\n') {
    	symbol = getwchar();
    	if (symbol == L'\n') return NULL;
    }
    	while (symbol != '.') {
    		string[length] = symbol;
    		length++;
    		if (length >= N_words-1) {
	    		string = (wchar_t*)realloc(string, (N_words + STEP)*sizeof(wchar_t));
	    		wmemset(string + N_words, 0x00, STEP);
	    		N_words += STEP;
    		}
    		symbol = getwchar();
    	}
    string[length] = symbol;
    Sentence *sentence = (Sentence *)malloc(sizeof(Sentence));
    sentence->string = string;
    sentence->length = length;
    return sentence;  
}

Text read_t() {
    int N_sent = 10;
    int length = 0;
    int flag = 0;
    Sentence **text = (Sentence **)malloc(N_sent * sizeof(Sentence *));
    Sentence *sentence;
    while (1){
    	sentence = read_s();
    	if (sentence == NULL) break;
    	if (length == N_sent-1) {
    		N_sent += STEP;
    		text = (Sentence **)realloc(text, N_sent*sizeof(Sentence *));
    	}
    	del_extra(sentence);
    	text[length] = sentence;
    	length++;
    }
    Text txt;
    txt.text = text;
    txt.length = length;
    return txt;
}
