class CustomStack {
public:
    CustomStack() {
        mData = new int[10];
    }
    void push(int val) {
        if (currentSize == maxSize) {
            extend(10);
        }
        mData[currentSize] = val;
        currentSize++;
    }
    void pop() {
        if (!isEmpty()) currentSize--;
        else {
            cout << "error";
            exit(0);
        }
    }
    int top() {
        if (!isEmpty()) return (mData[currentSize - 1]);
        else {
            cout << "error";
            exit(0);
        }
    }
    size_t size() {
        return currentSize;
    }
    bool isEmpty() {
        return (currentSize == 0);
    }
    void extend(int n) {
        int* newData = new int[maxSize + n];
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        maxSize += n;
    }
    ~CustomStack() {
        currentSize = 0;
        delete[] mData;
    }
protected:
    int* mData;
    int maxSize = 10;
    int currentSize = 0;
};

int main() {
    CustomStack stack;
    string input;
    int x, y, z;
    while (cin >> input) {
        if (input == "+") {
            x = stack.top();
            stack.pop();
            y = stack.top();
            stack.pop();
            stack.push(x + y);
        }
        else if (input == "-") {
            x = stack.top();
            stack.pop();
            y = stack.top();
            stack.pop();
            stack.push(y - x);
        }
        else if (input == "*") {
            x = stack.top();
            stack.pop();
            y = stack.top();
            stack.pop();
            stack.push(x * y);
        }
        else if (input == "/") {
            x = stack.top();
            stack.pop();
            y = stack.top();
            stack.pop();
            stack.push(y / x);
        }
        else {
            z = 0;
            int flagNumber = 1;
            int flagMinus = 0;
            for (int i = 0; i < input.size(); i++) {
                if (isdigit(input[i])) {
                    z = z * 10 + (input[i] - '0');
                } else if (i == 0 && input[i] == '-') {
                    flagMinus = 1;
                }
                else {
                    flagNumber = 0;
                    break;
                }
            }
            if (flagMinus) z *= -1;
            if (flagNumber) {
                stack.push(z);
            }
            else {
                cout << "error";
                return 0;
            }
        }
    }
    if (stack.size() != 1){
        cout << "error";
        return 0;
    }
    cout << stack.top() << '\n';
    return 0;
}
