#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** read_text();
void write_text(char **text);
char** primary_processing(char **text);
void display_information();
void text_free(char **text);
char** func_1(char **text);
char** func_2(char **text);
int is_vowel(char ch);
int cmp(const void* str1, const void* str2);
char** func_3(char **text);
int is_lower(char *word);
void func_4(char* str);
int cmp2(const void* str1, const void* str2);
char** func9(char **text);

int count_sent =0;
int sent_4 = 0;

char ** read_text(){
    int len_sent=0, max_len_sent=100, max_count_sent = 50;
    int flag = 1; //момент чтения
    char **text = malloc(sizeof(char*)*max_count_sent);
    char *sent = malloc(sizeof(char) * max_len_sent);

    char symbol, symbol_bef;
    while(flag){
        symbol_bef = symbol;
        symbol = getchar();
        //проверка на конец текста
        if ((symbol == '\n') && (symbol_bef == '\n'))
            flag = 0;

        //пропуск ненужных символов
        if (((symbol == '\t') && (len_sent == 0)) || ((symbol == '\n') && (len_sent == 0)) || ((symbol == ' ') && (len_sent == 0)) || ((symbol == '.') && (len_sent == 0)))
            continue;
        len_sent++;
        
        //выделение дополнительной памяти
        if(len_sent>=max_len_sent){
            max_len_sent += 100;
            sent = realloc(sent, sizeof(char)*max_len_sent);
            if(sent==NULL){
                free(sent);
                return NULL;
            }
        }
        
        sent[len_sent-1]=symbol;
        
        //нашлось новое предложение
        if(symbol=='.'){
            count_sent++;
            if(count_sent>=max_count_sent){
                max_count_sent+=50;
                text = realloc(text, sizeof(char*)*max_count_sent);
                if(text==NULL){
                    count_sent=0;
                    free(text);
                    return NULL;
                }
            }
            //запись предложения в массив
            text[count_sent-1] = malloc(sizeof(char)*max_len_sent);
            strcpy(text[count_sent-1], sent);
            text[count_sent-1][len_sent]='\0';
            len_sent = 0;
            max_len_sent = 100;
            free(sent);
            sent = malloc(sizeof(char)*max_len_sent);
        }
    }
    free(sent);
    return text;
}

void write_text(char **text) {
    if(count_sent!=0){
        for (int i = 0; i < count_sent; i++)
            puts(text[i]);
    }
    else{
        printf("The number of sentences is 0.\n");
    }
}

char** primary_processing(char **text){
    int flag_delete;
    
    for(int i=0;i<(count_sent-1);i++){
        int j=i;
        while(j<count_sent){
                flag_delete=0;
                if((strlen(text[i])==strlen(text[j]))&&j>i){
                    flag_delete=1;
                    for(int k=0; k<strlen(text[i]);k++){
                        if(tolower(text[i][k])!=tolower(text[j][k])){
                            flag_delete=0;
                            break;
                        }
                    }
                }
                if(flag_delete){
                    free(text[j]);
                    for(int k=j;k<(count_sent-1);k++){
                        text[k]=text[k+1];
                    }
                    count_sent--;
                    j--;
                }
            j++;
        }
    }
    
    
    return text;
};

void display_information(){
    printf("Description of functions used in the program:\n");
    printf("0 – Outputing text after initial mandatory processing.\n");
    printf("1 – Outputing of sentences in a familiar format. The first letter is capital, the rest are lowercase.\n");
    printf("2 – Removing all sentences with an even number of words.\n");
    printf("3 – Sorting sentences by the sum of the number of vowels in every second word.\n");
    printf("4 - Displaying all sentences that contain words consisting of capital letters in the middle of the sentence. These words will be highlighted in blue.\n");
    printf("5 – Showing all program functions.\n");
}

void text_free(char **text) {
    for (int i = 0; i < count_sent; i++)
        free(text[i]);
    free(text);
}

