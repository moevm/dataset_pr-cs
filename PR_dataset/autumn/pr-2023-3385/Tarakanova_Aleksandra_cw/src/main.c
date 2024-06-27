#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "del.h"
#include "free.h"
#include "func1.h"
#include "func2.h"
#include "func3.h"
#include "func4.h"
#include "func9.h"
#include "sio.h"
#include "struct.h"

int main(){
	setlocale(LC_CTYPE,"");
	printf("Course work for option 5.6, created by Tarakanova Aleksandra\n");
    int comand;
    wchar_t s;
   	wscanf(L"%d%c",&comand,&s);
	switch(comand){
    	case 0:{
        	struct Text text=inttext();
			text = delete(text);
    		outtext(text);
    		freetext(text);
       		break;
    	}
    	case 1:{
       		struct Text text=inttext();
            text = delete(text);
			func1(text);
			freetext(text);
        	break;
    	}
    	case 2:{
       		struct Text text=inttext();
			text = delete(text);
			func2(text);
			freetext(text);
       		break;
    	}
    	case 3:{
			struct Text text=inttext();
			text = delete(text);
			func3(text);
			freetext(text);
       		break;
    	}
    	case 4:{
       		struct Text text=inttext();
       		text = delete(text);
            func4(text);
            freetext(text);
        	break;
    	}
    	case 5:{
        	printf("0–Вывод текста после первичной обязательной обработки.\n1-Распечатать каждое слово которое встречается не более одного раза в тексте.\n2-Каждую подстроку в тексте имеющую вид “<день> <месяц> <год> г.” заменить на подстроку вида “ДД/ММ/ГГГГ”.\n3-Отсортировать предложения по произведению длин слов в предложении.\n4-Удалить все предложения, которые содержат символ ‘#’ или ‘№’, но не содержат ни одной цифры.\n");
        	break;
    	}
    	case 9:{
       		struct Text text=inttext();
       		text = delete(text);
            func9(text);
            freetext(text);
        	break;
    	}
    	default:{
        	printf("Error: неизвестная команда\n");
    	}
	}
    return 0;
}
