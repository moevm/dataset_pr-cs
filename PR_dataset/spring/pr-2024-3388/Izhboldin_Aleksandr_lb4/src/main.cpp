#define TAG_MAXSIZE 3000
#define TAG_BLACKLIST "br", "hr"

class CustomStack
{
    size_t len = 0;
public:
    CustomStack() = default;


    void push(const char *tag)
    {
        ListNode *node = new ListNode;
        node->mData = (char *) tag;
        node->mNext = nullptr;

        if (this->mHead) {
            ListNode *it = this->mHead;
            while (it->mNext)
                it = it->mNext;
            it->mNext = node;
        } else {
            this->mHead = node;
        }

        this->len++;
    }

    size_t size()
    {
        return this->len;
    }

    bool empty()
    {
        return size() == 0;
    }

    char *top()
    {
        if (empty()) return nullptr;
        ListNode *it = this->mHead;
        while (it->mNext)
            it = it->mNext;
        return it->mData;
    }

    void pop()
    {
        if (empty()) return;
        ListNode *it = this->mHead;
        if (!it->mNext) {
            delete it;
            this->mHead = nullptr;
        } else {
            while (it->mNext && it->mNext->mNext != nullptr)
                it = it->mNext;
            delete it->mNext;
            it->mNext = nullptr;
        }
        this->len--;
    }

    ~CustomStack()
    {
        while (!empty())
            pop();
    }

protected:
    ListNode *mHead = nullptr;
};

// return only name without braces
char *read_tag()
{
    char *str = new char[TAG_MAXSIZE];
    char c;
    while (true) { // find start
        c = (char) getchar();
        if (c == '<') break;
        if (c == EOF) {
            delete[] str;
            return nullptr;
        }
    }

    size_t it = 0;
    while (true) { // find end
        c = (char) getchar();
        if (c == '>') break;
        if (c == EOF) {
            delete[] str;
            return nullptr;
        }
        str[it] = c;
        it++;
    }
    str[it] = '\0';
    return str;
}

bool is_single_tag(char *str)
{
    char blacklist[][TAG_MAXSIZE] = {TAG_BLACKLIST};
    for (auto &i: blacklist) {
        if (!strcmp(str, i)) {
            delete[] str;
            return true;
        }
    }
    return false;
}

bool check_text()
{
    CustomStack stack;
    while (true) {
        char *str = read_tag();
        if (!str) break;

        if (is_single_tag(str)) continue;

        if (str[0] != '/')
            stack.push(str);
        else if (str[0] == '/' && stack.top() && !strcmp((str + sizeof(char)), stack.top()))
            stack.pop();
        else
            return false;
    }
    return true;
}


int main()
{
    if (check_text()) cout << "correct";
    else cout << "wrong";
    return EXIT_SUCCESS;
}
