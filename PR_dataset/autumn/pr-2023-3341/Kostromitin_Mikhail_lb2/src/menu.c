#include "Libraries.h"
#include "input.h"
#include "output.h"

int main()
{
    int array[100];
    int size = 0;

	int funcType = input(array, &size);
    output(funcType, size, array);
	return 0;
}
