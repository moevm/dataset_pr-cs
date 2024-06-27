#include "SortFunctions.h"
#include "Common.h"

int DigitsProduct(char* sentence)
{
    int product = 1;
    int len = strlen(sentence);
    for (int i = 0; i < len; ++i)
    {
        if (sentence[i] >= '0' && sentence[i] <= '9')
        {
            int digit = sentence[i] - '0';
            product *= digit;
        }
    }
    return product;
}

int compare(const void* a, const void* b)
{
    char* sentence1 = *(char**)a;
    char* sentence2 = *(char**)b;
    int product1 = DigitsProduct(sentence1);
    int product2 = DigitsProduct(sentence2);
    return product1 - product2;
}

