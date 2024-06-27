#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK 200
#define STR_BLOCK 10

int n7=0;//переменная для подсчета количества предложений, содержащих 7
int blockread(char**);

int main() {
 char** text=(char**)malloc(BLOCK*sizeof(char*));//создание массива для предложений (указатели)
    int number=blockread(text);
    for (int i=0;i<=number;i++){
    printf("%s\n", text[i]);
    }
    for (int i=0; i<BLOCK; i++){
   	free(text[i]);   	}
    free(text);
    printf("Количество предложений до %d и количество предложений после %d\n", number+n7,number);
    return 0;
}

int blockread(char** text){
   for (int i=0; i<BLOCK; i++){
   	text[i]=(char*)malloc(STR_BLOCK*sizeof(char));//выделение памяти для символов предложения
   	}
   char c=getchar();
  char cpred;//переменная для исключения лишних пробелов в предложении
   int symbols=STR_BLOCK;//переменная для размера строки
   int not7=1;//переменная для удаления предложений, содержащих 7
   size_t ind=0;//индекс символа
   size_t num=0;//индекс предложения
   
   while(1){//цикл для количества предложений
   if (c!='\t' && c!=' ' && c!='\n'){//удаление табуляции, пробелов и перевода строки между предложениями

   while (1){//цикл для предложения
   	if ((c!='\n') && ((cpred==' ')!=c)) {//удаляются лишние пробелы и переводы строк в предложении)
   	if (c=='.' || c==';' || c=='?'){//проверка на окончание предложения
   		text[num][ind++]=c;
   		text[num][ind]='\0';
   		symbols=STR_BLOCK;
   		ind=0;
		break;
   	}
   	if (c=='7'){
   		n7++;//увеличение количества предложений, содержащих 7
   		free(text[num]);//освобождения памяти массива символов, где ранее хранилось предложение с 7
   		symbols=STR_BLOCK;
   		text[num]=(char*)malloc(sizeof(char)*symbols);//выделение памяти для следующего предложения
   		ind=0;
   		while (c!='.' && c!=';' && c!='?'){
   				c=getchar();//считывание предложения с 7 до конца без занесения в массив предложений
   			}
   		not7=0;
   		break;
   	}
   	else{
   	cpred=c;
   	text[num][ind++]=c;
   	if (ind==symbols-1){
   		symbols+=STR_BLOCK;		
   		text[num]=(char*)realloc(text[num],sizeof(char)*symbols);//увеличение памяти для предложения
   	}
   	
   	if (strstr(text[num],"Dragon flew away!")){//проверка на предложение, завершающее ввод текста
   		text[num][ind]='\0';
   		return num;}
   	}
   	c=getchar();
   	
   	}
   	else{
   	c=getchar();
   	}
   }
   if (not7){
   	num++;}//увеличение индекса предложения при условии, что предложение не содержало 7
   else{
   not7=1;
   }
   }
   c=getchar();
   }
  }
