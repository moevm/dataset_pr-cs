#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int mas[], int count) {
    int pr = 1;
    for (int i = 0; i < index_first_negative(mas, count); i++) {
        pr *= mas[i];
    }
    for (int i = index_last_negative(mas, count); i < count; i++) {
        pr *= mas[i];
    }
    return pr;
}
