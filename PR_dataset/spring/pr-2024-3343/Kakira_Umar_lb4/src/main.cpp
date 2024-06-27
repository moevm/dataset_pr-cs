class CustomStack {
protected:
    ListNode* mHead;

public:
    CustomStack() : mHead(nullptr) {}

    ~CustomStack() {
        while (!empty()) {
            pop();
        }
    }

    void push(int val) {
        ListNode* node = new ListNode;
        node->mData = val;
        node->mNext = mHead;
        mHead = node;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("error");
        }

        ListNode* tmp = mHead;
        mHead = mHead->mNext;
        delete tmp;
    }

    int top() {
        if (empty()) {
            throw std::runtime_error("error");
        }
        return mHead->mData;
    }

    size_t size() {
        size_t size = 0;
        ListNode* node = mHead;
        while (node != nullptr) {
            node = node->mNext;
            size++;
        }
        return size;
    }

    bool empty() {
        return mHead == nullptr;
    }
};

int main() {
    CustomStack stack;
    std::string str;
    std::getline(std::cin, str);

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            continue;
        }
        else if (isdigit(str[i]) || (str[i] == '-' && isdigit(str[i+1]))) {
            int j = i+1;
            while (isdigit(str[j])) {
                j++;
            }
            stack.push(std::stoi(str.substr(i, j-i)));
            i = j-1;
        }
        else {
            int num1, num2, res;
            try {
                num1 = stack.top();
                stack.pop();
                num2 = stack.top();
                stack.pop();
            }
            catch (const std::runtime_error& error) {
                std::cout << "error" << std::endl;
                return 0;
            }

            switch(str[i]) {
                case '+': res = num1 + num2; break;
                case '-': res = num2 - num1; break;
                case '*': res = num1 * num2; break;
                case '/':
                    if(num1 == 0) {
                        std::cout << "error" << std::endl;
                        return 0;
                    }
                    res = num2 / num1;
                    break;
                default: std::cout << "error" << std::endl; return 0;
            }

            stack.push(res);
        }
    }

    if (stack.size() != 1) {
        std::cout << "error" << std::endl;
        return 0;
    }

    std::cout << stack.top() << std::endl;

    return 0;
}