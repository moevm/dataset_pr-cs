class CustomStack{
    public:
        CustomStack(){
            mHead = nullptr;
            size_of_stack = 0;
        }
        
        ~CustomStack(){
            if (!empty()){
                delete mHead;
            }
        }
    
        bool empty(){
            return size_of_stack == 0;
        }
    
        size_t size(){
            return size_of_stack;
        }
    
        int top(){
            if (!empty()){
                return mHead->mData;
            } else{
                cout << "error" << endl;
                exit(0);
            }
        }
    
        void push(int value){
            ListNode* elem = new ListNode;
            elem->mData = value;
            elem->mNext = nullptr;
            if (empty()) {
                mHead = elem;
                size_of_stack++;
            } else{
                elem->mNext = mHead;
                mHead = elem;
                size_of_stack++;
            }
        }
    
        void pop(){
            if (!empty()){
                ListNode* next_head = mHead->mNext;
                delete mHead;
                mHead = next_head;
                size_of_stack--;
            } else{
                cout << "error" << endl;
                exit(0);
            }
        }

    private:
        int size_of_stack;

    protected:
        ListNode* mHead;
};

int operation(char oper, int elem1, int elem2){
    if (oper == '+'){
        return elem1 + elem2;
    } else if (oper == '-'){
        return elem2 - elem1;
    } else if (oper == '*'){
        return elem1 * elem2;
    } else if (oper == '/'){
        return elem2 / elem1;
    }
}


int main(){
    CustomStack Stack = CustomStack();
    string elem;
    int elem1, elem2, push_elem;
    while (cin >> elem){
        if (elem == "-" || elem == "+" || elem == "*" || elem == "/"){
            elem1 = Stack.top();
            Stack.pop();
            elem2 = Stack.top();
            Stack.pop();
            Stack.push(operation(elem[0], elem1, elem2));
        } else{
            push_elem = 0;
            int flag_number = 1;
            int flag_minus = 0;
            for (int i = 0; i < elem.size(); i++){
                if (isdigit(elem[i])){
                    push_elem = push_elem * 10 + (elem[i] - '0');
                } else if (i == 0 && elem[i] == '-'){
                    flag_minus = 1;
                } else{
                    flag_number = 0;
                    break;
                }
            }
            if (flag_minus){
                push_elem *= -1;
            }
            if (flag_number){
                Stack.push(push_elem);
            } else{
                cout << "error" << endl;
                exit(0);
            }
        }
    }
    int result = Stack.top();
    Stack.pop();
    if (!Stack.empty()){
        cout << "error" << endl;
        exit(0);
    }
    cout << result << endl;
    return 0;
}