#include <stdio.h>
#include <stdlib.h>
/*Program lab N1*/
int input(int * array, int size){
    int length=0;
    for(int i = 0; i!= size; i++)
        {
        char end;
        int val;
        scanf("%d%c", &val, &end);
        array[length] = val;
        length++;
        if(end == '\n')
            {break;}
    }
    return length;
}



int oper(int * array, int input_length, int operation)
{
    int abs_max_min[2] = {array[0], array[0]};
    int summer = 0;
    for(int i=0; i!=input_length; i++){
    {
        if(abs(abs_max_min[0]) < abs(array[i]))
        {
            abs_max_min[0] = array[i];
            summer = array[i];
        }
        else
        {
            if(abs(abs_max_min[1]) > abs(array[i]))
            {
                abs_max_min[1] = array[i];
            }
            summer+=array[i];
            }
        }
    }
    switch(operation)
    {
        case 0:
        {
            printf("%d", abs_max_min[0]);
            break;
        }
        case 1:
        {
            printf("%d",abs_max_min[1]);
            break;
        }
        case 2:
        {
            printf("%d",abs_max_min[0]-abs_max_min[1]);
            break;
        }
        case 3:
        {
            printf("%d", summer);
            break;
        }
        default:{
        printf("Данные некорректны");}
    }
    return 0;
}

int main(){
    int size=100;
    int operation;
    scanf("%d", &operation);
    int array[size];
    int input_length=input(array, size);
    oper(array, input_length, operation);
    return 0;
}
