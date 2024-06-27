#include <stdio.h>


int mode_0(int* nums, int len);
int mode_1(int* nums, int len);
int mode_2(int* nums, int len);
int mode_3(int* nums, int len);
int min(int num1, int num2);
int max(int num1, int num2);


int main() {
    char ch;
    int nums[101];
    int mode, num;

    int len = 0;
    do {
        scanf("%d%c", &num, &ch);
        nums[len++] = num;
    } while (ch != '\n');

    mode = nums[0];

    switch (mode) { 
        case 0:
            printf("%d\n", mode_0(nums, len));
            break;

        case 1:
            printf("%d\n", mode_1(nums, len));
            break;

        case 2:
            printf("%d\n", mode_2(nums, len));
            break;

        case 3:
            printf("%d\n", mode_3(nums, len));
            break;

        default:
            printf("Данные некорректны\n");
    }
}

int mode_0(int* nums, int len) {
    int mx = nums[1];

    for (int i = 2; i < len; ++i) {
        mx = max(mx, nums[i]);
    }

    return mx;
}

int mode_1(int* nums, int len) {
    int mn = nums[1];

    for (int i = 2; i < len; ++i) {
        mn = min(mn, nums[i]);
    }

    return mn;
}

int mode_2(int* nums, int len) {
    int mn = nums[1];
    int mx = nums[1];

    for (int i = 2; i < len; ++i) {
        mn = min(mn, nums[i]);
        mx = max(mx, nums[i]);
    }

    return mx - mn;
}

int mode_3(int* nums, int len) {
    int mn = nums[1];
    int sumL = 0, sumR = nums[1];

    for (int i = 2; i < len; ++i) {
        if (mn > nums[i]) {
            mn = nums[i];
            sumL += sumR;
            sumR = 0;
        }
        
        sumR += nums[i];
    }

    return sumL;
}

int min(int num1, int num2) {
    if (num1 > num2) return num2;
    return num1;
}

int max(int num1, int num2) {
    if (num1 < num2) return num2;
    return num1;
}