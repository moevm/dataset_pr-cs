class CustomStack {
public:
    CustomStack () {
        mHead = new ListNode();
    }

    void push (int val) {
        ListNode* new_ListNode = new ListNode();
        new_ListNode->mData = val;
        new_ListNode->mNext = mHead;
        mHead = new_ListNode;
        size_++;
    }
    
    void pop () {
        if (empty()) {
            cout << "error" << endl;
            exit(0);
        }
        else {
            ListNode* cur = mHead;
            mHead = mHead->mNext;
            size_--;
            delete cur;
        }
    }

    int top () {
        if (empty()) {
            cout << "error" << endl;
            exit(0);
        }
        return mHead->mData;
    }

    size_t size () {
        return size_;
    }

    bool empty () {
        return size_ == 0;
    }

private:
    size_t size_ = 0;
protected:
    ListNode* mHead;
};

int main () {
    CustomStack stack;
    string cmd;
    int n;
    while (cmd != "cmd_exit") { 
        cin >> cmd;
        if (cmd == "cmd_push") {
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        }
        else if (cmd == "cmd_pop") {
            cout << stack.top() << endl;
            stack.pop();
        }
        else if (cmd == "cmd_top") {
            cout << stack.top() << endl;
        }
        else if (cmd == "cmd_size") {
            cout << stack.size() << endl;
        }
    }
    cout << "bye" << endl;
    return 0;
} 