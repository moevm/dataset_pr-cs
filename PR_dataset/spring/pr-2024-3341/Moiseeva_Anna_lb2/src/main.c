#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char*, char*, int);
MusicalComposition* createMusicalCompositionList(char**, char**, int*, int);
void push(MusicalComposition*, MusicalComposition*);
void removeEl(MusicalComposition*, char*);
int count(MusicalComposition*);
void print_names(MusicalComposition*);

MusicalComposition* createMusicalComposition(char* name, char* autor, int year){
    MusicalComposition* new_composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    new_composition->name = name;
    new_composition->author = autor;
    new_composition->year = year;
    new_composition->next = NULL;
    new_composition->prev = NULL;
    return new_composition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    if (n == 0){
        return NULL;
    }
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* current = head;
    for(int i = 1; i < n; i++){
        MusicalComposition* next_composition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        current->next = next_composition;
        next_composition->prev = current;
        current = next_composition;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    if (head == NULL)
        return;
    MusicalComposition* current = head;
    while(current->next)
        current = current->next;
    current->next = element;
    element->prev = current;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    if (head == NULL)
        return;
    MusicalComposition* current = head;
    while(strcmp(current->name, name_for_remove) != 0)
        current = current->next;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
}

int count(MusicalComposition* head){
    int number_of_elements = 0;
    MusicalComposition* current = head;
    while(current){
        current = current->next;
        number_of_elements++;
    }
    return number_of_elements;
}

void print_names(MusicalComposition* head){
    MusicalComposition* current = head;
    while(current){
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