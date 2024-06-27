#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define STR_FIELD_LEN 80


/* Описание структуры MusicalComposition */
typedef struct MusicalComposition {
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
    char name[STR_FIELD_LEN];
    char author[STR_FIELD_LEN];
    int year; // uint
} MusicalComposition;


MusicalComposition* 
createMusicalComposition(
    char* name, 
    char* author, 
    int year
) {
    MusicalComposition* mc = malloc(sizeof(MusicalComposition));
    mc->next = NULL;
    mc->prev = NULL;
    strncpy(mc->name, name, STR_FIELD_LEN);
    strncpy(mc->author, author, STR_FIELD_LEN);
    mc->year = year;
    return mc;
}


void 
removeMusicalComposition(
    MusicalComposition* mc
) { 
    free(mc);
}


MusicalComposition* 
createMusicalCompositionList(
    char** array_names, 
    char** array_authors, 
    int* array_years, 
    int n
) {
    MusicalComposition *head, *end;
    
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    end = head;
    
    // Так как нет поля end, то оптимальней обойтись без функции push
    for (size_t i = 1; i < n; i++) {
        MusicalComposition* mc = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        end->next = mc;
        mc->prev = end;
        end = mc;
    }
    
    return head;
}


void 
removeMusicalCompositionList(
    MusicalComposition* head
) {
    MusicalComposition *mc, *next_mc;
    mc = head;
    
    while (mc != NULL) {
        next_mc = mc->next;
        removeMusicalComposition(mc);
        mc = next_mc;
    }
}


void 
push(
    MusicalComposition* head,
    MusicalComposition* element
) {
    if (head == NULL) {
        return;
    }
    
    MusicalComposition* mc = head;
    while (mc->next != NULL) {
        mc = mc->next;
    }
    
    mc->next = element;
    element->prev = mc;
}


void 
removeEl(
    MusicalComposition* head, 
    char* name_for_remove
) {
    MusicalComposition* mc = head;
    while (1) {
        if (mc == NULL) {
            return; // TODO: not found msg
        }
        
        if (strcmp(mc->name, name_for_remove) == 0) {
            MusicalComposition *prev_mc, *next_mc;
            prev_mc = mc->prev;
            next_mc = mc->next;
            
            prev_mc->next = next_mc;
            next_mc->prev = prev_mc;
            
            removeMusicalComposition(mc);
            return;
        }
        
        mc = mc->next;
    }
}


int 
count(
    MusicalComposition* head
) {
    int count = 0;
    MusicalComposition* mc = head;
    while (mc != NULL) {
        count++;
        mc = mc->next;
    }
    
    return count;
}


void 
print_names(
    MusicalComposition* head
) {
    MusicalComposition* mc = head;
    while (mc != NULL) {
        puts(mc->name);
        mc = mc->next;
    }
    
    // TODO: head == NULL errmsg
}



/* -------------------------------------- */
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

    // CLEAN UP
    removeMusicalCompositionList(head);

    return 0;
}