#include <iostream>

class CustomStack {
    public:
        CustomStack(){
            mHead = NULL;
        }

        void push(int val){
            ListNode *prev = mHead;
            mHead = new ListNode();
            mHead->mNext = prev;
            mHead->mData = val;
            count++;
        }

        void pop(){
            if (count == 0){
                std::cout << "error" << std::endl;
                exit(0);
            }
            ListNode *prev = mHead;
            mHead = mHead->mNext;
            delete prev;
            count--;
        }
        
        size_t size(){
            return count;
        }

        bool empty(){
            return count == 0;
        }

        int top(){
            if (count == 0){
                std::cout << "error" << std::endl;
                exit(0);
            }
            return mHead->mData;
        }
    

    private:
        size_t count = 0;


    protected:
        struct ListNode {
            ListNode *mNext;
            int mData;
        };
        ListNode *mHead;
};

int main(){
    CustomStack stack;
    std::string command;
    while (command != "cmd_exit"){
        std::cin >> command;
        if (command == "cmd_push"){
            int num;
            std::cin >> num;
            stack.push(num);
            std::cout << "ok" << std::endl;
        }
        else if (command == "cmd_pop"){
            std::cout << stack.top() << std::endl;
            stack.pop();
        }
        else if (command == "cmd_top"){
            std::cout << stack.top() << std::endl;
        }
        else if (command == "cmd_size"){
            std::cout << stack.size() << std::endl;
        }
    }
    std::cout << "bye" << std::endl;
    return 0;
}
