class CustomStack {

public:
    CustomStack() : mData(nullptr), mSize(0), mCapacity(0){};
    void push(int value) {
        if (mSize == mCapacity)
            extend(mCapacity);
        mData[mSize++] = value;
    }
    int pop() { return mData[--mSize]; }
    int top() { return mData[mSize - 1]; }
    size_t size() { return mSize; }
    bool empty() { return mSize == 0; }
    ~CustomStack() { delete[] mData; };

private:
    void extend(int n) {
        int new_capacity = mCapacity + n;
        int *new_data = new int[new_capacity];
        for (int i = 0; i < mSize; i++)
            new_data[i] = mData[i];
        delete[] mData;
        mData = new_data;
        mCapacity = new_capacity;
    };

protected:
    int *mData;
    size_t mSize;
    size_t mCapacity;
};

#define HASH_START 2166136261ULL
#define HASH_PRIME 16777619ULL
inline constexpr uint64_t str_hash(const char *str,
                                   uint64_t hash = HASH_START) {
    return *str ? str_hash(str + 1, (hash ^ *str) * HASH_PRIME) : hash;
}

void panic() {
    cout << "error" << endl;
    exit(0);
}

void work(CustomStack &stack) {
    string command;
    int op;
    while (cin >> command) {
        switch (str_hash(command.c_str())) {
        case str_hash("cmd_push"):
            cin >> op;
            stack.push(op);
            cout << "ok" << endl;
            break;
        case str_hash("cmd_pop"):
            if (stack.empty())
                panic();
            cout << stack.pop() << endl;
            break;
        case str_hash("cmd_top"):
            if (stack.empty())
                panic();
            cout << stack.top() << endl;
            break;
        case str_hash("cmd_size"):
            cout << stack.size() << endl;
            break;
        case str_hash("cmd_exit"):
            cout << "bye" << endl;
            return;
        default:
            panic();
        }
    }
}

int main() {
    CustomStack stack;
    work(stack);
}
