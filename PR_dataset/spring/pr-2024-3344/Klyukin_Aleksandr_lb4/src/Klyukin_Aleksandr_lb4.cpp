class CustomStack{
public:
	CustomStack(size_t initialCapacity){
		this->mCapacity = initialCapacity;
		this->mData = new char *[initialCapacity];
		this->mIndex = -1;
	}
	CustomStack() : CustomStack(10)
	{
		// 10 -- начальный размер стека, вызов другого конструктора
	}

	~CustomStack(){
		delete[] this->mData;
	}

	void push(const char *val){
		this->ensureSpace(); // проверка, что размера массива достаточно для нового элемента
		this->mIndex++;
		mData[this->mIndex] = new char[strlen(val) + 1];

		strcpy(mData[this->mIndex], val);
	}

	void pop(){
		if (this->empty()){
			throw logic_error("pop() called on empty stack");
		}
		this->mIndex--; // “удаление” элемента
	}

	char *top(){
		return this->mData[this->mIndex];
	}

	size_t size() const{
		return this->mIndex + 1;
	}

	bool empty() const{
		return this->mIndex == -1;
	}

	void extend(int n){
		if (n <= 0){
			throw logic_error("extend() called with a nonpositive argument");
		}
		this->resize(this->mCapacity + n);
	}

protected:
	size_t mCapacity;
	size_t mIndex;
	char **mData;

	size_t getNewCapacity() const{
		// получение нового размера
		return this->mCapacity * 3 / 2 + 1;
	}

	void ensureSpace()
	{
		if (this->mIndex + 1 == mCapacity){
			// если достигнут максимальный размер
			size_t newCapacity = this->getNewCapacity();
			this->resize(newCapacity);
		}
	}

	void resize(size_t newCapacity)
	{
		if (newCapacity == mCapacity){
			return;
		}
		char **newData = new char *[newCapacity];
		copy(this->mData, this->mData + this->mCapacity, newData); // копирование данных при помощи функции из заголовочного файла<algorithm>
		delete[] this->mData;
		this->mData = newData;
		this->mCapacity = newCapacity;
	}
};

int main()
{
	CustomStack p;
	char *text, *tag;
	int flag = 0, tagLen = 0;
	text = new char[3001];
	tag = new char[3001];
	fgets(text, 3000, stdin);

	for (size_t i = 0; i < strlen(text); i++){
		if (text[i] == '<'){
			flag = 1;
		}
		else if (flag == 1 && text[i] == '/'){
			flag = 2;
		}
		else if (text[i] == '>'){
			tag[tagLen] = '\0';
			if (flag == 1 && (strcmp("<hr", tag) != 0 && strcmp("<br", tag) != 0)){
				p.push(tag);
			}
			else if (flag == 2){
				for (size_t j = 1; j < strlen(p.top()); j++){
					if (tag[j + 1] != p.top()[j]){
						cout << "wrong" << endl;
						return 0;
					}
				}
				p.pop();
			}

			flag = 0;
			tagLen = 0;
		}

		if (flag != 0){
			tag[tagLen++] = text[i];
		}
	}
	cout << "correct" << endl;


	return 0;
}