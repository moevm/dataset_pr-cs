#include "show_answer.h"

void show_answer(int ans)
{
    if (ans == INT_MIN)
        printf("Данные некорректны\n");
    else
        printf("%d\n", ans);
}
