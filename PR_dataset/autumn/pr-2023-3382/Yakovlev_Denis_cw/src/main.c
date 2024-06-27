/*

    Main returns:
0 - correct finish
1 - memory limit of text or sentence

    Source code support:
TODO - must be implemented
IMPROVE - can be improved
EXP - code snippets that need to be explained
*/

//needed libs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//functions

int get_choice(int* choice_link);
int check_memory_limit(char** str);
int validity(char* before, char* symbol);
int strcmp_changed(char** str1, char** str2);
int check_indict(char*** dict, int* dict_len, char** word, int** cnt);
int cmp_5elem(const void* x, const void* y);
int get_code_5elem(char** str);
void intro();
void get_text(char*** text, int* text_len);
void act_with_choice(int* choice, char*** text, int* text_len);
void get_sentence(char** sentence, int* sentence_len);
void print_text(char*** text, int* text_len);
void make_text_right(char*** text, int* text_len);
void delete_repeated_sentences(char*** text, int* text_len, int* sentence_len);
void move_symbols_left(char** sentence, int* sentence_len, int* start);
void print_words(char*** text, int* text_len);
void make_dictionary(char*** text, int* text_len, char*** dict, int** cnt, int* dict_len);
void reverse_words(char*** text, int* text_len);
void swap_2_symbols(char* a, char* b);
void delete_comma_sentences(char*** text, int* text_len);
void sort_words_5elem(char*** text, int* text_len);
void functions_help();
void sort_words_summary(char*** text, int* text_len);
void sort_words(char** str);

// IMPROVE: replace char to wchat_t in whole code and string-functions -> wstring-funcions

int main()
{
    setlocale(LC_ALL, "ru_EN.UTF-8");
    //introduction
    
    intro();
    //create needed values
    
    int choice = 0, text_len = 0;
    char** text;
    
    //cycle of user choice
    
    while(get_choice(&choice));
    
    if(choice != 5)
    {
    	//receive the text
    	
    	get_text(&text, &text_len);
    	
    	//check possible memory limit of text (potential wrong returned code and invalid end)
    	
    	//if(check_memory_limit(text)){return 1;}
    	
    	//repair text
   	 
   	make_text_right(&text, &text_len);
    	
    	//do function of choice
    	
    	act_with_choice(&choice, &text, &text_len);
    	
    	// free allocated memory
    	
    	for(int i = 0; i < text_len; i++)
    	{
    	    free(text[i]);
    	}
    	free(text);
    }
    else
    {
    	act_with_choice(&choice, &text, &text_len);
    }
    
    /*
    
    EXP: explain why "free(): invalid pointer" when
    
    *text = (char**)malloc(...) but no ...calloc(...) in get_text()
    free(text);
    
    */
    
    //correct end
    
    return 0;
}

void intro()
{
    //show introduction
    
    printf("Course work for option 4.6, created by Denis Yakovlev.\n");
}

int get_choice(int* choice_link)
{
    //function works while user do not write correct number: integer 0-5
    
    //create needed values
    
    int input_len = 0;
    char c = getchar();
    char* input = (char*)calloc((input_len+2),sizeof(char));
    input[1] = '\n';
    
    //take the string before '\n'
    
    while(c != '\n')
    {
        
        //end writing if it's not ended
        
        if(input_len >= 2)
        {
            while(getchar() != '\n');
            break;
        }
        
        //continue cycle
        
        input[input_len] = c;
        c = getchar();
        input = (char*)realloc(input, ((input_len++)+2)*sizeof(char));
    }
    
    //check the correction of the received string 
    
    if(!isdigit(input[0]))
    {
        printf("Error: Incorrect type of input.\nTry again!\n");
        free(input);
        return 1;
    }
    else if(input[1] != '\n')
    {
        printf("Error: Incorrect input.\nTry again!\n");
        free(input);
        return 1;
    }
    else if(((int)input[0] < 48) || ((int)input[0] > 53 && ((int)input[0] != 57)))
    {
        printf("Error: Incorrect range of input.\nTry again!\n");
        free(input);
        return 1;
    }
    
    //write choice if all is right
    
    *choice_link = (int)input[0] - 48;
    free(input);
    return 0;
}

