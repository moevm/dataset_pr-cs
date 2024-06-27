#define BLOCK 10



class Thrower {

public:
    template <typename T>
    static inline void info(const T &_x)
    { std::cout << _x << std::endl; }
    
    static inline void error() 
    {
        std::cout << "error";
        std::exit(0);

    }

};


class CustomStack
{
public:
    CustomStack(const std::size_t &_size)
    {
        this->_len = 0;
        this->_size = _size;

        if (_size)
            this->mData = new int[_size];

    }

    CustomStack() : CustomStack(2) {}


    void
    push(int val)
    {
        if (this->_size < this->_len+1)
            this->__alloc_new_memory();

        this->mData[this->_len++] = val;

    }
    
    void
    pop()
    {
        if (!this->_len)
            Thrower::error();

        --this->_len;
    }

    int
    top()
    {
        if (!this->_len)
            Thrower::error();

        return this->mData[this->_len-1];

    }

    int
    get()
    {
        int val = this->top();
        this->pop();
        return val;

    }

    std::size_t
    size() { return this->_len; }

    bool
    empty() { return (bool)this->_len; }
    
    void
    extend(int n)
    {
        this->__alloc_new_memory(n);

    }


    ~CustomStack()
    {
        delete [] this->mData;

    }

private:
    std::size_t _size;
    std::size_t _len;

protected:
    int *mData = nullptr;

private:
    void
    __alloc_new_memory(const std::size_t &_block = BLOCK)
    {
        this->_size += _block;
        int *new_memory_ptr = new int[this->_size];

        for (size_t i = 0; i < this->_len; ++i)
            new_memory_ptr[i] = this->mData[i];

        delete [] this->mData;
        this->mData = new_memory_ptr;

    }
    
};


bool
is_number(const std::string &str)
{
    if (str.size() == 1)
    {
        return std::isdigit(str[0]);

    }

    bool negative = false;

    if (str[0] == '-')
        negative = true;

    for (char ch : str)
    {
        if (negative && ch == '-')
        {
            continue;

        }

        if (!std::isdigit(ch))
            return false;

    }
    return true;

}


int main()
{
    std::string sequence;
    std::getline(std::cin, sequence);

    std::stringstream ss(sequence);
    std::string token;

    CustomStack stack;
    int a, b;

    while (std::getline(ss, token, ' '))
    {
        if (is_number(token))
        {
            stack.push(
                std::stoi(token)
            );

            continue;
        }

        a = stack.get();
        b = stack.get();

        switch (*token.data())
        {
        case '+':
            stack.push(b + a);
            break;

        case '-':
            stack.push(b - a);
            break;
        
        case '*':
            stack.push(b * a);
            break;

        case '/':
            stack.push(b / a);
            break;

        }

    }

    if (stack.size() != 1)
        Thrower::error();

    Thrower::info(stack.top());

    return 0;

}
