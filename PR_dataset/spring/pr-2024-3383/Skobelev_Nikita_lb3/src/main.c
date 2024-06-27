#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
char search[1000];
char**itog;
void go(char DirPath[]){
    DIR *dir = opendir(DirPath);
    //puts(DirPath);
    if(dir == NULL){
            //printf("%s\n",DirPath);
            if(DirPath[strlen(DirPath)-6] == '/'){
                    //puts("ok");
                    char*tec = strchr(search,DirPath[strlen(DirPath)-5]);
                    if(tec != NULL)
                    //itog[tec-search]=strdup(DirPath);
                    {itog[tec-search]=(char*)malloc(sizeof(char)*(strlen(DirPath)+5));
                    strcpy(itog[tec-search],DirPath);}
                    //printf("%d",tec-search);}
            }
    }
//    a.txt5
//    01234
    else{
        struct dirent *files;
        while((files = readdir(dir))!= NULL){
            char di[100]="";
            strcat(di,DirPath);
            strcat(di,"/");
            strcat(di, files->d_name);
            //puts(di);
            if(strcmp(files->d_name,".")==0)continue;
            if(strcmp(files->d_name,"..")==0)continue;
            go(di);
        }
    }
    closedir(dir);
}
int main(){
    fgets(search, 1000, stdin);
    *strstr(search,"\n")=0;
    itog = (char**)malloc(sizeof(char*)*strlen(search));
    char file_name[]="result.txt";
    FILE *file = fopen(file_name, "w");
    go("./tmp");
    for(int i=0;i<strlen(search);++i){fputs(itog[i],file);fputs("\n",file);}
    fclose(file);
    return 0;

}
