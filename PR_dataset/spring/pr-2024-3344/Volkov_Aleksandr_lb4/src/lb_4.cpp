class CustomStack
{
public:
    CustomStack()
    {
        mSize = 0;
        mCapacity = 100;
        mData = new int[mCapacity];
    }

    ~CustomStack()
    {
        delete []mData;
    }

    void push(int val)
    {
        if (mSize == mCapacity) 
            extend(100);
        mData[mSize++] = val;
    }

    void pop()
    {
        if (empty()) {
            cout << "error" << endl;
            return;
        }
        --mSize;
    }

    int top()
    {
        if (empty()) {
            cout << "error" << endl;
            exit(1);
        }
        return mData[mSize - 1];
    }

    size_t size() 
    {
        return mSize;
    }

    bool empty()
    {
        return mSize == 0;
    }

    void extend(int n)
    {
        int *newData = new int[mCapacity + n];
        for (int i = 0; i < mSize; i++) {
            newData[i] = mData[i];
        }
        delete []mData;
        mData = newData;
        mCapacity += n;
    }

protected:
    int *mData;

private:
    size_t mSize;
    size_t mCapacity;
};

int main() {
    CustomStack stack;

    char str[101];
    fgets(str, 100, stdin);
    char *token = strtok(str, " \n");
    while (token) {
        string tokens(token, strlen(token));
        if (tokens == "+" || tokens == "-" || tokens == "*" || tokens == "/") {
            if (stack.size() < 2) {
                cout << "error" << endl;
                return 0;
            }
            int num1 = stack.top();
            stack.pop();
            int num2 = stack.top();
            stack.pop();
            int result;

            switch (tokens[0]) {
                case '+':
                    result = num2 + num1;
                    break;
                case '-':
                    result = num2 - num1;
                    break;
                case '*':
                    result = num2 * num1;
                    break;
                case '/':
                    if (num1 == 0) {
                        cout << "error" << endl;
                        return 0;
                    }
                    result = num2 / num1;
                    break;
            }
            stack.push(result);    
        } else {
            stack.push(stoi(tokens));
        }
        token = strtok(NULL, " \n");
    }

    if (stack.size() != 1) {
        cout << "error" << endl;
        return 0;
    }

    cout << stack.top() << endl;

    return 0;
}
