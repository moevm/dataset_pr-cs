#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define STEP_S 20
#define N 20

char *my_strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *res = (char *)malloc(len);

    if (res != NULL) {
        memcpy(res, src, len);
    }
    return res;
}
int my_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower(*s1) != tolower(*s2)) {
            return tolower(*s1) - tolower(*s2);
        }
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}
void free_memory(char **text, int max_count_string){
    for (int i = 0; i < max_count_string; i++){
         free(text[i]);
    }
    free(text);
    return;
}

void checkNull(char **text, int max_count_string, void *ptr){
    if (ptr == NULL){
        free_memory(text, max_count_string);
        fprintf(stderr, "error: Memory Allocation Error\n");
        exit(0);
     }
}

void count_numbers_in_text(char **text, int *count_sents, int *numbers){
    for (int i = 0; i < *count_sents; i++){
        for (int j = 0; text[i][j]; j++){
            if (isdigit(text[i][j])){
                int digit = text[i][j] - '0';
                numbers[digit]++;
            }
        }  
    }
}

int countWordsOfLengthThree(const char *sentence){
    int count = 0;
    char *sentenceCpy = my_strdup(sentence);
    if (sentenceCpy == NULL){
        fprintf(stderr, "error: Memory Allocation Error\n");
        exit(0);
    }
    char *token = strtok(sentenceCpy, " ,.");
    while (token != NULL){
        if (strlen(token) == 3){
            count++;
        }
        token = strtok(NULL, " ,.");
    }
    free(sentenceCpy);
    return count;
}
int cmp(const void *a, const void *b){
    const char *sentA = *(const char **)a;
    const char *sentB = *(const char **)b;
    int countA =  countWordsOfLengthThree(sentA);
    int countB =  countWordsOfLengthThree(sentB);
    return countB - countA;
}
void sort_sents_words_three(char **text, int *count_sents){
     qsort(text, *count_sents, sizeof(char *), cmp);
}
char **remove_sents_with_physics(char **text, int *count_sents, int *max_count_string){
    const char* keyword = "physics";
    char *test;
    int i = 0;
    while (i < *count_sents){
        char *sentenceCopy = my_strdup(text[i]);
        checkNull(text, *max_count_string, sentenceCopy);
        
        char *word = strtok(sentenceCopy, " ,.");
        while (word != NULL){
            if (my_strcasecmp(word, keyword) == 0){
                test = text[i];
                for (int j = i; j < *max_count_string - 1; j++){
                    text[j] = text[j + 1];
                }
                free(test);
                *max_count_string = *max_count_string - 1;
                *count_sents = *count_sents - 1;
                i--;
                break;
            }
            word = strtok(NULL, " ,.");
        }
        i++;
        free(sentenceCopy);
    }
    return text;
}

char **reverse_sentences(char **text, int *count_sents){
    for (int i = 0; i < *count_sents; i++){
        int len = strlen(text[i]);
        int st = 0, end = len - 1;
        while (st < end){
            if (text[i][st] == '.' || text[i][st] == ' ' || text[i][st] == ','){
                st++;
                continue;
            }
            if (text[i][end] == '.' || text[i][end] == ' '|| text[i][end] == ','){
                end--;
                continue;
            }
            char tmp = text[i][end];
            text[i][end] = text[i][st];
            text[i][st] = tmp;
            end--;
            st++;
        }
    }
    return text;
}

char **read_text(int *count_sents,int *max_count_string){
      char **text = malloc(sizeof(char*) * N);
      if (text == NULL){
          fprintf(stderr, "Memory Allocation Error\n");
          exit(0);
      }
      for (int k = 0; k < N; k++){
          text[k]= malloc(sizeof(char) * STEP_S);
          checkNull(text, k, text[k]);
      }
      char c;
      int j = 0, end_is_newline = 0, count_end = 0;
      while(1){
          int i = 0, size = STEP_S;
          int is_start_sent = 1;
          do{
              if (i % STEP_S == STEP_S - 1){
                  size += STEP_S;
                  char *test = text[j];
                  test = (char*)realloc(test, (size) * sizeof(char));
            	  checkNull(text, *max_count_string, test);
                  text[j] = test;
              }
              c = getchar();
              if (c == '\n' && count_end == 1){
                   end_is_newline = 1;
                   text[j][i-1] = '\0';
                   i++;
                   break;
              }
              if (c == '\n'){
                   c = ' ';
                   count_end++;
              }else{
                   count_end = 0;
              }
              if (is_start_sent){
                  if (isblank(c) || c == '.'){ 
                      continue;
                  }else{is_start_sent = 0;}
              }
              text[j][i] = c;
              i++;
    
         }while(c != '.');
         
         text[j][i] = '\0';
         if (end_is_newline){
             if (i > 1){
                 j++;
             }
             break;
         }
         j++;
         if (j % N == 0){
             *max_count_string = *max_count_string + N;
             char **test = text;
             test = (char **)realloc(text, *max_count_string * sizeof(char *));
             checkNull(text, *max_count_string, test); 
             text = test;
             for (int f = j; f < *max_count_string; f++){
                 text[f] = malloc(sizeof(char) * STEP_S);
                 checkNull(text, f, text[f]);
             }
         }
      }
      //text[j][0] = '\0';
      *count_sents = j;
      return text;
}
char **del_identical_sents(char **text, int *count_sents, int *max_count_string){
    int i = 0;
    char *test;
    while (i < *count_sents){
        int j = i + 1;
        while (j < *count_sents){
            if (my_strcasecmp(text[i], text[j]) == 0){
                test = text[j];
                for (int k = j; k < *max_count_string - 1; k++){
                     text[k]=text[k+1];
                }
                free(test);
                *max_count_string = *max_count_string - 1;
            *count_sents = *count_sents - 1;
            }else{
            j++;
            }
        }
        i++;
    }
    return text;
}

