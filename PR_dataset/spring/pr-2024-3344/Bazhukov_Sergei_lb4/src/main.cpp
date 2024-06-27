class CustomStack {
    public:
        CustomStack() {
            mHead = nullptr;
            mSize = 0;
        }
        
        void push(int val) {
            ListNode* newHead = new ListNode;
            
            newHead->mData = val;
            newHead->mNext = mHead;
            mHead = newHead;
            
            mSize++;
        }
        
        void pop() {
            if(empty()) {
                cout << "error" << endl;
                exit(0);
            }
            
            ListNode* delHead = mHead; //???
            mHead = mHead->mNext;
            delete delHead;
            
            mSize--;
        }
        
        int top() {
            if(empty()) {
                cout << "error" << endl;
                exit(0);
            }
            return mHead->mData;
        }
        
        size_t size() {
            return mSize;
        }
        
        bool empty() {
            return mHead == nullptr; 
        }
        
        ~CustomStack() {
            while(!empty()) {
                pop();
            }
        }
        
    private:
        size_t mSize;
        
    protected:
        ListNode* mHead;
};

int main() 
{
    CustomStack p = CustomStack();
    string input;
    getline(cin, input);

    stringstream ss(input);
    string token;
    
    while (getline(ss, token, ' ')) {
        if (isdigit(token[0]) || (token.size()>1 && isdigit(token[1]))) {
            int num = stoi(token);
            p.push(num);
        } else {
            int num1 = p.top();
            p.pop();
            int num2 = p.top();
            p.pop();
            
            char oper = token[0];
            int res;
            switch(oper) {
                case '+':
                    res = num2 + num1;
                    break;
                case '-':
                    res = num2 - num1;
                    break;
                case '*':
                    res = num2 * num1;
                    break;
                case '/':
                    res = num2 / num1;
                    break;
            }
            
            p.push(res);
        }
    }
    
    if(p.size() > 1) {
        cout << "error" << endl;
        exit(0);
    }
    cout << p.top();
    return 0;
}