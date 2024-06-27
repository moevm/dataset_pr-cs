#include<iostream>
#include<cstring>
#include<cstdlib>
#define SIGN "+-/*"

class CustomStack {
    public:
        CustomStack() {
            mHead = nullptr;
        }
        ~CustomStack() {
            while( not empty()){
                pop();
            }
        }
        void push(int val) {
            ListNode *mNext = new ListNode;
            mNext->mData = val;
            mNext->mNext = mHead;
            mHead = mNext;
            length++;
        }
        void pop() {
            ListNode *tmp = mHead->mNext;
            delete mHead;
            mHead = tmp;
            length--;
        }
        int top() {
            return mHead->mData;
        }
        size_t size() {
            return length;
        }
        bool empty(){
            return length == 0;
        }
    private:
        int length = 0;
    protected:
        ListNode* mHead;
};

int signCheck(char *str) {
    if (strlen(str) != 1 || !(strchr(SIGN, str[0]))) return 0;
    return 1;
}

int main() {
    auto stuck = new CustomStack;

    char buff[128];
    fgets(buff, 100, stdin);
    buff[strlen(buff) - 1] = '\0';

    char* p = strtok(buff, " ");
    while (p != nullptr && strlen(p) > 0) {
        if (!signCheck(p)) stuck->push(atoi(p));
        else {
            if (stuck->size() < 2) {
                cout << "error";
                return 0;
            }
            int secondValue = stuck->top();
            stuck->pop();
            int firstValue = stuck->top();
            stuck->pop();
            if (*p == '+')
                stuck->push(firstValue + secondValue);
            else if (*p == '-')
                stuck->push(firstValue - secondValue);
            else if (*p == '*')
                stuck->push(secondValue * firstValue);
            else if (*p == '/')
                stuck->push(firstValue / secondValue);
        }
        p = strtok(NULL, " \n");
    }

    if (stuck->size() > 1)
        cout << "error";
    else
        cout << stuck->top();
    return 0;
}
