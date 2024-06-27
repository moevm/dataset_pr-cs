class CustomStack{

public:

    CustomStack(){
        mHead = new ListNode;
        mHead->mNext = nullptr;
    }
    ~CustomStack(){
        while(mHead){
            ListNode* next = mHead->mNext;
            delete mHead;
            mHead = next;
        }
    }

    bool empty() {
        return count == 0;
    }
    
    void push(int val){
        ListNode* newNode = new ListNode{mHead, val};
        mHead = newNode;
        count++;
        cout << "ok" << endl;
    }
    
    void pop(){
        ListNode* next = mHead->mNext;
        cout << mHead->mData << endl;
        delete mHead;
        mHead = next;
        count--;
    }

    int top(){
        return mHead->mData;
    }

    size_t size(){
        return count;
    }

private:
    size_t count = 0;

protected:

    ListNode* mHead;

};

int main(){
    CustomStack stack;
    string command;

    while(cin >> command){
        if(command == "cmd_push"){
            int val;
            cin >> val;
            stack.push(val);
        }else if(command == "cmd_pop"){
            if(stack.empty()){
                cout << "error" << endl;
                exit(0);
            }
            stack.pop();
        }else if(command == "cmd_top"){
            if(stack.empty()){
                cout << "error" << endl;
                exit(0);
            }
            cout << stack.top() << endl;
        }else if(command == "cmd_size"){
            cout << stack.size() << endl;
        }else if(command == "cmd_exit"){
            cout << "bye" << endl;
            exit(0);
        }
    }

    return 0;
}
