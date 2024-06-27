#include <stdio.h>
#include <stdlib.h>
#include <time.h>
enum {size = 1000};

int cmp(const void * a, const void * b)
{
  return (*(int*)a - *(int*)b);
}

int main ()
{
  int mas[size];
  for(int i = 0; i < size; i++)
    scanf("%d", &mas[i]);

  qsort(mas, sizeof(mas) / sizeof(int), sizeof(int), cmp);
  clock_t bsrch = clock();
  int key = 0;
  int* res = bsearch(&key, mas, sizeof(mas) / sizeof(int), sizeof(int), cmp);

  if(res != NULL)
    printf("exists\n");
  else
    printf("doesn't exist\n");

  bsrch = clock() - bsrch;
  printf("%f\n",((float)bsrch)/CLOCKS_PER_SEC);

  clock_t slow_srch = clock();
  int flag = 1;

  for(int i = 0; i < size; i++){
    if(mas[i] == key){
      flag = 0;
      printf("exists\n");
      break;
    }
  }
  if(flag)
    printf("doesn't exist\n");

  slow_srch = clock() - slow_srch;
  printf("%f\n",((float)slow_srch)/CLOCKS_PER_SEC);

  return 0;
}