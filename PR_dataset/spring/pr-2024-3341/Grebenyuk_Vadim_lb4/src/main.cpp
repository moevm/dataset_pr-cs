class CustomStack {
public:
    void push(int val) {
        ListNode **cursor = this->last();
        if (*cursor != nullptr)
            cursor = &(*cursor)->mNext;
        *cursor = new ListNode();
        (*cursor)->mData = val;
        this->len++;
    }
    void pop() {
        if (!this->len) return;
        ListNode **nodeToDelete = this->last();
        if (this->len > 1) {
            ListNode **secondToLast = this->last(-1);
            delete *nodeToDelete;
            (*secondToLast)->mNext = nullptr;
        } else {
            delete *nodeToDelete;
            this->mHead = nullptr;
        }
        this->len--;
    }
    int top() {
        if (this->len == 0)
            throw exception();
        return (*this->last())->mData;
    }
    size_t size() const {
        return this->len;
    }

    bool empty() {
        return this->mHead != nullptr;
    }

private:
    ListNode **last(int offset = 0) {
        ListNode **cursor = &this->mHead;
        for (auto i = 1; i < this->len + offset; i++)
            cursor = &(*cursor)->mNext;
        return cursor;
    }
    size_t len = 0;

protected:
    ListNode *mHead = nullptr;
};

void run_commands(CustomStack &stack) {
    string buffer;
    try {
        while (true) {
            cin >> buffer;

            if (buffer.compare("cmd_push") == 0) {
                int val;
                cin >> val;
                stack.push(val);
                cout << "ok\n";
            } else if (buffer.compare("cmd_pop") == 0) {
                cout << stack.top() << '\n';
                stack.pop();
            } else if (buffer.compare("cmd_top") == 0) {
                cout << stack.top() << '\n';
            } else if (buffer.compare("cmd_size") == 0) {
                cout << stack.size() << '\n';
            } else if (buffer.compare("cmd_exit") == 0) {
                cout << "bye" << endl;
                break;
            } else {
                throw exception();
                break;
            }
        }
    } catch (const exception &e) {
        cout << "error\n"
             << endl;
    }
}

int main() {
    CustomStack stack = CustomStack();
    run_commands(stack);
    return 0;
}
