class CustomStack {
protected:
    int* mData;
    
private:
    static constexpr int INITIAL_CAPACITY = 16;
    int stack_size, top_ind;
    
public:
    CustomStack(){
		top_ind = 0;
		stack_size = INITIAL_CAPACITY;
		mData = new int[stack_size];
	}
	
	~CustomStack(){
		delete[] mData;
	}
	
	void push(int val){
		if(stack_size == top_ind){
			extend(INITIAL_CAPACITY);
		}
		mData[top_ind++] = val;
	}

	void pop(){
        --top_ind;
    }

	int top(){
		if(!empty()) {
		return mData[top_ind - 1];
		}
	}
	
	size_t size(){
		return top_ind;
	}
	
	bool empty(){
		return top_ind == 0;
	}
	
	void extend(int n){
        int *new_mData = new int[stack_size + n];
        copy(mData, mData + top_ind, new_mData);
        delete[] mData;
        mData = new_mData;
        stack_size += n;
    }
};

int main(){
    string cmd;
    CustomStack new_stack;
    while(cin >> cmd){
        if(cmd == "cmd_push"){
            int n; cin >> n;
            new_stack.push(n);
            cout << "ok\n";
        }else if(cmd == "cmd_pop"){
            if(new_stack.empty()){
                cout << "error\n";
                return 1;
            }
            cout << new_stack.top() << "\n";
            new_stack.pop();
        }else if(cmd == "cmd_top"){
            if(new_stack.empty()){
                cout << "error\n";
                return 2;
            }
            cout << new_stack.top() << "\n";
        }else if(cmd == "cmd_size"){
            cout << new_stack.size() << "\n";
        }else if(cmd == "cmd_exit"){
            cout << "bye\n";
            return 0;
        }
    }
    return 0;
}

