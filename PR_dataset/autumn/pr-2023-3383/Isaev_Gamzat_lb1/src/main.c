#include <stdio.h>

int index_first_negative(int mas[], int count) {
    for (int i = 0; i < count; i++) {
        if (mas[i] < 0) {
            return i;
        }
    }
}

int index_last_negative(int mas[], int count) {
    for (int i = count - 1; i >= 0; i--) {
        if (mas[i] < 0) {
            return i;
        }
    }
}

int multi_between_negative(int mas[], int count) {
    int pr = 1;
    for (int i = index_first_negative(mas, count); i < index_last_negative(mas, count); i++) {
        pr *= mas[i];
    }
    return pr;
}

int multi_before_and_after_negative(int mas[], int count) {
    int pr = 1;
    for (int i = 0; i < index_first_negative(mas, count); i++) {
        pr *= mas[i];
    }
    for (int i = index_last_negative(mas, count); i < count; i++) {
        pr *= mas[i];
    }
    return pr;
}

int main() {
    int com, count = 0; //zn 0123
    int mas[100]; //masiv
    scanf("%d", &com); //vvod zn 0123
    char ch;
    for (int i = 0; (ch = getchar()) != '\n'; i++) {
        scanf("%d", &mas[i]);
        count++;
    }
    switch (com) {
        case 0:
            printf("%d\n", index_first_negative(mas, count));
            break;
        case 1:
            printf("%d\n", index_last_negative(mas, count));
            break;
        case 2:
            printf("%d\n", multi_between_negative(mas, count));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(mas, count));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
