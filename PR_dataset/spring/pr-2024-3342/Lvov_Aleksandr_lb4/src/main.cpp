#define BUF_SIZE 1024

void printError() {
    printf("error");
    exit(0);
}

class CustomStack {
public:
    CustomStack(){
        mHead = nullptr;
        mSize = 0;
    }

    void push(int value) {
        auto lNode = new ListNode;
        lNode -> mData = value;
        lNode -> mNext = mHead;
        mHead = lNode;
        mSize++;
    }

    void pop() {
        if ( !(empty()) ) {
            ListNode *tmp = mHead -> mNext;
            delete mHead;
            mHead = tmp;
        } else {
           printError();
        }
        mSize--;
    }

    int top() const {
        if (empty()) {
            printError();
        } else {
            return mHead -> mData;
        }
    }

    size_t size() const {
        return mSize;
    }

    bool empty() const {
        return mSize == 0;
    }

    ~CustomStack() {
        ListNode *tmp = mHead;
        while (tmp != nullptr) {
            tmp = tmp -> mNext;
            delete mHead;
            mHead = tmp;
        }
    }
private:
    size_t mSize;
protected:
    ListNode* mHead{};
};



void compute(CustomStack * s, const char * op) {
    int num2 = s -> top();
    s -> pop();
    int num1 = s -> top();
    s -> pop();
    
    int res;
    switch (*op) {
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            res = num1 / num2;
            break;
        default:
            return;
    }
    s -> push(res);
}

int main() {
    auto s = new CustomStack;
    auto str = new char[BUF_SIZE];
    
    fgets(str, BUF_SIZE, stdin);
    
    char * p;
    p = strtok(str, " \n");
    
    while (p != nullptr) {
        if (strlen(p) == 1) {
            if (!isdigit(*p) && (*p != '\n')) {
                compute(s, p);
            } else {
                s -> push(stoi(p));
            }
        } else {
            if (isdigit(*p) || *p == '-') {
                s -> push(stoi(p));
            }
        }
        p = strtok(nullptr, " \n");
    }
    
    if (s -> size() != 1) {
        printError();
    } else {
        printf("%d", s->top());
    }

    delete s;
    delete[] str;
}

