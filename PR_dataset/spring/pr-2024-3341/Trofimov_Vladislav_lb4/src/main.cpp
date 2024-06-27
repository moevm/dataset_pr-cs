#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUF 100

using namespace std;

class CustomStack {
    public:
    
        CustomStack(){
            mHead = nullptr;
        }

        ~CustomStack(){
            while (mHead){
                pop();
            }
        }
        void push(int val){
            ListNode* current = new ListNode;
            if (current != nullptr){
                current->mData = val;
                current->mNext = mHead;
                mHead = current;
            }
        }

        void pop(){
            ListNode* current = mHead;
            if (this->empty()){
                mHead = mHead->mNext;
                delete current;
            }
        }

        int top(){
            if (mHead){
                return mHead->mData;
            }
            return -1;
        }

        size_t size(){
            ListNode* current = mHead;
            size_t size = 0;
            while (current){
                size++;
                current = current->mNext;
            }
            return size;
        }

        bool empty(){
            if (mHead)
                return 1;
            return 0;
        }

    protected:
        ListNode* mHead;
};

int main() {
    CustomStack stack;
    char string[BUF];
    cin.getline(string, BUF);
    char* ptr = strtok(string, " ");
    while (ptr != nullptr) {
        if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
            stack.push(atoi(ptr));
        } 
        else if (strlen(ptr) == 1 && (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/')) {
            if (stack.size() < 2) {
                cout << "error" << endl;
                return 0;
            }
            int num2 = stack.top();
            stack.pop();
            int num1 = stack.top();
            stack.pop();
            switch (*ptr) {
                case '+':
                    stack.push(num1 + num2);
                    break;
                case '-':
                    stack.push(num1 - num2);
                    break;
                case '*':
                    stack.push(num1 * num2);
                    break;
                case '/':
                    if (num2 == 0) {
                        cout << "error" << endl;
                        return 0;
                    }
                    stack.push(num1 / num2);
                    break;
            }
        } 
        else {
            cout << "error" << endl;
            return 0;
        }
        ptr = strtok(nullptr, " ");
    }

    if (stack.size() != 1) {
        cout << "error" << endl;
        return 0;
    }
    cout << stack.top() << endl;
    return 0;
}