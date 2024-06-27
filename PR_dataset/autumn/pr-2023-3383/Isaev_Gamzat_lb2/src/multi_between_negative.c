#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int mas[], int count) {
    int pr = 1;
    for (int i = index_first_negative(mas, count); i < index_last_negative(mas, count); i++) {
        pr *= mas[i];
    }
    return pr;
}
