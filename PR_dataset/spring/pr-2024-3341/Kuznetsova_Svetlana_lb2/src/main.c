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
	MusicalComposition* element = (MusicalComposition*)malloc(sizeof(MusicalComposition));
	element->name = name;
	element->author = author;
	element->year = year;
	element->next = NULL;
	element->prev = NULL;
	return element;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
	MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
	MusicalComposition* tmp = head;

	for (int i = 1; i < n; i++) {
		tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	return head;
}

void push(MusicalComposition* head, MusicalComposition* element) {
	MusicalComposition* tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = element;
	tmp->next->prev = tmp;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
	MusicalComposition* tmp = head;
	while (strcmp(tmp->name, name_for_remove) && tmp != NULL) {
		tmp = tmp->next;
	}

	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;

	free(tmp);
}

int count(MusicalComposition* head) {
	MusicalComposition* tmp = head;
	int cnt = 0;
	while (tmp != NULL) {
		cnt++;
		tmp = tmp->next;
	}
	return cnt;
}

void print_names(MusicalComposition* head) {
	MusicalComposition* tmp = head;
	while (tmp != NULL) {
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}

int main() {
	int length;
	scanf("%d\n", &length);

	char** names = (char**)malloc(sizeof(char*)*length);
	char** authors = (char**)malloc(sizeof(char*)*length);
	int* years = (int*)malloc(sizeof(int)*length);

	for (int i = 0; i < length; i++)
	{
		char name[80];
		char author[80];

		fgets(name, 80, stdin);
		fgets(author, 80, stdin);
		fscanf(stdin, "%d\n", &years[i]);

		(*strstr(name, "\n")) = 0;
		(*strstr(author, "\n")) = 0;

		names[i] = (char*)malloc(sizeof(char*) * (strlen(name) + 1));
		authors[i] = (char*)malloc(sizeof(char*) * (strlen(author) + 1));

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
	(*strstr(name_for_push, "\n")) = 0;
	(*strstr(author_for_push, "\n")) = 0;

	MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

	fgets(name_for_remove, 80, stdin);
	(*strstr(name_for_remove, "\n")) = 0;

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

	for (int i = 0; i < length; i++) {
		free(names[i]);
		free(authors[i]);
	}
	free(names);
	free(authors);
	free(years);

	return 0;

}