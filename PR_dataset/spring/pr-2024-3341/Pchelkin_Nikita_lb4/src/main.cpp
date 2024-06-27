#define STACK_CONTAINER 20
#define POSITIVE_STATUS "ok"
#define ERROR_STATUS "error"
#define EXIT_STATUS "bye"


class CustomStack {
public:
    CustomStack() {
        mData = new int[STACK_CONTAINER];
        stack_size = STACK_CONTAINER;
        current_size = 0;
    }
    void push(int val) {
        if (current_size + 1 > stack_size) {
            throw logic_error("Stack overflow!");
        }
        mData[current_size] = val;
        current_size++;
    }
    void pop() {
        if (current_size == 0)
            throw logic_error("Trying to delete element from empty stack!");
        current_size--;
    }
    int top() {
        if (current_size == 0)
            throw logic_error("Stack is empty!");
        return mData[current_size-1];
    }
    size_t size() {
        return current_size;
    }
    bool empty() {
        return current_size == 0;
    }
    void extend(int n) {
        mData = (int*)realloc(mData, stack_size + n);
        stack_size += n;
    }
private:
    size_t stack_size;
    size_t current_size;
protected:
    int* mData;
};

void error() {
    cout << ERROR_STATUS;
    exit(0);
}

void cmd_push(CustomStack& stack, int n) {
    try {
        stack.push(n);
        cout << POSITIVE_STATUS << endl;
    }
    catch (const logic_error &e) {
        error();
    }
}

void cmd_pop(CustomStack& stack) {
    try {
        cout << stack.top() << endl;
        stack.pop();
    }
    catch (const logic_error& e) {
        error();
    }
}

void cmd_top(CustomStack& stack){
    try {
        cout << stack.top() << endl;
    }
    catch (const logic_error& e) {
        error();
    }
}

void cmd_size(CustomStack& stack) {
    cout << stack.size() << endl;
}

void cmd_exit() {
    cout << EXIT_STATUS;
    exit(0);
}

void cmdExecution(CustomStack& stack) {
    string newCommand;
    while(true) {
        cin >> newCommand;

        if (newCommand == "cmd_push")
        {
            int data;
            cin >> data;
            cmd_push(stack, data);
        }
        if (newCommand == "cmd_pop")
            cmd_pop(stack);
        if (newCommand == "cmd_top")
            cmd_top(stack);
        if (newCommand == "cmd_size")
            cmd_size(stack);
        if (newCommand == "cmd_exit")
            cmd_exit();
    }
}

int main() {
    CustomStack stack;
    cmdExecution(stack);
    return 0;
}