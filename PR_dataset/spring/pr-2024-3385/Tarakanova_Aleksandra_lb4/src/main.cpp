class CustomStack {
public:
    CustomStack()
    {
        this->mData = new char*[mDataSize]; 
        topIndex = -1;
    }
    ~CustomStack()
    {
        delete[] mData;
    }

    
    void push(const char* val)
    {
        topIndex++;
        if (topIndex > mDataSize) {
            extend(mDataSize);
        }
        mData[topIndex] = new char[strlen(val) + 1];
        strcpy(mData[topIndex], val);
    }

    char* top()
    {
    	if(!empty()) 
    	{
		return mData[topIndex];
		}
    }

    char* pop()
    {
        return mData[topIndex--];
    }

    bool empty()
    {
        return topIndex == -1;
    }

    size_t size()
    {
        return topIndex + 1;
    }

    void extend(int n)
    {
        char** newData = new char*[mDataSize + n];
        for (size_t i = 0; i <= topIndex; ++i) {
            newData[i] = mData[i];
        }
        delete[] mData;
        mDataSize += n;
        mData = newData;
    }

protected:
    char** mData;
    int topIndex; 
    size_t mDataSize = 10; 
};

bool isBalanced(string line)
{
    int startIndex = line.find('<');
    int endIndex = line.find('>');
    CustomStack* stack = new CustomStack;

    while (startIndex != string::npos || endIndex != string::npos) {
        string tag = line.substr(startIndex + 1, endIndex - startIndex - 1);
        if (tag == "br" || tag == "hr") {
            line = line.substr(endIndex + 1);
            startIndex = line.find('<');
            endIndex = line.find('>');
            continue;
        }
        if (tag[0] != '/') { 
            stack->push(tag.c_str());

            line = line.substr(endIndex + 1);
            startIndex = line.find('<');
            endIndex = line.find('>');
            continue;
        }

        if (stack->empty()) {
            return false;
        }
        char* previous_tag = stack->pop();
        if (strcmp(previous_tag, tag.c_str() + 1) != 0) { 
            return false;
        }
        line = line.substr(endIndex + 1);
        startIndex = line.find('<');
        endIndex = line.find('>');
    }
}

int main()
{
    string line;
    getline(cin, line);

    if (isBalanced(line)) {
        cout << "correct";
    } else {
        cout << "wrong";
    }

    return 0;
}

