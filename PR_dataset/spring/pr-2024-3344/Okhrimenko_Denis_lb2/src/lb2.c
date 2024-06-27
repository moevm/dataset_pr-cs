#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Описание структуры MusicalComposition

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year)
{
    MusicalComposition* MusComp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    MusComp->name = name;
    MusComp->author = autor;
    MusComp->year = year;
    return MusComp;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    MusicalComposition* head = NULL;
    MusicalComposition* tail = NULL;
    for(int i = 0; i < n; ++i){
        MusicalComposition* MusComp = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if(NULL == head){
            head = MusComp;
            tail = MusComp;
        } else {
            tail->next=MusComp;
            MusComp->prev=tail;
            tail = MusComp;
        }
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element)
{
    MusicalComposition* pointer = head;
    while(pointer->next != NULL){
        pointer = pointer->next;   
    }
    pointer->next = element;
    element->next = NULL;
    element->prev = pointer;
}

void removeEl(MusicalComposition* head, char* name_for_remove)
{
    MusicalComposition* pointer = head;
    while(strcmp(pointer->name, name_for_remove)){
        pointer = pointer->next;
    }
    pointer->prev->next = pointer->next;
    pointer->next->prev = pointer->prev;
    free(pointer);
}

int count(MusicalComposition* head)
{
    int counter = 0;
    MusicalComposition* pointer = head;
    do counter++; while((pointer=pointer->next) != NULL);
    return counter;
}

void print_names(MusicalComposition* head){
    MusicalComposition* pointer = head;
    do printf("%s\n", pointer->name); while((pointer=pointer->next) != NULL);
}


int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

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