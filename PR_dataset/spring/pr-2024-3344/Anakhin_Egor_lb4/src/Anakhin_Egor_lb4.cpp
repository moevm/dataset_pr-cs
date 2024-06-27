class CustomStack {

    public: 

        bool push(int number) {
            if (!isFull()) {
                mData[leng++] = number;
                return true;
            }
            return false; 
        };

        bool pop() {
            if (size() == 0) {
                std::cout << "error";
                return false;
            }
            leng--;
            return true;
        };

        int top() {
            if (isEmpty()) {
                std::cout << "error";
                return 0;
            }
            return mData[leng-1];
        };

        bool isEmpty() {
            return leng == 0;
        }

        bool isFull() {
            return leng == capacity;
        };

        size_t size() {
            return leng;
        };

        void extend(int newLength) {
            int* newArray = new int[newLength];

            for (int i = 0; i < leng && i < newLength; i++) {
                newArray[i] = mData[i];
            }
            
            delete[] mData;
            mData = newArray;
            capacity = newLength;
        };

        CustomStack() {
            capacity = 100;
            leng = 0;
            mData = new int[capacity];
        }

        ~CustomStack() {
            delete[] mData;
        };

        bool makeMath(char operation) {
            if (size() < 2) {
                return false;
            }

            int num2 = top();
            pop();
            int num1 = top();
            pop();
            int newNum;

            if (num2 == 0 || num1 == 0) {
                return false;
            }

            switch (operation)
            {
            case '/':
                newNum = num1 / num2;
                break;
            case '*':
                newNum = num1 * num2;
                break;
            case '+':
                newNum = num1 + num2;
                break;
            case '-':
                newNum = num1 - num2;
                break;
            default:
                return false;
                break;
            }

            push(newNum);
            return true;
        };

    protected:
        int* mData;


    private: 
        int leng;
        int capacity;

};

int main() {

    CustomStack stack;

    std::string line;
    std::getline(std::cin, line);
    line.push_back('\0');

    char* str = &line[0];
    char* token = std::strtok(str, " ");

    while (token != nullptr) {
        try {
            int number = std::stoi(token);
            stack.push(number);
        } catch(std::invalid_argument) {
            bool isCorrect = stack.makeMath(token[0]);
            if (!isCorrect) {
                std::cout << "error";
                return 0;
            }
        }
        token = std::strtok(nullptr, " ");
    }

    if (stack.size() != 1) {
        std::cout << "error";
        return 0;
    }

    std::cout << stack.top() << std::endl;

    return 0;

}


