#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
} PROD;

PROD* createMusicalComposition(char* name, char* autor, int year);
PROD* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);
void push(PROD* head, PROD* element);
void removeEl(PROD* head, char* name_for_remove);
int count(PROD* head);
void print_names(PROD* head);

PROD* createMusicalComposition(char* name, char* autor, int year) {
    PROD* curr = (PROD*)malloc(sizeof(PROD));

    curr->name = name;
    curr->author = autor;
    curr->year = year;

    return curr;
}

PROD* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    if (n <= 0 || array_names == NULL || array_authors == NULL || array_years == NULL) {
        return NULL;
    }
    PROD* top = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    top->prev = NULL;// т.е. начало списка, предыдущих элементов нет
    PROD* temp_prev = top; // просто копия адреса первого
    
    for (int i = 1; i < n; i++) {
        
        PROD* incom = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        temp_prev->next = incom;// указывает адрес на след структуру
        incom->prev = temp_prev;// указывает адрес из текущей структуры на предыдущюю
        temp_prev = incom; // обновление адреса структуры (текущее)
    }
    
    temp_prev->next = NULL;// последний элемент(temp т.к. обновлялся в for)

    return top;
}

void push(PROD* head, PROD* element) {
    
    PROD* curr = head;//  копия
    
    while (curr->next != NULL) curr = curr->next;;// дальше по списку

    curr->next = element;//указатель на след элемент списка
    element->prev = curr;//соединение с предыдущим
    element->next = NULL;// показывает что это конец

    return;
}

void removeEl(PROD* head, char* name_for_remove) {
    
    PROD* curr = head;
    size_t a;

    while (curr->next != NULL) {
        a = strcmp(curr->name, name_for_remove);
        if (!a) {
                
                PROD* beyond = curr->next;
                PROD* before = curr->prev;
                
                before->next = beyond;
                beyond->prev = before;
                
                free(curr);
                
                curr = beyond;
        }
        else curr = curr->next;
}}

int count(PROD* head) {
    PROD* curr = head;
    int count = 1;
    
    while (curr->next != NULL)
        {count++;
        curr = curr->next;}
    
    return count;
}

void print_names(PROD* head) {
    PROD* curr = head;
    
    while (curr->next != NULL) {
        printf("%s\n", curr->name);
        curr = curr->next;;
    }
    
    printf("%s\n", curr->name);
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
    PROD* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    PROD* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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
