#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* NewMusicalComposition = malloc(sizeof(struct MusicalComposition));
    NewMusicalComposition->name = name;
    NewMusicalComposition->author = author;
    NewMusicalComposition->year = year;
    NewMusicalComposition->prev = NULL;
    NewMusicalComposition->next = NULL;
    return NewMusicalComposition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head;
    MusicalComposition* current;
    MusicalComposition* beforeCurrent;
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    beforeCurrent = head;
    for (int i = 1; i <= n-1; i++){
        current = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        beforeCurrent->next = current;
        current->prev = beforeCurrent;
        beforeCurrent = current;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* current;
    current = head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = element;
    element->prev = current;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* current;
    current = head;
    while (strcmp(current->name, name_for_remove)){
        current = current->next;
    }
    if (current->prev != NULL)
        current->prev->next = current->next;
    if (current->next != NULL)
        current->next->prev = current->prev;
}

int count(MusicalComposition* head){
    int counter;
    if (head == NULL){
        counter = 0;
    }
    else{
        counter = 1;
    }
    MusicalComposition* current;
    current = head;
    while (current->next != NULL){
        current = current->next;
        counter+=1;
    }
    return counter;
}

void print_names(MusicalComposition* head){
    MusicalComposition* current;
    current = head;
    while (current != NULL){
        printf("%s\n", current->name); 
        current = current->next;
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
