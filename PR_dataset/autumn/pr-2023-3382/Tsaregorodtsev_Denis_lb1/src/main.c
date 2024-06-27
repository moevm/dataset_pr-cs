#include <stdio.h>
#include <stdlib.h>

int index_first_even(int arr[100]){
	int index=0;
	for(int i=0;i<100;i++){
		if(abs(arr[i])%2==0){
			index=i;
		break;
		}
	}
	return index;
}
int index_last_odd(int arr[100]){
        int index=0;
        for(int i=0;i<100;i++){
                if(abs(arr[i])%2!=0){
                        index=i;
                }
        }
        return index;
}
int sum_between_even_odd(int arr[100]){
	int index1=0;
	int index2=0;
	int sum=0;
        for(int i=0;i<100;i++){
                if(abs(arr[i])%2==0){
                        index1=i;
                break;
                }
        }
	for(int i=0;i<100;i++){
                if(abs(arr[i])%2!=0){
                        index2=i;
                }
        }
	for(int i=index1;i<index2;i++){
		sum+=abs(arr[i]);
	}
	return sum;
}
int sum_before_even_and_after_odd(int arr[100]){
        int index1=0;
        int index2=0;
        int sum=0;
        for(int i=0;i<100;i++){
                if(abs(arr[i])%2==0){
                        index1=i;
                break;
                }
        }
        for(int i=0;i<100;i++){
                if(abs(arr[i])%2!=0){
                        index2=i;
                }
        }
        for(int i=0;i<index1;i++){
                sum+=abs(arr[i]);
        }
	for(int i=index2;i<100;i++){
                sum+=abs(arr[i]);
        }

        return sum;
}

int main(){
	int a;
	scanf("%d",&a);
	int arr[100];
	for(int i=0;i<100;i++){
		arr[i]=0;
	}
	for(int i=0;i<100;i++){
		scanf("%d",&arr[i]);
	}
	switch(a){
		case 0:
			printf("%d\n",index_first_even(arr));
			break;
		case 1:
			printf("%d\n",index_last_odd(arr));
			break;
		case 2:
			printf("%d\n",sum_between_even_odd(arr));
			break;
		case 3:
			printf("%d\n",sum_before_even_and_after_odd(arr));
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}
