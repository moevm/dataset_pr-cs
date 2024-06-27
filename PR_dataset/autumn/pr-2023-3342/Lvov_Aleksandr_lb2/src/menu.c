#include <stdio.h>

#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define MAX_SIZE 100
#define OUT_FMT "%d\n"

int input(int *arr, int *num_case);
void output(int num_case, int *arr, int size);

int main(){
	int num_case;
        int arr[MAX_SIZE];

	int size = input(arr, &num_case);
	output(num_case, arr, size);

        return 0;
}

int input(int *arr, int *num_case){

       	int index = 0;
        char space = ' ';
        scanf("%d", num_case);

        while (index < MAX_SIZE && space ==  ' '){
                scanf("%d%c", &arr[index], &space);
                index++;
        }

        return index;
}

void output(int num_case, int *arr, int size){
        switch(num_case)
        {
                case 0:
                printf(OUT_FMT, max(arr, size));
                break;

                case 1:
                printf(OUT_FMT, min(arr, size));
                break;

                case 2:
                printf(OUT_FMT, diff(arr, size));
                break;

                case 3:
                printf(OUT_FMT, sum(arr, size));
                break;

                default:
                printf("Данные некорректны");
        }


}