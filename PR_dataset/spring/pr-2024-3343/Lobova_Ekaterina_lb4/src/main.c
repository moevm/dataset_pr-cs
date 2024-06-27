class CustomStack {
public:
    CustomStack(size_t initialCapacity) {
        this->mCapacity = initialCapacity;
        this->mData = new int[initialCapacity];
        this->mIndex = -1;
    }
    CustomStack() : CustomStack(10) {
    }
    ~CustomStack() {
        delete[] this->mData;
    }
    void push(int val) {
        this->ensureSpace();
        this->mIndex++;
        this->mData[this->mIndex] = val;
    }
    void pop() {
        if (this->empty()) {
            cout<<"error";
            exit(0);
        }
        this->mIndex--;
    }
    int top(){
        if (this->empty()) {
            cout<<"error";
            exit(0);
        }
        return this->mData[this->mIndex];
    }
    size_t size() const {
        return this->mIndex + 1;
    }
    bool empty() const {
        return this->mIndex == -1;
    }
    void extend(int n) {
        if (n <= 0) {
            throw logic_error("extend() called with a nonpositive argument");
        }
        this->resize(this->mCapacity + n);
    }
protected:
    size_t mCapacity;
    size_t mIndex;
    int *mData;
private:
    size_t getNewCapacity() const {
        return this->mCapacity * 3 / 2 + 1;
    }
    void ensureSpace() {
        if (this->mIndex + 1 == mCapacity) {
            size_t newCapacity = this->getNewCapacity();
            this->resize(newCapacity);
        }
    }
    void resize(size_t newCapacity) {
        if (newCapacity == mCapacity) {
            return;
        }
        if (newCapacity < mCapacity) {
            throw logic_error("resize() called with a lower capacity");
        }
        int *newData = new int[newCapacity];
        copy(this->mData, this->mData + this->mCapacity, newData);
        delete[] this->mData;
        this->mData = newData;
        this->mCapacity = newCapacity;
    }
};
int main(){
    CustomStack s = CustomStack();
    string command;
    int value;
    while (command!="cmd_exit"){
        getline(cin, command);
        if (command.find("cmd_push") != string::npos){
            value = stoi(command.substr(command.find(" ") + 1));
            s.push(value);
            cout<<"ok"<<endl;
        }
        if (command=="cmd_top"){
            value = s.top();
            cout<<value<<endl;
        }
        if (command=="cmd_pop"){
            value = s.top();
            s.pop();
            cout<<value<<endl;
        }
        if (command=="cmd_size"){
            value = s.size();
            cout<<value<<endl;
        }
    }
    cout<<"bye"<<endl;
    return 0;
}

