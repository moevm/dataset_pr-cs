#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

class CustomStack {
public:
    CustomStack(size_t capacity = 10) : mCapacity(capacity), mSize(0), mData(new int[capacity]) {}
    ~CustomStack() { delete[] mData; }

    void push(int val) {
        if (mSize >= mCapacity) {
            extend(10);
        }
        mData[mSize++] = val;
    }

    void pop() {
        if (mSize > 0) {
            --mSize;
        } else {
            throw std::runtime_error("Stack underflow");
        }
    }

    int top() const {
        if (mSize > 0) {
            return mData[mSize - 1];
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    size_t size() const {
        return mSize;
    }

    bool empty() const {
        return mSize == 0;
    }

    void extend(size_t n) {
        size_t newCapacity = mCapacity + n;
        int* newData = new int[newCapacity];
        std::copy(mData, mData + mSize, newData);
        delete[] mData;
        mData = newData;
        mCapacity = newCapacity;
    }

private:
    size_t mCapacity;
    size_t mSize;
protected:
    int* mData;
};

bool processTokens(CustomStack& stack, std::istringstream& iss) {
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

    return error;
}

int main() {
    CustomStack stack;

    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
    bool error = processTokens(stack, iss);

    if (error || stack.size() != 1) {
        std::cout << "error" << std::endl;
    } else {
        std::cout << stack.top() << std::endl;
    }

    return 0;
}
