class CustomStack{
public:
     CustomStack (){
         mHead = new ListNode;
         mHead->mNext=NULL;
         siz=0;
     }
     ~CustomStack(){
         while(mHead->mNext!=NULL){
            tmp=mHead;
            mHead=tmp->mNext;
            delete tmp;
         }
         delete mHead;
     }
     size_t size(){
         return siz;
     }
     void push(int data){
         tmp=new ListNode;
         tmp->mNext=mHead;
         tmp->mData=data;
         mHead=tmp;
         siz++;
     }
     void pop(){
         tmp =mHead;
         mHead=tmp->mNext;
         delete tmp;
         --siz;
     }
     int top(){
         return mHead->mData;
     }
     bool empty(){
         if(!mHead->mNext)return 1;
         else return 0;
     }
     size_t sizee(){
         return siz;
     }
private:
    ListNode*tmp;
    size_t siz;
protected:
    ListNode*mHead;
};



int main()
{
    CustomStack st{};
    std::string s;
    getline(std::cin,s);
    s+=' ';
    bool f =1;
    for(int i=0;i<s.size() && f;++i){
        std::string tmp = "";
        while(i!=s.size() &&s[i]!= ' '){
                tmp+=s[i++];
        }
        if(tmp.size()==1)
            if(tmp[0]<'0'||tmp[0]>'9'){
                int a,b;
                if(!st.empty()){
                    b = st.top();
                    st.pop();
                }else f =0;
                if(!st.empty()){
                    a = st.top();
                    st.pop();
                }else f =0;
                if(f){
                if(tmp == "+")st.push(a+b);
                else if(tmp == "-")st.push(a-b);
                else if(tmp == "*")st.push(a*b);}
            }
            else st.push(stoi(tmp));
        else if(tmp.size()>0)st.push(stoi(tmp));
    }
    if(f){
        if(st.size()==1)std::cout<<st.top();
        else f =0;
    }
    if(!f){
        std::cout<<"error";
    }
    //~CustomStack();
    return 0;
}
