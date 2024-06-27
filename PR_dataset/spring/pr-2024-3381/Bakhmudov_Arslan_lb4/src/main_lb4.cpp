#define SIZE 128



class CustomStack
{
	private:
		bool dead;

    public:

        CustomStack()
        {
        	mHead = NULL;
        	dead = false;
        }

        ~ CustomStack()
        {
        	ListNode * tmp = NULL;
        	while(this->mHead != NULL)
        	{
           		tmp = this->mHead->mNext;
        		delete this->mHead;
        		this->mHead = tmp;
        	}
        }

        void error()
        {
        	printf("error\n");
        	this->dead = true;
        }


        bool isdead()
        {
        	return this->dead;
        }


        size_t size()
        {
        	size_t c = 0;
        	ListNode * head = this->mHead;
        	while (head != NULL)
        	{
        		head = head->mNext;
        		c++;
        	}
        	return c;
        }

        ListNode * getNodePointer(int index)
        {
        	if (index < 0) return NULL;
        	int i = 0;
        	ListNode * head = this->mHead;
        	while (i < index)
        	{
        		if (head == NULL) return NULL;
        		head = head->mNext;
        		i++;
        	}
        	return head;
        }

        int top()
        {
        	ListNode * tail = this->getNodePointer(this->size() - 1);
        	if (tail == NULL) {this->error(); return 0;}
        	return tail->mData;
        }

        void pop()
        {
        	ListNode * prev = this->getNodePointer(this->size() - 2);
        	if (prev == NULL)
        	{
        		if (this->mHead == NULL) {this->error(); return;}
        		delete this->mHead;
        		this->mHead = NULL;
        		return;
        	}
        	delete prev->mNext;
        	prev->mNext = NULL;
        	return;
        }

        void push(int val)
       	{
       		ListNode * tail = this->getNodePointer(this->size() - 1);
       		if (tail == NULL)
       		{
       			this->mHead = new ListNode;
       			this->mHead->mData = val;
       			this->mHead->mNext = NULL;
       			return;
       		}
   			tail->mNext = new ListNode;
   			tail->mNext->mData = val;
   			tail->mNext->mNext = NULL;
   			return;
       	}

        bool empty()
        {
        	return (this->mHead == NULL);
        }

        void calculate(char operation)
        {
        	ListNode * resPointer = this->getNodePointer((int)(this->size()) - 2);
        	if (resPointer == NULL) {this->error(); return;}
        	switch (operation)
        	{
	        	case '+':
	        		resPointer->mData += resPointer->mNext->mData;
	        		break;

        		case '-':
	        		resPointer->mData -= resPointer->mNext->mData;
	        		break;

        		case '*':
	        		resPointer->mData *= resPointer->mNext->mData;
	        		break;

        		case '/':
	        		resPointer->mData /= resPointer->mNext->mData;
	        		break;
        	}
        	delete resPointer->mNext;
        	resPointer->mNext = NULL;
        }

    protected:
        ListNode * mHead;
};



int main()
{
	char input[SIZE];
	char * ip = input;
	int curr_sym = 0;
	CustomStack * stack = new CustomStack;

	while (true)
	{
		char c = getchar();
		if (isspace(c) || c == '\n')
		{
			if (curr_sym == 1 && !isdigit(input[0]))
			{
				stack->calculate(input[0]);
				input[curr_sym] = '\0';
				curr_sym = 0;
			}
			else if (curr_sym > 0)
			{
				input[curr_sym] = '\0';
				stack->push(strtol(ip, &ip, 10));
				ip = input;
				curr_sym = 0;
			}
		}
		else
		{
			input[curr_sym] = c;
			curr_sym++;
		}
		if (stack->isdead())
		{
			delete stack;
			return 0;
		}
		else if (c == '\n')
		{
			break;
		}
	}
	if (stack->size() == 1)
	{
		printf("%d\n", stack->top());
	}
	else
	{
		stack->error();
	}
	delete stack;
	return 0;
}
