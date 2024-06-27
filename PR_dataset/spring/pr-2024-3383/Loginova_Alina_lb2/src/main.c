#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Описание структуры MusicalComposition

typedef struct musical_composition {
    char *name, *author;
    unsigned long year;
    struct musical_composition *next, *prev;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year);

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);

void push(MusicalComposition* head, MusicalComposition* element);

void removeEl(MusicalComposition* head, char* name_for_remove);

int count(MusicalComposition* head);

void print_names(MusicalComposition*  head);

void remove_first(MusicalComposition *current);

void remove_last(MusicalComposition *current);

MusicalComposition* find_el_by_name(MusicalComposition *head, char *name);

void print_error(char *func_name, char *msg);

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition *musicalComposition = malloc(sizeof(MusicalComposition));
    if(!musicalComposition) {
        print_error("createMusicalComposition", "memory allocation");
        exit(errno);
    }
    musicalComposition->name = name;
    musicalComposition->author = author;
    musicalComposition->year = year;
    musicalComposition->next = NULL;
    musicalComposition->prev = NULL;
    return musicalComposition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition *head    = createMusicalComposition(array_names[0], array_authors[0], array_years[0]),
                       *current = head;
    for (int i = 1; i < n; i++)
        push(current, createMusicalComposition(array_names[i], array_authors[i], array_years[i]));
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    if (!head)
        return print_error("push", "head is invalid");
    if (!element)
        return print_error("push", "element for push is invalid");

    for (; head->next; head = head->next);
    head->next = element;
    element->prev = head;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    if(!head)
        return print_error("removeEl", "head is invalid");
    if(!name_for_remove)
        return print_error("removeEl", "name for remove is invalid");

    MusicalComposition *el_to_remove = find_el_by_name(head, name_for_remove);

    if(!el_to_remove)
        return;
    if (!el_to_remove->prev)
        return remove_first(el_to_remove);
    if (!head->next)
        return remove_last(el_to_remove);

    el_to_remove->prev->next = el_to_remove->next;
    el_to_remove->next->prev = el_to_remove->prev;

    free(el_to_remove);
}

int count(MusicalComposition* head) {
    int count = 0;
    for(; head; head = head->next, count++);
    return count;
}

void print_names(MusicalComposition*  head) {
    static int need_lf = 0;
    for(; head; head = head->next) {
        if (need_lf)
            printf("\n");
        else
            ++need_lf;
        printf("%s", head->name);
    }
}

void remove_first(MusicalComposition *current) {
    current->name = current->next->name;
    current->author = current->next->author;
    current->year = current->next->year;
    current->next = current->next->next;

    free(current->next->prev);
    current->next->prev = current;
}

void remove_last(MusicalComposition *current) {
    current->prev->next = current->next;
    free(current);
}

MusicalComposition* find_el_by_name(MusicalComposition *head, char *name) {
    for(; head && name; head = head->next)
        if(strcmp(head->name, name) == 0)
            return head;
    return NULL;
}

void print_error(char *func_name, char *msg) {
    if(func_name && msg)
        printf("[%s()] error: %s\n", func_name, msg);
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