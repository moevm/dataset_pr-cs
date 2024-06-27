#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

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
