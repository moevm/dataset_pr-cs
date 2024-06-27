class CustomStack {
public:
    CustomStack(){
        mData = new int[10];
        len = 0;
        memory = 10;
    }

    ~CustomStack() {
        delete[] mData;
    }

    void push(int val){
        if(len == memory){
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
        memory += n;
        int *tmp_arr = new int[memory];
        for (int i = 0; i < len; ++i) {
            tmp_arr[i] = mData[i];
        }
        delete[] mData;
        mData = tmp_arr;
    }
protected:
    int* mData;

private:
    size_t len;
    size_t memory;
};

int main() {
    CustomStack stack;

    char input[10];
    int num1, num2;

    while (cin >> input) {
        if (isdigit(input[0]) || isdigit(input[1])) {
            int num = strtol(input, NULL, 10);
            stack.push(num);
        } else {
            if (stack.size() < 2) {
                cout << "error" << endl;
                return 1;
            }

        num2 = stack.top();
        stack.pop();
        num1 = stack.top();
        stack.pop();
        switch (input[0]) {
            case '+':
                stack.push(num1 + num2);
                break;
            case '-':
                stack.push(num1 - num2);
                break;
            case '*':
                stack.push(num1 * num2);
                break;
            case '/':
                if (num2 != 0) {
                    stack.push(num1 / num2);
                } else {
                    cout << "error" << endl;
                    return 1;
                }
                break;
            default:
                cout << "error" << endl;
                return 1;
            }
        }
    }
    

    if (stack.size() != 1) {
        cout << "error" << endl;
       return 1;
    }

    cout << stack.top() << endl;

    return 0;
}
