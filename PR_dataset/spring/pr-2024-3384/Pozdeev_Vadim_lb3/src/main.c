#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

char * find_path(char * dirPath, const char * cmpPath)
{
    if(strstr(dirPath, cmpPath)!= NULL){
        return dirPath;
    }
    DIR *dir = opendir(dirPath);
    if(dir) {
        struct dirent *de = readdir(dir);
        while (de) {
            if(strcmp(".", de->d_name) && strcmp("..", de->d_name)){
                char * new_dirPath = (char *)malloc(100);
                strcpy(new_dirPath, dirPath);
                strcat(new_dirPath, "/");
                strcat(new_dirPath, de->d_name);
                char * result = find_path(new_dirPath, cmpPath);
                if(result != NULL) {
                    closedir(dir);
                    return result;
                }
            }
            de = readdir(dir);
        }
        closedir(dir);
    }
    return NULL;
}
void write(char ** files, int k){
    FILE *fw = fopen("result.txt", "at");
    for(int i =0; i!=k; i++){
        fputs(files[i], fw);
    }
    fclose(fw);
}

char ** find_file(char path[100], char * file_name, char ** paths_to_files, int * k){
    char * path_to_file = find_path(path, file_name);
    FILE *fr = fopen(path_to_file, "r");
    strcat(path_to_file, "\n");
    char result[100];
    char * pattern = "([!-~]+\\.txt)";
    regex_t re;
    regcomp(&re, pattern, REG_EXTENDED);
    int f = 0;
    while(!feof(fr)){
        fgets(result, 100, fr);
        regmatch_t pmatch[1];
        if (regexec(&re, result, 1, pmatch, 0) == 0){
            if (f == 0){
                free(paths_to_files[*k]);
                paths_to_files[*k] = path_to_file;
                (*k)++;
            }
            f++;
            
            char new_file[10];
            int j = 0;
            for(int i = pmatch[0].rm_so; i!= pmatch[0].rm_eo; i++){
                new_file[j++] = result[i];
            
            }
            new_file[j] = '\0';
            char ** new_paths_to_files = find_file(path, new_file, paths_to_files, k);
            if(new_paths_to_files != NULL) {
                    return new_paths_to_files;
                }
        }
        }
    if(!(strcmp(result, "Minotaur"))){
        paths_to_files[*k] = path_to_file;
        (*k)++;
        fclose(fr);
        return paths_to_files;
        }
    fclose(fr);
    return NULL;
}
int main(){
    char path[100] = "./labyrinth";
    int k = 0;
    char ** paths_to_files = malloc(sizeof(char * ) * 100);
    find_file(path, "file.txt", paths_to_files, &k);
    write(paths_to_files, k);
}
