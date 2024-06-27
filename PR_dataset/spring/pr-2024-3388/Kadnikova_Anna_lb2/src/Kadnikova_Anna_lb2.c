#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
        char* name;
        char* author;
        int year;
        struct MusicalComposition* next;
        struct MusicalComposition* prev;
        struct MusicalComposition* final;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* n, char* a,int y){
        MusicalComposition* tmp = (MusicalComposition*) malloc(sizeof(MusicalComposition));
        tmp -> name = n;
        tmp -> author = a;
        tmp -> year = y;
        tmp -> next = NULL;
        tmp -> prev = NULL;
        tmp -> final = NULL;
        return tmp;

}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
        MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
        MusicalComposition* cur = head;
        for(int i = 1; i < n; i++){
                cur -> next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                cur -> next -> prev = cur;
                cur = cur -> next;
        }
        head -> final = cur;
        cur -> final = head;
        return head;

}

void push(MusicalComposition* head, MusicalComposition* element){
        MusicalComposition* lst = head -> final;
        lst -> next = element;
        lst -> final = NULL;
        element -> final = head;
        element -> prev = lst;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
        MusicalComposition t = {NULL, NULL, 0, head, NULL, NULL};
        MusicalComposition* tmp = &t;
        do{
                tmp = tmp -> next;
                if(!strcmp(tmp -> name, name_for_remove)){
                        tmp -> prev -> next = tmp -> next;
                        tmp -> prev -> final = tmp -> final;
                    
                    
                        tmp -> next -> prev = tmp -> prev;
                        tmp -> next -> final = tmp -> final;
                }
        }while(tmp -> next != NULL);
}

int count(MusicalComposition* head){
        int i = 1;
        while(head -> next != NULL){
                head = head -> next;
                i++;
        }
        return i;
}

void print_names(MusicalComposition* head){
    printf("%s\n", head -> name);
        do{
                head = head -> next;
                printf("%s\n", head -> name);
        }while(head -> next != NULL);

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
}
