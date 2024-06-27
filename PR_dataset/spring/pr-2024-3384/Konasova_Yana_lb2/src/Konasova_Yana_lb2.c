#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;

MusicalComposition* createMusicalComposition(char* name1, char* autor1,int year1){
    MusicalComposition* some_one = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    some_one->name=name1;
    some_one->author=autor1;
    some_one->year=year1;
    return some_one;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    head->next=tmp;
    head->prev=NULL;
    tmp->prev=head;
    tmp->next=NULL;

    for (int i=2; i<n; i++){
        tmp->next=(MusicalComposition*)malloc(sizeof(MusicalComposition));
        tmp->next=createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmp->next->next=NULL;
        tmp->next->prev=tmp;
        tmp = tmp->next;
    }
    return head;
}


void push(MusicalComposition* head, MusicalComposition* element){
    while (head->next!=NULL){
        head= head ->next;
    }
    head->next=element;
}


void removeEl(MusicalComposition* head, char* name_for_remove){
    while(strcmp(head->name, name_for_remove)!=0){
        head->prev=head;
        head=head->next;
    }
    head->prev->next=head->next;
    free(head);
}
int count(MusicalComposition* head){
    int count=0;
    while(head->next!=NULL){
        head = head -> next;
        count+=1;
    }
    return count+1;
}

void print_names(MusicalComposition* head){
    while(head->next!=NULL){
        printf("%s\n", head->name);
        head = head -> next;
    }
    printf("%s\n", head->name);
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
