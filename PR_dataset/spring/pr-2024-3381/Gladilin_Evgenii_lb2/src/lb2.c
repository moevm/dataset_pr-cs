#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* autor, int year){
    MusicalComposition *cur = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    cur->name = name;
    cur->author = autor;
    cur->year = year;
    cur->next = NULL;
    cur->prev = NULL;
    return cur;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition *head = NULL;
    MusicalComposition *list = createMusicalComposition(*array_names, *array_authors, *array_years);
    head = list;
    for (int i = 1; i < n; i++) {
        list->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        list->next->prev = list->next;
        list = list->next;
    }
    return head;
} 

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *cur;
    cur = head;
    if (!head)
        return;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = element;
    element->prev = cur;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *cur;
    cur = head;
    while (cur != NULL) {
        if (strcmp(cur->name, name_for_remove) == 0) {
            if (cur->prev == NULL) {
                cur = cur->next;
                if (head != NULL)
                    cur->prev = NULL;
                return;
            } else {
                cur->prev->next = cur->next;
                if (cur->next != NULL)
                    cur->next->prev = cur->prev;
                return;
            }
        }
        cur->next->prev = cur;
        cur = cur->next;
    }
}

int count(MusicalComposition* head){
    int count = 1;
    MusicalComposition *cur;
    cur = head;
    if (!head) {
        return 0;
    }
    while (cur->next) {
        count++;
        cur = cur->next;
    }
    return count;
}

void print_names(MusicalComposition* head){
    MusicalComposition *cur;
    cur = head;
    if (head) {
        while (cur->next) {
            printf("%s\n", cur->name);
            cur = cur->next;
        }
        printf("%s\n",cur->name);
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