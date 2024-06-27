#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "input.h"
#include "output.h"
#define MAX_ARR 20

int main(){
    int arr[MAX_ARR];
    int choice;
    scanf("%d", &choice);
    size_t size = input(arr);
    output(choice, arr, size);
    return 0;
}