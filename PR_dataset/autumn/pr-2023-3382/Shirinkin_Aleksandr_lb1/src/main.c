#include <stdio.h>
#include <stdlib.h>
int abs_max(int q[], int len_q) {
	int q_max = 0, max_i;
    for(int i = 0; i < len_q;i++){
        if (abs(q[i]) > q_max){
                q_max = abs(q[i]);
                max_i = i;
        }
    }
	return max_i;
}	
int abs_min(int q[], int len_q){
    int q_min = 100000;
    int min_i;
    for(int i = 0; i < len_q; i++){
        if (abs(q[i]) < q_min){
            q_min = abs(q[i]);
            min_i = i;
        }
    }
    return min_i;
}
int diff(int q[], int max_i, int min_i) {
	return (q[max_i] - q[min_i]);
}
int sum(int q[], int len_q, int max_i) {
	int sum_m = 0;
	for (int i = max_i; i < len_q; i++) {
		sum_m += q[i];
	}
	return sum_m;  
}
int main(){
    int i = 0,max_ind, min_ind, len_q,z;
    int q[101];
    char end1;
	scanf("%d%c", &z, &end1);
	do {
		scanf("%d%c", &q[i], &end1);
		i += 1;
	} while (end1 != '\n');
    len_q = i;
    max_ind = abs_max(q, len_q); 
    min_ind = abs_min(q ,len_q); 
    switch(z)
    {
    case 0:
        printf("%d\n", q[max_ind]);
        break;
    case 1:
        printf("%d\n", q[min_ind]);
        break;
    case 2 :
        printf("%d\n", diff(q, max_ind, min_ind));
        break;
    case 3 :
        printf("%d\n", sum(q , len_q, max_ind));
        break;
    default:
        printf("Данные некорректны\n");
    }
    return 0;
}
