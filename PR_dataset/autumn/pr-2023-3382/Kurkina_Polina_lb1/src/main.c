#include <stdio.h> 
#include <stdlib.h> // для функции модуля

int index_first_negative(int Mas[100]){
    int ans = -1;
    int i = 0;
    while (i<100){
        if (Mas[i]>= 0){
            i++;
        }else{
            ans = i;
            break;
        }
    }
    return ans;
}

int index_last_negative(int Mas[100], int len){
    int ans = -1;
    int i = 0;
    for(i; i<len; i++){
        if (Mas[i]< 0){
            ans = i;
        }
    }
    return ans;
}

int sum_between_negative(int Mas[100], int len){
    int ans = 0;
    int indexFirst = index_first_negative(Mas);
    if (indexFirst!=-1){
        int indexSec = index_last_negative(Mas, len);
        int i = indexFirst;
        while (i<indexSec){
            ans += abs(Mas[i]);
            i++;
        }
        
    }
    else{
        ans = -1;
    }
    
    return ans;
}

int sum_before_and_after_negative(int Mas[100], int len){
    int ans = 0;
    int indexFirst = index_first_negative(Mas);
    if (indexFirst != -1){
        int indexSec = index_last_negative(Mas, len);
        int i = 0;
        while (i<indexFirst){
            ans += abs(Mas[i]);
            i++;
        }
        i = indexSec;
        while (i<len){     
            ans += abs(Mas[i]);
            i++;
        }
    }
    else{
        ans = -1;
    }
    return ans;
}
void Solution(int a, int Mas[100], int len){
    int ans;
    switch(a){
        case 0:
            ans = index_first_negative(Mas);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        case 1:
            ans = index_last_negative(Mas, len);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        case 2:
            ans = sum_between_negative(Mas, len);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        case 3:
            ans = sum_before_and_after_negative(Mas, len);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        default:
            printf("Данные некорректны");
    
    }
}

int main()
{
    int num, ans;
    int Mas[100];
    char space;
    scanf("%d%c", &num, &space);
    int i = 0, len = 0;
    do{
        scanf("%d%c", &Mas[i], &space);
        i ++;
        len ++;
    } while(space != '\n');
    Solution(num, Mas, len);
    
    return 0;
}
