class CustomStack {
    public:
        CustomStack() {
            mHead = nullptr;
            mSize = 0;
        }

        bool empty() {
            return mHead == nullptr;
        }

        long long top() {
            if (empty()) {
                cout << "error";
                exit(0);
            }
            return mHead->mData;
        }

        size_t size() {
            return mSize;
        }

        void push(int value) {
            ListNode* node = new ListNode;
            node->mData = value;
            node->mNext = mHead;
            mHead = node;
            ++mSize;
        }

        void pop() {
            if (empty()) {
                cout << "error";
                exit(0);
            }

            mHead = mHead->mNext;
            --mSize;
        }

        void change(string value) {
            ListNode* current = new ListNode;
            current = mHead->mNext;
            long long data;
            
            if (value == "+") {
                data = current->mData + mHead->mData;
            }
            else if (value == "-") {
                data = current->mData - mHead->mData;
            }
            else if (value == "*") {
                data = current->mData * mHead->mData;
            }
            else if (value == "/") {
                data = current->mData / mHead->mData;
            }

            pop();
            pop();
            push(data);
        }

        ~CustomStack() {
        while (!empty())
            pop();
        }

    private:
        size_t mSize;

    protected:
        ListNode* mHead;
};


void check(CustomStack stack) {
    if (stack.size() < 2) {
        cout << "error";
        exit(0);
    }
}

int main() {
    CustomStack stack = CustomStack();
    string value;
    vector <string> vec;
    char nextChar;
    int prevSize = 0;

    do {
        cin >> value;
        vec.push_back(value);
    }
    while ((nextChar = cin.peek()) != '\n');

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == "+" || vec[i] == "-" || vec[i] == "*" || vec[i] == "/") {
            check(stack);
            stack.change(vec[i]);
        }

        else {
            long long pushValue = stoi(vec[i]);
            stack.push(pushValue);
        }
    }

    if (stack.size() > 1) {
        cout << "error";
        return 0;
    }

    cout << stack.top();
    return 0;
}