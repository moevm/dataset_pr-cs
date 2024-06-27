class CustomStack {

public:
    CustomStack(){
        mData = new int [100];
        len = 0;
    }

    void push(int val){
        mData[len++] = val;
    }

    void pop(){
        len--;
    }

    int top(){
        return mData[len - 1];
    }

    size_t size(){
        return len;
    }

    bool empty(){
        return len == 0;
    }

    void extend(int n){
        len += n;
    }

protected:
    int* mData;
    size_t len;
};

int main() {
    char str[200];
    int num;
    CustomStack stack = CustomStack();
    scanf("%s %d", str, &num);
    while (strcmp(str, "cmd_exit") != 0){
        if (strcmp(str, "cmd_push") == 0){
            stack.push(num);
            cout<<"ok\n";
        }
        else if (strcmp(str, "cmd_pop") == 0){
            if (stack.size() > 0){
                num = stack.top();
                stack.pop();
                cout<<num<<endl;
            }
            else{
                cout<<"error\n";
                return(0);
            }
        }
        else if (strcmp(str, "cmd_top") == 0){
            if (stack.size() > 0) {
                num = stack.top();
                cout << num << endl;
            }
            else{
                cout<<"error\n";
                return(0);
            }
        }
        else if (strcmp(str, "cmd_size") == 0){
            num = stack.size();
            cout<<num<<endl;
        }
        scanf("%s %d", str, &num);
    }
    cout<<"bye\n";
    return 0;
}