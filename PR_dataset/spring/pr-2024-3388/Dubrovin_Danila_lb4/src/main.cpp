#define ARRAY_SIZE 100
#define BUFFER_SIZE 20
#define ERROR_MESSAGE "error"

enum {
    ADD = 1,
    SUBTRACT = 2,
    MULTIPLY = 3,
    DIVIDE = 4
};

class Exception{
public:
    static void returnError(){
        cout << ERROR_MESSAGE;
        exit(0);
    }
};

class CustomStack {
public:
CustomStack() {
    mHead = nullptr;
}

~CustomStack() {
    while(mHead){
        pop();
    }
}

void push(int value) {
    ListNode* node = new ListNode();
    node -> mData = value;
    node -> mNext = mHead;
    mHead = node;
}

void pop(){
    if(empty()){
        Exception::returnError();
    }
    ListNode* top = mHead;
    mHead = top -> mNext;
    delete top; 
}

int top(){
    if(empty()){
        Exception::returnError();
    }
    return mHead -> mData;
}

size_t size(){
    size_t counter = 0;
    ListNode* current = mHead; 
    while(current){
        counter++;
        current = current -> mNext;
    }
    return counter;
}

bool empty(){
    return mHead ? false : true;
}

protected:
ListNode* mHead;
};

int getOperand(char* str){
    if(!strcmp(str, "+")) return ADD;
    if(!strcmp(str, "-")) return SUBTRACT;
    if(!strcmp(str, "*")) return MULTIPLY;
    if(!strcmp(str, "/")) return DIVIDE;
    return 0;
}

int calculate(){
    CustomStack* stack = new CustomStack();
    int counter, firstNumber, secondNumber;
    counter = 0;
    int operand;
    char buffer[BUFFER_SIZE];
    do{
        cin >> buffer;

        if(!(operand = getOperand(buffer))){
            stack -> push(atoi(buffer));
            counter++;
            continue;
        }

        if(stack->size() < 2)
            Exception::returnError();
        secondNumber = stack -> top();
        stack -> pop();
        firstNumber = stack -> top();
        stack -> pop();

        switch(operand){
            case ADD:
                stack -> push(firstNumber + secondNumber);
                break;
            case SUBTRACT:
                stack -> push(firstNumber - secondNumber);
                break;
            case MULTIPLY:
                stack -> push(firstNumber * secondNumber);
                break;
            case DIVIDE:
                if(secondNumber == 0)
                    Exception::returnError();
                stack -> push(firstNumber / secondNumber);
                break;
            }
        counter++;
    }while(counter < ARRAY_SIZE && cin.get() != '\n');

    if(stack -> size() > 1)
        Exception::returnError();

    return stack -> top();
}

int main(){
    cout << calculate();
    return 0;
}
