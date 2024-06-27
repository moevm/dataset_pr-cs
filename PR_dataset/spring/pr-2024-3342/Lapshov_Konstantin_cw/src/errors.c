#include "errors.h"

void
showError(char* message, int errorType) {
    printf("%s\n", message);
    exit(errorType);
}