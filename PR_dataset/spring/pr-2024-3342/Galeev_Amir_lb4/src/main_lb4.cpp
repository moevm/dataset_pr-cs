class CustomStack {
public:
    CustomStack() : mData(nullptr), mCapacity(0), mSize(0) {}
    ~CustomStack() {
        delete[] mData;
    }

    void push(int val) {
        if (mSize == mCapacity) {
            if (!extend(1)) {
                std::cerr << "Failed to extend memory." << std::endl;
                return;
            }
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

    bool extend(int n) {
        int newCapacity = mCapacity + n;
        int* newData = new (std::nothrow) int[newCapacity];
        if (!newData) {
            return false;
        }
        for (size_t i = 0; i < mSize; ++i) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        mCapacity = newCapacity;
        return true;
    }

protected:
    int* mData;

private:
    size_t mCapacity;
    size_t mSize;
};

int main() {
    CustomStack stack;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "cmd_push") {
            int n;
            std::cin >> n;
            stack.push(n);
            std::cout << "ok" << std::endl;
        } else if (cmd == "cmd_pop") {
            if (stack.empty()) {
                std::cout << "error" << std::endl;
                return 0;
            }
            std::cout << stack.top() << std::endl;
            stack.pop();
        } else if (cmd == "cmd_top") {
            if (stack.empty()) {
                std::cout << "error" << std::endl;
                return 0;
            }
            std::cout << stack.top() << std::endl;
        } else if (cmd == "cmd_size") {
            std::cout << stack.size() << std::endl;
        } else if (cmd == "cmd_exit") {
            std::cout << "bye" << std::endl;
            break;
        } else {
            std::cout << "error" << std::endl;
            break;
        }
    }

    return 0;
}
