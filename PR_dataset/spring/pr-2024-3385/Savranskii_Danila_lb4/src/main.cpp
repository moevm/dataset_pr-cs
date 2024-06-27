class CustomStack {
    public:
        CustomStack() {
            mHead = NULL;
            stack_size = 0;
        }
        
        ~CustomStack() {
            while(!empty()) {
                pop();
            }
        }
        
        void push(int val) {
            ListNode* tmp = new ListNode;
            tmp->mNext = mHead;
            tmp->mData = val;
            mHead = tmp;
            stack_size++;
        }
        
        void pop() {
            if (empty()) {
                throw 1;
            }
            ListNode* tmp = mHead;
            mHead = mHead->mNext;
            delete tmp;
            stack_size--;
        }
        
        int top() {
            if (empty()) {
                throw 1;
            }
            return mHead->mData;
        }
        
        size_t size() {
            return stack_size;
        }
        
        bool empty() {
            return stack_size == 0;
        }
    protected:
        ListNode* mHead;
        size_t stack_size;
};

bool is_operation(const string& c) {
    return c == "+" || c == "-" || c == "*" || c == "/";
}
    
        
int main() {
    string input;
    CustomStack stack;
    int x, y;
    
    while (cin >> input) {
        if (is_operation(input)) {
            try {
                x = stack.top();
                stack.pop();
                y = stack.top();
                stack.pop();
            }
            catch(int error) {
                cout << "error";
                return 1;
            }
            switch(input.at(0)) {
                case '+':
                    stack.push(y + x);
                    break;
                case '-':
                    stack.push(y - x);
                    break;
                case '*':
                    stack.push(y * x);
                    break;
                case '/':
                    stack.push(y / x);
                    break;
            }
        }
        else {
            stack.push(stoi(input));
        }
    }
    
    if (stack.size() != 1) {
        cout << "error";
        return 1;
    }
    cout << stack.top();
}