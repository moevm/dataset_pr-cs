#include "func.h"
#include "getprint.h"
#include <math.h>

wchar_t * sample(struct Text * text) { 
	for (int i = 0; i < text->num_sent; i++){
		int min = 10000;
		wchar_t ** set = get_words(text->sent[i]);
		for (int j = 0; j<text->sent[i]->num_words; j++) {
			if (wcslen(set[j]) < min) min = wcslen(set[j]);
		}
		wchar_t * sample_word = (wchar_t *) malloc((min + 2) * sizeof(wchar_t));
		int n[min];
		for (int l = 0; l<min; l++) {
			n[l] = 1;
		}
		for (int k = 0; k < min; k++){
			for (int j = 1; j < text->sent[i]->num_words; j++){
				if (set[0][k] == set[j][k]) {
					n[k] += 1;
				} 
			}
		}
		for (int p = 0; p < min; p++){
			if (n[p] == text->sent[i]->num_words) sample_word[p] = set[0][p];
			else sample_word[p] = L'?';
		}
		sample_word[min]=L'*';
		sample_word[min+1]=L'\0';
		wprintf(L"%ls\n", sample_word);
		free(sample_word);
		free(set);
	}
}

wchar_t * first_upper(struct Text * text) { 
	for (int i = 0; i<text->num_sent; i++){
		int k = 0;
		wchar_t ** set = get_words(text->sent[i]);
		for (int j = 0; j<text->sent[i]->num_words; j++){
			if (iswupper(set[j][0])) k = 1;
		}
		if (k == 0){
			for (int f = i; f < text->num_sent-1; f++) {
		    	text->sent[f] = text->sent[f+1];
        	}
		(text->num_sent)--;
        i--;
        }
        free(set);
	}
	return 0;
}


wchar_t * vowel_sort(struct Text * text) {
	for (int i = 0; i<text->num_sent; i++){
		wchar_t ** set = get_words(text->sent[i]);
		int size[text->sent[i]->num_words+1];
		int n[text->sent[i]->num_words+1];
		for (int l = 0; l<text->sent[i]->num_words; l++) {
			n[l] = 0;
		}
		for (int k = 0; k < text->sent[i]->num_words; k++){
			size[k] = wcslen(set[k]);
			for (int j = 0; j < size[k]; j++){
				if (isvowel(set[k][j])) {
					n[k] ++;
				} 
			}
		}
		wchar_t * change;
		int chge;
		for (int x = 0; x < text->sent[i]->num_words; x++){
			for (int y = x+1; y < text->sent[i]->num_words; y++){
				if (n[x] > n[y]) {	
					chge = n[x];
					n[x] = n[y];
					n[y] = chge;
									
					change = set[x];
					set[x] = set[y];
					set[y] = change;
				}
			}
		}
		for (int k = 0; k < text->sent[i]->num_words-1; k++) wprintf(L"%ls ", set[k]);
		wprintf(L"%ls.\n", set[text->sent[i]->num_words-1]);
		wprintf(L"\0");
		free(set);
	}
}

void func8(struct Text * text){
	for (int i = 0; i < text->num_sent; i++){
		int sum = 0;
		for (int j = 0; j < text->sent[i]->num_sym-1; j++){
			if (iswdigit(text->sent[i]->symbols[j]) && !iswdigit(text->sent[i]->symbols[j+1])) {
			char ch;
			wcstombs(&ch,&text->sent[i]->symbols[j],sizeof(ch));
			sum += ch - '0';
			}
			else if (iswdigit(text->sent[i]->symbols[j]) && iswdigit(text->sent[i]->symbols[j+1])){
				int n[text->sent[i]->num_sym - j];
				char ch2;
				wcstombs(&ch2,&text->sent[i]->symbols[j],sizeof(ch2));
				n[0] = ch2 - '0';
				char ch3;
				wcstombs(&ch3,&text->sent[i]->symbols[j+1],sizeof(ch3));
				n[1] = ch3 - '0';
				int count = 1;
				for (int k = j+2; k < text->sent[i]->num_sym; k++){
					if (iswdigit(text->sent[i]->symbols[k])){
						count++;
						char ch4;
						wcstombs(&ch4,&text->sent[i]->symbols[k],sizeof(ch4));
						n[count] = ch4 - '0';
						//wprintf(L"n ---- %d\n", n[count]);
					}
					else {
					j+=count;
					break;
					}
				}
				
				int a[count];
				for (int t = 0; t<count+1; t++) a[t] = 1;
				for (int r = 0; r<count+1; r++){
					for (int s = count;s>r;s--){
						a[r] *=10;
					}
					sum += n[r]*a[r];
					//wprintf(L"a[r] = %d,r = %d, sum = %d, n[r] = %d\n", a[r], r, sum, n[r]);
				}
			}
		} 
		
		wprintf(L"%d\n", sum);
	}
}


wchar_t * num_repeat(struct Text * text){
	for (int i = 0; i < text->num_sent; i++){
		wchar_t ** set = get_words(text->sent[i]);
		int numWords = 0;
		int count[text->sent[i]->num_words];
		for (int j = 0; j < text->sent[i]->num_words; j++){
			count[j] = 0;
       		int duplicateIndex = -1;
        	for (int g = 0; g < numWords; g++) {
            	if (wcscasecmp(set[j], set[g]) == 0) {
                	duplicateIndex = g;
                	break;
            	}
        	}
        	if (duplicateIndex != -1) {
        	count[duplicateIndex]++;
        	}
        	else {
            	wcscpy(set[numWords], set[j]);
            	count[numWords] += 1;
            	numWords++;
        	}
    	}
    	int sum = 0;
    	for (int d = 0; d < numWords; d++) {
        	if (count[d] > 1) {
          		sum += count[d];
       		}
    	}
		wprintf(L"Количество одинаковых слов: %d\n", sum);
		free(set);
	}
    return 0;
}

int isvowel(wchar_t letter){
	wchar_t low = towlower(letter);
	if (iswalpha(low) && (low == L'а'||low == L'ё'||low == L'у'||low == L'е'||low == L'ы'||low == L'о'||low == L'э'||low == L'я'||low == L'и'||low == L'ю'||low == L'a'||low == L'e'||low == L'u'||low == L'i'||low == L'o')) return 1;
	else return 0;
}

void del_repeat (struct Text * txt){
	for (int i = 0; i < txt->num_sent; i++) {
		for (int j = 0; j < txt->num_sent;j++) {
		    if (i != j && wcscasecmp(txt->sent[i]->symbols,txt->sent[j]->symbols) == 0) {
		        for (int f = j; f < txt->num_sent-1; f++) {
		            txt->sent[f] = txt->sent[f+1];
                }
                (txt->num_sent)--; 
                j--;
		    }
		}
	} 
}

void free_text(struct Text * text) {
	for (int i = 0; i < text->num_sent; i++) {
		free(text->sent[i]->symbols);
		free(text->sent[i]);
	} 
	free(text->sent);
    free(text); 
}



