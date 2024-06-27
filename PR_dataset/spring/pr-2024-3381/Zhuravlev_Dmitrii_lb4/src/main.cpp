#define MAX_TAG_LEN 100
#define MAX_INPUT_LEN 3000

class CustomStack
{
public:
    CustomStack()
    {
        this->mHead = nullptr;
        this->len = 0;
    }

    void push(const char *tag)
    {
        ListNode *newNode = new ListNode;
        newNode->mData = new char[strlen(tag) + 1];
        strcpy(newNode->mData, tag);
        newNode->mNext = this->mHead;
        this->mHead = newNode;

        this->len++;
    }

    void pop()
    {
        if (this->mHead == nullptr)
        {
            return;
        }
        ListNode *temp = this->mHead;
        mHead = mHead->mNext;
        delete[] temp->mData;
        delete temp;

        this->len--;
    }

    char *top()
    {
        if (this->mHead == nullptr)
        {
            return nullptr;
        }
        return this->mHead->mData;
    }

    size_t size()
    {
        return this->len;
    }

    bool empty()
    {
        return this->mHead == nullptr;
    }

    ~CustomStack()
    {
        while (this->mHead != nullptr)
        {
            this->pop();
        }
    }

protected:
    ListNode *mHead;

private:
    size_t len;
};

int main()
{
    CustomStack stack;
    char input[MAX_INPUT_LEN];
    fgets(input, MAX_INPUT_LEN, stdin);
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++)
    {
        if (input[i] == '<')
        {
            char tag[MAX_TAG_LEN] = {0};
            size_t j = 1;
            while (input[i + j] != '>' && i + j < len)
            {
                tag[j - 1] = input[i + j];
                j++;
            }
            if (tag[0] == '/')
            {
                if (stack.empty())
                {
                    puts("wrong");
                    return 0;
                }
                if (strcmp(stack.top(), tag + 1) != 0)
                {
                    puts("wrong");
                    return 0;
                }
                stack.pop();
            }
            else if (strcmp(tag, "br") != 0 && strcmp(tag, "hr") != 0)
            {
                stack.push(tag);
            }
        }
    }
    if (stack.empty())
    {
        puts("correct");
    }
    else
    {
        puts("wrong");
    }
    return 0;
}