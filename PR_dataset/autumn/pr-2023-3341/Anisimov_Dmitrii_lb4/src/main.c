#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LENBUF 1000
#define LENKEY 30
int comparator(const void* a, const void* b){
    char* str_first=*((char**)a);
    char* str_second=*((char**)b);
    return strcmp(str_first, str_second);
}
char** getText(char** key, int* line_number)
{
    char buf[LENBUF+1];
    fgets(buf, LENBUF,stdin);
    *key = (char*)malloc(LENKEY+1);
    fgets(*key, LENKEY, stdin);
    char **text=(char**)malloc(sizeof(char*));
    text[0]=(char*)malloc(100);
    char* first=strtok(buf, " .");
    *line_number=1;
    strcpy(text[0],first);
    do{
        first=strtok(NULL, " .");
        if (first!=NULL){
            text=(char**)realloc(text, sizeof(char*)*((*line_number)+1));
            text[*line_number]=(char*)malloc(100);
            strcpy(text[*line_number],first);
            (*line_number)++;
        }
        //printf("> %d\n", *line_number);
    }
    while(first!=NULL);
    return text;
}
void findWord(char** text, char* key, int line_number)
{
    qsort(text, line_number, sizeof(char*),comparator);
    char* res = (char*)bsearch(&key, text, line_number, sizeof(char*), comparator);
    if(res==NULL)
    printf("doesn't exist");
    else
    printf("exists");
}
int main()
{
    char* key;
    char** text;
    int line_number;
    text=getText(&key, &line_number);
    findWord(text, key, line_number);
    return 0;
}
