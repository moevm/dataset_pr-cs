#include <iostream>

class CustomStack {
	public:
		CustomStack(){
			mData = new int[0];
			length = 0;
		}

		~CustomStack(){
			delete[] mData;
		}

		void push(int val){
			extend(1);
			mData[length-1] = val;
		}

		void pop(){
			extend(-1);
		}

		int top(){
			return mData[length-1];
		}

		size_t size(){
			return length;
		}

		void extend(int n) {
    		int* newData = new int[length + n];
    		for (int i = 0; i < length; ++i) {
        		newData[i] = mData[i];
    		}
    		delete[] mData;
    		mData = newData;
    		length += n;
		}

		bool empty(){
			if(length == 0) return true;
			return false;
		}
	protected:
    	int* mData;
		int length;
};

void processing() {
	CustomStack stack;
	std::string cmd;
	int value;

	while(true){
		std::cin >> cmd;

		if(cmd == "cmd_push"){
			std::cin >> value;
			stack.push(value);
			std::cout << "ok" << std::endl;
		} else if(cmd == "cmd_top"){
			if(stack.empty()){
				std::cout << "error" << std::endl;
				break;
			} else{
				std::cout << stack.top() << std::endl;
			}
		} else if(cmd == "cmd_pop"){
			if(stack.empty()){
				std::cout << "error" << std::endl;
				break;
			} else{
				std::cout << stack.top() << std::endl;
				stack.pop();
			}
		} else if(cmd == "cmd_size"){
			std::cout << stack.size() << std::endl;
		} else if(cmd == "cmd_exit"){
			std::cout << "bye" << std::endl;
			break;
		} else{
			std::cout << "error" << std::endl;
			break;
		}
	}
}

int main() {
	processing();
    return 0;
}