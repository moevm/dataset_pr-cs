class CustomStack {
public:
    CustomStack()
    {
        mData=new int[1];
        mLength=0;
        mSize=1;
    }
    void push(int val)
    {
        if(mLength>=mSize)
        {  
            int* newData = new int[mSize+1];
            memcpy(newData, mData, sizeof(int)*mSize);
            mSize++;
            delete[] mData;
            mData=newData;
        }
        mData[mLength++]=val;
    }
    void pop()
    {
        if(mLength<=0)
            throw std::logic_error("pop() called on empty stack!");
        mData[--mLength]=0;
        int* newData=new int[--mSize];
        memcpy(newData, mData, sizeof(int)*mSize);
        delete[] mData;
        mData=newData;
    }
    int top()
    {
        if(mLength<=0)
            throw std::logic_error("top() called on empty stack!");
        return mData[mLength-1];
    }
    size_t size()
    {
        return mLength;
    }
    bool empty()
    {
        return mLength==0;
    }
    void extend(int n)
    {
        int* newData = new int[mSize+n];
        memcpy(newData, mData, sizeof(int)*mSize);
        mSize+=n;
        delete[] mData;
        mData=newData;
    }
    ~CustomStack()
    {
        delete[] mData;
        mSize=0;
        mLength=0;
    }
protected:
    int* mData;
private:
    size_t mLength;
    size_t mSize;
};

void cmd_push(CustomStack &stack, int n)
{
    stack.push(n);
    std::cout<<"ok"<<std::endl;
}
void cmd_pop(CustomStack &stack)
{
    int val;
    try
    {
        val=stack.top();
        stack.pop();
    }
    catch(const std::exception& e)
    {
        std::cout<<"error"<<std::endl;
        exit(0);
    }
    std::cout<<val<<std::endl;
}
void cmd_top(CustomStack &stack)
{
    int val;
    try
    {
        val=stack.top();
    }
    catch(const std::exception& e)
    {
        std::cout<<"error"<<std::endl;
        exit(0);
    }
    std::cout<<val<<std::endl;
}
void cmd_size(CustomStack &stack)
{
    std::cout<<stack.size()<<std::endl;
}
void cmd_exit()
{
    std::cout<<"bye";
    exit(0);
}

void cmdExecution(CustomStack &stack)
{
    std::string newCommand;
    while(true)
    {
        std::cin>>newCommand;
        if (newCommand=="cmd_push")
        {
            int data;
            std::cin>>data;
            cmd_push(stack, data);
        }
        if(newCommand=="cmd_pop")
            cmd_pop(stack);
        if(newCommand=="cmd_top")
            cmd_top(stack);
        if(newCommand=="cmd_size")
            cmd_size(stack);
        if(newCommand=="cmd_exit")
            cmd_exit();
    };
    
}

int main() {
    CustomStack stack;
    cmdExecution(stack);
    return 0;
}
