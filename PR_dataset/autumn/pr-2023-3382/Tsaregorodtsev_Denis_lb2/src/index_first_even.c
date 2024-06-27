#include <stdio.h>
#include <stdlib.h>
int index_first_even(int arr[100]){
	int index=0;
	int i;
	for(i=0;i<100;i++){
		if(abs(arr[i])%2==0){
			index=i;
		break;
		}
	}
	return index;
}