void get_sentence(char** sentence, int* sentence_len)
{
    //create needed values
    
    char symbol = getchar();
    char* local_sentence = (char*)malloc((*sentence_len+1)*sizeof(char));
    
    //check memory limit of local_sentence
    
    if(check_memory_limit(&local_sentence)) 
    {
        free(local_sentence);
        *sentence = NULL;
        return;
    }
    
    //cycle input sentence
    
    while(1)
    {
        //write one symbol and take the next
        
        local_sentence[*sentence_len] = symbol;
        symbol = getchar();
        
        //check the end of the cycle
        
        if(symbol == '.' || ((local_sentence[*sentence_len] == '\n') && (symbol == '\n')))
        {
            local_sentence = (char*)realloc(local_sentence, (((*sentence_len)++)+3)*sizeof(char));
            
            //check memory limit of local_sentence
            
            if(check_memory_limit(&local_sentence)) {break;}
            
            local_sentence[*sentence_len] = symbol;
            local_sentence[*sentence_len+1] = '\000';
            break;
        }
        
        //step
        
        local_sentence = (char*)realloc(local_sentence, (((*sentence_len)++)+2)*sizeof(char));
        if(check_memory_limit(&local_sentence)) {break;}
    }
    
    //check memory limit and if possible allocate memory for *sentence
    
    if(check_memory_limit(&local_sentence)) 
    {
        free(local_sentence);
        *sentence = NULL;
        return;
    }
    *sentence = (char*)malloc((*sentence_len+3)*sizeof(char));
    if(check_memory_limit(sentence))
    {
    	free(local_sentence); 
    	return;
    }
    
    //if memory allocated for *sentence, copy local_sentence to *sentence
    
    strncpy(*sentence,local_sentence,*sentence_len+3);
    free(local_sentence);
}

void get_text(char*** text, int* text_len)
{
    //create needed values
    
    int sentence_len = 0;
    char** local_text = (char**)malloc((*text_len+1)*sizeof(char*));
    
    /*
    
    EXP: explain why don't need (segm fault)
    
    //check possible memory limit of local_text
    
    if(check_memory_limit(&local_text[*text_len]))
    {
        for(int i = 0; i <= *text_len; i++)
        {
            free(local_text[i]);
        }
        free(local_text);
        *text = NULL;
        return;
    }
    
    */
    
    //cycle of creating the local_text of strings
    
    while(1)
    {
        //create needed values
        
        sentence_len = 0;
        get_sentence(&local_text[*text_len], &sentence_len);
        
        //check memory limit of string
        
        if(check_memory_limit(&local_text[*text_len])) {break;}
        
        //check the end of local_text
        
        if(local_text[*text_len][sentence_len] == '\n')
        {
            break;
        }
        
        //step
        
        local_text = (char**)realloc(local_text, (((*text_len)++)+2)*sizeof(char*));
        
        if(!(local_text)){break;}
    }
    
    //check interrupt from memory limit 
    
    if(check_memory_limit(&local_text[*text_len]))
    {
        for(int i = 0; i < *text_len; i++)
        {
            free(local_text[i]);
        }
        free(local_text);
        *text = NULL;
        return;
    }
    
    //allocate memory for text (no more: and check possible memory limit)
    
    *text = (char**)malloc((*text_len)*sizeof(char*));
    
    /*
    
    EXP: do not work with it: need to explain why
    
    if(check_memory_limit(*text))
    {
        for(int i = 0; i <= *text_len; i++)
        {
            free(local_text[i]);
        }
        free(local_text);
        *text = NULL;
        return;
    }
    
    */
    
    //copy local_text to text (no errors) and free allocated memory for local_text + make the end of local_text (last sentence = NULL)
    
    local_text[*text_len] = NULL;
    
    for(int i = 0; i < *text_len; i++)
    {
        (*text)[i] = local_text[i];
    }
    free(local_text);
}

int check_memory_limit(char** str)
{
    //check returning of calloc() or malloc() (if NULL: memory limit)
    
    return (*str == NULL);
    
    //IMPROVE: print error with parameters
}

int validity(char* before, char* symbol)
{
    //check if symbol is correct
    
    if(isalnum(*symbol) || (isalnum(*before) && ((*symbol == ' ') || (*symbol == '.') || (*symbol == ','))))
    {
        return 1;
    }
    return 0;
}

