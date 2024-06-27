#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LEN 80


struct MusicalComposition
{
	char * name;
	char * author;
	int year;

	struct MusicalComposition * prev;
	struct MusicalComposition * next;
};


struct MusicalComposition * createMusicalComposition
(
	char * name,
	char * author,
	int year
)
{
	struct MusicalComposition * mc_p = malloc(sizeof(struct MusicalComposition));
	if (mc_p == NULL) 
	{
		printf("[ERROR] Memory allocation (for mc_p) failed\n");
		return NULL;
	}

	mc_p->name = malloc(LEN * sizeof(char));
	if (mc_p->name == NULL) 
	{
		printf("[ERROR] Memory allocation (for name) failed\n");
		return NULL;
	}

	mc_p->author = malloc(LEN * sizeof(char));
	if (mc_p->author == NULL) 
	{
		printf("[ERROR] Memory allocation (for author) failed\n");
		return NULL;
	}

	strncpy(mc_p->name, name, LEN);
	strncpy(mc_p->author, author, LEN);
	mc_p->year = year;

	mc_p->prev = NULL;
	mc_p->next = NULL;

	return mc_p;
}


void freeMusicalComposition(struct MusicalComposition * mc_p)
{
	free(mc_p->name);
	free(mc_p->author);

	free(mc_p);
}


struct MusicalComposition * createMusicalCompositionList
(
	char** array_names,
	char** array_authors,
	int* array_years,
	int n
)
{
	struct MusicalComposition * head = createMusicalComposition
	(
		array_names[0],
		array_authors[0],
		array_years[0]
	);
	struct MusicalComposition * mc_p = head;
	int i = 1;
	while (i < n)
	{
		mc_p->next = createMusicalComposition
		(
			array_names[i],
			array_authors[i],
			array_years[i]
		);
		mc_p->next->prev = mc_p;
		mc_p = mc_p->next;
		i++;
	}

	return head;
}


void push(struct MusicalComposition * head, struct MusicalComposition * element)
{
	while(head->next != NULL)
	{
		head = head->next;
	}
	head->next = element;
	head->next->prev = head;
}


void removeEl (struct MusicalComposition ** head, char * name_for_remove)
{
	struct MusicalComposition * el;
	struct MusicalComposition * mc_p = *head;
	if (!strcmp(mc_p->name, name_for_remove))
	{
		*head = mc_p->next;
		freeMusicalComposition(mc_p);
		return;
	}
	while (mc_p->next != NULL && strcmp(mc_p->next->name, name_for_remove))
	{
		mc_p = mc_p->next;
	}
	if (mc_p->next == NULL)
	{
		printf("Musical composition \"%s\" not found\n", name_for_remove);
		return;
	}
	el = mc_p->next;
	mc_p->next = el->next;
	mc_p->next->prev = mc_p;
	freeMusicalComposition(el);
}


int count(struct MusicalComposition * head)
{
	int counter = 1;
	while(head->next != NULL)
	{
		head = head->next;
		counter++;
	}
	return counter;
}


void print_names(struct MusicalComposition * head)
{
	while (head != NULL)
	{
		printf("%s\n", head->name);
		head = head->next;
	}
}


void freeMusicalCompositionList(struct MusicalComposition * head)
{
	while (head->next != NULL)
	{
		head = head->next;
		freeMusicalComposition(head->prev);
	}
	freeMusicalComposition(head);
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[LEN];
        char author[LEN];

        fgets(name, LEN, stdin);
        fgets(author, LEN, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    struct MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[LEN];
    char author_for_push[LEN];
    int year_for_push;

    char name_for_remove[LEN];

    fgets(name_for_push, LEN, stdin);
    fgets(author_for_push, LEN, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    struct MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, LEN, stdin);
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

    freeMusicalCompositionList(head);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}
