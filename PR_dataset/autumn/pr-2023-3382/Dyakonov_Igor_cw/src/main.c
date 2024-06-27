#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 


char** push_back(char** pp, int n, char* p_buf)
{
	char** m;
	m = (char**)realloc(pp, sizeof(char*) * (++n));

	m[n - 1] = p_buf;

	return m;
}
char* push_back_1(char* buf, int n, char ch)
{
	if (buf == NULL)
	{
		buf = (char*)malloc(sizeof(char) * 2);
		buf[0] = ch;
		buf[1] = '\0';
	}
	else
	{
		buf = (char*)realloc(buf, sizeof(char) * (n + 2));
		buf[n] = ch;
		buf[n + 1] = '\0';
	}

	return  buf;
}


void free_arr(char** arr_str, int n_arr)
{
	for (int i = 0; i < n_arr; i++)
	{
		if (arr_str[i] != NULL) free(arr_str[i]);
	}

	free(arr_str);
}


unsigned short counter_words(char* sentence)
{
	char* c_sentence;
	c_sentence  = strdup((const char*)sentence);

	char* p = strtok(c_sentence, " .,");
	if (p == NULL)
	{
		return 0;
	}

	unsigned short k = 1;

	while (1)
	{
		p = strtok(NULL, " .,");
		if (p == NULL) break;
		k++;
	}

	return k;
}




unsigned short counter_big_letters(const void* _s)
{
	const char* s = (const char*)_s;
	int k = 0;
	while (*s)
	{
		if (isalpha(*s) == 1)  k++;
		//if ((*s) >= 'A' && (*s) <= 'Z') k++;
		s++;
	}
	return k;


}
int  comp(char* a, char* b)
{
	return counter_big_letters(a) - counter_big_letters(b);
}
void my_sort(char** arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (comp(arr[j], arr[j + 1]) > 0)
			{
				char* tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}

		//print_arr(arr, n);
	}
}




