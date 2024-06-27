#define BUFFER_SIZE 150
#define ERROR_MESSAGE "error\n"
#define PLUS 1
#define MINUS 2
#define MULTI 3
#define DIVISION 4
#define NOT_OPERATION 0

class CustomStack {

public:
    CustomStack() {
        mHead = new ListNode;
        mHead->mNext = NULL;
        stackLen = 0;
    }

    ~CustomStack() {
        delete[] mHead;
    }

    void push(int val) {
        if (!stackLen){
            mHead->mData = val;
            stackLen++;
            return;
        }

        ListNode* tmp = mHead;
        for (int i = 0; i < stackLen - 1; i++){
            tmp = tmp->mNext;
        }

        tmp->mNext = new ListNode; 
        tmp->mNext->mData = val;
        tmp->mNext->mNext = NULL;
        stackLen++;

        return;
    }

    void pop() {
        if (!stackLen){
            panic();
        }
        stackLen--;
        return;
    }

    int top() {
        if (!stackLen){
            panic();
        }
        ListNode* tmp = mHead;
        for (int i = 0; i < stackLen - 1; i++){
            tmp = tmp->mNext;
        }
        return tmp->mData;
    }

    size_t size() {
        return stackLen;
    }

    bool empty() {
        return !((bool)stackLen);
    }

    void panic() {
        cout << ERROR_MESSAGE;
        exit(0);
    }

private:
    size_t stackLen;

protected:
    ListNode* mHead;
};

int getOperand(char *str) {
    if (strlen(str) != 1) return 0;
    char letter = str[0];
    switch (letter) {
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULTI;
        case '/':
            return DIVISION;
        default:
            return NOT_OPERATION;
    }
}

void inputAndProcces(){
    auto myStack = new CustomStack;

    char buff[BUFFER_SIZE];
    fgets(buff, BUFFER_SIZE, stdin);
    buff[strlen(buff) - 1] = '\0';

    char* p = strtok(buff, " ");
    while (p != nullptr && strlen(p) > 0) {
        if (!getOperand(p)) myStack->push(atoi(p));
        else {
            if (myStack->size() < 2) {
                myStack->panic();
            }
            int secondValue = myStack->top();
            myStack->pop();
            int firstValue = myStack->top();
            myStack->pop();

            switch (getOperand(p)) {
                case PLUS:
                    myStack->push(firstValue + secondValue);
                    break;
                case MINUS:
                    myStack->push(firstValue - secondValue);
                    break;
                case MULTI:
                    myStack->push(firstValue * secondValue);
                    break;
                case DIVISION:
                    myStack->push(firstValue / secondValue);
                    break;
            }
        }
        p = strtok(NULL, " ");
    }

    if (myStack->size() > 1)
        myStack->panic();
    else
        cout << myStack->top();
}

int main() {
    inputAndProcces();
    return 0;
}