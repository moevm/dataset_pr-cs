#include "Common.h"
#include "FunctionText.h"

char** functionText(int* count_sent) {
 int lenght = 20, width = 20;
 char symbol;
 int end = 0;
 char** text = malloc(sizeof(char*) * lenght);
 *count_sent = 0;
 for (int n = 0;; n++) {
  while (strchr(" \t\n", symbol = getchar())) {
   if (symbol == '\n') {
    end++;
    if (end == 2) {
     return text;
    }
    continue;
   }
  }
  char* sentens = malloc(sizeof(char) * width);

  end = 0;
  int m = 0;
  for (; symbol != '.'; m++) {
   sentens[m] = symbol;

   if (m > width - 1) {
    width += 20;
    sentens = realloc(sentens, sizeof(char) * width);
   }
   symbol = getchar();
  }
  sentens[m] = '.';
  m++;
  if (m > width - 1) {
   width += 20;
   sentens = realloc(sentens, sizeof(char) * width);
  }
  sentens[m] = '\0';
  text[n] = sentens;
  (*count_sent)++;
  if (*count_sent >= lenght) {
   lenght += 20;
   text = realloc(text, sizeof(char*) * lenght);
  }
 }
}
