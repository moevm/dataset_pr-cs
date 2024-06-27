#include <stdio.h> 
#include <locale.h> // расширение для работы с русскими символами
#include <wchar.h> // расширение для работы с широкими символами

// изз-за работы с wchar перед строками стоит L'..'
// все выводы строк из-за формата wchar выводятся с помощью %ls
void simple_input_output() {
    int i;
    wchar_t text[1000]; //строчка - текст (текстовый массив)
    wchar_t c, previous = L'1'; // Инициализируем previous значением L'\0'
    c = getwchar();
    for (i = 0; i < 1000; i++) {
        previous = c;
        c = getwchar();
        if (c == L'\n' && previous == L'\n') {
            break;  // Если два подряд символа новой строки, то выходим из цикла
        }
        text[i] = c;
        
    }
    //получили text заполненную вводом
    // '\n' - символ перевода строки. !!! '\0' - символ конца строки
    if (i >= 1) {
        text[i] = L'\0'; // Устанавливаем завершающий ноль, чтобы использовать text как строку
        wprintf(L"%ls", text); // Отобразим введенный текст
    } else {
        wprintf(L"Error: Empty input."); // Ошибка если ничего не введено
    }
}

void case_1(){
    wchar_t c = L's';
    wchar_t previous = L'a';
    
    long int mult = 0; // произведение
    while (c != -1){
        previous = c;
        c = getwchar();
        if (c == L'\n' && previous == L'\n'){
            wprintf(L"%ld", mult);
            break;
        }
        
        if (mult == 0 && c != L'\n' && c != L'0') mult = 1;
        
        if ((mult > 0 && c != L'\n' && c != L'0') && (mult * (int)c < 0)){
            wprintf(L"Warning: Buffer is full"); // когда mult переполняется, переменная выдаёт значение <0;
            break;
        }
        if (mult > 0 && c != L'\n' && c != L'0') mult = mult * (int)c;
    }
}
// (int)c - код символа c

char result[100];
wchar_t res[100]; // wchar* res
// wchar_t* - один из вариантов задать символьный массив ()

wchar_t* binary_to_decimal() { // возвращается символьный массив - строка wchar_t
    wchar_t binary[100]; //двоичным числом
    wchar_t previous = L'c', c = L'd';
    int j = 0, i = 0;
    wchar_t* buf = L"Warning: Buffer is full.";
    wchar_t* error = L"Error: Wrong input.";
    int len = 0;
    
    // начало ввода
    while (1){
        if (j == 99) return buf;
        previous = c;
        c = getwchar();
        if (c != L'\n'){
            binary[j] = c;
            j++; // j += 1; j = j + 1
        }
        
        if (c == L'\n' && previous == L'\n') break;  
        
    }
    
    //конец  вывода
    
    binary[j]= L'\0';
    //printf("|%s|",binary);
    
    for (i = 0; binary[i] != L'\0'; i++){
        if (binary[i] != '0' && binary[i] != L'1') return error;
        if (len == 0 && binary[i] == L'1') len = 1;
        if (len > 0) len++;
    }
    if (len > 0 || binary[0]== L'0') len--; // || - логическое ИЛИ. && лог. И
    else{
        return error;
    }
    
    int decimal = 0;
    int base = 1; //степень двойки
    for (i = len - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += base;
        }
        base *= 2; // base = base * 2;
    }

    snprintf(result, 100, "%d", decimal); // конвертируем десятичное число в строк. эта штука работает только с char. поэтому нужно result перевести в wchar_t
    i = 0;
    while(result[i] != L'\0'){
        res[i] = result[i];
        i++;
    }
    res[i] = L'\0';
    // res - строка wchar,которая содержит нужное число
    return res;
}

