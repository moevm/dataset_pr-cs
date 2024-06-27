#define BUFFER_SIZE 10

class CustomStack {
public:
    CustomStack() {
        top_index = -1;
        capacity = BUFFER_SIZE;
        mData = new char*[capacity];
    }

    void push(const char* val) {
        top_index++;
        if (top_index >= capacity) {
            extend(BUFFER_SIZE);
        }
        mData[top_index] = new char[strlen(val) + 1];
        strcpy(mData[top_index], val);
    }

    void pop() {
        delete[] mData[top_index];
        top_index--;
    }

    char* top() {
        return mData[top_index];
    }

    size_t size() {
        return top_index + 1;
    }

    bool empty() {
        return top_index == -1;
    }

    ~CustomStack() {
        for (int i = 0; i <= top_index; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
    }

protected:
    char** mData;

private:
    int top_index;
     size_t capacity;

    void extend(int n) {
        capacity += n;
        char** new_stack_data = new char*[capacity];
        memcpy(new_stack_data, mData, (top_index + 1) * sizeof(char*));
        delete[] mData;
        mData = new_stack_data;
    }
};

bool isValidHTMLString(std::string line) {
    CustomStack stack;
    size_t left_index = line.find('<');
    size_t right_index = line.find('>');

    while (left_index != std::string::npos || right_index != std::string::npos) {
        std::string tag = line.substr(left_index + 1, right_index - left_index - 1);

        if (tag[0] != '/' && tag != "br" && tag != "hr") {
            stack.push(tag.c_str());
        } else if (tag != "br" && tag != "hr") {
            if (stack.empty()) {
                return false;
            }
            char* prev_tag = stack.top();
            if (strcmp(prev_tag, tag.c_str() + 1) != 0) {
                return false;
            }
            stack.pop();
        }

        line = line.substr(right_index + 1);
        left_index = line.find('<');
        right_index = line.find('>');
    }

    return stack.empty();
}

int main() {
    std::string line;
    std::getline(std::cin, line);

    if (isValidHTMLString(line)) {
        std::cout << "correct";
    } else {
        std::cout << "wrong";
    }

    return 0;
}