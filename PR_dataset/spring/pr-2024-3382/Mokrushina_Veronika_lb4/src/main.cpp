class CustomStack {
    public:
    
        CustomStack() { 
            mHead = nullptr;
        }
        
        void push(const char* tag) {
            ListNode* Node = new ListNode;
            Node->mData = new char[sizeof(tag) + 1];
            strcpy(Node->mData, tag);
            Node->mNext = mHead;
            mHead = Node;
        }
        
        void pop() {
            if (!empty()){
                ListNode* new_mHead = mHead->mNext;
                delete[] mHead->mData;
                delete mHead;
                mHead = new_mHead;
            }
        }
        
        char* top() {
            if (!empty()) {
                return mHead->mData;
            }
            return nullptr;
        }
        
        size_t size() {
            size_t count = 0;
            if (empty()) {
                return count;
            } else {
                while (mHead) {
                    count++;
                    pop();
                }
                return count;
            }
        }
        
        bool empty() {
            return (!mHead);
        }
        
        ~CustomStack() {
            while (mHead) {
                pop();
            }
        }
    protected:
        ListNode* mHead;
};


int main() {
    string str;
    getline(cin, str);
    CustomStack stack;
    string serv_tag1 = "br"; 
    string serv_tag2 = "hr";
    int start = str.find('<');
    int end = str.find('>');
    bool result = true;
    while (start != string::npos || end != string::npos) {
        string tag = str.substr(start + 1, end - start - 1);
        if (tag != serv_tag1 && tag != serv_tag2) {
            if (tag[0] != '/') {
                stack.push(tag.c_str());
            } else {
                string top_str = stack.top();
                if (top_str.substr(0) != tag.substr(1)){
                    result = false;
                    break;
                }
                else {
                    stack.pop();
                }
            }
        }
        str = str.substr(end + 1);
        start = str.find('<');
        end = str.find('>');
    }
    if (result) {
        cout << "correct" << endl;
    } else {
        cout << "wrong" << endl;
    }
    return 0;
}

