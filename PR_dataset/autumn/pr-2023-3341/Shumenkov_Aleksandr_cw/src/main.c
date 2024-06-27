#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define AUTHOR "Course work for option 4.12, created by Shumenkov Aleksandr.\n"

char **removing(char **sentences, int *s_count);
char **separation(char *text, int s_count);
char *input(int *s_count);

int call_fun();
int calculate_product(char *sentence);
int compare_sentences(const void *a, const void *b);

void menu(int option);
void search_word(char **sentences, int s_count);
void preobrazovanie(char **sentences, int s_count);
void udalenie(char **sentences, int s_count);
void sortirovka(char **sentences, int s_count);
void vivod_posle_obr(char **sentences, int s_count);
void print_colored(char* word, char* color);
void new_task(char** sentences, int s_count, int dop_option);

// MAIN FUNCTION

int main() {
  printf(AUTHOR);
  int option = call_fun();
  menu(option);
  return 0;
}

// OPTIONS

int call_fun() {
  int option;
  scanf("%d", &option);
  return option;
}

// INPUT

char *input(int *s_count) {
  int size_str = 1;
  int text_size = 0;
  char *text = NULL;
  int count = 0;
  char symbol = getchar();
  while (count < 2) {
    symbol = getchar();
    if (symbol == '\n') {
      count++;
    } else {
      count = 0;
    }
    if (text_size + 1 >= size_str) {
      size_str = size_str * 2;
      text = (char *)realloc(text, size_str * sizeof(char));
    }
    if (symbol == '.') {
      (*s_count)++;
      if (text_size > 0 && text[text_size - 1] == ' ') {
        text[text_size - 1] = '\0';
        text_size--;
        (*s_count)--;
      }
    }
    text[text_size] = symbol;
    text_size++;
  }
  text[text_size - 2] = '\0';
  return text;
}

// SEPARATION

char **separation(char *text, int s_count) {
  char **arr = (char **)calloc(s_count, sizeof(char *));
  int i = 0;
  char *sentences = strtok(text, ".");
  while (sentences != NULL) {
    while (isspace(*sentences)) {
      sentences++;
    }
    arr[i++] = sentences;
    sentences = strtok(NULL, ".");
  }
  return arr;
}

// REMOVE_DUPLIKATES

char **removing(char **sentences, int *s_count) {
  int removed_sentences = 0;
  for (int i = 0; i < (*s_count); i++) {
    for (int j = i + 1; j < (*s_count); j++) {
      if (sentences[i] != NULL && sentences[j] != NULL) {
        if (strcasecmp(sentences[i], sentences[j]) == 0) {
          sentences[j] = NULL;
            removed_sentences++;
        }
      }
    }
  }
  char **arr = (char **)calloc((*s_count) - removed_sentences, sizeof(char *));
  int j = 0;
  for (int i = 0; i < (*s_count); i++) {
    if (sentences[i] != NULL) {
      arr[j++] = sentences[i];
    }
  }
  (*s_count) -= removed_sentences;
  return arr;
}

// CASE0

void vivod_posle_obr(char **sentences, int s_count) {
  for (int i = 0; i < s_count; i++) {
    printf("%s.\n", sentences[i]);
  }
}

// CASE1

void search_word(char **sentences, int s_count) {
  for (int i = 0; i < s_count; i++) {
    char *sentence = sentences[i];
    int length = strlen(sentence);
    int startIndex = 0;
    int flag = 1;
    for (int j = 0; j < length; j++) {
      if (((j == 0) && (strncmp(&sentence[j], "banana", 6) == 0) && (sentence[j+6] == ' ')) 
        || ((sentence[j - 1] == ' ') && (strncmp(&sentence[j], "banana", 6) == 0) && (sentence[j+6] == ' ')) 
        || ((strlen(sentence) == 6) && (strncmp(&sentence[j], "banana", 6) == 0))
        || ((sentence[j - 1] == ' ') && (strncmp(&sentence[j], "banana", 6) == 0) && (strlen(sentence) == (j + 6)))){
        for (int k = startIndex; k < j; k++) {
          printf("%c", sentence[k]);
        }
        printf("\033[1;33mbanana\033[0m");
        startIndex = j + 6;
        flag = 0;
      } else if  (((j == 0) && (strncmp(&sentence[j], "apple", 5) == 0) && (sentence[j+5] == ' ')) 
        || ((sentence[j - 1] == ' ') && (strncmp(&sentence[j], "apple", 5) == 0) && (sentence[j+5] == ' ')) 
        || ((strlen(sentence) == 5) && (strncmp(&sentence[j], "apple", 5) == 0))
        || ((sentence[j - 1] == ' ') && (strncmp(&sentence[j], "apple", 5) == 0) && (strlen(sentence) == (j + 5)))){
        for (int k = startIndex; k < j; k++) {
          printf("%c", sentence[k]);
        }
        printf("\033[1;32mapple\033[0m");
        startIndex = j + 5;
        flag = 0;
      }
    }
    if (flag) {
      break;
    } else {
      for (int k = startIndex; k <= length; k++) {
        if ((k < length)) {
          printf("%c", sentence[k]);
        } else {
          printf(".\n");
          break;
        }
      }
    }
  }
}

