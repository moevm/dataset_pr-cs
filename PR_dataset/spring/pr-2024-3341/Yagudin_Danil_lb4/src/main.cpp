class CustomStack {

public:
    CustomStack(int capacity = 10) : mCapacity(capacity), mSize(0), mData(new int[capacity]){}
    ~CustomStack() { delete[] mData; }

    void push(int item) {
        if (mSize >= mCapacity) {
            extend(10);
        }

        mData[mSize++] = item;
    }

    void pop() {
        if (mSize > 0) {
            --mSize;
        }else{
            throw runtime_error("not enough stack size\n");
        }
    }

    int top() const {
        if (mSize > 0) {
            return mData[mSize - 1];
        }else{
            throw runtime_error("empty stack\n");
        }
    }

    int size() const {
        return mSize;
    }

    bool empty() const {
        return mSize == 0;
    }

    void extend(int n) {
        int newCapacity = mCapacity + n;

        int* newData = new int[newCapacity];

        copy(mData, mData + mSize, newData);
        delete[] mData;

        mData = newData;
        mCapacity = newCapacity;
    }

private:
    int mCapacity;
    int mSize;

protected:
    int* mData;

};

int main() {
	CustomStack stack;

    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string token;
    bool error = false;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            stack.push(std::atoi(token.c_str()));
        } else {
            if (stack.size() < 2) {
                error = true;
                break;
            }

            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            if (token == "+") {
                stack.push(a + b);
            } else if (token == "-") {
                stack.push(a - b);
            } else if (token == "*") {
                stack.push(a * b);
            } else if (token == "/") {
                if (b == 0) {
                    error = true;
                    break;
                }
                stack.push(a / b);
            } else {
                error = true;
                break;
            }
        }
    }

    if (error || stack.size() != 1) {
        std::cout << "error" << std::endl;
    } else {
        std::cout << stack.top() << std::endl;
    }

    return 0;
}
