#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    
    MusicalComposition* new_composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));

    if (new_composition == NULL){
        fprintf(stderr, "Memory allocation error");
        exit(1);
    }

    *new_composition = (MusicalComposition){name,author,year};
    
    return new_composition;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    if (n==0) return NULL;

    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head->prev = NULL;

    if (n==1) return head;

    MusicalComposition *tmp = createMusicalComposition(array_names[1], array_authors[1],array_years[1]);

    head->next = tmp;
    tmp->prev = head;

    for(size_t i = 2; i < n; i++){   
        tmp->next = createMusicalComposition(array_names[i], array_authors[i],array_years[i]);
        tmp->next->next = NULL;  
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    return head;
}


void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *el = head;
    
    while (el->next != NULL) el = el->next;
    
    el->next = element;
    element->prev = el;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *el = head->next;
    
    while(strcmp(el->name, name_for_remove)!= 0)el = el->next;
    
    if (el->prev == NULL) el->next->prev = NULL;
    
    else if (el->next == NULL) el->prev->next = NULL;
    
    else {
        el->prev->next = el->next;
        el->next->prev = el->prev;
    }
    free(el);
}

int count(MusicalComposition* head){
    int amount=1;
    MusicalComposition *el = head;
    while(el->next != NULL) {
        el = el->next;
        amount++;
    }
    return amount;
}

void print_names(MusicalComposition* head){
    MusicalComposition *el = head;
    for (int i=0;i<count(head);i++){
        printf("%s\n", el->name);
        el = el->next;
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
