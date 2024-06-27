#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class CustomStack {
public:
    CustomStack();

    ~CustomStack();

    void push(int val);

    void pop();

    int top();

    size_t size();

    bool empty();

protected:
    ListNode *mHead{nullptr};
};

CustomStack::CustomStack() = default;

CustomStack::~CustomStack() {
    while (!empty()) {
        pop();
    }
}

void CustomStack::push(int val) {
    auto *node = new ListNode{mHead, val};
    mHead = node;
}

void CustomStack::pop() {
    if (!mHead) {
        return;
    }
    auto *node = mHead;
    mHead = mHead->mNext;
    delete node;
}

int CustomStack::top() {
    return mHead->mData;
}

size_t CustomStack::size() {
    size_t cnt = 0;
    ListNode *cur = mHead;
    while (cur) {
        cnt++;
        cur = cur->mNext;
    }
    return cnt;
}

bool CustomStack::empty() {
    return mHead == nullptr;
}

bool isNumber(const string &str) {
    if (str.empty()) {
        return false;
    }

    for (size_t i = 0; i < str.length(); ++i) {
        if (i == 0 && str[i] == '-') {
            if (str.length() == 1) {
                return false;
            }
            continue;
        }
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    string input;
    getline(cin, input);
    istringstream ss(input);
    string token;

    auto *stack = new CustomStack;

    while (ss >> token) {
        if (isNumber(token)) {
            stack->push(stoi(token));
        } else {
            if (stack->size() < 2) {
                cout << "error" << endl;
                delete stack;
                return 1;
            }
            int b = stack->top();
            stack->pop();
            int a = stack->top();
            stack->pop();
            if (token == "+") stack->push(a + b);
            else if (token == "-") stack->push(a - b);
            else if (token == "*") stack->push(a * b);
            else if (token == "/") {
                if (b == 0) {
                    cout << "error" << endl;
                    delete stack;
                    return 1;
                }
                stack->push(a / b);
            } else {
                cout << "error" << endl;
                delete stack;
                return 1;
            }
        }
    }

    if (stack->size() != 1) {
        cout << "error" << endl;
        delete stack;
        return 1;
    }

    cout << stack->top() << endl;

    delete stack;

    return 0;
}
