class CustomStack {
public:
    CustomStack(): mData(nullptr), _size(0), _capacity(0) {}

    ~CustomStack() {
        delete[] mData;
    }

    void push(int val) {
        if (_size >= _capacity) {
            extend(max(1, static_cast<int>(_capacity * 2)));
        }
        mData[_size++] = val;
    }

    void pop() {
        if (empty()) {
            throw runtime_error("error");
        }
        _size--;
    }

    int top() {
        if (empty()) {
            throw runtime_error("error");
        }
        return mData[_size - 1];
    }

    size_t size() {
        return _size;
    }

    bool empty() {
        return _size == 0;
    }

protected:
    void extend(int n) {
        int newCapacity = _size + n;
        int* newData = new int[newCapacity];
        
        for (size_t i = 0; i < _size; i++) {
            newData[i] = mData[i];
        }
        
        delete[] mData;
        mData = newData;
        _capacity = newCapacity;
    }

    int* mData;
    size_t _size;
    size_t _capacity;
};

int main() {
    CustomStack stack;
    string command;

    while (std::cin >> command) {
        try {
            if (command == "cmd_push") {
                int n;
                cin >> n;
                stack.push(n);
                cout << "ok\n";
            } else if (command == "cmd_pop") {
                cout << stack.top() << "\n";
                stack.pop();
            } else if (command == "cmd_top") {
                cout << stack.top() << "\n";
            } else if (command == "cmd_size") {
                cout << stack.size() << "\n";
            } else if (command == "cmd_exit") {
                cout << "bye\n";
                break;
            }
        } catch (const runtime_error& e) {
            cout << e.what() << "\n";
            return 1;
        }
    }

    return 0;
}