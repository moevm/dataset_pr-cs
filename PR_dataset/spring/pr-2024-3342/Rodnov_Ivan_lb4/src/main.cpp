class CustomStack {
public:
    CustomStack() : mSize(0), mData(nullptr), mCapacity(0){}
    CustomStack(const CustomStack& stack): mSize(stack.mSize), mCapacity(stack.mCapacity), mData(nullptr){
        if(stack.mData){
            mData = new int[mCapacity];
            if (!mData) {
                cerr << "Memory allocation failed" << endl;
                exit(0);
            }
            for(size_t i = 0; i < mSize; ++i){
                mData[i] = stack.mData[i];
            }   
        }
    }

    ~CustomStack(){
        delete[] mData;
    }

    void push(int val){
        if(mSize == mCapacity){
            extend(1);
        }
        mData[mSize++] = val;
    }

    void pop(){
        mSize--;
    }

    int top(){
        int top_el = mData[mSize - 1];
        return top_el;
    }

    size_t size(){
        return mSize;
    }

    bool empty(){
        return mSize == 0;
    }

    void extend(int n){
        mCapacity = mCapacity + n;
        int* nData = new int[mCapacity];
        if (!nData) {
            cerr << "Memory allocation failed" << endl;
            exit(0);
        }
        for(size_t i = 0; i < mSize; ++i){
            nData[i] = mData[i];
        }
        delete[] mData;
        mData = nData;
    }

private:
    int mSize;
    int mCapacity;

protected:
    int* mData;
};

int main() {
    CustomStack myStack;
    string cmd;
    int n;

    while(cin >> cmd){
        if(cmd == "cmd_push"){
            cin >> n;
            myStack.push(n);
            cout << "ok" << endl;
        }
        else if(cmd == "cmd_pop"){
            if(myStack.empty()){
                cout << "error" << endl;
                return 0;
            }
            else{
                cout << myStack.top() << endl;
                myStack.pop();
            }
        }
        else if(cmd == "cmd_top"){
            if(myStack.empty()){
                cout << "error" << endl;
                return 0;
            }
            else{
                cout << myStack.top() << endl;
            }
        }
        else if(cmd == "cmd_size"){
            cout << myStack.size() << endl;
        }
        else if(cmd == "cmd_exit"){
            cout << "bye" << endl;
            break;
        }
    }   
    return 0;
}
