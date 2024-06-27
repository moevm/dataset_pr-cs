#define BLOCK_SIZE 8

class CustomStack {

private:
    int len;


public:
    CustomStack() {
        mData = new char *[BLOCK_SIZE];
        len = -1;
    }

    ~CustomStack() {
        for (int i = 0; i <= len; i++) {
            delete[] mData[i];
        }
        delete[] mData;
    }

    void extend(int n) {
        char **tmp = new char *[len + n + 1];
        for (size_t i = 0; i <= len; i++) {
            tmp[i] = mData[i];
        }
        delete[] mData;
        mData = tmp;
    }

    void push(const char *val) {
        ++len;
        mData[len] = new char[strlen(val)];
        strcpy(mData[len], val);
        if ((len - 1) % BLOCK_SIZE == 0) {
            extend(BLOCK_SIZE);
        }
    }

    void pop() {
        delete[] mData[len--];
    }

    char *top() {
        return mData[len];
    }

    size_t size() {
        return len + 1;
    }

    bool empty() {
        if (len == -1) {
            return true;
        }
        return false;
    }


protected:
    char **mData;
};

int main() {
    string s;
    getline(cin, s);
    CustomStack st = CustomStack();
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '<') {
            size_t j = i + 1;
            while (s[j] != '>') {
                ++j;
            }
            string str = s.substr(i, j - i + 1);
            if (str != "<br>" && str != "<hr>") {
                if (s[i + 1] == '/') {
                    char *str1;
                    if (!st.empty()) {
                        str1 = st.top();
                    } else {
                        cout << "wrong";
                        return 0;
                    }
                    char *str2 = &str[0];
                    if (strcmp(str1 + 1, str2 + 2) == 0) {
                        st.pop();
                    } else {
                        cout << "wrong";
                        return 0;
                    }
                } else {
                    st.push(str.c_str());
                }
            }
            i = j;
        }
    }
    if (!st.empty()) {
        cout << "wrong";
    } else {
        cout << "correct";
    }
    return 0;
}