class CustomStack {
public:
    CustomStack() {
        mHead = nullptr;
    }

    ~CustomStack() {
        while (mHead) {
            pop();
        }
    }

    void push(int val) {
        auto current = mHead;
        auto *listNode = new ListNode;
        listNode->mNext = current;
        listNode->mData = val;
        mHead = listNode;
    }

    int pop() {
        auto current = mHead;
        int data = current->mData;
        mHead = mHead->mNext;
        delete current;
        return data;
    }

    int top() {
        return mHead->mData;
    }

    size_t size() {
        int count = 0;
        auto current = mHead;
        while (current) {
            current = current->mNext;
            count++;
        }
        return count;
    }

    bool empty() {
        return mHead == nullptr;
    }

protected:
    ListNode *mHead;
};

int main() {
    CustomStack stack;
    string command;
    int value;

    while (cin >> command) {
        if (command == "cmd_push") {
            cin >> value;
            stack.push(value);
            cout << "ok" << endl;
        } else if (command == "cmd_pop") {
            if (stack.empty()) {
                cout << "error" << endl;
                return 1;
            }
            cout << stack.pop() << endl;
        } else if (command == "cmd_top") {
            if (stack.empty()) {
                cout << "error" << endl;
                return 1;
            }
            cout << stack.top() << endl;
        } else if (command == "cmd_size") {
            cout << stack.size() << endl;
        } else if (command == "cmd_exit") {
            cout << "bye" << endl;
            return 0;
        }
    }
}