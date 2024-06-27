constexpr int const SIZE = 1;

class CustomStack {
protected:
    int* mData;

private:
    size_t count;
    int sz;

public:
    CustomStack() {
        this->count = 0; 
        this->sz = SIZE;
        this->mData = new int[sz];
    }

    ~CustomStack() {
        delete[] this->mData;
    }

    void push(int val) {
        if (this->count == this->sz)
            extend(1);
        this->mData[this->count++] = val;
    }

    void pop() {
        this->mData[this->count-1] = 0;
        this->count--;
    }

    int top() {
        if (this->count > 0)
            return this->mData[this->count-1];
        throw out_of_range("Stack is empty");
    }

    size_t size() {
        return this->count;
    }

    bool empty() {
        return this->count == 0;
    }

    void extend(int n) {
        this->sz += n;
        int* new_ptr = new int[sz];
        for (int i = 0; i < this->count; i++) 
            new_ptr[i] = this->mData[i];
        delete[] this->mData;
        this->mData = new_ptr;
    }
};

int main() {
    CustomStack st;

    while (1) {
        string cmd;
        cin >> cmd;

        if (cmd == "cmd_push") {
            try {
                int n;
                cin >> n;
                st.push(n);
                cout << "ok" << endl;
            } catch (const bad_alloc& err) {       
                cout << "error" << endl;
                break;
            }
        }
        if (cmd == "cmd_pop") {
            try {
                cout << st.top() << endl;
                st.pop();
            } catch(const out_of_range& err) {
                cout << "error" << endl;
                break;
            }
        }
        if (cmd == "cmd_top") {
            try {
                cout << st.top() << endl;
            } catch(const exception& err) {
                cout << "error" << endl;
                break;
            }
        }
        if (cmd == "cmd_size") {
            cout << st.size() << endl;
        }
        if (cmd == "cmd_exit") {
            cout << "bye" << endl;
            break;
        }
    }
    return 0;
}
