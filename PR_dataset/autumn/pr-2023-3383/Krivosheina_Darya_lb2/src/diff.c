#include <stdio.h>
#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int massif3[], int len3){
        int difference = max(massif3, len3) - min(massif3, len3);
        return difference;
}
