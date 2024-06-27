#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 81

typedef struct MusicalComposition {
    struct MusicalComposition *next;
    char *name;
    char *author;
    int year;
    struct MusicalComposition *prev;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition *newComposition = malloc(sizeof(MusicalComposition));
    newComposition->name = malloc(strlen(name) + 1);
    strcpy(newComposition->name, name);
    newComposition->author = malloc(strlen(author) + 1);
    strcpy(newComposition->author, author);
    newComposition->year = year;
    return newComposition;
}

MusicalComposition* createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    MusicalComposition *comp_list = malloc(sizeof(MusicalComposition) * n);
    comp_list[0].prev = NULL;
    comp_list[0].next = &comp_list[1];
    comp_list[0].name = malloc(strlen(array_names[0]) + 1);
    strcpy(comp_list[0].name, array_names[0]);
    comp_list[0].author = malloc(strlen(array_authors[0]) + 1);
    strcpy(comp_list[0].author, array_authors[0]);
    comp_list[0].year = array_years[0];
    for(int i = 1; i < n; i++) {
        comp_list[i].name = malloc(strlen(array_names[i]) + 1);
        strcpy(comp_list[i].name, array_names[i]);
        comp_list[i].author = malloc(strlen(array_authors[i]) + 1);
        strcpy(comp_list[i].author, array_authors[i]);
        comp_list[i].year = array_years[i];
        comp_list[i].next = &comp_list[i + 1];
        comp_list[i].prev = &comp_list[i - 1];
    }
    comp_list[n - 1].prev = &comp_list[n - 2];
    comp_list[n - 1].next = NULL;
    return comp_list;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition *last_el = head;
    while (last_el->next != NULL) {
        last_el = last_el->next;
    }
    element->prev = last_el;
    last_el->next = element;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* comp = head;
    while (comp != NULL) {
        if (strcmp(comp->name, name_for_remove) == 0) {
            if (comp->prev != NULL) {
                comp->prev->next = comp->next;
            }
            if (comp->next != NULL) {
                comp->next->prev = comp->prev;
            }
            break;
        }
        comp = comp->next;
    }
}

int count(MusicalComposition* head) {
    MusicalComposition *comp = head;
    int counter = 0;
    while (comp != NULL) {
        counter++;
        comp = comp->next;
    }
    return counter;
}

void print_names(MusicalComposition* head) {
    MusicalComposition* comp = head;
    while (comp != NULL) {
        printf("%s\n", comp->name);
        comp = comp->next;
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
