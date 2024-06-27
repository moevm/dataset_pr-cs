#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmp(const void *a,const void *b){
    const char** f = (const char**)a;
    const char** s = (const char**)b;
    return strcmp(*f,*s);
}

int main()
{
    char text[1000];
    fgets(text,1000,stdin);
    char* key = (char*)malloc(sizeof(char)*30);
    fgets(key,30,stdin);
    char sep [10]="  .!";
    char** sentences  = (char**)malloc(sizeof(char*)*1);
    int count = 0;
    char* word = strtok(text,sep);
    while (word!= NULL)
    {
        sentences[count] = word;
        count++;
        sentences = realloc(sentences, (count+1) * sizeof(char*));
        word = strtok(NULL, sep);
    }
    qsort(sentences,count,sizeof(char*),cmp);
    char** res = bsearch(&key,sentences,count,sizeof(char*),cmp);
    if (res!=NULL)
        printf("exists");
    else
        printf("doesn't exist");
   return 0;
}
