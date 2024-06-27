#define BLOCK 10

class CustomStack {
private:
    size_t dataSize;
    size_t memSize;

protected:
    int* mData;
    
public:
    CustomStack() {
        this->mData = (int *) malloc(BLOCK * sizeof(int));
        this->dataSize = 0;
        this->memSize = BLOCK;
    }
    
    ~ CustomStack() {
        free(this->mData);
    }

    void push(int val) {
        if (this->dataSize == this->memSize) {
            this->memSize += BLOCK;
            this->mData = (int *) realloc(this->mData, this->memSize * sizeof(int));
        }
        this->mData[this->dataSize++] = val;
    }

    void pop() {
        if (this->dataSize <= 0) throw 0;
        this->dataSize--;
    }

    int top() {
        if (this->dataSize <= 0) throw 0;
        return this->mData[this->dataSize - 1];
    }

    size_t size() {
        return this->dataSize;
    }

    bool empty() {
        return this->dataSize == 0;
    }

    void extend(int n) {
        if (n < 0) throw 0;
        this->memSize += n;
        this->mData = (int *) realloc(this->mData, this->memSize * sizeof(int));
    }
};

int main() {
    CustomStack stack;
    char str[200];

    fgets(str, 200, stdin);
    char* token = strtok(str, " ");
    int error = 0;

    while(token != NULL) {
        try {
            if (atoi(token) != 0 || strstr("0", token))
                stack.push(atoi(token));

            else if (strstr("+-*/", token) && stack.size() > 1) {
                int a = stack.top();
                stack.pop();

                int b = stack.top();
                stack.pop();

                if (strstr(token, "+"))
                    stack.push(a + b);

                if (strstr(token, "-"))
                    stack.push(b - a);
                
                if (strstr(token, "*"))
                    stack.push(a * b);

                if (strstr(token, "/"))
                    stack.push(b / a);
            }
            else throw 0;
            token = strtok(NULL, " ");
        }
        catch (int e) {
            error = 1;
            break;
        }
    }
    
    if (stack.size() > 1) error = 1;

    if(error) printf("error\n");
    else printf("%d\n", stack.top());

    return 0;
}