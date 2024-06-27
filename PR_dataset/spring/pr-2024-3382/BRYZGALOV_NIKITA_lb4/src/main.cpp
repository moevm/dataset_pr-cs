class CustomStack {
public:
    CustomStack() {
        mHead = new ListNode;
        mHead->mNext = nullptr;
    }
    
    ~CustomStack() {
        while (!empty())
            pop();
        delete mHead;
    }
    
    void push(int val) {
        ListNode* new_mHead = new ListNode;
        new_mHead->mData = val;
        new_mHead->mNext = mHead;
        mHead = new_mHead;
        counter ++;
    }
    
    void pop() {
        ListNode* new_mHead = mHead->mNext;
        delete mHead;
        mHead = new_mHead;
        counter --;
    }
    
    int top() {
        return mHead->mData;
    }
    
    size_t size() {
        return counter;
    }
    
    bool empty() {
        return counter == 0;
    }
    
private:
    size_t counter = 0;
    
protected:
    ListNode* mHead;
};


int main() {
    CustomStack stack;
    string command;
    
    while (cin >> command) {
        if (command == "cmd_push") {
            int value;
            cin >> value;
            stack.push(value);
            cout << "ok" << endl;
            
        } else if (command == "cmd_pop") {
            if (stack.empty()) {
                cout << "error" << endl;
                break;
            } else {
                cout << stack.top() << endl;
                stack.pop();
            }
            
        } else if (command == "cmd_top") {
            if (stack.empty()) {
                cout << "error" << endl;
                break;
            } else {
                cout << stack.top() << endl;
            }
          
        } else if (command == "cmd_size") {
            cout << stack.size() << endl;
            
        } else if (command == "cmd_exit") {
            cout << "bye" << endl;
            break;
            
        } else {
            cout << "error" << endl;
            break;
        }
    }

    return 0;
}