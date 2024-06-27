

class CustomStack{
public:

    CustomStack()
    {
        this->stackSize = 0;
        this->mHead = NULL;

    }

    void push(int val)
    {
        ListNode* newElement = new ListNode();
        
        
        if(newElement == nullptr)
    {
        cout << "Memory error\n";
        exit(1);
    }


        newElement->mNext = NULL;
        newElement->mData = val;

        if (this->empty())
        {
            this->mHead = newElement;
        } else
        {
            ListNode* tempNode = mHead;
            while(tempNode->mNext!=NULL)
            {
                tempNode = tempNode->mNext;
            }
            tempNode->mNext = newElement;

        }
        this->stackSize ++;
    }

    void pop()
    {
        if (this->empty())
        {
            cout << "error";
            exit(0);

        } else if (this->stackSize == 1)
        {
            delete this->mHead;
            this->stackSize --;
        }
        else
        {
            ListNode* tempNode = mHead;
            while(tempNode->mNext->mNext!=NULL)
            {
                tempNode = tempNode->mNext;
            }
            delete tempNode->mNext;
            tempNode->mNext = NULL;
            this->stackSize--;
        }
    }

    int top()
    {
        if (this->empty())
        {
            cout << "error";
            exit(0);

        }

        ListNode* tempNode = mHead;
        while(tempNode->mNext!=NULL)
        {
            tempNode = tempNode->mNext;
        }
        return tempNode->mData;
    }

    size_t size()
    {
        return this->stackSize;
    }

    bool empty()
    {
        return (this->stackSize == 0);
    }

    ~CustomStack()
    {
        if (this->empty())
        {
            return;
        } else
        {
            ListNode* tempNode = mHead;
            while(tempNode->mNext!=NULL)
            {
                ListNode* removeNode = tempNode;
                tempNode = tempNode->mNext;
                delete removeNode;
            }

        }
    }


private:
size_t stackSize;

protected:
    ListNode* mHead;

};

vector<string> split(const string &str, char separator) {
    vector<string> result;
    stringstream ss(str);
    string buffer;

    while (getline(ss, buffer, separator)) {
        result.push_back(buffer);
    }

    return result;
}


int main() {

    bool okFlag = true;

    CustomStack *stack = new CustomStack();

    if(stack == nullptr)
    {
        cout << "Memory error\n";
        exit(1);
    }


    string text;

    getline(cin, text);
    vector<string> arr = split(text, ' ');

    for (int i = 0; i < arr.size(); ++i) {

        if (arr[i] == "+" || arr[i] == "-" || arr[i] == "*" || arr[i] == "/") {
            if (stack->empty()) {
                okFlag = false;
                break;
            }
            int rightOperand = stack->top();
            stack->pop();
            int leftOperand = stack->top();
            stack->pop();

            int result;
            if (arr[i] == "+") {
                result = leftOperand + rightOperand;
            } else if (arr[i] == "-") {
                result = leftOperand - rightOperand;
            } else if (arr[i] == "*") {
                result = leftOperand * rightOperand;
            } else {
                result = leftOperand / rightOperand;
            }
            stack->push(result);


        } else {
            stack->push(stoi(arr[i]));
        }

       
    }

    if (!okFlag || stack->size()!=1) {
        cout << "error";

    } else
    {
        cout << stack->top();
    }



    delete stack;

    return 0;
}
