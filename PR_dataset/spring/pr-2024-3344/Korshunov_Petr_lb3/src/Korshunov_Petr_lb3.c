#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int counter(FILE *fp, char* operation){     
    if(fp == NULL) {
        return -1;
    }
    if(strcmp(operation, "add")==0){

        int overall = 0;
        int c;
        while(fscanf(fp, "%d ", &c) == 1)
            overall += c;
        return overall;
    }else{
        int overall = 1;
        int c;
        while(fscanf(fp, "%d ", &c) == 1)
            overall *= c;
        return overall;
    }
}


int listdir(const char *name, char *last_dir)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        exit(-1);

    int c;   
    if(strcmp(last_dir, "add")==0){
        c = 0;
    }else if (strcmp(last_dir, "mul")==0)
    {
        c = 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            char* path = malloc(strlen(name) + strlen(entry->d_name) + 2);
            snprintf(path, strlen(name) + strlen(entry->d_name) + 2, "%s/%s", name, entry->d_name);
            int count = listdir(path, entry->d_name);
            if(strcmp(last_dir, "add")==0){
                c += count;
            }else if (strcmp(last_dir, "mul")==0)
            {
                c *= count;
            }
            else{
                return count;
            }
            
        } else {
            char* temp = malloc(strlen(name) + strlen(entry->d_name) + 2);
            snprintf(temp, strlen(name) + strlen(entry->d_name) + 2, "%s/%s", name, entry->d_name);
            FILE* fp = fopen(temp, "r");
            int count = counter(fp, last_dir);
            fclose(fp);
            if(strcmp(last_dir, "add")==0){
                c += count;
            }else if (strcmp(last_dir, "mul")==0)
            {
                c *= count;
            }
        }
    }
    closedir(dir);
    return c;
}

int main(void) {
    int overall = 0;
    overall = listdir("./tmp", ".");
    FILE* fp = fopen("result.txt", "w");
    if(fp == NULL) {
        return 1;
    }
    fprintf(fp, "%d", overall);
    fclose(fp);
    return 0;
}
