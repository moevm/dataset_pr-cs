#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stddef.h>


struct MusicalComposition{
	char* name;
	char* author;
	int year;
	struct MusicalComposition* next;
	struct MusicalComposition* prev;
}typedef MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
	MusicalComposition* mus = malloc(sizeof(MusicalComposition));
	mus->name = name;
	mus->author = autor;
	mus->year = year;
	mus->next = NULL;
	mus->prev = NULL;
	return mus;
}

void push(MusicalComposition* head, MusicalComposition* element){
	MusicalComposition* item = head;
	while (item->next != NULL) {
		item = item->next;
	}
	item->next = element;
	element->prev = item;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
	MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
	for (int i = 1; i < n; i++) {
		push(head, createMusicalComposition(array_names[i], array_authors[i], array_years[i]));
	}
	return head;
}


void removeEl(MusicalComposition* head, char* name_for_remove){
	MusicalComposition* item = head;
	while (strcmp(item->name, name_for_remove) && item->next != NULL) {
		item = item->next;
	}
	if (item->prev == NULL) {
		MusicalComposition* new_item = item->next;
        item->name = new_item->name;
        item->author = new_item->author;
        item->year = new_item->year;
        item->next = new_item->next;	
        item->next->next->prev = item;
        item = new_item;
	} else {
		item->prev->next = item->next;
		if (item->next) item->next->prev = item->prev;
	}
	free(item);
}

int count(MusicalComposition* head){
	int cnt = 0;
	MusicalComposition* item = head;
	while (item->next != NULL) {
		cnt++;
		item = item->next;
	}
	cnt++;
	return cnt;
}

void print_names(MusicalComposition* head){
	MusicalComposition* item = head;
	while (item->next != NULL) {
		printf("%s\n", item->name);
		item = item->next;
	}
	printf("%s\n", item->name);

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
