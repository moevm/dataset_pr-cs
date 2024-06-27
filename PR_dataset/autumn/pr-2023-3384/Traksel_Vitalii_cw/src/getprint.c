#include "getprint.h"
#include "func.h"

struct Sentence * get_sentence() {
    int len = 100;
	int count=-1;
	wchar_t* snt = (wchar_t *) malloc(len * sizeof(wchar_t));
	wchar_t sym;
	int end = 0;
	int n_cnt = 0;
	while (end != 1){
    	sym = getwchar();
    	count++;
    	if ((count == 0 || count == 1) && sym == L'\n') n_cnt += 1;
    	if (count == 1 && sym != L'\n' && snt[0] == L'\n') {
    		n_cnt = 0;
    		snt[count-1] = sym;
    		count--;
    		continue;
    	}
    	if (count != 0 && sym == L'\n') sym = L' ';
    	if (n_cnt == 2) {
    		count--;
   		    break;
    	}
    	if (count == 0 && sym == L' ') {
    	    count--;
    	    continue;
    	}
    	if (count == 0 && sym == L'.') {
    	    count--;
    	    continue;
    	}
    	if (count>=len) {
    		len += len;
    		snt = realloc (snt, len * sizeof(wchar_t));
    		if (snt == NULL) {
    			wprintf(L"Error: ошибка выделения памяти");
    			exit(0);
    		}
    	}			
    	if (sym == L'.') end = 1;
        else end = 0;
        snt[count] = sym;
	}
	snt[count+1] = L'\0';
	struct Sentence * sent_return = (struct Sentence *) malloc(sizeof(struct Sentence));
	sent_return->symbols = snt;
	sent_return->num_sym = count+1;
	return sent_return;
}

struct Text * get_text() {
	int len = 100;
	int count = -1;
	struct Sentence ** text = (struct Sentence **) malloc(len*sizeof(struct Sentence *));
	int end = 0;
	struct Sentence * sen;
	while (end != 1){
    	sen = get_sentence();
    	count++;
    	if (count>=len) {
    		len += len;
    		text = realloc(text, len * sizeof(struct Sentence *));
    		if (text == NULL) {
    			wprintf(L"Error: ошибка выделения памяти");
    			exit(0);
    		}
    	}
    	
    	if ((sen->symbols[0] == L'\n') && sen->symbols[1] == L'\0') {
    	    end = 1;
    	    free(sen->symbols);
		    free(sen);
    	}
    	else{
		    end = 0;
		    text[count] = sen;
	    }
	}
	if (count == 0) wprintf(L"Error: текст не введён\n");
	
    struct Text * txt = malloc(sizeof(struct Text));
	txt->sent = text;
	txt->num_sent = count;
	
	del_repeat(txt);
    return txt;
}


wchar_t ** get_words(struct Sentence * sentence) {
	int len = 20;
	int count=-1;
	wchar_t** wrd =(wchar_t **) malloc(len*sizeof(wchar_t *));
	wchar_t * copy_sentence = (wchar_t *) malloc((wcslen(sentence->symbols) + 1) * sizeof(wchar_t));
	wcscpy(copy_sentence, sentence->symbols);
	if (copy_sentence == NULL){
		wprintf(L"Error: ошибка копирования");
    	exit(0);
	}
	wchar_t * ptr;
    wchar_t * separate_word = wcstok(copy_sentence, L". ,\n", &ptr);
	while (separate_word != NULL) {
    	count++;
    	if (count>=len) {
    		len += len;
    		wrd = realloc(wrd, len * sizeof(wchar_t *));
    		if (wrd == NULL) {
    			wprintf(L"Error: ошибка выделения памяти");
    			exit(0);
    		}
    	}
    	wrd[count] = (wchar_t *) malloc((wcslen(separate_word) + 1) * sizeof(wchar_t));
    	wcscpy(wrd[count], separate_word);
    	separate_word = wcstok(NULL, L". ,\n", &ptr);
	}
    sentence->num_words = count + 1;
    sentence->words = wrd;
    return (sentence->words);
}

void print_text(struct Text * text) { 
	for (int i = 0; i < text->num_sent; i++) {
		wprintf(L"%ls\n", text->sent[i]->symbols);
	} 
}
