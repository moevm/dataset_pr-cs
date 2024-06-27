class CustomStack {
public:
    CustomStack() { 
        mHead = NULL;
    }

    ~CustomStack() {
        ListNode *current = mHead;
        while (current != NULL) {
            ListNode *next = current->mNext;
            delete current;
            current = next;
        }
    }

    void push(int val) {
        if (empty()) {
            mHead = new ListNode{NULL, val};
            return;
        }

        ListNode *tmp = mHead;
        while (tmp->mNext != NULL) {
            tmp = tmp->mNext;
        }
        tmp->mNext = new ListNode{NULL, val};
    }

    void pop() {
        if (mHead->mNext == NULL) {
            ListNode *tmp = mHead;
            mHead = NULL;
            delete tmp;
            return;
        }

        ListNode *tmp = mHead;
        while (tmp->mNext->mNext != NULL) {
            tmp = tmp->mNext;
        }
        delete tmp->mNext;
        tmp->mNext = NULL;
    }

    int top() {
        ListNode *tmp = mHead;
        while (tmp->mNext != NULL) {
            tmp = tmp->mNext;
        }
        return tmp->mData;
    }

    size_t size() {
        if (empty()) {
            return 0;
        }

        int ans = 1;
        ListNode *tmp = mHead;
        while (tmp->mNext != NULL) {
            ans++;
            tmp = tmp->mNext;
        }
        return ans;
    }

    bool empty() {
        return mHead == NULL;
    }

protected:
    struct ListNode {
        ListNode *mNext;
        int mData;
    };

    ListNode *mHead;
};

int main() {
    CustomStack stack;
    string s;
    cin >> s;

    while (s != "cmd_exit") {
        if (s == "cmd_push") {
            int a;
            cin >> a;
            stack.push(a);
            cout << "ok\n";
        } else if (s == "cmd_pop") {
            if (stack.empty()) {
                cout << "error";
                return 0;
            }
            cout << stack.top() << "\n";
            stack.pop();
        } else if (s == "cmd_top") {
            if (stack.empty()) {
                cout << "error";
                return 0;
            }
            cout << stack.top() << "\n";
        } else if (s == "cmd_size") {
            cout << stack.size() << "\n";
        } else {
            cout << "Envalid command " << s << endl;
        }
        cin >> s;
    }

    cout << "bye";

    while (!stack.empty()) {
        stack.pop();
    }

    return 0;
}