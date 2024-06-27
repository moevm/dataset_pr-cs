class CustomStack {
public:
    // методы push, pop, size, empty, top + конструкторы, деструктор
    CustomStack() {
        mHead = new ListNode;
        mHead->mNext = nullptr;
        mTail = mHead;
    }

    // добавляет новый элемент в стек
    void push(int val) {
        if (empty()) {
            mHead->mData = val;
        } else {
            ListNode *mNext = new ListNode{nullptr, val};
            mTail->mNext = mNext;
            mTail = mNext;
        }
        this->amount++;
    }

    // удаляет из стека последний элемент
    void pop() {
        if (size() == 1) {
            this->amount--;
            return;
        }

        ListNode *cursor = mHead;
        while (cursor->mNext != mTail)
            cursor = cursor->mNext;
        delete cursor->mNext;
        cursor->mNext = nullptr;
        mTail = cursor;
        this->amount--;
    }

    // доступ к верхнему элементу
    int top() {
        return mTail->mData;
    }

    // возвращает количество элементов в стеке
    size_t size() {
        return amount;
    }

    //проверяет отсутствие элементов в стеке
    bool empty() {
        return amount == 0;
    }

    ~CustomStack() {
        while (!empty()) pop();
        delete mHead;
    }

private:
    size_t amount = 0;

protected:  // в этом блоке должен быть указатель на голову
    ListNode *mHead;
    ListNode *mTail;
};

int getOperand(char *str) {
    if (strlen(str) != 1) return 0;
    char letter = str[0];
    switch (letter) {
        case '+':
            return 1;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 4;
        default:
            return 0;
    }
}

int main() {
    auto cs = new CustomStack;

    char buff[128];
    fgets(buff, 100, stdin);
    buff[strlen(buff) - 1] = '\0';

    char* p = strtok(buff, " ");
    while (p != nullptr && strlen(p) > 0) {
        if (!getOperand(p)) cs->push(atoi(p));
        else {
            if (cs->size() < 2) {
                cout << "error";
                return 0;
            }
            int secondValue = cs->top();
            cs->pop();
            int firstValue = cs->top();
            cs->pop();

            switch (getOperand(p)) {
                case 1:
                    cs->push(firstValue + secondValue);
                    break;
                case 2:
                    cs->push(firstValue - secondValue);
                    break;
                case 3:
                    cs->push(firstValue * secondValue);
                    break;
                case 4:
                    cs->push(firstValue / secondValue);
                    break;
            }
        }
        p = strtok(NULL, " ");
    }

    if (cs->size() > 1)
        cout << "error";
    else
        cout << cs->top();
    return 0;
}