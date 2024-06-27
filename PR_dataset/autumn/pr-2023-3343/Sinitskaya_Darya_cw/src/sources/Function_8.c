#include"../include/Function_8.h"
void Removal_Non_Palindrome_Sentence(Text *text){
    for(int i=0; i<text->size;i++)
        {
            wchar_t* sentence = wcsdup(text->sentences[i].sentence);
            int a=0;
            int h=wcslen(sentence)-1;
            int f=0;

            for(int j=0;j<wcslen(sentence);j++){
                while(sentence[j]==L' ' ||sentence[j]==L'.' ||sentence[j]==L','||sentence[j]==L';'||sentence[j]==L'\n'){
                    j++;
                }
                while(sentence[h]==L' ' ||sentence[h]==L'.' ||sentence[h]==L','||sentence[h]==L';'||sentence[h]==L'\n'){
                    h--;
                }

                if(sentence[j]>=L'А' && sentence[j]<=L'Я') sentence[j]+=L'я'-L'Я';
                 if(sentence[h]>=L'А' && sentence[h]<=L'Я') sentence[h]+=L'я'-L'Я';
                 if(sentence[j]>=L'A' && sentence[j]<=L'Z') sentence[j]+=L'z'-L'Z';
                 if(sentence[h]>=L'A' && sentence[h]<=L'Z') sentence[h]+=L'z'-L'Z';
                if(sentence[j]!=sentence[h]){
                    f=1;
                    break;
                }
                h--;
                
            }
            if(f==0){
                if(text->sentences[i].sentence[0]==L'\n'){
                    memmove(text->sentences[i].sentence,&text->sentences[i].sentence[1],sizeof(wchar_t)*wcslen(text->sentences[i].sentence));
                    
                }
                wprintf(L"%ls\n", text->sentences[i].sentence);
            }
            
        }
}