void move_symbols_left(char** sentence, int* sentence_len, int* start)
{
    //move symbols in sentence to left
    
    for(int point = *start; point < *sentence_len - 1; point++)
    {
        (*sentence)[point] = (*sentence)[point+1];
        if(point == *sentence_len - 2){(*sentence)[point+1] = '\000';}
    }
}

// TODO: сделать освобождение памяти для пустых and recursion предложений и перенос указателей на строки в text и изменить print_text() при пустой строке

void make_text_right(char*** text, int* text_len)
{
    //create needed values
    
    int sentence_len = 0;
    char before;
    //check if every symbol on text is correct
    
    for(int i = 0; i < *text_len; i++)
    {
        //before symbol = NULL
        
        before = '\000';
        sentence_len = strlen((*text)[i]);
        
        //check if every symbol in sentence is correct
        
        for(int j = 0; j < sentence_len; j++)
        {
            //nullify symbol if it's not correct
            
            if(!(validity(&before, &(*text)[i][j])))
            {
                move_symbols_left(&(*text)[i], &sentence_len, &j);
                j--;
                sentence_len = strlen((*text)[i]);
            }
            else
            {
                before = (*text)[i][j];
            }
        }
        
        // exception: before ('.') (' ' or ',')
        
        (*text)[i][sentence_len-1] = '.';
    }
    
    //make text without reprated sentences
    
    delete_repeated_sentences(text, text_len, &sentence_len);
}

void delete_repeated_sentences(char*** text, int* text_len, int* sentence_len)
{
    //check every sentences in pairs
    
    for(int i = 0; i < *text_len - 1; i++)
    {
        for(int j = i+1; j < *text_len; j++)
        {
            //compare sentences
            
            if(strcmp_changed(&(*text)[i], &(*text)[j]))
            {
                //nullify repeated sentence
                
                //IMPROVE: free allocated memory, len--, move left next sentences in array (text)
                
                for(int k = 0; k < strlen((*text)[j]); k++)
                {
                    (*text)[j][k] = '\000';
                }
            }
        }
    }
}

int strcmp_changed(char** str1, char** str2)
{
    //create needed values
    
    int flag = 1;
    
    //check size of sentences
    
    if(strlen(*str1) != strlen(*str2))
    {
        flag = 0;
    }
    else
    {
        //check every symbols in pairs
        
        for(int iter = 0; iter < strlen(*str1); iter++)
        {
            //compare symbols
            
            if(tolower((*str1)[iter]) != tolower((*str2)[iter]))
            {
                flag = 0;
                break;
            }
        }
    }
    
    //return result of compare
    
    return flag;
}

void print_text(char*** text, int* text_len)
{
    // print every sentence of text (while i < count of sentences)
    for(int i = 0; i < *text_len; i++)
    {
        if(*(*text)[i] != '\000')
        {
            printf("%s\n", (*text)[i]);
        }
    }
}

void print_words(char*** text, int* text_len)
{
    //create needed values
    int dict_len = 0;
    char** dict;
    int* cnt;
    
    //create dictionary of words from text and array of their repeats
    
    make_dictionary(text, text_len, &dict, &cnt, &dict_len);
    
    //print list (word - count of repeats)
    
    for(int i = 0; i < dict_len; i++)
    {
    	printf("%s - %d\n", dict[i], cnt[i]);
    	free(dict[i]);
    }
    free(dict);
    free(cnt);
}

