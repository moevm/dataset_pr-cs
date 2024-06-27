#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define END_OF_LINE '\0'
#define MAX_ARRAY_LENGTH 100
#define FORBIDDEN_SYMBOL '7'

int text_formatting();

int main() {
    text_formatting();
}

int text_formatting() {
  int len = 0, max_len = MAX_ARRAY_LENGTH, counter = 0, trash = 0;
  char *sentence = calloc(MAX_ARRAY_LENGTH, sizeof(char));
  char symbol;
  while (1){
    symbol = getchar();
    if (symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!'){
      if (len != -1) {
        sentence[len++] = symbol;
        if (len == max_len - 2){
          max_len += MAX_ARRAY_LENGTH;
          sentence = realloc(sentence, max_len * sizeof(char));
        }
        sentence[len++] = '\n';
        sentence[len] = END_OF_LINE;
        printf("%s", sentence);
      }
      if (symbol == '!') break;
      counter += 1;
      len = 0;
    }
        else{
      if ((len == 0 && isblank(symbol)) || len == -1 || symbol == '\n') continue;
      if (symbol == FORBIDDEN_SYMBOL) {
        len = -1;
        trash += 1;
        continue;
      }
      sentence[len++] = symbol;
      if (len == max_len){
        max_len += MAX_ARRAY_LENGTH;
        sentence = realloc(sentence, max_len * sizeof(char));
      }
    }
  }
  free(sentence);
  printf("Количество предложений до %d и количество предложений после %d", counter, counter - trash);
}