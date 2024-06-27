class CustomStack{

public:

    CustomStack():mHead(nullptr){}
    
    ~CustomStack(){
        delete mHead;
    }
    
    void push(int val){
        stack_size++;
        ListNode *newVal = new ListNode;
        newVal->mData = val;
        newVal->mNext = mHead;
        mHead = newVal;
    }
    
    void pop(){
        if(stack_size>0){
            --stack_size;
            ListNode *newHead;
            newHead = mHead->mNext;
            delete mHead;
            mHead = newHead;
        }else{
            cout << "error" << endl;
            exit(1);
        }
    }
    
    int top(){
        if(stack_size>0){
            return mHead->mData;
        }else{
            cout << "error" << endl;
            exit(1);
        }
    }
    
    size_t size(){
        return stack_size;
    }
    
    bool empty(){
        return stack_size == 0;
    }
    
private:
    int stack_size = 0;
    
protected:
    ListNode* mHead;
};

int main(){
    CustomStack stack = CustomStack();
    string cmd;
    while (cin >> cmd)
        if (cmd == "cmd_push"){
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        }
        else if (cmd == "cmd_pop")
            if(stack.empty()){
                cout<<"error";
                break;
            }else{
                cout<<stack.top()<<endl;
                stack.pop();
            }
        else if (cmd == "cmd_top")
            if(stack.empty()){
                cout<<"error";
                break;
            }else
                cout<<stack.top()<<endl;
                
        else if (cmd == "cmd_size")
            cout<<stack.size()<<endl;
            
        else if (cmd == "cmd_exit"){
            cout << "bye";
            break;
        }
    return 0;
}
