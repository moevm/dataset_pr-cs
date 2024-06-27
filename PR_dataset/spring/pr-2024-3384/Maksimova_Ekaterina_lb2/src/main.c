#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year) {
    MusicalComposition *cur = (MusicalComposition *) malloc(sizeof(MusicalComposition));
    cur->name = name;
    cur->author = author;
    cur->year = year;
    cur->next = NULL;
    cur->prev = NULL;
    return cur;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition *cur = createMusicalComposition(*array_names, *array_authors, *array_years);
    MusicalComposition *head = cur;
    for (int i = 1; i < n; i++) {
        cur->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        cur->next->prev = cur;
        cur = cur->next;
    }
    return head;
}


void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition *cur= head;
    while (cur->next != NULL) 
        cur = cur->next;
    cur->next = element;
    cur->next->prev = cur;
    element->next = NULL;
}


void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition *cur= head;
    while (cur != NULL && strcmp(cur->name, name_for_remove) != 0)
        cur = cur->next;
    if (cur->prev != NULL)
        cur->prev->next = cur->next;
    if (cur->next != NULL)
        cur->next->prev = cur->prev;
    free(cur);
}

int count(MusicalComposition* head) {
    MusicalComposition* cur = head;
    int counter = 1;
    while (cur->next!=NULL) {
        counter++;
        cur = cur->next;
    }
    return counter;
}

void print_names(MusicalComposition* head ){
    MusicalComposition* cur = head;
    while (cur != NULL) {
        printf("%s\n", cur->name);
        cur = cur->next;
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
