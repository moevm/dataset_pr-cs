#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int cmp(const void *a, const void *b){
	const int *f = (const int *)a;
	const int *s = (const int *)b;
	if(*f > *s)
		return 1;

	if(*f < *s)
		return -1;
	return 0;
}
int binar(int* arr)
{
    int low, high, middle;
    low = 0;
    int n = 1;
    int a = 0;
    high = n - 1;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (a < arr[middle])
            high = middle - 1;
        else if (a > arr[middle])
            low = middle + 1;
        else 
            return 0;
    }
    return 1;
}

int main(){
    clock_t start_time1, end_time1 , start_time2, end_time2;
    double total_time1 , total_time2;
    int *arr ;
    int j, l=0, r = 999;
    bool flag = 1;
    int *buffer;
    int n = sizeof(arr)/sizeof(int);
    int mind_num = 500;
    arr = (int*)malloc(1000 * sizeof(int));
    for( int i = 0; i < 1000;i++){
    	scanf("%d", &arr[i]);
    }
   start_time1 = clock();		//начало счета времени для 1 функции 
    for(int i = 0; i < 1000;  i++){
    	if(arr[i] == 0){
    	flag = 0;
    	break;		
    	}
    }
    end_time1 = clock(); // конец счета для 1 функции 

    qsort(arr,1000, sizeof(int), cmp); //сортировка 

    start_time2 = clock();
    flag = binar(arr);
    end_time2 = clock();

    total_time1 = end_time1-start_time1; //время перебором 
    total_time2 = end_time2-start_time2; //время подитового  
    if(flag == 0){printf("%s","exists");}
    else{printf("%s","doesn't exist");}
    printf("\n%f ",(total_time1/CLOCKS_PER_SEC));
    printf("\n%f ",(total_time2/CLOCKS_PER_SEC));
    return 0;
}
