class CustomStack {
    public:
        CustomStack(){
            mHead=nullptr;
            mSize=0;
        }
        bool empty(){
            return mHead==nullptr;
        }
        int size(){
            return mSize;
        }
        char *top(){
            if (empty())
                return nullptr;
            return mHead->mData;
        }
        void push(const char *str){
            ListNode* newElement= new ListNode;
            newElement->mData= new char[strlen(str)];
            strcpy(newElement->mData, str);
            newElement->mNext=mHead;
            mHead=newElement;
            mSize++;
        }
        void pop(){
            if (empty()){
            return;
            }
            ListNode* Del = mHead;
            mHead = mHead->mNext;
            delete[] Del->mData;
            delete Del;
            mSize--;
        }
        ~CustomStack(){
            while(!empty()){
                pop();
            }
        }
    private:
        int mSize;          
    protected:
        ListNode* mHead;
    };
string getWord(istream& in) 
{
    int c;
    string word;
    while( !in.eof() ) 
    {
        c = in.get();
        word += c;
    }
    return word;
}
        int main() {
            CustomStack p =CustomStack();
            string s = getWord(cin);
            if (s.length()==0){
                cout<<"correct"<<endl;
            }
            else{
                int already=0;
                for (int i=0; i<s.length();i++){
                    if ((s[i]=='<') and (s[i+1]=='/')){
                        int k=i+2;
                        string tag("/");
                        while(s[k]!='>'){
                            tag+=s[k];
                            k++;
                        }
                        string tagcmp("");
                        if (!p.empty()){
                            tagcmp=p.top();
                            p.pop();
                        }else{
                            cout<<"wrong"<<endl;
                            return 0;
                        }if (tag!='/'+tagcmp){
                            cout<<"wrong"<<endl;
                            return 0;
                        }
                        
                    }if ((s[i]=='<') and (s[i+1]!='/')){
                        int k=i+1;
                        string tag("");
                        while(s[k]!='>'){
                            tag+=s[k];
                            k++;
                        }
                        if ((tag!="br")&&(tag!="hr")){
                            p.push(tag.c_str());
                        }
                    }
                }
                if (p.empty()){
                    cout<<"correct"<<endl;
                }else{
                    cout<<"wrong"<<endl;
                }
            }
            return 0;
        }