#define STACK_DEFAULT_SIZE 10

class CustomStack {

  public:
    CustomStack() {
        this->mIndex = -1;
        this->mCapacity = STACK_DEFAULT_SIZE;
        this->mData = (int*)malloc(this->mCapacity * sizeof(int));
    }

    ~CustomStack() { free(mData); }

    void
    push(int val) {
        if (size() == this->mCapacity) {
            this->mCapacity += STACK_DEFAULT_SIZE;
            this->mData = (int*)realloc(this->mData, this->mCapacity * sizeof(int));
        }
        this->mData[++(this->mIndex)] = val;
    }

    void
    pop() {
        if (empty()) {
            throw 1;
        }
        this->mIndex -= 1;
    }

    int
    top() {
        if (empty()) {
            throw 2;
        }
        return this->mData[this->mIndex];
    }

    size_t
    size() {
        return this->mIndex + 1;
    }

    bool
    empty() {
        return this->mIndex == -1;
    }

    void
    extend(int n) {
        if (n <= 0) {
            throw 3;
        }
        this->mCapacity += n;
        this->mData = (int*)realloc(this->mData, mCapacity * sizeof(int));
    }

  private:
    size_t mIndex;
    size_t mCapacity;

  protected:
    int* mData;
};

int
main() {
    CustomStack stack = CustomStack();
    char buffer[51];
    while (fgets(buffer, 51, stdin)) {
        try {
            if (strstr(buffer, "cmd_push")) {
                int a;
                sscanf(buffer, "cmd_push %d", &a);
                stack.push(a);
                cout << "ok" << endl;
            } else if (strstr(buffer, "cmd_pop")) {
                cout << stack.top() << endl;
                stack.pop();
            } else if (strstr(buffer, "cmd_top")) {
                cout << stack.top() << endl;
            } else if (strstr(buffer, "cmd_size")) {
                cout << stack.size() << endl;
            } else if (strstr(buffer, "cmd_exit")) {
                cout << "bye" << endl;
                break;
            } else {
                throw 4;
            }
        } catch (int e) {
            cout << "error" << endl;
            break;
        }
    }
    return 0;
}