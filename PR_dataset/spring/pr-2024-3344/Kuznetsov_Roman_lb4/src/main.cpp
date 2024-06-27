class CustomStack {
public:
    CustomStack() : mData (new int[20])
    , capacity (20)
    , len (0)
    {}
    
    ~CustomStack() {delete[] mData;}
    
    void push(int val)
    {
        if (len == capacity) extend(1); 
        mData[len++] = val;
    }
    
    void pop() {len--;}
    
    int top() {return mData[len - 1];}
    
    size_t size() {return len;}
    
    bool empty() {return len == 0;}
    
    void extend(size_t n)
    {
        capacity += n;
        int* temp = new int[capacity];
        memcpy(temp, mData, (capacity * sizeof(int)));
        delete[] mData;
        mData = temp;
    }
    
protected:
    int* mData;

private:
    size_t capacity;
    size_t len;
};

int main() {
    CustomStack stack;
    string option;
    
    while (true) {
        cin >> option;
        
        if (option == "cmd_push") {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << '\n';
        }
        
        else if (option == "cmd_pop") {
            if(stack.empty()) {
                cout << "error\n";
                break;
            }
            cout << stack.top() << '\n';
            stack.pop();
        }
        
        else if (option == "cmd_top") {
            if(stack.empty()) {
                cout << "error\n";
                break;
            }
            cout << stack.top() << '\n';
        }
        
        else if (option == "cmd_size") {
            cout << stack.size() << '\n';
        }
        
        else if (option == "cmd_exit") {
            cout << "bye";
            break;
        
        } else cout << "error";
    }
    return 0;
}
