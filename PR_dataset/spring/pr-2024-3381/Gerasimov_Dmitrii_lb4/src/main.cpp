#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

class CustomStack
{
private:
    void extend(int n)
    {
        char **tmp;
        tmp = new char *[length + n];
        for (size_t i = 0; i < length; i++)
        {
            tmp[i] = mData[i];
        }
        if (mData != nullptr) delete[] mData;
        mData = tmp;
        count += n;
    }

public:
    CustomStack(size_t size = 1000)
    {
        length = 0;
        count = size;
        mData = nullptr;
        extend(size);
    }

    ~CustomStack()
    {
        for (size_t i = 0; i < this->length; i++)
        {
            delete mData[i];
        }
        delete[] mData;
    }

    void push(const char *val)
    {
        if (length >= count)
        {
            extend(10);
        }
        mData[length++] = strdup(val);
    }

    void pop()
    {
        if (length <= 0)
        {
            return;
        }
        delete mData[--length];
    }

    char *top()
    {
        if (length <= 0)
        {
            return nullptr;
        }
        return mData[length - 1];
    }

    size_t size()
    {
        return length;
    }

    bool empty()
    {
        return length == 0;
    }

protected:
    char **mData;
    size_t length;
    size_t count;
};

int main()
{
    string s;
    getline(cin, s);
    CustomStack st;
    string tmp = "";
    for (auto i : s)
    {
        if (i == '<')
        {
            tmp += i;
        }
        else if (!tmp.empty())
        {
            tmp += i;
            if (i == '>')
            {
                if (tmp == "<br>" || tmp == "<hr>")
                {
                    tmp = "";
                }
                else if (tmp[1] == '/')
                {
                    tmp.erase(1, 1);
                    if (!strcmp(tmp.c_str(), st.top()))
                    {
                        st.pop();
                        tmp = "";
                    }
                    else
                    {
                        cout << "wrong\n";
                        return 0;
                    }
                }
                else
                {
                    st.push(tmp.c_str());
                    tmp = "";
                }
            }
        }
    }
    cout << "correct\n";
    return 0;
}