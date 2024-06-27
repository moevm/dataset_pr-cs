#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MusicalComposition {
    char *name;
    char *author;
    int year;
    struct MusicalComposition *prev;
    struct MusicalComposition *next;
};
typedef struct MusicalComposition MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *author, int year) {
    MusicalComposition *composition = (MusicalComposition *) malloc(sizeof(MusicalComposition));
    if (composition == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    composition->name = malloc(81 * sizeof(char));
    composition->author = malloc(81 * sizeof(char));
    if (composition->name == NULL || composition->author == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    composition->year = year;
    composition->prev = NULL;
    composition->next = NULL;

    strcpy(composition->author, author);
    strcpy(composition->name, name);
    return composition;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    MusicalComposition *head;
    MusicalComposition *last_elem;
    for (int i = 0; i < n; i++) {
        MusicalComposition *new_elem;
        if (i == 0) {
            new_elem = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
            head = new_elem;
        } else {
            new_elem = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
            last_elem->next = new_elem;
            new_elem->prev = last_elem;
        }
        last_elem = new_elem;
    }
    return head;
}

void push(MusicalComposition *head, MusicalComposition *element) {
    MusicalComposition *next_elem = head->next;
    while (next_elem->next != NULL) {
        next_elem = next_elem->next;
    }
    next_elem->next = element;
    element->prev = next_elem;
}

void removeEl(MusicalComposition *head, char *name_for_remove) {
    MusicalComposition *next_elem = head->next;
    while (next_elem != NULL) {
        if (strcmp(next_elem->name, name_for_remove) == 0) {
            if (next_elem->next != NULL) {
                next_elem->next->prev = next_elem->prev;
            }
            if (next_elem->prev != NULL) {
                next_elem->prev->next = next_elem->next;
            }
            free(next_elem->name); // Free memory for name
            free(next_elem->author); // Free memory for author
            free(next_elem); // Free memory for the element
            break;
        }
        next_elem = next_elem->next;
    }
}

int count(MusicalComposition *head) {
    int cnt = 0;
    MusicalComposition *next_elem = head;
    while (next_elem != NULL) {
        cnt++;
        next_elem = next_elem->next;
    }
    return cnt;
}

void print_names(MusicalComposition *head) {
    MusicalComposition *next_elem = head;
    while (next_elem != NULL) {
        printf("%s\n", next_elem->name);
        next_elem = next_elem->next;
    }
}

int main() {
    int length;
    scanf("%d\n", &length);

    char **names = (char **) malloc(sizeof(char *) * length);
    char **authors = (char **) malloc(sizeof(char *) * length);
    int *years = (int *) malloc(sizeof(int) * length);

    if (names == NULL || authors == NULL || years == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; i++) {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name, "\n")) = 0;
        (*strstr(author, "\n")) = 0;

        names[i] = (char *) malloc(sizeof(char) * (strlen(name) + 1));
        authors[i] = (char *) malloc(sizeof(char) * (strlen(author) + 1));

        if (names[i] == NULL || authors[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }

    MusicalComposition *head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MusicalComposition *element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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