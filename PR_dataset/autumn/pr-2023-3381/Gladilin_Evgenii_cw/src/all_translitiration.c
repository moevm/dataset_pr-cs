#include "all_translitiration.h"

struct Sentence *make_trans(struct Sentence *sentence){
	struct Dictionary dict[] = CYRILLIC_DICT;
	struct Sentence *cyrillic_sentence;
        cyrillic_sentence = malloc(sizeof(struct Sentence));
        if(!cyrillic_sentence)
                fail(MEM_ERROR);
	cyrillic_sentence->str = malloc(sizeof(wchar_t));
	if(!cyrillic_sentence->str)
		fail(MEM_ERROR);
        int n = 0;
	wchar_t cyr[2] = {0};
        for(int i = 0; i<sentence->len;i++){
		if(((L'а' <= towlower(sentence->str[i]) && towlower(sentence->str[i]) <= L'я') || towlower(sentence->str[i]) == L'ё')){
                        cyr[0] = sentence->str[i];
			int sym_len = wcslen(get_value(dict, 66, cyr));
                        cyrillic_sentence->str = realloc(cyrillic_sentence->str,(n+sym_len)*sizeof(wchar_t));
                        if(!cyrillic_sentence->str)
                                fail(MEM_ERROR);
                        for(int j = 0; j<sym_len;j++){
                                cyrillic_sentence->str[n++] = get_value(dict,66,cyr)[j];
                        }
                }else{
                        cyrillic_sentence->str = realloc(cyrillic_sentence->str,(n+1)*sizeof(wchar_t));
                        if(!cyrillic_sentence->str)
                                fail(MEM_ERROR);
                        cyrillic_sentence->str[n++] = sentence->str[i];
                }

	}
	cyrillic_sentence->str = realloc(cyrillic_sentence->str,(n+2)*sizeof(wchar_t));
	if(!cyrillic_sentence->str)
		fail(MEM_ERROR);
	cyrillic_sentence->str[n] = '\0';
        cyrillic_sentence->len = n;
	return cyrillic_sentence;
}

struct Text translitiration(struct Text text){
	struct Text new_text;
	new_text.sents = malloc(sizeof(struct Sentence*));
	if(!new_text.sents)
		fail(MEM_ERROR);
	int n = 0;
	for(int i = 0; i < text.n; i++){
		if(make_trans(text.sents[i])){
			new_text.sents = realloc(new_text.sents,(n+1)*sizeof(struct Sentence*));
			new_text.sents[n++] = make_trans(text.sents[i]);
                }
        }
        new_text.n = n;
        return new_text;
}

void all_transliteration(struct Text text){
	text_print(translitiration(text));
	freeText(text);
}
