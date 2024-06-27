class CustomStack{
    public:
        CustomStack(){
            mHead = nullptr;
            mSize = 0;
        }

        void push(int val){
            ListNode* newElement = new ListNode;
            newElement->mData = val;
            newElement->mNext = mHead;
            mHead = newElement;
            mSize++;
        }
        bool empty(){
            return mHead == nullptr;
        }
        void pop(){
            if (empty()){
                return;
            }
            ListNode *deletingElement = mHead;
            //cout << deletingElement->mData << endl;
            mHead = mHead->mNext;
            delete deletingElement;
            mSize--;
        }
        int top(){
            if (empty()){
                return 0;}
            return mHead->mData;
        }
        size_t size(){
            if (empty()){
                return 0;
            }
            return mSize;
        }
        ~CustomStack() {
        while (mHead) {
            ListNode* temp = mHead;
            mHead = mHead->mNext;
            delete temp;
        }
    }
    private:
        size_t mSize;
    protected:
        ListNode* mHead;
};

int pushing(string s){
    int n;
    string cmd;
    istringstream iss(s);
    iss >> cmd >> n;
    return n;
}

int main(){
    string s;
    CustomStack Stack;
    while (s != "cmd_exit"){
        getline(cin, s);
        if (s.find("cmd_push") == 0){
            int n = pushing(s);
            Stack.push(n);
            cout << "ok\n";
        }
        else if (s == "cmd_pop"){
            if (Stack.top() == 0){
                cout << "error" << endl;
                return 0;
            }
            else{
                cout << Stack.top() << endl;
            }
            Stack.pop();
        }
        else if (s == "cmd_top"){
            if (Stack.top() == 0){
                cout << "error\n";
                return 0;
            }else{
            cout << Stack.top() << endl;
            }
        }
        else if (s == "cmd_size"){
            cout << Stack.size() << endl;
        } 

    }
    cout << "bye\n";
    return 0;
}
