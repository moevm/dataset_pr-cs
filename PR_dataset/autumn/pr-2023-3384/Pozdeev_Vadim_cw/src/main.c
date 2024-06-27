#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


struct Sentence_Date{
    struct tm * date;
    int size;
};

void help(){
    puts("1: Print all sentences that contain a date with the current year and month. (The date is written in the format DD/MM/YYYY)\n"
         "2: Sort sentences by increasing the minimum date in them.\n"
         "3: Delete all sentences in which all dates refer to the 19th century.\n"
         "4: For each sentence, print the earliest and latest date.\n");
}

char * read_sentence(int * end){
    char * sentence = malloc(sizeof(char));
    char symbol = getchar();
    int length = 0;
    int flag = 1;
    int capacity = 1;
    for(;(symbol!='.');length++){
        if( (length!=0)&&(sentence[length-1]=='\n')&& (symbol!='\n')){
                length--;
                flag=1;
        }
        if( symbol=='\t')
            symbol = ' ';
        if( flag&&( (symbol == ' ')||(symbol == '\t') )){
            length--;

            symbol = getchar();
            continue;
        }
        flag = 0;
     
        /*if( (symbol==' ') && (sentence[length-1]==' ') ){
                length--;
                symbol = getchar();
                continue;
        }*/
        if((symbol == '\n')&&(length!=0)&&(sentence[length-1]=='\n'))
            {*end=1; break;}
        if (length >= capacity) {
            capacity*=2;
            sentence = realloc(sentence, capacity * sizeof(char));
        }
        sentence[length] = symbol;
        symbol = getchar();
    }
    if((sentence[length-1]==' ')||(sentence[length-1]=='\n')){
        sentence = realloc(sentence, length*sizeof(char));
        sentence[length-1]='\0';
    }
    else{
        sentence = realloc(sentence, (length+1)*sizeof(char));
        sentence[length]='\0';
        }
    return sentence;
}


int in_text( char ** text,  char * sentence, int length){
    for(int i=0; i!=length; i++){
        if (strcmp(text[i], sentence)==0)
            return 1;
    }
    return 0;
}

char ** read_text(int * size){
    getchar();
    char ** text = NULL;
    int i = 0;
    int end = 0;
    char * sentence = read_sentence(&end);
    for(;!(end);i++){
        if(in_text(text, sentence, i)){
            free(sentence);
            i--;
            sentence = read_sentence(&end);
            continue;
        }
        text = (char **)realloc(text, (i+1)*sizeof(char*));
        text[i] = sentence;
        sentence = read_sentence(&end);
    }
    *size = i;
    if(strcmp(sentence, "")==0)
        free(sentence);
    else{

        (*size)++;
        text = (char **)realloc(text, (i+1)*sizeof(char*));

        text[i] = sentence;
    }
    return text;
}
int check(char * pch){
    int k = 0;
    if( pch[0]=='/'){
        return 0;
        }

    for(int i=0; pch[i]; i++){
        if(pch[i]=='/'){
            k++;
            if( !(isdigit(pch[i-1])&&isdigit(pch[i+1])) ){
                return 0;
                }
            }
        if(!((isdigit(pch[i]))||(pch[i]!='/')||(pch[i]!='\n')) ){
            return 0;}

    }
  if(k != 2){
        return 0;}
  return 1;
}

struct Sentence_Date make_sentence(char* sentence, int * error){
    struct Sentence_Date new_sentence;
    new_sentence.date = NULL;
    int i = 0;
    char * pch = strtok(sentence, " ");
    for(;pch!=NULL;i++){
        struct tm new_date;
        if(!check(pch)){
            printf("<ERROR> Wrong input\n");
            *error = 1;
            free(sentence);
            return new_sentence;
        }
        sscanf(pch, "%d/%d/%d\n", &new_date.tm_mday, &new_date.tm_mon, &new_date.tm_year);
        new_sentence.date = realloc(new_sentence.date, (i+1)*sizeof(struct tm));
        new_sentence.date[i] = new_date;
        pch = strtok (NULL, " ");
    }
    new_sentence.size = i;
    return new_sentence;
}

struct Sentence_Date * make_text(char ** text, int size){
    struct Sentence_Date * new_text = malloc(size*sizeof(struct Sentence_Date));
    int error = 0;
    int i = 0;
    for(;i!=size;i++){
        new_text[i] = make_sentence(text[i], &error);
        if(error){
            free(new_text[i].date);
            for(int t=0; t!=i; t++){
                free(new_text[t].date);
            }
            free(new_text);
            exit(0);
        }
        free(text[i]);
    }
    free(text);
    return new_text;
}

void print_sentence(struct Sentence_Date sentence){

    for(int i = 0; i!=sentence.size; i++){
        printf("%d/%d/%d", sentence.date[i].tm_mday, sentence.date[i].tm_mon, sentence.date[i].tm_year);
        if(i!=sentence.size-1)
            printf(" ");
        }
        printf(".\n");
}

int cmp_date(struct tm date1, struct tm date2){
    if(date1.tm_year != date2.tm_year)
        return date1.tm_year-date2.tm_year;
    else{
        if(date1.tm_mon != date2.tm_mon)
            return date1.tm_mon-date2.tm_mon;
        else{
            if(date1.tm_mday != date2.tm_mday)
                return date1.tm_mday-date2.tm_mday;
            else
                return 0;
        }
    }
}

