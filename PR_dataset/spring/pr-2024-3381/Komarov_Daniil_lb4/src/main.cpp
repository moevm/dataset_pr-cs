#define BLOCK_SIZE 5

class CustomStack
{
public:
    CustomStack()
    {
        mData = (int *)malloc(sizeof(int) * BLOCK_SIZE);
        mDataSize = BLOCK_SIZE;
        len = 0;
    }

    ~CustomStack()
    {
        free(mData);
    }

    void push(int val)
    {
        if (len == mDataSize)
        {
            extend(BLOCK_SIZE);
        }
        mData[len++] = val;
    }

    void pop()
    {
        if (len == 0)
        {
            throw invalid_argument("Pop on empty stack!");
        }
        len--;
    }

    int top()
    {
        if (len == 0)
        {
            throw invalid_argument("Top on empty stack!");
        }
        return mData[len - 1];
    }

    size_t size()
    {
        return len;
    }

    bool empty()
    {
        return len == 0;
    }

    void extend(int n)
    {
        int *newPtr = (int *)realloc(mData, sizeof(int) * (mDataSize + n));
        if (newPtr == nullptr)
        {
            throw bad_alloc();
        }
        mData = newPtr;
        mDataSize += n;
    }

protected:
    // It's way better to use vector objects to create resizable
    // dynamic arrays in c++, but this task requires to use standart int array,
    // so I'm using c-style memory allocation to allow realloc
    // without copying array content.
    int *mData;
    int mDataSize;
    int len;
};

int main()
{
    // Creating empty stack and entering control loop
    CustomStack stack;
    string cmd;
    while (true)
    {
        cin >> cmd;
        if (cmd == "cmd_push")
        {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        }
        else if (cmd == "cmd_pop")
        {
            if (stack.empty())
            {
                cout << "error" << endl;
                break;
            }
            cout << stack.top() << endl;
            stack.pop();
        }
        else if (cmd == "cmd_top")
        {
            if (stack.empty())
            {
                cout << "error" << endl;
                break;
            }
            cout << stack.top() << endl;
        }
        else if (cmd == "cmd_size")
        {
            cout << stack.size() << endl;
        }
        else if (cmd == "cmd_exit")
        {
            cout << "bye";
            break;
        }
        else if (cmd == "help")
        {
            cout << "Stack simulation program. List of supported commands:"
                 << endl;
            cout << "cmd_push <n> - push element <n> on top the of stack"
                 << endl;
            cout << "cmd_pop      - remove element from top of the stack and "
                    "print it"
                 << endl;
            cout << "cmd_top      - print element from top of the stack"
                 << endl;
            cout << "cmd_size     - print amount of elements in the stack"
                 << endl;
            cout << "cmd_exit     - exit" << endl;
            cout << "help         - print this help" << endl;
        }
        else
        {
            cout << "Unknown command!" << endl
                 << "Type 'help' to show all commands" << endl;
        }
    }
    return 0;
}
