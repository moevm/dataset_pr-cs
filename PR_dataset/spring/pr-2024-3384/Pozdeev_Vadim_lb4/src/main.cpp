#include <iostream>
#include <cstring>

class CustomStack {
public:
    CustomStack() : mHead(NULL) {}
    
    void push(const char* tag){
        ListNode * mTag = new ListNode;
        char * new_tag = new char[strlen(tag)];
        strcpy(new_tag, tag);
        mTag->mData = new_tag;
        mTag->mNext = mHead;
        mHead = mTag;
    }
    
    void pop(){
        if (mHead == NULL) {
            return;
        }
        ListNode * mTag = mHead;
        mHead = mHead->mNext;
        delete mTag;
    }
    
    const char* top(){
        if (mHead == NULL) {
            return NULL;
        }
        return mHead->mData;
    }
    bool empty(){
        return mHead == NULL;
    }
protected:
    ListNode* mHead;
};
int main(){
    string input;
    getline(cin, input);
    
    CustomStack Tags = CustomStack();
    bool flag = false;
    string tag;
    for(size_t i = 0; i != input.size(); i++){
        if(input[i] == '<'){
            tag.clear();
            flag = true;
            continue;
        }
        if(flag){
            if(input[i] != '>'){
                tag.push_back(input[i]);
            }
        }
        if(input[i] == '>'){
            flag = false;
            if(tag=="br" || tag=="hr"){
                continue;
            }
            if(tag.find("/")!=string::npos){
                tag.erase(0, 1);
                if(!strcmp(Tags.top(), tag.c_str())){
                    Tags.pop();
                }
                else{
                    puts("wrong");
                    return 0;
                }
                
            }
            else{
                Tags.push(tag.c_str());
                }
        }
    }
    cout << Tags.top();
    if(Tags.empty()){
        puts("correct");
    }
    else{
        puts("wrong");
    }

    return 0;
}
