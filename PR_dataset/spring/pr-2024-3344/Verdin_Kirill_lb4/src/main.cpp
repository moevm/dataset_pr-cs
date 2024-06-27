#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::string;
using std::realloc;

class CustomStack
{
public:
	CustomStack()
	{
		mDataSize = 0;
		mDataCapacity = 100;
		mData = new char *[mDataCapacity];
	}

	~CustomStack()
	{
		for (size_t i = 0; i < mDataSize; i++)
			delete[] mData[i];
		delete[] mData;
	}

	void push(const char *val)
	{
		if (mDataCapacity < mDataSize + 1)
			extend(10);
		mData[mDataSize] = new char[strlen(val) + 1];
		strcpy(mData[mDataSize++], val);
	}

	void pop()
	{
		delete[] mData[mDataSize - 1];
		mDataSize--;
	}

	char *top()
	{
		return mData[mDataSize - 1];
	}

	size_t size()
	{
		return mDataSize;
	}

	bool empty()
	{
		return mDataSize == 0;
	}

	void extend(int n)
	{
		mDataCapacity += n;
		mData = (char**)realloc(mData, sizeof(char*) * mDataCapacity);
	}

	void print()
	{
		for (int i = mDataSize - 1; i >= 0; i--)
		{
			cout << mData[i] << '\n';
		}
	}

protected:
	size_t mDataSize;
	size_t mDataCapacity;
	char **mData;
};

bool isVoidElement(char *el)
{
	if (strcmp(el, "br") == 0 || strcmp(el, "hr") == 0)
		return true;
	return false;
}

bool isValidHtml(CustomStack &stack)
{
	CustomStack newstack;
	while (!stack.empty())
	{
		char *top = stack.top();
		if (strchr(stack.top(), '/'))
		{
			newstack.push(top);
			stack.pop();
		}
		else if (!newstack.empty() && strstr(newstack.top(), top))
		{
			stack.pop();
			newstack.pop();
		}
		else if (isVoidElement(top))
			stack.pop();
		else
			return false;
	}
	return true;
}

int main()
{
	CustomStack stack;
	string line;
	for (string line; getline(cin, line, '>');)
	{
		if (line.find("<") != std::string::npos)
		{
			stack.push(line.substr(line.find("<") + 1).data());
		}
	}
	if (isValidHtml(stack))
		cout << "correct\n";
	else
		cout << "wrong\n";
	return 0;
}