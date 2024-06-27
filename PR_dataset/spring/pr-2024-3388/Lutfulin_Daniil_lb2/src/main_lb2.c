#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);
void push(MusicalComposition* head, MusicalComposition* element);
void removeEl(MusicalComposition** head, char* name_for_remove);
int count(MusicalComposition* head);
void print_names(MusicalComposition* head);
void freeMusicalCompositionList(MusicalComposition* head);

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* new_composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    new_composition->name = name;
    new_composition->author = author;
    new_composition->year = year;
    new_composition->next = NULL;
    new_composition->prev = NULL;
    return new_composition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){

    MusicalComposition *head = createMusicalComposition( array_names[0],array_authors[0],array_years[0]);
    MusicalComposition *previous_composition = head;

    for(int i = 1; i<n;i++){
        MusicalComposition *current_composition = createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
        current_composition->prev = previous_composition;
        previous_composition->next = current_composition;
        previous_composition= current_composition;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *current_composition = head;
    while(current_composition->next!=NULL)
        current_composition = current_composition->next;
    current_composition->next = element;
    element->prev = current_composition;
}

void removeEl(MusicalComposition** head, char* name_for_remove){
    MusicalComposition *current_composition = *head;
    size_t is_name_to_remove = 1;
    do{
        is_name_to_remove = strcmp(current_composition->name, name_for_remove);
        if (is_name_to_remove == 0)
            break;
        current_composition = current_composition->next;
    }while(current_composition->next!=NULL);
    is_name_to_remove = strcmp(current_composition->name, name_for_remove);\

    if(is_name_to_remove == 0){

        if(current_composition == *head){
            *head = (*head)->next;
            free((*head)->prev);
            (*head)->prev = NULL;
            current_composition = *head;
        }
        else if (current_composition->next==NULL){
            current_composition->prev->next = NULL;
            free(current_composition);
        }else{
            current_composition->prev->next = current_composition->next;
            current_composition->next->prev = current_composition->prev;
            free(current_composition);
        }
    }
}

int count(MusicalComposition*  head){
    MusicalComposition *current_composition = head;
    int counter = 1;
    while(current_composition->next!=NULL){
        counter++;
        current_composition= current_composition->next;
    }
    return counter;
}
void print_names(MusicalComposition*  head){
    MusicalComposition *current_composition = head;
    printf("%s\n", head->name);
    while(current_composition->next != NULL){
        current_composition = current_composition->next;
        printf("%s\n", current_composition->name);
    }
}

void freeMusicalCompositionList(MusicalComposition* head){
    while(head->next != NULL){
        head = head->next;
        free(head->prev);
    }
    free(head);
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

    removeEl(&head, name_for_remove); 
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
    freeMusicalCompositionList(head);
    return 0;
}