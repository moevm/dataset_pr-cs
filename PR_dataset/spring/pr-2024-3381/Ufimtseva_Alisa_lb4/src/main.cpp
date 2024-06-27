class CustomStack
{
public:
    // Constructor
    CustomStack()
    {
        mData = new char *[mCapacity];
        mIndex = -1;
    }

    // Destructor
    ~CustomStack()
    {
        delete[] mData;
    }

    void push(const char *val)
    {
        mIndex++;
        if (mIndex >= mCapacity)
        {
            extend(mCapacity);
        }
        mData[mIndex] = new char[strlen(val) + 1];
        strcpy(mData[mIndex], val);
    }

    char *top()
    {
        return mData[mIndex];
    }

    char *pop()
    {
        return mData[mIndex--];
    }

    bool empty()
    {
        return mIndex == -1;
    }

    size_t size()
    {
        return mIndex + 1;
    }

    void extend(int n)
    {
        char **newData = new char *[mCapacity + n];
        for (size_t i = 0; i <= mIndex; ++i)
        {
            newData[i] = mData[i];
        }
        delete[] mData;
        mCapacity += n;
        mData = newData;
    }

private:
    int mIndex;
    size_t mCapacity = 10;

protected:
    char **mData;
};

int main()
{
    string commands;
    getline(cin, commands);
    CustomStack st;
    for (int i = 0; i < commands.size(); i++)
    {
        char tag[10];
        if (commands[i] == '<')
        {
            int j = i + 1, n = 0;
            while (commands[j] != '>')
            {
                tag[n] = commands[j];
                n++;
                j++;
            }
            tag[n] = '\0';
            if (tag[0] == '/')
            {
                if (st.empty())
                {
                    cout << "wrong";
                    return 0;
                }
                char *check = st.top();
                for (int k = 1; tag[k]; k++)
                {
                    if (check[k - 1] != tag[k])
                    {
                        cout << "wrong";
                        return 0;
                    }
                }
                st.pop();
            }
            else if (strcmp(tag, "br") != 0 && strcmp(tag, "hr") != 0)
            {
                st.push(tag);
            }
            i = j;
        }
    }
    if (st.empty())
    {
        cout << "correct";
        return 0;
    }
    cout << "wrong";
    return 0;
}