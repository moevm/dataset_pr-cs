#include "structs.h"
#include "first_function.h"

bool is_palindrome(const wchar_t* word) {
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



int pallindroms(struct Sentence *sen){
    int word_count =0;
    int pal_count = 0;
    wchar_t *state;
    wchar_t *str = malloc((sen->size+1)* sizeof(wchar_t));
    wcscpy(str, sen->str);
    wchar_t seps[] = L" ,.";
    wchar_t *token;
    token = wcstok(str, seps, &state);
    while (token!=NULL){
        pal_count += is_palindrome(token);
        word_count +=1;
        token = wcstok(NULL, seps, &state);
    }
    wprintf(L"%ls\t", sen->str);
    if (pal_count ==0){
        wprintf(L"Кто-то потерял все палиндромы.\n");
    }
    else if (pal_count == word_count){
        wprintf(L"Палиндромы на месте.\n");
    }
    else{
       wprintf(L"Чего-то не хватает.\n"); 
    }
    free(str);
    return 0;
}



int pallindrom_analys(struct Text *text){ 
    for (int i = 0; i < text->n; i++) { 
        pallindroms(text->sents[i]); 
    }
    return 0;
}
