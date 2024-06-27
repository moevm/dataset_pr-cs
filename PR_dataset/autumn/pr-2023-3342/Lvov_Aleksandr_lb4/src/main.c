#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 1000
#define KEY 0
#define PATTERN (double)(end - begin) / CLOCKS_PER_SEC
#define START_TIME time_t begin = clock()
#define END_TIME time_t end = clock()

void get_arr(int * arr);
int cmp(const void * a, const void * b);
bool check_arr(int * arr);
void print_info_bsearch(int * arr, const int key);
void print_info_enum(int * arr, const int key);


int main(){
    int arr[MAX_SIZE];
    const int key = KEY;
    
    get_arr(arr);
    qsort(arr, MAX_SIZE, sizeof(int), cmp);
    print_info_bsearch(arr, key); 
    print_info_enum(arr, key); 
    
    return 0;
}

int cmp(const void * a, const void * b){
    // функция сравнивает два числа, предварительно приведя указатели на них к типу int* и возвращает 0, если числа равны, -1 - если первое число меньше второго и 1 в противном случае
    const int * first = (const int *)a;
    const int * second = (const int *)b;
    if (*first < *second){
        return -1;
    }
    if (*first > *second){
        return 1;
    }
    return 0;
}

void get_arr(int * arr){
    for(int i = 0; i < MAX_SIZE; i++){
        scanf("%d", &arr[i]);
    }
}

bool check_arr(int * arr){
    for(int i = 0; i < MAX_SIZE; i++){
        if (arr[i] == 0){
            return true;
        }
    }
    return false;
}

void print_info_bsearch(int * arr, const int key){
    // функция выводит 1) информацию о нахождении ключа в массиве и 2) время, за которое был совершён поиск, используя двоичный поиск
    START_TIME;
    int * ptr = bsearch(&key, arr, MAX_SIZE, sizeof(int), cmp);
    END_TIME;
    if (ptr){
        printf("exists\n");
    }
    else {
        printf("doesn't exist\n");
    }
    printf("%f\n", PATTERN);
}

void print_info_enum(int * arr, const int key){
    // функция выводит 1) информацию о нахождении ключа в массиве и 2) время, за которое был совершён поиск, используя перебор
    START_TIME;
    bool check = check_arr(arr);
    END_TIME;
    if (check){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", PATTERN);
}
