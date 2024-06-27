
#include <stdio.h>
#include <stdlib.h>

int main() {
    int array[100];
    char space;
    int key;
    int i = 0, array_lenght = 0;
    
    
    scanf("%d",&key);
    do{
        scanf("%d%c", &array[i], &space);
        i ++;
        array_lenght ++;
    } while(space != '\n');

    int index_first_negative(int array[]) {
        for (i = 0;i < array_lenght;i++) {
            if (array[i] < 0) {
                return i;
            }    
        }
        return -1;
    }
    
    int index_last_negative(int array[]) {
        int last_index = -1;
        for (i = 0;i < array_lenght;i++) {
            if (array[i] < 0) {
                last_index = i;
            }    
        }
        return last_index;
    }
    
    int sum_between_negative(int array[]) {
        int sum = 0;
        int first_index = index_first_negative(array);
        int last_index = index_last_negative(array);
        while (first_index < last_index) {
            sum = sum + abs(array[first_index]);
            first_index++;
        }
        return sum;
    }

    int sum_before_and_after_negative(int array[]){
        int between = sum_between_negative(array);
        int sum = 0;
        for (i = 0;i < array_lenght;i++){
            sum = sum + abs(array[i]);
        }
        sum = sum - between;
        return sum;
    }

    switch(key){
        case 0:
            printf("%d",index_first_negative(array));
            break;
        case 1:
            printf("%d",index_last_negative(array));
            break;
        case 2:
            printf("%d",sum_between_negative(array));
            break;
        case 3:
            printf("%d",sum_before_and_after_negative(array));
            break;
        default:
            printf("%s","Данные некорректны");
        }
    
    
}