#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>

#include "struct.h"
#include "print_error.h"
#include "free_all.h"

#define BLOCK_SIZE 20
#define TXT_BLOCK_SIZE 3

struct Text txt;

int sent_equals(struct Sentence* sent) {
	wchar_t dub_sent[sent->len+1];
	wcscpy(dub_sent, sent->ptr);
	for (int x = 0; x < sent->len; x++){
		if (iswupper(sent->ptr[x])) 
			dub_sent[x] = towlower(sent->ptr[x]);
	}
	
    for (int i = 0; i < txt.len; i++){
		wchar_t lower_isent[txt.ptr[i]->len];
		wcscpy(lower_isent, txt.ptr[i]->ptr);
   		for (int x = 0; x < sent->len; x++){
        	if (iswupper(txt.ptr[i]->ptr[x])) 
				lower_isent[x] = towlower(txt.ptr[i]->ptr[x]);
		}

        if (!wcscmp(lower_isent, dub_sent)) return 0;
	}
    return 1;
}

void memory_error(struct Sentence* sent, wchar_t* ptr){
	print_error(L"Не удалось выделить память");
	free(sent);
	free(ptr);
	free_all(txt);
	exit(0);
}

struct Sentence* get_sentence(int* flag){
	struct Sentence* sent = (struct Sentence*)malloc(sizeof(struct Sentence));
	if (!sent) memory_error(sent, NULL);
	sent->ptr = (wchar_t*)malloc(BLOCK_SIZE*sizeof(wchar_t));
	if (!sent->ptr) memory_error(sent, sent->ptr);
	
	sent->len = 0;
	size_t size = BLOCK_SIZE;
	size_t n_count = 0;
	
	while (n_count != 2){
		wchar_t ch = getwchar();
		if (!(sent->len == 0 && iswspace(ch)))
			sent->ptr[sent->len++] = ch;
	
		if (ch == L'.') break;

		if (ch == L'\n') {
			n_count++;
			if (n_count == 2) break;
		} else {
			n_count = 0;
		}
		
		if (sent->len == size-1){
			size += BLOCK_SIZE;
			wchar_t* old_ptr = sent->ptr;
			sent->ptr = (wchar_t*)realloc(sent->ptr, size*sizeof(wchar_t));
			if (!sent->ptr) memory_error(sent, old_ptr);
		}
	}
	sent->ptr[sent->len] = L'\0';
	if (n_count == 2) {
		*flag = 0;
		if (sent->len > 2) {
			sent->ptr[sent->len-2] = L'.';
			sent->ptr[sent->len-1] = L'\0';
		}
	}
	return sent;
}

struct Text get_text(){
	int flag = 1;
	txt.ptr = (struct Sentence**)malloc(TXT_BLOCK_SIZE*sizeof(struct Sentence*));
	if (!txt.ptr) {
		print_error(L"невозможно выделить память");
		free_all(txt);
		exit(0);
	}
	txt.len = 0;
	
	size_t size = TXT_BLOCK_SIZE;

	while(flag){
		struct Sentence* sentence = get_sentence(&flag);
		
		if ((sentence->len>1) && sent_equals(sentence)) {
			txt.ptr[txt.len++] = sentence;
		} else {
			free(sentence->ptr);
			free(sentence);
		}

		if (txt.len == size-1){
            size += BLOCK_SIZE;
            struct Sentence** old_ptr = txt.ptr;
            txt.ptr = (struct Sentence**)realloc(txt.ptr, size*sizeof(struct Sentence*));
            if (!txt.ptr) {
                txt.ptr = old_ptr;
                memory_error(sentence, sentence->ptr);
            }
        }
	}

	return txt;
}
