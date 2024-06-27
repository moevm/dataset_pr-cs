#define SIZE 8

class CustomStack {
public:
    CustomStack() {
        mData = new char *[SIZE];
        lastIndex = -1;
        maxSize = SIZE;
    }

    ~CustomStack() {
        delete[] mData;
    }

    void push(const char *value) {
        ++lastIndex;
        if (lastIndex == maxSize - 1) extend();
        mData[lastIndex] = new char[strlen(value) + 1];
        strcpy(mData[lastIndex], value);
    }

    char *pop() {
        return lastIndex == -1 ? nullptr : mData[lastIndex--];
    }

    char *top() {
        return lastIndex == -1 ? nullptr : mData[lastIndex];
    }

    size_t size() {
        return lastIndex + 1;
    }

    bool empty() {
        return lastIndex == -1;
    }
private:
    void extend() {
        int additionalSize = 8;
        char **newData = new char *[maxSize + additionalSize];
        for (size_t i = 0; i < size(); ++i) newData[i] = mData[i];
        delete[] mData;
        mData = newData;
        maxSize += additionalSize;
    }
protected:
    char **mData;
    int lastIndex;
    size_t maxSize;
};

bool checkFunction(string someHtmlCode) {
    size_t firstBracket = someHtmlCode.find('<');
    size_t secondBracket = someHtmlCode.find('>');
    CustomStack stack;
    for (; firstBracket != string::npos && secondBracket != string::npos;) {
        string subString = someHtmlCode.substr(firstBracket + 1, secondBracket - firstBracket - 1);
        if (subString == "br" || subString == "hr") {
            firstBracket = someHtmlCode.find('<', firstBracket + 1);
            secondBracket = someHtmlCode.find('>', secondBracket + 1);
            continue;
        }
        if (subString[0] != '/') {
            stack.push(subString.c_str());
            firstBracket = someHtmlCode.find('<', firstBracket + 1);
            secondBracket = someHtmlCode.find('>', secondBracket + 1);
            continue;
        }
        if (stack.empty()) {
            return false;
        }
        string prevTag = stack.pop();
        if ('/' + prevTag != subString) {
            return false;
        }
        firstBracket = someHtmlCode.find('<', firstBracket + 1);
        secondBracket = someHtmlCode.find('>', secondBracket + 1);
    }
    return true;
}

int main() {
    string someHtmlCode;
    getline(cin, someHtmlCode);
    if (checkFunction(someHtmlCode)) {
        cout << "correct" << endl;
    } else cout << "wrong" << endl;
    return 0;
}