class CustomStack{
    public:
    CustomStack(){
        mHead = nullptr;
        mSize = 0;
    }

    void push(const char* str){
        ListNode *newElement = new ListNode;
        if(newElement == nullptr){
            cout<< "Memory error";
            exit(0);
        }
        newElement->mData = new char[strlen(str)+1];
        if(newElement->mData == nullptr){
            cout<< "Memory error";
            exit(0);
        }
        strcpy(newElement->mData, str);
        newElement->mNext = mHead;
        mHead = newElement;
        mSize++;
    }

    void pop(){
        if (empty())
            return;
        ListNode *deletingElement = mHead->mNext;
        delete[] mHead->mData;
        delete mHead;
        mHead = deletingElement;
        mSize--;
    }

    char* top(){
        if (empty())
            return nullptr;
        return mHead->mData;
    }

    size_t size(){
        return mSize;
    }

    bool empty(){
        return mHead == nullptr;
    }

    ~CustomStack(){
        while(!empty())
            pop();
    }

    private:
    size_t mSize;

    protected:
    ListNode *mHead;
};

int main(){
    CustomStack p;
    string text;
    getline(cin, text);
    string serv_tag1 = "br";
    string serv_tag2 = "hr";
    int start_idx = text.find('<');
    int end_idx = text.find('>');
    while (start_idx != string::npos || end_idx != string::npos) {
        string tag = text.substr(start_idx + 1, end_idx - start_idx - 1);
        if (tag != serv_tag1 && tag != serv_tag2) {
            if (tag[0] == '/') {
                string top = p.top();
                if (top.substr(0) != tag.substr(1)){
                    cout<<"wrong";
                    return 0;
                }
                p.pop();
            }
            else {
                p.push(tag.c_str());
            }
        }
        text = text.substr(end_idx + 1);
        start_idx = text.find('<');
        end_idx = text.find('>');
    }

    if(p.empty()){
        cout<<"correct";
    }
    else{
        cout<<"wrong";
    }
    return 0;
}
