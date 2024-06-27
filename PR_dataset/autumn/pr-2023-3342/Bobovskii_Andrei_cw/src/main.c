#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int poww(int number, int exponent)
{
    int result = 1;
    if (exponent==0)
        return 1;
    for(int i = 0; i<exponent;i++)
        result*=number;
    return result;
}

char* reading_text_without_order (int *str_count, int *error_indicator)
{
    int points_error = 0;
    int latin_err = 0;
    int len = 10;
    char c;
    char *text = malloc(len*sizeof(char));
    for(int i = 0; ; i++)
    {
        c = getchar();
        if (c == '\n' && text[i-1]=='\n')
        {
            text[i-1] = '\0';
            break;
        }
        if (c=='.' && text[i]=='.')
        {
            points_error = 1;
        }
        text[i]=c;
        if (i+1==len)
        {
            len+=10;
            text = realloc(text, len*sizeof(char));
        }

        if ((c<48 && c!=32 && c!=46 && c!=44 && c!=0 && c!=10) || (c>57 && c<65) || (c>90 && c<97) || (c>122))
        {
            latin_err = 1;
        }

        if (c=='.')
            (*str_count)++;
    }

    if (text[strlen(text)-1]!='.')
    {
        printf("ERROR!You should've end text with a point!");
        (*error_indicator)=1;
    }

    if (latin_err == 1)
    {
        printf("Error! Only latin letters and numbers.");
        (*error_indicator)=1;
    }
    if (points_error == 1)
    {
        printf("Error! You should not type many points in a row.");
        (*error_indicator) = 1;
    }
    return text;
}

void text_in_order (char ***text, char**text_without_order, int str_count)
{
    int len = 10;
    int sentence_number = 0;
    int symbol_number = 0;
    for (int i = 0; i<str_count; i++)
        (*text)[i] = malloc(len * sizeof(char));
    for (int i = 0; (*text_without_order)[i]; i++, symbol_number++)
    {
        if ((*text_without_order)[i]==' ' && (*text_without_order)[i-1]=='.')
            i++;
        if ((*text_without_order)[i]=='\n' && (*text_without_order)[i-1]=='.')
            i++;
        (*text)[sentence_number][symbol_number] = (*text_without_order)[i];
        if(symbol_number+2==len)
        {
            len+=10;
            (*text)[sentence_number] = realloc((*text)[sentence_number], len*sizeof(char));
        }
        if ((*text_without_order)[i]=='.')
        {
            (*text)[sentence_number][symbol_number+1] = '\0';
            sentence_number++;
            symbol_number=-1;
            len=10;
        }
    }
}

int letter_compare(char a, char b)
{
    if (a==b)
        return 1;
    else
        if (a-b==32 && a>=97 && a<=122)
            return 1;
        else
            if (b-a==32 && b>=97 && b<=122)
                return 1;
            else
                return 0;
}

int string_compare (char *a, char *b)
{
    int j = 0;
    int len_A = strlen(a);
    int len_B = strlen(b);
    if (len_A!=len_B)
        return 0;
    for (int i = 0; i < len_A; i++, j++)
    {
        if (letter_compare(a[i], b[i])==0)
            return 0;
    }
    return 1;
}

void deletion (char ***text, int *str_count)
{
    for (int i = 1; i < *str_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (string_compare((*text)[i], (*text)[j])==1)
                (*text)[i][0] = '\0';
        }
    }
    int j = 0;
    for (int i = 0; i < *str_count; i++)
    {
        if ((*text)[i][0]=='\0')
        {
            j++;
            free((*text)[i]);
            continue;
        }
        (*text)[i-j] = (*text)[i];
    }
    *str_count -= j;
}

void print (char **text, int str_count)
{
    for (int i = 0; i < str_count; i++)
    {
        printf("%s", text[i]);
        if (i+1!=str_count)
            printf("%c", '\n');
    }
}

