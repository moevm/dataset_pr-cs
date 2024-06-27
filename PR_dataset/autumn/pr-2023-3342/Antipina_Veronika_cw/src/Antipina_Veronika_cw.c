#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#define BLOCK_SIZE 10
#define END_OF_STRING '\0'

char* input(char* text){
	int k = 0;
        char ch = getchar();
        char ch_prev = ch;
        int capacity = BLOCK_SIZE;

        while(ch != '\n' || ch_prev !='\n'){
                text[k++] = ch;
                if (k == capacity-1){
                        capacity += BLOCK_SIZE;
                        text = realloc(text,capacity*sizeof(char));
                        if(text == NULL){
                                printf("ERROR: could not find the memory");
                                return 0;}
                }
                ch_prev = ch;
                ch = getchar();
        }
        text[k-1] = END_OF_STRING;
        return text;
}

void print_text(char** text, int* sent_count){
        for(int i = 0;i<(*sent_count);i++){
                printf("%s.\n",text[i]);}
}

char** find_sentences(char* text, int *sent_count){
        int capacity = BLOCK_SIZE;
        int k = 0;
        char** changed_text = (char**)malloc(capacity*sizeof(char*));
        char* sentence = strtok(text,".");
        int len = strlen(sentence);

        while(sentence!=NULL){
                changed_text[k] = (char*)malloc((len+1)*sizeof(char));

                int count = 0;
                int c = count;
                while(count<len){
                        if(c!=0 || isspace(sentence[c])==0){
                                changed_text[k][count++]=sentence[c++];}
                        else{
                                while(isspace(sentence[c]))
                                        c++;
                        }
                }
                changed_text[k][count] = END_OF_STRING;
                k++;
                (*sent_count)++;
                if(k == capacity-1){
                        capacity += BLOCK_SIZE;
                        changed_text = (char**)realloc(changed_text,capacity*sizeof(char*));
                }
                sentence = strtok(NULL,".");
                if(sentence!=NULL){len = strlen(sentence);}
        }
        changed_text[k] = END_OF_STRING;

        return changed_text;
}

char** find_repeat(char** text, int* sent_count){
        for(int i = 0; i<(*sent_count); i++){
                for (int c = 0; c<(*sent_count); c++){
                        if(c!=i){
                                if(strcasecmp(text[i],text[c])==0){
                                        for(int count = c; count < (*sent_count)-1; count++){
                                                text[count] = text[count+1];
                                        }
                                        text[(*sent_count)-1] = END_OF_STRING;
                                        (*sent_count)--;
                                        c--;
                                }
                        }
                }
        }

        return text;
}

char*** find_words(char** text, int *sent_count){
        char*** changed_again = (char***)malloc((*sent_count)*sizeof(char**));

        for(int count = 0; count < (*sent_count); count++){
                int len = strlen(text[count]);
                changed_again[count] = (char**)malloc((len+1)*sizeof(char*));

                char* word = strtok(text[count]," ");
                int len_of_word = strlen(word);
                int words_per_sentence = 0;

                while(word!=NULL){
                        changed_again[count][words_per_sentence] = (char*)malloc((len_of_word+1)*sizeof(char));
                        strcpy(changed_again[count][words_per_sentence++],word);

                        word = strtok(NULL," ");
                        if(word!=NULL){
                                len_of_word = strlen(word);}
                }
                changed_again[count][words_per_sentence] = END_OF_STRING;
        }
        return changed_again;
}

void free_memory(int *sent_count, char** text){
        for(int y = 0; y<(*sent_count); y++){
                free(text[y]);}
        free(text);
}

void start_equal_to_end(char** text, int *sent_count){
        for(int i = 0;i<(*sent_count);i++){
                int len = strlen(text[i]);
                if((toupper(text[i][0])==toupper(text[i][len-1]))||(text[i][0]==text[i][len-1])){
                        text[i] = END_OF_STRING;
                }
        }

        for(int counter = 0; counter<(*sent_count);counter++){
                if(text[counter]!=NULL){
                        printf("%s.\n",text[counter]);}
        }
}

void delete_all_numbers(char** text,int *sent_count){
        int k = *sent_count;
        for(int c=0;c<k;c++){
                int len = strlen(text[c]);
                int flag = 0;
                for(int i=0;i<len;i++){
                        if(flag==1){
                                i--;
                                flag = 0;
                        }
                        if(isdigit(text[c][i])){
                                for(int count = i;count<len-1;count++){
                                        text[c][count] = text[c][count+1];
                                        flag = 1;
                                }
                                len--;
                                text[c][len] = END_OF_STRING;
                                if(isdigit(text[c][len-1]))
                                        text[c][len-1]=END_OF_STRING;

                        }
                }
        }
        print_text(text,sent_count);
}

int is_palindrome(char* sentence){
        int len = strlen(sentence);
        int flag = 0;
        for(int i = 0; i<len/2;i++){
                if(toupper(sentence[i])==toupper(sentence[len-1-i])){
                        flag = 1;}
                else{
                        return 0;}
        }
        return flag;
}


