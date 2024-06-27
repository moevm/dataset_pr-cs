#include <iostream>
#include <string>

using namespace std;

const int SIZE = 10;

class CustomStack {
public:
    CustomStack() {
        mData = new int[SIZE];
        capacity = SIZE;
        max_size = 0;
    }
    ~CustomStack() {
        delete[] mData;
    }
    void push(int val) {
        if (max_size == capacity) {
            extend(SIZE);
        }
        mData[max_size++] = val;
        cout << "ok" << endl;
    }
    void pop() {
        if (empty()) {
            cout << "error" << endl;
            return;
        }
        --max_size;
    }
    int top() {
        if (empty()) {
            cout << "error" << endl;
            return -1;
        }
        return mData[max_size - 1];
    }
    size_t size() const {
        return max_size;
    }
    bool empty() const {
        return max_size == 0;
    }
    void extend(int n) {
        capacity += n;
        int* new_data = new int[capacity];
        for (int i = 0; i < max_size; ++i) {
            new_data[i] = mData[i];
        }
        delete[] mData;
        mData = new_data;
    }
private:
    int capacity;
    int max_size;
protected:
    int* mData;
};

void processCommand(CustomStack& stack, const string& cmd) {
    if (cmd == "cmd_push") {
        int n;
        cin >> n;
        stack.push(n);
    }
    else if (cmd == "cmd_pop") {
        if (stack.empty()) {
            cout << "error" << endl;
            exit(0);
        }
        cout << stack.top() << endl;
        stack.pop();
    } else if (cmd == "cmd_top") {
        if (stack.empty()) {
            cout << "error" << endl;
            exit(0);
        }
        cout << stack.top() << "\n";
    } else if (cmd == "cmd_size") {
        cout << stack.size() << endl;
    } else if (cmd == "cmd_exit") {
        cout << "bye" << endl;
        exit(0);
    } else {
        cout << "error" << endl;
        exit(0);
    }
}

void func() {
    CustomStack stack;
    string cmd;
    while (cin >> cmd) {
        processCommand(stack, cmd);
    }
}

int main() {
    func();
    return 0;
}