#define BUFFER_SIZE 10

class CustomStack {
public:
    CustomStack(){
        this->top_index = -1;
        this->capacity = BUFFER_SIZE;
        this->mData = new char*[BUFFER_SIZE];
    }
    void push(const char* val){
        top_index++;
        if (top_index >= capacity){
            extend(BUFFER_SIZE);
        }
        mData[top_index] = new char[strlen(val) + 1];
        strcpy(mData[top_index], val);
    }
    void pop(){
        delete[] mData[top_index];
        top_index--;
    }
    char *top(){
        return mData[top_index];
    }
    size_t size(){
        return this->top_index + 1;
    }
    bool empty(){
        return top_index == -1;
    }
    void extend(int n){
        this->capacity += BUFFER_SIZE;
        char **newData = new char*[this->capacity];
        memcpy(newData, mData, (this->top_index + 1) * sizeof(char *));
        delete[] mData;
        this->mData = newData;
    }
    ~CustomStack(){
        for (int i = 0; i <= this->top_index; ++i){
            delete[] mData[i];
        }
        delete[] this->mData;
    }
protected:
    char** mData;

private:
    int top_index;
    size_t capacity;
};

bool isValidHTMLString(string line){
    CustomStack *stack = new CustomStack;
    int left_index = line.find('<');
    int right_index = line.find('>');
    while (left_index != string::npos || right_index != string::npos){
        string tag = line.substr(left_index + 1, right_index - left_index - 1);
        if (tag[0] != '/' && tag != "br" && tag != "hr"){
            stack -> push(tag.c_str());
        }else if (tag != "br" && tag != "hr"){
            if (stack->empty()){
                return false;
            }
            char *prev_tag = stack -> top();
            if (strcmp(prev_tag, tag.c_str() + 1) != 0){
                    return false;
            }
            stack->pop();
        }
        line = line.substr(right_index + 1);
        left_index = line.find('<');
        right_index = line.find('>');
    }
    return stack->empty();
}

int main() {
    string line;
    getline(cin, line);
    if (isValidHTMLString(line)){
        cout << "correct";
    }else{
        cout << "wrong";
    }
    return 0;
}