// CASE2

void preobrazovanie(char **sentences, int s_count) {
  for (int i = 0; i < s_count; i++) {
    int m = strlen(sentences[i]);
    for (int j = 0; j < m; j++) {
      if (isdigit(sentences[i][j])) {
        sentences[i][j] = 'D';
      } else if (isalpha(sentences[i][j])) {
        sentences[i][j] = tolower(sentences[i][j]);
      }
    }
  }
  for (int i = 0; i < s_count; i++) {
    printf("%s.\n", sentences[i]);
  }
}

// CASE3

void udalenie(char **sentences, int s_count) {
  for (int i = 0; i < s_count; i++) {
    if (strlen(sentences[i]) <= 15) {
      printf("%s.\n", sentences[i]);
    }
  }
}

// CASE4

int calculate_product(char* sentence) {
  int product = 1;
  for (int i = 0; i < strlen(sentence); i++) {
    if (isdigit(sentence[i])) {
      product *= sentence[i] - '0';
    }
  }
  return product;
}
int compare_sentences(const void* a, const void* b) {
  char* sentenceA = *(char**)a;
  char* sentenceB = *(char**)b;
  int productA = calculate_product(sentenceA);
  int productB = calculate_product(sentenceB);
  return productA - productB;
}
void sortirovka(char** sentences, int s_count) {
  qsort(sentences, s_count, sizeof(char*), compare_sentences);
  for (int i = 0; i < s_count; i++) {
    printf("%s.\n", sentences[i]);
  }
}

// MENU

void menu(int option) {
  if (option == 5) {
    printf("Cправка о функциях, которые реализует программа:\n1) Функция под номером 1 (search_word)	выводит все предложения в которых есть слово “banana” или “apple”. Слово “banana” выделяется жёлтым цветом, а слово “apple” выделяется зеленым.\n2) Функция под номером 2 (preobrazovanie) Преобразовает предложения так, чтобы в слове все буквы были строчные, а все цифры были заменены буквой ‘D’.\n3) Функция под номером 3 (udalenie) удаляет все предложения длина которых больше 15.\n4) Функция под номером 4 (sortirovka) сортирует предложения по возрастанию произведений всех цифр в них.\n5) Функция под номером 5 (information) выводит информацию о функциях, которые реализует программа.\n");
    return;
  }
  int dop_option;
  if(option == 8){
    scanf("%d", &dop_option);
  }
  int s_count = 0;
  char *text = input(&s_count);
  char **sentences = separation(text, s_count);
  sentences = removing(sentences, &s_count);
  switch (option) {
  case 0:
    vivod_posle_obr(sentences, s_count);
    break;
  case 1:
    search_word(sentences, s_count);
    break;
  case 2:
    preobrazovanie(sentences, s_count);
    break;
  case 3:
    udalenie(sentences, s_count);
    break;
  case 4:
    sortirovka(sentences, s_count);
    break;
  case 8:
    new_task(sentences, s_count, dop_option);
    break;
  default:
    printf("Error: такой функции нет.\n");
  } 
}
void new_task(char** sentences, int s_count, int dop_option){
  for(int i = 0; i < s_count; i++){
    for(int j = 0; j < dop_option - 1; j++){
      printf("%s ", sentences[i]);
    }
    printf("%s", sentences[i]);
    printf(".\n");
  }
}
