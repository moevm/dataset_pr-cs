class CustomStack {
public:

	CustomStack() {
		this->mHead = nullptr;
	}

	~CustomStack() {
		delete this->mHead;
	}

	void push(int data) {
		ListNode* element = new ListNode();
		element->mData = data;
		element->mNext = this->mHead;
		this->mHead = element;
	}

	void pop() {
		if (this->empty()) {
			this->error();
		}
		this->mHead = this->mHead->mNext;
	}

	int top() {
		if (this->empty()) {
			this->error();
		}
		return this->mHead->mData;
	}

	size_t size() {
		ListNode* curr = mHead;
		size_t size = 0;
		while (curr != nullptr) {
			curr = curr->mNext;
			size++;
		}
		return size;
	}

	bool empty() {
		return (this->mHead == nullptr);
	}

	void print() {
		if (this->size() == 1) {
			cout << this->top() << endl;
		}
		else {
			this->error();
		}
	}

private:

	void error() {
		cout << "error" << endl;
		exit(0);
	}

protected:

	ListNode* mHead;

};

int operate(int a, int b, string sign) {
	if (sign == "+") {
		return b + a;
	}
	else if (sign == "-") {
		return b - a;
	}
	else if (sign == "*") {
		return b * a;
	}
	else {
		return b / a;
	}
}

string input() {
	string inp;
	getline(cin, inp);
	return inp;
}

void process(CustomStack& stack) {
	string inp = input();
	istringstream stream(inp);
	string symbol;

	while (stream >> symbol) {
		try {
			int result = stoi(symbol);
			stack.push(result);
		}
		catch (invalid_argument e) {
			string sign = symbol;
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			int result = operate(a, b, sign);
			stack.push(result);
		}
	}
	stack.print();
}

int main()
{
	CustomStack stack;
	process(stack);
	return 0;
}
