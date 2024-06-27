#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
int cmp(const void* a, const void* b){ 
    const char *f = *(const char**)a; 
    const char *s = *(const char**)b; 
    return strcmp(f, s); 
} 
int compare(const void* a, const void* b){
    const char *f = (const char*)a;
    const char *s = *(const char**)b;
    return strcmp(f, s);
}
int main() { 
    char arr[1001]; 
    int length = 0; 
    char *istr; 
    char str[31];  
    char *arr_split[1001];
    fgets(arr, 1000, stdin); 
    fgets(str, 30, stdin); 
    istr = strtok(arr, " ."); 
    int i = 0; 
    while (istr != NULL) { 
        arr_split[i++] = istr; 
        length++; 
        istr = strtok(NULL, " ."); 
    } 
    qsort(arr_split, length, sizeof(char*), cmp); 
    if (bsearch(&str, arr_split, length, sizeof(char*), compare)) { 
        printf("exists"); 
    } 
    else { 
        printf("doesn't exist"); 
    } 
    return 0; 
}