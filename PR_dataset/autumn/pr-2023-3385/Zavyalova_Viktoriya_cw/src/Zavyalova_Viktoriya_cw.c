#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <strings.h> 
#include <ctype.h> 
 
#define BLOCK_SIZE 20 
#define TXT_BLOCK_SIZE 3 
 
int sent_equals(char** text, int txt_len, char* sent) { 
    for (int i = 0; i < txt_len; i++) { 
        if (!strcasecmp(text[i], sent)) return 0; // если считываемое предложение совпадает с каким-то из уже записанных 
    } 
        
    return 1; 
} 

 
char* get_sentence(){ 
    size_t idx = 0; 
    size_t capacity = BLOCK_SIZE; 
     
    char ch = getchar(); 
    char* sentence = (char*)malloc(capacity); 
    if (sentence == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        for (int l = 0; l < capacity; l++) {
            free(sentence);
        }
        
        free(sentence);
        exit(0);
    }
 
    while(1){ 
        if (!((idx == 0 && isblank(ch))||(ch=='\n'))) {sentence[idx++] = ch; 
        } 
        if ((ch == '.') || (ch=='\n')) { 
            sentence[idx++] = '\0'; 
            break; 
        } 
         
        if (idx == capacity-1) { 
            capacity += BLOCK_SIZE; 
            sentence = (char*)realloc(sentence, capacity);
            if (sentence == NULL) {
                fprintf(stderr, "Ошибка выделения памяти\n");
                free(sentence);
                exit(0);
            }
        } 
        ch = getchar(); 
    } 
 
    return sentence; 
} 

 
char** get_text(int *len_text){ 
    size_t size = TXT_BLOCK_SIZE; 
    int txt_id = 0; 
    int empty_lines = 0; // счетчик пустых строк 
    char** text = (char**)malloc(size*sizeof(char*)); 
    if (text == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        for (int l = 0; l < size; l++) {
            free(text[l]);
        }
        free(text);
        exit(0);
    }
    char* sentence = get_sentence(); 
 
    while(1) { 
        if (strlen(sentence)<1) { 
            empty_lines++;
            if ((txt_id > 0) && (text[txt_id-1][strlen(text[txt_id-1])-1] != '.')){
                empty_lines++;
                int sent_len = strlen(text[txt_id-1]);
                text[txt_id-1][sent_len] = '.';
                text[txt_id-1][sent_len+1] = '\0';
            }   
            if (empty_lines == 2) break; // если две пустые строки подряд, то остановка 
        } else { 
            empty_lines = 0;  
        }

        if (sent_equals(text, txt_id, sentence) && empty_lines==0) text[txt_id++] = sentence; // если не нашлось "дубликата" то предложение записывается в массив, иначе просто ничего не происходит 
        if (txt_id == size-1) { 
            size += TXT_BLOCK_SIZE; 
            char** old_text = text;
            text = (char**)realloc(text, size*sizeof(char*));
            if (text == NULL) {
                text = old_text;
                fprintf(stderr, "Ошибка выделения памяти\n");
                for (int l = 0; l < size; l++) {
                    free(text[l]);
                }
            free(text);
            exit(0);
        }
}
             
            for (int x = txt_id; x < size; x++) { 
            text[x] = (char*)malloc(BLOCK_SIZE);
            if (text[x] == NULL) {
                fprintf(stderr, "Ошибка выделения памяти\n");
                for (int l = 0; l <BLOCK_SIZE; l++) {
                    free(text[l]);
                }
            free(text);
            exit(0);
            }
        } 
        } 
         
        sentence = get_sentence(); 
         
    } 
    *len_text = txt_id;    
    return text; 
  
}


void print(char** text,int *len_text){
    for(int i = 0; i < *len_text; i++){
            printf("%s\n", text[i]);
            free(text[i]);
        }
        
    free(text);
    exit(0);
}


char** del_sent(char** text, int txt_len,int id){ 
    for(int i = id;i<txt_len;i++){ 
        text[i] = text[i+1]; 
    } 
    return text;
} 
 
 
char** del_first_word(char** text,int *len_text){
    int new_len = *len_text;
    for(int i=0;i<*len_text;i++){
        int space_count = 0;
        for(int j=1;j<strlen(text[i]);j++){
            if((text[i][j]==' ')&&(!isspace(text[i][j+1]))){
                space_count+=1;
                memmove(text[i],text[i]+j+1,strlen(text[i])*sizeof(char));
                break;
            }
            else if(text[i][j]==','){
                space_count+=1;
                memmove(text[i],text[i]+j,strlen(text[i])*sizeof(char));
                break;
            }
            
        }
        if((space_count==0)||(strlen(text[i])==1)){
            text = del_sent(text,new_len,i);
            i--;
            new_len--;
            *len_text = new_len;
        }
        
    } 
     
    return text;
} 


