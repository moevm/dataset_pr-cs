#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define RESET "\033[0m"
#define RED "\033[1;31m"

int getLongestRepeatedSequence(const char *sentence, int length)
{
    //char whatsSubstring[100];
    int maxSequence = 1;

    for (int i = 0; i < length; i++)
    {
        for (int j = length - 1; j > i; j--)
        {
            int k = 0;
            while (j + k < length && i + k < j && sentence[i + k] == sentence[j + k])
            {
                if (sentence[i + k] == ' ' || sentence[j + k] == ' ' || sentence[i+k] == ',' || sentence[j+k ]== ',')
                    break;
                k++;
            }

            if (k > maxSequence)
            {
                maxSequence = k;
                //strncpy(whatsSubstring, sentence + i, k);
                //whatsSubstring[k] = '\0';
            }
        }
    }
    //printf("%s\n", whatsSubstring);
    return maxSequence;
}

int compare(const void *arg1, const void *arg2)
{
    const char *a = *(const char **)arg1;
    const char *b = *(const char **)arg2;

    int aLongestRepeatedSequence = getLongestRepeatedSequence(a, strlen(a));
    int bLongestRepeatedSequence = getLongestRepeatedSequence(b, strlen(b));

    //printf("%d %d\n", aLongestRepeatedSequence, bLongestRepeatedSequence);

    return bLongestRepeatedSequence - aLongestRepeatedSequence;
}

void sortingSubsequence(char **text, int count){
    qsort(text, count, sizeof(char*), compare);
}

int my_strcasecmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        int diff = tolower(*s1) - tolower(*s2);
        if (diff != 0) {
            return diff;
        }
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

char * my_strdup (const char *s)
{
  size_t len = strlen (s) + 1;
  void *new = malloc (len);
  if (new == NULL)
    return NULL;
  return (char *) memcpy (new, s, len);
}

void ThreeSymb(char **text, int* length, int cnt){
    
    for (int i = 0; i < *length; i++){
        int len_s = strlen(text[i]);
        int sep_c = 0;
        for (int j = 0; j < len_s; j++){
            if (text[i][j] == ' ' || text[i][j] == ','){
                sep_c += 1;
            }
        }

        if (sep_c > 0){
        char* s = malloc(4);
        
        char sep[3] = " ,";
        char *istr;

        char *line_copy = my_strdup(text[i]);
        int flag = 1;
        istr = strtok(line_copy, sep);
        strncpy(s, istr, 3);
        s[3] = '\0';

        while (istr != NULL)
        {
            if (strncmp(s, istr, 3) != 0)
            {
                flag = 0;
                break;
            }     
            istr = strtok(NULL, sep);
        }

        if (flag == 1)
        {
            strcpy(text[i], "");
            cnt -=1;
        }
        else
        {
            continue;
        }

    }
    else{
        continue;
    }
    }
    *length = cnt;
}

void ThirdSep(char **text, int length){
    for (int i = 0; i < length; i++){
        int len_s = strlen(text[i]);

        int count_sep = 0;

        for (int j = 0; j < len_s; j++){
            if (text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.'){
                count_sep++;
                if (count_sep % 3 == 0){
                memmove(&text[i][j], &text[i][j+1], len_s - j);
                j--;
                len_s--;

            }
            }
            
        }
    }

}

void find_dopsa(char **text, int length) {
    
    for (int i = 0; i < length; i++) {        
        char *istr;
        char sep[10] = " ,";
        char *line_copy = my_strdup(text[i]); 
       
        istr = strtok(line_copy, sep);

        int cnt = 0;
        int len = strlen(istr);


        while (istr != NULL)
        {   
            if (my_strcasecmp(istr, "dopsa") == 0){
                char stt[len+1];
                strncpy(stt,istr-len-1,len+1);
                if (strcmp(stt,"") != 0)

                {
                printf ("Word's position - %d, number of sentence - %d\nPrevious word - %s\n",cnt, i + 1, istr - len - 1);
                len = strlen(istr);
                istr = strtok(NULL, sep);
                
                
                if (istr != NULL){
                    printf("next word - %s\n\n", istr);
                }
                else{
                    printf("%s<<dopsa>> - the last word in sentence.%s\n", RED, RESET);
                }  
                }else{
                    printf ("Word's position - %d, number of sentence - %d\n%s<<dopsa>> - the first word in sentence.%s\n",cnt, i + 1,RED,RESET);
                len = strlen(istr);
                istr = strtok(NULL, sep);
                
                
                if (istr != NULL){
                    printf("next word - %s\n\n", istr);
                }
                else{
                    printf("%s<<dopsa>> - the last word in sentence.%s\n", RED, RESET);
                } 
                }      
            }

            else{
                len = strlen(istr);
                istr = strtok (NULL,sep);
            }
            
            cnt ++;
        }

        cnt = 0;

    }

}

