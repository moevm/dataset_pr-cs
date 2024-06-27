
#include "loc.h"
void print_func2(char **text, int *sentence_number) {
    for (int i = 0; i < (*sentence_number); i++) {
        if((*(sentence_number)-i)!=2){
        printf("%s ", text[i]);}
        else {
            printf("%s ", text[i]);
        }
    }
}

char **newFunc(char **text, int *sentenceNumber) {
    for (int i = 0; i < *(sentenceNumber); i++) {
        int buffer = strlen(text[i]);
        int size=0;
        char *newSentence = calloc(strlen(text[i]), sizeof(char));
        for (int j = 0; j < strlen(text[i]); j++) {
            if(size>=(buffer-3)){
                buffer= buffer*1000;
                newSentence = realloc(newSentence, buffer*sizeof(char));
                newSentence[size]='\0';
            };
            char now = text[i][j];
            switch (now) {
                case '0':
                    strcat(newSentence, "X");
                    size+=1;
                    break;
                case '1':
                    strcat(newSentence, "I");
                    size+=1;
                    break;
                case '2':
                    strcat(newSentence, "II");
                    size+=2;
                    break;
                case '3':
                    strcat(newSentence, "III");
                    size+=3;
                    break;
                case '4':
                    strcat(newSentence, "IV");
                    size+=2;
                    break;
                case '5':
                    strcat(newSentence, "V");
                    size+=1;
                    break;
                case '6':
                    strcat(newSentence, "VI");
                    size+=2;
                    break;
                case '7':
                    strcat(newSentence, "VII");
                    size+=3;
                    break;
                case '8':
                    strcat(newSentence, "VIII");
                    size+=4;
                    break;
                case '9':
                    strcat(newSentence, "IX");
                    size+=2;
                    break;
                default:
                    newSentence[size] = now;
                    size+=1;
                    break;
            }
            newSentence[size]='\0';

        }
            newSentence[size]='\0';
            text[i]=newSentence;
    }
    return text;
}

