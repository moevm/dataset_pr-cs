
#include <iostream>
#include <string>

class CustomStack
{
public:
    CustomStack() : mHead(nullptr) {}

    ~CustomStack()
    {
        while (mHead)
        {
            auto temp = mHead;
            mHead = mHead->mNext;
            delete temp;
        }
    }

    void push(int val)
    {
        auto temp = make_ListNode(val);
        auto end = get_end_ListNode();
        if (!end)
            mHead = temp;
        else
            end->mNext = temp;

        std::cout << "ok\n";
    }

    void pop()
    {
        auto end = get_end_ListNode(true);

        if (!end)
            exitExec();
        else if (end == mHead && !mHead->mNext)
        {
            delete end;
            mHead = nullptr;
        }
        else
        {
            delete (end->mNext);
            end->mNext = nullptr;
        }
    }

    int top()
    {
        auto end = get_end_ListNode();
        if (!end)
            exitExec();
        return end->mData;
    }

    size_t size()
    {
        auto temp = mHead;
        if (!temp)
            return 0;

        int count = 1;
        for (; temp->mNext; count++)
            temp = temp->mNext;

        return count;
    }

    bool empty()
    {
        return !mHead;
    }

private:
    ListNode *make_ListNode(int val)
    {
        ListNode *ln = new ListNode;
        if (!ln)
            exitExec();
        ln->mNext = nullptr;
        ln->mData = val;

        return ln;
    }

    ListNode *get_end_ListNode(bool returnOneBeforeLast = false)
    {
        auto temp = mHead;
        if (!temp)
            return nullptr;

        auto prev = temp;
        while (temp->mNext)
        {
            prev = temp;
            temp = temp->mNext;
        }
        return returnOneBeforeLast ? prev : temp;
    }

    void exitExec()
    {
        std::cout << "error\n";
        exit(0);
    }

protected:
    ListNode *mHead;
};

int main()
{
    {

        auto stack = CustomStack();
        std::string cmd = "";
        do
        {
            std::cin >> cmd;
            if (!cmd.compare("cmd_push"))
            {
                int val = 0;
                std::cin >> val;
                stack.push(val);
            }
            else if (!cmd.compare("cmd_pop"))
            {
                std::cout << stack.top() << '\n';
                stack.pop();
            }
            else if (!cmd.compare("cmd_top"))
            {
                std::cout << stack.top() << '\n';
            }
            else if (!cmd.compare("cmd_size"))
            {
                std::cout << stack.size() << '\n';
            }
            else if (!cmd.compare("cmd_exit"))
            {
                std::cout << "bye";
                exit(0);
            }
            std::cin.ignore();

        } while (cmd.compare("cmd_exit") != 0);
    }
}
