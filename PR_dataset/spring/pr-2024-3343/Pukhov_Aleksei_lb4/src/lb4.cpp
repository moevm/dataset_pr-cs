#include <cstring>
#include <iostream>

#define SIZE 3000

class CustomStack
{
public:
    size_t mSize = 0;
    
    void push(const char *tag)
    {
        ListNode *newtag = new ListNode;
        newtag->mData = new char[strlen(tag) + 1];
        newtag->mNext = mHead;
        strcpy(newtag->mData, tag);
        mHead = newtag;
        mSize++;
    }

    void pop()
    {
        if (!empty())
        {
            ListNode *temp = mHead;
            mHead = mHead->mNext;
            delete[] temp->mData;
            delete temp;
            mSize--;
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
            std::cerr << "Error: Stack is empty\n";
            exit(EXIT_FAILURE);;
        }
    }

    size_t size()
    {
        return mSize;
    }

    bool empty()
    {
        return mSize == 0;
    }

protected:
    ListNode *mHead = NULL;
};

int main()
{
    char *html = new char[SIZE];
    fgets(html, SIZE, stdin);
    CustomStack stack;
    int fl = 0;
    char *open;
    char *close;
    open = strchr(html, '<');
    close = strchr(html, '>');
    while (open != NULL && close != NULL)
    {
        char tag[close - open];
        strncpy(tag, open + 1, close - open - 1);
        tag[close - open - 1] = '\0';
        if ((tag[0] != '/') && (strcmp(tag,"br\0") != 0) && (strcmp(tag,"hr\0") != 0))
        {
            stack.push(tag);
            if (fl == 0)
            {
                fl = 1;
            }
        }
        else if ((strcmp(tag,"br\0") != 0) && (strcmp(tag,"hr\0") != 0))
        {
            if (strstr(tag, stack.top()) == NULL)
            {
                if (fl == 1)
                {
                    fl = 0;
                }
                break;
            }
            else
            {
                stack.pop();
            }
        }
        open = strchr(open + 1, '<');
        close = strchr(close + 1, '>');
        tag[0] = '\0';
    }
    if (fl == 1 && stack.empty())
    {
        std::cout << "correct" << std::endl;
    }
    else
    {
        std::cout << "wrong" << std::endl;
    }

    if (!stack.empty())
    {
        while (stack.mSize)
        {
            stack.pop();
        }
    }
    delete[] html;
}