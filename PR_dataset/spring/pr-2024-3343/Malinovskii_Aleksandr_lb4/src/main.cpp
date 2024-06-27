class CustomStack{
    public:

    CustomStack(){
        mHead=NULL;
        len=0;
    }
    bool empty(){
        return mHead==NULL;
    }
    void push(int val){
            ListNode* temp=new ListNode;
            temp->mData=val;
            temp->mNext=mHead;
            mHead=temp;
            len++;
    }
    void pop(){
        if(!empty()){
            mHead=mHead->mNext;
            len--;
        }
        else{
            cout<<"error";
            exit(0);
        }
    }
    int top(){
        if (!empty())
            return mHead->mData;
        else{
            cout<<"error";
            exit(0);
        }
    }
    size_t size(){
        return len;
    }
    void printStack(){
        ListNode* temp=new ListNode;
        temp=mHead;
        while (temp){
            cout<<temp->mData<<"\n";
            temp=temp->mNext;
        }
        
    }
    ~CustomStack(){
        while (!empty()){
            pop();
        }
        
    }
    private:
    size_t len;

    protected:
    ListNode* mHead;
};

int main(){
    CustomStack stack=CustomStack();
    string s;
    while(s!="cmd_exit"){
        getline(cin,s);
        if (s.find("cmd_push") != string::npos){
            int value = stoi(s.substr(s.find(" ") + 1));
            stack.push(value);
            cout<<"ok\n";
        }
        if (s=="cmd_pop"){
            cout<<stack.top()<<"\n";
            stack.pop();
        }
        if (s=="cmd_top"){
            cout<<stack.top()<<"\n";
        }
        if (s=="cmd_size"){
            cout<<stack.size()<<"\n";
        }
    }
    cout<<"bye\n";
}