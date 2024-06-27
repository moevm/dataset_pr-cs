#include <stdio.h>
#include <stdlib.h>

#define N 100
#define result return res

int abs_max(int arr[],int  i){
	int max_abs=-1e9;
	int res=0;
	for (int k=0; k<i; k++){
		if (abs(arr[k])>max_abs){
			max_abs=abs(arr[k]);
			res=arr[k];
		}
	}
	result;

}

int abs_min(int arr[], int i){
	int min_abs=1e9;
	int res=0;
	for (int k=0; k<i; k++){
		if(abs(arr[k])<min_abs){
			min_abs=abs(arr[k]);
			res=arr[k];
		}
	}

	result;
}

int diff(int arr[], int i){
	int res=abs_max(arr,i)-abs_min(arr,i);
	result;
}

int sum(int arr[], int i){
	int max_abs_index=0;
	int max_abs=abs_max(arr,i);
	int res=0;
	while (max_abs!=arr[max_abs_index]){
		max_abs_index++;
	}
	for (max_abs_index; max_abs_index<i; max_abs_index++){
		res+=arr[max_abs_index];
	}
	result;
}


void input_output(int arr[], int i, int func_id, char space){
	scanf("%d", &func_id);
        while (i<N && space == ' '){
                scanf("%d%c", &arr[i], &space);
                i++;
        }


	switch(func_id) {
		case 0:
			printf("%d\n", abs_max(arr,i));
			break;
		case 1:
			printf("%d\n", abs_min(arr,i));
			break;
		case 2:
			printf("%d\n", diff(arr,i));
			break;
		case 3:
			printf("%d\n",sum(arr,i));
			break;
		default:
			printf("Данные некорректны\n");
	}
}


int main(){
	int arr[N];
	int func_id=0;
	int i=0;
	char space=' ';

	input_output(arr, i, func_id, space);

	return 0;
}