int is_word (char *text, int i, char *word_one, char *word_two)
{
    int len = strlen(word_one);
    int tumbler = 1;
    for (int j = 0; j < len; j++)
    {
        if (text[i+j]!=word_one[j] && text[i+j]!=word_two[j])
            tumbler=0;
    }
    if (tumbler ==1)
    {
        if (text[i+len]==' ' || text[i+len]=='.' || text[i+len]==',')
        {
            if (i==0)
                return 2;
            if (text[i-1] == ' ' || text[i-1] == ',')
                return 1;
        }
    }
    return 0;
}

void garden (char ***text, int str_count)
{
    for (int i = 0; i < str_count; i++)
    {
        for (int j = 0; j + 6 < strlen((*text)[i]); j++)
        {
            int tumbler = is_word((*text)[i], j, "flower", "FLOWER");
            if (tumbler > 0)
            {
                for (int z = strlen((*text)[i]); z > j; z--)
                {
                    (*text)[i][z+1] = (*text)[i][z];
                }
                if (tumbler == 1)
                    (*text)[i][j] = 'p';
                else
                    (*text)[i][j] = 'P';
                (*text)[i][j+1] = 'l';
                (*text)[i][j+2] = 'a';
                (*text)[i][j+3] = 'n';
                (*text)[i][j+4] = 't';
                (*text)[i][j+5] = 'e';
                (*text)[i][j+6] = 'd';
            }
        }
    }
    print(*text, str_count);
}

void student_count (char **text, int str_count)
{
    int flag = -1;
    int student_count;
    for (int i = 0; i < str_count; i++)
    {
        student_count = 0;
        for (int j = 0; j < strlen(text[i]); j++)
        {
            if (is_word(text[i], j, "student", "STUDENT"))
            {
                student_count++;
                flag = j;
            }
            if (flag == j)
                printf("\033[1;31m%c", text[i][j]);
            if (flag == j - 6)
                printf("%c\033[0m", text[i][j]);
            if (flag!=j && flag != j - 6)
                printf("%c", text[i][j]);
        }
        flag = -1;
        printf("\nAmount of students: %d", student_count);
        if (i!=str_count-1)
            printf("\n");
    }
}

void friends_deletion (char ***text, int *str_count)
{
    for (int i = 0; i < *str_count; i++)
    {
        int count = 0;
        for (int j = 0; j + 6 < strlen((*text)[i]); j++)
        {
            if (is_word((*text)[i], j, "friend", "FRIEND"))
                count++;
        }
        if (count>1)
            (*text)[i][0]='\0';
    }
    int j = 0;
    for (int i = 0; i < *str_count; i++)
    {
        if ((*text)[i][0]=='\0')
        {
            j++;
            free((*text)[i]);
            continue;
        }
        (*text)[i-j] = (*text)[i];
    }
    *str_count -= j;
    print(*text, *str_count);
}

int is_digit (char c)
{
    if (c >= 48 && c<=57)
        return 1;
    else
        return 0;
}

int is_number (char *text, int i)
{
    char c = text[i];
    int len = 0;
    int tumbler = 1;
    for (int j = 0; c!=' ' && c!= ',' && c!='.'; j++)
    {
        len++;
        if (is_digit(c)==0)
            tumbler = 0;
        c = text[i+j+1];
    }
    if (tumbler==0)
        return 0;
    if (i==0)
        return len;
    if (text[i-1]==' ' || text[i-1]==',')
        return len;
    return 0;
}

int max_number (char * text)
{
    int len_arr = 1;
    long* array = malloc(len_arr*sizeof(int));
    for (int i = 0; i < len_arr; i++)
        array[i] = 0;
    int arr_index=0;
    long max = 0;
    long number = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        int len = is_number(text, i);
        if (len>0)
        {
            number = 0;
            for (int j = 0; j<len; j++)
                number += ((int)text[i+j] - 48)*(poww(10, len-j-1));
            array[arr_index] = number;
            arr_index++;
            if (arr_index+1==len_arr)
            {
                len_arr+=1;
                array = realloc(array, len_arr*sizeof(int));
            }
        }
    }
    for (int i = 0; i < len_arr; i++)
        {
            if (max<array[i])
                max = array[i];
        }
    free(array);
    return max;
}

