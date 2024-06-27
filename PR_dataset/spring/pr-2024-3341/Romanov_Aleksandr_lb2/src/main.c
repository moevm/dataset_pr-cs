#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define STR_LEN 80


// Описание структуры MusicalComposition

typedef struct MusicalComposition
{
    char name[STR_LEN];
    char author[STR_LEN];
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

int count(MusicalComposition* head);
void print_names(MusicalComposition* head);
void removeEl(MusicalComposition** head, char* name_for_remove);
void push(MusicalComposition* head, MusicalComposition* element);
MusicalComposition* createMusicalComposition(char* name, char* author,int year);
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);

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

    removeEl(&head, name_for_remove); 
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

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* song = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    
    song->year = year;
    strncpy(song->name, name, STR_LEN);
    strncpy(song->author, author, STR_LEN);
    return song;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head_song = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head_song->prev = NULL;
    head_song->next = NULL;
    MusicalComposition* previous_ptr = head_song;
    for(int i = 1; i < n; i++){
        MusicalComposition* song = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        song->prev = previous_ptr;
        song->next = NULL;
        previous_ptr->next = song;
        previous_ptr = song;

    }
    return head_song;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* ptr = head->next;
    while (1)
    {
        if (ptr->next == NULL){
            break;
        }
        ptr = ptr->next;
    }
    element->prev = ptr;
    element->next = NULL;
    ptr->next = element;
    
}

int count(MusicalComposition* head){
    int counter = 1;
    MusicalComposition* ptr = head->next;
    while (1)
    {
        counter++;

        if (ptr->next == NULL){
            break;
        }
        ptr = ptr->next;

    }
    return counter;
}

void removeEl(MusicalComposition** head, char* name_for_remove) {
    MusicalComposition* ptr = (*head)->next;

    if (strstr((*head)->name, name_for_remove)) {
        (*head)->next->prev = NULL;
        MusicalComposition *temp = *head;
        *head = (*head)->next;
        free(temp);
    } else {
        while (ptr != NULL) {
            if (strstr(ptr->name, name_for_remove)) {
                ptr->prev->next = ptr->next;
                if (ptr->next != NULL) {
                    ptr->next->prev = ptr->prev;
                }
                free(ptr);
                break;
            }
            ptr = ptr->next;
        }
    }
}

void print_names(MusicalComposition* head){
    MusicalComposition* ptr = head->next;
    puts(head->name);
    while (1)
    {   
        puts(ptr->name);
        if (ptr->next == NULL){
            break;
        }
        ptr = ptr->next;
    }
}
