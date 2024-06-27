class CustomStack {
    public:
        // Constructor
        CustomStack(){
            this->mData = new char *[this->mCapacity]; 
            if (!(this->mData)) {
                cerr << "Error" << endl;
                exit(0);
            }
            this->mIndex = -1;
        }
        // Destructor 
        ~CustomStack(){
            for (int i = 0; i <= mIndex; i++){
                delete mData[i];
            }
            delete[] mData;
        }
        void push(const char *val){
            this->mIndex++;
            if (this->mIndex >= this->mCapacity){
                extend(this->mCapacity);
            }
            this->mData[this->mIndex] = new char[strlen(val) + 1];
            if (!(this->mData[this->mIndex])) {
                cerr << "Error" << endl;
                exit(0);
            }
            strcpy(this->mData[this->mIndex], val);
        }
        char *top(){
            return this->mData[this->mIndex];
        }
        char *pop(){
            return this->mData[this->mIndex--];
        }
        bool empty(){
            return this->mIndex == -1;
        }
        size_t size(){
            return this->mIndex + 1;
        }
        void extend(int n){
            char **newData = new char *[this->mCapacity + n];
            if (newData == nullptr) {
                cerr << "Error" << endl;
                exit(0);
            }
            for (size_t i = 0; i <= this->mIndex; ++i){
                newData[i] = this->mData[i];
            }
            delete[] mData;
            this->mCapacity += n;
            this->mData = newData;
        }
    private:
        int mIndex;
        size_t mCapacity = 10;
    protected:
        char **mData;
};

int main(){
    string commands;
    getline(cin, commands);
    CustomStack st;
    for (int i = 0; i < commands.size(); i++) {
        char tag[10];
        if (commands[i] == '<') {
            int j = i + 1, n = 0;
            while (commands[j] != '>') {
                tag[n] = commands[j];
                n++; 
                j++;
            }
            tag[n] = '\0';
            if (tag[0] == '/') {
                if (st.empty()){
                    cout << "wrong";
                    return 0;
                }
                char *check = st.top();
                for (int k = 1; tag[k]; k++){
                    if (check[k - 1] != tag[k]){
                        cout << "wrong";
                        return 0;
                    }
                }
                st.pop();
            }
            else if(strcmp(tag, "br") != 0 && strcmp(tag, "hr") != 0){
                st.push(tag);
            }
            i = j;
        }
    }
    if (st.empty()){
        cout << "correct";
        return 0;
    }
    cout<<"wrong";
    return 0;
}
