class CustomStack
{
public:
    CustomStack()
    {
        mHead = nullptr;
        mSize = 0;
    }

    void push(int value)
    {
        ListNode *node = new ListNode;
        node->mData = value;
        node->mNext = mHead;
        mHead = node;
        mSize++;
    }

    long long pop()
    {
        if (empty())
        {
            cout << "error";
            exit(0);
        }
        long long data = mHead->mData;
        mHead = mHead->mNext;
        mSize--;
        return data;
    }

    long long top()
    {
        if (empty())
        {
            cout << "error";
            exit(0);
        }
        return mHead->mData;
    }

    size_t size()
    {
        return mSize;
    }

    bool empty()
    {
        return mHead == nullptr;
    }

private:
    size_t mSize;

protected:
    ListNode *mHead;
};

CustomStack calculate(CustomStack s, string operation)
{
    int a = s.pop();
    int b = s.pop();
    if (operation == "+")
        s.push(a + b);
    else if (operation == "-")
        s.push(b - a);
    else if (operation == "*")
        s.push(a * b);
    else if (operation == "/")
        s.push(b / a);
    return s;
}

int main()
{
    CustomStack s;
    string mDataBuffer;
    while (cin.peek() != '\n')
    {
        cin >> mDataBuffer;
        if (mDataBuffer == "+" || mDataBuffer == "-" || mDataBuffer == "/" || mDataBuffer == "*")
        {
            s = calculate(s, mDataBuffer);
        }
        else
        {
            s.push(stoi(mDataBuffer));
        }
    }
    if (s.size() > 1)
    {
        cout << "error";
        return (1);
    }
    cout << s.top();
    return 0;
}