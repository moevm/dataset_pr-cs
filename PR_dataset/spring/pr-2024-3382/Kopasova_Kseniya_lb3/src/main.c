#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

typedef struct FileInfo{
    char* text;
    struct FileInfo* next;
}FileInfo;

FileInfo* pathcat(char* txt){
    FileInfo* temp = malloc(sizeof(FileInfo));
    temp->text = malloc(sizeof(char)*(strlen(txt)+1));
    strcpy(temp->text, txt);
    temp->next = NULL;
    return temp;
}

void add_FileInfo(FileInfo** head, char* txt){
    FileInfo* temp = pathcat(txt);
    if(!*head){
        temp->next = *head;
        *head = temp;
    }else if(atoi(temp->text) < atoi((*head)->text)){
        temp->next = *head;
        *head = temp;
    }else{
        FileInfo* cur = *head;
        while(cur->next){
            if(atoi(cur->next->text) > atoi(temp->text)){
                break;
            }else {
                cur = cur->next;
            }
        }
        FileInfo* t = cur->next;
        cur->next = temp;
        temp->next = t;
    }
}

void dir_func(const char* dir_name, FileInfo** head) {
    DIR* dir = opendir(dir_name);
    struct dirent* de;
    FILE* fp;
    while (de = readdir(dir)) {
        if (de->d_type == 8 && strstr(de->d_name, ".txt")) {

            char arr[128];
            strcpy(arr, dir_name);
            strcat(arr, "/");
            strcat(arr, de->d_name);
            fp = fopen(arr, "r");

            char* ans = calloc(100, sizeof(char));
            fgets(ans, 99, fp);
            ans[strlen(ans)] = '\0';
            add_FileInfo(head, ans);
            free(ans);

            fclose(fp);
        }
        if (de->d_type == 4 && strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
            char* arr = calloc(120, sizeof(char));
            strcpy(arr, dir_name);
            strcat(arr, "/");
            strcat(arr, de->d_name);
            dir_func(arr, head);
            free(arr);
        }
    }
    closedir(dir);
}


void print_FileInfo(FileInfo* head){
    FileInfo* cur = head;
    while(cur){
        printf("%s\n", cur->text);
        cur = cur->next;
    }
}

void free_FileInfo(FileInfo* head) {
    FileInfo* temp;
    while (head) {
        temp = head->next;
        free(head->text);
        free(head);
        head = temp;
    }
}


int main() {
    char dir_name[5] = ".";
    FileInfo* head = NULL;

    dir_func(dir_name, &head);
    FILE* result = fopen("result.txt", "w");
    FileInfo* cur = head;
    while(cur){
        fprintf(result, "%s\n", cur->text);
        cur = cur->next;
    }

    free_FileInfo(head);
    return 0;
};