#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


// Описание структуры createMusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author, int year){
    MusicalComposition* composition = malloc(sizeof(MusicalComposition));
    composition->name = name;
    composition->author = author;
    composition->year = year;
    composition->next = NULL;
    composition->prev = NULL;
    return composition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* first = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    first->next = tmp;
    tmp->prev = first;
    for (int i = 2; i < n; i++){
        tmp->next = malloc(sizeof(MusicalComposition));
        tmp->next->name = array_names[i];
        tmp->next->author = array_authors[i];
        tmp->next->year = array_years[i];
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    return first;
}

void push(MusicalComposition* head, MusicalComposition* element){
    int flag = 0;
    do {
        if (head->next == NULL){
            flag = 1;
            head->next = element;
            element->prev = head;
        } else {
            head = head->next;
        }
    } while (flag != 1);
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    int check = 0;
    MusicalComposition* tmp = head->next;
    if (strcmp(head->name, name_for_remove) == 0){
        tmp->prev = NULL;
        free(head);
    } else {
        do {
            if (strcmp(tmp->name, name_for_remove) == 0){
                check = 1;
                head->next = tmp->next;
                tmp->next->prev = head;
                free(tmp);
            } else {
                head = tmp;
                tmp = tmp->next;
            }
        } while (check != 1);
    }
}

int count(MusicalComposition* head){
    int counter = 0;
    while (head->next != NULL){
        counter++;
        head = head->next;
    }
    counter++;
    return counter;
}

void print_names(MusicalComposition* head){
    do {
        printf("%s\n", head->name);
        head = head->next;
    } while (head->next != NULL);
    printf("%s\n", head->name);
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
