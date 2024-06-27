#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stddef.h>
#define SIZE 80


struct MusicalComposition
{
    char name[SIZE], author[SIZE];
    int year;

    struct MusicalComposition* next;
};

typedef struct MusicalComposition MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
	MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    strcpy(tmp->name, name);
    strcpy(tmp->author, author);
    tmp->year = year;
    tmp->next = NULL;
    return tmp;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    MusicalComposition* Head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    if ( n == 1 ) return Head;
    MusicalComposition* tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    Head->next = tmp;
    for( size_t i = 1; i < n-1; i ++)
    {
        tmp->next = createMusicalComposition(array_names[i+1], array_authors[i+1], array_years[i+1]);
        tmp->next->next = NULL;
        tmp = tmp->next;
    }
    return Head;
}


void push(MusicalComposition*  head, MusicalComposition* element)
{
    MusicalComposition* current = head;
    do
    {
        current = current-> next;
    }while( current-> next );
    current->next = element;
}

void removeEl (MusicalComposition**  head, char* name_for_remove)
{
    int len = strlen(name_for_remove);
    MusicalComposition* current = *head;
    if ( !strncmp(current->name, name_for_remove, len))
    {
        MusicalComposition* tmp  = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }
    while(1)
    {
        if ( !strncmp(current->next->name, name_for_remove, len)) break;
        current = current->next;
    }
    MusicalComposition* tmp = current->next;
    current->next = current->next->next;
    free(tmp);
}

int count(MusicalComposition*  head)
{
    int count = 0;
    MusicalComposition* current  = head;
    do
    {
        count += 1;
        current = current->next;
    } while (current);
    return count;
}

void print_names(MusicalComposition*  head)
{
    MusicalComposition* current  = head;
    do
    {
        printf("%s\n", current->name);
        current = current->next;
    } while (current);
    
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
