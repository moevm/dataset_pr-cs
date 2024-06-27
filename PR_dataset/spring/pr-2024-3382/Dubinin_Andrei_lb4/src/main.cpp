class CustomStack {
public:
    CustomStack() {
        this->mData = new char*[stack_size];
        max_index = -1;
    }

    ~CustomStack() {
        for (int i = 0; i <= max_index; i ++) {
            delete[] mData[i];
        }
        delete[] mData;
    }

    void push(const char* val) {
        max_index ++;
        if (max_index > stack_size) {
            extend(stack_size);
        }
        mData[max_index] = new char[strlen(val) + 1];
        strcpy(mData[max_index], val);
    }

    char* top() {
        return mData[max_index];
    }

    char* pop() {
        return mData[max_index --];
    }

    bool empty() {
        return max_index == -1;
    }

    size_t size() {
        return max_index + 1;
    }

    void extend(int n) {
        stack_size += n;
        char** newData = new char*[stack_size];
        for (int i = 0; i <= max_index; i ++) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
    }
    
private:
    size_t stack_size = 5;
    size_t max_index;
    
protected:
    char** mData;
};

bool isBalanced(string text) {
    int start_index = text.find('<');
    int end_index = text.find('>');
    CustomStack* tagStack = new CustomStack;

    while (start_index != string::npos || end_index != string::npos) {
        string currentTag = text.substr(start_index + 1, end_index - start_index - 1);
        if (currentTag == "br" || currentTag == "hr") {
            text = text.substr(end_index + 1);
            start_index = text.find('<');
            end_index = text.find('>');
            continue;
            
        } else if (currentTag[0] != '/') {
            tagStack->push(currentTag.c_str());
            text = text.substr(end_index + 1);
            start_index = text.find('<');
            end_index = text.find('>');
            continue;
        }

        if (tagStack->empty()) {
            return false;
        }
        char* prevTag = tagStack->pop();
        if (strcmp(prevTag, currentTag.c_str() + 1) != 0) {
            return false;
        }
        text = text.substr(end_index + 1);
        start_index = text.find('<');
        end_index = text.find('>');
    }
    
    return true;
}

int main() {
    string text;
    getline(cin, text);
    
    if (isBalanced(text))
        cout << "correct" << endl;
    else
        cout << "wrong" << endl;

    return 0;
}
