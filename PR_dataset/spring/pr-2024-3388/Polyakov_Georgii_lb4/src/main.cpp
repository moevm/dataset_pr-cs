class CustomStack {
        public:
            CustomStack(){
                mHead = nullptr;
            }
            void push(const char* new_tag){
                ListNode* new_element  = new ListNode;
                new_element->mData = new char[strlen(new_tag)+1];
                strcpy(new_element->mData, new_tag);
                new_element->mNext = mHead;
                mHead = new_element;
            }
            void pop(){
                if (mHead != nullptr){
                    ListNode* new_head = mHead->mNext;
                    delete mHead;
                    mHead = new_head;
                }
            }
            size_t size(){
                if (mHead != nullptr){
                    size_t count = 1;
                    while (mHead->mNext != nullptr){
                        count++;
                    }
                    return count;
                }
                return 0;
            }
            char* top(){
                return mHead->mData;
            }
            bool empty(){
                if (mHead == nullptr){
                    return true;
                }
                return false;
            }
            ~CustomStack(){
                while (mHead!=nullptr){
                    pop();
                }
            }
        protected:
            ListNode* mHead;
};
bool get_result(string& html_code){
    CustomStack stack;
    int code_length = html_code.length();
    int count = 0;
    bool flag_read_start = false;
    bool flag_read_end = false;
    string tag = "";
    while (count<code_length){
        if (html_code[count] == '>'){
            if (tag != "br" && tag != "hr"){
                if (flag_read_start == true){
                    stack.push(tag.c_str());
                }else{
                    string top = stack.top();
                    if (tag != top){
                        return false;
                    }
                    stack.pop();
                }
            }
            flag_read_start = false;
            flag_read_end = false;
            tag = "";
        }
        if (flag_read_start == true || flag_read_end == true){
            tag+=html_code[count];
        }
        if (html_code[count] == '<'){
            if (html_code[count+1] == '/'){
                flag_read_end = true;
                count++;
            }else{
                flag_read_start = true;
            }
        }
        count++;
    }
    return true;
}
int main() {
    string html_code;
    getline(cin, html_code);
    if (get_result(html_code)) {
        cout << "correct" << endl;
    } else {
        cout << "wrong" << endl;
    }
    return 0;
}
