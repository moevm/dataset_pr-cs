#include <stdio.h>


int max(int arr[], int n){
	int maxx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > maxx)
			maxx = arr[i];
	return maxx;
}

int min(int arr[], int n){
	int minn = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] < minn)
			minn = arr[i];
	return minn;
}

int diff(int arr[], int n){
	return max(arr, n) - min(arr, n);
}

int sum(int arr[], int n){
	int minn = min(arr, n), summ = 0;
	for (int i = 0; i < n; i++)
		if (arr[i] == minn) break;
		else summ += arr[i];
	return summ;	
}

int main(){
    int mode, arr[100] = {}, i = 0;
    char s;
    scanf("%d", &mode);
    while(scanf("%d%c", &arr[i++], &s)){
    	if (s=='\n') break;
    }
    switch (mode){
    	case 0:
    		printf("%d\n", max(arr, i));
    		break;
    	case 1:
    		printf("%d\n", min(arr, i));
    		break;
    	case 2:
    		printf("%d\n", diff(arr, i));
    		break;
    	case 3:
    		printf("%d\n", sum(arr, i));
    		break;
    	default:
    		printf("Данные некорректны\n");
    }
    return 0;
}