void removeDuplicates(char **text, int* count) {
    for (int i = 0; i < *count - 1; i++) {
        if (strcmp(text[i], "") == 0) 
            continue;

        for (int j = i + 1; j < *count; j++) {
            if (strcmp(text[j], "") == 0) 
                continue;

            if (my_strcasecmp(text[i], text[j]) == 0) {
                free(text[j]);
                *count-=1;
                strcpy(text[j], ""); 
            }
        }
    }
}

void choosingAction(char num_of_func);

char* Input(){
    int length = 0;
    char buf;
    char* text = malloc(sizeof(char));

    while ((buf = getchar())){
            if (length > 0 && text[length-1] == '\n' && buf == '\n'){
                break;
            }
            else{
            text[length++] = buf;
            text = realloc(text, sizeof(char) * (length+1));
        
            }
    }
        text[strlen(text)] = '\0';

    return text;
}

void trim(char *str) {
    int start = 0, end = strlen(str) - 1;

    while (isspace((unsigned char)str[start]))
        start++;

    while ((end >= start) && isspace((unsigned char)str[end]))
        end--;

    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

char** Separator(char* text, int *count){
    char sep[3] = ".";
    int maxSentences = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == '.') {
            maxSentences++;
        }
    }
    int index = 0;
    char **splitted_text = malloc(sizeof(char*) * (maxSentences + 1));
    char* sentence;

    char* istr = strtok(text, sep);
    while (istr != NULL){
        trim(istr);
        sentence = malloc(sizeof(char) * (strlen(istr)+1));

        strncpy(sentence, istr, strlen(istr));
        sentence[strlen(sentence)] = '\0';
        splitted_text[index++] = sentence;
        istr = strtok(NULL, sep);
    }
    *count = index - 1;
    return splitted_text;
}

void Output(char** text, int len){
    for (int i = 0; i < len; i++){
        if (strcmp(text[i], "") != 0){
                printf("%s.\n", text[i]);
                free(text[i]);
        }
        }
    free(text);
}

int main() {
    printf("Course work for option 4.22, created by Gelman Polina.\n");
    char n_cmd;

    scanf("%c\n",&n_cmd);
    if (isdigit(n_cmd) != 0){
        choosingAction(n_cmd);
    }
    else{
        printf("\nError: the entered character is not in the list\n");
        return 0;
    }
    return 0;
}

void deleteSentences(char** text, int count, char* s){
    
    int cnt = 0;
    for (int i = 0; i < strlen(s); i++){
        if (isupper(s[i]) != 0){
            cnt++;
        }
    }
    //printf("%d\n", cnt);
    for (int i = 0; i < count; i++){
        int cnt2 = 0;
        for (int j = 0; j < strlen(text[i]); j++){
            if (isupper(text[i][j]) != 0){
                cnt2++;
            }
        }
        if (cnt2 > cnt){
            strcpy(text[i],"");
        }
    }
Output(text, count);
}


void choosingAction(char num_of_func){
    char* text;
    char** sep_text;
    int count = 0;
    switch (num_of_func)
    {
    case '0':
        text = Input();
        sep_text = Separator(text, &count);
        removeDuplicates(sep_text, &count);
                //printf("%d\n", count);
        Output(sep_text, count);
        break;

    case '1':
        text = Input();
        sep_text = Separator(text, &count);
        removeDuplicates(sep_text, &count);
        //printf("c %d\n", count);
        find_dopsa(sep_text, count);
        Output(sep_text, count);
        break;

    case '2':
        text = Input();
        sep_text = Separator(text, &count);
        removeDuplicates(sep_text, &count);
        //printf("%d\n", count);
        ThirdSep(sep_text, count);
        Output(sep_text, count);
        break;

    case '3':
        text = Input();
        sep_text = Separator(text, &count);
        removeDuplicates(sep_text, &count);
        //printf("%d\n", count);
        ThreeSymb(sep_text, &count, count);
        Output(sep_text, count);
        break;

    case '4':
        text = Input();
        sep_text = Separator(text, &count);
        removeDuplicates(sep_text, &count);
        sortingSubsequence(sep_text, count);
        Output(sep_text, count);
        break;

    case '5':
        printf("\r0 – вывод текста после первичной обязательной обработки\n\
        \r1 – вызов функции под номером 1, которая ищет вхождения слова dopsa\n\
        \r2 – вызов функции под номером 2, которая удаляет каждый третий разделитель слов\n\
        \r3 – вызов функции под номером 3, которая удаляет предложения, в которых у слов одинаковые первые 3 символа\n\
        \r4 – вызов функции под номером 4, которая сортирует предложения по длине подпоследовательности\n\
        \r5 – вывод справки о функциях, которые реализует программа.\n");
        break;

    case '9': ;
        char str[121];
        fgets(str, 121, stdin);
        //printf("%s", str);
        text = Input();
        sep_text = Separator(text, &count);
        removeDuplicates(sep_text, &count);
        deleteSentences(sep_text, count, str);
        break;

    default:
        printf("\nError: number not in range 0 to 5\n");
        break;
    }
}
