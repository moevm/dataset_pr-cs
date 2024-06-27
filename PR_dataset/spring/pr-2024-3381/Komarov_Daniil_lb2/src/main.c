#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct MusicalComposition {
        char* name;
        char* author;
        int year;
        struct MusicalComposition* prev;
        struct MusicalComposition* next;
} MusicalComposition;

// Create new composition struct
MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
        MusicalComposition* new_comp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
        new_comp->name = name;
        new_comp->author = author;
        new_comp->year = year;
        new_comp->prev = NULL;
        new_comp->next = NULL;
        return new_comp;
}

// Create composition list
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
        MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
        MusicalComposition* current = head;
        for(unsigned int i = 1; i < n; i++) {
                current->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                current->next->prev = current;
                current = current->next;
        }
        return head;
}

// Push to end of list
void push(MusicalComposition* head, MusicalComposition* element)
{
        while(head->next != NULL) {
                head = head->next;
        }
        head->next = element;
        element->prev = head;
}

// Remove element from list by name
void removeEl(MusicalComposition* head, char* name_for_remove)
{
        MusicalComposition* to_remove = head;
        while(strcmp(to_remove->name, name_for_remove)) {
                to_remove = to_remove->next;
        }

        // If to_remove is first element
        // AVOID THIS SITUATION - LEADS TO LOSS OF POINTER TO ENTIRE LIST
        if(to_remove->prev == NULL) {
                to_remove->next->prev = NULL;
        }
        // If to_remove is last element
        else if(to_remove->next == NULL) {
                to_remove->prev->next = NULL;
        }
        // If to_remove is in the middle of list
        else {
                to_remove->prev->next = to_remove->next;
                to_remove->next->prev = to_remove->prev;
        }
        free(to_remove);
}

int count(MusicalComposition* head) {
        unsigned int i = 0;
        for(; head->next != NULL; i++) {
                head = head->next;
        }
        return i+1;
}

void print_names(MusicalComposition* head) {
        printf("%s\n", head->name);
        while(head->next != NULL) {
                printf("%s\n", head->next->name);
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
