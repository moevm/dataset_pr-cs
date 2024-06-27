class CustomStack {
public:
    CustomStack() : mData(nullptr), mCapacity(0), mSize(0) {}
    CustomStack(const CustomStack& other) : mCapacity(other.mCapacity), mSize(other.mSize) {
        mData = new int[mCapacity];
        for (size_t i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    ~CustomStack() {
        delete[] mData;
    }

    void push(int val) {
        if (mSize == mCapacity) {
            extend(1);
        }
        mData[mSize++] = val;
    }

    void pop() {
        --mSize;
    }

    int top() {
        return mData[mSize - 1];
    }

    size_t size() {
        return mSize;
    }

    bool empty() {
        return mSize == 0;
    }

    void extend(int n) {
        int* newData = new int[mCapacity + n];
        for (size_t i = 0; i < mSize; ++i) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        mCapacity += n;
    }

protected:
    int* mData;

private:
    size_t mCapacity;
    size_t mSize;
};


int main() {
    CustomStack stack;

    std::string command;
    while (std::cin >> command) {
        if (command == "cmd_push") {
            int n;
            std::cin >> n;
            stack.push(n);
            std::cout << "ok\n";
        } else if (command == "cmd_pop") {
            if (stack.empty()) {
                std::cout << "error";
                return 0;
            }
            std::cout << stack.top() << std::endl;
            stack.pop();
        } else if (command == "cmd_top") {
            if (stack.empty()) {
                std::cout << "error";
                return 0;
            }
            std::cout << stack.top() << std::endl;
        } else if (command == "cmd_size") {
            std::cout << stack.size() << std::endl;
        } else if (command == "cmd_exit") {
            std::cout << "bye\n";
            break;
        }
    }

    return 0;
}
