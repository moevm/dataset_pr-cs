class CustomStack{
public:
    CustomStack(){
        mSize = 0;
        mCapacity = 1;
        mData = (int*)malloc(mCapacity * sizeof(int));
    }
    ~CustomStack(){
        free(mData);
    }
    void push(int val){
        if (mSize == mCapacity){
            extend(1);
        }
        mData[mSize++] = val;
    }
    void extend(int n){
        mCapacity += n;
        mData = (int*)realloc(mData, mCapacity * sizeof(int));
    }
    void pop(){
        if (empty()){
            std::cout << "error" << std::endl;
        }
        mSize--;
    }
    int top(){
        if (empty())
            std::cout << "error" << std::endl;
        return mData[mSize - 1];
    }
    size_t size(){
        return mSize;
    }
    bool empty(){
        return mSize == 0;
    }
private:
    size_t mSize; // Количество элементов в стеке
    size_t mCapacity; // Максимально количество элементов в стеке
    
protected:
    int* mData; // Массив данных из чисел
};

int evaluate(int operand1, int operand2, char op){
    switch (op){
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: 
            std::cout << "error" << std::endl;
            exit(1);
    }
}

bool is_number(const std::string& s) {
    if (s.size() == 1 && s[0] == '-') {
        return false;
    }
    size_t start = (s[0] == '-') ? 1 : 0;
    for (size_t i = start; i < s.size(); ++i) {
        if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

int main(){
    CustomStack stack;
    std::string input;
    std::getline(std::cin, input); // Считывает строку из входного потока
    std::string token; // Строка для числа или оператора
    std::istringstream input_stream(input);
    while(input_stream >> token){
        if (is_number(token)){
            stack.push(std::stoi(token));
        } else {
            if (stack.size() < 2){
                std::cout << "error" << std::endl;
                return 1;
            }
            int operand_2 = stack.top();
            stack.pop();
            int operand_1 = stack.top();
            stack.pop();
            int result = evaluate(operand_1, operand_2, token[0]);
            stack.push(result);
        }
    }
    if (stack.size() == 1){
        std::cout << stack.top() << std::endl;
    } else {
        std::cout << "error" << std::endl;
        return 1;
    }
    return 0;
}