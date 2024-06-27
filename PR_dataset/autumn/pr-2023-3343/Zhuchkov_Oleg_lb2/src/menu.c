#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

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
