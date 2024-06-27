class CustomStack {
public:

    CustomStack(){
        mHead = nullptr;
    }
    CustomStack(ListNode* headElem){
        mHead = headElem;
    }
    
    void push(int val){
        ListNode* newElem = new ListNode;

        if (newElem == nullptr) {
            cerr << "Ошибка выделения памяти!\n";
            exit(1);
        }

        newElem->mData = val;
        newElem->mNext = mHead;

        mHead = newElem;

    }

    void pop(){

        ListNode* headNode = mHead;
        
        if (headNode == nullptr) 
            return;
            
        mHead = mHead->mNext;
        
        delete headNode;   
    }

    int top(){
        return mHead->mData;
    }

    size_t size(){
        int count = 0;

        ListNode* currentElement = mHead;

        if (currentElement == nullptr) return count;

        while (currentElement != nullptr){
            currentElement = currentElement->mNext;
            count++;
        }

        return count;
    }

    bool empty(){
        return mHead == nullptr;
    }

    ~CustomStack()
    {
        while(!empty())
        {
            pop();
        }
    }
    
protected:
    ListNode* mHead;
};


int main(){
    using namespace std;

    CustomStack myStack;

    string currWord;

        while (cin >> currWord){
        
        if (currWord == "cmd_push") {
            int nodeData;
            cin >> nodeData;

            myStack.push(nodeData);
            
            cout << "ok\n";

        } else if (currWord == "cmd_pop"){
            if (!myStack.empty()){
                cout << myStack.top() << '\n';
                myStack.pop();
            } else {
                cout << "error" << '\n';
                break;
            }
            
        } else if (currWord == "cmd_size"){

            cout << myStack.size() << "\n";

        } else if(currWord == "cmd_top"){
            if (!myStack.empty()){
                cout << myStack.top() <<'\n';
            } else {
                cout << "error";
                break; 
            }
        } else if(currWord == "cmd_exit"){
            cout << "bye\n";
            break;
        }
    
    }
    
    return 0;
}