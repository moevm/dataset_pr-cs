#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* composition = malloc(sizeof(MusicalComposition));
    composition->name = name;
    composition->author = author;
    composition->year = year;
    composition->next = NULL;
    return composition;
};

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = malloc(sizeof(MusicalComposition));
    MusicalComposition* tmp = malloc(sizeof(MusicalComposition));
    head->name = array_names[0];
    head->author = array_authors[0];
    head->year = array_years[0];
    head->next = tmp;

    tmp->name = array_names[1];
    tmp->author = array_authors[1];
    tmp->year = array_years[1];
    tmp->next = NULL;

    for (int i = 2; i < n; i++){
        tmp->next = malloc(sizeof(MusicalComposition));
        tmp->next->name = array_names[i];
        tmp->next->author = array_authors[i];
        tmp->next->year = array_years[i];
        tmp->next->next = NULL;
        tmp = tmp->next;
    }
    return head;
};

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* current = head;
    while (current->next != NULL){
        current = current->next;
    };
    current->next = element;
};

void removeEl(MusicalComposition* head, char* name_for_remove) {
    if (head == NULL) return;

    MusicalComposition* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->name, name_for_remove) == 0) {
            //MusicalComposition* temp = current->next;
            current->next = current->next->next;
            //free(temp);
        } else {
            current = current->next;
        }
    }
}

int count(MusicalComposition* head){
    MusicalComposition* current = head;
    int k = 0;
    while (current->next != NULL){
        k++;
        current = current->next;
    }
    return k+1;
};

void print_names(MusicalComposition* head){
    MusicalComposition* current = head;
    while (current != NULL) {
        puts(current->name);
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