wchar_t* check_substring(){
    wchar_t* buf =L"Error: Buffer is full";
    wchar_t c = L'a';
    wchar_t find_str[100], str[1000];
    wchar_t previous = L'w';
    int i1 = 0, i2 = 0;
    int i = 0, j = 0;
    int counter = 0;
    
    c = getwchar(); // костыль чтобы убрать с ввода символ переноса строки
    c = L'a';
    
    while (1){
        if (c == L'\n') break;
        c = getwchar();
        if (i1 == 99) return buf;
        find_str[i1] = c;
        i1++;
    }
    find_str[i1-1] = '\0';
    c = getwchar(); // тот же самый костыль чтобы убрать символ переноса строки со ввода
    
    
    while (1){
        previous = c;
        str[i2] = c;
        c = getwchar();
        if (c == L'\n' && previous == L'\n') break;
        if (i2 == 999) return buf;
        i2++;
    }
    
    str[i2] = L'\0';
    
    //printf("|%s|\n|%s|",find_str,str);
    
    while (find_str[counter] != L'\0'){
        counter++;
    }
    
    //printf("|%s|\n|%s|",find_str,str);
    
    if (counter == 0 || str[0] == L'\n' || str[0] == L'\0'){
        return L"0";
    }
    while (str[i] != L'\0'){
        if (j == counter) return L"1";
        if (str[i] == find_str[j]){
            j++;
        }
        else{
            j = 0;
        }
        i++;
    }
    if (j == counter) return L"1";
    return L"0";
}
//работает корректно только на линуксе
int count_vowels() {
    int i = 0, count = 0;
    wchar_t str[100];
    wchar_t vowels[] = L"aeiouyаеёиоуыэюяAEIOUYАЕЁИОУЫЭЮЯ";
    wchar_t wc = L'a', previous = L'c';
    
    for (i = 0; i < 100; i++){
        wc = getwchar();
        str[i] = wc;
        if (previous == L'\n' && wc == L'\n') break;
        previous = wc;
    }
    // завершён ввод строки
    for (i = 0; str[i] != L'\0'; i++) {
        for (int j = 0; j < wcslen(vowels); j++) {
            if (str[i] == vowels[j]) {
                count++;
                break;
            }
        }
    }

    return count;
}




void del_words(){
    wchar_t s1[10000];
    wchar_t out[10000] = {L'\0'};
    wchar_t s2[10000];
    fgetws(s1,9999,stdin);
    fgetws(s2,9999,stdin);
    int flag = 0;
    int start = 0;

    for(int i = 0;i < wcslen(s1);i++){
        flag = 0;
        for(int j = 0;j < wcslen(s2) - 1;j++){
            if(s1[i+j] != s2[j]){
                flag = 1;
                break;
                
            }
            
        }
        if(flag){ 
            if(start == 0 && s1[i] == L' '){
                continue;
            }
          
            out[start++] = s1[i];
            
            
            
        } else {
            i+=wcslen(s2) - 2;
            
        }
        
    }
    
  wprintf(L"%ls",out);  
    
    
}


void information(){
    wprintf(L"Function 1: multiplication codes of all symbols\n");
    wprintf(L"Function 2: Convert decimal to binary string.\n");
    wprintf(L"Function 3: Find substring in string.\n");
    wprintf(L"Function 4: Count russian and english vowels in text.\n");
    wprintf(L"Function 5: Information.\n");
}

int main() {
    setlocale(LC_ALL, ""); // установление локали языка. это необходимо для корректной с русскими символами
    int condition;
    wprintf(L"Course work for option 3.6, created by Alexey Alexandrov.\n");
    wscanf(L"%d", &condition);
    getwchar();
    
    if (condition == 0){
        simple_input_output();
        return 0;
    }
    if (condition == 1){
        case_1();
        return 0;
    }
    else if (condition == 2){
        wprintf(L"%ls", binary_to_decimal());
        return 0;
    }
    else if (condition == 3){
        wprintf(L"%ls", check_substring());
        return 0;
    }
    else if (condition == 4){
        int result;
        result = count_vowels();
        wprintf(L"%d", result);
        return 0;
    }
    else if (condition == 5){
        information();
        return 0;
    }
    else if (condition == 9){
        
        del_words();
        return 0;
    }
    else{
        wprintf(L"Error: Incorrect input. ");
        return 0;
    }
}
