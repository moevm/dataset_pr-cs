#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание MusicalComposition
typedef struct MusicalComposition
{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
}MusicalComposition;



// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year);

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

MusicalComposition* createMusicalComposition(char* name, char* author,int year) {
    MusicalComposition* new_track = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    new_track->name = name;
    new_track->author = author;
    new_track->year = year;
    return new_track;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    if (n > 0) {
        MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
        MusicalComposition* tmp = head;
        tmp->next = NULL;
        for (int i = 1; i < n; i++){
            tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
            tmp->next->next = NULL;
            tmp = tmp->next;
        }
        return head;
    }
    else {
        return NULL;
    }
}


void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* tmp = head->next;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = element;
    tmp->next->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    if (strcmp(head->name, name_for_remove)==0) {
        MusicalComposition* a = head;
        head = head->next;
        free(a);
    }
    else {
        MusicalComposition* tmp = head;
        while(tmp->next != NULL) {
            if (strcmp(tmp->next->name, name_for_remove) == 0) {
                MusicalComposition* a = tmp->next;
                tmp->next = tmp->next->next;
                free(a);
                break;
            }
            tmp = tmp->next;
        }
    }
}

int count(MusicalComposition* head) {
    int c = 0;
    if (head != NULL) {
        MusicalComposition* tmp = head;
        do
        {
            c++;
            tmp = tmp->next;
        } while (tmp != NULL);
    }
    return c;
}

void print_names(MusicalComposition* head){
    if (head != NULL) {
        puts(head->name);
        MusicalComposition* tmp = head->next;
        while(tmp != 0) {
            puts(tmp->name);
            tmp = tmp->next;
        }
    }
}

