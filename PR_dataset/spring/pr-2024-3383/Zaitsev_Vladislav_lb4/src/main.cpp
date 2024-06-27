class CustomStack {
public:
    CustomStack(){
        mHead = new ListNode;
        mHead = nullptr;
        mSize = 0;
    }
    ~CustomStack(){
        delete mHead;
    }
    void push(int val){
        ListNode *new_node = new ListNode;
        new_node->mNext = mHead;
        new_node->mData = val;
        mHead = new_node;
        mSize++;
    }
    void pop(){
        if (mSize != 0){
            ListNode *new_node;
            new_node = mHead->mNext;
            delete mHead;
            mHead = new_node;
            mSize--;
        }
    }
    int top(){
        return mHead->mData;
    }
    size_t size(){
        return mSize;
    }
    bool empty(){
        if (mSize == 0){
            return true;
        }
        else{
            return false;
        }
    }
private:
    size_t mSize;
protected:
    ListNode* mHead;
};

int main() {
    CustomStack Stack = CustomStack();
    string comand;
    while(cin>>comand){
        if (comand == "cmd_push"){
            int value;
            cin>>value;
            Stack.push(value);
            cout<<"ok"<<endl;
        }
        else if(comand == "cmd_pop"){
            if (Stack.empty()){
                cout<<"error"<<endl;
                break;
            }
            else{
                cout<<Stack.top()<<endl;
                Stack.pop();
            };
        }
        else if (comand == "cmd_top"){
            if (Stack.empty()){
                cout<<"error"<<endl;
                break;
            }
            else{
                cout<<Stack.top()<<endl;
            };
        }
        else if(comand == "cmd_size"){
            cout<<Stack.size()<<endl;
        }
        else if(comand == "cmd_exit"){
            cout<<"bye"<<endl;
            break;
        };
    }
    return 0;
};
