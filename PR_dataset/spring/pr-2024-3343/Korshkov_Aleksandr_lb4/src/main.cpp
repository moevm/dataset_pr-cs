class CustomStack
{
public:
    CustomStack(size_t initialCapacity)
    {
        this->mCapacity = initialCapacity;
        this->mData = new int[initialCapacity];
        this->mIndex = -1;
    }
    CustomStack(): CustomStack(10)
    {
    }
    ~CustomStack()
    {
        delete[] this->mData;
    }
    void push(int val)
    {
        if (this->mIndex + 1 == mCapacity)
        {
            size_t newCapacity = this->getNewCapacity();
            this->resize(newCapacity);
        }
        this->mIndex++;
        this->mData[this->mIndex] = val;
    }
    void pop()
    {
        if (this->empty())
        {
            cout << "error";
            exit(0);
        }
        this->mIndex--;
    }
    int top()
    {
        if (this->empty())
        {
            cout << "error";
            exit(0);
        }
        return this->mData[this->mIndex];
    }
    size_t size() const
    {
        return this->mIndex + 1;
    }
    bool empty() const
    {
        return this->mIndex == -1;
    }
    void extend(int n)
    {
        if (n <= 0)
        {
            cout << "error";
            exit(0);
        }
        this->resize(this->mCapacity + n);
    }

protected:
    size_t mCapacity;
    size_t mIndex;
    int *mData;
    size_t getNewCapacity() const
    {
        return this->mCapacity * 3 / 2 + 1;
    }
    void resize(size_t newCapacity)
    {
        if (newCapacity == mCapacity)
        {
            return;
        }
        if (newCapacity < mCapacity)
        {
            cout << "error";
            exit(0);
        }
        int *newData = new int[newCapacity];
        copy(this->mData, this->mData + this->mCapacity, newData);
        delete[] this->mData;
        this->mData = newData;
        this->mCapacity = newCapacity;
    }
};

int main()
{
    CustomStack stack;
    string s("");
    getline(cin, s);
    stringstream ss(s);
    string word;
    while (ss >> word)
    {
        if (word == "-" || word == "+" || word == "*" || word == "/")
        {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            if (word == "-")
            {
                stack.push(a - b);
            }
            else if (word == "+")
            {
                stack.push(a + b);
            }
            else if (word == "*")
            {
                stack.push(a * b);
            }
            else if (word == "/")
            {
                stack.push(a / b);
            }
        }
        else
        {
            int i = stoi(word);
            stack.push(i);
        }
    }
    if (stack.size() == 1)
        cout << stack.top() << endl;
    else
        cout << "error";
    return 0;
}
