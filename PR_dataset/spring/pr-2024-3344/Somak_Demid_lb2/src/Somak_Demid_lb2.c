#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition {

    struct MusicalComposition *prev;
    struct MusicalComposition *next;
    char *name;
    char *author;
    int year;

} MusicalComposition;


// Создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* Composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));

    Composition->name = name;
    Composition->author = author;
    Composition->year = year;
    Composition->next = NULL;
    Composition->prev = NULL;

    return Composition;
}

void push(MusicalComposition* head, MusicalComposition* element);

// Функции для работы со списком MusicalComposition
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    if (n < 1){
        printf("Для создания списка необходима хотя бы одна композиция");
        exit(1);
    }
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* element;

    for(int i = 1; i < n; i++){
        element = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(head,element);
    }

    return head;
}

// Функции для добавления элемента в конец списка
void push(MusicalComposition* head, MusicalComposition* element){
    while(head->next != NULL){
        head = head -> next;
    }

    element -> prev = head;
    head-> next = element;

}

int count(MusicalComposition* head);

// Функции для удаления элемента списка,
void removeEl(MusicalComposition* head, char* name_for_remove){

    while(head != NULL){
        if (strcmp(head->name,name_for_remove)==0){
            head->next->prev = head->prev;
            head->prev->next = head->next;
            free(head);
            head = NULL;
        }else{
            head = head->next;
        }
    }
}

// Функции для подсчёта количества элементов списка
int count(MusicalComposition* head){
    int count = 1;

    while(head->next != NULL){
        head = head->next;
        count+= 1;
    }

    return count;
}

// Функции для вывода названия композиций
void print_names(MusicalComposition* head){
    while(head != NULL) {
        printf("%s\n", head->name);
        head = head->next;
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
