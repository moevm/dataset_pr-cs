#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int main()
{
    int arr[20];
	int switch_num,negative=0,len=0;
	scanf("%d", &switch_num);
	char sep;
	while (sep != '\n'){

		scanf("%d%c", &arr[len], &sep);
		if (arr[len]<0){
			negative++;
		}
        len++;	
	}	
    if (negative)
    {
        switch (switch_num)
        {
        case 0:
            printf("%d\n",index_first_negative(arr, len));
            break;
        case 1:
            printf("%d\n",index_last_negative(arr,len));
            break;
        case 2:
            if (negative==1){
                printf("%d\n",arr[index_first_negative(arr,len)]);
            }
            else{
                printf("%d\n",multi_between_negative(arr,len));
            }
            break;
        case 3:
            printf("%d\n",multi_before_and_after_negative(arr,len));
            break;
        default:
            printf("Данные некорректны");
            break;
        }
    }
    else{
        printf("Данные некорректны");
    }


    return 0;
}

