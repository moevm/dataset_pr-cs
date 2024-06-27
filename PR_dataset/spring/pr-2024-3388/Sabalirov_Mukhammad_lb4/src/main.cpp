#define BUFFER_SIZE 150
#define ERROR_MESSAGE "error\n"
#define CMD_PUSH "cmd_push"
#define PUSH_ANSWER "ok\n"
#define CMD_POP "cmd_pop"
#define CMD_TOP "cmd_top"
#define CMD_SIZE "cmd_size"
#define CMD_EXIT "cmd_exit"
#define EXIT_MESSAGE "bye\n"


class CustomStack {

public:
    CustomStack() {
        mData = new int[0];
        mDataLen = 0;
        stackLen = 0;
    }

    ~CustomStack() {
        delete[] mData;
    }

    void extend(int n) {
        size_t new_size = mDataLen + n;
        int* newData = new int[new_size];
        memcpy(newData, mData, mDataLen*sizeof(int));
        delete[] mData;
        mDataLen = new_size;
        mData = newData;
        return;
    }

    void push(int val) {
        if (stackLen + 1 > mDataLen)
            extend(stackLen - mDataLen + 1);
        mData[stackLen++] = val;
        return;
    }

    void pop() {
        stackLen--;
        return;
    }

    int top() {
        return mData[stackLen - 1];
    }

    size_t size() {
        return stackLen;
    }

    bool empty() {
        return !((bool)stackLen);
    }

private:
    size_t mDataLen;
    size_t stackLen;

protected:
    int* mData;
};

void panic() {
    cout<<ERROR_MESSAGE;
    exit(0);
}

void inputAndProcces(){
    CustomStack stack;
    char buffer[BUFFER_SIZE];
    int pushVal;
    do {
        cin>>buffer;
        if (!strcmp(buffer, CMD_PUSH)){
            cin>>pushVal;
            stack.push(pushVal);
            cout<<PUSH_ANSWER;
        } else if (!strcmp(buffer, CMD_POP)) {
            if (stack.empty())
                panic();
            cout<<stack.top()<<'\n';
            stack.pop();
        } else if (!strcmp(buffer, CMD_TOP)) {
            if (stack.empty())
                panic();
            cout<<stack.top()<<'\n';
        } else if (!strcmp(buffer, CMD_SIZE)) {
            cout<<stack.size()<<'\n';
        }
    } while (strcmp(buffer, CMD_EXIT));
    cout<<EXIT_MESSAGE;
    return;
}

int main() {
    inputAndProcces();
    return 0;
}