char** timer(char** text,int *len_text){
    int new_len = *len_text;
    for(int i=0;i<new_len;i++){
        char sent [strlen(text[i])+1];
        strcpy(sent,text[i]);
        char* k = strtok(sent," ,");
         while(k!=NULL){
            int num = 0;
            if((strlen(k)>3)&&(strstr(k,"sec")!=NULL)){
                num = atoi(k);
                printf("%d:%d:%d\n", num / 3600, (num % 3600) / 60, (num % 3600) % 60);
            }
        
            k = strtok(NULL," ,.");
        }
    }
    
    for(int i = 0; i < *len_text; i++){ 
        free(text[i]); 
    } 
    free(text); 
    return 0;
}
 

char** del_same_lenght(char** text,int *len_text){
    int new_len = *len_text;
    for(int i=0;i<new_len;i++){
        char sent [strlen(text[i])+1];
        strcpy(sent,text[i]);
        char* tmp = strtok(sent," ,.");
        int a = strlen(tmp);
        tmp = strtok(NULL," ,.");
        int flag = 1;
        if(tmp==NULL) flag=1;
        while(tmp!=NULL){
            if(!(a==strlen(tmp))){
                flag = 0;
                break;
            }
            
            tmp = strtok(NULL," ,.");
        }
        if(flag){
            text = del_sent(text,new_len,i);
            i--;
            new_len--;
            *len_text = new_len;
        }
    }
    
    return text;
    exit(0);
}
 
 
int low(char *str){ 
    int count = 0; 
    for(int i=0;i<strlen(str);i++){ 
        if(islower(str[i])){ 
           count+=1;  
        }  
    } 
    return count; 
} 
 
 
int sort(void const* a,void const* b){ 
    int l_x = low(*(char**)a);  
    int l_y = low(*(char**)b); 
    if(l_x<l_y){ 
        return 1; 
    } 
    if(l_x>l_y){ 
        return -1; 
    } 
     
    return 0; 
} 

char** txt_d(char** text,int *len_text,char* arr){
    int new_len = *len_text;
    arr[strlen(arr)-1]=' ';
    arr[strlen(arr)]='\0';
    if (new_len%2==0){
        for(int i=0;i<(new_len/2);i++){
            for(int j=0;j<strlen(text[i]);j++){
                if(text[i][j]=='.'){
                    text[i][j]=' ';
                }
            }
            printf("%s%s%s",text[i],arr,text[new_len-i-1]);
            printf("\n");
            
        }
    }
    if(new_len%2!=0){
        for(int i=0;i<(new_len/2)+1;i++){
            for(int j=0;j<strlen(text[i]);j++){
                if(text[i][j]=='.'){
                    text[i][j]=' ';
                }
            }
            if(i!=((new_len-1)/2)){
                printf("%s%s%s",text[i],arr,text[new_len-i-1]);
                printf("\n");
            }
            else{
                text[i][strlen(text[i])-1]='\0';
                printf("%s %s%s.",text[i],arr,text[i]);
                printf("\n");
            }
        }
        
    }
    exit(0);
}
 
 
void get_info(void){ 
    printf("0: Вывод текста после первичной обязательной обработки. \n1: Посчитать колличество секунд.\n2: Удаление первых слов в предложении.\n3: Удалеине все предложений у которых длины всех слов одинаковые. \n4: Cортировка предложений по уменьшению количества строчных букв в нем.\n");
} 
 
 
int main()
{ 
    int len_text = 0; 
    printf("Course work for option 4.11, created by Viktoriya Zavyalova.\n"); 
    char symb = getchar();
    getchar();
    int s = 8;
    if(isdigit(symb)){
        s = (int)(symb-48);
    } 
    
    char** text;
    char arr[100];
    switch(s)
    {
        case 0:
            text = get_text(&len_text);
            print(text,&len_text);
            break;
        case 1:
            text = get_text(&len_text);
            timer(text,&len_text);
            break;
        case 2:
            text = get_text(&len_text);
            del_first_word(text,&len_text);
            print(text,&len_text);
            break;
        case 3:
            text = get_text(&len_text);
            del_same_lenght(text,&len_text);
            print(text,&len_text);
            break;
        case 4:
            text = get_text(&len_text);
            qsort(text,len_text,sizeof(char*),sort);
            print(text,&len_text);
            break;
        case 5:
            get_info();
            break;
        case 8:
            fgets(arr,100,stdin);
            text = get_text(&len_text);
            txt_d(text,&len_text,arr);
            break;
        default:
            printf("Такой команды не существует! Введите цифру от 0 до 5.");
            break;
    }
    return 0; 
}
