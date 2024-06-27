class CustomStack {
public:
    CustomStack() : mSize(0), mCapacity(1), mData(new int[mCapacity]) {}

    ~CustomStack() {
        delete[] mData;
    }

    void push(int val) {
        if (mSize == mCapacity) {
            extend(1);
        }
        mData[mSize] = val;
        mSize++;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Error: pop from empty stack");
        }
        mSize--;
    }

    int top() {
        if (empty()) {
            throw std::runtime_error("Error: top of empty stack");
        }
        return mData[mSize - 1];
    }

    size_t size() {
        return mSize;
    }

    bool empty() {
        return mSize == 0;
    }

    void extend(int n) {
        int newCapacity = mCapacity + n;
        int* newData = new int[newCapacity];
        for (size_t i = 0; i < mSize; i++) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        mCapacity = newCapacity;
    }

private:
    size_t mSize;
    size_t mCapacity;

protected:
    int* mData;
};

int main() {
    CustomStack stack;
    string cmd;

    while (true) {
        cin >> cmd;

        if (cmd == "cmd_push") {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        } else if (cmd == "cmd_pop") {
            try {
                int val = stack.top();
                stack.pop();
                cout << val << endl;
            } catch (const std::runtime_error& e) {
                cout << "error" << endl;
                return 1;
            }
        } else if (cmd == "cmd_top") {
            try {
                int val = stack.top();
                cout << val << endl;
            } catch (const std::runtime_error& e) {
                cout << "error" << endl;
                return 1;
            }
        } else if (cmd == "cmd_size") {
            cout << stack.size() << endl;
        } else if (cmd == "cmd_exit") {
            cout << "bye" << endl;
            return 0;
        } else {
            cout << "error" << endl;
            return 1;
        }
    }

    return 0;
}
