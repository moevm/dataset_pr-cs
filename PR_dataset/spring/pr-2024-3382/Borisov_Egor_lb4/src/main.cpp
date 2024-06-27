class CustomStack{
public:
    CustomStack(){
        mData = new int;
        stack_size = 0;
    }
    
    void push(int val){
        mData[stack_size] = val;
        stack_size++;
    }
    
    void pop(){
        stack_size--;
    }
    
    int top(){
        return mData[stack_size - 1];
    }
    
    size_t size(){
        return stack_size;
    }
    
    bool empty(){
        return stack_size == 0;
    }
    
    int extend(int n){
        mData = new int[stack_size + n];
        stack_size += n;
        return *mData;
    }
    
    ~CustomStack(){
        if(!empty()){
            delete mData;
        }
    }
    
private:
    size_t stack_size;
    
protected:
    int *mData;
};


int main(){
    CustomStack Stack = CustomStack();
    
    string command;
    while(cin >> command){
        if(command == "cmd_push"){
            int n;
            cin >> n;
            Stack.push(n);
            cout << "ok" << endl;
        }else if(command == "cmd_pop"){
            if(Stack.empty()){
                cout << "error" << endl;
                break;
            }else{
                cout << Stack.top() << endl;
                Stack.pop();
            }
        }else if(command == "cmd_top"){
            if(Stack.empty()){
                cout << "error" << endl;
                break;
            }else{
                cout << Stack.top() << endl;
            }
        }else if(command == "cmd_size"){
            cout << Stack.size() << endl;
        }else if(command == "cmd_exit"){
            cout << "bye" << endl;
            break;
        }else{
            cout << "error" << endl;
        }
    }
    return 0;
}