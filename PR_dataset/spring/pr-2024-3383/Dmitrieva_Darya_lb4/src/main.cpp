class CustomStack{
private:
    int stack_limit = 15;
    int stack_size = 0;

protected:
    int* mData;

public:
    CustomStack(){
        mData = new int[15];
    }
    void extend(int n){
        int *arr = new int[stack_limit + n];
        for (int i=0; i<stack_size; i++){
            arr[i] = mData[i];
        }
        stack_limit +=n;
        delete[] mData;
        mData = arr;
    }
    void push(int el){
        if (stack_size == stack_limit){
            extend(15);
        }
        mData[stack_size++] = el;
    }
    void pop(){
        stack_size--;
    }
    int top(){
        return mData[stack_size-1];
    }
    size_t size(){
        return stack_size;
    }
    bool empty(){
        return (stack_size == 0);
    }
    ~CustomStack(){
        delete[] mData;
    }
};

int main(){
    CustomStack stack = CustomStack();
    char input[101];
    fgets(input, 101, stdin);
    input[strcspn(input, "\n")] = '\0';
    char sep[] = " ";
    char *token = strtok(input, sep);
    while (token!=NULL){
        if (atoi(token)){
            stack.push(atoi(token));
        }
        else{
            if (stack.size() < 2){
                std::cout<<"error"<<"\n";
                return 0;
            }
            int el_1 = stack.top();
            stack.pop();
            int el_2 = stack.top();
            stack.pop();
            if (strcmp(token, "-") == 0){
                stack.push(el_2 - el_1);
            }
            else if (strcmp(token, "+") == 0){
                stack.push(el_1 + el_2);
            }
            else if (strcmp(token, "*") == 0){
                stack.push(el_1 * el_2);
            }
            else if (strcmp(token, "/") == 0){
                if (el_1 != 0){
                    stack.push(el_2 / el_1);
                }
            }
        }
        token = strtok(NULL, sep);
    }
    if (stack.size() > 1){
        std::cout<<"error"<<"\n";
    }
    else{
        std::cout<<stack.top()<<"\n";
    } 
    return 0;
}