#include<stdio.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define TIGER "HiddenTiger"
void spravka()
{
	printf("0 - Вывод текста после первичной обработки(удаление повторяющихся предложений.\n");
	printf("1 - Удалить все символы в начале и в конце предложения так, чтобы в итоге первый и последний символы предложений были различны.\n");
	printf("2 - Отсортировать все слова в предложении в лексикографическом порядке.\n");
	printf("3 - Удалить все предложения, в которых хотя бы одно слово является палиндромом.\n");
	printf("4 - Вывести все предложения, в которых присутствует слово HiddenTiger, но при этом не являющееся первым словом предложения.\n");
}
char** input_text(int* number_of_sentences) 
{
	int BASE_WIDTH = 10, BASE_HEIGHT = 10;
	char** our_text = (char**)malloc(BASE_HEIGHT * sizeof(char*));
	if(our_text==NULL) printf("Error: error memory allocating");
	char* sentence = (char*)malloc(BASE_WIDTH * sizeof(char));
	if(sentence==NULL) printf("Error: error memory allocating");
	char alpha;
	int sentences_count = *number_of_sentences;
	int length_of_sentence = 0;
	char TwoLastEnters[2];//Создание массива из двух символов, проверяющего парность символа переноса строки.
	our_text[sentences_count] = sentence;
	while (1) 
        {
		alpha = getchar();
		TwoLastEnters[0] = TwoLastEnters[1];
		TwoLastEnters[1] = alpha;
		if (TwoLastEnters[0] == '\n' && TwoLastEnters[1] == '\n') 
                {
			our_text[sentences_count][length_of_sentence - 1] = 0;
			if (length_of_sentence - 2 >= 0) sentences_count += 1;
			*number_of_sentences = sentences_count;
			return our_text;//Возвращение введенного текста после двойного энтера
		}

		if ((length_of_sentence == 0 && alpha == '\t')||(length_of_sentence == 0 && alpha == '\n')||(length_of_sentence == 0 && alpha == ' ')||(length_of_sentence == 0 && alpha == '.'))
		continue;//Игнорирование пробелов, табов, символов переноса в начале предложения
		if (length_of_sentence > BASE_WIDTH - 2) 
                {
			BASE_WIDTH += 10;
			sentence = (char*)realloc(sentence, sizeof(char) * BASE_WIDTH);
			if(sentence==NULL) printf("Error: error memory allocating");
			our_text[sentences_count] = sentence;
			//Перераспределение памяти для предложения в случае переполнения строки
		}
		our_text[sentences_count][length_of_sentence] = alpha;
		length_of_sentence++;

		if (alpha == '.'|| (alpha=='\n' && sentences_count==0)) {
			our_text[sentences_count][length_of_sentence] = 0;
			int flag = 1;//Создание флага
			for (int i = 0; i < sentences_count; i++) 
                        {
				if (!strcasecmp(our_text[i], our_text[sentences_count])) 
                                {
					flag = 0;//Инициализация флага нулем в случае равенства предложений.
					break;//Поскольку цикл вложенный, то использование break вместо continue
					//В цикле текущее предложение сравнивается только с каждым введенным ранее. С более поздними сравнение, очевидно, необязательно.
				}
			}
			if (flag==1) 		//В данном условии проверяется значение флага
			sentences_count++;		//В случае, если введенное предложение не является копией одного из предыдущих, число предложений увеличивается
			else 				//В противном случае память, выделенная для предложения, освобождается, т.е предложение не сохраняется в памяти.
			free(our_text[sentences_count]);

			if (sentences_count > BASE_HEIGHT - 2) 
                        {
				BASE_HEIGHT += 10;
				our_text = (char**)realloc(our_text, sizeof(char*) * BASE_HEIGHT);
				if(our_text==NULL) printf("Error: error memory allocating");
			}//Перераспределение памяти для массива указателей в случае переполнения

			BASE_WIDTH = 10;
			sentence = (char*)malloc(BASE_WIDTH * sizeof(char));
			if(sentence==NULL) printf("Error: error memory allocating");//Выделение памяти для следующего предложения
			our_text[sentences_count] = sentence;
			length_of_sentence = 0;
		}
	}
}
void base_output_function(char** text, int len) 
{
	for (int i = 0; i < len; i++) 
    {
		printf("%s\n", text[i]);
		free(text[i]);
	}
	free(text);
}
void tiger_output_function(char** text, int len)
{
	for(int i=0;i<len;i++)
        {
		if(strstr(text[i], TIGER) && (strlen(text[i]) - strlen(strstr(text[i], TIGER)))!=0)
		printf("%s\n", text[i]);
		free(text[i]);
	}
	free(text);
}
int is_palindrome(char* word)
{
    int len = strlen(word)-1;
    for(int i=0;i<strlen(word)/2;i++)
    {
        if(tolower(word[i])!=tolower(word[len-i]))
            return 0;//no palindrome
    }
    return 1;//palin.
}
int has_palindrome(const char* sent)
{
    char copy_sent[strlen(sent)+1];
    strcpy(copy_sent, sent);
    char* word;
    word=strtok(copy_sent, " ,.");
    while(word!=NULL)
    {
        if(is_palindrome(word)==1)
        return 0;//Has palindrome
        word=strtok(NULL, " ,.");
    }
    return 1;//no palindrome in sentence
}
void output_without_palindrome(char** text, int len)
{
        for(int i=0;i<len;i++)
        {
                if(has_palindrome(text[i])==1)
                        printf("%s\n", text[i]);
                free(text[i]);
        }
        free(text);
}
void without_palindrome_symbols(char* sentence)
{
        int length = strlen(sentence);
        int end = length - 1;
        int i = 0;
        int flag = 0;
        if(sentence[end-1]==' ')
                flag=1;
        while(tolower(sentence[i])==tolower(sentence[end-i-flag-1]))
                i++;
        for(int j = i;j<=end-flag-i-1; j++)
                printf("%c", sentence[j]);
        printf(".\n");
}
void output_without_palindrome_symbols(char** text, int len)
{
	for(int i=0;i<len;i++){
		without_palindrome_symbols(text[i]);
		free(text[i]);
	}
	free(text);
}
void sort_words(char* sentence)
{
	char *words[100];
	int word_count=0;
	char *word=strtok(sentence, " .,-");
	while(word != 0)
	{
		words[word_count++]=word;
		word = strtok(NULL, " .,-");
	}
	for(int i=0; i<word_count;i++){
		for(int j=i+1; j<word_count;j++){
			if(strcasecmp(words[i], words[j])>0){
				char* temp = words[i];
				words[i] = words[j];
				words[j] = temp;
			}
		}
	}
	for(int i = 0; i<word_count;i++)
	printf("%s ", words[i]);
	printf(".\n");
}
void output_in_order(char** text, int len){
	for(int num = 0; num<len; num++){
		sort_words(text[num]);
		free(text[num]);
	}
	free(text);
}


