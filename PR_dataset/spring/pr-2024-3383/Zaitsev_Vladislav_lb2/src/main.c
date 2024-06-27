#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char *name;
    char *author;
    int year;
    struct MusicalComposition* next;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    tmp->name = name;
    tmp->author = autor;
    tmp->year = year;
    tmp->next = NULL;
    return tmp;
};

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    if (n == 1){
        return head;
    }
    MusicalComposition* tmp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    head->next = tmp;
    for(size_t i = 2; i < n; i++){
          tmp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
          tmp->next->next = NULL;
          tmp = tmp->next;
    }
    return head;
};

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *cur = head;
    while(cur->next){
        cur = cur->next;
    }
    cur->next = element;
    cur->next->next = NULL;
};
void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *cur = head;
    MusicalComposition *new_cur = head;
    MusicalComposition *new_continue = NULL;
    int count = 0;
    while(strcmp(cur->name, name_for_remove) != 0){
        cur = cur->next;
        count++;
    }
    new_continue = cur->next;
    for(size_t i = 0; i < count - 1; i++){
        new_cur = new_cur->next;
    }
    new_cur->next = new_continue;
};
int count(MusicalComposition* head){
    MusicalComposition* cur = head;
    int count = 1;
    do{
        count++;
        cur = cur->next;
    }while(cur->next);
    return count;
}
void print_names(MusicalComposition*  head){
    MusicalComposition* cur = head;
    do{
        printf("%s\n", cur->name);
        cur = cur->next;
    }while(cur->next);
   printf("%s\n", cur->name);
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
