#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// посимвольное считывание текста и подсчет количества предложений
int ReadText(char **text){
    int size = 100; // начальный размер буфера
    char *buffer = (char*)malloc(size*sizeof(char)); // выделение памяти
    int CurrentIndex=0; // индекс текущего символа в буфер
    int KolSentence = 0; // изначальное количество предложений
    char symbol; // текущий считанный символ
    
    do{
        if(CurrentIndex >= size-2){ // проверка на достижение текущего предела размера буфера 
            char *a = (char*)realloc(buffer, size+100);
            size+=100;
            buffer = a;
        }
        symbol = getchar();
        if (symbol=='.' || symbol=='?' || symbol==';') KolSentence++; // проверка на конец предложения
        buffer[CurrentIndex]= symbol;
        CurrentIndex++;
    }while(symbol!='!'); // проверка на конец текста
    buffer[CurrentIndex]= '\0'; 
    *text = buffer; // присваивание указателя для доступа текста в основной программе через переменную text
    return KolSentence;
}

// проверка условия: все предложения, в которых больше одной заглавной буквы, должны быть удалены
int NumberOfCapitalLetters(char* sentence){
    int KolLetters = 0; // счетчик заглавных букв
    
    for (int i = 0; sentence[i] != '\0'; i++) {
    
        if (isupper(sentence[i])) {
            KolLetters++;
            
            if (KolLetters > 1) {
                return 1;
            }
        }
    }
    return 0;
}

// разбиение текста на отдельные предложения, исключение предложений не проходящих по условию на количество заглавных букв
char** SplittingTextIntoSentences(char* text, int* KolSentence) {
    int LenText = strlen(text); // длина строки text
    int volume = 10; // начальная вместимость массива NewText
    char** NewText = (char**)malloc(volume * sizeof(char*)); // массив для хранения обработанного текста
    int BeginningSentence = 0; // отслеживание начало предложения
    
    for (int i = 0; i < LenText; i++) {
    
        if (text[i] == '.' || text[i] == '?' || text[i] == ';') {
        
            if (text[BeginningSentence]==' ') BeginningSentence++; // пропуск пробелов в начале предложения
            
            int LenSentence = i - BeginningSentence + 2; // длина предложения с учетом "\0"
            char* sentence = (char*)malloc((LenSentence) * sizeof(char)); // хранение текущего предложения
            strncpy(sentence, text + BeginningSentence, LenSentence - 1);
            sentence[LenSentence-1] = '\0';
            
            if (!NumberOfCapitalLetters(sentence)) { // проверка условия на количество заглавных букв
                if (*KolSentence>= volume) { // проверка вместимости NewText 
                    volume+=10;
                    NewText = (char**)realloc(NewText, volume * sizeof(char*));
                }
                NewText[*KolSentence] = sentence;
                (*KolSentence)++;
            } 
            else {free(sentence);}
                
            BeginningSentence = i + 1;
        }
    }
    return NewText;
}

int main() {
    char** text = (char**)malloc(sizeof(char*));
    int NumberSentences = ReadText(text); // количество предложений исходного текста
    int NewNumberSentences = 0; // количество предложений обработанного текста
    char** NewText = SplittingTextIntoSentences(*text,&NewNumberSentences);
    
    for (int i = 0; i<NewNumberSentences;i++){
    
        for (int j = 0; j<strlen(NewText[i]);j++){
        
            if (NewText[i][j]!='\t' || NewText[i][j]!='\n')
               printf("%c",NewText[i][j]);
        }
        printf("\n");
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %i и количество предложений после %i", NumberSentences,NewNumberSentences);
    return 0;
    free(text);
    free(NewText);
}
