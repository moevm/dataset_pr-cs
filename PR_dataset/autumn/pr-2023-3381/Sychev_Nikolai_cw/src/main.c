#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h> 

#define HELP_MSG "Программа может выполнить одно из введенных пользователем действий и завершить работу:\n0 - Вывод текста после первичной обязательной обработки\n1 - Сортировка все предложений по уменьшению суммарного времени указанного в строке.\n2 - Вывод всех предложений в которых количество слов больше 2 и меньше 7\n3 - Во всем тексте происходит замена согласных строчные букв на заглавные.\n4 - Удаление всех предложений в которых количество слов больше среднего количества слов предложениях.\n5 - Вывод справки о функциях, которые реализует программа.\n"
#define ERR_ALLOC "Error: Ошибка выделения памяти.\n"
#define ERR_COMMAND "Error: Введенной команды не существует.\n"

void print_error(char* err) {
	printf("%s", err);
	exit(1);
}

void print_help() {
	printf("%s", HELP_MSG);
}

void print_text(char** text, int sent_count) {
	for (int i = 0; i < sent_count; i++) {
		printf("%s\n", text[i]);
	}
}

char** get_text(int* sent_count_addr) {
	int N = 20, M = 20;
	char** sentences = (char**) malloc(M * sizeof(char*));
	if (sentences == NULL) print_error(ERR_ALLOC);
	char* sentence = (char*) malloc(N * sizeof(char));
	if (sentence == NULL) print_error(ERR_ALLOC);
	char ch;
	int sent_count = *sent_count_addr;
	int chars = 0;
	char last_2[2] = { 0 };
	sentences[sent_count] = sentence;

	while (1) {
		ch = getchar();
		last_2[0] = last_2[1];
		last_2[1] = ch;
		if (last_2[0] =='\n' && last_2[1] =='\n') {
			sentences[sent_count][chars-1] = 0;
			if (chars-2>=0) sent_count+=1;
			*sent_count_addr = sent_count;
			return sentences; 
		}
		if (chars == 0 && ch == '\t') continue;
		if (chars == 0 && ch == '\n') continue;
		if (chars == 0 && ch == ' ') continue;
		if (chars == 0 && ch == '.') continue;
		if (chars > N-2) {
			N += 10;
			sentence = (char*) realloc(sentence, sizeof(char)*N);
			if (sentence == NULL) {
			    print_error(ERR_ALLOC);
			}
			sentences[sent_count] = sentence;
		}

		sentences[sent_count][chars] = ch;
		chars += 1;
		if (ch == '.') {
			sentences[sent_count][chars] = 0;
			bool flag = true;
			for (int i = 0; i < sent_count; i++) {
				if (!strcasecmp(sentences[i], sentences[sent_count])) {
					flag = false;
					break;
				}
			}
			if (flag) sent_count += 1; 
			else free(sentences[sent_count]);
			if (sent_count > M-2) {
				M += 10;
				sentences = (char**) realloc(sentences, sizeof(char*)*M);
				if (sentences == NULL) print_error(ERR_ALLOC);
			}
			N = 10;
			sentence = (char*) malloc(N * sizeof(char));
			if (sentence == NULL) print_error(ERR_ALLOC);
			sentences[sent_count] = sentence;
			chars = 0;
		}
	}
}

void func3(char** text, int sent_count) {
    for (int i = 0; i < sent_count; i++) {
        char* sentence = text[i];
        for (int j = 0; sentence[j] != '\0'; j++) {
            if (isalpha(sentence[j]) && !isupper(sentence[j]) && strchr("AEIOUaeiou", sentence[j]) == NULL) {
                sentence[j] = toupper(sentence[j]);
            }
        }
    }
    for (int i = 0; i < sent_count; i++) {
		printf("%s\n", text[i]);
	}
}

void func4(char** text, int sent_count) {
    int total_words = 0;  
    int sentence_count = 0;  
    for (int i = 0; i < sent_count; i++) {
        int word_count = 0;  
        for (int j = 0; text[i][j] != '\0'; j++) {
            if (text[i][j] == ' ') {
                word_count++;
            }
        }
        total_words += (word_count + 1);
        sentence_count++;
    }
    int average_words = total_words / sentence_count;
    for (int i = 0; i < sent_count; i++) {
        int word_count = 0;  
        for (int j = 0; text[i][j] != '\0'; j++) {
            if (text[i][j] == ' ') {
                word_count++;
            }
        }
        if (word_count + 1 > average_words) {
            for (int k = i; k < sent_count - 1; k++) {
                text[k] = text[k + 1];
            }
            sent_count--;
            i--; 
        }
    }
    for (int i = 0; i < sent_count; i++) {
		printf("%s\n", text[i]);
	}
}

