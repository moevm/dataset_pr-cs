class CustomStack {
public:
    CustomStack(){
        mCapacity = 10;
        mSize = 0;
        mData = new char *[mCapacity];
    }

    explicit CustomStack(int capacity){
        mCapacity = capacity;
        mSize = 0;
        mData = new char *[mCapacity];
    }

    ~CustomStack(){
        for (size_t i = 0; i < mSize; ++i){
            delete[] mData[i];
        }
        delete[] mData;
    }

    void push(const char *val){
        if (mSize >= mCapacity){
            extend(mCapacity); 
        }
        mData[mSize] = new char[strlen(val) + 1];
        strcpy(mData[mSize], val);
        ++mSize;
    }

    void pop(){
        if (!empty()){
            delete[] mData[mSize - 1];
            --mSize;
        }
    }

    char *top(){
        if (!empty()){
            return mData[mSize - 1];
        }
        return nullptr;
    }

    size_t size(){
        return mSize;
    }

    bool empty(){
        return mSize == 0;
    }

    void extend(int n){
        mCapacity += n;
        char **newData = new char *[mCapacity];
        for (size_t i = 0; i < mSize; ++i){
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
    }
private:
    size_t mCapacity{}; 
    size_t mSize{}; 
protected:
    char **mData; 
};

int main(){
    string data;
    getline(cin, data);
    int count_open_tags = 0;
    int count_closing_tags = 0;
    for (int i = 1; i < data.size(); i++){
        if (data[i - 1] == '<' && data[i] != '/')
            count_open_tags++;
        else if(data[i - 1] == '<' && data[i] == '/')
            count_closing_tags++;
    }
    CustomStack open_tags(count_open_tags);
    for (int i = 0; i  < data.size(); i++){
        char res[10];
        res[0] = '\0';
        if (data[i] == '<'){
            int j = i + 1, n = 0;
            while(data[j] != '>') {
                res[n] = data[j];
                n++; j++;
            }
            res[n] = '\0';
            if(res[0] == '/'){
                char *check = open_tags.top();
                for(int k = 1; res[k]; k++)
                    if(check[k - 1] != res[k]){
                        cout << "wrong";
                        return 0;
                    }
                open_tags.pop();
            }
            else if(strcmp(res, "br") != 0 && strcmp(res, "hr") != 0)
                open_tags.push(res);
            i = j;
        }
    }
    cout << "correct";
    return 0;
}