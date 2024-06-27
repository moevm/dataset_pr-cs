#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class CustomStack {
public:
    CustomStack() : mData(nullptr), mCapacity(0), mSize(0) {}
    
    ~CustomStack() {
        delete[] mData;
    }
    
    void push(int val) {
        if (mSize == mCapacity) {
            extend(mCapacity > 0 ? mCapacity : 1); 
        }
        mData[mSize++] = val;
    }
    
    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack underflow");
        }
        --mSize;
    }
    
    int top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return mData[mSize - 1];
    }
    
    size_t size() {
        return mSize;
    }
    
    bool empty() {
        return mSize == 0;
    }
    
    void extend(int n) {
        int* newMData = new int[mCapacity + n];
        for (size_t i = 0; i < mSize; ++i) {
            newMData[i] = mData[i];
        }
        delete[] mData;
        mData = newMData;
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
    std::string input;
    
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::string token;
    
    try {
        while (ss >> token) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (stack.size() < 2) {
                    throw std::runtime_error("Not enough operands");
                }
                int b = stack.top();
                stack.pop();
                int a = stack.top();
                stack.pop();
                int result;
                if (token == "+") {
                    result = a + b;
                } else if (token == "-") {
                    result = a - b;
                } else if (token == "*") {
                    result = a * b;
                } else if (token == "/") {
                    if (b == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    result = a / b;
                }
                stack.push(result);
            } else {
                int num = std::stoi(token);
                stack.push(num);
            }
        }
        
        if (stack.size() != 1) {
            throw std::runtime_error("Stack should contain exactly one element");
        }
        
        std::cout << stack.top() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "error" << std::endl;
    }
    
    return 0;
}