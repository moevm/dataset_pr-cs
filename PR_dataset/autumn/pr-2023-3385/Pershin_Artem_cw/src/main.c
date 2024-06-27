#include "structs.h"
#include "free.h"
#include "InOut.h"
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main(){
    setlocale(LC_CTYPE,"");
    printf("Course work for option 5.4, created by Pershin Artem\n");
    int comand;
    char c;
    wscanf(L"%d%c",&comand,&c);
    switch(comand){
        case 0:{
            struct Text text=intext();
            struct Text newtext;
            newtext=format(text);
            outtext(newtext);
            freetext(text);
            break;
        }
        case 1:{
            struct Text text=intext();
            struct Text newtext;
            newtext=format(text);
            func1(newtext);
            outtext(newtext);
            freetext(text);
            break;
        }
        case 2:{
            struct Text text=intext();
            struct Text newtext;
            newtext=format(text);
            func2(newtext);
            outtext(newtext);
            freetext(text);
            break;
        }
        case 3:{
            struct Text text=intext();
            struct Text newtext;
            newtext=format(text);
            func3(newtext);
            freetext(text);
            break;
        }
        case 4:{
            struct Text text=intext();
            struct Text newtext;
            newtext=format(text);
            func4(newtext);
            outtext(newtext);
            freetext(text);
            break;
        }
	case 9:{
		struct Text text = intext();
		struct Text newtext;
		newtext = format(text);
		func9(newtext);
		outtext(newtext);
		freetext(text);
		break;
	}
        case 5:{
            printf("0 - Вывод текста после первичной обязательной обработки. \n1 - В каждом предложении заменить первое слово на второе слово из предыдущего предложения.\n2 - Отсортировать предложения по длине третьего слова. Если слов меньше трех, то длина третьего слова равняется нулю.\n3 - Вывести на экран все предложения, в которых в середине слова встречаются цифры. Данные слова нужно выделить зеленым цветом.\n4 - В каждом предложении, в слове, все символы, которые встречаются несколько раз подряд заменить одним таким символом.\n");
            break;
        }
        default:{
            printf("Error: неизвестная команда\n");
        }
    }
    return 0;
}
