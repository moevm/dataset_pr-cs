#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} MusCom;



MusCom* createMusicalComposition(char* name, char* author, int year){
    MusCom* node = (MusCom*)malloc(sizeof(MusCom));
    node->name = name;
    node->author = author;
    node->year = year;

    return node;
}



void push(MusCom* head, MusCom* node){
    MusCom* temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = node;
    node->prev = temp;
    node->next = NULL;
}



MusCom* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    if (n > 0){
        MusCom* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
        head->prev = NULL;

        if (n > 1){
            for (int i = 1; i < n; i++){
                MusCom* node = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                push(head, node);
            }
        }

        return head;
    }
    else{
        printf("Error: input array's length isn't enough!");
        exit(1);
    }
}



void removeEl(MusCom* head, char* name_for_remove){
    MusCom* temp = head;
    while(temp){
        if (!strcmp(temp->name, name_for_remove)){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            break;
        }
        temp = temp->next;
    }
}



int count(MusCom* head){
    MusCom* temp = head;
    int count = 0;

    while(temp){
        count += 1;
        temp = temp->next;
    }

    return count;
}



void print_names(MusCom* head){
    MusCom* temp = head;
    while(temp){
        printf("%s\n", temp->name);
        temp = temp->next;
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
    MusCom* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusCom* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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