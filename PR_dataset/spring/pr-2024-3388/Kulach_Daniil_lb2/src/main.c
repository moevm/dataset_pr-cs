#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* autor,int year);

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);

void push(MusicalComposition* head, MusicalComposition* element);

void removeEl(MusicalComposition* head, char* name_for_remove);

int count(MusicalComposition* head);

void print_names(MusicalComposition* head);


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

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* new_el = malloc(sizeof(MusicalComposition));
    new_el->name = name;
    new_el->author = autor;
    new_el->year = year;
    new_el->prev = NULL;
    new_el->next = NULL;
    return new_el;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* list_head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for(int i = 1; i < n; i++){
        MusicalComposition* new_el = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(list_head, new_el);
    }
    return list_head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    while(head->next){
        head = head->next;
    }
    element->prev = head;
    head->next = element;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* previous = NULL;
    while (head){
        if (strcmp(head->name, name_for_remove) == 0){
            if (previous == NULL) {
                head->next->prev = NULL;
                free(head);
            } else {
                previous->next = head->next;
                free(head);
            }
            break;
        }
        previous = head;
        head = head->next;
    }
}

int count(MusicalComposition* head){
    int el_count = 0;
    while(head){
        el_count++;
        head = head->next;
    }
    return el_count;
}

void print_names(MusicalComposition* head){
    while (head){
        printf("%s\n", head->name);
        head = head->next;
    }
}
