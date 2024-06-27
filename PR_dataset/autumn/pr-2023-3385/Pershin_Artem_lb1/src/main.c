 #include <stdlib.h>
 #include <stdio.h>
 #define N 100

int index_first_negative(int s[],int l){
        for(int i = 0; i < l; i++){
                if(s[i] < 0){
                        return i;
                }
        }
}

int index_last_negative(int s[],int l){
        for(int i = l - 1; i >= 0; i--){
                if(s[i] < 0){
                        return i;
                }
        }
}

int sum_between_negative(int s[],int l){
        int in_f_n = index_first_negative(s,l);
        int in_l_n = index_last_negative(s,l);
        int sum = 0;
        for(int i = in_f_n; i < in_l_n; i++){
                sum += abs(s[i]);
        }
        return sum;
}

int sum_before_and_after_negative(int s[],int l){
        int in_f_n = index_first_negative(s,l);
        int in_l_n = index_last_negative(s,l);
        int sum = 0;
        for(int i = 0; i < in_f_n; i++){
                sum += abs(s[i]);
        }
        for(int j = in_l_n; j < l; j++){
                sum += abs(s[j]);
        }
        return sum;
}

int main(){
        int a,n,c,i=0;
        scanf("%d", &n);
        int s[N];
        while( ( c=getchar() ) != '\n' ){
                scanf("%d",&a);
                s[i] = a;
                i++;
        }
        switch(n){
                case 0:
                        printf("%d", index_first_negative(s,i));
                        break;
                case 1:
                        printf("%d", index_last_negative(s,i));
                        break;
                case 2:
                        printf("%d", sum_between_negative(s,i));
                        break;
                case 3:
                        printf("%d", sum_before_and_after_negative(s,i));
                        break;
                default:
                        printf("Данные некорректны");
        }
        printf("\n");
        return 0;
}
