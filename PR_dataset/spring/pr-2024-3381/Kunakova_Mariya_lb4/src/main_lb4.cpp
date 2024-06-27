class CustomStack
{
protected:
    ListNode *mHead;

public:
    CustomStack()
    {
        mHead = nullptr;
    }

    void push(const char *tag)
    {
        ListNode *newEl = new ListNode;
        newEl->mData = new char[strlen(tag) + 1];
        strcpy(newEl->mData, tag);
        newEl->mNext = mHead;
        mHead = newEl;
    }

    void pop()
    {
        if (!empty())
        {
            ListNode *newHead = mHead->mNext;
            delete[] mHead->mData;
            delete mHead;
            mHead = newHead;
        }
    }

    char *top()
    {
        if (!empty())
        {
            return mHead->mData;
        }
        else
        {
            return nullptr;
        }
    }

    size_t size()
    {
        size_t length = 0;
        ListNode *current = mHead;
        while (current != nullptr)
        {
            length++;
            current = current->mNext;
        }
        return length;
    }

    bool empty()
    {
        return (size() == 0);
    }

    ~CustomStack()
    {
        while (mHead != nullptr)
        {
            pop();
        }
    }
};

bool checkHtml(string &html)
{
    CustomStack stack;
    int startOfTag = (int)html.find('<');
    int endOfTag = (int)html.find('>');
    while (startOfTag != string::npos || endOfTag != string::npos)
    {
        string tagValue =
            html.substr(startOfTag + 1, endOfTag - startOfTag - 1);
        if (tagValue != "br" && tagValue != "hr")
        {
            if (tagValue[0] != '/')
            {
                stack.push(tagValue.c_str());
            }
            else
            {
                if (strcmp(stack.top(), tagValue.c_str() + 1) != 0)
                {
                    return false;
                }
                else
                {
                    stack.pop();
                }
            }
        }
        html = html.substr(endOfTag + 1);
        startOfTag = html.find('<');
        endOfTag = html.find('>');
    }
    if (stack.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    string html;
    getline(cin, html);
    if (checkHtml(html))
    {
        cout << "correct" << endl;
    }
    else
    {
        cout << "wrong" << endl;
    }
    return 0;
}
