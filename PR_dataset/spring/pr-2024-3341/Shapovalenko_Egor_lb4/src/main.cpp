#define HR_TAG "hr"
#define BR_TAG "br"
#define OPEN_TAG '<'
#define CLOSE_TAG '>'
#define CLOSING_TAG_SLASH '/'
#define TAG_OFFSET 1
#define NULL_CH_BUFFER_SIZE 1
#define CMP_OFFSET 1

const char *correct_answer = "correct";
const char *wrong_answer = "wrong";

class CustomStack {
public:
    CustomStack() {
        this->mHead = nullptr;
    }

    void push(const char *data) {
        ListNode* newNode = new ListNode;
        
        newNode->mData = new char[strlen(data) + NULL_CH_BUFFER_SIZE];
        strcpy(newNode->mData, data);
        
        newNode->mNext = this->mHead;
        this->mHead = newNode;
    }

    void pop() {
        if (!this->empty()) {
			ListNode* tmp = this->mHead;
			this->mHead = this->mHead->mNext;

			delete[] tmp->mData;
			delete tmp;
		}
    }

    size_t size() {
        ListNode* tmp = this->mHead;
        size_t counter = 0;

        while (tmp) {
            counter++;
            tmp = tmp->mNext;
        }

        return counter;
    }

    bool empty() {
        return this->mHead == nullptr;
    }

    char* top() {
        if (this->empty())
            return nullptr;

        return this->mHead->mData;
    }

    ~CustomStack() {
        while (!this->empty())
			this->pop();
    }

protected:
    ListNode* mHead;
};

int main() {
    std::string buffer;
    getline(cin, buffer);

    CustomStack stack;

    for (size_t i = 0; i < buffer.size(); i++) {
        if (buffer[i] == OPEN_TAG) {
            size_t len = 1;

            while (buffer[i + len + TAG_OFFSET] != CLOSE_TAG)
                len++;

            stack.push(buffer.substr(i + TAG_OFFSET, len).c_str());

            char *tag = new char[strlen(stack.top()) + NULL_CH_BUFFER_SIZE];
			strcpy(tag, stack.top());
            

            if (strcmp(tag, BR_TAG) == 0 || strcmp(tag, HR_TAG) == 0)
                stack.pop();
            else {
                if (stack.size() >= 2) {
                    stack.pop();
 
                    if (strcmp(tag + CMP_OFFSET, stack.top()) == 0 && tag[0] == CLOSING_TAG_SLASH)
                        stack.pop();
                    else
                        stack.push(tag);
                }
            }
			
			delete[] tag;
        }
    }

    if (stack.empty())
        std::cout << correct_answer << endl;
    else
        std::cout << wrong_answer << endl;

	return 0;
}