void is_sent_palindrome(char** text, int *sent_count){
        for(int sent=0;sent<(*sent_count);sent++){
                int len = 0;
                int len_of_sentence = strlen(text[sent]);

                for(int count=0;count<len_of_sentence;count++){
                        if((text[sent][count]!=' ') && (text[sent][count]!=','))
                                len++;
                }
                char* string = (char*)malloc((len+1)*sizeof(char));
                int i = 0;
                for(int count = 0;count<len_of_sentence;count++){
                        if(isspace(text[sent][count])==0 && text[sent][count]!=','){
                                        string[i++] = text[sent][count];}
                }
                string[i] = END_OF_STRING;
                int flag = is_palindrome(string);
                if(flag==1 || len==1)
                        printf("Palindrome\n");
                else
                        printf("Nothing interesting\n");

                free(string);
        }
}

int get_third_word_length(const char* string){
        int len_s = strlen(string);
        int ptr_st = 0;
        int ptr_end = 0;
	int how_many_s = 0;
        if(string[0]!=','){
		how_many_s = 1;}
        int index = 0;
        while(index<len_s && how_many_s<3 && ptr_end<len_s){
                if(string[index]==',' || string[index]==' '){
                        ptr_st = index;
                        ptr_end = ptr_st + 1;
                        while(string[ptr_end]==',' || string[ptr_end]==' '){
                                ptr_st++;
                                ptr_end++;}
                        ptr_st = ptr_end-1;
                        while(string[ptr_end]!=',' && string[ptr_end]!=' ' && ptr_end<len_s){
                                ptr_end++;}
                        if(ptr_end==len_s)
                                ptr_end++;
                        how_many_s++;
                        index = ptr_end-1;
                }else{
                        index++;}
        }
        if(how_many_s<3)
                return 3;
        else
                return ptr_end-ptr_st-1;
}

int cmp(const void* a, const void* b){
        const char* f = *(const char**)a;
        const char* s = *(const char**)b;

        return get_third_word_length(f)-get_third_word_length(s);
}

void sort_by_third(char** text, int *sent_count){
        qsort(text,(*sent_count),sizeof(char*),cmp);
        print_text(text,sent_count);
}

void copy(char** to_here, char** from_here, int* length){
        for(int i=0;i<(*length);i++){
                int len = strlen(from_here[i]);
                to_here[i] = (char*)malloc((len+1)*sizeof(char));
                strcpy(to_here[i], from_here[i]);
        }
}

char* binary(int num){
        char* res = (char*)malloc(15*sizeof(char));
        int k = 1;
        int bin = 0;
        int i = 0;
        while(num){
                bin+=(num%2)*k;
                k*=10;
                i++;
                num/=2;
        }
        res[0] = '0';
        res[1] = 'b';
        char* ch = malloc((i+1)*sizeof(char));
        snprintf(ch,i+1,"%d",bin);
        strncat(res,ch,i);

        return res;
}

void change_to_bin(char** text,int *sent_count){
        for(int i = 0;i<(*sent_count);i++){
                int len = strlen(text[i]);

                int ind_end = 0;
                char* number = (char*)malloc(11*sizeof(char));

                for(int x = 0;x<len;x++){
                        int f = 0;
                        if(isdigit(text[i][x])==0)
                                printf("%c",text[i][x]);
                        else{
                                f = 1;
                                ind_end = x;
                                int index = 0;
                                while(isdigit(text[i][x])!=0){
                                        number[index++] = text[i][x];
                                        x++;
                                        ind_end++;
                                }

                                int num = 0;
                                num = atoi(number);
                                char* add = binary(num);
				
                                for(int y = 0;y<strlen(add);y++)
                                        printf("%c",add[y]);
                        }
                        if(f ==1)
                                x = ind_end-1;
                }
                printf(".\n");
        }
}

void cases(int* choose_function, char** changed_text, int* sent_count){
        switch(*choose_function){
                case(0):
                        print_text(changed_text,sent_count);
                        break;
                case(1):
                        delete_all_numbers(changed_text,sent_count);
                        break;
                case(2):
                        is_sent_palindrome(changed_text,sent_count);
                        break;
                case(3):
                        start_equal_to_end(changed_text,sent_count);
                        break;
                case(4):
                        sort_by_third(changed_text,sent_count);
                        break;
                case(9):
                        change_to_bin(changed_text,sent_count);
                        break;
        }
}

void user_input(int* choose_function){
        scanf("%d",choose_function);
        getchar();
}

int main(){

        printf("Course work for option 4.14, created by Veronika Antipina\n");

        int choose_function;
        user_input(&choose_function);

	if(choose_function!=5){
	        char* text = (char*)malloc(BLOCK_SIZE*sizeof(char));
	        int j = 0;
		text = input(text);
	        char** changed_text = find_sentences(text,&j);
        	changed_text = find_repeat(changed_text, &j);

		cases(&choose_function,changed_text,&j);
		free(text);
		free_memory(&j, changed_text);
	}else{
		printf("0 - print text.\n1 - delete all numbers in the text.\n2 - for every sentence print 'Palindrome' if it's true, else print 'Nothing interesting'.\n3 - delete all sentences that start and end with one symbol.\n4 - sort text by sentences using length of third words for comparison. If sentence doesn't have the third word use 3 as length.\n");
	}

        return 0;
}
