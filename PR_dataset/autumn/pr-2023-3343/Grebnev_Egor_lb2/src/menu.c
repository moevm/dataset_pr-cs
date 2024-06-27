#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
        int n;
        int arr[100];

        scanf("%d", &n);
        int act_size = 0;
        while (getchar() != '\n') {
                scanf("%d", &arr[act_size]);
                act_size++;
        }
        switch (n){
                case 0:
                        printf("%d", abs_max(act_size, arr));
                        break;
                case 1:
                        printf("%d", abs_min(act_size, arr));
                        break;
                case 2:
                        printf("%d", diff(act_size, arr));
                        break;
                case 3:
                        printf("%d", sum(act_size, arr));
                        break;
                default:
                        printf("%s", "Данные некорректны");
                        break;
        }
	return 0;
}
