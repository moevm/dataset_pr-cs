class CustomStack {

    public:
        CustomStack(){
            mpamat = 100;
            msize = 0;
            mData = new char*[mpamat];
        }
        explicit CustomStack(int pamat){
            mpamat = pamat;
            msize = 0;
            mData = new char*[mpamat];
        }
        ~CustomStack(){
            for (int i = 0; i<msize; ++i){
                delete [] mData[i];
            }
            delete [] mData;
        }

        void push(const char* val){
            if (msize >= mpamat){
                extend(mpamat); // add the value
            }
            mData[msize] = new char[strlen(val)+1];
            strcpy(mData[msize], val);
            msize+=1;
        }
        void pop(){
            if (!empty()){ // add the function
                delete[] mData[msize-1];
                msize-=1;
            }
        }
        char* top(){
            //if (!empty()){ // add the function
            return mData[msize-1];
        }
        size_t size(){
            return msize;
        }
        bool empty(){
            return msize == 0;
        }
        void extend(int n){
            mpamat += n;
            char **data = new char*[mpamat];
            for (int i = 0; i<msize; ++i){
                data[i] = mData[i];
            }
            delete[] mData;
            mData = data;
        }

    private:
        int mpamat{};
        int msize{};

    protected:  

        char** mData;
};


int main(){
    string data;
    getline(cin, data);
    int c_open = 0;
    int c_close = 0;
    for (size_t i = 0; i<data.size(); ++i){
        if (data[i] == '<' && data[i-1] != '/' ){
            c_open+=1;
        }
        else if (data[i] == '>' && data[i-1] == '/' ){
            c_close+=1;
        }
    }
    CustomStack open(c_open);
    for (size_t i = 0; i<data.size(); ++i){
        char arr[10];
        if (data[i] == '<'){
            int j = i + 1;
            int n = 0;
            while(data[j] != '>'){
                arr[n] = data[j];
                j+=1;
                n+=1;
                //cout << "1 ";
            }
            arr[n] = '\0';
            //cout << "2 ";
            if (arr[0] != '/' && strcmp(arr, "br") != 0 && strcmp(arr, "hr")!=0){
                open.push(arr);
                //cout << "3\n";
            }
            else if (arr[0] == '/'){
                char* tg = open.top();
                //cout <<"4  "<<tg; 
                for (size_t k = 1; k<strlen(tg);++k){
                    //cout <<"5  "<<tg[k];
                    if (tg[k-1] != arr[k]){
                        cout << "wrong";
                        return 0;
                    }
                }
                open.pop();
            }
            i = j;
        }
    }
    cout << "correct";
    return 0;
}