#define CHUNK 1
#define CAPACITY_ERR_MSG "New capacity is smaller than the size of the stack!"
#define POP_EMPTY_STACK_ERR_MSG "You can't pop an empty stack, silly!!!"
#define TOP_EMPTY_STACK_ERR_MSG "You can't peek at the top value since the stack is empty, what a fool you are..."
#define ERROR_MSG "error"
#define LEFT_FACING_CHEVRON '<'
#define RIGHT_FACING_CHEVRON '>'
#define EMPTY_STRING ""
#define CLOSING_TAG_SLASH '/'
#define BR_TAG "br"
#define HR_TAG "hr"
#define WRONG_RESULT_MSG "wrong"
#define CORRECT_RESULT_MSG "correct"

class CustomStack {
public:
    CustomStack() {
        
        mCapacity = 1;
        mLen = 0;
        mData = new char *[mCapacity];
    }
    
    ~CustomStack() {
        delete[] mData;
    }
    
    void extend(int n) {
        char **tmpData = new char *[mCapacity + n];
        
        if (mCapacity + n < mLen)
            this->throwError(CAPACITY_ERR_MSG);
        
        mCapacity += n;
        memcpy(tmpData, mData, sizeof(char *) * mCapacity);
        delete[] mData;
        mData = tmpData;
    }
    
    void push(const char *val) {
        if (mLen >= mCapacity) {
            extend(CHUNK);
        }
        
        mData[mLen] = new char[strlen(val) + 1];
        strcpy(mData[mLen], val);
        mLen += 1;
    }
    
    void pop() {
        if (this->empty()) 
            this->throwError(POP_EMPTY_STACK_ERR_MSG); 
            
        mData[--mLen] = nullptr;
        extend(-1);
    }
    
    char *top() {
        if (this->empty()) 
            this->throwError(TOP_EMPTY_STACK_ERR_MSG);
            
        return mData[mLen - 1];
    }
    
    size_t size() {
        return mLen;
    }
    
    bool empty() {
        return mLen <= 0;
    }

private:
    size_t mLen;
    size_t mCapacity;
    
    void throwError() {
        std::cout << ERROR_MSG << std::endl;
        exit(0);
    }
    
    void throwError(const char *text) {
        std::cout << ERROR_MSG << ", " << text << std::endl;
        exit(0);
    }

protected:
    char** mData;
};

std::string getTag(const std::string html, size_t &pos) {
    size_t start = html.find(LEFT_FACING_CHEVRON, pos);
    size_t end = html.find(RIGHT_FACING_CHEVRON, pos);
    size_t len;
    
    std::string rawTag;
    if (end > start && start != std::string::npos && end != std::string::npos) {
        len = end - start + 1;
        rawTag = html.substr(start, len);
        
        pos = end + 1;
    } else {
        pos = std::string::npos;
        
        return std::string(EMPTY_STRING);
    }
    
    std::string tag = rawTag.substr(1 , rawTag.length() - 2);
    return tag;
}

bool isClosingTag(const std::string tag) {
    return (tag.at(0) == CLOSING_TAG_SLASH);
}

bool isOpeningTag(const std::string tag) {
    return (tag.at(0) != CLOSING_TAG_SLASH);
}

bool isPairTag(const std::string tag) {
    return (tag != BR_TAG && tag != HR_TAG); 
}

bool checkTag(const std::string closingTag, CustomStack &stk) {
    return (CLOSING_TAG_SLASH + std::string(stk.top()) == closingTag);
}

void processTag(const std::string tag, CustomStack &stk) {
    if (!isPairTag(tag)) { 
        return;
    }
        
    if (isOpeningTag(tag)) {
        char *arr = new char[tag.length() + 1];
        strcpy(arr, tag.c_str());
        stk.push(arr);
    }
        
    if (isClosingTag(tag)) {
        if (!checkTag(tag, stk)) {
            std::cout << WRONG_RESULT_MSG << std::endl;
            exit(0);
        }
        
        stk.pop();
    }
}

void processHtml(const std::string html, CustomStack &stk) {
    std::string tag;
    size_t buf = 0;
    
    tag = getTag(html, buf);
    while (tag != EMPTY_STRING) {
        processTag(tag, stk);
        
        tag = getTag(html, buf);
    }
    
    if (stk.empty())
        std::cout << CORRECT_RESULT_MSG << std::endl;
    else
        std::cout << WRONG_RESULT_MSG << std::endl;
}

int main() {
    CustomStack stk;
    
    std::string html;
    getline(std::cin, html);
    
    processHtml(html, stk);
    return 0;
}
