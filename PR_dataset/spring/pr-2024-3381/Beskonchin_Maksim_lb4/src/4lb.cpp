class CustomStack {
protected:
    int *mData;

private:
    size_t mCap;
    size_t mSize;

public:
    CustomStack() : mData(nullptr), mCap(0), mSize(0) {}

    ~CustomStack() {
        free(mData);
    }

    void push(int val) {
        if (mSize >= mCap) {
            if (mCap > 0) {
                extend(mCap);
            } else {
                extend(1);
            }
        }
        mData[mSize++] = val;
    }

    void pop() {
        if (empty()) {
            throw runtime_error("error");
        }
        mSize--;
    }

    int top() {
        if (empty()) {
            throw runtime_error("error");
        }
        return mData[mSize - 1];
    }

    size_t size() {
        return mSize;
    }

    bool empty() {
        return mSize == 0;
    }

    void extend(size_t n) {
        mCap += n;
        mData = reinterpret_cast<int*>(realloc(mData, mCap * sizeof(int)));
        if (!mData) {
            throw runtime_error("error");
        }
    }
};

int main() {
    string command;
    CustomStack stack;

    while (cin >> command) {
        try {
            if (command == "cmd_push") {
                int number;
                cin >> number;
                stack.push(number);
                cout << "ok\n";
            } else if (command == "cmd_pop") {
                cout << stack.top() << endl;
                stack.pop();
            } else if (command == "cmd_top") {
                cout << stack.top() << endl;
            } else if (command == "cmd_size") {
                cout << stack.size() << endl;
            } else if (command == "cmd_exit") {
                cout << "bye";
                break;
            } else {
                cout << "error\n";
            }
        } catch (const runtime_error &e) {
            cout << "error" << endl;
            break;
        }
    }
    return 0;
}