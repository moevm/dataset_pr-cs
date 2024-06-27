class CustomStack {
    public:
        CustomStack() : mHead(nullptr) {};
        ~CustomStack()
        {
            while(!is_empty())
            {
                pop();
            }
        }

        int size()
        {
            int length = 0;
            ListNode* check = mHead;
            if(nullptr == check) return length;
            while(check->mNext != nullptr)
            {
                check = check->mNext;
                length++;
            }
            length++;
            return length;
        }

        void push(const char* x)
        {
         ListNode* node = new ListNode;
         node->mData = new char[strlen(x) + 1];
         strcpy(node->mData, x);
         node->mNext = mHead;
         mHead = node;
        }

        bool is_empty()
        {
            return (nullptr == mHead);
        }

        const char* top()
        {
            return mHead->mData;
        }

        char* pop()
        {
            if(is_empty())
            {
                throw std::length_error("stack is empty");
            }

        ListNode* delnode = mHead;
        char* x = delnode->mData;
        mHead = delnode->mNext;    
        return x;
        }
    protected:
        ListNode* mHead;
    };
        
int main() {
    CustomStack vector;

    char str[3000];
    fgets(str, 3000, stdin);
    char* token;
    token = strtok(str, "<");
    while (token != NULL) { // <br>, <hr>.
        for(int i = 0; i < strlen(token); ++i){
            if(token[i] == '>'){
                token[i] = '\0';
                break;
            }
        }
        if(strcmp(token, "br") && strcmp(token, "hr") && strcmp(token, "\n"))
        {
            if(vector.is_empty())
            {
                vector.push(token);
                // std::cout << "  input " << token << std::endl;
                token = strtok(NULL, "<");
                continue;
            }
            char closingword[100] = "/";
            char curtop[100];
            memcpy(curtop, vector.top(), 100);
            strcat(closingword, curtop);
            // std::cout << "close " << closingword << std::endl;
            
            if(!strcmp(token, closingword))
            {
                // std::cout << "delete " << vector.pop() << std::endl;
                vector.pop();
            } else {
                vector.push(token);
                // std::cout << "  input " << token << std::endl;
            }
        }
        token = strtok(NULL, "<");
    }

    if(vector.is_empty())
        std::cout << "correct";
    else
        std::cout << "wrong";
    
    return 0;
}
