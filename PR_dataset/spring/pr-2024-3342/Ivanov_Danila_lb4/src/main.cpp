void memory_error(){
    cout << "Memory error!" << endl;
    exit(1);
}

class CustomStack {
public:
    CustomStack() {
        mData = nullptr;
	    topIndex = -1;
    };

    void push(const char* val) {
        extend(1);
	    memcpy(mData[++topIndex], val, strlen(val));
        mData[topIndex][strlen(val)] = '\0';
    }

    void pop(){
        if (topIndex >= 0){
            delete[] mData[topIndex--];
        }
    }

    ~CustomStack() {
        for (int i = 0; i <= topIndex; i++){
            delete mData[i];
        }
        delete[] mData;        
    };

    char* top(){
        if (topIndex >= 0){
	        return mData[topIndex];
	    }
	    return NULL;
    }

    bool empty(){
	    return topIndex == -1;
    }

    size_t size(){
	    return topIndex + 1;
    }

    void extend(int n){
        char** NewData = new char* [topIndex + 1];
        if (NewData == nullptr)
        	memory_error;
        for (int i = 0; i <= topIndex; i++){
            NewData[i] = new char [300];
            if (NewData[i] == nullptr)
        	    memory_error;
            memcpy(NewData[i], mData[i], strlen(mData[i]));
            NewData[i][strlen(mData[i])] = '\0';
        }
		for (int i = 0; i <= topIndex; i++){
			delete [] mData[i];
		}
		delete [] mData;
        mData = new char* [topIndex + 1 + n];
        if (mData == nullptr)
        	memory_error;
        for (int i = 0; i <= topIndex; i++){
            mData[i] = new char [300];
            if (mData[i] == nullptr)
        	    memory_error;
            memcpy(mData[i], NewData[i], strlen(NewData[i]));
            mData[i][strlen(NewData[i])] = '\0';
        }
        for (int i = 1; i <= n; i++){
            mData[topIndex + i] = new char [300];
        }
        for (int i = 0; i <= topIndex; i++){
            delete[] NewData[i];
        }
        delete[] NewData;
    }

private:
    int topIndex;

protected:
    char** mData;
};

int equal(char* str_start, char* str_end){
    if (strlen(str_end) == strlen(str_start) + 1){
        int flag = 1;
	for (int i = 0; i < strlen(str_start); i++){
	    if (str_start[i] != str_end[i + 1]){
	        flag = 0;
		return 0;
	    }
	}
	if (flag == 1)
	    return 1;
	}
    return 0;
}

int main(){
    CustomStack obj;
    char* text = new char [3000];
    if (text == nullptr)
        memory_error();
    int result = 0;
    int flag = 0;
    int index = 0;
    char* str = new char [3000];
    if (str == nullptr)
        memory_error;
    fgets(text, 3000, stdin);
    for (int i = 0; i < strlen(text); i++){
        if (text[i] == '<'){
            flag = 1;
	    continue;
	}
	if (text[i] == '>'){
	    str[index] = '\0';
	    if (!(strlen(str) == 2 && ((str[0] == 'b' && str[1] == 'r') || (str[0] == 'h' && str[1] == 'r')))){
	        if (str[0] != '/'){
		    obj.push(str);
		}
		if (str[0] == '/' && (equal(obj.top(), str) == 1)){
		    obj.pop();
		    result = 0;
		}
		else if (str[0] == '/' && (equal(obj.top(), str) == 0)){
		    obj.push(str);
		    result = 1;
		}
	    }
	    flag = 0;
	    delete [] str;
	    str = new char [3000];
	    if (str == nullptr)
        	memory_error;
	    index = 0;
	}
	if (flag == 1){
	    str[index++] = text[i];
	}
    }
    if (obj.empty() && result == 0){
        cout << "correct" << endl;
    }
    else{
        cout << "wrong" << endl;
    }
    delete[] text;
    delete[] str;
    return 0;
}
