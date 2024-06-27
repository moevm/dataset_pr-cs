#define ERROR_MESSAGE "error"

class CustomStack {
public:

    CustomStack()
    {
        mHead = new ListNode;
        mHead->mNext = nullptr;
    }
    
    ~CustomStack(){
        delete mHead;
    }
    
    void push(int val)
    {
        ListNode *mNext = new ListNode;
        mNext->mData = val;
        mNext->mNext = mHead;
        mHead = mNext;
        stack_size++;
    }
    void pop()
    {
        ListNode *newHead = mHead->mNext;
        delete mHead;
        mHead = newHead;
        --stack_size;
    }
    int top()
    {
        return mHead->mData;
    }
    
    size_t size()
    {
        return stack_size;
    }
    
    bool empty()
    {
        return stack_size == 0;
    }
private:
    int stack_size = 0;
    
protected:
    ListNode* mHead;
};

void processCommands(CustomStack& stack) {
    string cmd;
    while (cin >> cmd) {
        if (cmd == "cmd_push") {
            int val;
            cin >> val;
            stack.push(val);
            cout << "ok" << endl;
        } else if (cmd == "cmd_pop") {
            if (stack.empty()) {
                cout << ERROR_MESSAGE;
                break;
            } else {
                cout << stack.top() << endl;
                stack.pop();
            }
        } else if (cmd == "cmd_top") {
            if (stack.empty()) {
                cout << ERROR_MESSAGE;
                break;
            } else {
                cout << stack.top() << endl;
            }
        } else if (cmd == "cmd_size") {
            cout << stack.size() << endl;
        } else if (cmd == "cmd_exit") {
            cout << "bye";
            break;
        } else if (cmd == "cmd_empty") {
            cout << stack.empty() << endl;
            break;
        }
    }
}

int main() {
    CustomStack stack = CustomStack();
    processCommands(stack);
    return 0;
}
