class CustomStack {

public:
    CustomStack(){
        mHead = nullptr;
        mSize=0;
    }

    void push(long long el){
        ListNode* tmp = new ListNode;
        tmp->mData = el;
        tmp->mNext = mHead;
        mHead = tmp;
        mSize++;
    }

    void pop(){
        if(!empty()){
            mSize--;
            mHead = mHead->mNext;
        }
    }

    int size(){
        return mSize;
    }

    bool empty(){
        return mHead == nullptr;
    }

    long long top(){
        if(!empty()){
            return mHead->mData;
        }
    }

    ~CustomStack() {
        for (int i = 0; i < mSize; i++) {
            pop();
        }
    }

private:
    long long mSize;

protected:
    ListNode* mHead;
};

int main()
{
    CustomStack st = CustomStack();
    long long n = 100, zn = 1, el = 0, flag = 0, flag1 = 0;
    char symb;
    for(int i = 0; i < n; i++){
        if(flag1 == 0){
            scanf("%c", &symb);
        }
        flag1 = 0;
        if(symb == ' ' && flag == 1){
            st.push(zn * el);
            el = 0;
            zn = 1;
            flag = 0;
        }else if(symb == '\n' || symb == EOF){
            if(flag == 1){
                cout << "error" << endl;
                return 0;
            }
            break;
        }else if(symb <= '9' && symb >= '0'){
            el = el * 10 + (symb - '0');
            flag = 1;
        }else if(symb == '-'){
            char symb1;
            scanf("%c", &symb1);
            if(symb1 == ' '){
                if(st.size() >= 2){
                    long long razn = st.top();
                    st.pop();
                    razn = st.top() - razn;
                    st.pop();
                    st.push(razn);
                }else{
                    cout << "error" << endl;
                    return 0;
                }
            }else if(symb1 == '\n' || symb1 == EOF){
                if(st.size() >= 2){
                    long long razn = st.top();
                    st.pop();
                    razn = st.top() - razn;
                    st.pop();
                    st.push(razn);
                    break;
                }else{
                    cout << "error" << endl;
                    return 0;
                }
            }else{
                zn = -1;
                symb = symb1;
                flag1 = 1;
            }
        }else{
            if(symb == '+'){
                if(st.size() >= 2){
                    long long sum = st.top();
                    st.pop();
                    sum += st.top();
                    st.pop();
                    st.push(sum);
                }else{
                    cout << "error" << endl;
                    return 0;
                }
            } else if(symb == '*'){
                if(st.size() >= 2){
                    long long pr = st.top();
                    st.pop();
                    pr *= st.top();
                    st.pop();
                    st.push(pr);
                }else{
                    cout << "error" << endl;
                    return 0;
                }
            } else if(symb == '/'){
                if(st.size() >= 2){
                    long long del = st.top();
                    st.pop();
                    del = st.top() / del;
                    st.pop();
                    st.push(del);
                }else{
                    cout << "error" << endl;
                    return 0;
                }
            }
        }
    }
    if(st.size() == 1){
        cout << st.top() << endl;
    }else{
        cout << "error" << endl;
    }
    return 0;
}
