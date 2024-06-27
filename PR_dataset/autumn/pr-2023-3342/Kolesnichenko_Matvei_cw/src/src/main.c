#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <locale.h>

#include "structures.h"
#include "inputHandler.h"
#include "logHandler.h"
#include "taskHandler.h"

int main(){
    setlocale(LC_ALL, "");
    logCwInfo();
    switchTasks(getTask());
}
