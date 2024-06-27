class CustomStack
{
public:
    CustomStack() {
        this->mHead = nullptr; 
        this->mSize = 0;
    }

    void push(int value) {
        ListNode *newNode = new ListNode; 
        newNode->mData = value;
        newNode->mNext = this->mHead; 
        this->mHead = newNode;
        this->mSize++;
    }

    void pop() {
        if(this->empty()) {
            throw range_error("Stack is empty"); 
            return;
        }
        this->mHead = this->mHead->mNext;
        this->mSize--;
    }

    int top() {
        if(this->empty()) {
            throw range_error("Stack is empty"); 
            return -1;
        }
        return this->mHead->mData;
    }

    size_t size() {
        return this->mSize;
    }

    bool empty() {
        return this->mHead == nullptr;
    }

protected:
    ListNode *mHead;
    int mSize;
};

vector<string> split(string src, string delimiter) {
    size_t pos; 
    string token; 
    auto result = vector<string>();

    while((pos = src.find(delimiter)) != string::npos) {
        token = src.substr(0, pos); 
        result.push_back(token);
        src.erase(0, pos + 1);
    }
    result.push_back(src);

    return result;
}

int calcRPNString(string expression) {
    CustomStack *stack = new CustomStack();
    auto tokens = split(expression, " ");

    for(auto token : tokens) {
        try {
            stack->push(stoi(token));
            continue;
        } catch(invalid_argument &e) {}

        char operation = token[0];
        int a, b;
        try {
            b = stack->top();
            stack->pop();
            a = stack->top();
            stack->pop();
        } catch(range_error &e) {
            cout << "error" << endl;
            exit(0);
        }

        switch(operation) {
            case '+': 
                stack->push(a + b); 
                break;
            case '-': 
                stack->push(a - b); 
                break;
            case '*': 
                stack->push(a * b); 
                break;
            case '/': 
                stack->push(a / b); 
                break;
        }
    }

    if(stack->size() > 1) {
        cout << "error" << endl;
        exit(0);
    }
    return stack->top();
}

int main()
{   
    string expression; 
    getline(cin, expression);

    int result = calcRPNString(expression); 
    
    cout << result << endl;

    return 0;
}