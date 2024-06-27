class CustomStack {
protected:
    int* mData;
private:
    int capacity;
    int topIdx;
public:
    CustomStack() {
        mData = new int[10];
        capacity = 10;
        topIdx = 0;
    }
    ~CustomStack() {
        delete[] mData;
    }
    void push(int val) {
        if (topIdx == capacity) {
            extend(10);
        }
        mData[topIdx++] = val;
    }
    void pop() {
        --topIdx;
    }
    int top() {
        return mData[topIdx - 1];
    }
    int size() {
        return topIdx;
    }
    bool empty() {
        return topIdx == 0;
    }
    void extend(int n) {
        int *new_arr = new int[capacity + n];
        for (int i = 0; i < topIdx; ++i) {
            new_arr[i] = mData[i];
        }
        delete[] mData;
        mData = new_arr;
        capacity += n;
    }
};

int processing() {
    string cmd;
    CustomStack stack;
    while (cin >> cmd) {
        if (cmd == "cmd_push") {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok\n";
        } else if (cmd == "cmd_pop" || cmd == "cmd_top") {
            if (stack.empty()) {
                cout << "error\n";
                exit(0);
            }
            cout << stack.top() << "\n";
            if (cmd == "cmd_pop"){
                stack.pop();
            }
        } else if (cmd == "cmd_size") {
            cout << stack.size() << "\n";
        } else if (cmd == "cmd_exit") {
            cout << "bye\n";
            return 0;
        }
    }
    return 0;
}

int main(){
    processing();
    return 0;
}