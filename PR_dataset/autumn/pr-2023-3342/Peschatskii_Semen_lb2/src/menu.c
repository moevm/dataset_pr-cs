#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "output.h"
#define N 100
int main(){int option; int num_list[N];
    int list_len=input(&option, num_list);
    output(option, num_list, list_len);
    return 0;
}