int compare(const void* a, const void* b)   // функция сравнения элементов массива
{
	return counter_big_letters(*(char**)a) - counter_big_letters(*(char**)b);


	//return strcmp(*(char**)x2, *(char**)x1);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}


int compare2(const void* a, const void* b)   // функция сравнения элементов массива
{
	return  strlen(*(char**)b) - strlen(*(char**)a);


	//return strcmp(*(char**)x2, *(char**)x1);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

void sort_sentence(char* sentence)
{
	char** arr_words = NULL;
	int    arr_n = 0;

	char* c_sentence; 
	c_sentence  = strdup((const char*)sentence);

	char* p = strtok(c_sentence, " .,");
	if (p == NULL)
	{
		return;
	}
	arr_words = push_back(arr_words, arr_n++, p);


	unsigned short k = 1;

	while (p = strtok(NULL, " .,"))
	{
		k++;
		arr_words = push_back(arr_words, arr_n++, p);
	}


	//my_sort(arr_words, k);
	qsort(arr_words, k, sizeof(char*), compare);

	sentence[0] = '\0';

	for (int i = 0; i < k - 1; i++)
	{
		strcat(sentence, arr_words[i]);
		strcat(sentence, " ");
	}

	strcat(sentence, arr_words[k - 1]);
	strcat(sentence, ".");
}

void  fun1(char** arr_str, int* p_n)
{
	int n = *p_n;

	for (int i = 0; i < n; i++)
	{
		if (arr_str[i] == NULL) continue;

		if ((i + 1) % 2 == 0)
		{
			if (counter_words(arr_str[i]) % 2 == 0)
			{
				free(arr_str[i]);
				arr_str[i] = NULL;
				n--;
			}
		}
	}

	*p_n = n;
}
void  fun2(char** arr_str, int* p_n)
{
	for (int i = 0; i < *p_n; i++)
	{
		if (arr_str[i] != NULL)
		{
			sort_sentence(arr_str[i]);
		}
	}

}
char* fun3(char* str)
{
	char* c_str;
	c_str  = strdup((const char*)str);


	char* s = NULL;
	char* p = strtok(str, " ,.");




	if (strlen(p) <= 3)
	{
		s = strdup("Less Then 3");
	}
	else
	{
		s = strdup((const char*)p);
	}


	while (p = strtok(NULL, " ,."))
	{
		if (strlen(p) <= 3)
		{
			s = (char*)realloc(s, strlen(s) + 1 + 12);

			if (c_str[p - str - 1] == ' ')  strcat(s, " Less Then 3");
			else                            strcat(s, ",Less Then 3");
		}
		else
		{
			s = (char*)realloc(s, strlen(s) + 1 + 1);

			if (c_str[p - str - 1] == ' ')   strcat(s, " ");
			else                             strcat(s, ",");

			s = (char*)realloc(s, strlen(s) + 1 + strlen(p));
			strcat(s, p);
		}
	}

	s = (char*)realloc(s, strlen(s) + 1 + 1);
	strcat(s, ".");


	free(c_str);
	return s;
}




char* fun_substring(char* str)
{
	//cout << "---> " << str << endl;

	char* c_str = strdup((const char*)str);
	char** arr_sub_str = NULL;
	int    n = 0;

	//arr_sub_str = push_back(arr_sub_str, n++, strtok(c_str, "0123456789."));
	//cout << arr_sub_str[0] << endl;

	char* p1 = NULL, * p2;

	int flag1 = 0;
	int in_str = 0;
	/*
	234dfsfsdffds
	11qqqqq   asd1111aaa   aaaa2bbbbbb3333qqqqq5ccccwwwww
	*/
	while (*str)
	{
		if (isdigit(*str))
		{
			if (in_str == 1 && flag1 == 1)
			{

				arr_sub_str = push_back(arr_sub_str, n++, p1);
				*str = '\0';
			}

			flag1 = 1;
			in_str = 0;
		}
		else
		{
			if (in_str == 0 && flag1 == 1)
			{
				p1 = str;
			}

			in_str = 1;
		}
		str++;
	}

	/*
	for (int i = 0; i < n; i++)
	{
		printf("*** %s\n", arr_sub_str[i]);
	}
	*/



	/*
	char* p;
	while (p = strtok(NULL, "0123456789."))
	{
		arr_sub_str = push_back(arr_sub_str, n++, p);
		//cout << arr_words[n -1] << endl;
	}


	//aaa.111bbb.ccc111.111yyy111

	cout << "n = " << n << endl;
	cout << "--------------" << endl;

	if (n == 1)
	{

			//if (isdigit(str[(arr_sub_str[0] + strlen(arr_sub_str[0])) - c_str]) == false) return 0;




		if (arr_sub_str[0] - c_str)
		{
			return 0;
		}
	}

	*/







	int   l_max = 0;
	char* p_max_substring = NULL;


	for (int i = 0; i < n; i++)
	{
		if (arr_sub_str[i] != NULL)
		{
			//cout << arr_words[i] << endl;

			if (strlen(arr_sub_str[i]) > l_max)
			{
				l_max = strlen(arr_sub_str[i]);
				p_max_substring = arr_sub_str[i];
			}
		}
	}
	/*
	xxxxxx.1xxxxxx.xxxxxx3.2xxx3.yyy yyy.qqqqqq4545qqqqq q q qqqqqq

	*/
	/*
	xxx xxxxx xxx.aaa aa 123bbbbbb bbbb b b b5555 iiii444 tttt.tttt 1aaa34. xxxx45yyyyyyy. 12bbbb bb45.
	*/


	p_max_substring = strdup(p_max_substring);

	free(c_str);

	return p_max_substring;
}



void  fun4(char** arr_str, int* p_n)
{
	char** arr_substring = (char**)malloc(sizeof(char*) * (*p_n));

	int k = 0;
	for (int i = 0; i < *p_n; i++)
	{
		if (arr_str[i] == NULL) continue;

		char* p = fun_substring(arr_str[i]);
		if (p != NULL)
		{
			arr_substring[k++] = p;
		}
	}

	qsort(arr_substring, k, sizeof(char*), compare2);


	//printf("!!!!!!!qsort!!!!!! k = %i\n", k);


	for (int i = 0; i < k; i++)
	{
		printf("%s\n", arr_substring[i]);
	}
}


void printf_arr(char** arr_str, int n_arr)
{
	for (int i = 0; i < n_arr; i++)
	{
		if (arr_str[i] != NULL)
		{
			printf("%s\n", arr_str[i]);
		}
	}
	printf("\n");
	//printf("!!!!!!!!!!!!\n\n");
}


void cleaning_arr_str(char** arr_str, int n)
{


	for (int i = 0; i < n - 1; i++)
	{
		char* p1 = strdup((const char*)arr_str[i]);
		strupr(p1);


		for (int j = i + 1; j < n; j++)
		{

			char* p2 = strdup((const char*)arr_str[j]);
			strupr(p2);

			if (strcmp(p1, p2) == 0)
			{
				free(arr_str[i]);
				arr_str[i] = NULL;

				free(p2);
				break;
			}

			free(p2);
		}

		free(p1);
	}

}


int main()
{

	char* buf = NULL;
	int   n_buf = 0;

	char** arr_str = NULL;
	int    n_arr = 0;

	_Bool flag = 0;
	_Bool flag_nn = 0;


	printf("Course work for option 4.23, created by Dyakonov Igor .\n");
	int command;
	scanf("%i", &command);


	while (!flag_nn)
	{
		char ch = getchar();

		switch (ch)
		{
		case '\n':
		{
			if (flag == 1)
			{
				if (buf != NULL) arr_str = push_back(arr_str, n_arr++, buf);

				buf = NULL;
				n_buf = NULL;

				flag_nn = 1;

			}
			else
			{
				flag = 1;
			}

			break;
		}
		case '.':
		{

			buf = push_back_1(buf, n_buf++, ch);
			arr_str = push_back(arr_str, n_arr++, buf);

			buf = NULL;
			n_buf = NULL;

			break;
		}
		default:
		{
			buf = push_back_1(buf, n_buf++, ch);
			flag = 0;

			break;
		}
		}
	}




	if (command == 0)
	{
		cleaning_arr_str(arr_str, n_arr);
		printf_arr(arr_str, n_arr);
	}
	else if (command == 1)
	{
		fun1(arr_str, &n_arr);
		printf_arr(arr_str, n_arr);
	}
	else if (command == 2)
	{
		fun2(arr_str, &n_arr);
		printf_arr(arr_str, n_arr);
	}
	else if (command == 3)
	{
		for (int i = 0; i < n_arr; i++)
		{
			if (arr_str[i] != NULL)
			{
				char* p = fun3(arr_str[i]);
				printf("%s", p);
				free(p);
			}
		}
	}
	else if (command == 4)
	{
		fun4(arr_str, &n_arr);
		printf_arr(arr_str, n_arr);
	}
	else if (command == 5)
	{
		printf("0 - text output after initial mandatory processing.\n1 - Delete all even-numbered sentences that have an even number of words.\n2 - Sort all words in sentences by increasing number of uppercase letters in the word.\n3 - Replace all words in the text that are no more than 3 characters long with the substring “Less Then 3”.\n4 - Find in each sentence a line of maximum length that begins and ends with a number. Print found substrings in descending order of substring length.\n5 - displaying help about the functions that the program implements.\n");
	}
	else
	{
		printf("Error: Invalid option.\n");
	}

	///sss ssss

	free_arr(arr_str, n_arr);
}

