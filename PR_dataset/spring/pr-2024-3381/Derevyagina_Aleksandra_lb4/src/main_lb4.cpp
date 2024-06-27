#define MAX_SIZE 100

class CustomStack
{
public:
    CustomStack()
    {
        mHead = new ListNode;
        mHead->mNext = nullptr;
        last = mHead;
    }

    void push(int val)
    {
        if (empty())
        {
            mHead->mData = val;
        }
        else
        {
            ListNode *mNext = new ListNode{nullptr, val};
            last->mNext = mNext;
            last = mNext;
        }
        countElements++;
    }

    void pop()
    {
        if (size() == 1)
        {
            countElements--;
            return;
        }
        else
        {
            ListNode *element = mHead;
            while (element->mNext != last)
            {
                element = element->mNext;
            }
            delete element->mNext;
            element->mNext = nullptr;
            last = element;
            this->countElements--;
        }
    }

    int top()
    {
        return last->mData;
    }

    size_t size()
    {
        return countElements;
    }

    bool empty()
    {
        return countElements == 0;
    }

private:
    size_t countElements = 0;

protected:
    ListNode *mHead;
    ListNode *last;
};

int main()
{
    char getStr[MAX_SIZE + 1];
    fgets(getStr, MAX_SIZE, stdin);
    getStr[strlen(getStr) - 1] = '\0';
    char *space = strtok(getStr, " ");
    auto stack = new CustomStack;
    while (space != nullptr && strlen(space) > 0)
    {
        char symbol = space[0];
        if (strlen(space) != 1 ||
            (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '+'))
        {
            stack->push(atoi(space));
        }
        else
        {
            if (stack->size() < 2)
            {
                cout << "error";
                return 0;
            }
            int secondElement = stack->top();
            stack->pop();
            int firstElement = stack->top();
            stack->pop();
            if (symbol == '+')
            {
                stack->push(firstElement + secondElement);
            }
            if (symbol == '-')
            {
                stack->push(firstElement - secondElement);
            }
            if (symbol == '*')
            {
                stack->push(firstElement * secondElement);
            }
            if (symbol == '/')
            {
                stack->push(firstElement / secondElement);
            }
        }
        space = strtok(NULL, " ");
    }
    if (stack->size() > 1)
    {
        cout << "error";
    }
    else
    {
        cout << stack->top();
    }
    return 0;
}
