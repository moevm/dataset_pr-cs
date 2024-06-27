#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int containts_seven(char *string);
char* removeFirstSpace(char *string);

int main() {
  char **sentences_array = malloc(1 * sizeof(char*));
  char *sentence = malloc(1 * sizeof(char));
  int sentences_count = 0;
  int overall_sentences_count = 0;
  int letter_count = 0;
  char letter;

  while (1) {

    overall_sentences_count++;
    free(sentence);
    sentence = malloc(1 * sizeof(char));
    letter = '1';

    while (letter != '.' && letter != ';' && letter != '?' && letter != '!') {
      if (letter == '\n') {
        letter = ' ';
      }
        letter = getchar();
        sentence[letter_count] = letter;
        letter_count++;
        sentence = realloc(sentence, letter_count + 1);
    }

    sentence[letter_count] = '\0';
    
    if (containts_seven(sentence) == 0) {
      sentences_array[sentences_count] = sentence;
      sentences_count++;
      sentences_array = realloc(sentences_array, (sentences_count + 1) * sizeof(char*));
    }

    if (strstr(sentence, "Dragon flew away")) {
      break;
    }

    letter_count = 0;
    sentence = malloc(1 * sizeof(char));
  }

  for (int i = 0; i < sentences_count; i++) {
    printf("%s\n", removeFirstSpace(sentences_array[i]));
  }

  free(sentence);
  free(sentences_array);

  printf("Количество предложений до %d и количество предложений после %d", overall_sentences_count-1, sentences_count-1);

  return 0;
}

int containts_seven(char *string) {
  for (int i = 0; i < strlen(string); i++){
    if (string[i] == '7') {
      return 1;
    }
  }
  return 0;
}

char* removeFirstSpace(char *string) {
    if (string[0] == ' ') {
        memmove(string, string + 1, strlen(string));
    }
    return string;
}