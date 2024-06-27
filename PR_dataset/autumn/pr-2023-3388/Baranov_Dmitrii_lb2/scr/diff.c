#include<stdio.h>
#include"diff.h"
#include"max.h"
#include"min.h"

int diff(int introValues[], int len) {
	return max(introValues,  len) - min(introValues, len);
}