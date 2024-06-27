class CustomStack
{
private:
    ListNode *createListNode(int val)
    {
        ListNode *element = (ListNode *)malloc(sizeof(ListNode));
        element->mData = val;
        element->mNext = NULL;

        return element;
    }

    size_t sizeOfStack = 0;

public:
    CustomStack()
    {
        this->mHead = createListNode(0);
    }

    ~CustomStack()
    {
        while (this->mHead != NULL)
        {
            pop();
        }
    }

    void push(int val)
    {
        if (empty())
        {
            this->mHead->mData = val;
        }
        else
        {
            ListNode *elementToPush = createListNode(val);
            elementToPush->mNext = this->mHead;
            this->mHead = elementToPush;
        }

        sizeOfStack++;
    }

    void pop()
    {
        if (sizeOfStack > 1)
        {
            ListNode *tmp = this->mHead;
            this->mHead = tmp->mNext;
            free(tmp);
        }
        sizeOfStack--;
    }

    int top()
    {
        return this->mHead->mData;
    }

    size_t size()
    {
        return sizeOfStack;
    }

    bool empty()
    {
        return sizeOfStack == 0;
    }

protected:
    ListNode *mHead;
};

int main()
{
    int flag = 1;
    CustomStack stackExample;
    string terminalInput;
    getline(cin, terminalInput);
    while (terminalInput.compare("cmd_exit"))
    {
        if (terminalInput.find("cmd_push") != string::npos)
        {
            string sub = terminalInput.substr(9, terminalInput.length());
            int valueToPush = stoi(sub);
            stackExample.push(valueToPush);
            cout << "ok\n";
        }
        else if (terminalInput.find("cmd_pop") != string::npos)
        {
            if (stackExample.size() > 0)
            {
                cout << stackExample.top();
                cout << "\n";
                stackExample.pop();
            }
            else
            {
                flag = 0;
                break;
            }
        }
        else if (terminalInput.find("cmd_top") != string::npos)
        {
            if (stackExample.size() > 0)
            {
                cout << stackExample.top();
                cout << "\n";
            }
            else
            {
                flag = 0;
                break;
            }
        }
        else if (terminalInput.find("cmd_size") != string::npos)
        {
            cout << stackExample.size();
            cout << "\n";
        }
        getline(cin, terminalInput);
    }

    if (flag == 1)
    {
        cout << "bye" << endl;
    }
    else
    {
        cout << "error";
    }
    
    return 0;
}
