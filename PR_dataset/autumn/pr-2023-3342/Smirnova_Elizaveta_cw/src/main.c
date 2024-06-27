#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void free_memory(char **text, int str_number)
{
    for (int i = 0; i < str_number; i++)
    {
        free(text[i]);
    }
    free(text);
}
void read_char(char* text, int* counter)
{
    int is_working = 1;
    char symbol = 0, prev_symb = 0;

     while (is_working)
    {
        prev_symb = symbol;
        symbol = getchar();

        if (symbol == '\n' && prev_symb == '\n')
        {
            is_working = 0;
        }
        else
        {
            if (symbol != '\n')
            {
                text[*counter] = symbol;
                if(&text[*counter]==NULL)
                {
                    fprintf(stderr, "Error: memory allocation error\n");
                    free_memory(&text, *counter);
                    exit(0);
                }
                (*counter)++;

                text = (char*)realloc(text, sizeof(char) * (*counter + 1));
            }
        }
    }

}

void check_last_dot(char* text, int* counter)
{
    if (text[(*counter)-1] != '.')
    {
        text = (char*)realloc(text, sizeof(char) * ((*counter) + 1));
        text[*counter] = '.';

        if(&text[*counter]==NULL)
        {
            fprintf(stderr, "Error: memory allocation error\n");
            free_memory(&text, *counter);
            exit(0);
        }

        (*counter)++;
    }
}

int find_max_str(char* text, int* counter, int* length)
{
     int chr_counter = 0, max_str = 0 ;

    for (int i = 0; i < (*length); i++)
    {
        if (text[i] == '.')
        {
            (*counter)++;
            chr_counter++;

            if (chr_counter > max_str)
                max_str = chr_counter;

            chr_counter = 0;
        }
        else
        {
            chr_counter++;
        }
    }

    return max_str;
}

void fill_array(char** result, char* text, int* length)
{
  int row = 0, col = 0;

    for (int i = 0; i < (*length); i++)
    {
        if ( !(((isspace(text[i]))) && (col == 0)) )
        {
             if(&result[row]==NULL)
            {
                fprintf(stderr, "Error: memory allocation error\n");
                free_memory(result, row);
                exit(0);
            }

            if (text[i] == '.')
            {
                result[row][col] = text[i];
                row++;
                col = 0;
            }
            else
            {
                result[row][col] = text[i];
                col++;
            }
        }
    }
}

char** input_text(int* str_number)
{
    char* text = (char*)calloc(1, sizeof(char));
    int counter = 0, length = 0, max_str = 0;

    read_char(text, &counter);
    check_last_dot(text, &counter);

    length = counter;
    counter = 0;
    max_str = find_max_str(text, &counter, &length);

    int str_count = counter;
    *str_number = str_count;

    char** result = (char**)malloc(sizeof(char*) * str_count);

    for (int i = 0; i < str_count; i++)
    {
        result[i] = (char*)calloc(max_str + 1, sizeof(char));
    }

    fill_array(result, text, &length);

    free(text);
    return result;
}
void output_text(char** text, int* str_number)
{
    for ( int i = 0; i < *str_number; i++)
    {
        if ( text[i][0] != '.')
        {
            printf("%s\n", text[i]);
        }
    }
}

char** delete_double(char** text, int* str_number)
{
    for (int i = 0; i < *str_number; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (strlen(text[i]) != strlen(text[j]))
            {
                continue;
            }
            else
            {
                int k = 0;
                for (int l = 0; l < strlen(text[i]); l++)
                {
                    if (tolower(text[i][l]) == tolower(text[j][l]))
                    {
                        k += 1;
                    }
                }
                if (k == strlen(text[i]))
                {
                    for (int m = i; m < *str_number; m++)
                    {
                        text[m] = text[m + 1];
                    }
                    i = i - 1;
                    *str_number = *str_number - 1;
                }
            }
        }
    }
    return text;
}

