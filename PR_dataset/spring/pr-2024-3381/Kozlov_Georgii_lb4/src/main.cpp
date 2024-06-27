#include <iostream>
#include <string.h>
#include <string>
using namespace std;

#define LEN_STR 256

class CustomStack {
protected:
  ListNode *mHead;
  size_t size1;

public:
  CustomStack() {
    mHead = NULL;
    size1 = 0;
  }
  void push(int val) {
    ListNode *tmp = new ListNode;
    tmp->mData = val;
    tmp->mNext = mHead;
    mHead = tmp;
    this->size1++;
  }
  size_t size() { return this->size1; }

  bool empty() { return size() == 0; }
  void pop() {
    if (empty()) {
      throw "error";
    }
    ListNode *tmp = mHead;
    mHead = mHead->mNext;
    delete tmp;
    this->size1--;
  }
  int top() {
    if (empty()) {
      throw "error";
    }
    return mHead->mData;
  }
};

int main() {
  char *data;
  char line[LEN_STR];
  fgets(line, LEN_STR, stdin);
  CustomStack stack;
  int num1, num2;
  data = strtok(line, " ");
  try {
    for (int i = 0; data; i++) {
      if (data[strlen(data) - 1] == '\n') {
        data[strlen(data) - 1] = '\0';
      }
      if (data[0] == '*' && strlen(data) == 1) {
        num2 = stack.top();
        stack.pop();
        num1 = stack.top();
        stack.pop();
        stack.push(num1 * num2);
      } else if (data[0] == '-' && strlen(data) == 1) {
        num2 = stack.top();
        stack.pop();
        num1 = stack.top();
        stack.pop();
        stack.push(num1 - num2);
      } else if (data[0] == '+' && strlen(data) == 1) {
        num2 = stack.top();
        stack.pop();
        num1 = stack.top();
        stack.pop();
        stack.push(num1 + num2);
      } else if (data[0] == '/' && strlen(data) == 1) {
        num2 = stack.top();
        stack.pop();
        num1 = stack.top();
        stack.pop();
        stack.push((int)(num1 / num2));
      } else {
        int n = atoi(data);
        stack.push(n);
      }
      data = strtok(NULL, " ");
    }
    if (stack.size() == 1) {
      cout << stack.top() << endl;
    } else {
      throw "error";
    }
  } catch (const char *error_message) {
    cout << error_message << endl;
    return 1;
  }
  return 0;
}
