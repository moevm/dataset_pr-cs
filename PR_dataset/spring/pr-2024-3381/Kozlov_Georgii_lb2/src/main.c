#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
};
typedef struct MusicalComposition MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor, int year){
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    tmp->name = name;
    tmp->author = autor;
    tmp->year = year;
    tmp->next = NULL;
    return tmp;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head;
    MusicalComposition* tmp;
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head->next = NULL;
    if (n > 1){
        tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
        head->next = tmp;
    }
    for(int i = 2; i < n; i++){
        tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmp = tmp->next;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* tmp = head;
    while (tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = createMusicalComposition(element->name, element->author, element->year);
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    while (strcmp(head->name, name_for_remove) == 0 && head->next != NULL){
        head = head->next;
    }
    MusicalComposition* last_tmp = head;
    MusicalComposition* tmp = head->next;
    while (tmp != NULL){
        if (strcmp(tmp->name, name_for_remove) == 0){
            last_tmp->next = tmp->next;
            free(tmp);
        }
        else{
            last_tmp = tmp;
        }
        tmp = tmp->next;
    }
}

int count(MusicalComposition* head){
    MusicalComposition* tmp = head;
    int n = 1;
    while (tmp->next != NULL){
        n+=1;
        tmp = tmp->next;
    }
    return n;
}

void print_names(MusicalComposition* head){
    MusicalComposition* tmp = head;
    while (tmp != NULL){
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++){
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
