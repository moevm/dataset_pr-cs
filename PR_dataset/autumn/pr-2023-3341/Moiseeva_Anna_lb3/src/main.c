#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP_SIGN "Dragon flew away!"
#define TXT_SIZE 100
#define BUF free(text);
#define END_CHAR '\0'

int quest_mark(char *symbol){
  int correct = 0;
  int len_text = strlen(symbol);
  if(symbol[len_text-1] == '?'){
    correct = 1;
  }
  return correct;
}

void print_res(char *text, int start_sent_count, int end_sent_count){
  printf("%s\n", text);
  printf("Количество предложений до %d и количество предложений после %d\n", start_sent_count, end_sent_count);
}

void readAndProcessText(char *text) {
  int len_text = TXT_SIZE;
  int index = 0;
  int start_sent_count = 0, end_sent_count = 0;
  char letter;
  while (strcmp(text, STOP_SIGN)){
    letter = getchar();
    if ((index == 0) && ((letter == '\t') || (letter == ' '))){
      continue;
    }
    if (index == len_text - 2){
      len_text += TXT_SIZE;
      text = (char*)realloc(text, len_text*sizeof(char));
    }
    text[index] = letter;
    index++;

    if ((letter == '.') || (letter == ';')){
      text[index] = END_CHAR;
      printf("%s\n", text);
      BUF
      text = (char*)calloc(len_text, sizeof(char));
          start_sent_count++;
          end_sent_count++;
      index = 0;
      }
    if (quest_mark(text) == 1){
          start_sent_count++;
      index = 0;
      BUF
      text = (char*)calloc(len_text, sizeof(char));
          }
          }
          print_res(text, start_sent_count, end_sent_count);
  BUF
}

int main() {
  char* text = (char*)malloc(TXT_SIZE*sizeof(char));
  readAndProcessText(text);
  return 0;
}