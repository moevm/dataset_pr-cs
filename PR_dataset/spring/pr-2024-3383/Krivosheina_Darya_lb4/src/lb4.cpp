int flag = 0;

class CustomStack {
public:
    int count = 0;
    CustomStack(){
        mHead = nullptr;
    }
    void push(long val){
        struct ListNode *new_elem = new ListNode;
        new_elem->mData = val;
        new_elem->mNext = mHead;
        mHead = new_elem;
        count++;
    }
    void pop(){
        if (mHead == nullptr){
            flag = 1;
        } else {
            struct ListNode *tmp = mHead->mNext;
            delete mHead;
            mHead = tmp;
            count--;
        }
    }
    long top(){
        if (mHead == nullptr){
            flag = 1;
            return 0;
        } else {
            return mHead->mData;
        }
    }
    size_t size(){
        return count;
    }
    bool empty(){
        if (mHead == nullptr){
            return true;
        } else {
            return false;
        }
    }
    ~CustomStack(){
        while(!empty()) pop();
    }
protected:
    ListNode* mHead;
};

int main() {
    char str[101];
    fgets(str, 101, stdin);
    char *part = strtok(str, " ");
    CustomStack stack;
    while (part != nullptr){
        if (atoi(part) || strcmp(part, "0") == 0){
            stack.push(atoi(part));
        } else {
            long a = stack.top();
            stack.pop();
            long b = stack.top();
            stack.pop();
            if (flag == 1){
                std::cout<<"error\n";
                return 0;
            }
            if (strcmp(part, "+") == 0){
                stack.push(a + b);
            } else if (strcmp(part, "-") == 0){
                stack.push(b - a);
            } else if (strcmp(part, "*") == 0){
                stack.push(a * b);
            } else if (strcmp(part, "/") == 0){
                stack.push(b / a);
            }
        }
        part = strtok(nullptr, " \n");
    }
    if (stack.size() == 1){
        std::cout<<stack.top();
    } else {
        std::cout<<"error\n";
    }
    return 0;
}
