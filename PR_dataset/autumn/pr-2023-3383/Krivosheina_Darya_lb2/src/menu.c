#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int n;
    scanf("%d", &n);
    
    int massif[100] = {0};
    int len = 0;
    for (int i = 0; i < 100; i++){
        scanf("%d", &massif[i]);
        len++;
        if (getchar() == '\n'){
            break;
        }
    }
    
    if (n == 0){
        printf("%d\n", max(massif, len));
    } else if (n == 1) {
        printf("%d\n", min(massif, len));
    } else if (n == 2) {
        printf("%d\n", diff(massif, len));
    } else if (n == 3) {
        printf("%d\n", sum(massif, len));
    } else {
        printf("Данные некорректны");
    }
}
