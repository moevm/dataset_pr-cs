#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmp(const void *a, const void *b){
    const char *str1 = *(const char**)a;
    const char *str2 = *(const char**)b;
    return strcmp(str1, str2);
}
int cmp1(const void *a, const void *b){
    return strcmp((char *)a, *(char **)b);
}

int main(){
    int r = 2;
    char c = getchar();
    char* text = (char*)malloc(sizeof(char));
    int i =0;
    while(c != '\n' && i <= 1000){
        text[i++] = c;
        if (i>r) {
            r *= 2;
            text = realloc(text,r*sizeof(char));
        }
        c = getchar();

    }
    text[i+1] = '\0';
    char input_word[20];
    scanf("%s", input_word);
    char** words = (char**)malloc(250*sizeof(char*));
    int count =0;
    char* ptr = strtok(text, " .");
    while (ptr != NULL){
        words[count] = (char*)malloc(30*sizeof(char));
        words[count] = strdup(ptr);
        ptr = strtok(NULL, " .");
        count++;
    }
    
    qsort(words, count, sizeof(char*), cmp);
    char** search_ptr = (char**)bsearch(&input_word, words, count, sizeof(char*), cmp1);
    if (search_ptr != NULL){
        printf("exists");
    }
    else printf("doesn't exist");
    for (int pops = 0; pops < count; pops++){
        free(words[pops]);
    }
    free(words);
    free(text);
    return 0;
}
