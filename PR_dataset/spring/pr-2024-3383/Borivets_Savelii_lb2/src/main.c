#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Описание структуры MusicalComposition

typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year) {
    MusicalComposition* muscomp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    muscomp->name = name;
    muscomp->author = author;
    muscomp->year = year;
    muscomp->prev = NULL;
    muscomp->next = NULL;
    return muscomp;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    if (n == 1) return head;
    MusicalComposition* currentmc =  createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    head->next = currentmc;
    currentmc->prev = head;
    for (int i = 2; i < n; i++) {
        currentmc->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        currentmc->next->prev = currentmc;
        currentmc->next->next = NULL;
        currentmc = currentmc->next;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* currentmc = head;
    while (currentmc != NULL) {
        if (currentmc->next != NULL)
            currentmc = currentmc->next;
        else {
            break;
        }
    }
    currentmc->next = element;
    element->prev = currentmc;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* currentmc = head;
    int flag = 0;
    while (currentmc != NULL) {
        if (strcmp(currentmc->name, name_for_remove) == 0) {
            flag = 1;
            break;
        }
        currentmc = currentmc->next;
    }
    if (flag) {
        MusicalComposition* left = currentmc->prev;
        MusicalComposition* right = currentmc->next;
        if (left == NULL && right == NULL) {
            currentmc->prev = NULL;
            currentmc->next = NULL;
        } else if (left == NULL) {
            *head = *right;
            right->prev = NULL;
        } else if (right == NULL) {
            left->next = NULL;
        } else {
            left->next = right;
            right->prev = left;
        }
    }
}

int count(MusicalComposition* head){
    MusicalComposition* currentmc = head;
    int count = 0;
    while (currentmc != NULL) {
        count++;
        currentmc = currentmc->next;
    }
    return count;
}

void print_names(MusicalComposition* head) {
    MusicalComposition* currentmc = head;
    while (currentmc != NULL) {
        printf("%s\n", currentmc->name);
        currentmc = currentmc->next;
    }
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