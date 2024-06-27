#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class CustomStack{
protected:
    size_t mCapacity;
    size_t mIndex;
    char** mData;

    size_t getNewCapacity() const {
        return this->mCapacity * 3 / 2 + 1;
    } 

    void ensureSpace(){
        if (this->mIndex + 1 == this->mCapacity){
            size_t newCapacity = this->getNewCapacity();
            this->resize(newCapacity);
        }
    }

    void resize(size_t newCapacity) {
        if (newCapacity == this->mCapacity) {
            return;
        } else if (newCapacity < this->mCapacity) {
            throw logic_error("resize() called with a lower capacity");
        }

        char** newData = new char*[newCapacity];
        for (int i = 0; i <= this->mIndex; i++) {
            newData[i] = this->mData[i];
        }

        delete[] this->mData; 
        this->mData = newData;
        this->mCapacity = newCapacity;
    }

public:
    CustomStack(size_t initialCapacity){
        this->mCapacity = initialCapacity;
        this->mData = new char*[initialCapacity];
        this->mIndex = -1;
    }

    CustomStack(): CustomStack(10){} 

    ~CustomStack(){
        delete[] this->mData;
    }

    void push(const char* val) {
        this->ensureSpace(); 
        this->mIndex++;
        this->mData[this->mIndex] = new char[strlen(val) + 1]; 
        strcpy(this->mData[this->mIndex], val); 
    }

    void pop(){
        if (this->empty()){
            throw logic_error("pop() called on empty stack");
        }
        this->mIndex--;
    }

    char* top(){
        if (this->empty()){
            throw logic_error("top() called on empty stack");
        }
        return this->mData[this->mIndex];
    }

    size_t size(){
        return this->mIndex + 1;
    }

    bool empty(){
        return this->mIndex == -1;
    }

    void extend(int n){
        if (n <= 0){
            throw logic_error("extend() called with a nonpositive argument");
        }
        this->resize(this->mCapacity + n);
    }
};

int main(){
    CustomStack stack = CustomStack();
    string str;
    getline(cin, str);
    if (str.empty()) {
        cout << "correct" << endl;
        return 0;
    }
    int index = 0;
    int newIndex;
    while (index <= str.length()-1){
        if (str.substr(index, 4) ==  "<br>" ||  str.substr(index, 4) ==  "<hr>"){
            index = index + 4;
            continue;
        }else if(str.substr(index, 5) ==  "</br>" ||  str.substr(index, 5) ==  "</hr>"){
            cout << "wrong" << endl;
            return 0;
        }else if(str.substr(index, 2) == "</"){
            newIndex = index;
            while(str[newIndex] != '>')newIndex++;
            string closingTag = str.substr(index, newIndex - index + 1);
            if (!stack.empty() && stack.top() == ("<" + closingTag.substr(2))) {
                stack.pop(); 
            }else{
                cout << "wrong" << endl;
                return 0;
            }            
        }else if(str[index] == '<'){
            newIndex = index;
            while(str[newIndex] != '>')newIndex++;
            stack.push(str.substr(index,  newIndex - index + 1).c_str());
            index = newIndex+1;
            continue;
        }
        index++;
    }
    if (stack.empty() ){
        cout << "correct" << endl;
    }else{
        cout << "wrong" << endl;
    }
}