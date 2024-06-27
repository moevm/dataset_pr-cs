#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char * name;
    char * author;
    int year;
    struct MusicalComposition * next;
    struct MusicalComposition * previous;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition * createMusicalComposition(char* name, char* author,int year){
        MusicalComposition * Composition = (MusicalComposition *)malloc(sizeof(MusicalComposition));
        Composition->name = name;
        Composition->author = author;
        Composition->year = year;
        return Composition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition * CompositionHead = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    CompositionHead->previous = NULL;
    if(n==1){
        CompositionHead->next = NULL;
        return CompositionHead;
    }
    MusicalComposition * tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    tmp->previous = CompositionHead;
    CompositionHead->next = tmp;
    for(int i = 2; i!=n; i++){
        MusicalComposition * next_tmp = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        next_tmp->previous = tmp;
        tmp->next = next_tmp;
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return CompositionHead;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition * tmp = head; 
    while(tmp->next!=NULL){
        tmp = tmp->next;
    }
    tmp->next = element;
    tmp->next->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition * tmp = head;
    if(!strcmp(head->name, name_for_remove)){
        if(head->next != NULL){
            tmp = tmp->next;
            free(head);
            *head = *tmp;
            head->previous = NULL;
        }
        else{
            free(head);
            head = NULL;
        }
        return;
    }
    while((strcmp(tmp->name, name_for_remove))&&(tmp->next!=NULL)){
        tmp = tmp->next;
    }
    if(!strcmp(tmp->name, name_for_remove)){
        if(tmp->next != NULL){
            tmp->previous->next = tmp->next;
            free(tmp);
        }
        else{
            tmp->previous->next = NULL;
            free(tmp);
        }
    }
}

int count(MusicalComposition* head){
    MusicalComposition * tmp = head;
    int i = 1;
    for(;tmp->next!=NULL;i++){
        tmp = tmp->next;
    }
    return i;
}

void print_names(MusicalComposition* head){
    MusicalComposition * tmp = head;
    
    for(;tmp->next!=NULL;){
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
    printf("%s\n", tmp->name);
}


int main(){
    int length;
    scanf("%d\n", &length); 
    if(length == 0)
        return 0;

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