char** func_1(char **text){
    for(int i=0;i<count_sent;i++){
        for(int j=0;j<strlen(text[i]);j++){
            text[i][j]=tolower(text[i][j]);
        }
        text[i][0]=toupper(text[i][0]);
    }
    return text;
};

char** func_2(char **text){
    int i=0;
    while(i<count_sent){
        int count=0;
        for(int j=0;j<strlen(text[i]);j++){
            if(text[i][j]==' '){
                count++;
            }
        }
        if(count % 2 == 1){
            free(text[i]);
            for(int k=i;k<(count_sent-1);k++){
                text[k]=text[k+1];
            }
            count_sent--;  
            i--;
        }
        i++;
    }
    return text;
};

int is_vowel(char ch){
    char vowels[]= "aeiouyAEIOUY";
    if (strchr(vowels, ch)){
        return 1;
    }
    else{
        return 0;
    }
};

int cmp(const void* str1, const void* str2) {
    char *str1_ = *((char **) str1);
    char *str2_ = *((char **) str2);
    
    int count_vowels_str1=0;
    int word_str1 = 1;
    for(int i=0;i<strlen(str1_);i++){
        if(str1_[i]==' '){
            word_str1++;
            continue;
        }
        if(word_str1 % 2 == 1){
            count_vowels_str1 += is_vowel(str1_[i]);
        }
    }
    
    int word_str2 = 1;
    int count_vowels_str2=0;
    for(int i=0;i<strlen(str2_);i++){
        if(str2_[i]==' '){
            word_str2++;
            continue;
        }
        if(word_str2 % 2 == 1){
            count_vowels_str2 += is_vowel(str2_[i]);
        }
    }
    if(count_vowels_str1 > count_vowels_str2){
        return 1;
    }
    else if(count_vowels_str1==count_vowels_str2){
        return 0;
    }
    else{
        return -1;
    }
};

char** func_3(char **text){
    qsort(text, count_sent, sizeof(char *), cmp);
    return text;
};

int is_lower(char *word){
    int flag = 1;
    for(int i=0;i<strlen(word);i++){
        if(word[i]!=tolower(word[i])){
            flag=0;
        }
    }
    
    if(flag){
        return 1;
    }
    else{
        return 0;
    }
};

void func_4(char* str){
    char color[] = "\033[94m";
    char reset[] = "\033[0m";
    
    int len_str = 0;
    int max_len_str = 100;
    char* new_str=(char*)calloc(max_len_str, sizeof(char*));
    //char* new_str=(char*)malloc(sizeof(char) * max_len_str);
    
    //подсчёт слов
    int count_words = 0;
    for(int i=0;i<strlen(str);i++){
        if(str[i]==' '){
            count_words++;
        }
    }
    count_words++;
    
    int is_changed = 0;
    
    
    char* word;
    word = strtok(str," ");
    int num_word;
    num_word=0;
    
    while (word != NULL)
    {
        num_word++;
        
        if(num_word!=1 && num_word !=count_words){
            //если слово строчное и не первое
            if(is_lower(word)){
                len_str += strlen(color);
                len_str += strlen(word);
                len_str += 2;
                if(len_str>max_len_str){
                    max_len_str += 100;
                    new_str = (char*)realloc(new_str, sizeof(char)*max_len_str);
                }
                if(new_str==NULL){
                    free(new_str);
                }
                //проверка на запятую
                if(word[strlen(word)-1]==','){
                    word[strlen(word)-1]='\0';
                    strcat(new_str, color);
                    strcat(new_str, word);
                    strcat(new_str, reset);
                    strcat(new_str,", ");
                }
                else{
                    strcat(new_str, color);
                    strcat(new_str, word);
                    strcat(new_str," ");
                }
                is_changed = 1;
            }
            //если слово нестрочное
            else{
                len_str += strlen(reset);
                len_str += strlen(word);
                len_str += 2;
                if(len_str>max_len_str){
                    max_len_str += 100;
                    new_str = (char*)realloc(new_str, sizeof(char)*max_len_str);
                }
                if(new_str==NULL){
                    free(new_str);
                }    
                strcat(new_str, reset);
                strcat(new_str, word);
                strcat(new_str," ");
            }
        }
        
        else{
            len_str += strlen(reset);
            len_str += strlen(word);
            len_str += 2;
            if(len_str>max_len_str){
                max_len_str += 100;
                new_str = (char*)realloc(new_str, sizeof(char)*max_len_str);
            }
            if(new_str==NULL){
                free(new_str);
            }
            strcat(new_str, reset);
            strcat(new_str, word);
            if(num_word==1){
                strcat(new_str," ");
            }
        }
        word = strtok(NULL," ");
    }
    
    if(is_changed){
        printf("%s\n", new_str);
        sent_4++;
    }
    free(new_str);
};

