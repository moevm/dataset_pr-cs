#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int A = 20, B = 20;
	char** sentences = (char**) malloc(A * sizeof(char*));
	if (sentences == NULL) print_error(ERR_ALLOC);
	char* sentence = (char*) malloc(A * sizeof(char));
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
		if (chars > A-2) {
			A += 10;
			sentence = (char*) realloc(sentence, sizeof(char)*A);
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
			if (sent_count > B-2) {
				B += 10;
				sentences = (char**) realloc(sentences, sizeof(char*)*B);
				if (sentences == NULL) print_error(ERR_ALLOC);
			}
			A = 10;
			sentence = (char*) malloc(A * sizeof(char));
			if (sentence == NULL) print_error(ERR_ALLOC);
			sentences[sent_count] = sentence;
			chars = 0;
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
    for (int s = 0; s < count_sent - 1; s++) {
        for (int f = 0; f < count_sent - s - 1; f++) {
            char* currentSentence = text[f];
            char* nextSentence = text[f + 1];

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
                char* temp = text[f];
                text[f] = text[f + 1];
                text[f + 1] = temp;
            }
        }
    }
}

void func2(char** text, int sent_count) {
    for (int s = 0; s < sent_count; s++) {
        char* sentence = text[s];   
        int word_count = 0;         
        int word_started = 0;       
        for (int f = 0; sentence[f] != '\0'; f++) {
            if (word_started) {
                if (sentence[f] == ' ' || sentence[f] == '.' || sentence[f] == ',' || sentence[f] == '!' || sentence[f] == '?') {
                    word_started = 0;  
                    word_count++;      
                }
            }
            else {
                if (sentence[f] != ' ' && sentence[f] != '.' && sentence[f] != ',' && sentence[f] != '!' && sentence[f] != '?') {
                    word_started = 1;  
                }
            }
        }
        if (word_count > 2 && word_count < 7) {
            printf("%s\n", sentence);
        }
    }
}

void func3(char** text, int sent_count) {
    for (int s = 0; s < sent_count; s++) {
        char* sentence = text[s];
        for (int f = 0; sentence[f] != '\0'; f++) {
            if (isalpha(sentence[f]) && !isupper(sentence[f]) && strchr("AEIOUaeiou", sentence[f]) == NULL) {
                sentence[f] = toupper(sentence[f]);
            }
        }
    }
    for (int s = 0; s < sent_count; s++) {
		printf("%s\n", text[s]);
	}
}

void func4(char** text, int sent_count) {
    int total_words = 0;  
    int sentence_count = 0;  
    for (int s = 0; s < sent_count; s++) {
        int word_count = 0;  
        for (int f = 0; text[s][f] != '\0'; f++) {
            if (text[s][f] == ' ') {
                word_count++;
            }
        }
        total_words += (word_count + 1);
        sentence_count++;
    }
    int average_words = total_words / sentence_count;
    for (int s = 0; s < sent_count; s++) {
        int word_count = 0;  
        for (int f = 0; text[s][f] != '\0'; f++) {
            if (text[s][f] == ' ') {
                word_count++;
            }
        }
        if (word_count + 1 > average_words) {
            for (int t = s; t < sent_count - 1; t++) {
                text[t] = text[t + 1];
            }
            sent_count--;
            s--; 
        }
    }
    for (int s = 0; s < sent_count; s++) {
		printf("%s\n", text[s]);
	}
}

int main() {
	printf("Course work for option 4.21, created by Chalkova Valeriya.\n");
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
	default:
		print_error(ERR_COMMAND);
	}
	return 0;
}