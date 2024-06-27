#include <cstdio>
#include <cstring>
#include <cstdlib>

class CustomStack {
    
    	public:
    	    CustomStack() : mHead(nullptr) {}

            ~CustomStack() {
                while (mHead != nullptr) {
                    ListNode* temp = mHead;
                    mHead = mHead->mNext;
                    delete temp;
                }
            }
    	    void push(int data) {
                ListNode* newNode = new ListNode;
                newNode->mData = data;
                newNode->mNext = mHead;
                mHead = newNode;
            }
        	int top() {
                if (mHead != nullptr) {
                    return mHead->mData;
                }
                return -1; // стек пуст
            }
            void pop() {
                if (mHead != NULL) {
                    ListNode* temp = mHead;
                    mHead = mHead->mNext;
                    delete temp;
                } 
            }

            bool empty() {
                return mHead == nullptr;
            }
            int size() {
                int count = 0;
                ListNode* current = mHead;
                while (current != nullptr) {
                    count++;
                    current = current->mNext;
                }
                return count;
            }
    	protected:
        	ListNode* mHead;
};

int main() {
	CustomStack stk;
    char str[104];
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = ' ';
    str[strlen(str)] = '7';
    str[strlen(str) + 1] = '\0';
    char* t = strtok(str, " ");
    int ch;
    while(t){
        std::string token(t);
    	if ((token=="/")||(token=="+")||(token=="-")||(token=="*")){
    	    if(stk.size() < 2){
    	        cout<<"error";
                return 0;
    	    }
            ch=stk.top();
    	    stk.pop();
            if (token=="/"){
                ch=stk.top()/ch;
                stk.pop();
                stk.push(ch);
            }
            if (token=="*"){
                ch=stk.top()*ch;
                stk.pop();
    	        stk.push(ch);
    	    }
    	    if (token=="+"){
    	        ch=stk.top()+ch;
    	        stk.pop();
    	        stk.push(ch);
    	    }
    	    if (token=="-"){
    	        ch=stk.top()-ch;
    	        stk.pop();
    	        stk.push(ch);
    	    }
    	}
    	else{
            const char *c = token.c_str();
            stk.push(atoi(c));
    	}
    	t = strtok(NULL, " ");
    }
    stk.pop();
    if (stk.size()!=1){
        cout<<"error";
        return 0;
    }
    cout<<stk.top();
    return 0;
}
