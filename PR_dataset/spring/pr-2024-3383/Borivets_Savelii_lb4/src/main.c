class CustomStack {
public:
    CustomStack()
    {
        mHead = new ListNode;
        mHead->mNext = nullptr;
        st_size = 0;
    }

    void push(int val)
    {
        ListNode *newElem = new ListNode;
        newElem->mData = val;
        newElem->mNext = mHead;
        mHead = newElem;
        st_size++;
    }
    void pop()
    {  
        if (!(*this).empty()) {
            ListNode *newHead = mHead->mNext;
            delete mHead;
            mHead = newHead;
            st_size--;
        }
    }
    int top()
    {
        return mHead->mData;
    }

    size_t size()
    {
        return st_size;
    }

    bool empty()
    {
        return st_size == 0;
    }

    ~CustomStack(){
        delete mHead;
    }
private:
    size_t st_size;

protected:
    ListNode* mHead;
};

int main() {
    CustomStack stack = CustomStack();
    string cmd;
    while (cin >> cmd) {
        if (cmd == "cmd_push") {
            int val;
            cin >> val;
            stack.push(val);
            cout << "ok" << endl;

        } else if (cmd == "cmd_pop") {
            if(stack.empty()){
                cout << "error";
                break;
            } else {
                cout << stack.top() << endl;
                stack.pop();
            }
        } else if (cmd == "cmd_top") {
            if(stack.empty()){
                cout << "error";
                break;
            } else {
                cout << stack.top() << endl;
            }
        } else if (cmd == "cmd_size") {
            cout << stack.size() << endl;
        } else if (cmd == "cmd_exit") {
            cout << "bye";
            break;
        }
    }
    return 0;
}

