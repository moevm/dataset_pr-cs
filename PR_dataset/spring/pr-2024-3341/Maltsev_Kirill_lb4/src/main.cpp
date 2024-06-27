class CustomStack
{
public:

    CustomStack()
    {
        this->mHead = nullptr;
    }
    
    ~CustomStack()
    {
        delete this->mHead;
    }

    void push(int data)
    {
        ListNode* newNode = new ListNode();
        newNode->mData = data;
        newNode->mNext = this->mHead;
        this->mHead = newNode;
    }

    void pop()
    {
        if (this->empty()) {
            this->throwIndexError();
        }
        this->mHead = this->mHead->mNext;
    }

    int top()
    {
        if (this->empty()) {
            throwIndexError();
        }
        return this->mHead->mData;
    }

    size_t size()
    {
        ListNode* current = mHead;
        size_t size = 0;
        while (current != nullptr) {
            current = current->mNext;
            size++;
        }
        return size;
    }

    bool empty()
    {
        return (this->mHead == nullptr);
    }

private:

    void throwIndexError()
    {
        std::cout << "error" << std::endl;
        exit(0);
    }

    void showData(ListNode* node)
    {
        std::cout << node->mData << std::endl;
    }

protected:

    ListNode* mHead;

};

void quit()
{
    std::cout << "bye" << std::endl;
    exit(0);
}

void throwOkMessage()
{
    std::cout << "ok" << std::endl;
}

void commandAllocator(CustomStack& stack)
{
    std::string command;
    while (true) {
        std::cin >> command;
        if (command == "cmd_push") {
            int data;
            std::cin >> data;
            stack.push(data);
            throwOkMessage();
        }
        if (command == "cmd_pop") {
            std::cout << stack.top() << std::endl;
            stack.pop();
        }
        if (command == "cmd_top") {
            std::cout << stack.top() << std::endl;
        }
        if (command == "cmd_size") {
            std::cout << stack.size() << std::endl;
        }
        if (command == "cmd_exit") {
            quit();
        }
    }
}

int main()
{
    CustomStack stack;
    commandAllocator(stack);
    return 0;
}
