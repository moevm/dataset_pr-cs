#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
    char* name;
    char* author;
    int year;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition*
createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* node = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    node->name = name;
    node->author = author;
    node->year = year;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void
freeMusicalComposition(MusicalComposition* node){
    node->next = NULL;
    node->prev = NULL;
    free(node);
}

// Функции для работы со списком MusicalComposition

MusicalComposition*
createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition *head;
    if (n >= 1){
        head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
        if (n >= 2){
            MusicalComposition *tmp;
            tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
            head->next = tmp;
            tmp->prev = head;
            for (size_t i = 2; i < n; i++){
                tmp->next  = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                tmp->next->prev = tmp;
                tmp = tmp->next;
            }
        }
    }
    return head;
}

void
push(MusicalComposition* head, MusicalComposition* element){
    if (head == NULL)
        return;
    MusicalComposition *node =  head;
    while (node->next){
        node = node->next;
    }
    node->next = element;
    element->prev = node;
    element->next = NULL;
}

void
removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *tmp = head;
    while (tmp){
        if (!strcmp(tmp->name, name_for_remove)){
            if (tmp->prev == NULL && tmp->next == NULL){
                freeMusicalComposition(tmp);
                head = NULL;
            }
            else if (tmp->prev == NULL){
             head = head->next;
                freeMusicalComposition(head->prev);
                head->prev = NULL;
                tmp = NULL;
            }
            else if (tmp->next == NULL){
				tmp->prev->next = NULL;
                freeMusicalComposition(tmp);
            }
            else{
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                freeMusicalComposition(tmp);
            }
            break;
        }
        tmp = tmp->next;
    }
}

int
count(MusicalComposition* head){
    MusicalComposition *node =  head;
    int num = 0;
    while (node){
        num++;
        node = node->next;
    }
    return num;
}

void
print_names(MusicalComposition* head){
    MusicalComposition *node =  head;
    while (node){
        printf("%s\n", node->name);
        node = node->next;
    }
}


int main(){
    int length;
    scanf("%d\n", &length);

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++){
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