void make_dictionary(char*** text, int* text_len, char*** dict, int** cnt, int* dict_len)
{
    //create needed values
    
    int word_len = 0;
    *dict = (char**)calloc(((*dict_len)+1),sizeof(char*));
    *cnt = (int*)calloc(((*dict_len)+1),sizeof(int));
    char* word = (char*)calloc(word_len+1, sizeof(char));
    
    //check every symbol in text
    
    for(int i = 0; i < *text_len; i++)
    {
    	for(int j = 0; j < strlen((*text)[i]); j++)
    	{
    	    //check the end of word
    	    
    	    if(!(isalnum((*text)[i][j])))
    	    {
    	    	//make correct len of word
    	    	
    	        if(word_len < strlen(word))
    	        {
    	            word[word_len] = '\000';
    	        }
    	        
    	        //check if word is already in the dictionary
    	        
    	        if(!(check_indict(dict, dict_len, &word, cnt)))
    	        {
    	            //add new word to dictionary
    	        
    	            (*dict)[*dict_len] = (char*)calloc(word_len+1, sizeof(char));
    	            strcpy((*dict)[*dict_len], word);
    	            (*cnt)[*dict_len] = 1;
    	            *dict = (char**)realloc(*dict, ((*dict_len)+2)*sizeof(char*));
    	    	    *cnt = (int*)realloc(*cnt, (((*dict_len)++)+2)*sizeof(int));
    	    	}
    	    	
    	    	//nullify values
    	    	
    	    	//EXP: free allocated memory and try allocate again - do not work
    	    	
    	    	for(int i_w = 0; i_w < word_len; i_w++)
    	    	{
    	    	    word[i_w] = '\000';
    	    	}
    	    	word_len = 0;
    	    }
    	    else
    	    {
    	    	//memorize every symbol of word
    	    	
    	        //TODO: make max len of word and compare with word_len for realloc()
    	        
    	    	word[word_len] = tolower((*text)[i][j]);
    	    	word = (char*)realloc(word, ((word_len++)+2)*sizeof(char));
    	    }
    	}
    }
}

int check_indict(char*** dict, int* dict_len, char** word, int** cnt)
{
    //compare every word in dictionary with new word

    for(int iter = 0; iter < *dict_len; iter++)
    {
    	//word is already in the dictionary
    
    	if(strcmp_changed(word, &(*dict)[iter]))
    	{
    	    (*cnt)[iter]++;
    	    return 1;
    	}
    }
    return 0;
}

void reverse_words(char*** text, int* text_len)
{
    //create needed values

    int left = 0, right = 0, memo = 0;
    
    //check every symbol in the text
    
    for(int i = 0; i < *text_len; i++)
    {
    	//nullify values
    
        left = 0;
        right = 0;
        memo = 0;
    	for(int j = 0; j < strlen((*text)[i]); j++)
    	{
    	    //check the end of word
    	
    	    if(!(isalnum((*text)[i][j])))
    	    {
    	    	//set end of word
    	    
    	    	right = j - 1;
    	    	memo = j + 1;
    	    	
    	    	//reverse word
    	    	
    	    	while(right - left > 0)
    	    	{
    	    	    swap_2_symbols(&(*text)[i][left], &(*text)[i][right]);
    	            right--;
    	            left++;
    	    	}
    	    	
    	    	//set start of word
    	    	
    	    	left = memo;
    	    	right = memo;
    	    }
    	}
    }
}

void swap_2_symbols(char* a, char* b)
{
    //swap 2 elements
    
    char x = *a;
    *a = *b;
    *b = x;
}

void delete_comma_sentences(char*** text, int* text_len)
{
    //set flag value

    int flag = 0;
    
    //check every sy,bol in the text
    
    for(int i = 0; i < *text_len; i++)
    {
    	//nullify flag value
    
   	flag = 0;
   	
   	//check if comma is in sentence
   	
    	for(int j = 0; j < strlen((*text)[i]); j++)
    	{
    	    if((*text)[i][j] == ',')
    	    {
    	    	flag = 1;
    	    	break;
    	    }
    	}
    	
    	//nullify sentence if flag is True
    	
    	if(flag)
    	{
    	    for(int j = 0; j < strlen((*text)[i]); j++)
    	    {
    		(*text)[i][j] = '\000';
    	    }
    	}
    }
}

void sort_words_5elem(char*** text, int* text_len)
{
    //quick sort with comparator

    qsort(*text, *text_len, sizeof(char*), cmp_5elem);
}

int cmp_5elem(const void* x, const void* y)
{
    //take code of 5 element 

    int a = get_code_5elem(&(*(char**)x));
    int b = get_code_5elem(&(*(char**)y));
    
    //compare
    
    if(a > b)
    {
    	return -1;	
    }
    else if(a < b)
    {
    	return 1;
    }
    else
    {
    return 0;
    }
}

