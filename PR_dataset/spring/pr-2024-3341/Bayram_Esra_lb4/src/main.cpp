#define MAX_STR_SIZE 3000

class CustomStack {
public:
	CustomStack()
	{
		mHead = nullptr;
	}

	~CustomStack()
	{
		while (mHead != nullptr) pop();
	}

	void push(const char *tag)
	{
		auto *NewNode = new ListNode;
		NewNode->mData = new char[strlen(tag) + 1];

		strcpy(NewNode->mData, tag);
		NewNode->mNext = mHead;
		mHead = NewNode;
	}

	void pop()
	{
		if (mHead != nullptr)
		{
			ListNode *tmp = mHead;

			mHead = mHead->mNext;
			delete[] tmp->mData;
			delete tmp;
		}
	}

	char *top()
	{
		return mHead != nullptr ? mHead->mData : nullptr;
	}

	size_t size()
	{
		size_t size = 0;

		for (ListNode *tmp = mHead; tmp != nullptr; tmp = tmp->mNext, size++);

		return size;
	}

	bool empty()
	{
		return size() == 0;
	}

protected:
	ListNode *mHead;
};

char *getTag(char *str)
{
	static char *localStr = nullptr;
	if (str != nullptr) localStr = str;
	char *startPos = localStr != nullptr ? strchr(localStr, '<') : nullptr;
	localStr = startPos != nullptr ? strchr(startPos, '>') : nullptr;

	if (localStr != nullptr)
		*(localStr++) = '\0';
	else
		return nullptr;

	return startPos + 1;
}

bool checkHtmlCode(char *htmlCode)
{
	CustomStack TagStack;

	for (char *tag = getTag(htmlCode); tag != nullptr; tag = getTag(nullptr))
	{
		if (*tag != '/')
		{
			if (strcmp(tag, "br") != 0 && strcmp(tag, "hr") != 0) TagStack.push(tag);
		}
		else
		{
			if (TagStack.top() != nullptr && strcmp(TagStack.top(), tag + 1) == 0) TagStack.pop();
			else return false;
		}
	}

	return TagStack.empty();
}

int main()
{
	char htmlCode[MAX_STR_SIZE];
	cin.getline(htmlCode, MAX_STR_SIZE);

	cout << (checkHtmlCode(htmlCode) ? "correct" : "wrong");

	return 0;
}