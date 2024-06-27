#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int main(){
        int arr[100]={0};
        int n; scanf("%d", &n);
        for(int i=0;i<100;++i){
                scanf("%d",&arr[i]);
                if(getchar()=='\n')
                        break;
        }
        switch(n){
                case 0:
                        printf("%d\n",index_first_negative(arr));
                        break;

                case 1:
                        printf("%d\n",index_last_negative(arr));
                        break;

                case 2:
                        printf("%d\n",sum_between_negative(arr));
                        break;

                case 3:
                        printf("%d\n",sum_before_and_after_negative(arr));
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}