int get_code_5elem(char** str)
{
    //check len of sentence

    if(strlen(*str) >= 5)
    {
    	//check if 5 element is separator of words
    
    	if((*str)[4] == ' ' || (*str)[4] == ',')
    	{
    	    return((int)((*str)[5]));
    	}
    	
    	/*Couldn't be case:
    	
    	else if(((*str)[4] == ' ' || (*str)[4] == ',') && strlen(*str) == 5)
    	{
    	    return((int)((*str)[3]));
    	}
    	
    	*/
    	
    	else
    	{
    	    return((int)((*str)[4]));
    	}
    }
    else
    {
    	//sentence len < 5
    
        return (-1);
    }
}

void functions_help()
{
    //display information of functions

    printf("Function 0: Show text after first correction.\n");
    printf("Function 1: Show all words in the text and the count of their repetitions.\n");
    printf("Function 2: Reverse every word in the text.\n");
    printf("Function 3: Remove centences with comma.\n");
    printf("Function 4: Sort sentences to reduse the code value of the 5 symbol. If there are no 5 symbol, then the code is '-1'. If 5 symbol is a separator of words, then take 6 symbol.\n");
    printf("Function 5: Display information about all functions.\n");
    printf("Function 9: Sort words in sentences to summary of numbers in them.\n");
}

void sort_words_summary(char*** text, int* text_len)
{
    for(int iterator = 0; iterator < *text_len; iterator++)
    {
        sort_words(&(*text)[iterator]);
    }
}

void sort_words(char** str)
{
    int cnt_words = 0, summary = 0;
    int* summary_inwords = (int*)malloc((cnt_words+1)*sizeof(int));
    char** ptr_words = (char**)malloc((cnt_words+1)*sizeof(char*));
    for(int i = 0; i < strlen(*str); i++)
    {
        if(((*str)[i] == ' ') || ((*str)[i] == ',') || ((*str)[i] == '.'))
        {
            summary_inwords[cnt_words] = summary;
            ptr_words[cnt_words] = &(*str)[i];
            if((*str)[i] != '.')
            {
                summary_inwords = (int*)realloc(summary_inwords, ((cnt_words++)+1)*sizeof(int));
                ptr_words = (char**)realloc(summary_inwords, ((cnt_words)+1)*sizeof(char*));
            }
            summary = 0;
        }
        else
        {
            if(((*str)[i] <= 57) && ((*str)[i] >= 48))
            {
                summary += (*str)[i] - 48;
            }
        }
    }
    cnt_words++;
    for(int i = 0; i < cnt_words - 1; i++)
    {
        for(int j = i+1; j < cnt_words; i++)
        {
            if(summary_inwords[i] < summary_inwords[j])
            {
                int k = 0;
                char* check_end = ptr_words[j];
                char* start = ptr_words[j];
                char* start1 = ptr_words[i];
                start -= 2;
                while(isalnum(*check_end))
                {
                    check_end++;
                    k++;
                }
                char* memo = (char*)malloc(k*sizeof(char));
                check_end = ptr_words[j] - 1;
                k = 0;
                while(isalnum(*check_end))
                {
                    memo[k] = *check_end;
                    check_end++;
                    k++;
                }
                check_end--;
                while(isalnum(*start))
                {
                    *check_end = *start;
                    start--;
                }
                for(int t = 1; t <= k; t++)
                {
                    *start1 = memo[t];
                    start1++;
                }
                start1++;
                *start1 = memo[0];
                ptr_words[j] = start1;
                free(memo);
            }
        }
    }
    free(summary_inwords);
    free(ptr_words);
}

void act_with_choice(int* choice, char*** text, int* text_len)
{
    //do action with choice of user

    switch(*choice)
    {
        case(0):
            print_text(text,text_len);
            break;
        case(1):
            print_words(text,text_len);
            break;
        case(2):
            reverse_words(text,text_len);
            print_text(text,text_len);
            break;
        case(3):
            delete_comma_sentences(text,text_len);
            print_text(text,text_len);
            break;
        case(4):
            sort_words_5elem(text,text_len);
            print_text(text,text_len);
            break;
        case(5):
            functions_help();
            break;
        case(9):
            sort_words_summary(text,text_len);
            print_text(text,text_len);
            break;
        default:
            printf("Error: Imposible action - %d", *choice);
    }
}
