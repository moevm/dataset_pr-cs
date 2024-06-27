class CustomStack
{
public:
    // методы push, pop, size, empty, top + конструкторы, деструктор
    CustomStack()
    {
        mHead = new ListNode;
        mHead -> mNext = nullptr;
    }

    ~CustomStack()
    {
        while(!empty())
        {
            pop();
        }
        delete mHead;
    }
    
    //новый элемент, val в поле для данных, Next - старая голова, новая голова - новый элемент, размер стека++
    void push(int val)
    {
        ListNode* NewListHead = new ListNode;
        NewListHead -> mData = val;
        NewListHead -> mNext = mHead;
        mHead = NewListHead;
        StackSize++;
    }
    
    //новый элемент = следующий от головы, удаление старой головы, новая голова = новый элемент = следующий от старой головы,
    //размер стека--
    void pop()
    {
        ListNode* NewListHead = mHead -> mNext;
        delete mHead;
        mHead = NewListHead;
        StackSize--;
    }
    
    //вернуть последний элемент
    int top()
    {
        return mHead -> mData;
    }
    
    //вернуть размер стека
    size_t size()
    {
        return StackSize;
    }
    
    //Возвращает true/false, если стек пуст/не пуст
    bool empty()
    {
        return (StackSize == 0);
    }
    
private:
    // поля класса, к которым не должно быть доступа извне
    size_t StackSize = 0;

protected:
    // в этом блоке должен быть указатель на голову
    ListNode* mHead;
};

int main() {
    CustomStack stack;
    string input;

    while (cin >> input)
    {
        //добавление в стек число n
        if (input == "cmd_push")
        {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        }
        
        //если стэк пуст - вывод ошибки / полон - вывод последнего на экран и удаление его
        else if(input == "cmd_pop")
        {
            if (stack.empty())
            {
                cout << "error" << endl;
                break;
            }
            else
            {
                cout << stack.top() << endl;
                stack.pop();
            }

        }
        
        //если стэк пуст - вывод ошибки / полон - вывод последнего на экран
        else if(input == "cmd_top")
        {
            if(stack.empty())
            {
                cout << "error" << endl;
                break;
            }
            else
            {
                cout << stack.top() << endl;
            }
        }
        
        //вывод количество элементов в стеке
        else if(input == "cmd_size")
        {
            cout << stack.size() << endl;
        }
        
        //вывод "bye" и завершить работу
        else if(input == "cmd_exit")
        {
            cout << "bye" << endl;
            break;
        }
        
        //введена неверная команда - вывести ошибку и завершить программу
        else
        {
            cout << "error" << endl;
            break;
        }
    }
    return 0;
}