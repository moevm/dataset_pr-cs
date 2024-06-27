#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h> 

char* pattern = "([A-z0-9_]+\\.txt)";
#define NEW_LINE '\n'
#define END_LINE '\0'
#define BUFFER_SIZE 256

char* return_Fname(char* buffer){
    regex_t regexCompiled;
    regcomp(&regexCompiled, pattern, REG_EXTENDED);
    regmatch_t groups[2];

    int j = 0;
    char* file_name = (char*)malloc(sizeof(char) * ((groups[1].rm_eo - groups[1].rm_eo) + 1));

    if(regexec(&regexCompiled, buffer, 2, groups, 0) == 0){
        for(int i = groups[1].rm_so; i < groups[1].rm_eo; i++){
            file_name[j++] = buffer[i];
        }
        file_name[j] = END_LINE;
        return file_name;
    }else{
        return NULL;
    }
}

char* add_path(char* old_String, char* new_path){
    char* new_string;

    if (old_String == NULL){
        new_string = (char*)malloc(sizeof(char)*(strlen(new_path) + 1));
        strcpy(new_string, new_path);
        return new_string;
    }

    new_string = (char*)malloc(sizeof(char)*(strlen(old_String) + strlen(new_path) + 2));
    strcpy(new_string, old_String);

    int size = strlen(old_String);
    int maxsize = strlen(old_String) + strlen(new_path) + 1;
    int j = 0;
    
    new_string[size] = NEW_LINE;

    for(int i = size + 1; i < maxsize + 1; i++){
        new_string[i] = new_path[j++];
    }

    new_string[maxsize] = END_LINE;
    return new_string;
}


void find_File(char* file_name, char* path, char* paths){
    DIR* file_status;
    struct dirent* file;
    file_status = opendir(path);
    
    if(file_status == NULL){
        printf("Error, directory won't be open");
        exit(1);
    }

    while((file = readdir(file_status)) != NULL){
        if (strcmp(file_name, file->d_name) == 0 && file->d_type == DT_REG)
        {
            char* file_path = (char*)malloc(sizeof(char)*(strlen(path)+strlen(file_name) + 2));
            sprintf(file_path, "%s/%s", path, file->d_name);

            paths = add_path(paths, file_path); 

            char buffer[BUFFER_SIZE];
            FILE *fp = fopen(file_path, "r");

            if(fp){   
                while((fgets(buffer, BUFFER_SIZE, fp))!=NULL){
                    if(!strcmp(buffer, "Minotaur")){
                        FILE *nfp = fopen("result.txt", "w");

                        if(nfp)
                        {
                            fputs(paths, nfp);
                            fclose(nfp);
                        }
                    }else{
                        char* nameNextFile = return_Fname(buffer);

                        if (nameNextFile != NULL){
                            find_File(nameNextFile, ".", paths);
                        }
                    }
                }
                fclose(fp);
            } 
        }
        else if(file->d_type == DT_DIR && strcmp(file->d_name, "..") && strcmp(file->d_name, ".")){
            char* new_dir = (char*)malloc(sizeof(char)*(strlen(path)+strlen(file->d_name) + 2));

            sprintf(new_dir, "%s/%s", path, file->d_name);
            find_File(file_name, new_dir, paths);
        }
    }

    if(closedir(file_status) == -1){
        printf("directory don't be close");
        exit(1);
    }
}

int main(){
    char* paths = NULL;
    find_File("file.txt", "./labyrinth", paths);
    return 0;
}