struct tm * find_min_date(struct Sentence_Date sentence){
    struct tm * min_date = &sentence.date[0];
    for(int i = 1; i!=sentence.size; i++){
        struct tm * cur_date = &sentence.date[i];
        if(cmp_date(*min_date, *cur_date)>0){
            min_date = cur_date;
        }
    }
    return min_date;
}
struct tm * find_max_date(struct Sentence_Date sentence){
    struct tm * max_date = &sentence.date[0];
    for(int i = 1; i < sentence.size; i++){
        struct tm * cur_date = &sentence.date[i];
        if(cmp_date(*max_date, *cur_date)<0){
            max_date = cur_date;
        }

    }
    return max_date;
}

int sort_text(const void * object1, const void * object2){
    struct Sentence_Date sentence1 = *(struct Sentence_Date *)object1;
    struct Sentence_Date sentence2 = *(struct Sentence_Date *)object2;
    struct tm * min_date1 = find_min_date(sentence1);
    struct tm * min_date2 = find_min_date(sentence2);
    return cmp_date(*min_date1, *min_date2);
}

void operation_0(){
    int size_text = 0;
    char ** text = read_text(&size_text);
    for(int i=0; i!=size_text; i++){
        printf("%s.\n", text[i]);
        free(text[i]);
    }
    free(text);
}

int in_sentence(struct Sentence_Date sentence, struct tm now_date){
    for(int i=0; i!=sentence.size; i++){
        if( (sentence.date[i].tm_year==now_date.tm_year) && (sentence.date[i].tm_mon==now_date.tm_mon))
            return 1;
    }
    return 0;
}

void operation_1(){
    int size_text = 0;
    char ** text = read_text(&size_text);
    struct Sentence_Date * new_text = make_text(text, size_text);
    time_t mytime = time(NULL);
    struct tm now_date = *localtime(&mytime);
    now_date.tm_year+=1900;
    now_date.tm_mon++;
    for(int i=0; i!=size_text; i++){
        if(in_sentence(new_text[i], now_date))
            print_sentence(new_text[i]);
        free(new_text[i].date);
    }
    free(new_text);
}

void operation_2(){
    int size_text = 0;
    char ** text = read_text(&size_text);
    struct Sentence_Date * new_text = make_text(text, size_text);
    qsort(new_text, size_text, sizeof(struct Sentence_Date), sort_text);
    for(int i = 0; i!=size_text; i++){
        print_sentence(new_text[i]);
        free(new_text[i].date);
    }
    free(new_text);

}
int check_19_century(struct Sentence_Date sentence){
    for(int i = 0; i!=sentence.size; i++){
        if((sentence.date[i].tm_year > 1900) || (sentence.date[i].tm_year < 1801)){

            return 0;
        }
    }
    return 1;
}
void operation_3(){
    int size_text = 0;
    char ** text = read_text(&size_text);
    struct Sentence_Date * new_text = make_text(text, size_text);
    for(int i=0; i!=size_text; i++){
        if (!check_19_century(new_text[i])){
            print_sentence(new_text[i]);
        }
        free(new_text[i].date);
    }
    free(new_text);

}
void operation_4(){
    int size_text = 0;
    char ** text = read_text(&size_text);
    struct Sentence_Date * new_text = make_text(text, size_text);
    for(int i=0; i!= size_text; i++){
        struct tm min_date = *find_min_date(new_text[i]);
        struct tm max_date = *find_max_date(new_text[i]);
        printf("%d/%d/%d %d/%d/%d.\n", min_date.tm_mday, min_date.tm_mon, min_date.tm_year,
                                     max_date.tm_mday, max_date.tm_mon, max_date.tm_year);
        free(new_text[i].date);
    }
    free(new_text);
}


// NEW FUNCTIONS START ------------------------------------------------
void to_bin(char * decimal){
    int d;
    sscanf(decimal, "%d\n", &d);
    //sscanf(pch, "%d/%d/%d\n", &new_date.tm_mday, &new_date.tm_mon, &new_date.tm_year);
    printf("0b");
    if(d==0){printf("0");}
    int * bin_d = malloc(sizeof(int));
    int capacity = 1;
    int size = 0;
    while(d > 0) {
        if(size>=capacity){
            capacity *= 2;
            bin_d = realloc(bin_d, capacity*sizeof(int));
        }
        bin_d[size] = d % 2;
        d = d / 2;
        size++;
}
for(int i = size-1; i!=-1; i--){
    printf("%d", bin_d[i]);
}



}

void operation_9(){
    int size_text = 0;

    char ** text = read_text(&size_text);
    for(int i=0; i!=size_text; i++){
        char * decimal = malloc(sizeof(char));
        decimal[0]='\0';
        int k = 0;
        for(int t=0; text[i][t]; t++){
            char symbol = text[i][t];
            if(isdigit(symbol)){
                decimal[k]=symbol;
                k++;
                decimal = realloc(decimal, (k+1)*sizeof(char));
                decimal[k]='\0';
                if(t==(strlen(text[i])-1)){
                to_bin(decimal);
                decimal = malloc(sizeof(char));
                k = 0;
                decimal[0]='\0';}
                }
            else{
                if(strlen(decimal)!=0){
                to_bin(decimal);
                decimal = malloc(sizeof(char));
                k = 0;
                decimal[0]='\0';}
                printf("%c", symbol);
            }
        }
        if(strlen(text[i])>0){
        printf(".\n");}
    }
}


// NEW FUNCTIONS END ------------------------------------------------


int main()
{
    printf("Course work for option 4.8, created by Vadim Pozdeev.\n");
    char func_num = getchar();
    switch(func_num)
    {
    case '0':
        operation_0();
        break;
    case '1':
        operation_1();
        break;
    case '2':
        operation_2();
        break;
    case '3':
        operation_3();
        break;
    case '4':
        operation_4();
        break;
    case '5':
        help();
        break;
    case '9':
        operation_9();
        break;
    default:
        printf("ERROR: <Wrong number of operation>\n");

    }
    return 0;
}
