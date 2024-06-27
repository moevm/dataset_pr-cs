#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<iostream>
using namespace std;
#define SIZE 50
#define STR_SIZE 101
#define ERROR "error"

class CustomStack
{
    public:

        CustomStack()
        {
            length = 0;
            mData = new int[SIZE * sizeof(int)];
            size_count = 1;
        }

        void push(int val)
        {
            if(length >= size_count * SIZE * sizeof(int))
            extend(SIZE);
            mData[length++] = val;
        }

        void pop()
        {
            if(!empty())
            length--;
            else
            {
                cout<<ERROR;
                exit(0);
            }
            
        }

        int top()
        {
            if(!empty())
            return mData[length-1];
            else
            {
                cout<<ERROR;
                exit(0);
            }
        }

        int size()
        {
            return length;
        }

        bool empty()
        {
            return (length) == 0;
        }

        void extend(int n)
        {
        int* nData = new int[length + n];
        for (int i = 0; i < length; ++i)
        {
            nData[i] = mData[i];
        }
        delete[] mData;
        mData = nData;
        length += n;
        }

        ~CustomStack()
        {
            length = 0;
            delete[] mData;
        }
    private:
        int length = 0;
        int size_count = 1;
    
    protected:
        int* mData;
};

void solve()
{
    CustomStack my_stack = CustomStack();
    
    char str[STR_SIZE];
    fgets(str, STR_SIZE, stdin);
    
    int first, second, result;
    char oper;
    char* value = (char*) malloc(SIZE);
    int value_size = 0;
    int number;

    int str_size = strlen(str);

    for(int i = 0; i < str_size; i++)
    {
        if((i == 0 && str[i] =='-') || (i != str_size-1 && str[i] == '-' && isdigit(str[i+1])) || isdigit(str[i]))
        {
            value[value_size++] = str[i];
        }
        if(str[i] == ' ' && (i>0 && isdigit(str[i-1])) || (i == str_size-1 && isdigit(str[i])))
        {
            sscanf(value, "%d", &number);
            my_stack.push(number);
            value = (char*) malloc(SIZE);
            value_size = 0;
        }
        if(!isdigit(str[i]) && str[i] != ' ' && !(i != str_size-1 && isdigit(str[i+1])))
        {
            oper = str[i];

            first = my_stack.top();
            my_stack.pop();
            
            second = my_stack.top();
            my_stack.pop();
            
            if(oper == '+')
            result = first + second;
            else if(oper == '-')
            result = second - first;
            else if(oper == '*')
            result = first * second;
            else if(oper == '/')
            result = second / first;

            my_stack.push(result);
        }
    }
    if(my_stack.size() == 1)
    cout<<my_stack.top()<<endl;
    else
    cout<<ERROR;
}

int main()
{
    solve();
}