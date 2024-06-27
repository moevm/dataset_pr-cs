#include <iostream>
#include <string>
#include <cstring> // Для функции strtok
#include <cstdlib> // Для функции exit
#include <sstream>

class CustomStack {
public:
    CustomStack(){
        mSize=0; //кол-во эл-тов в стеке
        mCapacity=100; //размер массива данных стека
        mData=new int[mCapacity]; // указатель на массив целых чисел
    }
    ~CustomStack(){
        delete[] mData;
    }

    void push(int val) {
        if (mSize == mCapacity) {
            extend(100); // Расширяем массив при необходимости
        }
        mData[mSize++] = val;
    }

     void pop() {
        if (mSize == 0) {
            std::cout << "error" << std::endl;
            exit(1); // Завершить программу с кодом ошибки
         }
        if (mSize > 0) {
            --mSize;
        }
    }

    int top(){
        if (empty()) {
            std::cout << "error" << std::endl;
            exit(1);
        }
        return mData[mSize - 1];
    }

    bool empty(){
        return mSize == 0;
    }

    size_t size() {
        return mSize;
    }

    void extend(int n) {
        int* newData = new int[mCapacity + n];
        for (size_t i = 0; i < mSize; ++i) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mData = newData;
        mCapacity += n;
    }

protected:
    int *mData;

private:
    size_t mSize;
    size_t mCapacity;
};
int main() {
    CustomStack stack;

    char str[101];
    fgets(str, 100, stdin);
    char *token = strtok(str, " \n");
    while (token) {
        std::string tokens(token, strlen(token));
        if (tokens == "+" || tokens == "-" || tokens == "*" || tokens == "/") {
            if (stack.size() < 2) {
                std::cout << "error" << std::endl;
                return 0;
            }
            int num1 = stack.top();
            stack.pop();
            int num2 = stack.top();
            stack.pop();
            int result;

            switch (tokens[0]) {
                case '+':
                    result = num2 + num1;
                    break;
                case '-':
                    result = num2 - num1;
                    break;
                case '*':
                    result = num2 * num1;
                    break;
                case '/':
                    if (num1 == 0) {
                        std::cout << "error" << std::endl;
                        return 0;
                    }
                    result = num2 / num1;
                    break;
            }
            stack.push(result);    
        } else {
            stack.push(std::stoi(tokens));
        }
        token = strtok(NULL, " \n");
    }

    if (stack.size() != 1) {
        std::cout << "error" << std::endl;
        return 0;
    }

    std::cout << stack.top() << std::endl;

    return 0;
}
