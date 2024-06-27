#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* composition = malloc(sizeof(MusicalComposition));
    composition->name = name;
    composition->author = author;
    composition->year = year;
    return composition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition* arr = malloc(sizeof(MusicalComposition) * n);
    for (int i = 0; i < n; ++i) {
        arr[i].name = array_names[i];
        arr[i].author = array_authors[i];
        arr[i].year = array_years[i];
        if (i != 0)
            arr[i].prev = &arr[i-1];
        if (i != (n-1))
            arr[i].next = &arr[i+1];
    }
    arr[0].prev = NULL;
    arr[n-1].next = NULL;
    return arr;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* composition = head;
    while (composition->next != NULL)
        composition = composition->next;
    composition->next = element;
    element->prev = composition;
    element->next = NULL;
}
void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* composition = head;
    while (strcmp(composition->name, name_for_remove) != 0)
        composition = composition->next;
    if (composition->next != NULL)
        composition->next->prev = composition->prev;
    if (composition->prev != NULL)
        composition->prev->next = composition->next;
}

int count(MusicalComposition* head) {
    MusicalComposition* composition = head;
    int count = 0;
    while (composition != NULL) {
        ++count;
        composition = composition->next;
    }
    return count;
}
void print_names(MusicalComposition* head) {
    MusicalComposition* composition = head;
    while (composition != NULL) {
        printf("%s\n", composition->name);
        composition = composition->next;
    }
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = malloc(sizeof(char*)*length);
    char** authors = malloc(sizeof(char*)*length);
    int* years = malloc(sizeof(int)*length);

    for (int i = 0; i < length; ++i) {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n")) = 0;
        (*strstr(author,"\n")) = 0;

        names[i] = malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = malloc(sizeof(char*) * (strlen(author)+1));

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
    (*strstr(name_for_push,"\n")) = 0;
    (*strstr(author_for_push,"\n")) = 0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n")) = 0;

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

    for (int i = 0; i < length; ++i){
        free(names[i]);
        free(authors[i]);
    }

    free(names);
    free(authors);
    free(years);

    return 0;
}