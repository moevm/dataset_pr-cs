class CustomStack {
    public:
        CustomStack() {
            stackSize = 0;
            capacity = 100;
            mData = new char* [capacity];
        }

        ~CustomStack() {
            for (size_t i = 0; i < stackSize; i++) {
                delete[] mData[i];
            }

            delete[] mData;
        }

        void
        push(const char* val) {
            if (stackSize >= capacity) extend(capacity);

            mData[stackSize] = new char [strlen(val) + 1];
            strcpy(mData[stackSize++], val);
        }

        void
        pop() {
            delete[] mData[stackSize - 1];
            stackSize--;
        }

        char*
        top() {
            return mData[stackSize - 1];
        }

        size_t
        size() {
            return stackSize;
        }

        bool
        empty() {
            return stackSize == 0;
        }

        void
        extend(int n) {
            capacity += n;
            char** newmData = new char* [capacity];

            for (size_t i = 0; i < stackSize; i++) {
                newmData[i] = mData[i];
            }
            delete[] mData;
            mData = newmData;
        }
    
    private:
        size_t stackSize;
        size_t capacity;
        
    protected:
        char** mData;
};


int
main() {
    char* text, * tag;
    int flag = 0, tagLen = 0, isCorrect;
    text = new char [3001];
    tag = new char [3001];
    fgets(text, 3000, stdin);

    CustomStack stack;

    for (size_t i = 0; i < strlen(text); i++) {
        if (text[i] == '<') {
            flag = 1;
        } else if (flag == 1 && text[i] == '/') {
            flag = 2;
        } else if (text[i] == '>') {
            tag[tagLen] = '\0';
            if (flag == 1 && strcmp("<hr", tag) != 0 && strcmp("<br", tag)) {
                stack.push(tag);
            } else if (flag == 2) {
                isCorrect = 1;
                for (size_t j = 1; j < strlen(stack.top()); j++) {
                    if (tag[j + 1] != stack.top()[j]) isCorrect = 0;
                }
                if (isCorrect == 1) stack.pop();
            }
            
            flag = 0;
            tagLen = 0;
        }
        
        if (flag > 0) tag[tagLen++] = text[i];
    }
    if (stack.empty()) {
        cout << "correct";
    } else {
        cout << "wrong";
    }

    return 0;
}