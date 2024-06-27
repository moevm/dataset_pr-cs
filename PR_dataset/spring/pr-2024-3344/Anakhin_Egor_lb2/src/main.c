#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition {
    int n;
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* musicItem = malloc(sizeof(MusicalComposition));
    if (musicItem == NULL) {
        return NULL;
    }
    musicItem->n = 1;
    strcpy(musicItem->author, author);
    strcpy(musicItem->name, name);
    musicItem->year = year;
    musicItem->next = NULL;
    musicItem->prev = NULL;
    return musicItem;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition* firstItem = NULL;
    MusicalComposition* prevItem = NULL;
    for (int i = 0; i < n; i++) {
        MusicalComposition* thisItem = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if (thisItem == NULL) {
            while (firstItem != NULL) {
                MusicalComposition* temp = firstItem;
                firstItem = firstItem->next;
                free(temp);
            }
            return NULL;
        }
        if (prevItem != NULL) {
            prevItem->next = thisItem;
            thisItem->prev = prevItem;
        } else {
            firstItem = thisItem;
        }
        prevItem = thisItem;
    }
    return firstItem;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* this = head;
    while (this->next != NULL) {
        this = this->next;
    }
    this->next = element;
    element->prev = this;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* this = head;
    while (this != NULL) {
        if (strcmp(this->name, name_for_remove) == 0) {
            if (this->prev != NULL) {
                this->prev->next = this->next;
            }
            if (this->next != NULL) {
                this->next->prev = this->prev;
            }
            free(this);
            return;
        }
        this = this->next;
    }
}

int count(MusicalComposition* head) {
    int amount = 0;
    MusicalComposition* this = head;
    while (this != NULL) {
        amount++;
        this = this->next;
    }
    return amount;
}

void print_names(MusicalComposition* head) {
    MusicalComposition* this = head;
    while (this != NULL) {
        printf("%s\n", this->name);
        this = this->next;
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
