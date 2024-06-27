class CustomStack {
public:
    CustomStack(){
        mData = new int[10];
        len = 0;
        capacity = 10;
    }

    ~CustomStack() {
        delete[] mData;
    }

    void push(int val){
        if(len == capacity){
            extend(1);
        }
        mData[len++] = val;
    }

    void pop(){
        len--;
    }

    int top(){
        return mData[len-1];
    }

    size_t size(){
        return len;
    }

    bool empty(){
        return len == 0;
    }
    void extend(int n){
        capacity += n;
        int* temp = new int[capacity];
        memcpy(temp, mData, (capacity * sizeof(int)));
        delete[] mData;
        mData = temp;
    }
protected:
    int* mData;

private:
    size_t len;
    size_t capacity;
};

int main(){
    CustomStack stack;
    string inp_cmd;

    while (true) {
        cin >> inp_cmd;

        if (inp_cmd == "cmd_push") {
            int n;
            cin >> n;
            stack.push(n);
            cout << "ok" << endl;

        } else if (inp_cmd == "cmd_pop") {

            if (stack.empty()) {
                cout << "error\n";
                break;
            }

            cout << stack.top() << "\n";
            stack.pop();

        } else if (inp_cmd == "cmd_top") {

            if (stack.empty()) {
                cout << "error\n";
                break;
            }

            cout << stack.top() << "\n";

        } else if (inp_cmd == "cmd_size") {

            cout << stack.size() << "\n";

        } else if (inp_cmd == "cmd_exit") {

            cout << "bye\n";
            break;

        } else{ 

            cout<<"Some error";
        }
    }
    return 0;
}