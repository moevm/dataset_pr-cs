#define MAX_SEQUENCE_LENGTH 100
#define END_STRING '\0'

class CustomStack
{
    public:
        CustomStack()
        {
            mHead = NULL;
        }
        
        bool empty()
        {
            return mHead == NULL ? true : false;
        }
        
        void push(long long int val)
        {
            ListNode* tempNode = new ListNode;
            tempNode->mNext = mHead;
            tempNode->mData = val;
            mHead = tempNode;
        }
        
        void pop()
        {
            ListNode* tempNode = mHead;
            mHead = mHead->mNext;
            delete tempNode;
        }
        
        long long int top()
        {
            return mHead->mData;
        }
        
        size_t size()
        {
            long long int sizeStack = 0;
            ListNode* tempNode = mHead;
            while (tempNode)
            {
                sizeStack++;
                tempNode = tempNode->mNext;
            }
            return sizeStack;
        }
        
        ~CustomStack()
        {
            ListNode* head = mHead;
            ListNode* tempNode;
            while (head)
            {
                tempNode = head->mNext;
                delete head;
                head = tempNode;
            }
        };

    protected:
    ListNode* mHead;
};

bool isArithmeticOperation(char currChar)
{
    return (currChar == '+' || currChar == '-' || currChar == '*' || currChar == '/');
}

void performArithmeticOperation(CustomStack &stack, bool &noError, char currChar)
{
    long long int secondNumber = stack.top();
    stack.pop();
    long long int firstNumber = stack.top();
    stack.pop();
    switch(currChar)
    {
        case '+':
            stack.push(firstNumber + secondNumber);
            break;
        case '-':
            stack.push(firstNumber - secondNumber);
            break;
        case '*':
            stack.push(firstNumber * secondNumber);
            break;
        case '/':
            if (secondNumber == 0) noError = false;
            else stack.push(firstNumber / secondNumber);
            break;
    }
}

void processInputSequence(CustomStack &stack, char* inputSequence, bool &noError)
{
    char *NumberOrArithmeticOperation = strtok(inputSequence, " ");
    while (NumberOrArithmeticOperation != NULL)
    {
        if (strlen(NumberOrArithmeticOperation) == 1 && isArithmeticOperation(NumberOrArithmeticOperation[0]))
        {
            if(stack.size() >= 2)
                performArithmeticOperation(stack, noError, NumberOrArithmeticOperation[0]);
            else noError = false;
        }
        else stack.push(stoi(NumberOrArithmeticOperation));
        NumberOrArithmeticOperation = strtok(NULL, " ");
    }
}

int main()
{
    CustomStack stack = CustomStack();
    bool noError = true;
    char inputSequence[MAX_SEQUENCE_LENGTH + 1];
    
    fgets(inputSequence, MAX_SEQUENCE_LENGTH, stdin);
    inputSequence[strlen(inputSequence) - 1] = END_STRING;
    
    processInputSequence(stack, inputSequence, noError);
    if (stack.size() != 1) noError = false;
    noError ? cout << stack.top() : cout << "error";
    return 0;
}
