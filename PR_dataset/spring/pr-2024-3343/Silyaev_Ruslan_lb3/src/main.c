#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
 
void dirRec(FILE* file, char ch, char* dirName){
    DIR* direct = opendir(dirName);
    if (direct) {
        struct dirent* den = readdir(direct);
        while(den){
            if(strstr(den->d_name,".txt") != NULL && den->d_name[0] == ch && den->d_name[1] == '.'){
                fprintf(file, "%s/%s\n", dirName, den->d_name);
                printf("%s/%s\n", dirName, den->d_name);
            }
            else if(strstr(den->d_name,".txt") == NULL && strcmp(den->d_name, ".") != 0 && strcmp(den->d_name, "..") != 0){
                char* newDir = malloc(strlen(dirName)+strlen(den->d_name)+2);
                sprintf(newDir, "%s/%s", dirName, den->d_name);
                dirRec(file, ch, newDir);
                free(newDir);    
            }
            den = readdir(direct);
        }
        closedir(direct);
    }
}
 
int main() {
    char name[1000];
    scanf("%s", name);
    FILE* file = fopen("result.txt","w");
    for(int i = 0; i < strlen(name); ++i){
        dirRec(file, name[i], "./tmp");
    }
    fclose(file);
    return 0;
} 
