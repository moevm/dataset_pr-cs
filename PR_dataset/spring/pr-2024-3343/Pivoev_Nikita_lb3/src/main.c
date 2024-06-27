#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
 
void findDir(FILE* file, char letter, char* dirName) {
    DIR* dir = opendir(dirName);
    if (dir) {
        struct dirent* de = readdir(dir);
        while (de) {
            if (strstr(de->d_name,".txt") != NULL && de->d_name[0] == letter && de->d_name[1] == '.') {
                fprintf(file, "%s/%s\n", dirName, de->d_name);
                printf("%s/%s\n", dirName, de->d_name);
            }
 
            else if (strstr(de->d_name,".txt") == NULL && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                char* newDir = malloc(strlen(dirName)+strlen(de->d_name)+2);
                sprintf(newDir, "%s/%s", dirName, de->d_name);
                findDir(file, letter, newDir);
                free(newDir);    
            }
            de = readdir(dir);
        }
        closedir(dir);
    }
}
 
int main() {
    char str[1000];
    scanf("%s", str);
    FILE* file = fopen("result.txt","w");
 
    for (int i = 0; i < strlen(str); ++i)
        findDir(file, str[i], "./tmp");
 
    fclose(file);
    return 0;
} 