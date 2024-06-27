#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define PATTERN "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)"
#define END_WORD "Fin."
#define START_TEXT_SIZE 10

int main();
void regex(char* text, regex_t regex_comp);
void input_text(char** text);
void print_regex(char* text, regmatch_t match);

int main(){
    regex_t regex_comp;
    regcomp(&regex_comp, PATTERN, REG_EXTENDED);
    int flag = 0;
    while (flag != 1) {
        char* text = (char* )malloc(START_TEXT_SIZE * sizeof(char));
        input_text(&text);
        regex(text, regex_comp);
        if(strcmp(text, END_WORD) == 0){
          flag = 1;
        }
  }
}

void input_text(char** text){
    char c;
    int text_size = START_TEXT_SIZE, i = 0;
    while ((c = getchar()) != '\n'){
        if(i + 1 == text_size){
          text_size += START_TEXT_SIZE;
          (*text) = (char*)realloc((*text), text_size * sizeof(char));
        }
        (*text)[i++] = c;
        if(strcmp((*text), END_WORD) == 0){
          break;
    }
    (*text)[i] = '\0';
    }
}

void regex(char* text, regex_t regex_comp){
  regmatch_t matches[3];
  if (regexec(&regex_comp, text, 3, matches, 0) == 0) {
    print_regex(text, matches[1]);
    printf(" - ");
    print_regex(text, matches[2]);
    printf("\n");
  }
}

void print_regex(char* text, regmatch_t match) {
  for (int i=match.rm_so; i<match.rm_eo; i++) {
    printf("%c", text[i]);
  }
}
