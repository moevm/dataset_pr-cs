#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void findFiles(const char *basePath, char searchCh, FILE* res) {
    DIR *dir;
    struct dirent *de;

    if ((dir = opendir(basePath)) == NULL) {
        return;
    }

    while ((de = readdir(dir)) != NULL) {
        if (de->d_type == DT_DIR) {
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                char path[1024];
                sprintf(path, "%s/%s", basePath, de->d_name);
                findFiles(path, searchCh, res);
            }
        } else {
            if (de->d_name[0] == searchCh && strlen(de->d_name) == 5 && strstr(de->d_name, ".txt")) {
                fprintf(res, "%s/%s\n", basePath, de->d_name);
            }
        }
    }

    closedir(dir);
}

int main() {
    char filename[256];
    fgets(filename, 256, stdin);
    FILE* res = fopen("result.txt", "w");
    
    const char* rootDir = "./tmp";
    for(int i = 0; i < strlen(filename); i++){
        findFiles(rootDir, filename[i], res);
    }
    fclose(res);

    return 0;
}