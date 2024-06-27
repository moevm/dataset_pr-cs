#include <stdio.h> 
#include <stdlib.h> 
 
int abs_max(); 
 
int abs_min(); 
 
int diff(); 
 
int sum(); 
 
 
int main(){ 
 int n; 
 scanf("%d", &n); 
 int massiv[100]; 
 int y =0; 
 
 while(y <= 100 && scanf("%d", &massiv[y]) ==1){ 
 y++; 
 
 if(getchar() == '\n'){ 
 break; 
        }
    }
 int mas[y]; 
 
    for(int i=0; i < y; i++){
 
        mas[i] = massiv[i];}
 
    int N = y;
    switch(n)
    {
      case 0: printf("%d\n", abs_max(N, mas)); break;
      case 1: printf("%d\n", abs_min(N, mas)); break;
      case 2: printf("%d\n", diff(N, mas)); break;
      case 3: printf("%d\n", sum(N, mas)); break;
      default: printf("Данные некорректны \n"); break;
 
    }
 
 
}
int abs_max(int c, int* arr){
    int mx = abs(arr[0]);
    int mxx = arr[0];
    for(int i=0; i<c; i++){
        if(abs(arr[i]) > mx){
            mx = abs(arr[i]);
            mxx = arr[i];
        }
    }
 
    return mxx;
}
 
int abs_min(int c, int* arr){
    int mn = abs(arr[0]);
    int mnn = arr[0];
    for(int i=0; i<c; i++){
        if(abs(arr[i]) < mn){
            mn = abs(arr[i]);
            mnn = arr[i];
        }
    }
 
    return mnn;
}
int diff(int c, int* arr){
    int d =0;
    d = abs_max(c, arr) - abs_min(c, arr);
    return d;
}
int sum(int c, int* arr){
    int maximus=0;
    maximus=abs_max(c, arr);
    int summar = 0;
    int index = 0;
 
    for(int i=0; i<c; i++){
        if(arr[i]==maximus){
            index = i;
            break;
        }
    }
    for(int i=index; i<c; i++){
        summar += arr[i];
    }
    return summar;
}
