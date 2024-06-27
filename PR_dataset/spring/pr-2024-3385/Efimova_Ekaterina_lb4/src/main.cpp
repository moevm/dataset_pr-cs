#include <iostream>
#include <cstring> 
#define EXTEND_SIZE 5
#define START_CAPACITY 10
#define TEXT_LEN 3000
#define TAG_LEN 100
using namespace std; 

class CustomStack {

public:

CustomStack(){
   mLastIndex = -1;
   mCapacity = START_CAPACITY;
   mData = new char*[mCapacity];
}


void push(const char* val){

    char * new_element = new char[strlen(val)];
    strcpy(new_element, val);

    if ((size_t)mLastIndex == mCapacity - 1)
        extend(EXTEND_SIZE);

    mLastIndex++;

    mData[mLastIndex] = new_element;

}

void pop(){

    if(!empty()){

        delete[] this->mData[mLastIndex]; 
        mLastIndex--;
    }
    else throw out_of_range("ERROR: trying to pop from empty stack!");
}

size_t size(){

    return (size_t)mLastIndex+1;
}

bool empty(){

    return mLastIndex == -1;
}

char* top(){

    if(empty()) return nullptr;
    return mData[mLastIndex];    
}

~CustomStack(){

    while (!empty()) {
        pop();
    }
    delete[] this->mData;
}


private:

int mLastIndex;

void extend(size_t n){

    mCapacity += n;
    char **newData = new char*[mCapacity];
    copy(this->mData, this->mData + this->mCapacity-n, newData);
    delete[] this->mData;
    this->mData = newData;
}

protected:
    char** mData;
    size_t mCapacity;
};


char * get_tag(char * text, int index){

    char * tag  = new char[TAG_LEN];
    int tag_index = 0;
    tag[tag_index] = text[index];

    while(tag[tag_index] != '>') {

        tag_index++;
        tag[tag_index] = text[tag_index+index];
    }

    tag[tag_index+1] = '\0';
    return tag;
}

bool check_line(char *text){

    CustomStack stack;
    char *cur_tag;
    fgets(text, TEXT_LEN, stdin);
    for(int i = 0; i < (int) strlen(text); i++){
        if(text[i] == '<') {
            cur_tag = get_tag(text, i);
            if (!strcmp("<br>", cur_tag) || !strcmp("<hr>", cur_tag)) {
                delete[] cur_tag;
                continue;
            }

            if (cur_tag[1] != '/'){
                stack.push(cur_tag);
            }

            else{
                
                if(stack.empty()){
                    delete[] cur_tag;
                    return false;
                }

                if (!strcmp(cur_tag+2, stack.top()+1)) {
                stack.pop();
                }
                else {

                    delete[] cur_tag;
                    return false; 
                }
            }
            delete[] cur_tag;
        }
    }
    
    return true;
}
int main() {

    char * text = new char[TEXT_LEN];
    if(check_line(text)) cout << "correct" << endl;
    else cout << "wrong" << endl;
    delete[] text;
    return 0;
}
