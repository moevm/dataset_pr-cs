#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year);

// Функции для работы со списком MusicalComposition

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


MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* Music = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    Music->name = name;
    Music->author = author;
    Music->year = year;
    Music->next = NULL;
    Music->prev = NULL;
    return Music;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);

    head->next = tmp;
    tmp->prev = head;

    for (int i = 2; i < n; i++)
    {
        MusicalComposition* tmpSecond = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmpSecond->prev = tmp;
        tmp->next = tmpSecond;
        tmp = tmpSecond;
    }
    return head;
}


void push(MusicalComposition* head, MusicalComposition* element){
    while (head->next) head = head->next;
    head->next = element;
    element->prev = head;
}


void removeEl(MusicalComposition* head, char* name_for_remove){
    while (head)
    {
        if (!strcmp(head->name, name_for_remove))
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            MusicalComposition* tmp = head;
            head = head->next;
            free(tmp);
        }
        else head = head->next;
    }
}


int count(MusicalComposition* head){
    int counter = 0;
    while (head)
    {
        counter++;
        head = head->next;
    }
    return counter;
}


void print_names(MusicalComposition* head){
    while(head)
    {
        printf("%s\n", head->name);
        head = head->next;
    }
}