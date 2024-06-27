#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition
{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* previous;
}MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author,int year)
{
    MusicalComposition* newComposition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    newComposition->name=(char*)calloc(strlen(name)+1, sizeof(char));
    newComposition->author=(char*)calloc(strlen(author)+1, sizeof(char));
    strcpy(newComposition->name, name);
    strcpy(newComposition->author, author);
    newComposition->year=year;
    newComposition->next = NULL;
    newComposition->previous = NULL;
    return newComposition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    MusicalComposition* MusicalCompositionList = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* currentComposition = MusicalCompositionList;
    for (int i=1; i<n; i++)
    {
        MusicalComposition* tempComposition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tempComposition->previous = currentComposition;
        currentComposition->next=tempComposition;
        currentComposition=tempComposition;
    }
    return MusicalCompositionList;
}

void push(MusicalComposition* head, MusicalComposition* element)
{
    MusicalComposition* tail = head;
    while(tail->next!=NULL)
        tail=tail->next;
    tail->next=element;
    element->previous = tail;
}

void removeEl(MusicalComposition* head, char* name_for_remove)
{
    MusicalComposition* node = head;
    while(node->next!=NULL && strcmp(node->name, name_for_remove)!=0)
        node=node->next;
    if (strcmp(node->name, name_for_remove)==0)
    {
        free(node->name);
        free(node->author);
        node->previous->next=node->next;
        node->next->previous=node->previous;
        free(node);
    }
}

int count(MusicalComposition* head)
{
    int num=0;
    if (head!=NULL)
    {
        num=1;
        MusicalComposition* current=head;
        while(current->next!=NULL)
        {
            num++;
            current=current->next;
        }
    }
    return num;
}

void print_names(MusicalComposition* head)
{
    if (head!=NULL)
    {
        MusicalComposition* current = head;
        do
        {
            puts(current->name);
            current=current->next;
        }while(current!=NULL);
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