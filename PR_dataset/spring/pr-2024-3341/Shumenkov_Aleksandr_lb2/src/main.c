#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
    
}MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition *new_musical_composition = (MusicalComposition*)calloc(1, sizeof(MusicalComposition));
    new_musical_composition->name = name;
    new_musical_composition->author = author;
    new_musical_composition->year = year;
    new_musical_composition->next = NULL;
    new_musical_composition->prev = NULL;
    return new_musical_composition;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* tmp = head;
    for (int i=1; i<n; i++) {
        tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    return head;
}

int count(struct MusicalComposition* head){
    int counting = 0;
    struct MusicalComposition* curr_musical_composition = head;
    while (curr_musical_composition != NULL)
    {
        curr_musical_composition = curr_musical_composition->next;
        counting++;
    }
    return counting;
}

void push(MusicalComposition** head, MusicalComposition* element) {
    if (*head == NULL) {
        *head = element;
        return;
    }
    MusicalComposition* current = *head;
    while (current->next != NULL) {
        current = current->next;        
    }
    current->next = element;
    current->next->prev = current;
}


void removeEl(MusicalComposition* head, char* nameForRemove){
    if(strcmp(head->name, nameForRemove) == 0){
        head = head->next;
        head->prev = NULL;
    } else {
    while(strcmp(head->next->name, nameForRemove) != 0){
        head = head->next;
    }
    head->next = head->next->next;
    if(head->next != NULL)
        head->next->prev = head;
    }
}

void printNames(MusicalComposition* head){
    MusicalComposition* tmp = head;
    while(tmp != NULL){
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}

int main() {
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0; i<length; i++) {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);
        (*strstr(name, "\n"))=0;
        (*strstr(author, "\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }

    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    
    char nameForPush[80];
    char authorForPush[80];
    int yearForPush;

    char nameForRemove[80];

    fgets(nameForPush, 80, stdin);
    fgets(authorForPush, 80, stdin);
    fscanf(stdin, "%d\n", &yearForPush);
    (*strstr(nameForPush,"\n"))=0;
    (*strstr(authorForPush,"\n"))=0;

    MusicalComposition* elementForPush = createMusicalComposition(nameForPush, authorForPush, yearForPush);

    fgets(nameForRemove, 80, stdin);
    (*strstr(nameForRemove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(&head, elementForPush);

    k = count(head);
    printf("%d\n", k);


    removeEl(head, nameForRemove); 
    printNames(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0; i<length; i++) {
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;
    
}
