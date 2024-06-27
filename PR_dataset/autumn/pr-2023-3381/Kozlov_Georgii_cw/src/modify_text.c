#include "headers.h"
#include <stdlib.h>
#include <string.h>


void additional_task(struct Text txt, wchar_t* first_word){
	int sum = 0;
	int len_word = 0;
	int size = 100;
	wchar_t letter_b[33][1] = {L'А', L'Б', L'В', L'Г', L'Д', L'Е', L'Ё', L'Ж',
	L'З', L'И', L'Й', L'К', L'Л', L'М', L'Н', L'О',L'П', L'Р', L'С', L'Т', L'У', L'Ф', L'Х', L'Ц',L'Ч', L'Ш', L'Щ', L'Ъ', L'Ы',
	L'Ь', L'Э', L'Ю',  L'Я'};
	wchar_t letter_w[33][1] = {L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж',
	L'з', L'и', L'й', L'к', L'л', L'м', L'н', L'о',L'п', L'р', L'с', L'т', L'у', L'ф',L'х', L'ц',L'ч', L'ш', L'щ', L'ъ', L'ы',
	L'ь', L'э', L'ю',  L'я'};
	wchar_t *word = malloc(size * sizeof(wchar_t));
   for (int i = 0; i < txt.len; i++){
	for (int j = 0; j < txt.text[i]->len; j++){
		if (txt.text[i]->str[j] != ' ' && txt.text[i]->str[j] != ',' && txt.text[i]->str[j] != '.' && txt.text[i]->str[j] != '!' && txt.text[i]->str[j] != '?'){
			for (int k = 0; first_word[k]; k++){
				wchar_t a = tolower(first_word[k]);
				wchar_t b = tolower(txt.text[i]->str[j]);
				for (int r = 0; r < 33; r++){
					if (a == letter_b[0][r]){
						a = letter_w[0][r];
					}
					if (b == letter_b[0][r]){
						b = letter_w[0][r];
					}
				}
				if (len_word == (size - 1)){
					word = realloc(word, (size + 20) * sizeof(wchar_t));
					size += 20;
				}
				if (a == b){
					word[len_word] = txt.text[i]->str[j];
					len_word++;
					break;
				}
			}
			sum++;
		}
		else{
			word[len_word] = '\0';
			if (len_word == sum && len_word != 0 && sum != 0){
				wprintf(L"%ls\n", word);
			}
			len_word = 0;
			sum = 0;
		}
	}
   }
}


struct Sentence *fix_sentence(struct Sentence *sentence) {
    if (sentence->str[0] == L'\t' || sentence->str[0] == L' ' || sentence->str[0] == L'\n' || sentence->str[0] == L'.'){
        for (int i = 0; i <= sentence->len; i++)
            sentence->str[i] = sentence->str[i + 1];
        sentence->len--;
    }
    return sentence;
}

struct Text delete_same_sentance(struct Text text)
{
    int flag = 1;
    int len = 0;
    struct Sentence **text1 = (struct Sentence **)malloc((len + 1) * sizeof(struct Sentence*));
    text1[0] = text.text[0];
    for (int i = 1; i < text.len; i++){
        for (int j = 0; j < (len + 1); j++){
            if (!wcscasecmp(text.text[i]->str, text1[j]->str)){
                flag = 0;
                break;
            }
        }
        if (flag){
            struct Sentence **tmp;
            len++;
            tmp = (struct Sentence **)realloc(text1, (len + 1) * sizeof(struct Sentence*));
            text1 = tmp;
            text1[len] = text.text[i];
        }
        flag = 1;
    }
    struct Text returned_text;
    returned_text.text = text1;
    returned_text.len = len + 1;
    return returned_text;
	}

struct Sentence *find_and_insert(wchar_t* str, wchar_t* sub_str, wchar_t* sub_str_rep){
    struct Sentence *sentence = (struct Sentence *)malloc(1 * sizeof(struct Sentence));
    wchar_t *s = (wchar_t *) malloc(200 * sizeof(wchar_t));
    wchar_t* buffer = (wchar_t *) malloc(200 * sizeof(wchar_t));
    wcsncpy(buffer, str, wcslen(str) - wcslen(wcsstr(str,sub_str)) );
    wcscat(buffer, sub_str_rep);
    wcscat(buffer, wcsstr(str,sub_str) + wcslen(sub_str));
    wcscpy(s, buffer);
    free(buffer);
    sentence->str = s;
    sentence->len = wcslen(s);
    return sentence;
}

struct Text replace_words(struct Text text){
    for (int i = 0; i < text.len; i++){
        if (wcsstr(text.text[i]->str, L"high noon")){
            while (wcsstr(text.text[i]->str, L"high noon")){
                text.text[i] = find_and_insert(text.text[i]->str, L"high noon", L"полдень");
            }
        }
        if (wcsstr(text.text[i]->str, L"полночь")){
            while (wcsstr(text.text[i]->str, L"полночь")){
                text.text[i] = find_and_insert(text.text[i]->str, L"полночь", L"midnight");
            }
        }
    }
    return text;
}

struct Text delete_same_start_end(struct Text text){
    int len = 0;
    struct Sentence **sentences = (struct Sentence **)malloc((len + 1) * sizeof(struct Sentence*));
    for (int i = 0; i < text.len; i++){
        wchar_t *word1;
        wchar_t *word2;
        int len_word1 = 0;
        int len_word2 = 0;
        word1 = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
        word2 = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
        for (int j = 0; text.text[i]->str[j] != ' ' && text.text[i]->str[j] != '.'; j++){
            word1[len_word1] = text.text[i]->str[j];
            wchar_t *tmp;
            tmp = (wchar_t*)realloc(word1, (j + 2) * sizeof(wchar_t));
            word1 = tmp;
            len_word1++;
        }
        for (int j = wcslen(text.text[i]->str) - 1 - len_word1; text.text[i]->str[j] != '.'; j++){
            word2[len_word2] = text.text[i]->str[j];
            wchar_t *tmp1;
            tmp1 = (wchar_t*)realloc(word2, (len_word2 + 2) * sizeof(wchar_t));
            word2 = tmp1;
            len_word2 ++;
        }
        if (wcscasecmp(word1, word2)){
            sentences[len] = text.text[i];
            struct Sentence **tmp;
            len++;
            tmp = (struct Sentence **)realloc(sentences, (len + 1) * sizeof(struct Sentence*));
            sentences = tmp;
        }

    }
    struct Text returned_text;
    returned_text.text = sentences;
    returned_text.len = len;
    return returned_text;
}
