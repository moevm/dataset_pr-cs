#include <locale.h>
#include "headers/give-initial-information.h"
#include "headers/process-command.h"
#include "headers/structs.h"


int main(){
    setlocale(LC_ALL, "");
    give_initial_information();
    process_commands();
    return 0;
}
