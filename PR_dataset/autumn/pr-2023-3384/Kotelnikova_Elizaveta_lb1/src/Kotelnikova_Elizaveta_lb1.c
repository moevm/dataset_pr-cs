#include <stdio.h>
#include <stdlib.h>
 int index_first_negative(int kolvo_elem, int arr[100]){
    int ind_fir_negat=0;
    for (ind_fir_negat; ind_fir_negat<kolvo_elem; ++ind_fir_negat){
        if (arr[ind_fir_negat]<0){
            return ind_fir_negat;
        }
    }
 }

 int index_last_negative(int kolvo_elem, int arr[100]){
    int ind_last_neg=kolvo_elem-1;
    for (kolvo_elem-1; ind_last_neg>=0; --ind_last_neg){
        if (arr[ind_last_neg]<0){
            return ind_last_neg;
        }
    }
}
int sum_between_negative(int ind_fir_negat, int ind_last_neg, int arr[100]){
    int summa=0;
    for (ind_fir_negat; ind_fir_negat<ind_last_neg; ++ind_fir_negat){
        summa=summa+abs(arr[ind_fir_negat]);
    }
    printf("%d\n", summa);
    return 0;
}

int sum_before_and_after_negative(int ind_fir_negat, int ind_last_neg, int kolvo_elem, int arr[100]){
    int summa1=0;
    int l=0;
    for (l; l<ind_fir_negat; ++l){
        summa1=summa1+abs(arr[l]);
        }
    int l1=ind_last_neg; 
    for (l1; l1<kolvo_elem; ++l1){
        summa1=summa1+abs(arr[l1]);
        }
    printf("%d\n", summa1);
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    if (N!=0 && N!=1 && N!=2 && N!=3){
        printf("Данные некорректны");
        return 0;
        }
    int kolvo_elem=0;
    char st=' ';
    int arr[100];
    while (kolvo_elem<100){
        scanf("%d%c", &arr[kolvo_elem], &st);
        kolvo_elem=kolvo_elem+1;
        if (st=='\n'){
            break;
            }
        }
    if (N==0){
        printf("%d\n", index_first_negative(kolvo_elem, arr));
        }
    else if (N==1){
        printf("%d\n",index_last_negative(kolvo_elem, arr));
        }
    else if (N==2){
        int ind_fir_negat=index_first_negative(kolvo_elem, arr);
        int ind_last_neg=index_last_negative(kolvo_elem, arr);
        sum_between_negative(ind_fir_negat, ind_last_neg, arr);
        }
    else if (N==3){
        int ind_fir_negat=index_first_negative(kolvo_elem, arr);
        int ind_last_neg=index_last_negative(kolvo_elem, arr);
        sum_before_and_after_negative(ind_fir_negat, ind_last_neg, kolvo_elem, arr);
        }
    return 0;
}