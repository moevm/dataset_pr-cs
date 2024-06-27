#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition {
    char name[80];
    char author[80];
    int year;
    
    struct MusicalComposition *prev;
    struct MusicalComposition *next;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
    MusicalComposition *result = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    
    if (result == NULL)
        return NULL;

    strcpy(result->name, name);
    strcpy(result->author, author);
    result->year = year;
    result->prev = NULL;
    result->next = NULL;
    
    return result;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
	if (n == 0) return NULL;

    MusicalComposition *first = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *last  = first;
    
    for (int i = 1; i < n; i++) {
        last->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        
        last->next->prev = last;
        last = last->next;
    }
    
    return first;
}

void push(MusicalComposition* head, MusicalComposition* element)
{
    MusicalComposition *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    
    last->next = element;
    element->prev = last;
}

void removeEl(MusicalComposition* head, char* name_for_remove)
{
	MusicalComposition *current = head;
	while (current != NULL && strcmp(current->name, name_for_remove) != 0) {
		current = current->next;
	}

	if (current == NULL)
		return;

	MusicalComposition *prev = current->prev;
	MusicalComposition *next = current->next;
    free(current);

	if (prev) prev->next = next;
	if (next) next->prev = prev;
}

int count(MusicalComposition* head)
{
	MusicalComposition *tail = head;
	int cnt = 0;

	while (tail != NULL) {
		cnt++;
		tail = tail->next;
	}

	return cnt;	
}

void print_names(MusicalComposition* head)
{
	MusicalComposition *current = head;
	while (current != NULL) {
		puts(current->name);
		current = current->next;
	}
}

int main()
{
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
