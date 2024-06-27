#include <stdio.h>
#include "input.h"
#include "output.h"

#define MAX_ARRAY_SIZE 100


int main(){
    int choice;
    int array[MAX_ARRAY_SIZE];

    scanf("%d", &choice);

    output(choice, array, input(array));

    return 0;
}