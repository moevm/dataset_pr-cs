#include <locale.h>
#include "welcome.h"
#include "action_selection.h"

int main(){
	setlocale(LC_ALL, "");
	welcome();
	action_selection();
	return 0;
}
