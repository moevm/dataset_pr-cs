#include "structs.h"
#include "ninth_function.h"

wchar_t* to_lower(wchar_t *word){
    wchar_t *new_word = wcsdup(word);
    for (int i=0; new_word[i]!=L'\0'; i++){
        new_word[i] = towlower(new_word[i]);
    }
    return new_word;
}

bool is_palindrome1(const wchar_t* word) {
  size_t i = 0;
  size_t j = wcslen(word) - 1;
  while (i < j) {
    if (!iswalpha(word[i]) && !iswdigit(word[i])) {
      i++;
      continue;
    }
    if (!iswalpha(word[j]) && !iswdigit(word[j])) {
      j--;
      continue;
    }
    if (word[i] != word[j]) {
      return false;
    }
    i++;
    j--;
  }
  return true;
}

int pallindroms_in_sents(struct Sentence *sen){
    int word_count =0;
    int pal_count = 0;
    wchar_t *state;
    wchar_t *str = malloc((sen->size+1)* sizeof(wchar_t));
    wchar_t *new_str = wcsdup(sen->str);
    wcscpy(str, sen->str);
    wchar_t seps[] = L".";
    wchar_t *token;
    token = wcstok(str, seps, &state);
    while (token!=NULL){
        pal_count += is_palindrome1(to_lower((token)));
        word_count +=1;
        token = wcstok(NULL, seps, &state);
    }
    if (pal_count == word_count){
        wprintf(L"%ls", new_str);
    }
    
    free(str);
    free(new_str);
    return 0;
}

int pals_analys(struct Text *text){ 
    for (int i = 0; i < text->n; i++) { 
        pallindroms_in_sents(text->sents[i]);
    }
    return 0;
}