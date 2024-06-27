#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int funccompar (const void * key, const void * cmpelem)
{
  if ( *(int*)key <  *(int*)cmpelem ) return 1;
  if ( *(int*)key == *(int*)cmpelem ) return 0;
  if ( *(int*)key >  *(int*)cmpelem ) return -1;
}

int main(){
    int arr[1000];
    
    for (int i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    double t1 = clock(); // замеряем время до
    qsort( arr, 1000, sizeof(int), funccompar);
    double t2 = clock(); // замеряем время после
    double t3 = (t2-t1) / CLOCKS_PER_SEC; // время в секундах
    for (int i = 0; i < 1000; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%f", t3);
}
