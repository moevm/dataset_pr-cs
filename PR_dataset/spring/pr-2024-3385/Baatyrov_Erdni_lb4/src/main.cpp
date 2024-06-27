class CustomStack {
    public:
        CustomStack() {
            mData = new int[10];
        }
        void push(int val) {
            if (stack_size == max_size) {
                extend(10);
            }
            mData[stack_size] = val;
            stack_size++;
        }
        void pop() {
            if (!empty()) stack_size--;
            else {
              try {
                throw std::runtime_error("Произошла ошибка");
            } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
            }
        }
        int top() {
            if (!empty()) return (mData[stack_size - 1]);
            else {
              cout << "error";
              exit(0);
            }
        }
        size_t size() {
            return stack_size;
        }
        bool empty() {
            return (stack_size == 0);
        }
        void extend(int n) {
            int* new_data = new int[max_size + n];
            for (int i = 0; i < stack_size; ++i) {
                new_data[i] = mData[i];
            }
            delete[] mData;
            mData = new_data;
            max_size += n;
        }
        ~CustomStack(){
            delete[] mData;
        }
    protected:
        int* mData;
        int max_size = 10;
        int stack_size = 0;
};

int main() {
    CustomStack stac = CustomStack();
    string input;
    int x, y, z;
    while (cin >> input) {
        if (input == "+") {
            x = stac.top();
            stac.pop();
            y = stac.top();
            stac.pop();
            stac.push(x + y);
        }
        else if (input == "-") {
            x = stac.top();
            stac.pop();
            y = stac.top();
            stac.pop();
            stac.push(y - x);
        }
        else if (input == "*") {
            x = stac.top();
            stac.pop();
            y = stac.top();
            stac.pop();
            stac.push(x * y);
        }
        else if (input == "/") {
            x = stac.top();
            stac.pop();
            y = stac.top();
            stac.pop();
            stac.push(y / x);
        }
        else {
            z = 0;
            try {
                int z = std::stoi(input);
                stac.push(z);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
                return 1;
            } catch (const std::out_of_range& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
                return 1;
            }
        }
    }
    if (stac.size() != 1){
        cout << "error";
        return 0;
    }
    cout << stac.top() << '\n';
    return 0;
}