int Constant(char* sentence){
    int cons=0;
    int i=0;
    while(sentence[i]!='\n'){
        if(isupper(sentence[i]))
            cons++;
        i++;    
    }
    return cons;
}


int Value_num(char* sentence, int constant)
{
    int count=0;
    int l=strlen(sentence);
    for(int i=0;i<l;i++)
    {
        if(isupper(sentence[i]))
        count++;
    }
    if(count>constant)
    return 0;
    else return 1;
}

void Eight_func(char** text, int len)
{
 
    
    
    int cons=Constant(text[0]);
    for (int i = 1; i < len; i++) 
    {
        if(Value_num(text[i], cons)==1)
		    printf("%s\n", text[i]);
		free(text[i]);
	}
	free(text);
}
void switch_function(int value){
	int count=0;
	char** text;
	switch (value) 
        {
	case 0:
		text = input_text(&count);
		base_output_function(text, count);
		break;
	case 1:
		text = input_text(&count);
        output_without_palindrome_symbols(text, count);
		break;
    case 2:
        text = input_text(&count);
        output_in_order(text, count);                                                                                            
        break;
	case 3:
		text = input_text(&count);
		output_without_palindrome(text, count);
		break;
	case 4:
		text = input_text(&count);
		tiger_output_function(text, count);
		break;
	case 5:
		spravka();
		break;
	case 8:
		text = input_text(&count);
		Eight_func(text, count);
		break;
	default:
		printf("Error: ircorrect function value.");	
	}
}
int main() 
{
	printf("Course work for option 4.18, created by Alexander Snigirev.\n");
	int value;
	scanf("%d", &value);
	switch_function(value);
	return 0;
}
