class CustomStack {
public:
    CustomStack() {
        lenStack = 0;
        this->mHead = nullptr;
    }
    
    ~CustomStack() {
        delete this->mHead;
    }

    void push(int val) {
        ListNode* new_el= new ListNode;
        new_el->mData = val;
        new_el->mNext = nullptr;
        if (lenStack == 0) {
            mHead = new_el;
        }
        else {
            ListNode* current = mHead;
            while (current->mNext != nullptr) {
                current = current->mNext;
            }
            current->mNext = new_el;

        }
        lenStack++;
    }

    void pop() {
        check();
        if (lenStack == 1) {
            this->mHead = nullptr;
        }
        else {
            ListNode* current = mHead;
            while (current->mNext->mNext != nullptr) {
                current = current->mNext;
            }
            current->mNext = nullptr;
        }
        lenStack--;
    }

    int top() {
        check();
        ListNode* current = mHead;
        while (current->mNext != nullptr) {
            current = current->mNext;
        }
        return current->mData;
    }

    size_t size() {
        return lenStack;
    }

    bool empty() {
        if (lenStack == 0) {
            return true;
        }
        return false;
    }

private:
    int lenStack;

    void check() {
        if (lenStack == 0) {
            std::cout << "error\n";
            exit(0);
        }
    }

protected:
    ListNode* mHead;
};

void input(CustomStack& stack) {
    std::string input_cmd;
    int check_input = 1;
    while (check_input) {
        std::cin >> input_cmd;
        if (input_cmd == "cmd_push") {
            int val;
            std::cin >> val;
            stack.push(val);
            std::cout << "ok\n";
        }
        if (input_cmd == "cmd_pop") {
            std::cout << stack.top() << "\n";
            stack.pop();
        }
        if (input_cmd == "cmd_top") {
            std::cout << stack.top() << "\n";
        }
        if (input_cmd == "cmd_size") {
            std::cout << stack.size() << "\n";
        }
        if (input_cmd == "cmd_exit") {
            std::cout << "bye\n";
            check_input = 0;
        }
    }
}

int main() {
    CustomStack stack;
    input(stack); 
    return 0;
}