class CustomStack {
public:
    CustomStack(){ //конструктор
        mHead = nullptr;
    };
    void push(const char* str){
        ListNode* newnode = new ListNode;
        newnode->mData = new char[strlen(str) + 1];
        strcpy(newnode->mData, str);
        newnode->mNext = mHead;
        mHead = newnode;
    };
    void pop(){
        ListNode* out= mHead;
        mHead = mHead->mNext;
        delete[] out->mData;
        delete out;
    }
    size_t size(){
        size_t c = 0;
        ListNode* ptr = mHead;
        while(ptr != nullptr){
            c++;
            ptr = ptr->mNext;
        }
        return c;
    }
    bool empty(){
        return mHead == nullptr;
    }
    char* top(){
        if (mHead != nullptr){
            return mHead->mData;
        }
        return nullptr;
    }
    ~CustomStack(){
        while(!empty()) pop();
    }
// методы push, pop, size, empty, top + конструкторы, деструктор
private:
// поля класса, к которым не должно быть доступа извне
protected:  // в этом блоке должен быть указатель на голову
    ListNode* mHead;
};
int main() {
    char* str = new char [3001];
    std::cin.getline(str, 3001);
    str[strlen(str)] = '\0';
   // printf("[%s]", str);
    CustomStack mystack;
    int flag = 0;
    for (int i=0; i<strlen(str); i++){
        if (str[i] == '<'){
            if (str[i+1] == '/' && mystack.empty() == 1){
                flag =-1;
                break;
            }
            else if(str[i+1] == '/'){
                for (int j=i+2; j<strlen(str); j++){
                    if (str[j] == '>'){
                        int l = j-(i+1);
                        char* rr = new char[l];
                        strncpy(rr, str+i+2, l-1);
                        rr[l-1] = '\0';
                        //printf("/[%s]\n", rr);
                        if (strcmp(rr, mystack.top()) == 0) mystack.pop();
                        free(rr);
                        break;
                    }

                }
            }
            //основной проход добавления
            else {
                for (int j=i+1; j<strlen(str); j++){
                    if (str[j] == '>'){
                        int l = j-i;
                        char* rr = new char[l];
                        strncpy(rr, str+i+1, l-1);
                        rr[l-1] = '\0';
                        //printf("[%s]\n", rr);
                        if (strcmp(rr, "br") != 0 && strcmp(rr, "hr") != 0) mystack.push(rr);
                        free(rr);
                        break;
                    }
                }
            }

        }
    }

    if (flag != -1 && mystack.empty() == 1) printf("%s", "correct");
    else printf("%s", "wrong");

}
