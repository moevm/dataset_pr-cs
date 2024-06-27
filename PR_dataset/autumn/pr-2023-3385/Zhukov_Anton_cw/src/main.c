
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_text.h"
#include "free_text.h"
#include "choose_number.h"
#include "input_text.h"
#include "func1.h"
#include "func2.h"
#include "func3.h"
#include "func4.h"
#include "func5.h"
#include "func9.h"

void main(){
	printf("Course work for option 4.7, created by Anton Zhukov.\n");
	char number = choose_number();
	char** text = NULL;
	int num_str = 0;
	int N = 1;

	switch (number) {
	case '0':
		num_str = input_text(&text);
		print_text(text, num_str);
		break;
	case '1':
		num_str = input_text(&text);
		func1(text, num_str);
		print_text(text, num_str);
		break;
	case '2':
		num_str = input_text(&text);
		func2(text, num_str);
		print_text(text, num_str);
		break;
	case '3':
		num_str = input_text(&text);
		func3(&text, &num_str);
		print_text(text, num_str);
		break;
	case '4':
		num_str = input_text(&text);
		func4(text,num_str);
		print_text(text,num_str);
		break;
	case '5':
		func5();
		break;
	case '9':
		scanf("%d", &N);
		num_str = input_text(&text);
		func9(text, num_str, N);
		print_text(text, num_str);
		break;
	default:
		printf("Error: Wrong command.\n");
	}
	free_text(text, num_str);

}
