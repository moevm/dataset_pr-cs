#include <stdio.h>
#include "abs_max.h" 
#include "abs_min.h" 
#include "diff.h" 
#include "sum.h" 

int main(){
	int key, array[100], size = 0;
	char stop;
	scanf("%d", &key);
	for (int count = 0; count<100; count++){
		scanf ("%d%c", &array[count],&stop);
		size++;
		if (stop == '\n') break;
	}
	
	int new_array[size];
	for (int count = 0; count<size; count++){
 		new_array[count] = array[count];
	}

	switch (key){
		case 0: 
			printf("%d\n", new_array[abs_max(new_array, size)]);
			break;
		case 1:
			printf("%d\n", new_array[abs_min(new_array,size)]);
			break;
			
		case 2:
			printf("%d\n", diff(new_array, size));
			break;
			
		case 3:
			printf("%d\n", sum(new_array, size));
			break; 
		default: 
			printf("Данные некорректны\n");
			break;	
	} 
	return 0;
}
