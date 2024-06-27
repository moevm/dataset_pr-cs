#include <stdio.h>

int index_first_negative(int mas[], int len) {
        int otv = 0;
        for (int j=0; j<len; j++){
                if (mas[j] < 0){
                        otv = j;
                        break;
                }
        }
        return (otv);
}

int index_last_negative(int mas[], int len) {
        int otv = 0;
        for (int j=len; j>=0; j--){
                if (mas[j] < 0){
                        otv = j;
                        break;
                }
        }
        return (otv);
}

int multi_between_negative(int mas[], int len) {
        int f = index_first_negative(mas, len);
        int l = index_last_negative(mas, len);
        int proi = 1;
        for (int i=f; i<l; i++){
                proi *= mas[i];
        }
        return(proi);
}

int multi_before_and_after_negative(int mas[], int len) {
        int f = index_first_negative(mas, len);
        int l = index_last_negative(mas, len);
        int proi = 1;
        for (int i=0; i<f; i++){
                proi *= mas[i];
        }
        for (int i=l; i<len+1; i++){
                proi *= mas[i];
        }
        return(proi);
}

int main() {
        int input[21];
        int mas[20];
        char a;
        int trig;
        int len = 0;

        while (a != '\n') {
                scanf("%d%c", &input[len], &a);
                len++;
        }

        trig = input[0];
        for (int i=0; i<len-1; i++)
                mas[i] = input[i+1];

        switch (trig) {
        case 0:
                printf("%d \n", index_first_negative(mas, len-2));
                break;
        case 1:
                printf("%d \n", index_last_negative(mas, len-2));
                break;
        case 2:
                printf("%d \n", multi_between_negative(mas, len-2));
                break;
        case 3:
                printf("%d \n", multi_before_and_after_negative(mas, len-2));
                break;
        default:
                printf("Данные некорректны \n");
        }

        return 0;
}
