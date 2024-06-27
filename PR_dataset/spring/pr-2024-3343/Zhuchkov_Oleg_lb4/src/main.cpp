class CustomStack {

public:

    CustomStack(){
        mSize = 0;
        mHead = nullptr;
    }
    
    void push(int val){
        ListNode* temp = new ListNode;
        temp -> mData = val;
        temp -> mNext = mHead;
        mSize++;
        mHead = temp;
    }
    
    void pop(){
        if (empty()){
            cout << "error";
            exit(0);
        }
        mHead = mHead -> mNext;
        mSize--;
    }
    
    int top(){
        if (empty()){
            cout << "error";
            exit(0);
        }
        return mHead -> mData;
    }
    
    size_t size(){
        return mSize;
    }
    
    bool empty(){
        return mSize == 0;
    }
    
private:

    size_t mSize;

protected:

    ListNode* mHead;

};

int main(){
    CustomStack stk;
    string InputElem;
    int a, b;
    while (cin.peek() != '\n')
    {
        cin >> InputElem;
        if (InputElem == "+" || InputElem == "-" || InputElem == "*" || InputElem == "/"){
                b = stk.top();
                stk.pop();
                a = stk.top();
                stk.pop();
                if (InputElem == "+")
                    stk.push(a + b);
                else if (InputElem == "-")
                    stk.push(a - b);
                else if (InputElem == "*")
                    stk.push(a * b);
                else if (InputElem == "/")
                    stk.push(a / b);
        }
        else stk.push(stoi(InputElem));
    }
    if (stk.size() > 1){
            cout << "error";
            exit(0);
    }
    cout << stk.top();
    return 0;
}