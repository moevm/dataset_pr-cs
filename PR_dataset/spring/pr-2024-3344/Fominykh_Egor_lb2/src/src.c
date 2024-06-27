#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *pred;

} MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition *t = malloc(sizeof(MusicalComposition));
    t->name = name;
    t->author = author;
    t->year = year;
    return t;
    t->next = NULL;
    t->pred = NULL;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    MusicalComposition* head = NULL;
    MusicalComposition* tail = NULL;
    for(int i = 0; i < n; ++i){
        MusicalComposition* first = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if(NULL == head){
            head = first;
            tail = first;
        } else {
            tail->next=first;
            first->pred=tail;
            tail = first;
        }
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *first = head;
    while(first->next!=NULL){
        first = first->next;
    }
    first->next = element;
    element->pred = first;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    
    MusicalComposition *first = head;
    while(strcmp(first->name, name_for_remove)){
        first = first->next;
    }
    first->pred->next = first->next;
    first->next->pred = first->pred;
    free(first);
}

int count(MusicalComposition* head){
    MusicalComposition *first = head;
    int k=0;
    while(first!=NULL){
        k++;
        first = first->next;
    }
    return k;
}

void print_names(MusicalComposition* head){
    MusicalComposition *first = head;
    while (first != NULL) {
        printf("%s\n", first->name);
    first = first->next;
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
