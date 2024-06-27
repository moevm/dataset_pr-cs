class CustomStack {

public:
    CustomStack(): mHead{new ListNode{nullptr, 0}} {}

    CustomStack(ListNode * head): mHead{head} {}

    ~CustomStack() {
        while(!empty()){
            pop();
        }
    }

    void operation(char oper){
        if(size() < 2){
            cout << "error" << endl;
            exit(0);
        }
        int right = top();
        pop();
        int left = top();
        pop();
        if(oper == '+'){ push(left + right); }
        else if(oper == '-'){ push(left - right); }
        else if(oper == '/'){ push(left / right); }
        else if(oper == '*'){ push(left * right); }
    }

    void push(int val){
        if(empty()){
            mHead = new ListNode{nullptr, val};
            return;
        }
        ListNode * temp = mHead;
        while(temp->mNext != nullptr){
            temp = temp->mNext;
        }
        ListNode * node = new ListNode{nullptr, val};
        temp->mNext = node;
        return;
    }

    void pop(){
        if(empty()){
            cout << "error" << endl;
            exit(0);
        }
        ListNode * temp = mHead;
        if(temp->mNext == nullptr){
            delete temp->mNext;
            mHead = nullptr;
            return;
        }
        while(temp->mNext->mNext != nullptr){
            temp = temp->mNext;
        }
        delete temp->mNext->mNext;
        temp->mNext = nullptr;
        return;
    }

    int top(){
        if(empty()){
            cout << "error" << endl;
            exit(0);
        }
        ListNode * temp = mHead;
        while(temp->mNext != nullptr){
            temp = temp->mNext;
        }
        return temp->mData;
    }

    size_t size(){
        if(empty()){
            return 0;
        }
        size_t len = 1;
        ListNode * temp = mHead;
        while(temp->mNext != nullptr){
            len++;
            temp = temp->mNext;
        }
        return len;
    }

    bool empty(){
        return mHead == nullptr;
    }

private:

protected:

    ListNode* mHead;
};

int main() {

    char s[100];
    cin.getline(s, 100);
    char * p;
    char ** ls = new char* [100];
    p = strtok(s, " ");
    int c = 0;
    while (p != NULL) {
        ls[c++] = p;
        p = strtok(NULL, " ");
    }
    ListNode* head = new ListNode{nullptr, atoi(ls[0])};
    CustomStack stack(head);
    for(size_t i = 1; i < c; i++){
        if(strlen(ls[i]) == 1 & (*ls[i] == '+' | *ls[i] == '-' | *ls[i] == '/' | *ls[i] == '*')){
            stack.operation(*ls[i]);
        }else{
            stack.push(atoi(ls[i]));
        }
    }
    if((stack.size() != 1)){
        cout << "error" << endl;
    }else{
        cout << stack.top() << endl;
    }
    return 0;
    }
