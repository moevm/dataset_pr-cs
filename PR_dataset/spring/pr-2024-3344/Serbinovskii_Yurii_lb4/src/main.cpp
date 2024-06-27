class CustomStack {
public:
    CustomStack() {
        mHead = nullptr;
        len = 0;
    }

    CustomStack(int val) {
        mHead = new ListNode;
        mHead->mData = val;
        mHead->mNext = nullptr;
        len = 1;
    }

    ~CustomStack() {
        while(!empty()) {
            pop();
        }
    }

    void push(int val) {
        len++;
        ListNode* node = new ListNode;
        node->mData = val;
        node->mNext = mHead;
        mHead = node;
    }

    void pop() {
        if (!empty()) {
            len--;
            ListNode* p = mHead;
            mHead = mHead->mNext;
            delete p;
        } else {
            cout<<"error"<<endl;
            exit(0);
        }
    }

    int top() {
        if (!empty())
            return mHead->mData;
        else {
            cout<<"error"<<endl;
            exit(0);
        }
    }

    size_t size() {
        return len;
    }

    bool empty() {
        if (mHead == nullptr)
            return true;
        else
            return false;
    }

    
protected:
    ListNode* mHead;
private:
    size_t len;

};

int main() {
    string input;
    getline(cin, input);
    istringstream ss(input);
    string token;
    vector<string> tokens;

    while(getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    CustomStack stack;

    for(const string t : tokens) {
        if (string{"+-*/"}.find(t) != string::npos) {
            int arg2 = stack.top();
            stack.pop();
            int arg1 = stack.top();
            stack.pop();
            switch (t[0])
            {
            case '+':
                stack.push(arg1 + arg2);
                break;
            case '-':
                stack.push(arg1 - arg2);
                break;
            case '*':
                stack.push(arg1 * arg2);
                break;
            case '/':
                stack.push(arg1 / arg2);
                break;
            default:
                break;
            }
        }
        else {
            int arg = stoi(t);
            stack.push(arg);
        }
    }

    if (stack.size() != 1) {
        cout<<"error"<<endl;
        exit(0);
    }
    else {
        cout<<stack.top()<<endl;
    }

    return 0;
}
