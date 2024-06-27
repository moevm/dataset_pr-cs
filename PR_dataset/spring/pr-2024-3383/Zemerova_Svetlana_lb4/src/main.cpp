#define block 100
class CustomStack {

public:

    CustomStack(){
        this->mHead=new ListNode;
        this->mHead->mNext=NULL;
        this->mHead->mData=new char[block];
        this->length=0;
    }

    void push(const char* tag){
        ListNode* tek=this->mHead;
        while (tek->mNext!=NULL){
            tek=tek->mNext;
        }
        ListNode* el=new ListNode;
        el->mData=new char[strlen(tag)+1];
        strncpy(el->mData, tag, strlen(tag)+1);
        el->mNext=NULL;
        tek->mNext=el;
        this->length++;
    }

    void pop(){
        ListNode* tek=this->mHead;
        while (tek->mNext->mNext!=NULL){
            tek=tek->mNext;
        }
        ListNode* tmp=tek->mNext;
        tek->mNext=NULL;
        delete tmp;
        this->length--;
    }

    char* top(){
        ListNode* tek=this->mHead;
        while (tek->mNext!=NULL){
            tek=tek->mNext;
        }
        return tek->mData;
    }

    size_t size(){
        return this->length;
    }

    bool empty(){
        if (!this->length){
            return true;
        }
        return false;
    }
    
    ~CustomStack(){
        while (!this->empty()) {
            this->pop();
        }
    }

private:
    size_t length;

protected:  
    ListNode* mHead;

};

void getcheck(CustomStack st, char* str){
    size_t k=0;
    for (size_t i=0; i<strlen(str); i++){
        if (str[i]=='<'){
            char* tag=new char[block];
            k=0;
            for (size_t j=i+1; j<strlen(str); j++){
                if (str[j]!='>'){
                    tag[k++]=str[j];
                }
                else if (tag[0]=='/'){
                    if (strstr(tag,st.top())==tag+1){
                        st.pop();
                        i=j;
                        break;
                    }
                    else {
                        cout<<"wrong";
                        return ;
                    }
                    }
                else {
                    if (strcmp(tag,"br")!=0 && strcmp(tag, "hr")!=0){
                        st.push(tag);
                    }
                    i=j;
                    break;
                    }
            }
        }
    }
    if (st.empty()){
        cout<<"correct";
    }
    else{
        cout<<"wrong";
    }
}

int main(){
    CustomStack st;
    char str[3000];
    fgets(str,3000,stdin);
    getcheck(st, str);
    return 0;
}
