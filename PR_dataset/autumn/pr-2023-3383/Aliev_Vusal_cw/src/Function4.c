#include "Common.h"
#include "Function4.h"

int cmp(const void* a, const void* b) {
    const char** f = (const char**)a;
	const char** s = (const char**)b;

	int index1 = 4; int index2 = 4;

	int first = 0, second = 0;

	if (strlen(*f)-1< 5){ //если точка 5 символ, то будет -1.
		first = -1;
	}
	else if (strchr(" ,\t\n", (*f)[index1])){
		first = (*f)[++index1];
	}
	else{
		first = (*f)[index1];
	}
	if (strlen(*s) -1 < 5){
		second = -1;
	}
	else if (strchr(" ,\t\n", (*s)[index2])){
		second = (*s)[++index2];
	}
	else{
		second = (*s)[index2];
	}
	if (second > first ){
		return 1;
	}
	if (second < first){
		return -1;
	}
	return 0;
}

void Function4(char** text,int* count_sent) {
	qsort(text, *count_sent, sizeof(char*), cmp);
}