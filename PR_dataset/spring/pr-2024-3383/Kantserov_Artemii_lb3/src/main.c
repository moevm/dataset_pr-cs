#include <stdio.h>
#include <dirent.h>
#include <string.h>

char* file_txt[4000];
int  kol = 0;
char* file_txt_dir[4000];

void go(char dirPath[], char*past){
    DIR *dir= opendir(dirPath);
    if (dir==NULL){
        file_txt[kol] = strdup(past);
        file_txt_dir[kol++] = strdup(dirPath);
    }
    else{
        struct dirent *files;
        while( (files=readdir(dir))!=NULL){
            if(files->d_name[0]!='.'){
                char di[100]="";
                strcat(di, dirPath);
                strcat(di, "/");
                strcat(di, files->d_name);
                go(di, files->d_name);
            }
        }
    }
    closedir(dir);
}
char *itog[4000];
int  itog_kol = 0;
short flag = 1;
void search(char*find){
    for(int i=0;i<kol && flag;i++){
        if(strcmp(file_txt[i], find)==0){
            FILE *f = fopen(file_txt_dir[i], "r");
            char line[100]= "";
            while(fgets(line, 100, f)!=NULL && flag){
                if(line[strlen(line)-1]=='\n')line[strlen(line)-1]='\0';
                if(strcmp(line, "Deadlock")==0){
                    break;
                }
                if(strcmp(line, "Minotaur")==0){
                    itog[itog_kol] = file_txt_dir[i];
                    flag = 0;
                    break;
                }
                else{
                    char *id = strstr(line, "file");
                    itog[itog_kol++] = file_txt_dir[i];
                    search(id);
                    if(flag)--itog_kol;

                }
            }
            fclose(f);
        }
    }
}
int main() {
    go("./labyrinth", "12");
    search("file.txt");
    FILE* f = fopen("/home/box/result.txt", "w");
    for(int i=0;i<=itog_kol;i++){
        fprintf(f,"%s\n", itog[i]);
    }
    fclose(f);
    return 0;
}