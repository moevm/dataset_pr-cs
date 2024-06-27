#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * readStringInput (void ) {
    char * buffer;
    char currentChar;
    int bufferSize = 0;

    do {
        currentChar = getchar();
        if ( currentChar == '\n' )
            break;
        if ( !bufferSize )
            buffer = (char*) malloc ( ++bufferSize * sizeof(char) );
        else
            buffer = (char*) realloc ( buffer, ++bufferSize * sizeof(char) );
        buffer[bufferSize - 1] = currentChar;
    } while (currentChar != '\n');
    if ( bufferSize != 0 ) {
        buffer = (char*) realloc ( buffer, ++bufferSize * sizeof(char) );
        buffer[bufferSize - 1] = '\0';
    }
    return buffer;
}

int countOccurrences(const char *firstStr, const char *secondStr) {
    int matchCounter = 0;
    int i = 0;
    while (firstStr[i] != '\0') {
        int j = 0;
        int match = 1;
        while (secondStr[j] != '\0') {
            if (firstStr[i] != secondStr[j]) {
                match = 0;
                if(j == 0)
                    i++;
                break;
            }
            i++;
            j++;
        }
        if (match) {
            matchCounter++;
        }
    }
    return matchCounter;
}

int areStringsEqual(const char *firstStr, const char *secondStr) {
    while (*firstStr != '\0' && *secondStr != '\0') {
        if (*firstStr != *secondStr) {
            return 0;
        }
        firstStr++;
        secondStr++;
    }
    return (*firstStr == '\0' && *secondStr == '\0');
}

