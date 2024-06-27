class CustomStack {
public:
  CustomStack() : mHead(nullptr) {}

  void push(int val) {
    ListNode *newNode = new ListNode{mHead, val};
    mHead = newNode;
  }

  void pop() {
    if (empty()) {
      cout << "error" << endl;
      exit(1);
    }
    ListNode *temp = mHead;
    mHead = mHead->mNext;
    delete temp;
    return;
  }

  int top() {
    if (empty()) {
      cout << "error" << endl;
      exit(1);
    }
    return mHead->mData;
  }

  size_t size() {
    int count = 0;
    ListNode *current = mHead;
    while (current != nullptr) {
      count++;
      current = current->mNext;
    }
    return count;
  }

  bool empty() { return mHead == nullptr; }

  ~CustomStack() {
    while (mHead != nullptr) {
      ListNode *temp = mHead;
      mHead = mHead->mNext;
      delete temp;
    }
  }

protected:
  ListNode *mHead;
};

int main() {
  CustomStack stack;
  string command;
  while (cin >> command) {
    if (command == "cmd_push") {
      int n;
      cin >> n;
      stack.push(n);
      cout << "ok" << endl;
    } else if (command == "cmd_pop") {
      if (stack.empty()) {
        cout << "error";
        return 0;
      }
      cout << stack.top() << "\n";
      stack.pop();
    } else if (command == "cmd_top") {
      if (stack.empty()) {
        cout << "error";
        return 0;
      }
      cout << stack.top() << endl;
    } else if (command == "cmd_size") {
      cout << stack.size() << "\n";
    } else if (command == "cmd_exit") {
      cout << "bye" << endl;
      break;
    } else {
      cout << "error" << endl;
      break;
    }
  }
  while (!stack.empty())
    stack.pop();
  return 0;
}
