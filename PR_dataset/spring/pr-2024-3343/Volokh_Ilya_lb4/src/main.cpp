class CustomStack {
public:
    CustomStack();
    ~CustomStack();
    void push(int n);
    void pop();
    int top();
    size_t size();
    bool empty();

protected:
    size_t size_; 
    int* mData;
};

CustomStack::CustomStack() : size_(0), mData(NULL) {}

CustomStack::~CustomStack() {
    while (!empty()) {
        pop();
    }
}

void CustomStack::push(int n) {
    int* newData = new int[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = mData[i];
    }
    newData[size_] = n; 
    delete[] mData;
    mData = newData; 
    size_++; 
}

void CustomStack::pop() {
    if (empty()) {
        cout << "Error: pop, but stack is empty" << endl;
        return;
    }
    size_--;
    int* newData = new int[size_];
    for (size_t i = 0; i < size_; ++i) {
        newData[i] = mData[i]; 
    }
    delete[] mData; 
    mData = newData; 
}

int CustomStack::top() {
    if (empty()) {
        cout << "Error: top, but stack is empty" << endl;
    }
    return mData[size_ - 1];
}

size_t CustomStack::size() {
    return size_;
}

bool CustomStack::empty() {
    return size_ == 0;
}


int main() {
    CustomStack Newstack;
    string input;
    int value;

    while (cin >> input) {
        if (input == "cmd_push") {
            cin >> value;
            Newstack.push(value);
            cout << "ok" << endl;
        } else if (input == "cmd_pop") {
            if (Newstack.empty()) {
                cout << "error" << endl;
                return 1;
            }
            int poppedValue = Newstack.top(); 
            Newstack.pop();
            cout << poppedValue << endl; 
        } else if (input == "cmd_top") {
            if (Newstack.empty()) {
                cout << "error" << endl;
                return 1;
            }
            cout << Newstack.top() << endl;
        } else if (input == "cmd_size") {
            cout << Newstack.size() << endl;
        } else if (input == "cmd_exit") {
            cout << "bye" << endl;
            return 0;
        }
    }
}