int main() {
    const char *splitters = ".?;";
    int expression;
    int sentence_number = 0;
    printf("Course work for option 4.9, created by Savva Starkov.\n");
    scanf("%d", &expression);
    switch (expression) {
        case 8:
            print_func2(newFunc(delete_dublitacates(split_text(get_text_Input(), &sentence_number, splitters),
                                                   &sentence_number), &sentence_number),
                       &sentence_number);
            break;
        case 0:
            print_func(delete_dublitacates(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                       &sentence_number);
            break;
        case 1: {
            char **text = split_text(get_text_Input(), &sentence_number, splitters);
            text = delete_dublitacates(text, &sentence_number);
            robin_to_imBatman(&text, &sentence_number);
            print_func(text, &sentence_number);
            break;
        }
        case 2:
            print_func(split_to_number_sort(
                    delete_dublitacates(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                    &sentence_number), &sentence_number);
            break;
        case 3:
            print_func(sum_of_numbers_Sort(
                    delete_dublitacates(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                    &sentence_number), &sentence_number);
            break;
        case 4:
            print_func(if_vowel(
                    delete_dublitacates(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                    &sentence_number), &sentence_number);
            break;
        case 5:
            printf("1 - Заменить в тексте подстроки “Robin” (могут быть внутри слова) на подстроку “I am Batman”.\n"
                   "2 - Отсортировать предложения по увеличению количества запятых в предложении.\n"
                   "3 - Удалить все предложения в которых сумма цифр в предложении равняется 13.\n"
                   "4 - Вывести все предложения в которых первое слово начинается с гласной буквы или цифры.\n"
                   "5 - Вывод справки о функциях, которые реализует программа.\n");
            break;
        default:
            fprintf(stderr, "Неправильный выбор функции!\n");
            break;
    }

    return 0;
}

//делит первичный текст на массив предложений
char **split_text(char *text, int *num_sentences, const char *splitters) {
    int count_sentences = 0;
    int end_index = 0;
    char **splitted_text = malloc(sizeof(char *));

    for (int i = 0; i < (int) strlen(text); i++) {
        if (strchr(splitters, text[i]) != NULL) {
            count_sentences++;

            splitted_text = realloc(splitted_text, count_sentences * sizeof(char *));
            splitted_text[count_sentences - 1] = malloc((end_index + 2) * sizeof(char));

            int chr_counter = 0;
            for (int j = end_index; j >= 0; j--) {
                splitted_text[count_sentences - 1][chr_counter++] = text[i - j];
            }
            splitted_text[count_sentences - 1][chr_counter] = '\0';
            remove_lead_spaces(splitted_text[count_sentences - 1]);
            end_index = 0;
            continue;
        }
        end_index++;
    }

    *num_sentences = count_sentences;
    return splitted_text;
}

//получает первичный текст в один массив
char *get_text_Input() {
    char *text = malloc(sizeof(char));
    int size = 0;
    char ch;
    while (strstr(text, "\n\n") == NULL) {
        ch = getchar();
        text[size++] = ch;
        text = (char *) realloc(text, (sizeof(char) * (size + 2)));

    }
    text[size - 2] = '\0';
    return text;
}

void remove_lead_spaces(char *str) {
    char *start = str;
    while (*start && (*start == ' ' || *start == '\t' || *start == '\n')) {
        start++;
    }
    memmove(str, start, strlen(start) + 1);
}

//печатает массив предложений
void print_func(char **text, int *sentence_number) {
    for (int i = 0; i < (*sentence_number); i++) {
        printf("%s\n", text[i]);
    }
}

//case 4
char **if_vowel(char **text, int *sentence_number) {
    int index = 0;
    char **new_text = malloc(sizeof(text));
    char *vowel = "aeouyAEOUY1234567890";

    for (int i = 0; i < (*sentence_number); i++) {
        remove_lead_spaces(text[i]);
        if (strchr(vowel, text[i][0]) != NULL) {
            new_text[index] = text[i];
            index++;
        }
    }
    *sentence_number = index;
    return new_text;
}


int comp_num_sort(const void *a, const void *b) {
    char **sentenceA = (char **) (a);
    char **sentenceB = (char **) b;
    int counterA = 0;
    int counterB = 0;
    for (int i = 0; i < strlen(*sentenceA); i++) {
        if ((*sentenceA)[i] == ',') {
            counterA++;
        }
    }
    for (int i = 0; i < strlen(*sentenceB); i++) {
        if ((*sentenceB)[i] == ',') {
            counterB++;
        }
    }
    return counterA - counterB;
}

//case 2
char **split_to_number_sort(char **text, int *sentence_number) {
    qsort(text, *sentence_number, sizeof(char *), comp_num_sort);
    return text;
}


//case 3
char **sum_of_numbers_Sort(char **text, int *sentence_number) {
    for (int i = 0; i < *sentence_number; i++) {
        char *temp = text[i];
        int sum = 0;
        for (int j = 0; j < strlen(temp); j++) {
            if (isdigit(temp[j])) {
                sum += temp[j] - '0';
            }
        }
        if (sum == 13) {
            free(text[i]);
            for (int k = i; k < (*sentence_number); k++) {
                text[k] = text[k + 1];
            }
            (*sentence_number)--;
            i--;
        }
    }
    return text;


}

//case 1
void robin_to_imBatman(char ***text, int *sentence_number) {

    for (int i = 0; i < (*sentence_number); i++) {
        char *temp = (*text)[i];
        char *findindex = strstr(temp, ROBIN);;
        size_t index = 0;
        while (findindex != NULL) {
            char *new_char = calloc((strlen(temp) + SIZEBATMAN), sizeof(char));
            index = findindex - temp;
            size_t iterator = 0;
            while (iterator < index) {
                new_char[iterator] = temp[iterator];
                iterator++;
            }
            strcat(new_char, BATMAN);
            iterator = SIZEBATMAN + iterator;
            index = index + SIZEROBIN - 1;
            while (index < strlen(temp)) {
                new_char[iterator] = temp[index];
                iterator++;
                index++;
            }
            (*text)[i] = new_char;
            temp = (*text)[i];
            findindex = strstr(temp, ROBIN);;
        }
    }

}


int str_compare_without_register(char *a, char *b) {
    char *NewA = calloc(strlen(a), sizeof(char));
    char *NewB = calloc(strlen(b), sizeof(char));
    for (int i = 0; i < strlen(a); i++) {
        NewA[i] = tolower(a[i]);
    }
    for (int i = 0; i < strlen(b); i++) {
        NewB[i] = tolower(b[i]);
    }
    int result = 0;
    if (strcmp(NewA, NewB) != 0) {
        result = 1;
    }
    return result;

}

//удаляет повторяющиеся предложения после split_text
char **delete_dublitacates(char **text, int *sentence_number) {
    int buffer = 1;
    char **new_text = calloc(buffer, sizeof(char *));
    int new_size = 0;

    new_text[0] = text[0];
    new_size++;
    for (int i = 1; i < (*sentence_number); i++) {
        int flag_dub = 0;
        for (int j = 0; j < new_size; j++) {
            if (str_compare_without_register(text[i], new_text[j]) == 0) {
                flag_dub = 1;
                break;
            }
        }
        if (flag_dub == 0) {
            if (new_size >= buffer) {
                buffer = new_size + 1;
                new_text = realloc(new_text, sizeof(char *) * buffer);
            }
            new_text[new_size++] = text[i];
        }

    }
    *sentence_number = new_size;
    return new_text;

}


void split_char(char *sentence, char *first) {
    char d[] = "\n";
    int i = 0;
    while (sentence[i] != '\n') {
        i++;
    }
    char *new_sentence = calloc(strlen(sentence) - i, sizeof(char));
    char *new_first = calloc(i + 1, sizeof(char));
    char *token;
    token = strtok(sentence, d);
    new_first = strcpy(new_first, token);
    token = strtok(NULL, d);
    new_sentence = strcpy(new_sentence, token);

    sentence = strcpy(sentence, new_sentence);
    first = strcpy(first, new_first);
}

int func_help(char *sentence) {
    int counter = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (isupper(sentence[i])) {
            counter++;
        }
    }

    return counter;

}

char **func_9(char **text, int *sentence_number) {
    char **new_text = calloc(*sentence_number + 1, sizeof(char *));
    int size = *sentence_number;
    char first[122];
    int new_size = 0;
    split_char(text[0], first);
    int upper_first = func_help(first);
    for (int i = 0; i < size; i++) {
        int func_number = func_help(text[i]);
        if (func_number < upper_first) {
            new_text[new_size] = calloc(strlen(text[i]), sizeof(char));
            new_text[new_size] = strcpy(new_text[new_size], text[i]);
            new_size++;
        }
    }
    *sentence_number = new_size;
    return new_text;

}

