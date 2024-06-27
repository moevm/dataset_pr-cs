#include <iostream>
#include <sstream>
#include <string>

class CustomStack {
public:
  CustomStack()
      : mData(new int[INITIAL_CAPACITY]), mCapacity(INITIAL_CAPACITY),
        mSize(0) {}

  ~CustomStack() { delete[] mData; }

  void push(int val) {
    if (mSize >= mCapacity) {
      std::cout << "error" << std::endl;
      return;
    }
    mData[mSize++] = val;
  }

  void pop() {
    if (empty()) {
      std::cout << "error" << std::endl;
      return;
    }
    --mSize;
  }

  int top() const {
    if (empty()) {
      std::cout << "error" << std::endl;
      return -1;
    }
    return mData[mSize - 1];
  }

  size_t size() const { return mSize; }

  bool empty() const { return mSize == 0; }

  void extend(int n) {
    int newCapacity = mCapacity + n;
    int *newData = new int[newCapacity];
    for (size_t i = 0; i < mSize; ++i) {
      newData[i] = mData[i];
    }
    delete[] mData;
    mData = newData;
    mCapacity = newCapacity;
  }

protected:
  int *mData;

private:
  static const int INITIAL_CAPACITY = 100;
  static const int EXTENSION_SIZE = 10;
  size_t mCapacity;
  size_t mSize;
};

bool is_operator(const std::string &str) {
  return str == "+" || str == "-" || str == "*" || str == "/";
}

int main() {
  CustomStack stack;

  std::string input;
  std::getline(std::cin, input);
  std::istringstream iss(input);
  std::string word;

  while (iss >> word) {
    if (is_operator(word)) {
      if (stack.size() < 2) {
        std::cout << "error" << std::endl;
        return 1;
      }
      int operand2 = stack.top();
      stack.pop();
      int operand1 = stack.top();
      stack.pop();

      int result;
      if (word == "+")
        result = operand1 + operand2;
      else if (word == "-")
        result = operand1 - operand2;
      else if (word == "*")
        result = operand1 * operand2;
      else if (word == "/") {
        if (operand2 == 0) {
          std::cout << "error" << std::endl;
          return 1;
        }
        result = operand1 / operand2;
      }

      stack.push(result);
    } else {
      if (word == "error") {
        std::cout << "error" << std::endl;
        return 1;
      }
      stack.push(std::stoi(word));
    }
  }

  if (stack.size() != 1) {
    std::cout << "error" << std::endl;
    return 1;
  }

  std::cout << stack.top() << std::endl;

  return 0;
}