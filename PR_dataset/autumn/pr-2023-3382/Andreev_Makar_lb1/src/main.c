#include <stdio.h>

int index_first_negative(int array[], int len){
    int count=0;
    for (int i = 0; i < len; i++)
    {
        if (array[i]<0){
            return count;
        }
        count++;
    }
}
int index_last_negative(int arr[],int len){
    int count=len-1;
    for (int i = count; i >-1; i--)
    {
        if (arr[i]<0)
        {
            return count;
        }
        count--;

    }

}   
int multi_between_negative(int arr[],int len){
    int multi=1;
    int f=index_first_negative(arr, len);
    int s=index_last_negative(arr,len);
    for (int i = f; i < s; i++)
    {
        multi*=arr[i];
    }
    return multi;


}
int multi_before_and_after_negative(int arr[],int len){
    int multi=1;
    int f=index_first_negative(arr, len);
    int s=index_last_negative(arr,len);
    for (int i = 0; i < f; i++)
    {
        multi*=arr[i];
    }
    for (int i = s; i < len; i++)
    {
        multi*=arr[i];
    }
    return multi;


}
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
