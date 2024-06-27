class CustomStack
{
public:
    CustomStack()
    {
        count = 0;
        mHead = nullptr;
    }
    void push(int val)
    {
        ListNode *newElem{new ListNode};
        newElem->mData = val;
        newElem->mNext = mHead;
        mHead = newElem;
        count++;
    }
    void pop()
    {
        if (!count)
            throw "error";
        ListNode *next = mHead->mNext;
        delete mHead;
        mHead = next;
        count--;
    }
    int top()
    {
        if (!count)
            throw "error";
        return mHead->mData;
    }
    size_t size()
    {
        return count;
    }
    bool empty()
    {
        return count == 0;
    }
    ~CustomStack()
    {
        while(!this->empty())
        {
            this->pop();
        }
    }

protected:
    ListNode* mHead;
    size_t count;
};

int operation(const int a, const int b, const string &op)
{
    if (op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "*")
        return a * b;
    else
        return a / b;
}

int main()
{
    try
    {
        CustomStack someStack;
        string buff, curr, operations{"+-*/"}, space{" "};
        size_t start{}, end;
        int a, b;
        getline(cin, buff, '\n');


        while(start != string::npos)
        {
            end = buff.find(space, start + 1);
            if (end == string::npos)
                end = buff.length();
            curr = buff.substr(start, end - start);

            if (operations.find(curr) != string::npos)
            {
                b = someStack.top(), someStack.pop();
                a = someStack.top(), someStack.pop();
                someStack.push(operation(a, b, curr));
            }
            else
                someStack.push(stoi(curr));

            start = buff.find_first_not_of(space, end + 1);
        }

        if (someStack.size() > 1)
            throw "error";
        cout << someStack.top() << endl;
    }
    catch (const char *errorMessage)
    {
        cout << errorMessage << endl;
    }
    return 0;
}
