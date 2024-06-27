#include <stdio.h>

#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main(){
		
	int n;
	int arr[100];
	int length  = 0;
	char str = ' ';
	
 	scanf("%d", &n);

	while (str!='\n') {
		
		scanf("%d%c", &arr[length], &str);
		length++;
	}
	
 switch (n){
  case 0:
      printf("%d\n", max(arr, length)); 
      break;

  case 1:
      printf("%d\n", min(arr, length)); 
      break;

  case 2:
      printf("%d\n", diff(arr, length)); 
      break;

  case 3:
      printf("%d\n", sum(arr, length)); 
      break;
  default:
      printf("?????? ???????????\n"); 
      break;
    }
 return 0;
}
