void printError(){
    cout << "error";
    exit(0);
}

class CustomStack {
public:
    CustomStack(){
        mData = new int[100];
        if (mData == NULL){
            exit(0);
        }
        mSize = 0;
    }

    void push(int val){
        mData[mSize++] = val;
    }

    void pop(){
        if (mSize == 0){
            printError();
        }
        mSize--;
    }

    int top(){
        if (mSize == 0){
            printError();
        }
        return mData[mSize-1];
    }

    int get_elem(){
        int elem = top();
        pop();
        return elem;
    }

    size_t size(){
        return mSize;
    }

    bool empty(){
        return mSize == 0;
    }

    void extend(int n){
        mSize += n;
            if (mSize > 0){
            int* newData = new int [mSize];
            if (newData == NULL){
                exit(0);
            }
            for (size_t i = 0; i < mSize; ++i)
                newData[i] = mData[i];

            delete [] mData;
            mData = newData;
        } else{
            exit(0);
        }
    }

    ~CustomStack(){
        delete [] mData;
        mSize = 0;
    }

protected:
    int* mData;
private:
    size_t mSize;
};


bool isNumber(string& str) {
    if (str.empty()) {
        return false;
    }

    size_t i = 0;
    if (str[i] == '-') {
        ++i;
    }

    bool hasDigit = false;

    for (; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            hasDigit = true;
        } else {
            return false;
        }
    }

    return hasDigit;
}


int main() {
    CustomStack stack;
    string s;
    getline(cin, s);
    stringstream ss(s);
    string text;

    int x, y;


    while (getline(ss, text, ' ')) {
        if (isNumber(text)) {
            stack.push(stoi(text));
            continue;
        }

        y = stack.get_elem();
        x = stack.get_elem();
        char token = *text.data();
        if (token == '+') {
            stack.push(x + y);
        } else if (token == '-') {
            stack.push(x - y);
        } else if (token == '*') {
            stack.push(x * y);
        } else if (token == '/') {
            stack.push(x / y);
        }
    }


    if (stack.size() != 1)
        printError();

    cout << stack.top() << endl;
    return 0;


}
