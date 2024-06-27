#include "actions.h"
#include "input_output.h"

void removeEmptySentences(Text* text){
    int i = 0;
    for(Sentence* sent = text->sents; sent < text->sents + text->len; sent++, i++) {
        if(!sent->words[0].len){
            removeSentence(i, text);
            i--;
            sent--;
        }
    }
}

void removeCopies(Text* text){
    int c1, c2;
    Word *w1, *w2;

    for(int r = text->len-1; r > 0;r--)
        for(int l = r-1; l >= 0; l--){
            if(text->sents[l].len != text->sents[r].len)
                continue;
            w1 = text->sents[l].words;
            w2 = text->sents[r].words;
            c1 = 0;
            c2 = 0;
            for(int i = 0; i < text->sents[l].len; i++){
                c1 = wcscasecmp(w1[i].chars, w2[i].chars);
                c2 = w1[i].sep != w2[i].sep;
                if(c1 || c2)
                    break;
            }
            if(!c1 && !c2){
                removeSentence(r, text);
                break;
            }
        }
}

void removeSentence(int i, Text* text){
    freeSentence(text->sents[i]);
    memmove(text->sents+i, text->sents+i+1, (text->len-i-1)*sizeof(Sentence));
    text->len--;
}

void freeSentence(Sentence sent){
    for(Word* word = sent.words; word < sent.words + sent.len; word++)
        free(word->chars);

    free(sent.words);
}

void freeText(Text* text){
    for(int i = 0;i < text->len;i++)
        freeSentence(text->sents[i]);
    free(text->sents);
    text->len = 0;
}

void changeOneWord(Word* word, wchar_t* toWord) {
    free(word->chars);
    word->len = wcslen(toWord);
    wchar_t* newChars = malloc((wcslen(toWord) + 1)* sizeof(wchar_t));
    wcscpy(newChars, toWord);
    word->chars = newChars;
}

void changeWords(Text* text, Word replaceFrom, Word replaceTo){
    int size = MEMORY_STEP;
    for(Sentence* sent = text->sents; sent < text->sents + text->len; sent++){
        for(Word* word = sent->words; word < sent->words + sent->len; word++){
            if(!wcscasecmp(word->chars, replaceFrom.chars)){
                changeOneWord(word, replaceTo.chars);
            }
        }
    }
}

int countUpCaseLetters(Sentence* sent){
    int k = 0;
    for(Word* word = sent->words; word < sent->words + sent->len; word++){
        for(wchar_t *c = word->chars; c < word->chars + word->len; c++){
            if(L'A' <= *c && L'Z' >= *c || L'А' <= *c && L'Я' >= *c){
                k++;
            }
        }
    }
    return  k;
}

int cmp(const void *a, const void *b){
    Sentence *s1 = (Sentence*)a;
    Sentence *s2 = (Sentence*)b;
    return countUpCaseLetters(s1) - countUpCaseLetters(s2);
}

void sortSentences(Text* text){
    qsort(text->sents, text->len, sizeof(Sentence), cmp);
}

int isVowel(wchar_t c){
    wchar_t* vowels = L"aAeEiIoOyYаАеЕёЁиИоОуУыЫэЭюЮяЯ";
    for(int i = 0; i < wcslen(vowels); i++){
        if(c == vowels[i])
            return 1;
    }
    return 0;
}


void changeVowels(Text *text){
    wchar_t* replaceAlp = L"abcefgijkopqyzaABCEFGIJKOPQYZAабвеёжзийкопруфхыьэюяабАБВЕЁЖЗИЙКОПРУФХЫЬЭЮЯАБ";
    for(Sentence* sent = text->sents; sent < text->sents + text->len; sent++){
        for(Word* word = sent->words; word< sent->words + sent->len; word++){
            for(int i = 0; i <word->len; i++){
                if(isVowel(word->chars[i])){
                    int k = 0;
                    while(word->chars[i] != replaceAlp[k]){
                        k++;
                    }
                    wchar_t* newWord = malloc((word->len+2)* sizeof(wchar_t));
                    for(int j = 0; j < i; j++){
                        newWord[j] = word->chars[j];
                    }
                    newWord[i] = replaceAlp[k+1];
                    newWord[i+1] = replaceAlp[k+2];
                    for(int j = i + 1; j < word->len; j++){
                        newWord[j+1] = word->chars[j];
                    }
                    newWord[word->len+1] = '\0';
                    changeOneWord(word, newWord);
                    free(newWord);
                }
            }
        }
    }
}

void countSymbols(Text *text){
    for(Sentence* sent = text->sents; sent < text->sents + text->len; sent++){
        for(Word* word = sent->words; word< sent->words + sent->len; word++){
        	int k =1;
        	wchar_t s = word->chars[0];
        	int size = MEMORY_STEP;
        	int len = 0;
        	wchar_t* newWord = malloc(size * sizeof(wchar_t));
        	for (int i = 1; i< word->len; i++){
        		if (towupper(word->chars[i]) != towupper(s)){
        			if (k > 1){
        				 newWord[len++] = towupper(s);
        				 wchar_t* count = malloc(100 * sizeof(wchar_t));
        				 swprintf(count, 100, L"%d",k);
        				 for (int j = 0; count[j]; j++){
        				 	newWord[len++] = count[j];
        				 	if (len + 1 >= size){
        				 		size += MEMORY_STEP;
        				 		newWord = realloc(newWord, size);
        				 	}
        				 }
        				 free(count);
        			}else{
        				newWord[len++] = s;
        			}
        			if (len + 2 >= size){
		    			size+= MEMORY_STEP;
		    			newWord = realloc(newWord, size);
		    			}
		    			s = word->chars[i];
		    			k = 1;
		    		}else{
		    			k++;
		    		}
        		}
        		if (k>1){
        			newWord[len++] = towupper(s);
        			wchar_t* count = malloc(100 * sizeof(wchar_t));
    				swprintf(count, 100, L"%d",k);
    				for (int j = 0; count[j]; j++){
    					newWord[len++] = count[j];
    					if (len + 1 >= size){
        				 		size += MEMORY_STEP;
        				 		newWord = realloc(newWord, size);
        				}
    				}
    				free(count);
    			}else{
    				newWord[len++] = s;
    			}
				newWord[len] = L'\0';
				changeOneWord(word, newWord);
				free(newWord);
        		

    	}
	}
}

