#include "read_text.h"

int compare_for_text_sentences(const wchar_t * first_sentence, const wchar_t * second_sentence){
	while(*first_sentence && *second_sentence){
		if(towupper(*first_sentence) != towupper(*second_sentence)){
			return 0;
		}
		first_sentence++;
		second_sentence++;
	}
	return (*first_sentence == SYMBOL_END_STRING && *second_sentence == SYMBOL_END_STRING);
}

int is_dublicate(Text* text, Sentence* string){
	for (size_t i = 0; i < text->length; i++){
		if (compare_for_text_sentences(text->text[i]->sentence,string->sentence)){
			return 1;
		}
	}
	return 0;
}

wchar_t* read(){
    wchar_t input = getwchar();
    wchar_t last_char;
    wchar_t *text = NULL;
    size_t length = 0;
    while (input != L'\n' || last_char != L'\n'){
        if (input == WEOF)
            failure(FAILURE_INPUT);
        text = realloc(text, (length+1) * sizeof(wchar_t));
	    if (text == NULL){ 
	    	failure(FAILURE_MEMORY);
		}
        text[length++] = input;
        last_char = input;
        input = getwchar();
    }
    text = realloc(text, (length+1) * sizeof(wchar_t));
    if(text[length-2] == SYMBOL_POINT)
        text[length-2] = SYMBOL_END_STRING;
    else
        text[length-1] = SYMBOL_END_STRING;
    return text;
    return text;
}


Sentence* text_to_sentence(wchar_t *text, size_t start_index){
    Sentence *sentence = malloc(sizeof(Sentence));
    if (sentence == NULL){ 
    	failure(FAILURE_MEMORY);
	}
    sentence->length = 0;
    sentence->sentence = NULL;
    size_t counter = start_index;
    while (text[counter] != SYMBOL_POINT && text[counter] != SYMBOL_END_STRING){
        if (iswspace(text[counter])){
            counter++;
            continue;
        }else{
	        sentence->sentence = realloc(sentence->sentence, (sentence->length+1) * sizeof(wchar_t));
	        if (sentence->sentence == NULL){
	            failure(FAILURE_MEMORY);
	        }
	        sentence->sentence[sentence->length++] = text[counter];
			if (iswspace(text[counter + 1]) && text[counter + 2] != SYMBOL_POINT){
				sentence->sentence = (wchar_t*)realloc(sentence->sentence, sizeof(wchar_t)*(sentence->length + 1));
				if(sentence->sentence == NULL){
					failure(FAILURE_MEMORY);
				}
				sentence->sentence[sentence->length++] = SYMBOL_SPACE;
			}
	        counter++;
        }
    }   

    if (text[counter] == SYMBOL_END_STRING){
        sentence->last_index = -1;
    }else{
        sentence->last_index = counter+1;
	}
    if (sentence->sentence != NULL){
        sentence->sentence = realloc(sentence->sentence, (sentence->length+2) * sizeof(wchar_t));
    	sentence->sentence[sentence->length++] = SYMBOL_POINT;
    	sentence->sentence[sentence->length++] = SYMBOL_END_STRING;
    }
    return sentence;
}

Text * read_text(){
	Text * finish_text = (Text*)malloc(sizeof(Text));
	if (finish_text == NULL){
		failure(FAILURE_MEMORY);
	}
	wchar_t * text = read();
	if (text == NULL){
		failure(FAILURE_INPUT);
	}
	finish_text->length = 0;
	finish_text->text = NULL;
	int start_index = 0;
	Sentence * sentence = NULL;
	do{
		sentence = text_to_sentence(text,start_index);
		if (sentence->sentence != NULL && !is_dublicate(finish_text, sentence)){
			finish_text->text = (Sentence**)realloc(finish_text->text, sizeof(Sentence*)*(finish_text->length + 1));
			if (finish_text->text == NULL){
				failure(FAILURE_MEMORY);
			}
			finish_text->text[finish_text->length++] = sentence;
		}
		start_index = sentence->last_index;
	}while(sentence->last_index != -1);
	return finish_text;	
}
