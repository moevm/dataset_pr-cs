void memoryError(){
    cout << "Memory allocating error!";
    exit(1);
}

class CustomStack{
    private:
        size_t sizeOfStack;
    protected:
        ListNode* mHead;

    public:
        CustomStack(){
            this->mHead = nullptr;
            this->sizeOfStack = 0;
        }

        void push(const char* tag){
            ListNode* newListNode = new ListNode;
            if(newListNode == nullptr) memoryError();
            
            newListNode->mData = new char[strlen(tag) + 1];
            if(newListNode->mData == nullptr) memoryError();
            strcpy(newListNode->mData, tag);
            
            newListNode->mNext = this->mHead;
            this->mHead = newListNode;

            this->sizeOfStack++;
        }

        void pop(){
            if(!this->is_empty()){
                ListNode* tmp = this->mHead->mNext;
                delete[] mHead->mData;
                delete mHead;

                this->mHead = tmp;
                this->sizeOfStack--;
            }
        }

        char* top(){
            if(!this->is_empty()){
                return this->mHead->mData;
            }
            return nullptr;
        }

        size_t size(){
            return this->sizeOfStack;
        }

        bool is_empty(){
            return this->sizeOfStack == 0;
        }

        ~CustomStack(){
            while (!this->is_empty()) {
                this->pop();
            }
        }


};

bool checkHtmlString(string htmlString){
    size_t start_pos = 0, end_pos = 0;
    string currentTag;
    CustomStack tagStack;

    bool is_correct = true;
    while ((start_pos = htmlString.find('<', end_pos)) != string::npos){
        end_pos = htmlString.find('>', start_pos);
        currentTag = htmlString.substr(start_pos + 1, end_pos - start_pos - 1);

        if(currentTag != "br" && currentTag != "hr"){
            if(currentTag[0] != '/'){
                tagStack.push(currentTag.c_str());
            }else{
                if(strcmp(tagStack.top(), currentTag.c_str() + 1) != 0){
                    is_correct = false;
                    break;
                }else{
                    tagStack.pop();
                }
            }
        }
    }

    return is_correct;
};

int main(){
    string text;
    getline(cin,text);

    bool result = checkHtmlString(text);


    if(result){
        cout << "correct";
    }else{
        cout << "wrong";
    }
    return 0;
}