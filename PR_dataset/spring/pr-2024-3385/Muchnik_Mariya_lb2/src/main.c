#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* item = (MusicalComposition*)malloc(sizeof(MusicalComposition)); 
    item->name = name;
    item->author = author;
    item->year = year;
    item->prev = NULL;
    item->next = NULL;
    return item;
}

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* item = head;
    while(item->next) item = item->next;
    element->prev = item;
    item->next = element;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for (int i = 1; i < n; i++) {
        MusicalComposition* element = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(head, element);
    }
    return head;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* item = head;
    while(item->next) {
        if (!strcmp(item->name, name_for_remove)) {
            if (!item->prev) {
                MusicalComposition* next_item = item->next;
                item->name = next_item->name;
                item->author = next_item->author;
                item->year = next_item->year;
                item->next = next_item->next;
                item->next->next->prev = item;
                item = next_item;
            }
            else {
                item->prev->next = item->next;
                if (item->next) item->next->prev = item->prev;
            }
            free(item);
            break;
        }
        item = item->next;
    }
}

int count(MusicalComposition* head) {
    MusicalComposition* item = head;
    int count = 1;
    while(item->next) {
        count++;
        item = item->next;
    }
    return count;
}

void print_names(MusicalComposition* head) {
    MusicalComposition* item = head;
    while(item->next) {
        printf("%s\n", item->name);
        item = item->next;
    }
    printf("%s\n", item->name);
}

void free_list(MusicalComposition* head) {
    MusicalComposition* item = head;
    MusicalComposition* item_next;
    do {
        item_next = item->next;
        free(item);
        item = item_next;
    } while (item->next);
    free(item);
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0; i < length; i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n")) = 0;
        (*strstr(author,"\n")) = 0;

        names[i] = (char*)malloc(sizeof(char*)*(strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*)*(strlen(author)+1));

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
    (*strstr(name_for_push,"\n")) = 0;
    (*strstr(author_for_push,"\n")) = 0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n")) = 0;

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

    free_list(head);
    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(years);
    free(names);
    free(authors);
    return 0;
}