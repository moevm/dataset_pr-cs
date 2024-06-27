#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct file{
    char* filename;
    long int number;
    char* string;
} file;

typedef struct List{
    file** files;
    int count;
    int buf;
} List;

int 
compare(const void* a, const void* b){
    const file** f=(const file**)a;
    const file** s=(const file**)b;
    if ((*f)->number>(*s)->number){
        return 1;
    }
    else if ((*f)->number<(*s)->number){
        return -1;
    }
    else{
        return 0;
    }
}

char* 
regular(char* filename){
    regex_t regComp;
    regmatch_t array_groups[2];

    if (regcomp(&regComp, "(-?[0-9]+) [A-Za-z0-9,.!?;:'-_ ]+" , REG_EXTENDED)){
        return 0;
    }

    char* s=(char*)calloc(100,sizeof(char));
    int j=0;
    if (regexec(&regComp, filename, 2, array_groups, 0)==0){
        for (int i=array_groups[1].rm_so; i<array_groups[1].rm_eo; i++){
            s[j++]=filename[i];
        }
    }
    regfree(&regComp);

    if (strlen(s)>0){
        return s;
    }
    else{
        return NULL;
    }
}

void 
dirv(char* startdir, List* L){
    char* path;
    DIR* dir=opendir(startdir);
    struct dirent* tek=readdir(dir);
    while (tek!=NULL){
        if (tek->d_type==4 && strcmp(tek->d_name, ".")!=0 && strcmp(tek->d_name, "..")!=0){
            path=(char*)calloc((strlen(tek->d_name)+strlen(startdir)+2),sizeof(char));
            strncpy(path,startdir,strlen(startdir));
            strcat(path,"/");
            strncat(path, tek->d_name, strlen(tek->d_name));
            dirv(path, L);
        }
        if (strcmp(tek->d_name+strlen(tek->d_name)-4, ".txt")==0){
        path=(char*)calloc((strlen(tek->d_name)+strlen(startdir)+2),sizeof(char));
        strncpy(path,startdir,strlen(startdir));
        strcat(path,"/");
        strncat(path, tek->d_name,strlen(tek->d_name));

        FILE* filetek=fopen(path,"r");
        char s[100];
        fgets(s,100,filetek);
        if (regular(s)!=NULL){
            if (L->count==L->buf){
                l->buf+=10;
                L->files=(file**)realloc(L->files,sizeof(file*)*L->buf);
            }
            L->files[L->count]=(file*)malloc(sizeof(file));
            L->files[L->count]->filename=(char*)calloc((strlen(tek->d_name)+1),sizeof(char));
            strncpy(L->files[L->count]->filename, tek->d_name, strlen(tek->d_name));
            L->files[L->count]->number=strtol(regular(s),NULL,10);
            L->files[L->count]->string=(char*)calloc((strlen(s)+1),sizeof(char));
            strncpy(L->files[L->count++]->string, s, strlen(s));
        }
        fclose(filetek);
        }
        tek=readdir(dir);
    }
    closedir(dir);
}

int 
main(){
    List* L=(List*)malloc(sizeof(List));
    L->count=0;
    L->buf=10;
    L->files=(file**)malloc(sizeof(file*)*L->buf);
    dirv(".", L);
    qsort(L->files, L->count, sizeof(file*), compare);
    FILE* f=fopen("./result.txt","w");
    for (int i=0; i<L->count; i++){
        fprintf(f,"%s\n", L->files[i]->string);
    }
    fclose(f);
    return 0;
}
