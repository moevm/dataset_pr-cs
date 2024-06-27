#include <iostream>

using namespace std;

class CustomStack{
public:
    CustomStack(){
        this->mSize = 0;
        this->mData = new int[this->mSize];
    }

    ~CustomStack(){
        delete this->mData;
    }

    void push(int obj){
        this->extend(1);
        this->mData[this->mSize-1] = obj;
    }

    void pop(){
        if(this->mSize == 0){
            throw 1;
        }
        this->extend(-1);
    }

    int top(){
        if(this->mSize == 0){
            throw 2;
        }
        return this->mData[this->mSize-1];
    }

    size_t size(){
        return (size_t)this->mSize;
    }

    bool empty(){
        return this->mSize == 0;
    }

    void extend(int n){
        if(this->mSize+n < 0){
            throw 3;
        }

        int* new_mData = new int[this->mSize+n];
        if(n < 0) {
            for (int i = 0; i < this->mSize-n; ++i) {
                new_mData[i] = this->mData[i];
            }
        } else {
            for (int i = 0; i < this->mSize; ++i) {
                new_mData[i] = this->mData[i];
            }
        }
        delete this->mData;
        this->mSize += n;
        this->mData = new_mData;
    }

private:
    int mSize;

protected:
    int* mData;
};

int main(){
    string command;
    CustomStack stack = CustomStack();
    do{
        cin >> command;
        try{
            if(command == "cmd_push"){
                int value;
                cin >> value;
                stack.push(value);
                cout << "ok" << endl;
            } else if(command == "cmd_pop"){
                cout << stack.top() << endl;
                stack.pop();
            } else if(command == "cmd_top"){
                cout << stack.top() << endl;
            } else if(command == "cmd_size"){
                cout << stack.size() << endl;
            } else if(command == "cmd_exit"){
                cout << "bye" << endl;
                exit(0);
            } else {
                throw 4;
            }
        }catch (int exp) {
            cout << "error" << endl;
            break;
        }


    }while(!command.empty());
}
