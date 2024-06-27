#include <cstring>
#include <iostream>

class CustomStack {
public:
    CustomStack()
        : mHead(nullptr)
        , mSize(0)
    {
    }

    ~CustomStack()
    {
        while (!empty()) {
            pop();
        }
    }

    void push(const char* tag)
    {
        ListNode* newNode = new ListNode;
        newNode->mData = new char[strlen(tag) + 1];
        strcpy(newNode->mData, tag);
        newNode->mNext = mHead;
        mHead = newNode;
        ++mSize;
    }

    void pop()
    {
        if (!empty()) {
            ListNode* temp = mHead;
            mHead = mHead->mNext;
            delete[] temp->mData;
            delete temp;
            --mSize;
        }
    }

    char* top()
    {
        if (!empty()) {
            return mHead->mData;
        } else {
            std::cerr << "Error: Stack is empty\n";
            exit(EXIT_FAILURE);
        }
    }

    size_t size()
    {
        return mSize;
    }

    bool empty()
    {
        return mSize == 0;
    }

private:
    size_t mSize;

protected:
    ListNode* mHead;
};

bool isValidHTML(const std::string& html)
{
    CustomStack stack;

    size_t i = 0;
    while (i < html.length()) {
        if (html[i] == '<') {
            size_t j = i + 1;
            while (j < html.length() && html[j] != '>') {
                ++j;
            }
            if (j == html.length()) {
                return false;
            }
            std::string tag = html.substr(i + 1, j - i - 1);
            if (tag[0] != '/') {
                if (tag != "br" && tag != "hr") {
                    stack.push(tag.c_str());
                }
            } else {
                if (stack.empty() || strcmp(stack.top(), &tag[1]) != 0) {
                    return false;
                }
                stack.pop();
            }
            i = j;
        }
        ++i;
    }

    return stack.empty();
}

int main()
{
    std::string html;
    std::getline(std::cin, html);

    if (isValidHTML(html)) {
        std::cout << "correct\n";
    } else {
        std::cout << "wrong\n";
    }

    return 0;
}
