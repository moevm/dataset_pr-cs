#include <iostream>
#include <cstring>

class CustomStack {
public:

    CustomStack() {
        this->mData = new char *;
        top_elem = -1;
    }

    ~CustomStack() {
        delete[] mData;
    }

    void push(const char *val) {
        this->mData[++top_elem] = new char[strlen(val) + 1];
        strcpy(mData[top_elem], val);
    }

    void pop() {
        if (top_elem >= 0) {
            delete[] mData[top_elem];
            top_elem--;
        }
    }

    char *top() {
        if (top_elem >= 0) {
            return mData[top_elem];
        }
        return nullptr;
    }

    size_t size() {
        return top_elem + 1;
    }

    bool empty() {
        return top_elem == -1;
    }

    void extend(int n) {
        char **temp = new char *[size() + n];
        for (size_t i = 0; i < size(); i++) {
            temp[i] = mData[i];
        }
        delete[] mData;
        mData = temp;
    }

protected:
    char **mData;
private:
    int top_elem;
};

bool is_valid_html(const char *code) {
    CustomStack stack;
    const char *p = code;
    while (*p) {
        if (*p == '<') {
            if (*(p + 1) == '/') {
                if (stack.empty()) {
                    return false;  // нет открывающего тега для закрывающего
                }
                const char *top = stack.top();
                char *tag_name = strdup(p + 2);
                const char *end_tag_name = strchr(tag_name, '>');
                char *value = strndup(tag_name, end_tag_name - tag_name + 1);
                if (strcmp(top + 1, value) == 0) {
                    stack.pop();
                } else {
                    return false;  // несоответствие открывающего и закрывающего тегов
                }
            } else {
                if (strncmp(p, "<br>", 4) == 0 || strncmp(p, "<hr>", 4) == 0) {

                } else {
                    const char *tag_name = p;
                    const char *end_tag = strchr(tag_name, '>');
                    stack.push(strndup(tag_name, end_tag - tag_name + 1));
                }
            }
        }
        p++;
    }
    return stack.empty();  // если стек пуст, то все теги закрыты верно
}

int main() {
    char str[3001];
    std::cin.getline(str, 3001);
    str[strlen(str)] = '\0';
    bool a = is_valid_html(str);
    if (a) {
        std::cout << "correct\n";
    } else {
        std::cout << "wrong\n";
    }

    return 0;

}