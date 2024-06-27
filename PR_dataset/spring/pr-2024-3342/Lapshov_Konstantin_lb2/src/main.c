#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;


void memoryError(){
    printf("Memory allocation error!");
    exit(0);
}

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* newComp = malloc(sizeof(MusicalComposition));
    if(newComp == NULL){
        memoryError();
    }

    newComp->name = name;
    newComp->author = autor;
    newComp->year = year;
    newComp->next = NULL;
    newComp->prev = NULL;

    return newComp;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* tmp = head;

    for (int i = 1; i < n; i++) {
        MusicalComposition* new_composition = createMusicalComposition(array_names[i], array_authors[i],array_years[i]);

        tmp->next = (struct MusicalComposition* ) new_composition;
        new_composition->prev = (struct MusicalComposition* ) tmp;

        tmp = (MusicalComposition *) new_composition;
    }

    return head;
}

int count(MusicalComposition* head){
    MusicalComposition* tmp = head;
    int result = 0;

    while(tmp != NULL){
        tmp = (MusicalComposition *) tmp->next;
        result++;
    }

    return result;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* tmp = head;
    while(tmp->next != NULL){
        tmp = (MusicalComposition *) tmp->next;
    }

    tmp->next = (struct MusicalComposition *) element;
    element->prev = (struct MusicalComposition *) tmp;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* tmp = head;
    while(tmp != NULL){
        if(strcmp(tmp->name, name_for_remove) == 0){
           if(tmp == head){
               head = (MusicalComposition *) tmp->next;
           }else{
               MusicalComposition* prev = (MusicalComposition *) tmp->prev;
               MusicalComposition* next = (MusicalComposition *) tmp->next;

               next->prev = (struct MusicalComposition *)prev;
               prev->next = (struct MusicalComposition *)next;
           }
            free(tmp);
            break;
        }else{
            tmp = (MusicalComposition *) tmp->next;
        }
    }
}


void print_names(MusicalComposition* head){
    MusicalComposition* tmp = head;

    while (tmp != NULL){
        printf("%s\n", tmp->name);
        tmp = (MusicalComposition *) tmp->next;
    }
}


int main(){
    int length;
    scanf("%d\n", &length);

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    if(names == NULL || authors == NULL || years == NULL){
        memoryError();
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
            memoryError();
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