int cmp2(const void* str1, const void* str2){
    char *word1 = *((char **) str1);
    char *word2 = *((char **) str2);
    
    char digits[]="0123456789";
    
    int sums1=0;
    char* digit;
    int letter;
    for(int i=0;i<strlen(word1);i++){
        letter=0;
        if((digit=strchr(digits, word1[i]))!= NULL){
            letter = digit - digits;
        }
        sums1+=letter;
    }
    
    int sums2=0;
    for(int i=0;i<strlen(word2);i++){
        letter=0;
        if((digit=strchr(digits, word2[i]))!= NULL){
            letter = digit - digits;
        }
        sums2+=letter;
    }
    
    if(sums1 > sums2){
        return 1;
    }
    else if(sums1==sums2){
        return 0;
    }
    else{
        return -1;
    }
};


char** func_9(char **text){
    char* str;
	for(int i=0;i<count_sent;i++){
	    str=text[i];
	    int count_words = 0;
        for(int k=0;k<strlen(str);k++){
            if(str[k]==' '){
                count_words++;
            }
        }
        count_words++;
        
        
        char** words=malloc(sizeof(char*) * count_words);
        char* word;
        word = strtok(str," ");
        int num_word=0;
        
        while (word != NULL)
        {
            num_word++;
            words[num_word-1]=word;
            word = strtok(NULL," ,.");
        }    
        qsort(words, count_words,sizeof(char*), cmp2);
        int len_str = 0;
        int max_len_str = 100;
        char* new_str=(char*)calloc(max_len_str, sizeof(char*));
        for(int k=0;k<count_words;k++){
            len_str += strlen(words[k]);
            if(len_str>max_len_str){
                        max_len_str += 100;
                        new_str = (char*)realloc(new_str, sizeof(char)*max_len_str);
                    }
                    if(new_str==NULL){
                        free(new_str);
                    }
            strcat(new_str, words[k]);
            if(k!=count_words-1){
                strcat(new_str, " ");
            }    
        }
        if(new_str[strlen(new_str)-1]!='.'){
        	strcat(new_str, ".");
        }	
        text[i]=new_str;
    }
    return text;
};

int main(){
    printf("Course work for option 4.1, created by Andrei Potapov.\n");
    int command;
    int error_check = scanf("%d", &command)-1;
    if (error_check) {
        printf("Error: failed to read the command.\n");
        return 0;
    }else if((command<0 || command>5)&&command!=9){
    	printf("Error: command is incorrect.\n");
    	return 0 ;
    }
    if (command == 5) {
        display_information();
        return 0;
    }
    char **text = primary_processing(read_text());
    switch(command){
        case 0:
            write_text(text);
            break;
        case 1:
            write_text(func_1(text));
            break;
        case 2:
            write_text(func_2(text));
            break;
        case 3:
            write_text(func_3(text));
            break;
        case 4:
            if(count_sent==0){
            	printf("The number of sentences is 0.\n");
            }
            else{
            	for(int i=0; i<count_sent;i++){
                    func_4(text[i]);
                }
                if(sent_4==0){
            		printf("There are no such sentences.\n");
            	}
            }
            break;
        case 9:
            write_text(func_9(text));
            break;
    }        
    text_free(text);
    return 0;
}