void sort (char ***text, int str_count)
{
    int max_len = 0;
    for (int i = 0; i<str_count; i++)
    {
        if (max_len < strlen((*text)[i]))
            max_len = strlen((*text)[i]);
    }
    char *hollow;
    if (str_count>1)
    {
        for (int i = str_count-1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (max_number((*text)[j])<max_number((*text)[j+1]))
                {
                    hollow = (*text)[j];
                    (*text)[j] = (*text)[j+1];
                    (*text)[j+1] = hollow;
                }
            }
        }
    }
    hollow = NULL;
    print(*text, str_count);
}

void print_with_connector(char **text, char* connector, int str_count)
{
    if (str_count%2==0)
    {
        for (int i = 0; i < str_count/2; i++)
        {
            for (int j = 0; j < strlen(text[i])-1; j++)
                printf("%c", text[i][j]);
            printf("%c", ' ');
            for (int j = 0; j < strlen(connector)-1; j++)
                printf("%c", connector[j]);
            printf("%c", ' ');
            for (int j = 0; j < strlen(text[str_count-1-i]); j++)
                printf("%c", text[str_count-1-i][j]);
            printf("%c", '\n');
        }
    }
    if (str_count%2==1)
    {
        for (int i = 0; i < str_count/2+1; i++)
        {
            for (int j = 0; j < strlen(text[i])-1; j++)
                printf("%c", text[i][j]);
            printf("%c", ' ');
            for (int j = 0; j < strlen(connector)-1; j++)
                printf("%c", connector[j]);
            printf("%c", ' ');
            for (int j = 0; j < strlen(text[str_count-1-i]); j++)
                printf("%c", text[str_count-1-i][j]);
            printf("%c", '\n');
        }
    }
}

void free_all(char **text, char *text_without_order, int  str_count)
{
    free(text_without_order);
    for (int i = 0; i<str_count; i++)
        free(text[i]);
    free(text);
}

void rules()
{
    printf("I can do these following manipulations with text:\n");
    printf("1) Replacing all words \"flower\" with word \"planted\".\n");
    printf("2) Counting amount of words \"student\" in each sentence and marking them with red color.\n");
    printf("3) Deleting all sentences where word \"friend\" appears more than once.\n");
    printf("4) Sorting all sentences by biggest number they contain in descending order.\n");
    printf("0) Showing you your text after only deleting repeating sentences.");
}

int switching(int key)
{
    int error_indicator = 0;
    int str_count = 0;
    char connector[100];
    if (key == 5)
    {
        rules();
        return 0;
    }
    if (key == 8)
    {
        fgets(connector, 100, stdin);
    }
    char *text_without_order = reading_text_without_order(&str_count, &error_indicator);
    char **text = malloc(str_count*sizeof(char*));
    if (error_indicator==1)
    {
        free_all(text, text_without_order, str_count);
        getchar();
        return 0;
    }
    text_in_order(&text, &text_without_order, str_count);
    deletion(&text, &str_count);
    switch(key)
    {
    case 0:
        {
            print(text, str_count);
            break;
        }
    case 1:
        {
            garden(&text, str_count);
            break;
        }
    case 2:
        {
            student_count(text, str_count);
            break;
        }
    case 3:
        {
            friends_deletion(&text, &str_count);
            break;
        }
    case 4:
        {
            sort(&text, str_count);
            break;
        }
    case 8:
        {
            print_with_connector(text, connector, str_count);
            break;
        }
    }
    free_all(text, text_without_order, str_count);

    return 0;
}

int getting_key()
{
    char key_text[123];
    int key;
    printf("%s\n", "Course work for option 4.15, created by Andrei Bobovskii.");
    fgets(key_text, 10, stdin);
    if (strlen(key_text)>2)
    {
        printf("Error. Wrong key.");
        return 0;
    }
    key = key_text[0] - 48;

    if (key!= 0 && key!= 1 && key!= 2 && key!=3 && key!= 4 && key!= 5 && key!= 8)
    {
        printf("Error. Wrong key.");
        return 0;
    }
    switching(key);
    return 0;
}

int main()
{
    getting_key();
    getchar();
    return 0;
}
