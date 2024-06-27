#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int i = 0, len_q,z;
    int q[101];
    char end1;
	scanf("%d%c", &z, &end1);
	do {
		scanf("%d%c", &q[i], &end1);
		i += 1;
	} while (end1 != '\n');
    len_q = i;
    switch(z)
    {
    case 0:
        printf("%d\n", q[abs_max(q, len_q)]);
        break;
    case 1:
        printf("%d\n", q[abs_min(q ,len_q)]);
        break;
    case 2 :
        printf("%d\n", diff(q, len_q));
        break;
    case 3 :
        printf("%d\n", sum(q , len_q));
        break;
    default:
        printf("Данные некорректны\n");
    }
    return 0;
}
