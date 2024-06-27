#include "first_func.h"
#include "struct.h"

void first_func(Text txt) {
	int N_words = 10;
	wchar_t **all_words = (wchar_t **)malloc(N_words * sizeof(wchar_t *));
	wchar_t **uniq_words = (wchar_t **)malloc(N_words * sizeof(wchar_t *));
	wchar_t *ptr;
	wchar_t *token;
	int flag = 0;
	int count_times = 0;
	int count_words = 0;
	int index = 0;
	for (int i = 0; i < txt.length; i++) {
		token = wcstok(txt.text[i]->string, L" ,.\n", &ptr); 
		while (token != NULL) {
			if (count_words >= N_words) {
				all_words = (wchar_t **)realloc(all_words, (N_words + STEP)*sizeof(wchar_t *));
				N_words += STEP;
			}
			all_words[count_words] = token;
			count_words++;
			token = wcstok(NULL, L" ,.\n", &ptr);
		}
	}
	for (int k = 0; k < (count_words); k++) {
		count_times = 0;
		flag = 0;
		for (int i = 0; i < (count_words); i++) {
			if ((wcscmp(all_words[i], all_words[k])) == 0) {
				count_times++;
				if (count_times > 1) {
					flag = 1;
					break;
				}	
			}
		}
		if (flag == 0) {
			uniq_words[index] = all_words[k];
			wprintf(L"%ls\n", uniq_words[index]);
			index++;
		}
	}	
}
