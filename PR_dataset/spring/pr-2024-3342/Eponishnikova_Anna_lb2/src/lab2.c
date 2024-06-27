#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
}MusicalComposition;

MusicalComposition *createMusicalComposition(char* name, char* author, int year){
    MusicalComposition *composition = (MusicalComposition *)malloc(sizeof(MusicalComposition));
    if(composition == NULL){
        printf("Memory error");
        exit(0);
    } 
    composition->name = name;
    composition->author = author;
    composition->year = year;
    composition->next = NULL;
    composition->prev = NULL;
    return composition;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *curr = head;
    MusicalComposition *next;
    for (int i = 1; i < n; i++){
        next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        curr->next = next;
        next->prev = curr;
        curr = next;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *curr = head;
    if(head == NULL){
        return;
    }
    else{
        while(curr->next!=NULL){
          curr = curr->next;
        }
        curr->next = element;
        element->prev =  curr;
    }
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* curr = head;
    while(curr!=NULL){
       if(strcmp(curr->name, name_for_remove) == 0){
           if(curr->next == NULL){
               curr->prev->next = NULL;
           }
           else if(curr->prev == NULL){
               curr->next->prev = NULL;
           }
           else{
               curr->prev->next=curr->next;
               curr->next->prev = curr->prev;
           }
            free(curr);
       }
       curr = curr->next;
    }
}

int count(MusicalComposition* head){
    int count = 0;
    MusicalComposition *curr = head;
    while(curr!= NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

void print_names(MusicalComposition* head){
    MusicalComposition *curr = head;
    while(curr!= NULL){
        printf("%s\n",curr->name);
        curr = curr->next;
    }
}


int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);
    
    if(names == NULL || authors == NULL || years == NULL){
        printf("Memory error");
        exit(0);
    }

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));
        
        if(names[i] == NULL || authors[i] == NULL){
            printf("Memory error");
            exit(0);
        }

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}
