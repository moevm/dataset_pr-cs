class CustomStack{
public:
    CustomStack() : mCapacity(10), mSize(0), mData(new int[mCapacity]) {}
    CustomStack(const CustomStack& other) : mCapacity(other.mCapacity), mSize(other.mSize), mData(new int[mCapacity]) {
        for (size_t i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    ~CustomStack() {
        delete[] mData;
    }

    void push(int val) {
        if (mSize == mCapacity) {
            extend(10);
        }
        mData[mSize++] = val;
    }

    void pop() {
        if (empty()) {
            std::cout << "error" << std::endl;
            exit(1);
        }
        --mSize;
    }

    int top() const {
        if (empty()) {
            std::cout << "error" << std::endl;
            exit(1);
        }
        return mData[mSize - 1];
    }

    int size() const {
        return mSize;
    }

    bool empty() const {
        return mSize == 0;
    }

    void extend(int n) {
        int* temp = new int[mCapacity + n];
        for (size_t i = 0; i < mSize; ++i) {
            temp[i] = mData[i];
        }
        delete[] mData;
        mData = temp;
        mCapacity += n;
    }

    int* data() {
        return mData;
    }

private:
    size_t mCapacity;
    size_t mSize;
    
protected:
    int* mData;
};

int main() {
    CustomStack stack;

    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        try {
            int val = std::stoi(token);
            stack.push(val);
        } catch (...) {
            if (stack.size() < 2) {
                std::cout << "error" << std::endl;
                return 1;
            }
            int op2 = stack.top();
            stack.pop();
            int op1 = stack.top();
            stack.pop();
            switch (token[0]) {
                case '+':
                    stack.push(op1 + op2);
                    break;
                case '-':
                    stack.push(op1 - op2);
                    break;
                case '*':
                    stack.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) {
                        std::cout << "error" << std::endl;
                        return 1;
                    }
                    stack.push(op1 / op2);
                    break;
                default:
                    std::cout << "error" << std::endl;
                    return 1;
            }
        }
    }

    if (stack.size() != 1) {
        std::cout << "error" << std::endl;
        return 1;
    }

    std::cout << stack.top() << std::endl;

    return 0;
}