#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char name[80];
    char author[80];
    int year;
    
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    strcpy(tmp->name, name);
    strcpy(tmp->author, autor);
    tmp->year = year;
    return tmp;
};

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    head->next = tmp;
    head->prev = NULL;
    tmp->prev = head;
    for (int i = 2; i < n; i++){
        tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    return head;
};

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = element;
    element->prev = tmp;
    return;
};

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* tmp = head;
    while (tmp->next != NULL && strcmp(tmp->next->name, name_for_remove))
        tmp = tmp->next;
    if (tmp->next == NULL) return;
    tmp->next = tmp->next->next;
    tmp->next->prev = tmp;
};

int count(MusicalComposition* head){
    MusicalComposition* tmp = head;
    int n = 1;
    while (tmp->next != NULL){
        tmp = tmp->next;
        n++;
    }
    return n;
};

void print_names(MusicalComposition* head){
    MusicalComposition* tmp = head;
    while (tmp != NULL){
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
    return;
};


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