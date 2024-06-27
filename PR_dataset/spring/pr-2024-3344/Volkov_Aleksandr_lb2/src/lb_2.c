#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition

typedef struct MusicalComposition
{
    char *name;
    char *author;
    unsigned int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year)
{
    MusicalComposition *ptr = (MusicalComposition *)malloc(sizeof(MusicalComposition));
    ptr->name = name;
    ptr->author = autor;
    ptr->year = year;
    ptr->next = NULL;
    ptr->prev = NULL;

    return ptr;
}

// Функции для работы со списком MusicalComposition

void push(MusicalComposition* head, MusicalComposition* element)
{
 
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = element;
    element->prev = head;
    element->next = NULL;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    if (n < 1)
        return NULL;
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head->prev = NULL;

    for (int i = 1; i < n; i++) {
        MusicalComposition *element = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(head, element);
    }

    return head;
}


void removeEl(MusicalComposition* head, char* name_for_remove)
{
    MusicalComposition *current = head;
    while (strcmp(current->name, name_for_remove) != 0) {
        current = current->next;
    }
    if (current->prev == NULL) {
        current->next->prev = NULL; // удаление первого элемента
    } else if (current->next == NULL) {
        current->prev->next = NULL; // удаление последнего элемента
    } else {
        current->next->prev = current->prev;
        current->prev->next = current->next;
    }

    free(current);
}

int count(MusicalComposition* head)
{
    int count = 1;
    MusicalComposition *current = head;
    while (current->next != NULL){
        count += 1;
        current = current->next;
    }

    return count;
}

void print_names(MusicalComposition* head)
{
    MusicalComposition *current = head;
    while (current->next != NULL) {
        puts(current->name);
        current = current->next;
    }
    
    puts(current->name);
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
