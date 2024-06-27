const int MAX_LEN = 101;
const int INITIAL_SIZE = 10;

class CustomStack
{
public:
    CustomStack()
    {
        tmp = -1;
        currentSize = INITIAL_SIZE;
        mData = new int[currentSize];
    }

    ~CustomStack()
    {
        delete[] mData;
    };

    void push(int val)
    {
        if (tmp >= currentSize - 1)
        {
            extend(INITIAL_SIZE);
        }
        mData[++tmp] = val;
    }

    void pop()
    {
        if (empty())
        {
            cout << "error";
            return;
        }
        tmp--;
    }

    int top()
    {
        if (empty())
        {
            cout << "error";
            return -1;
        }
        return mData[tmp];
    }

    int size()
    {
        return tmp + 1;
    }

    bool empty()
    {
        return tmp == -1;
    }

    void extend(int n)
    {
        int *newData = new int[currentSize + n];
        for (int i = 0; i < currentSize; ++i)
        {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        currentSize += n;
    }

private:
    int tmp;
    size_t currentSize;

protected:
    int *mData;
};

int main()
{
    CustomStack stack;
    char line[MAX_LEN];
    cin.getline(line, MAX_LEN - 1);
    char separator = ' ';
    string currentSymbol;
    int result = 0, lineSize = 0;
    for (int i = 0; line[i]; i++)
    {
        lineSize++;
    }
    for (int i = 0; line[i]; i++)
    {
        int flag = 0;
        if (line[i] != separator and i == lineSize - 1)
        {
            currentSymbol += line[i];
            flag = 1;
        }
        if (line[i] == separator or flag == 1)
        {
            int count = 0;
            for (const char c : currentSymbol)
            {
                if (isdigit(c))
                {
                    count++;
                }
            }
            if (count > 0 and (count == currentSymbol.size() or
                               count == currentSymbol.size() - 1))
            {
                stack.push(stoi(currentSymbol));
            }
            else if (currentSymbol.size() == 1 and
                     (currentSymbol[0] == '+' or currentSymbol[0] == '-' or
                      currentSymbol[0] == '*' or currentSymbol[0] == '/'))
            {
                if (stack.size() >= 2)
                {
                    int a, b;
                    a = stack.top();
                    stack.pop();
                    b = stack.top();
                    stack.pop();
                    switch (currentSymbol[0])
                    {
                        case '+':
                            result = a + b;
                            break;
                        case '-':
                            result = b - a;
                            break;
                        case '*':
                            result = a * b;
                            break;
                        case '/':
                            result = b / a;
                            break;
                    }
                    stack.push(result);
                }
            }
            currentSymbol.clear();
        }
        else
        {
            currentSymbol += line[i];
        }
    }
    if (stack.size() > 1)
    {
        cout << "error";
    }
    else
    {
        cout << result;
    }
    return 0;
}