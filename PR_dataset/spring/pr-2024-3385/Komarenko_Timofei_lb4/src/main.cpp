class CustomStack {

public:

        CustomStack(){
                mHead = new ListNode;
                mHead->mNext = nullptr;
        }

        ~CustomStack(){
            while (mHead != nullptr) {
                ListNode* temp = mHead;
                mHead = mHead->mNext;
                delete temp;
            }
        }

        void push(const char* tag){
            ListNode *mNew = new ListNode;
            mNew->mData = strdup(tag);
            mNew->mNext = mHead;
            mHead = mNew;
            size_of_stack++;
        }

        void pop(){
                ListNode *newHead = mHead->mNext;
                delete mHead;
                mHead = newHead;
                --size_of_stack;
        }

        char* top(){
            if (size_of_stack != 0){
                return mHead->mData;
            }else{
                return nullptr;
            }
            
        }

        size_t size(){
                return size_of_stack;
        }

        bool empty(){
                return size_of_stack == 0;
        }
        
private:
        size_t size_of_stack = 0;

protected:
        ListNode* mHead;
};


int main() {
    string line;
    getline(cin, line);

    CustomStack* stack = new CustomStack;

    size_t startIndex = line.find('<');
    size_t endIndex = line.find('>');

    while (startIndex != string::npos && endIndex != string::npos) {
        string tag = line.substr(startIndex + 1, endIndex - startIndex - 1);

        if (tag == "br" || tag == "hr") {
            line = line.substr(endIndex + 1);
            startIndex = line.find('<');
            endIndex = line.find('>');
            continue;
        }

        if (tag[0] != '/') {
            stack->push(tag.c_str());
        } else {
            char* top_tag = stack->top();
            if (top_tag == nullptr || strcmp(top_tag, tag.c_str() + 1) != 0) {
                cout << "wrong" << endl;
                delete stack;
                return 0;
            }
            stack->pop();
        }

        line = line.substr(endIndex + 1);
        startIndex = line.find('<');
        endIndex = line.find('>');
    }

    if (stack->empty()) {
        cout << "correct" << endl;
    } else {
        cout << "wrong" << endl;
    }

    delete stack;

    return 0;
}