void func2(char** text, int sent_count) {
    for (int i = 0; i < sent_count; i++) {
        char* sentence = text[i];   
        int word_count = 0;         
        int word_started = 0;       
        for (int j = 0; sentence[j] != '\0'; j++) {
            if (word_started) {
                if (sentence[j] == ' ' || sentence[j] == '.' || sentence[j] == ',' || sentence[j] == '!' || sentence[j] == '?') {
                    word_started = 0;  
                    word_count++;      
                }
            }
            else {
                if (sentence[j] != ' ' && sentence[j] != '.' && sentence[j] != ',' && sentence[j] != '!' && sentence[j] != '?') {
                    word_started = 1;  
                }
            }
        }
        if (word_count > 2 && word_count < 7) {
            printf("%s\n", sentence);
        }
    }
}

int compareTimeStrings(const char* time1, const char* time2) {
    int hh1, mm1, ss1;
    int hh2, mm2, ss2;
    sscanf(time1, "%d-%d-%d", &hh1, &mm1, &ss1);
    sscanf(time2, "%d-%d-%d", &hh2, &mm2, &ss2);
    int totalTime1 = hh1 * 3600 + mm1 * 60 + ss1;
    int totalTime2 = hh2 * 3600 + mm2 * 60 + ss2;
    if (totalTime1 > totalTime2) {
        return -1;
    }
    else if (totalTime1 < totalTime2) {
        return 1;
    }
    else {
        return 0;
    }
}

void func1(char** text, int count_sent) {
    for (int i = 0; i < count_sent - 1; i++) {
        for (int j = 0; j < count_sent - i - 1; j++) {
            char* currentSentence = text[j];
            char* nextSentence = text[j + 1];

            char* ptrCurrentTime = strstr(currentSentence, " ");
            char currentTime[9] = "00-00-00";
            if (ptrCurrentTime != NULL) {
                strncpy(currentTime, ptrCurrentTime + 1, 8);
            }
            char* ptrNextTime = strstr(nextSentence, " ");
            char nextTime[9] = "00-00-00";
            if (ptrNextTime != NULL) {
                strncpy(nextTime, ptrNextTime + 1, 8);
            }
            if (compareTimeStrings(currentTime, nextTime) < 0) {
                char* temp = text[j];
                text[j] = text[j + 1];
                text[j + 1] = temp;
            }
        }
    }
}

typedef struct {
    char *sentence;
    size_t word_count;
    size_t lenght;
} Sentence;

int compareSentences(const void *a, const void *b) {
    const Sentence *sentenceA = (const Sentence *)a;
    const Sentence *sentenceB = (const Sentence *)b;
    if (sentenceA->word_count != sentenceB->word_count) {
        return sentenceA->word_count - sentenceB->word_count;
    }
    return sentenceA->lenght - sentenceB->lenght;
}

//void freeSentences(Sentence *sentences, size_t sentence_count) {
   // for (size_t i = 0; i < sentence_count; i++) {
        //free(sentences[i].sentence);
    //}
    //free(sentences);
//}

char *customTokenizer(char *sentence) {
    char *token = strtok(sentence, " ,.");
    return token;
}

void tokenizeSentence(Sentence *sentence) {
    char *temp_sentence = strdup(sentence->sentence);
    char *token = customTokenizer(temp_sentence);
    while (token != NULL) {
        ++sentence->word_count;
        token = customTokenizer(NULL);
    }
    free(temp_sentence);
}

void func9(char **input_sentences, size_t sentence_count) {
    Sentence *sentences = (Sentence *)malloc(sentence_count * sizeof(Sentence));
    for (size_t i = 0; i < sentence_count; ++i) {
        sentences[i].sentence = strdup(input_sentences[i]);
        sentences[i].word_count = 0;
        sentences[i].lenght = strlen(input_sentences[i]);
        tokenizeSentence(&sentences[i]);
    }
    qsort(sentences, sentence_count, sizeof(Sentence), compareSentences);
    for (size_t i = 0; i < sentence_count; ++i) {
        printf("%s\n", sentences[i].sentence);
    }
    //freeSentences(sentences, sentence_count);
}

int main() {
	printf("Course work for option 4.21, created by Nikolai Sychev.\n");
	int choice = -1;
	int sent_count = 0;
	char** text;
	scanf("%d", &choice);

	switch(choice){
	case 0:
		text = get_text(&sent_count);
		print_text(text, sent_count);
		break;
	case 1:
		text = get_text(&sent_count);
		func1(text, sent_count);
		print_text(text, sent_count);
		break;
	case 2: 
        text = get_text(&sent_count);
        func2(text, sent_count);
        break;
	case 3: 
        text = get_text(&sent_count);
        func3(text, sent_count);
        break;
    case 4: 
        text = get_text(&sent_count);
        func4(text, sent_count);
        break;
	case 5:
		print_help();
		break;
	case 9:
	    text = get_text(&sent_count);
	    func9(text, sent_count);   
	    break;
	default:
		print_error(ERR_COMMAND);
	}
	return 0;
}