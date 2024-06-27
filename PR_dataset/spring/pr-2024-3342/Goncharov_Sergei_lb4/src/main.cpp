class CustomStack {
public:
    CustomStack() : mHead(nullptr) {}   // Конструктор

    void push(int val) {
        ListNode* newNode = new ListNode;
        
        if (newNode == nullptr) {       // Проверка удалось ли выделить память
            cerr << "memory allocation error!";
        }
        
        newNode->mData = val;
        newNode->mNext = mHead;
        mHead = newNode;
    }

    void pop() {
        if (empty()) {
            return;
        }

        ListNode* temp = mHead;
        mHead = mHead->mNext;
        delete temp;
    }

    int top() const {
        if (empty()) {
            std::cout << "error" << std::endl;
            exit(1);
        }
        return mHead->mData;
    }

    size_t size() const {
        size_t count = 0;
        ListNode* current = mHead;

        while (current) {
            count++;
            current = current->mNext;
        }
        return count;
    }

    bool empty() const {
        return mHead == nullptr;
    }

    ~CustomStack() {                    // Деструктор
        while (!empty()) {
            pop();
        }
    }
    ListNode* mHead;
};

int main() {
    CustomStack stack;

    std::string command;
    while (std::cin >> command) {
        if (command == "cmd_push") {
            int val;
            std::cin >> val;
            stack.push(val);
            std::cout << "ok" << std::endl;
        } else if (command == "cmd_pop") {
            if (!stack.empty()) {
                std::cout << stack.top() << std::endl;
                stack.pop();
            } else {
                std::cout << "error" << std::endl;
                stack.pop();
                break;
            }
        } else if (command == "cmd_top") {
            if (!stack.empty()) {
                std::cout << stack.top() << std::endl;
            } else {
                std::cout << "error" << std::endl;
                break;
            }
        } else if (command == "cmd_size") {
            std::cout << stack.size() << std::endl;
        } else if (command == "cmd_exit") {
            std::cout << "bye" << std::endl;
            break;
        } else {
            std::cout << "error" << std::endl;
            break;
        }
    }

    return 0;
}
