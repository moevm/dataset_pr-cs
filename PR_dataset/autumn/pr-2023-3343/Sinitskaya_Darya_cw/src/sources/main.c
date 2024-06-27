#include"../include/main.h"
int main(){

     setlocale(LC_ALL, "");
     //информация о курсовой работе
     wprintf(L"Course work for option 5.10, created by Darya Sinitskaya.\n");
     
     int function;
     wscanf(L"%d",&function); //считывание действия пользователя

     if(function>5 && function!=8){
     wprintf(L"Error:Non-existent function! Call function 5 to view the help\n"); //обработка ошибки - ввод несуществующего действия
     } else {
     
     if(function!=5){
          //считывание текста
          Text text;
          Input(&text);
          int f=1;

          //вызов функции
          switch (function){
               case 0:
                    break;
               case 1:
                    Palindromes(&text);
                    f=0;
                    break;
               case 2: 
                    Replacing_Special_Characters(&text);
                    break;
               case 3: 
                    Sorting(&text);
                    break;
               case 4: 
                    Removal(&text);
                    break;
               case 8: 
                    Removal_Non_Palindrome_Sentence(&text);
                    f=0;
                    break;
               default: 
                    wprintf(L"Error:Non-existent function number\n"); 
                    break;
     }

     //вывод текста
     if(f==1)Output(&text);
     //очистка памяти
     Free(&text);
     }
     else{
          Reference();     
     }

     }

     return 0;
}
