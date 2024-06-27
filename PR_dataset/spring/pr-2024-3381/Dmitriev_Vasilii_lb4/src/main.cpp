class CustomStack
{
public:
    CustomStack()
    {
        max_count = 20;
        mData = new int[max_count];
        index = -1;
    }

    ~CustomStack()
    {
        delete[] mData;
    }

    void push(int val)
    {
        index++;
        if (index + 1 > max_count)
        {
            extend(20);
        }
        mData[index] = val;
    }

    void pop()
    {
        if (index == -1)
        {
            cerr << "error" << std::endl;
            exit(1);
        }
        index--;
    }

    int top()
    {
        if (index == -1)
        {
            cerr << "error" << std::endl;
            exit(1);
        }
        return mData[index];
    }

    size_t size()
    {
        return index + 1;
    }

    bool empty()
    {
        return index == -1;
    }

private:
    int index;
    int max_count;

    void extend(int n)
    {
        int *mas = new int[max_count + n];
        for (int i = 0; i < max_count; i++)
        {
            mas[i] = mData[i];
        }
        max_count += n;
        delete[] mData;
        mData = mas;
    }

protected:
    int *mData;
};

int main()
{
    CustomStack stack;
    string str;
    while (cin >> str)
    {
        if (str == "cmd_push")
        {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        }
        else if (str == "cmd_pop")
        {
            if (stack.empty())
            {
                cout << "error";
                return 1;
            }
            cout << stack.top() << endl;
            stack.pop();
        }
        else if (str == "cmd_top")
        {
            if (stack.empty())
            {
                cout << "error";
                return 1;
            }
            cout << stack.top() << endl;
        }
        else if (str == "cmd_size")
        {
            cout << stack.size() << endl;
        }
        else if (str == "cmd_exit")
        {
            cout << "bye" << endl;
            break;
        }
    }
    return 0;
}
