#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000


int cmp(const void *a, const void *b){
  const int *first = (const int *)a;
  const int *sec = (const int *)b;
  if(*first > *sec)
      return 1;
  if(*first < *sec)
      return -1;
  return 0;
}


int brut_force(int m[], int n){
  for(int i = 0; i < n; i++){
    if(m[i] == 0) {
       return 1;
    }
    else{
       return 0;
    }
  }
 }


int main(){
  int m[N];
  int *result_b;
  int key = 0;
  for(int i = 0; i < N; i++){
    scanf("%d", &m[i]);
  }
  
  qsort(m, N, sizeof(int), cmp);
  time_t start1, end1;
  start1 = clock();
  int result_brut = brut_force(m, N);
  end1 = clock();
  
  double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
  
  time_t start2, end2;
  start2 = clock();
  result_b = (int*) bsearch(&key, m, N, sizeof(int), cmp);
  end2 = clock();
  
  double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
  
  if(result_b){
    printf("%s\n", "exists");
    printf("%f\n", time2);
    }
  else{
    printf("%s\n", "doesn't exist");
    printf("%f\n", time2);
  }
  
  if(result_brut){
    printf("%s\n", "exists");
    printf("%f\n", time1);
    }
  else{
    printf("%s\n", "doesn't exist");
    printf("%f\n", time1);
  }
 
   return 0;
}
