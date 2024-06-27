#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* musicalComposition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    musicalComposition->name = name;
    musicalComposition->author = author;
    musicalComposition->year = year;
    musicalComposition->next = NULL;
    musicalComposition->prev = NULL;
    return musicalComposition;
}

MusicalComposition* createMusicalCompositionList(char** arrayNames, char** arrayAuthors, int* arrayYears, int n) {
    if (n == 0) {
        return NULL;
    }
    MusicalComposition* head = createMusicalComposition(arrayNames[0], arrayAuthors[0], arrayYears[0]);
    MusicalComposition* current = head;
    for (int i=1; i<n; i++) {
        current->next = createMusicalComposition(arrayNames[i], arrayAuthors[i], arrayYears[i]);
        current->next->prev = current;
        current = current->next;
    }
    return head;
}

int count(MusicalComposition* head) {
    MusicalComposition* current = head;
    int k = 0;
    while (current != NULL) {
        current = current->next;
        k++;
    }
    return k;
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

void removeEl(MusicalComposition** head, char* nameForRemove) {
    MusicalComposition* current = *head;
    if (strcmp((*head)->name, nameForRemove) == 0) {
        if ((*head)->next != NULL) {
            (*head)->next->prev = NULL;
        }
        (*head) = (*head)->next;
        return;
    }
    for (int i=0; i<count(*head); i++) {
        if (strcmp(current->next->name, nameForRemove) == 0) {
            if (current->next->next != NULL) {
                current->next->next->prev = current;
            }
            current->next = current->next->next;
            break;
        }
        current = current->next;
    }
}

void printNames(MusicalComposition* head) {
    MusicalComposition* current = head;
    for (int i=0; i<count(head); i++) {
        printf("%s\n", current->name);
        current = current->next;
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


    removeEl(&head, nameForRemove); 
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
