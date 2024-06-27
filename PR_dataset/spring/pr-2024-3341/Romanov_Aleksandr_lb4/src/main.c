#include <iostream>
#include <cstring>
#include <string>
#define STRING_SIZE 50


class CustomStack {

private:

    size_t number_of_elements = 0;
    ListNode* previous_element;


public:

    CustomStack(){
        this->mHead = nullptr;
    }

    ~CustomStack(){
        delete this->mHead;
    }

    void push(int val){
        if (number_of_elements == 0){
            ListNode *object = new ListNode;
            object->mData = val;
            object->mNext = nullptr;
            mHead = object;
            previous_element = object;

        }
        else{
            ListNode *object = new ListNode;
            object->mData = val;
            object->mNext = nullptr;
            previous_element->mNext = object;
            previous_element = object;
        }

        number_of_elements++;
    }

    void pop(){
      
        if(number_of_elements > 0){
            
            std::cout << previous_element->mData << std::endl;
            delete previous_element;

            if(number_of_elements == 1){
                mHead = nullptr;
            }
            else{
                ListNode* ptr = mHead;
                while(1){
                    if(ptr->mNext == previous_element){
                        previous_element = ptr;
                        break;
                    }
                    else{
                        ptr = ptr->mNext;
                    }
                }
            }
            number_of_elements--;
        }
        else{
            std::cout << "error" << std::endl;
            exit(0);
        }

        
    }

    int top(){
        if(number_of_elements > 0){
            return previous_element->mData;
        }
        else{
            std::cout << "error" << std::endl;
            exit(0);
        }
    }

    size_t size(){
        return number_of_elements;
    }

    bool empty(){
        return number_of_elements == 0;
    }

    void quit(){
        std::cout << "bye";
        exit(0);
    }

protected:
    ListNode* mHead;
};

int main() {
    CustomStack stack;
    
    while(1){
        char input[STRING_SIZE];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strstr(input, "cmd_push")){
            int element = std::stoi(strstr(input, " ")+1);
            stack.push(element);
            std::cout << "ok" << std::endl;
        }

        if (strstr(input, "cmd_pop")){
            stack.pop();
        }

        if (strstr(input, "cmd_top")){
            std::cout << stack.top() << std::endl;
        }

        if (strstr(input, "cmd_size")){
            std::cout << stack.size() << std::endl;
        }

        if(strstr(input, "cmd_empty")){
            std::cout << stack.empty() << std::endl;
        }

        if(strstr(input, "cmd_exit")){
            stack.quit();
        }
    }
    return 0;
}
