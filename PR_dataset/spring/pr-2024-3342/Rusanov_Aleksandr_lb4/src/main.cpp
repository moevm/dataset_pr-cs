class CustomStack
{
public:
    CustomStack()
    {
        mHead = new ListNode;
        if (mHead == nullptr)
        {
            cout << "Memory allocation error!";
            exit(1);
        }
        mHead->mNext = nullptr;
    }

    void push(const char *tag)
    {
        if (stack_size == 0)
        {
            mHead->mData = new char[strlen(tag) + 1];
            if (mHead->mData == nullptr)
            {
                cout << "Memory allocation error!";
                exit(1);
            }
            strcpy(mHead->mData, tag);
        }
        else
        {
            ListNode *new_node = new ListNode;
            if (new_node == nullptr)
            {
                cout << "Memory allocation error!";
                exit(1);
            }
            new_node->mData = new char[strlen(tag) + 1];
            if (new_node->mData == nullptr)
            {
                cout << "Memory allocation error!";
                exit(1);
            }
            strcpy(new_node->mData, tag);
            new_node->mNext = mHead;
            mHead = new_node;
        }
        stack_size++;
    }

    void pop()
    {
        ListNode *new_head = mHead->mNext;
        delete[] mHead->mData;
        delete mHead;
        mHead = new_head;
        stack_size--;
    }

    char *top()
    {
        if (!empty())
        {
            return mHead->mData;
        }
        return nullptr;
    }

    size_t size()
    {
        return stack_size;
    }

    bool empty()
    {
        return size() == 0;
    }

    ~CustomStack()
    {
        ListNode *tmp = mHead;
        while (tmp->mNext != nullptr)
        {
            tmp = tmp->mNext;
            delete[] mHead->mData;
            delete mHead;
            mHead = tmp;
        }
    }

private:
    size_t stack_size;

protected:
    ListNode *mHead;
};

int main()
{
    string line;
    getline(cin, line);
    int start = line.find('<');
    int end = line.find('>');
    CustomStack stack;
    bool answer = true;
    while (start != string::npos || end != string::npos)
    {
        string tag = line.substr(start + 1, end - (start + 1));
        if (tag != "br" && tag != "hr")
        {
            if (tag[0] != '/')
            {
                stack.push(tag.c_str());
            }
            else
            {
                if (strcmp(stack.top(), tag.c_str() + 1) != 0)
                {
                    answer = false;
                    break;
                }
                else
                {
                    stack.pop();
                }
            }
        }
        line = line.substr(end + 1);
        start = line.find('<');
        end = line.find('>');
    }
    if (answer)
    {
        cout << "correct";
    }
    else
    {
        cout << "wrong";
    }
    return 0;
}