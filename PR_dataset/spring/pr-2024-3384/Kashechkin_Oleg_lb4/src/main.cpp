class CustomStack {
public:
    CustomStack() {
        mData = new int[10];
    }

    void push(int val) {
        if(stack_size == capacity) {
            extend(10);
        }
        mData[stack_size++] = val;
    }

    void pop() {
        stack_size--;
    }

    int top() {
        return mData[stack_size-1];
    }

    bool empty() {
        return stack_size == 0;
    }

    int size() {
        return stack_size;
    }

    void extend(int n) {
        int *new_arr = new int[capacity + n];
        capacity += 10;
        for (int i = 0; i < stack_size; i++) {
            new_arr[i] = mData[i];
        }
        delete[] mData;
        mData = new_arr;
    }

    ~CustomStack() {
        delete[] this->mData;
    }

private:
    size_t stack_size = 0;
    size_t capacity = 10;

protected:
    int* mData;
};

int main() {
    CustomStack stack = CustomStack();
    string cmd;
    int n;
    while(cin >> cmd) {
        if (cmd == "cmd_push") {
            cin>>n;
            stack.push(n);
            cout << "ok" << endl;
        } else if (cmd == "cmd_pop") {
            if(stack.empty()) {
                cout << "error";
                exit(0);
            }
            cout << stack.top() << endl;
            stack.pop();
        } else if (cmd == "cmd_top") {
            if(stack.empty()) {
                cout << "error" << endl;
                exit(0);
            }
            cout << stack.top() << endl;
        } else if (cmd == "cmd_size"){
            cout << stack.size() << endl;
        } else if (cmd == "cmd_exit") {
            cout << "bye";
            exit(0);
        }
    }
    return 0;
}