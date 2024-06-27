#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h> 

#define LINE_FEED '\n'
#define END_STR '\0'
#define EXIT_DIR ".."
#define SAME_DIR "."

char* pattern = "([A-z0-9_]+\\.txt)";

int isDir(char* filename, unsigned char d_type);
void recSearchFile(char* filename, char* path, char* allPathes);
void writeResult(char* allpathes, char* filename);
char* returnFileName(char* buffer);
char* addPath(char* oldPath, char* newPath);

int main(){
    char* allPathes = NULL;
    recSearchFile("file.txt", "./labyrinth", allPathes);
    return 0;
}

char* returnFileName(char* buffer){
    regex_t regexCompiled;
    regcomp(&regexCompiled, pattern, REG_EXTENDED);
    regmatch_t groups[2];

    int j = 0;
    char* filename = (char*)malloc(sizeof(char) * ((groups[1].rm_eo - groups[1].rm_eo) + 1));
    if(regexec(&regexCompiled, buffer, 2, groups, 0) == 0){
        for(int i = groups[1].rm_so; i < groups[1].rm_eo; i++){
            filename[j++] = buffer[i];
        }
        filename[j] = '\0';
        return filename;
    }else{
        return NULL;
    }
}

char* addPath(char* oldStr, char* newPath){
    char* newStr;
    if (oldStr == NULL){
        newStr = (char*)malloc(sizeof(char)*(strlen(newPath) + 1));
        strcpy(newStr, newPath);
        return newStr;
    }
    newStr = (char*)malloc(sizeof(char)*(strlen(oldStr) + strlen(newPath) + 2));
    sprintf(newStr, "%s\n%s", oldStr, newPath);
    return newStr;
}

int isDir(char* d_name, unsigned char d_type){
    if (d_type == DT_DIR && strcmp(d_name, EXIT_DIR) && strcmp(d_name, SAME_DIR))
        return 1;
    else
        return 0;
}

void writeResult(char* allPathes, char* filename){
    FILE *nfp = fopen(filename, "w");
    if(nfp){
        fputs(allPathes, nfp);
        fclose(nfp);
    }
}

void recSearchFile(char* filename, char* path, char* allPathes){
    DIR* fileThread;
    struct dirent* file;
    fileThread = opendir(path);
    if(fileThread == NULL){
        printf("Error, fileThread won't be open");
        exit(1);
    }

    while((file = readdir(fileThread)) != NULL){
        if (strcmp(filename, file->d_name) == 0 && file->d_type == DT_REG) //нашли файлик
        {
            char* fullPathFile = (char*)malloc(sizeof(char)*(strlen(path)+strlen(filename) + 2));
            sprintf(fullPathFile, "%s/%s", path, file->d_name);
            
            allPathes = addPath(allPathes, fullPathFile); 

            char buffer[256];
            FILE *fp = fopen(fullPathFile, "r");

            if(fp){   
                while((fgets(buffer, 256, fp))!=NULL){ //читаем найденный файлик

                    if(!strcmp(buffer, "Minotaur"))
                        writeResult(allPathes, "result.txt");
                    else
                    {

                        char* nameNextFile = returnFileName(buffer);
                        if (nameNextFile != NULL)
                            recSearchFile(nameNextFile, ".", allPathes);
                    }
                }
                fclose(fp);
            } 
        }
        else if(isDir(file->d_name, file->d_type)){ //опускаемся в подкаталог
            char* new_dir = (char*)malloc(sizeof(char)*(strlen(path)+strlen(file->d_name) + 2));
            sprintf(new_dir, "%s/%s", path, file->d_name);
            recSearchFile(filename, new_dir, allPathes);
        }
    }

    if(closedir(fileThread) == -1){
        printf("FileThread don't be close");
        exit(1);
    }
}