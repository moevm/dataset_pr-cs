#include "max.h"
#include "min.h"
#include "diff.h"

long int diff (int * data, char size){
    return (long int) max(data, size) - min(data, size);
}
