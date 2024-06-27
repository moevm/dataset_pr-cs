#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_PATH 256
#define MAX_FILENAME 128


int dirValidator(char* dirname){
    int res;

    if(strcmp(dirname, ".") && strcmp(dirname, "..")){
        res = 1;
    }else{
        res = 0;
    }

    return res;
}

void dirLookup(char* root,char* findWord,char** outputPaths)
{
    char tmpDir[MAX_PATH];
    strncpy(tmpDir, root, MAX_FILENAME);

    DIR* rootDir = opendir(tmpDir);
    if(rootDir == NULL){
        return;
    }

    struct dirent* dir = readdir(rootDir);

    while(dir){
        if(dir->d_type == DT_REG){
            if(strlen(dir->d_name) > MAX_FILENAME){
                perror("FileName size error");
                exit(0);
            }

            strncat(tmpDir, "/", strlen(tmpDir)+1);
            strncat(tmpDir, dir->d_name, strlen(dir->d_name));

            //readFile(tmpDir);
            regex_t regex;
            regmatch_t groups[4];
            char* pattern = "^.\\.txt";
            regcomp(&regex, pattern, REG_EXTENDED);
            if(regexec(&regex,dir->d_name,4,groups,0)==0)
            {

                for (int i = 0; i < strlen(findWord); ++i)
                {
                    if(strncmp(&findWord[i], &dir->d_name[0],1) == 0)
                    {
                        strncat(outputPaths[i],tmpDir,MAX_PATH);
                        break;
                    }
                }
            }

            tmpDir[strlen(tmpDir) - 1 - strlen(dir->d_name)] = '\0';

        }else if(dir->d_type == DT_DIR && dirValidator(dir->d_name)){
            if(strlen(dir->d_name) > MAX_FILENAME){
                perror("FileName size error");
                exit(0);
            }

            strncat(tmpDir, "/", strlen(tmpDir)+1);
            strncat(tmpDir, dir->d_name, strlen(dir->d_name));


            dirLookup(tmpDir,findWord,outputPaths);
            tmpDir[strlen(tmpDir) - 1 - strlen(dir->d_name)] = '\0';
        }
        dir = readdir(rootDir);
    }
    closedir(rootDir);
}

int main()
{
    char* findWord = (char*)malloc(1000 * sizeof(char));
    if (findWord == NULL)
    {
        exit(1);
    }
    scanf("%s",findWord);



    char** outputPaths = (char **)malloc(strlen(findWord)*sizeof(char*));
    if (outputPaths == NULL)
    {
        exit(1);
    }
    for (int i = 0; i < strlen(findWord); ++i) {
        outputPaths[i] = malloc(MAX_FILENAME*sizeof(char));
        if (outputPaths[i] == NULL)
    {
        exit(1);
    }
    }

    FILE* file = fopen("result.txt","w");



    dirLookup("./tmp",findWord,outputPaths);

    if(file)
    {
        for (int i = 0; i < strlen(findWord); ++i)
        {
            fprintf(file,"%s\n",outputPaths[i]);
        }
        fclose(file);
    }

    for (int i = 0; i < strlen(findWord); ++i) {
        free(outputPaths[i]);
    }
    free(outputPaths);
    free(findWord);
    return 0;
}