void out(char **text, int count_sents){
    for (int j = 0; j < count_sents; j++){
        printf("%s\n", text[j]);
    }
    return;
}
void info(){
    printf("Information about course work.\n");
    printf("0 - Primary text processing.\n");
    printf("1 - Print a list of all the numbers found throughout the text and the frequency of their mention.\n");
    printf("2 - Convert the sentence so that characters other than separators go in reverse order. For example, for the string abc defg. the result will be gfe dcba.\n");
    printf("3 - Delete all sentences in which the word physics occurs.\n");
    printf("4 - Sort sentences by reducing the number of words whose length is 3.\n");
    printf("5 - Display information about functions in programm.\n");
}
int count_num(const char *word){
    int res_sum = 0; //итоговая сумма
    for (int j = 0; word[j]; j++){
            if (isdigit(word[j])){
                int digit = word[j] - '0';
                res_sum += digit;
            }
    }
    return res_sum;
}
int cmp9(const void *a, const void *b){
    const char *sentA = *(const char **)a;
    const char *sentB = *(const char **)b;
    int countA = count_num(sentA);
    int countB = count_num(sentB);
    return countA - countB;
}
void nine(char **text, int *count_sents){
    for (int i = 0; i < *count_sents; i++){
         char *sent = text[i];
         char **words;
         int size = 0;
         char *word = strtok(sent, " ,.");
         while (word != NULL){
            words = (char**)realloc(words, sizeof(char*) * (size + 2));
            words[size] = malloc(sizeof(char) * (strlen(word) + 2));
            strncpy(words[size], word, strlen(word));
            ++size;
            word = strtok(NULL, " ,.");
        }
         qsort(words, size, sizeof(char *), cmp9);
         for (int n = 0; n < size; ++n ){
            if (n < size - 1){
                printf("%s ", words[n]);
            }else{
                printf("%s.\n", words[n]);
            }
         }   
            do {
                free(words[--size]);
            } while (size);
            free(words);
            free(sent);
    }
}
int main(){
    printf("Course work for option 4.7, created by Anton Enikeev.\n");
    char **text;
    int instruction = -1, count_sents = 0;
    int max_count_string = N;
    int check_err = scanf("%d", &instruction) - 1;
    if (check_err){
        printf("Error: instruction reading error.\n");
    }else if ((instruction != 9 && instruction > 5) || (instruction != 9 && instruction < 0)){
        printf("Error: the instruction number is incorrect.\n");
    }
    if (instruction == 5){
        info();
        return 0;
    }
    switch(instruction){
        case 0:
            text = read_text(&count_sents, &max_count_string);
            del_identical_sents(text, &count_sents, &max_count_string);
            out(text, count_sents);
            break;
        case 1:
            text = read_text(&count_sents, &max_count_string);
            del_identical_sents(text, &count_sents, &max_count_string);
            int numbers[10] = {0};
            count_numbers_in_text(text, &count_sents, numbers);
            for (int j = 0; j <  10; j++)
                printf("%d: %d\n", j, numbers[j]);
           break;
        case 2:
            text = read_text(&count_sents, &max_count_string);
            del_identical_sents(text, &count_sents, &max_count_string); 
            reverse_sentences(text, &count_sents);
            out(text, count_sents);
            break;
        case 3:
            text = read_text(&count_sents, &max_count_string);
            del_identical_sents(text, &count_sents, &max_count_string); 
            text = remove_sents_with_physics(text, &count_sents, &max_count_string);
            out(text, count_sents);
            break;
        case 4:
            text = read_text(&count_sents, &max_count_string);
            del_identical_sents(text, &count_sents, &max_count_string);
            sort_sents_words_three(text, &count_sents);
            out(text, count_sents);
            break;
        case 9:
            text = read_text(&count_sents, &max_count_string);
            del_identical_sents(text, &count_sents, &max_count_string);
            nine(text, &count_sents);
            break;
            
    }
    if (text != NULL){
        free_memory(text, max_count_string);
    }
    return 0;
}



