#define PUSH "cmd_push"
#define POP "cmd_pop"
#define TOP "cmd_top"
#define SIZE "cmd_size"
#define EXIT "cmd_exit"
#define ERR "error"
class CustomStack {
public:
    CustomStack() {
        mHead = new ListNode;
        mHead->mNext = nullptr;
    }

    ~CustomStack() {
        while (mHead != nullptr) {
            pop();
        }
    }

    void push(int val) {
        ListNode *mNext = new ListNode;
        mNext->mData = val;
        mNext->mNext = mHead;
        mHead = mNext;
        stack_size++;
    }

    void pop() {
        if (mHead != nullptr) {
            ListNode *newHead = mHead->mNext;
            delete mHead;
            mHead = newHead;
            --stack_size;
        }
    }

    int top() {
        if (mHead != nullptr) {
            return mHead->mData;
        }
        return -1; // Сигнализирует об ошибке, можно выбрать другое значение по умолчанию
    }

    size_t size() {
        return stack_size;
    }

    bool empty() {
        return stack_size == 0;
    }

protected:
    ListNode *mHead;
    size_t stack_size = 0;
};

void processCommands() {
    CustomStack stack;

    string cmd;
    while (cin >> cmd) {
        if (cmd == PUSH) {
            int val;
            cin >> val;
            stack.push(val);
            cout << "ok" << endl;
        } else if (cmd == POP) {
            if (stack.empty()) {
                cout << ERR << endl;
                break;
            } else {
                cout << stack.top() << endl;
                stack.pop();
            }
        } else if (cmd == TOP) {
            if (stack.empty()) {
                cout << ERR << endl;
                break;
            } else {
                cout << stack.top() << endl;
            }
        } else if (cmd == SIZE) {
            cout << stack.size() << endl;
        } else if (cmd == EXIT) {
            cout << "bye" << endl;
            break;
        }
    }
}

int main() {
    processCommands();

    return 0;
}
