#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* previous;
    struct MusicalComposition* next;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* MComp = malloc(sizeof(MusicalComposition));
    MComp->name = name;
    MComp->author = author;
    MComp->year = year;
    MComp->previous = NULL;
    MComp->next = NULL;
    return MComp;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    element->previous = curr;
    curr->next = element;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for (int i = 1; i < n; i++) {
        MusicalComposition* curr = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(head, curr);
    }
    return head;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* curr = head;
    int found = 0;
    while (strcmp(curr->name, name_for_remove)) {
        curr = curr->next;
        found = 1;
    }
    if (found) {
        if (curr->previous == NULL) {
            curr->next->previous = NULL;
        } else if (curr->next == NULL) {
            curr->previous->next = NULL;
        } else {
            curr->previous->next = curr->next;
            curr->next->previous = curr->previous;
        }
    }
}

int count(MusicalComposition* head) {
    int counter;
    if (head == NULL){
        counter = 0;
    }
    else{
        counter = 1;
    }
    MusicalComposition* current;
    current = head;
    while (current->next != NULL){
        current = current->next;
        counter+=1;
    }
    return counter;
}


void print_names(MusicalComposition* head) {
    MusicalComposition* curr = head;
    while (curr->next) {
        puts(curr->name);
        curr = curr->next;
    }
    puts(curr->name);
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
