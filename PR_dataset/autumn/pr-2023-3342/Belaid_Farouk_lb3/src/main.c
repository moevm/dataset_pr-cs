#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void memory_and_create_text(char **mass, char *arr, int countBefore){
    int M = 10;
    int F = 0;
    int G = 0;

    for(int i = 0; arr[i]; i++){
        if(G+1 == M){
            M = M + 10;
            mass[F] = realloc(mass[F], M * sizeof(char));
        }
        mass[F][G] = arr[i];
        G++;
        if(arr[i] == '.' || arr[i] == ';' || arr[i] == '?' || arr[i] == '!'){
            mass[F][G] = '\0';
            F++;
            G = 0;
            M = 10;
        }
    }
}

int processing_text(char **mass, int countBefore){
    int countAfter = 0;

    for(int i = 0; i < countBefore; i++){
        for(int j = 1; mass[i][j]; j++){
            if(isdigit(mass[i][j]) && isalpha(mass[i][j-1])){
                while(isdigit(mass[i][j++]));
                if(isalpha(mass[i][j-1])){
                    mass[i][0] = '\0';
                    countAfter++;
                }
            }
        }
    }
    return countAfter;
}

void print_end(char **mass, int countBefore, int countAFF){
    for(int i = 0; i < countBefore; i++){
            if(mass[i][0] != '\0'){
                puts(mass[i]);
        }
    }

    printf("Количество предложений до %d и количество предложений после %d", countBefore-1, countBefore-countAFF-1);
}

void free_memory(char **mass, char *arr, int countBefore){
    free(arr);
    for(int i = 0; i < countBefore; i++){
        free(mass[i]);
    }
    free(mass);
}

int main(){
    int M = 10;
    int N = 10;
    char c;
    int i = 0;
    int countBefore = 0;
    int new = 0;
    
    char *arr = malloc(N * sizeof(char));
    
    while(1){
        c = getchar();
        if(new == 1){
            new = 0;
            while((c = getchar()) == ' ');
        }
        if(i+1 == N){
            N = N + 10;
            arr = realloc(arr, N * sizeof(char));
        }
        arr[i] = c;
        i++;
        if(c =='.' || c == ';' || c == '?' || c == '!'){
            countBefore++;
            new = 1;
        }
        if(c == '!'){
           arr[i] = '\0';
           break;
        }
    }

    char **mass = malloc(countBefore * sizeof(char*));
    for(int i = 0; i < countBefore; i++){
        mass[i] = malloc(M * sizeof(char));
    }

    memory_and_create_text(mass, arr, countBefore);

    int countAFF = processing_text(mass, countBefore);

    print_end(mass, countBefore, countAFF);
    
    free_memory(mass, arr, countBefore);

    return 0;
}
