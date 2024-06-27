#include "Output.h"

void Output(int *comand){
	char **input;
        int len_text = 0;
	switch(*comand){
		case 0:
			input = readText(&len_text);
			input = processText(&len_text, input);
			for (int i = 0; i < len_text; i++){
                                printf("%s\n", input[i]);

                        };
			if (!len_text){
                                printf("Error: отсутствует текст\n");
                                break;
                        }
                        freeText(input, len_text);
                        break;

		case 1:            
	    input = readText(&len_text);
            input = processText(&len_text, input);
            char *new_str;
            char *find = "Robin";
            char *replace = "I am Batman";
            for (int i = 0; i < len_text; i++){
                new_str = Robin_to_Batman_str(input[i], find, replace);
                if (new_str != NULL){
                    printf("%s\n", new_str);
		    free(new_str);
                }
                else{
                    printf("%s\n", input[i]);
		}
            };
            if (!len_text){
                printf("Error: ничего не выведено");
               	break;
	    };
	    freeText(input, len_text);
            break;

                case 2:
                        input = readText(&len_text);
                        input = processText(&len_text, input);

                    input = Sort_by_coma(&len_text, input);
                        for (int i = 0; i < len_text; i++){
                                printf("%s\n", input[i]);
                        }
                        if (!len_text){
                                printf("Error: отсутствует текст\n");
                                break;
                        }
                        freeText(input, len_text);
                        break;

                case 3:
                        input = readText(&len_text);
                        input = processText(&len_text, input);
                        input = Delete_13(&len_text, input);
                        for (int i = 0; i < len_text; i++){
                printf("%s\n", input[i]);
            }
                        if (!len_text){
                                printf("Error: отсутствует текст\n");
                                break;
                        }
                        freeText(input, len_text);
break;
                case 4:
                        input = readText(&len_text);
                        input = processText(&len_text, input);
                        input = First_vowel(&len_text, input);
                        for (int i = 0; i < len_text; i++){
                                printf("%s\n", input[i]);
                        }
                        if (!len_text){
                                printf("Error: отсутствует текст\n");
 				break;
                        }
                        freeText(input, len_text);
                        break;
		case 8: ;

                        int num;
                        scanf("%d\n", &num);
                        input = readText(&len_text);
                        input = processText(&len_text, input);
                        for(int i = 0; i < len_text; i++){
                                for(int x = 0; x < num - 1; x++){
                                        int str_len = strlen(input[i]);
                                        input[i][str_len - 1] = ' ';
                                        printf("%s", input[i]);
                                }
                                int str_len2 = strlen(input[i]);
                                input[i][str_len2 - 1] = '.';
                                printf("%s\n", input[i]);
                        }
                        freeText(input, len_text);
                        break;

                case 5:
                        printf(" 0 - вывод текста после первичной обязательной обработки\n 1 Robin_to_Batman() - Заменяет в тексте подстроки “Robin” (могут быть внутри слова) на подстроку “I am Batman”.\n 2 Sort_by_comma() - Сортирует предложения по увеличению количества запятых в предложении.\n 3 Delete_if_13() - Удаляет все предложения в которых сумма цифр в предложении равняется 13.\n 4 First_Vowel()  - Выводит все предложения в которых первое слово начинается с гласной буквы или цифры.\n");
                        break;
		default:
                       printf("Error: введённой команды (%d) не существует\n", *comand);
	}
}