// Преобразовать предложения так, чтобы каждое слово в нем начиналось с заглавной буквы, а остальные символы слова были строчными.
void convert_registers(char** text, int* str_number)
{
    int len_sent, count_caps = 0;
    char* sentence;

    for (int j = 0; j < *str_number; j++)
    {
        sentence = text[j];
        len_sent = strlen(sentence);

        for (int i = 0; i < len_sent-1; i++)
        {
            if (i == 0)
            {
                sentence[i] = toupper(sentence[i]);
            }

            if ((sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == '\t') && (isalpha(sentence[i+1])))
            {
                sentence[i+1] = toupper(sentence[i+1]);
            }
        }
    }

    for (int i = 0; i < *str_number; i++)
    {
        sentence = text[i];
        len_sent = strlen(text[i]);

        for (int j = 1; j < len_sent; j++)
        {
            if (sentence[j]!=' ' && sentence[j]!='\t' && sentence[j]!=',')
            {
                count_caps += 1;
            }

            else
            {
                count_caps = 0;
            }

            if (count_caps > 1)
            {
                sentence[j] = tolower(sentence[j]);
            }
        }
    }
}
//Удалить все предложения, в которых есть число 2018 (даже если оно  внутри какого-то слова).
void remove_sent(char **text, int *str_number)
{
    for (int i = 0; i < *str_number; i++)
    {
        if ((strstr(text[i], "2018")) != NULL)
        {
            for (int j = i; j < *str_number; j++)
            {
                text[j] = text[j + 1];
            }

            *str_number = *str_number - 1;
            i--;
        }
    }
}
//Отсортировать предложения по увеличению суммы цифр встречаемых в предложении. Если в предложении нет цифр, то сумма цифр данного предложения равняется ∞.
void sort_rise_sum(char **text, int *str_number)
{
    char* temporary_str;

    for (int k = 0; k < *str_number; k++)
    {
        float prev_sum = INFINITY, sum = 0;

        for (int i = *str_number-1; i >= k; i--)
        {
            int len_sent = strlen(text[i]);
            int count = 0;

            for (int j = 0; j < len_sent; j++)
            {
                if(isdigit(text[i][j]))
                {
                    sum += text[i][j];
                    count += 1;
                }
            }

            if (count == 0)
            {
                sum = INFINITY;
            }

            if (sum > prev_sum)
            {
                temporary_str = text[i+1];
                text[i+1] = text[i];
                text[i] = temporary_str;
                sum = 0;
            }

            else
            {
                prev_sum = sum;
                sum = 0;
            }
        }
    }
}
//Вывести на экран все предложения, в которых встречаются все цифры хотя бы один раз.
void print_all_numbers(char** text, int* str_number)
{
    for (int i = 0; i < *str_number; i++)
    {
        if ( ((strstr(text[i], "0")) == NULL) || ((strstr(text[i], "1")) == NULL) || ((strstr(text[i], "2")) == NULL) || \
            ((strstr(text[i], "3")) == NULL) || ((strstr(text[i], "4")) == NULL) || ((strstr(text[i], "5")) == NULL) || \
            ((strstr(text[i], "6")) == NULL) || ((strstr(text[i], "7")) == NULL) || ((strstr(text[i], "8")) == NULL) || ((strstr(text[i], "9")) == NULL) )
        {
            for (int j = i; j < *str_number; j++)
            {
                text[j] = text[j + 1];
            }

            *str_number = *str_number - 1;
            i--;
        }
    }
}

void nine_function(char** text, int* str_number, char* first_sentence)
{
    int len_first_sentence = strlen(first_sentence);
    first_sentence[len_first_sentence - 1] = '\0';
    int sum_first = 0;
    for(int i = 0; i < len_first_sentence; i++)
    {
        if (isdigit(first_sentence[i]))
        {
            sum_first += first_sentence[i]-'0';
        }

    }
    //printf("%d\n", sum_first);
    for (int i = 0; i < *str_number; i++)
    {
        char* sentence = text[i];
        int len_sentence = strlen(sentence);
        int sum = 0;
        for (int j = 0; j < len_sentence; j++)
        {
            if (isdigit(sentence[j]))
            {
                sum += sentence[j]-'0';
            }
        }
        if (sum > sum_first)
        {
            int num = abs(sum - sum_first);
            printf("(%d) %s\n", num, sentence);
        }
    }

}

void switch_case(int sign)
{
    int str_number = 0;
    char** text;
    char* first_sentence="";
    
    switch (sign)
    {
        case 0:

            text = input_text(&str_number);
            text = delete_double(text, &str_number);
            output_text(text, &str_number);
            break;

        case 1:

            text = input_text(&str_number);
            text = delete_double(text, &str_number);
            convert_registers(text, &str_number);
            output_text(text, &str_number);
            free_memory(text, str_number);
            break;

        case 2:

            text = input_text(&str_number);
            text = delete_double(text, &str_number);
            remove_sent(text, &str_number);
            output_text(text, &str_number);
            free_memory(text, str_number);
            break;

        case 3:

            text = input_text(&str_number);
            text = delete_double(text, &str_number);
            sort_rise_sum(text, &str_number);
            output_text(text, &str_number);
            free_memory(text, str_number);
            break;

        case 4:

            text = input_text(&str_number);
            text = delete_double(text, &str_number);
            print_all_numbers(text, &str_number);
            output_text(text, &str_number);
            free_memory(text, str_number);
            break;

        case 8:


            scanf("\n");
            first_sentence = (char*)malloc(sizeof(char)*201);
            fgets(first_sentence, 201, stdin);//первое пр

            text = input_text(&str_number);
            text = delete_double(text, &str_number);
            nine_function(text, &str_number, first_sentence);
            //output_text(text, &str_number);
            free_memory(text, str_number);

            break;

        case 5:

            printf("Help about the functions:\n0 - text output after the initial mandatory processing.\n1 - convert sentences so that each "\
                   "word in it starts with a capital letter, and the remaining characters of the word are lowercase.\n2 - delete all sentences "\
                   "that contain the number 2018 (even if it is inside some word).\n3 - sort the sentences by increasing the sum of the digits "\
                   "found in the sentence. If there are no digits in the sentence, then the sum of the digits of this sentence is infinity.\n4 - "\
                   "print all sentences in which all numbers occur at least once.\n5 - output "\
                   "help about the functions that the program realizes.\n");
            break;

        default:

            printf("Error: incorrect number\n");
        }
}

int main()
{
    printf("Course work for option 4.2, created by Elizaveta Smirnova.\n");
    int sign;
    scanf("%d", &sign);
    switch_case(sign);
}

