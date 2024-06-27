#include<stdio.h>
#include"max.h"

int max(int introValues[], int len) {
        int maxNum = -9999999;
        for (int i = 0; i < len; i++) {
                if (introValues[i] > maxNum) {
                        maxNum = introValues[i];
                }
        }
        return maxNum;
}
