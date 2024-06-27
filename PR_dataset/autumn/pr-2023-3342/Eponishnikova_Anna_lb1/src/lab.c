#include <stdio.h>
#include <stdlib.h>
#define max_size 100

int abs_max(int array[], int length)
{   
    int abs_max = 0;
    for(int i = 0; i < length; i++){
        if (abs(array[i]) > abs(abs_max)){
            abs_max = array[i];
            
        }
    }
    return abs_max;
}



int abs_min(int array[], int length)
{
    int abs_min = 100000;
    for(int i = 0; i < length; i++){
        if (abs(array[i]) < abs(abs_min)){
            abs_min = array[i];
        }
    }
    return abs_min;
}

int diff(int array[], int length)
{
   return abs_max(array, length) - abs_min(array, length);

}

int sum(int array[], int length)
{
    int sum = 0;
    int abs_maximum = abs_max(array,length);
    for(int i = 0;i <length; i++){
        if(array[i] == abs_maximum){
            for(int n = i; n < length;n++){
                sum += array[n];
            }
            return sum;
        }
    }
}

int main()
{
    int znach = 0;
    int length = 0;
    int array[max_size];
    scanf("%d", &znach);
    int j = 0;
    while(1){
        scanf("%d", &array[j]);
        j++;
        length++;
        if (getchar()=='\n'){
            break;
        }

    }
    switch(znach){
        case 0:
            printf("%d\n",abs_max(array, length));
            break;
        case 1:
            printf("%d\n",abs_min(array, length));
            break;
        case 2:
            printf("%d\n",diff(array, length));
            break;
        case 3:
            printf("%d\n",sum(array, length));
            break;
        default:
            printf("%s\n", "Данные некорректны");
    }

    return 0;
}
