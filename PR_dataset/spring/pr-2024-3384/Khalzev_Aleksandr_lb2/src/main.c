#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


// Описание структуры MusicalComposition

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;

MusicalComposition* createMusicalComposition(char* name1, char* author1,int year1){
    MusicalComposition* newM = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    newM->name = name1;
    newM->author = author1;
    newM->year = year1;
    return newM;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    int j = 0;
    MusicalComposition* h = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    h->name = array_names[j];
    h->author = array_authors[j];
    h->year = array_years[j];
    h->next = tmp;
    h->prev = NULL;
    j++;
    tmp->name = array_names[j];
    tmp->author = array_authors[j];
    tmp->year = array_years[j];
    tmp->next = NULL;
    tmp->prev = h;
    j++;
    for(int i = j; i < n; i++){
        tmp->next = (MusicalComposition*)malloc(sizeof(MusicalComposition));
        tmp->next->name = array_names[i];
        tmp->next->author = array_authors[i];
        tmp->next->year = array_years[i];
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    return h;
}

void push(MusicalComposition* head, MusicalComposition* element){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = element;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* prev = NULL;
    MusicalComposition* current = head;

    while(current != NULL){
        if(strcmp(current->name, name_for_remove) == 0){
            prev->next = current->next;
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

int count(MusicalComposition* head){
    int c = 0;
    while(head->next != NULL){
        c++;
        head = head->next;
    }
    return c + 1;
}

void print_names(MusicalComposition* head){
    printf("%s\n", head->name);
    while(head->next != NULL){
        head = head->next;
        printf("%s\n", head->name);
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
