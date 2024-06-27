class CustomStack {
public:
    CustomStack() : mData(nullptr), mSize(0), topIndex(-1) {}
    
    ~CustomStack() {
        delete[] mData;
    }
    
    void push(int val) {
        topIndex++;
        if ((!mData) || (topIndex == mSize)) {
            if (!extend(1)) {
                // Memory allocation failed
                return;
            }
        }
        mData[topIndex] = val;
    }   


    void pop(){
        topIndex--;
        mSize--;
    }
    
    size_t size(){
        return mSize;
    }
    
    bool empty(){
        if (topIndex == -1) return true;
        return false;
    }
    
    
    
    int top(){
        return mData[topIndex];
        
    }

private:
    int topIndex;
    size_t mSize;

    bool extend(int n) {
        int* new_arr = new (std::nothrow) int[mSize + n];
        if (new_arr == nullptr) {
            // Memory allocation failed
            return false;
        }

        if (mData) {
            for (size_t i = 0; i < mSize; i++) {
                new_arr[i] = mData[i];
            }
            delete[] mData;
        }
        mData = new_arr;
        mSize += n;
        return true;
}




protected:
    int* mData;
};

int main() {
    char str[256];
    int num;
    CustomStack stack;
    scanf("%s", str);
    while(strcmp(str, "cmd_exit") != 0){
        if(strcmp(str, "cmd_push") == 0){
            scanf("%d", &num);
            stack.push(num);
            if (!stack.empty()) {
                cout << "ok" << endl;
            } else {
                cout << "error" << endl;
                exit(0);
            }
        }
        
        else if(strcmp(str, "cmd_pop") == 0){
            if(stack.empty()){
                cout << "error" << endl;
                exit(0);
            }
            cout << stack.top() << endl;
            stack.pop();
        }
        else if(strcmp(str, "cmd_top") == 0) {
            if(stack.empty()){
                cout << "error" << endl;
                exit(0);
            }
            cout << stack.top() << endl;
        }
        
        else if(strcmp(str, "cmd_size") == 0) cout << stack.size() << endl;
        
        memset(str, 0, 256);
        scanf("%s", str);
    }
    cout << "bye" << endl;
    
    return 0;
}