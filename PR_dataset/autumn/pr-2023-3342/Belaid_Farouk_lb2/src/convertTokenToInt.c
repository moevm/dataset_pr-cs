#include "convertTokenToInt.h"

int convertTokenToInt(char* token,int *arr){
    int size = 0;
    token = strtok(NULL, " \n");

    while (token != NULL && size < 100) {
        arr[size++] = atoi(token);
        token = strtok(NULL, " \n");
    }

    return size;
}
