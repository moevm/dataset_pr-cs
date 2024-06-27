class CustomStack{
        public:
        CustomStack(): mHead{nullptr} {}

        CustomStack(ListNode* head): mHead{head} {}

        ~CustomStack() {
            while (!empty())
                pop();
        }
        
        void push(const char* tag){
            char* new_tag = new char[strlen(tag) + 1];
            strcpy(new_tag, tag);
            if (empty()){
                mHead = new ListNode;
                mHead->mNext = nullptr;
                mHead->mData = (char*)new_tag;
                return;
            }
            ListNode* temp = mHead;
            while(temp->mNext != nullptr){
                temp = temp->mNext;
            }
            ListNode* node = new ListNode;
            node->mNext = nullptr;
            node->mData = (char*)new_tag;
            temp->mNext = node;

            return;
        }

        void pop(){
            if (empty()){
                cout << "error" << endl;
                exit(0);
            }
            ListNode* temp = mHead;
            if(temp->mNext == nullptr){
                delete temp->mNext;
                mHead = nullptr;
                return;
            }
            while(temp->mNext->mNext != nullptr){
                temp = temp->mNext;
            }
            delete temp->mNext->mNext;
            temp->mNext = nullptr;
            return;
        }

        char* top(){
            if(empty()){
                cout << "error" << endl;
                exit(0);
            }
            ListNode* temp = mHead;
            while(temp->mNext != nullptr){
                temp = temp->mNext;
            }
            return temp->mData;
        }
        
        size_t size(){
            if (empty()){
                return 0;
            }
            size_t len = 1;
            ListNode * temp = mHead;
            while(temp->mNext != nullptr){
                len++;
                temp = temp->mNext;
            }
            return len;
        }
        
        bool empty(){
            return mHead == nullptr;
        }
            
        protected:
            ListNode* mHead;
};

void check(){
    int r = 1;
    CustomStack stack;
    string str;
    getline(cin, str);
    while (1){
        string temp;

        if (str.find("<") == -1){
            break;
        }

        for (int i = str.find("<") + 1; i < str.find(">"); i++){
            temp += str[i];
        }
        str.replace(str.find("<"), 1, "!");
        str.replace(str.find(">"), 1, "!");
        
        if (temp != "br" && temp != "hr"){
            if (temp[0] != '/'){
                stack.push(temp.c_str());
            }
            else if (temp[0] == '/'){
                if (stack.empty()){
                    r = 0;
                }
                string temp_candidate = (string)stack.top();
                stack.pop();

                if (('/' + temp_candidate) != temp){
                    r = 0;
                }
            }
        }
    }
    if (r && !stack.empty()){
        r = 0;
    }
     
    if (r){
        cout << "correct" << endl;
    }
    else{
        cout << "wrong" << endl;
    }
}

int main(){
    check();
    return 0;
}