class CustomStack {
public:
    CustomStack()
    {
        mHead= nullptr;
        mSize = 0;
    }


    void push(int val){
        ListNode* node = new ListNode;
        node->mData = val;
        node->mNext = mHead;
        mHead = node;
        mSize++;
    }

    long long pop(){
       if(empty())
       {
            cout<< "error";
            exit(0);
       }
       long long data = mHead->mData;
       mHead = mHead->mNext;
       mSize--;
       return data;

    }

    long long top(){
        if(empty()){
            cout<<"error";
            exit(0);
        }
        return mHead->mData;
    }

    size_t size(){
       return mSize;
    }

    bool empty(){
        return mHead == nullptr;
    }
private:
    size_t mSize;
protected:
    ListNode* mHead;
};

CustomStack calc(CustomStack s, string op){
    int a = s.pop();
    int b = s.pop();
    if(op == "+"){
        s.push(b+a);
    }
    else if(op == "-"){
        s.push(b - a);
    }
    else if (op == "*")
        s.push(a * b);
    
    else if (op == "/")
        s.push(b / a);
    return s;
}

int main() {
    CustomStack stack;
    string dBuffer;
    while(cin.peek() != '\n'){

        cin>>dBuffer;
        if(dBuffer == "+" || dBuffer == "-" || dBuffer == "/" || dBuffer == "*")
        {
            stack = calc(stack,dBuffer);
        }
        else{
            stack.push(stoi(dBuffer));
        }


    }

        if(stack.size() > 1){
            cout << "error";
            return 1;
        }
        cout << stack.top();
        return 0;
}
