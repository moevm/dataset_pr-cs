class CustomStack {
public:
    CustomStack() {
        mHead = nullptr;
        mSize = 0;
    }
    bool empty() {
        return mHead == nullptr;
    }
    size_t size() {
        return mSize;
    }
    char *top() {
        if (empty())
            return nullptr;
        return mHead->mData;
    }
    void push(const char *str) {
        // создание нового узла
        ListNode *newElement = new ListNode;
        newElement->mData = new char[strlen(str)];
        strcpy(newElement->mData, str);
        newElement->mNext = mHead; // новый узел указывает на предыдущую голову
        mHead = newElement; // новый узел становится головой
        mSize++;
    }
    void pop() {
        if (empty())
            return;
        ListNode* temp = mHead;
        mHead = mHead->mNext;
        mSize--;
        delete temp;
    }
    ~CustomStack() {
        // удаление элементов, пока они есть
        while (!empty())
            pop();
    }
private:
    size_t mSize;
protected:
    ListNode *mHead;
};

int checker() {
    CustomStack open_braces = CustomStack();
    char brace;
    cin.get(brace);
    while (brace != '\n') {
        if (brace == '<') {
            char input[100];
            cin.getline(input, 100, '>');
            if (input[0] != '/') {
                if (strcmp(input,"br") != 0 && strcmp(input, "hr") != 0) {
                    open_braces.push(input);
                }
            }
            else {
                if (open_braces.empty()) {
                    return 0;
                }
                char *pair_candidate = open_braces.top();
                char *input_without_slash = strchr(input, '/') + 1;
                if (strcmp(input_without_slash, pair_candidate) != 0) {
                    return 0;
                }
                open_braces.pop();
            }

        }
        cin.get(brace);
    }
    if (!open_braces.empty()) {
        return 0;
    }
    return 1;

}

int main() {
    if (checker()) {
        cout << "correct";
    }
    else {
        cout << "wrong";
    }
}