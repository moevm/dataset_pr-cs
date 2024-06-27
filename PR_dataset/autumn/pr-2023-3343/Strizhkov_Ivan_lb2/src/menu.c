#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
        int n;
        int arr[100];

        scanf("%d", &n);
        int i = 0;
        while (getchar() != '\n') {
                scanf("%d", &arr[i]);
                i++;
        }
        switch (n){
                case 0:
                        printf("%d", abs_max(i, arr));
                        break;
                case 1:
                        printf("%d", abs_min(i, arr));
                        break;
                case 2:
                        printf("%d", diff(i, arr));
                        break;
                case 3:
                        printf("%d", sum(i, arr));
                        break;
                default:
                        printf("%s", "Данные некорректны");
                        break;
        }
	return 0;
}