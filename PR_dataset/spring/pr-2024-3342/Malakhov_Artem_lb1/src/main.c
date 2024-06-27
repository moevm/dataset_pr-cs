#include <stdio.h>
#include <string.h>
#include <regex.h>
#define PATTERN "([a-zA-Z]+://)?(www\\.)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9]+)+)/((\\w+/)*)([a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+))*\n$"
#define MAX_GROUP 9
#define END_OF_TEXT "Fin."


void print_match(char *sentence, regmatch_t groupArray[], int groupIndex)
{
    for (int i = groupArray[groupIndex].rm_so; i < groupArray[groupIndex].rm_eo; i++)
    {
        printf("%c", sentence[i]);
    }
}

int main(){
  regex_t regex;
  char sentence [100];
  regmatch_t groupArray[MAX_GROUP];

  regcomp(&regex, PATTERN, REG_EXTENDED);
  
  while (fgets(sentence, 100, stdin) != NULL && strstr(sentence, END_OF_TEXT) == NULL) {
    if(regexec(&regex, sentence, MAX_GROUP, groupArray, 0) == 0){
      print_match(sentence, groupArray, 3); 
      printf(" - ");
      print_match(sentence, groupArray, 7);
      printf("\n");
    }
  }
  regfree(&regex);
  return 0;
}
