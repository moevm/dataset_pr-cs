#include <locale.h>

#include "input.h"
#include "output.h"
#include "solution.h"


int main() {
    setlocale(LC_CTYPE, "");

    printCourseInfoAndAuthor();
    
    int testType;
    getTestType(&testType);

    solution(testType);

    return 0;
}