int getMonthIndex(const char *firstStr) {
    char *monthNames[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
    int montheIndex = -1;
    for(int i=0; i<12; i++) {
        if(areStringsEqual(firstStr,monthNames[i])) {
            montheIndex=i;
            return montheIndex;
        }
    }
    return montheIndex;
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int parseDateString(char *dateStr, int *day, int *year, char *month) {
    int i = 0;

    // Parse day
    while (dateStr[i] != ' ') {
        if (dateStr[i] >= '0' && dateStr[i] <= '9') {
            *day = (*day) * 10 + (dateStr[i] - '0');
            i++;
        } else {
            return -1;  // Invalid character in day
        }
    }

    i++;

    // Parse month
    int j = 0;
    while (dateStr[i] != ' ') {
        if ((int)dateStr[i] >= 97 && (int)dateStr[i] <= 122) {
            month[j++] = dateStr[i++];
        } else if ((int)dateStr[i] >= 65 && (int)dateStr[i] <= 90) {
            month[j++] = (char)(int)dateStr[i++] + 32;
        } else {
            return -1;  // Invalid character in month
        }
    }

    month[j] = '\0';
    i++;

    // Parse year
    while (dateStr[i] != '\0') {
        if (dateStr[i] >= '0' && dateStr[i] <= '9') {
            *year = (*year) * 10 + (dateStr[i] - '0');
            i++;
        } else {
            return -1;  // Invalid character in year
        }
    }

    return 0;  // Successful parsing
}

int calculateDaysUntilNextLeapYear(int day, int year, char *month) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int nextLeapYear = year + 1;
    while (!isLeapYear(nextLeapYear)) {
        nextLeapYear = nextLeapYear + 1;
    }

    int monthIndex = getMonthIndex(month);
    if (monthIndex < 0) {
        return -1;  // Invalid month
    }

    int daysUntilLeapYear = 0;
    for (int yearCounter = 0; yearCounter < (nextLeapYear - year); yearCounter++) {
        if (isLeapYear(year + yearCounter)) {
            daysInMonth[1] = 29;
        } else {
            daysInMonth[1] = 28;
        }
        for (int monthCounter = monthIndex; monthCounter < 12; monthCounter++) {
            daysUntilLeapYear += daysInMonth[monthCounter];
        }
        monthIndex = 0;
    }
    daysUntilLeapYear -= day - 1;

    return daysUntilLeapYear;
}

int daysUntilNextLeapYear(char *dateStr) {
    int day = 0, year = 0;
    char month[4];
    // int i = 0;

    // Parse the date string and extract day, month, and year
    if (parseDateString(dateStr, &day, &year, month) != 0) {
        return -1;  // Error in parsing
    }

    // Calculate the days until the next leap year
    int daysUntilLeapYear = calculateDaysUntilNextLeapYear(day, year, month);
    return daysUntilLeapYear;
}

void removeExtraSpaces(char *firstStr) {
    int sourceIndex = 0, destinationIndex = 0;
    int spaceFlag = 1;

    // Process the string
    for (sourceIndex = destinationIndex; firstStr[sourceIndex] != '\0'; sourceIndex++) {
        if (firstStr[sourceIndex] != ' ' && firstStr[sourceIndex] != '\t' && firstStr[sourceIndex] != '\n' && firstStr[sourceIndex] != '\r') {
            firstStr[destinationIndex++] = firstStr[sourceIndex];
            spaceFlag = 0;
        } else if (spaceFlag == 0) {
            firstStr[destinationIndex++] = ' ';
            spaceFlag = 1;
        }
    }

    // Remove trailing spaces, tabs, newlines, and carriage return characters
    while (destinationIndex > 0 && (firstStr[destinationIndex - 1] == ' ' || firstStr[destinationIndex - 1] == '\t' || firstStr[destinationIndex - 1] == '\n' || firstStr[destinationIndex - 1] == '\r')) {
        destinationIndex--;
    }

    // Null-terminate the modified string
    firstStr[destinationIndex] = '\0';
}

void removeDigits(char *inputString) {
    char *src = inputString;
    char *dst = inputString;

    while (*src) {
        if (*src < '0' || *src > '9') {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';  // Null-terminate the resulting string
}

void convertDigitToRoman(char txt[],char resTxt[]){
    char *nums[] = {"X","I","II","III","IV","V","VI","VII","VIII","IX"};
    int index = 0;
    
    while(*txt != '\0'){
        if(*txt < '0' || *txt > '9'){
            resTxt[index++] = *txt;
        }else{
            int num = *txt - '0';
            int j = 0;
            while(nums[num][j] != '\0'){
                resTxt[index++] = nums[num][j++];
            }
        }
        txt++;
    }
    resTxt[index] = '\0';
}

void printHelp() {
    printf("1: Find occurrences in a text\n"
           "2: Calculate the number of days until the next leap year\n"
           "3: Remove extra spaces from a text\n"
           "4: Remove digits from a text\n"
           "5: Output help about functions.\n"
           "9: Convert digits to roman numeral\n");
}


void firstTask() {
    char *firstString,*secondString;
    int result = 0;

    firstString= readStringInput();
    secondString = readStringInput();
    result= countOccurrences(firstString,secondString);
    printf("%d\n", result);

    free(firstString);
    free(secondString);
}

void secondTask() {
    char *firstString;
    int result = 0;

    firstString = readStringInput();
    if(firstString[0] < '0' || firstString[0] > '9'){
        exit(EXIT_SUCCESS);
    }
    result = daysUntilNextLeapYear(firstString);
    if(result < 0) {
        printf("Error: Incorrect input.");
        exit(EXIT_SUCCESS);
    }

    printf("%d\n",result);
    free(firstString);
}

void thirdTask() {
    char *firstString;

    firstString = readStringInput();
    removeExtraSpaces(firstString);
    printf("%s\n", firstString);

    free(firstString);
}

void fourthTask() {
    char *firstString;

    firstString = readStringInput();
    removeDigits(firstString);
    printf("%s\n", firstString);

    free(firstString);
}

void ninthTask(){
    char *firstString = readStringInput();
    char resultString[strlen(firstString)*4];

    convertDigitToRoman(firstString,resultString);

    printf("%s\n",resultString);
    free(firstString);
}

int readTaskNumber() {
    char choice[4];
    int num;

    if (fgets(choice, sizeof(choice), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    if (strlen(choice) > 2 || (strlen(choice) == 2 && choice[1] != '\n')) {
        printf("Wrong data. Please enter a single digit.\n");
        return 0;
    }

    num = choice[0] - '0';

    return num;
}

void executeTask() {
    int choice = readTaskNumber();

    switch(choice) {
    case 1:
        firstTask();
        break;
    case 2:
        secondTask();
        break;
    case 3:
        thirdTask();
        break;
    case 4:
        fourthTask();
        break;
    case 5:
        printHelp();
        break;
    case 8:
        ninthTask();
        break;
    default:
        printf("Error: Incorrect input.");
        break;
    }
}

int main() {
    printf ("Course work for option 3.3, created by Belaid Farouk.\n");
    fflush(stdout);

    executeTask();

    return 0;
}
