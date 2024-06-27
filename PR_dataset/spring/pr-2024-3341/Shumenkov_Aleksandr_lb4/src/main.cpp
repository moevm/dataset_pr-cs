class CustomStack {
public:
    CustomStack() {
        mSize = 0;
        mData = new char *[10];
        mCapacity = 10;
    }

    ~CustomStack() {
        for (int i = 0; i < mSize; i++){
            delete[] mData[i];
        }
        delete[] mData;
    }

    void
    push(const char *val) {
        if (mSize >= mCapacity) {
            extend(10);
        }

        mData[mSize] = new char[strlen(val) + 1];
        strcpy(mData[mSize], val);
        mSize++;
    }

    void
    pop() {
        if (mSize > 0) {
            delete[] mData[mSize - 1];
            mSize--;
        }
    }

    char *
    top() {
        if (mSize > 0) {
            return mData[mSize - 1];
        }
        return nullptr;
    }

    size_t
    size(){
        return mSize;
    }

    bool
    empty(){
        return (mSize == 0);
    }

    void
    extend(int n){
        mCapacity += n;
        char** tmp = new char*[mCapacity];
        for (int i = 0; i < mSize; i++){
            tmp[i] = mData[i];
        }
        delete[] mData;
        mData = tmp;
    }

private:
    int mSize;
    int mCapacity;

protected:
    char** mData;
};

string input(){
    string data;
    getline(cin, data);
    return data;
}

bool checkingInput(const string data, CustomStack& open_tags){
    for (int i = 0; i < data.size(); i++) {
        char res[10];
        res[0] = '\0';
        if (data[i] == '<') {
            int j = i + 1, n = 0;
            while (data[j] != '>'){
                res[n] = data[j];
                n++; j++;
            }
            res[n] = '\0';
            if (res[0] == '/'){
                char* check = open_tags.top();
                for (int k = 1; res[k]; k++)
                    if (check[k - 1] != res[k]) return false;
                open_tags.pop();
            }
            else if (strcmp(res, "br") != 0 && strcmp(res, "hr") != 0) open_tags.push(res);
            i = j;
        }
    }
    return true;
}

void outPut(bool value){
    if (value) cout << "correct";
    else cout << "wrong";
}

int main(){
    string data = input();
    CustomStack open_tags;
    outPut(checkingInput(data, open_tags));
    return 0;
}

