#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition {
	char *name;
	char *author;
	int year;
	struct MusicalComposition *next;
	struct MusicalComposition *prev;
} MusicalComposition;

// Функции для создания структуры MusicalComposition
MusicalComposition *createMusicalComposition(char *name, char *author, int year)
{
	MusicalComposition *muscomp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
	muscomp->name = name;
	muscomp->author = author;
	muscomp->year = year;

	return muscomp;
}

// Функции для работы со списком MusicalComposition
MusicalComposition *createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
	MusicalComposition *head;
	if (n >= 1) {
		head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
		if (n >= 2) {
			MusicalComposition *tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
			
			head->next = tmp;
			tmp->prev = head;
			
			for (size_t i = 2; i < n; i++) {
				tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
				tmp->next->prev = tmp;
				tmp = tmp->next;
			}
		}
	}

	return head;
}

// функция для вставки элемента в конец списка
void push(MusicalComposition* head, MusicalComposition* element)
{
	if (head) {
		MusicalComposition *tmp = head;
		while (tmp->next)
			tmp = tmp->next;
	
		tmp->next = element;
		element->prev = tmp;
		element->next = NULL;
	}
}

// функция для удаления элемента списка с определённым именем
void removeEl(MusicalComposition* head, char* name_for_remove)
{
	MusicalComposition *tmp = head;
	while (tmp) {
		if (!strcmp(tmp->name, name_for_remove)) {
			if (tmp->prev == NULL && tmp->next == NULL) {
				free(tmp);
				head = NULL;
			} else if (tmp->prev == NULL) {
				head = tmp->next;
				free(head->prev);
			} else if (tmp->next == NULL) {
				MusicalComposition *tmp_sec = tmp->prev;
				free(tmp);
				tmp_sec->next = NULL;
			} else {
				MusicalComposition *tmp_prev = tmp->prev;
				tmp_prev->next = tmp->next;
				tmp->next->prev = tmp_prev;
				free(tmp);
			}
			break;
		}
		tmp = tmp->next;
	}
}

// функция для подсчёта количества элементов в списке
int count(MusicalComposition* head)
{
	if (head) {
		MusicalComposition *tmp = head;

		int count = 1;
		while (tmp->next) {
			count++;
			tmp = tmp->next;
		}
		return count;
	}
	return 0;
}

// вывод полей name музыкальных композиций
void print_names(MusicalComposition* head)
{
	if (head) {
		MusicalComposition *tmp = head;
		for (size_t i = 0; i < count(head); i++) {
			printf("%s\n", tmp->name);
			tmp = tmp->next;
		}
	}
}

int main()
{
	int length;
    	scanf("%d\n", &length);  

    	char** names = (char**)malloc(sizeof(char*)*length);
    	char** authors = (char**)malloc(sizeof(char*)*length);
    	int* years = (int*)malloc(sizeof(int)*length);

    	for (int i=0;i<length;i++) {
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

    	for (int i=0;i<length;i++) {
        	free(names[i]);
        	free(authors[i]);
    	}
    	free(names);
    	free(authors);
    	free(years);

    	return 0;
}
