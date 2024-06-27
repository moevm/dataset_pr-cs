#include <stdio.h> 
#include <dirent.h> 
#include <stdlib.h> 
#include <string.h> 
 
typedef struct Node{ 
    char* text; 
    struct Node* next; 
}Node; 
 
Node* cr_Node(char* txt){ 
    Node* tmp = malloc(sizeof(Node)); 
    tmp->text = malloc(sizeof(char)*(strlen(txt)+1)); 
    strcpy(tmp->text, txt); 
    tmp->next = NULL; 
    return tmp; 
} 
 
void add_Node(Node** head, char* txt){ 
    Node* tmp = cr_Node(txt); 
    if(!*head){ 
        tmp->next = *head; 
        *head = tmp; 
    }else if(atoi(tmp->text) < atoi((*head)->text)){ 
        tmp->next = *head; 
        *head = tmp; 
    }else{ 
        Node* cur = *head; 
        while(cur->next){ 
            if(atoi(cur->next->text) > atoi(tmp->text)){ 
                break; 
            }else { 
                cur = cur->next; 
            } 
        } 
        Node* t = cur->next; 
        cur->next = tmp; 
        tmp->next = t; 
    } 
} 
 
void dir_func(const char* dir_name, Node** head){ 
    DIR* dir = opendir(dir_name); 
    struct dirent* de; 
    FILE* fp; 
    while(de = readdir(dir)){ 
        if(de->d_type == 8 && strstr(de->d_name, ".txt")){ 
 
            char str[120]; 
            strcpy(str, dir_name); 
            strcat(str, "/"); 
            strcat(str, de->d_name); 
            fp = fopen(str, "r"); 
 
            char* ans = calloc(100, sizeof(char)); 
            fgets(ans, 99, fp); 
            ans[strlen(ans)] = '\0'; 
            add_Node(head, ans); 
            free(ans); 
 
            fclose(fp); 
        } 
        if(de->d_type == 4 && strcmp(de->d_name, ".") && strcmp(de->d_name, "..")){ 
            char* str = calloc(120, sizeof(char)); 
            strcpy(str, dir_name); 
            strcat(str, "/"); 
            strcat(str, de->d_name); 
            dir_func(str, head); 
            free(str); 
        } 
    } 
    closedir(dir); 
} 
 
void free_Node(Node* head){ 
    Node* tmp; 
    while(head){ 
        tmp = head->next; 
        free(head->text); 
        free(head); 
        head = tmp; 
    } 
} 
 
int main() { 
    char dir_name[5] = "."; 
    Node* head = NULL; 
 
    dir_func(dir_name, &head); 
    FILE* result = fopen("result.txt", "w"); 
    Node* cur = head; 
    while(cur){ 
        fprintf(result, "%s\n", cur->text); 
        cur = cur->next; 
    } 
 
    free_Node(head); 
    return 0; 
}