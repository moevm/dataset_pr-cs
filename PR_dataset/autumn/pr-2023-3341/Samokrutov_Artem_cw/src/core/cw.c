#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>

#include "cwerror.h"
#include "cwfuncs.h"
#include "cwio.h"
#include "cwprocessing.h"
#include "cwstructures.h"

int main(void) {
	setlocale(LC_CTYPE, "");
	
	print_cw_info();

	int task;
	get_task(&task);

	Text *text = NULL;
	task_match(text, task);
}
