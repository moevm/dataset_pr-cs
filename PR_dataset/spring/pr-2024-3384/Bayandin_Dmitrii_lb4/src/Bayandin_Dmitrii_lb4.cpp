class CustomStack {
private:
    int size_data;
    int memory;

public:
    CustomStack(){
        memory = 100;
        mData = new int[memory];
        size_data = 0;
    }

    ~CustomStack(){
        delete[] mData;
    }

    void extend(int n){
        memory += n;
        int* newData = new int [memory];
        for(int i = 0; i < size_data; i++){
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
    }
 
    void push(int element){
        mData[size_data] = element;
        size_data++;
        if(size_data + 1 == memory){
            extend(memory);
        }
    }
    bool empty(){
        return size_data == 0;
    }

    void pop(){
        size_data -= 1;
    }
    int top(){
        return mData[size_data-1];
    }
    size_t size(){
        return size_data;
    }
protected:
    int* mData;
};

int main(){
    CustomStack stck;
    string command;
    int n;
    while(1){
        cin >> command;
        if(command == "cmd_push"){
            cin >> n;
            stck.push(n);
            cout << "ok\n";
        }
        else if(command == "cmd_pop"){
            if(stck.empty() == 1){
                cout << "error\n";
                exit(0);
            }
            cout << stck.top() << "\n";
            stck.pop();
        }
        else if(command == "cmd_top"){
            if(stck.empty() == 1){
                cout << "error\n";
                exit(0);
            }
            cout << stck.top() << "\n";      
        }
        else if(command == "cmd_size"){
            cout << stck.size() << "\n";
        }
        else if(command == "cmd_exit"){
            cout << "bye";
            exit(0);
        }

    }
    return 0;
}
