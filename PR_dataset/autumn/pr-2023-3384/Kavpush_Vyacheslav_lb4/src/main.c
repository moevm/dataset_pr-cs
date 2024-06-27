#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void * a, const void * b){
    const int A = *(const int *)a;
    const int B = *(const int *)b;
    
    if (B > A){
        return -1;
    } else{
        if (A > B){
            return 1;
        } else {
            return 0;
        }
    }
}

int Bubble(int mas[]){
    for (int i = 0; i < 1000; i++){
        for (int j = i+1; j < 1000; j ++){
            if (mas[i] > mas[j]){
                int c = mas[i];
                mas[i] = mas[j];
                mas[j] = c;
            }
        }
    }
}

int main() {
    int mas[1000];
    int masb[1000];
    time_t Start;
    time_t End;
    double Btime;
    double Qtime;
    
    for (int i = 0; i < 1000; i++){
        scanf("%d", &mas[i]);
        masb[i] = mas[i];
    }
    
    time(&Start);
    Bubble(masb);
    time(&End);
    Btime = End - Start;
    
    time(&Start);
    qsort(mas, 1000, sizeof(int), cmp);
    time(&End);
    Qtime = End - Start;
    
    for (int i = 0; i < 1000; i++)
        printf("%d ", mas[i]);
    printf("\n%f\n%f\n", Btime, Qtime);
}