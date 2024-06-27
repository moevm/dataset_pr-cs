#include <iostream>
#include <cstddef>
#include <cstring>

class CustomStack {
private:
// поля класса, к которым не должно быть доступа извне
    size_t size_of_stack;
    int Max; 
public:
// методы push, pop, size, empty, top + конструкторы, деструктор
    CustomStack(){
          size_of_stack = 0;
          Max = 3001;
          this->mData = (char**)malloc(Max*sizeof(char*));
        }
    ~CustomStack(){
        erase();
    }
    void erase(){
        for(size_t i = 0; i<this->size_of_stack; i++){
            this->pop();
        }
        free(this->mData);
        
    }

    void push(const char* val){ //-  добавляет новый элемент в стек
        this->mData[size_of_stack] = (char*)calloc(strlen(val) + 1, sizeof(char));
        if(this->mData[size_of_stack]){
            strncpy(this->mData[this->size_of_stack], val, strlen(val));
        }
        this ->size_of_stack ++;
        
        

    }
    
    void pop(){ //- удаляет из стека последний элемент
        free(this -> mData[this->size_of_stack-1]);
        this->size_of_stack --;
        
    }
    
    char* top(){ //- доступ к верхнему элементу
        if (this->size_of_stack == 0) {
            puts("out of range");
        }
        return this -> mData[this->size_of_stack-1];
        
    }
    
    size_t size(){ //- возвращает количество элементов в стеке
        return this->size_of_stack;
    }
    
    bool empty(){ //- проверяет отсутствие элементов в стеке
        if (this->size() == 0){
            return true;
        }
        return false;
    }
    
    void extend(int n){ //- расширяет исходный массив на n ячеек 
        this->mData = (char**)realloc(this->mData, (this->Max+n)*sizeof(char*));
        this->Max +=n;
    }

protected:
// в этом блоке должен быть указатель на массив данных
    char** mData;
};

int cmp(char* tag1, char* tag2){
    int ans = 1;
    for(int i=0; i<strlen(tag1); i++){
        if (tag1[i] != tag2[i+1]){
            ans = 0;
        }
    }
    return ans;
}

int main() {

    char text [3001];
    fgets(text, 3001, stdin);
    CustomStack stac;
    int len = strlen(text);
    int i =0, ind_tmp = 0;
    char* tmp = (char*)malloc(50*sizeof(char));
    while(i<len){
        
        //если встречается <тег> при этом != <br>, <hr>, то добавить в стек, если закрывающий тэг, 
        //то проверить что последний это тот же тег но открывающий и удалить его
        if (text[i] == '<'){
            i++; //чтобы < не записывалась, так сравнивать удобее
            while((text[i] != '>')&&(i<len)){
                
                tmp[ind_tmp++] = text[i++];
        
            }
        }
        tmp[ind_tmp] = '\0';
        //сейчас в tmp кусок формата <...> надо проверить на br, hr и что тег не закрывающий
        if(strlen(tmp)>0){
            if((strcmp(tmp, "hr") && strcmp(tmp, "br"))){
                if(tmp[0] != '/'){
                    
                    stac.push(tmp);
                    
                }
                else{
                    if(cmp(stac.top(), tmp)){
                        stac.pop();
                    }
                }
                
                
            }
            memset(tmp, '\0', 50);
            ind_tmp = 0;
            
        }
        i++;
    }
    free(tmp);
    
    if(stac.empty()){
        puts("correct");
    }else{
        puts("wrong");
    }
    return 0;
}












