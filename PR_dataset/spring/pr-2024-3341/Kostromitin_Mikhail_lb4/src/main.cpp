#include <cstring>
#include <iostream>

using namespace std;

bool isValidHtml(char* html);
void gettag(char* input, char* dest);

class CustomStack {
public:
    CustomStack() {
        mData = new char *[10];
        mCapacity = 10;
        mSize = 0;
    }

    ~CustomStack() {
        for (int i = 0; i < mSize; i++){
            delete[] mData[i];
        }
        delete[] mData;
    }

    void
    push(const char *val) {
        if (mSize >= mCapacity) {
            extend(10);
        }

        mData[mSize] = new char[strlen(val) + 1];
        strcpy(mData[mSize], val);
        mSize++;
    }

    void
    pop() {
        if (mSize > 0) {
            delete[] mData[mSize - 1];
            mSize--;
        }
    }

    char *
    top() {
        if (mSize > 0) {
            return mData[mSize - 1];
        }
        return nullptr;
    }

    size_t
    size(){
        return mSize;
    }

    bool
    empty(){
        return (mSize == 0);
    }

    void
    extend(int n){
        mCapacity += n;
        char** tmp = new char*[mCapacity];
        for (int i = 0; i < mSize; i++){
            tmp[i] = mData[i];
        }
        delete[] mData;
        mData = tmp;
    }

private:
    int mSize;
    int mCapacity;

protected:
    char** mData;
};

int main() {
    char* input = new char[3001];
    fgets(input, 3000, stdin);
    if (isValidHtml(input)){
        cout << "correct";
    } else {
        cout << "wrong";
    }
    return 0;
}


void
gettag(char* input, char* dest){
    int size = 0;
    for (int i = 0; *input != '>'; input++ and i++){
        dest[i] = *input;
        size++;
    }
    dest[size] = '\0';
}

bool
isValidHtml(char* html) {
    CustomStack stack;
    char* tag = nullptr;
    char tmp[3001];
    while (*html) {
        if (*html == '<') {
            if (*(html + 1) == '/') {
                html++; // skip '/'
                html++; // move to tag name
                tag = stack.top();
                gettag(html, tmp);

                if (tag && strcmp(tag, tmp) == 0) {
                    stack.pop();
                } else {
                    return false;
                }
            } else {
                html++; // move to tag name
                gettag(html, tmp);
                if (strcmp(tmp, "br") and strcmp(tmp, "hr")) {
                    stack.push(tmp);
                }
            }
        }

        html++;
    }

    return stack.empty();
}