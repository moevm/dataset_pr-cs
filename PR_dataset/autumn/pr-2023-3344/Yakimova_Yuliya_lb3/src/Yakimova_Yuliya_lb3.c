#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main() {
    char **senten_arr = malloc(sizeof(char*));
    int count_before = 0, count_after = 0;
 
    while(1){
        count_before++;
        char *curr_senten = malloc(sizeof(char));
        int chr_count = 0;
        char chr = 'c';
 
        while (chr != '.' && chr != ';' && chr !='?' && chr != '!') {
            chr = getchar();
            curr_senten[chr_count] = chr;
            chr_count++;
            curr_senten = realloc(curr_senten, (chr_count + 1) * sizeof(char));
        }
        curr_senten[chr_count] = '\0';
 
        if (curr_senten[0] == ' ' || curr_senten[0] == '\n') {
            memmove(curr_senten, curr_senten + 1, strlen(curr_senten));
        }
 
        if (strchr(curr_senten,'7') == NULL) {
            senten_arr[count_after] = curr_senten;
            count_after++;
            senten_arr = realloc(senten_arr, (count_after + 1) * sizeof(char*));
        }
 
        if (strstr(curr_senten, "Dragon flew away")) {
            break;
        }
    }
 
  for (int i = 0; i < count_after; i++) {
        printf("%s\n", senten_arr[i]);
        free(senten_arr[i]);
  }
  free(senten_arr);
  
  printf("Количество предложений до %d и количество предложений после %d\n", count_before - 1, count_after - 1);
  
  return 0;
}