#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>



typedef struct FileInfo{
    char* name;
    char* path;
}fileInfo;

int fileNameComp(const void* f1, const void* f2){
    fileInfo *fip1 = (fileInfo*) f1;
    fileInfo *fip2 = (fileInfo*) f2;
    return strcmp(fip1->name, fip2->name);
}

void freeFileInfoArr(fileInfo* fInfoArray, int len){
	for (int i = 0; i < len; ++i) {
        	free(fInfoArray[i].name);
        	free(fInfoArray[i].path);
    	}
}

int getFilesInfo(fileInfo* fInfoArray, int maxLen, int len, char* path) {
    DIR *dir = opendir(path);
    if (!dir){
        printf("Dir \"%s\" does not exist", path);
        exit(1);
    }
    struct dirent *ent = readdir(dir);
    char entPath[1000];
    while (ent){
        switch (ent->d_type) {
            case DT_DIR:{
                if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
                    sprintf(entPath, "%s/%s", path, ent->d_name);
                    len = getFilesInfo(fInfoArray, maxLen, len, entPath);
                }
                break;
            }
            case DT_REG:{
                if (strstr(ent->d_name, ".txt")){
                    if (len == maxLen){
                        printf("Memory overflow");
                        freeFileInfoArr(fInfoArray, len);
                        exit(1);
                    }
                    sprintf(entPath, "%s/%s", path, ent->d_name);
                    fileInfo info;
                    info.name = malloc((strlen(ent->d_name) + 1) * sizeof(char ));
                    strcpy(info.name, ent->d_name);
                    info.name[strlen(ent->d_name)] = '\0';
                    info.path = malloc((strlen(entPath) + 1) * sizeof(char ));
                    strcpy(info.path, entPath);
                    info.path[strlen(entPath)] = '\0';
                    fInfoArray[len++] = info;
                }
                break;
            }
        }
        ent = readdir(dir);
    }
    closedir(dir);
    return len;
}

char* read_file(char* path){
    FILE *file = fopen(path, "r");
    if (!file){
        printf("File opening error");
        exit(1);
    }
    int maxLen = 100, len = 0;
    char *res = calloc(maxLen, sizeof(char ));
    char inp[1000];
    char sep[] = " \n";
    while (fgets(inp, 1000, file)){
        char *fileName = strstr(inp, ".txt");
        if (fileName) {
            while (fileName >= inp && *fileName != ' ') fileName--;
            if (*fileName == ' ') fileName++;
            len += strlen(fileName) + 1;
            if (len >= maxLen) {
                maxLen += 20;
                char *tmp = realloc(res, maxLen * sizeof(char ));
                if (!tmp){
                    printf("Memory error");
                    free(res);
                    fclose(file);
                    exit(1);
                }
                res = tmp;
            }
            sprintf(res, "%s%s", res, fileName);
        } else if (strstr(inp, "Deadlock")){
            sprintf(res, "%s", "Deadlock");
            break;
        } else if (strstr(inp, "Minotaur")){
            sprintf(res, "%s", "Minotaur");
            break;
        } else {
            printf("File reading error");
            free(res);
            res = NULL;
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
    return res;
}

int path_to_minotaur(char* res, int maxLen, char *startFileName, fileInfo* fIArr, int fILen){
    int isFound = 0;
    fileInfo toSearch = {startFileName};
    fileInfo *info;
    info = bsearch(&toSearch, fIArr, fILen, sizeof(fileInfo), fileNameComp);
    if (info == fIArr + fILen){
        printf("File \"%s\" is not found", startFileName);
        freeFileInfoArr(fIArr, fILen);
        exit(1);
    }
    char* filePath = info->path;
    char* readFromFile = read_file(filePath);
    char tmpRes[maxLen];
    if (strlen(res) + strlen(filePath) > maxLen){
        printf("Not enough memory for result");
        freeFileInfoArr(fIArr,fILen);
        exit(1);
    }
    sprintf(tmpRes, strlen(res) ?"%s\n%s" : "%s%s", res, filePath);
    int maxListLen = 10, len = 0;
    char **fileList = calloc(maxListLen, sizeof(char *));
    char* sep = " \n\r";
    char *token = strtok(readFromFile, sep);
    while(token){
        if (len == maxListLen){
            maxListLen +=2;
            char **tmp = realloc(fileList, maxListLen * sizeof(char ));
            if (!tmp){
                printf("Memory error");
                free(readFromFile);
                free(fileList);
                exit(1);
            }
            fileList = tmp;
        }
        fileList[len++] = token;
        token = strtok(NULL, sep);
    }
   for ( int i = 0; i < len; ++i) {
        if (!strcmp(fileList[i], "Minotaur")){
            isFound = 1;
            strcpy(res, tmpRes);
            break;
        } else if(strstr(fileList[i], ".txt")){
            isFound = path_to_minotaur(tmpRes, maxLen, fileList[i], fIArr, fILen);
            if (isFound){
                strcpy(res, tmpRes);
                break;
            }
        }
    }
    free(readFromFile);
    return isFound;
}

void writeResult(char* str){
    FILE *file = fopen("./result.txt", "w");
    fprintf(file, "%s", str);
    fclose(file);
}

int main() {
    char res[100000] = "";
    fileInfo info[3001];
    int len = getFilesInfo(info, 3001, 0, "./labyrinth");
    qsort(info, len, sizeof(fileInfo), fileNameComp);
    if(!path_to_minotaur(res, 100000, "file.txt", info, len))
        printf("Minotaur not found");
    else
        writeResult(res);
    freeFileInfoArr(info, len);
    return 0;
}