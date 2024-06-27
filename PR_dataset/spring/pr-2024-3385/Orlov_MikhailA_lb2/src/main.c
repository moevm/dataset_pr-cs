#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 80


// Описание структуры MusicalComposition

typedef struct MusicalComposition
{
	char* name;
	char* author;
	int year;
	struct MusicalComposition* next;
	struct MusicalComposition* prev;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
	MusicalComposition* composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
	composition->name = name;
	composition->author = author;
	composition->year = year;
	composition->next = NULL;
	composition->prev = NULL;
	return composition;
}

// Функции для работы со списком MusicalComposition

void push(MusicalComposition* head, MusicalComposition* element)
{
	MusicalComposition* composition = head;
	while(composition->next) composition = composition->next;
	element->prev = composition;
	composition->next = element;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
	MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
	for(size_t i = 1; i < n; i++)
	{
		MusicalComposition* composition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
		push(head, composition);
	}
	return head;
}

void removeEl(MusicalComposition* head, char* name_for_remove)
{
	int flag = 0;
	MusicalComposition* composition = head;
	while(strcmp(composition->name, name_for_remove))
	{
		composition = composition->next;
		flag = 1;
	}
	if(flag)
	{
		if(composition->prev == NULL)
		{
			composition->next->prev = composition->prev;
		}
		else if(composition->next == NULL)
		{
			composition->prev->next = composition->next;
		}
		else
		{
			composition->prev->next = composition->next;
			composition->next->prev = composition->prev;
		}
		free(composition);
	}
}
	
size_t count(MusicalComposition* head)
{
	MusicalComposition* composition = head;
	size_t k = 1;
	while(composition->next)
	{
		composition = composition->next;
		k++;
	}
	return k;
}

void print_names(MusicalComposition* head)
{
	MusicalComposition* composition = head;
	while(composition->next)
	{
		printf(composition->name);
		composition = composition->next;
	}
	printf(composition->name);
}


int main(){
	int length;
	scanf("%d\n", &length);  

	char** names = (char**)malloc(sizeof(char*)*length);
	char** authors = (char**)malloc(sizeof(char*)*length);
	int* years = (int*)malloc(sizeof(int)*length);

	for (int i=0;i<length;i++)
	{
		char name[SIZE];
		char author[SIZE];

		fgets(name, SIZE, stdin);
		fgets(author, SIZE, stdin);
		fscanf(stdin, "%d\n", &years[i]);

		(*strstr(name,"\n"))=0;
		(*strstr(author,"\n"))=0;

		names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
		authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

		strcpy(names[i], name);
		strcpy(authors[i], author);

	}
	MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
	char name_for_push[SIZE];
	char author_for_push[SIZE];
	int year_for_push;

	char name_for_remove[SIZE];

	fgets(name_for_push, SIZE, stdin);
	fgets(author_for_push, SIZE, stdin);
	fscanf(stdin, "%d\n", &year_for_push);
	(*strstr(name_for_push,"\n"))=0;
	(*strstr(author_for_push,"\n"))=0;

	MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

	fgets(name_for_remove, SIZE, stdin);
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