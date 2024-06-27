#define BASE_SIZE 10
#define ERROR_TEXT "error"

class CustomStack{
public:
    CustomStack(){
        mData = new int[BASE_SIZE];
        capacity = BASE_SIZE;
        max_size = 0;
    }
    ~CustomStack(){
        delete[] mData;
    }
    void push(int val){
        if(max_size == capacity ){
            extend(BASE_SIZE);
        }
        mData[max_size++] = val;
    }
    void pop(){
        checkEmpty();
        --max_size;
    }
    int top(){
        checkEmpty();
        return mData[max_size-1];
    }
    size_t size(){
        return max_size;
    }
    bool empty(){
        return max_size == 0;
    }
    void extend(int n){
        int* new_data = new int[capacity+n];
        for(int i = 0; i < max_size; ++i){
            new_data[i] = mData[i];
        }
        delete[] mData;
        mData = new_data;
        capacity += n;
    }
    void checkEmpty(){
        if(max_size == 0){
                cout << ERROR_TEXT << endl;
                exit(0);
            }
    }
private:
    int capacity;
    int max_size;
protected:
    int* mData;

};

void checkStackSize(CustomStack &stack){
    if (stack.empty()) {
                cout << ERROR_TEXT << endl;
                exit(0);
            }
}

int processStack(CustomStack &stack){
    string cmd;
    while(cin >> cmd){
        if(cmd == "cmd_push"){
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;
        }
        else if (cmd == "cmd_pop") {
            checkStackSize(stack);
            cout << stack.top() << endl;
            stack.pop();
        } else if (cmd == "cmd_top") {
            checkStackSize(stack);
            cout << stack.top() << "\n";
        } else if (cmd == "cmd_size") {
            cout << stack.size() << endl;
        } else if (cmd == "cmd_exit") {
            cout << "bye"<< endl;
            return 0;
        }
    }
}

int main() {
    CustomStack stack;
    processStack(stack);
    return 0;
}
