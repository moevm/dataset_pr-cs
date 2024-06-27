class CustomStack {
        public:

            CustomStack(){
                mHead = nullptr;
            }

            void push(const char* tag){
                ListNode* mCur = new ListNode;
                mCur->mData = new char(sizeof(tag)+1);
                strcpy(mCur->mData, tag);
                mCur->mNext = mHead;
                mHead = mCur;
            }
            void pop(){
                if (!empty()){
                    ListNode* mCur = mHead->mNext;
                    delete[] mHead->mData;
                    delete mHead;
                    mHead = mCur;
                }
                
            }

            char* top(){
                if(!empty()){
                    return mHead->mData;
                }
                return nullptr;
            }
            size_t size(){
                size_t count;
                ListNode* mCur = mHead;
                while (mCur){
                    count++;
                }
                return count;
            }

            bool empty(){
                return (!mHead);
            }

            ~CustomStack(){
                while (mHead){
                    pop();
                }
            }

        protected:
            ListNode* mHead;
        };


int main(){
    string str;
    getline(cin, str);
    CustomStack stack;
    string tag1 = "br";
    string tag2 = "hr";

    int start = str.find('<');
    int end = str.find('>');
    bool result = true;

    while (start != string::npos || end != string::npos){
        string tag = str.substr(start+1, end - start - 1);
        if (tag != tag1 && tag != tag2){
            if (tag[0] != '/'){
                stack.push(tag.c_str());
            }else{
                string top_str = stack.top();
                if (top_str.substr(0) != tag.substr(1)){
                    result = false;
                    break;
                }else{
                    stack.pop();
                }
            }
        }
        str = str.substr(end+1);
        start = str.find('<');
        end = str.find('>');
    }

    if(result){
        cout << "correct" << endl;
    }else{
        cout << "wrong" << endl;
    }

    return 0;
}