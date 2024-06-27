class CustomStack {

public:
    CustomStack()
    {
        mHead = nullptr;
    }      
    void
    push(int val)
    {
        ListNode* root = new ListNode;
        if(!root){
            std::cout << "Memory allocation error" << std::endl;
            exit(1);
        }
        root->mData = val;
        root->mNext = mHead;
        mHead = root;
    } 
    void
    pop()
    {
        if(empty())
        {
            return;
        }
        ListNode* temp = mHead;
        mHead = mHead->mNext;
        delete temp;
    }
    int
    top()
    {
        return mHead->mData;
    }
    size_t
    size()
    {
        size_t count = 0;
        ListNode* current = mHead;
        while (current != nullptr)
        {
            count++;
            current = current->mNext;
        }
        return count;
    }
    bool
    empty()
    {
        if(mHead)
            return false;
        
        return true;
        
    }
    ~CustomStack()
    {
        while(!empty())
        {
            pop();
        }
    }
protected:

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
            if(!stack.empty())
            {
                std::cout << stack.top() << std::endl; 
                stack.pop();
            }
            else
            {
                std::cout << "error";
                stack.pop();
                break;
            }
        } else if (command == "cmd_top") {
            if(!stack.empty()){
                std::cout << stack.top() << std::endl;
            }
            else
            {
                std::cout << "error";
                break;
            }
        } else if (command == "cmd_size") {
            std::cout << stack.size() << std::endl;
        } else if (command == "cmd_exit") {
            std::cout << "bye";
            break;
        }
    }

    return 0;
}
