#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct MusicalComposition {
    char *name, *author;
    int year;
    struct MusicalComposition *next, *prev;
};


// Создание структуры MusicalComposition

struct MusicalComposition* createMusicalComposition(char* name, char* author,int year) {
    struct MusicalComposition *ans = (struct MusicalComposition *)malloc(sizeof(struct MusicalComposition));
    ans->name = name;
    ans->author = author;
    ans->year = year;
    ans->prev = NULL;
    ans->next = NULL;

    return ans;
}

// Функции для работы со списком MusicalComposition

struct MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    struct MusicalComposition *head = createMusicalComposition(array_names[0],array_authors[0],array_years[0]);
    for(int i = 1; i < n;i++){
        head->next = createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
        head->next->prev = head;
        head = head->next;
    }
    while(head->prev!=NULL){
        head = head->prev;
    }
    return head;
}

void push(struct MusicalComposition* head,struct MusicalComposition* element){
    while(head->next != NULL){
        head = head->next;
    }
    head->next = element;
}

void removeEl(struct MusicalComposition* head, char* name_for_remove){
    while(head != NULL && strcmp(head->name, name_for_remove) != 0){
        head = head->next;
    }
    if(head != NULL) {
        if(head->prev != NULL) {
            head->prev->next = head->next;
        }
        if(head->next != NULL) {
            struct MusicalComposition *tmp = head->next->prev;
            head->next->prev = head->prev;
            free(tmp);
        }
    }
}

int count(struct MusicalComposition* head){
    int ans = 1;
    while(head->next != NULL){
        head = head->next;
        ans++;
    }
    return ans;
}

void print_names(struct MusicalComposition* head){
    while(head != NULL){
        printf("%s\n", head->name);
        head = head->next;
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
    struct MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    struct MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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