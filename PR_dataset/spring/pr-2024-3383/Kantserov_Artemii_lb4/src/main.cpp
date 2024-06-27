#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class CustomStack {
public:
    CustomStack(size_t start = 10) {
        mData = new int [start];
        mSize = 0;
        mMax = 0;
    };
    ~CustomStack() {
        delete[] mData;
    }
    void push(int val) {
        if (mSize == mMax) {
            extend(mMax);
        }
        mData[mSize++] = val;
    }
    void pop()  {
        if (empty()) {
            cerr << "error" << endl;
            exit(1);
        }
        mSize--;
    }
    int top() {
        if (empty()) {
            cerr << "error" << endl;
            exit(1);
        }
        return mData[mSize-1];
    }
    size_t size() {
        return mSize;
    }
    bool empty() {
        if (mSize == 0) {
            return 1;
        }
        return 0;
    }
    void extend(int n) {
        int* newData = new int[mMax + n];
        for (int i = 0; i < mSize; i++) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        mMax += n;
    }
protected:
    int* mData;
    size_t mSize;
    size_t mMax;
};

bool isNumber(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    bool hasMinus = (str[0] == '-');
    size_t start = hasMinus ? 1 : 0;
    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
int main() {
    CustomStack stack;
    string input;
    int num;
    getline(cin, input);
    istringstream iss(input);
    string word;

    while (iss >> word) {
        if (word == "-" || word == "/" || word == "*" || word == "+") {
            if (stack.size() < 2) {
                cout << "error" << endl;
                return 1;
            }
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            switch (word[0]) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        } else if (isNumber(word)) {
            num = stoi(word);
            stack.push(num);
        } else {
            cout << "error" << std::endl;
            return 1;
        }
    }

    if (stack.size() != 1) {
        cout << "error" << std::endl;
        return 1;
    }

    cout << stack.top() << std::endl;
    return 0;
}
