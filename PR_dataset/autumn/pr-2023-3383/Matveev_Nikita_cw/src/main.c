
#include "struct.h"
#include "sort.h"
#include "printer.h"
#include "freedom.h"
#include "zero_changer.h"
#include "up_changer.h"
#include "model.h"
#include "vowels_sort.h"
#include "similar.h"
#include "input.h"

void smile(struct Text* start){
    int count = start->size;
    for (int i=0; i<count; i++){
        wchar_t* sent = wcsdup(start->sentences[i]);
        wchar_t* ptr;
        wchar_t* word;
        wchar_t** words = (wchar_t**)malloc(sizeof(wchar_t*));
        int mem =1;
        int len = 1;
        word = wcstok(sent, L",  .\n", &ptr);
        words[0] = wcsdup(word);
        while (word !=NULL){
            if (len +2>= mem){
                mem *= MEM_STEP;
                words = (wchar_t**)realloc(words, mem*sizeof(wchar_t*));
            }
            word = wcstok(NULL, L",  .\n", &ptr);
            if (word != NULL){
                words[len++] = wcsdup(word);
            }
        }

        // :=)
        int c=0;
        wchar_t* smile_word = (wchar_t*)malloc(6*sizeof(wchar_t));
        smile_word[0] = L's';
        smile_word[1] =L'm';
        smile_word[2] =L'i';
        smile_word[3] =L'l';
        smile_word[4] =L'e';
        smile_word[5] =L'\0';
        wchar_t* new_smile = (wchar_t*)malloc(5*sizeof(wchar_t));
        new_smile[0] =L' ';
        new_smile[1] =L':';
        new_smile[2] =L'=';
        new_smile[3] =L')';
        new_smile[0] =L'\0';
        //wchar_t*
        //wprintf(L"%ls\n", smile_word);
        for (int j=0; j<len; j++){
            //wprintf(L"%ls\n", words[j]);

            if (wcscmp(words[j], smile_word)== 0){
                //wprintf(L"%ls\n", words[j]);
                int lenn = wcslen(words[j]);
                words[j] = (wchar_t*)realloc(words[j], (lenn+5)*sizeof(wchar_t));

                for (int jj=0; jj<5; jj++){
                    words[j][jj] = smile_word[jj];
                }
                wcsncat(words[j], L" :=)", 4);
                //words[lenn+5] = L'\0';

                //words[lenn+3] = L'\0';
                //wprintf(L"%ls\n", words[j]);
                c++;
               } //wprintf(L"%ls\n", words[j]);
           }

        free(smile_word);

        wchar_t* my_sentence = wcsdup(start->sentences[i]);
        start->sentences[i] = (wchar_t*)realloc(start->sentences[i], sizeof(wchar_t)*(wcslen(start->sentences[i])+(c*4)+1));
        int len_sent = 0;
        int sum_lens =0;
        int run =0;
        for (int j =0; j<len; j++){
            int len_word =wcslen(words[j]);
            if (len_sent == 0 || len_sent < sum_lens){
                for (int n =0; n<len_word; n++){
                    start->sentences[i][len_sent++] = words[j][n];
                }
                sum_lens += len_word;
            }
            else{
                while(my_sentence[run] != L' ' && my_sentence[run] != L',' && my_sentence[run] != L'\n'){
                    run++;
                }
                while(my_sentence[run] == L' ' || my_sentence[run] == L',' || my_sentence[run] == L'\n' ){
                    start->sentences[i][len_sent++] = my_sentence[run++];
                }
                for (int n =0; n<len_word; n++){
                    start->sentences[i][len_sent++] = words[j][n];
                }
                sum_lens += len_word;

            }
        }
        start->sentences[i][wcslen(my_sentence)+(c*4)-1]= L'.';
        start->sentences[i][wcslen(my_sentence)+(c*4)]= L'\0';
        for (int j =0; j<len; j++){
            free(words[j]);
        }
        free(words);
        free(sent);
        free(my_sentence);


    }
}

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.3, created by Nikita Matveev.\n");
    int number_of_function;
    wscanf(L"%d", &number_of_function);
    if (number_of_function == 5){
        helper();
        return 0;
    }
    else if(number_of_function==0){
        struct Text work_text = read_text();
        zero_changer(&work_text);
        printer(work_text);
        freedom(&work_text);
        return 0;
    }
    else if(number_of_function==1){
        struct Text work_text = read_text();
        zero_changer(&work_text);
        model(work_text);
        freedom(&work_text);
        return 0;
    }
    else if(number_of_function==2){
        struct Text work_text = read_text();
        zero_changer(&work_text);
        up_changer(&work_text);
        printer(work_text);
        freedom(&work_text);
        return 0;
    }
    else if(number_of_function==3){
        struct Text work_text = read_text();
        zero_changer(&work_text);
        vowels_sort(&work_text);
        printer(work_text);
        freedom(&work_text);
        return 0;
    }
    else if(number_of_function==4){
        struct Text work_text = read_text();
        zero_changer(&work_text);
        similar(work_text);
        freedom(&work_text);
        return 0;
    }
    else if (number_of_function ==9){
        struct Text work_text = read_text();
        zero_changer(&work_text);
        smile(&work_text);
        printer(work_text);
        freedom(&work_text);
        return 0;
    }
    else{
        wprintf(L"Error: Функции под таким номером не существует. Введите 5 для справки.");
        return 0;
    }


}
