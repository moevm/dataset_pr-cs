#include <iostream>
#include <cstring>

#define MAX_STR_SIZE 3000     // максимальный размер html кода
#define MAX_TAG_SIZE 100      // максимальный размер тега
#define BLOCK        5        // выделяемое за раз количество памяти в массиве стека

enum class TagType: int {Opener = 1, Closing = 0};

class CustomStack {	
public:
	CustomStack()
	{
		this->stack_size = 0;
		this->alloc_size = 0;
		this->mData = nullptr;
	}
	~CustomStack()
	{
		if (alloc_size) {
			for (size_t i = 0; i < stack_size; i++)
				delete this->mData[i];
			delete[] this->mData;
		}
	}
	void push(const char* val)
	{
		// добавляем памяти в массив, если её не хватает
		if (alloc_size <= stack_size) {
			this->extend(BLOCK);
		}
		this->mData[stack_size] = strdup(val);
		if (!this->mData[stack_size])
			fprintf(stderr, "Error while diplicating tag string\n");

		this->stack_size++;
	}
	void pop()
	{
		if (this->empty())
			printf("pop(): The stack is empty!\n");
		else {
			free(this->mData[stack_size - 1]);
			this->mData[stack_size - 1] = nullptr;
			this->stack_size--;
		}
	}
	char* top()
	{
		if (this->empty())
			return nullptr;
		return this->mData[stack_size - 1];
	}
	size_t size()
	{
		return this->stack_size;
	}
	bool empty()
	{
		return (this->stack_size == 0) ? true : false;
	}
	void extend(const int n)
	{
		// выделяем место под расширенный массив
		const size_t new_alloc_size = this->alloc_size + n;
		char **extended_mData;
		try {
			extended_mData = new char*[new_alloc_size];
		} catch (std::bad_alloc& ba) {
			fprintf(stderr, "extend function error: %s\n", ba.what());
		}

		// заполняем новый массив
		for (size_t i = 0; i < new_alloc_size; i++) {
			if (i < stack_size) {
				extended_mData[i] = this->mData[i];
			} else {
				extended_mData[i] = nullptr;
			}
		}

		// очищаем память старого массива и обновляем поля
		delete[] this->mData;
		this->mData = extended_mData;
		this->alloc_size = new_alloc_size;
	}
private:
	size_t stack_size;
	size_t alloc_size;
protected:
	char **mData;
};

int main()
{
	CustomStack *stack = new CustomStack();

	// выделяем место под html код и под строку для хранения тега
	char *html_code;
	char *tag_str;
	try {
		html_code = new char[MAX_STR_SIZE];
	} catch(std::bad_alloc& ba) {
		fprintf(stderr, "main function error: %s\n", ba.what());
	}

	size_t html_ind = 0;
	size_t tag_size = 0;

	bool in_tag = false;
	bool identity = true;
	bool incor_plmnt = false;

	fgets(html_code, MAX_STR_SIZE, stdin);
	size_t html_code_size = strlen(html_code);
	
	// убираем \n с конца строки (если он есть)
	if (html_code[html_code_size - 1] == '\n') {
		html_code[html_code_size - 1] = '\0';
		html_code_size--;
	}

	while (html_ind < html_code_size) {
		in_tag = (html_code[html_ind] == '<') ? true : false;
		if (in_tag) {
			try {
				tag_str = new char[MAX_TAG_SIZE];
			} catch (std::bad_alloc& ba) {
				fprintf(stderr, "main function error: %s\n", ba.what());
			}
			
			while (in_tag) {
				tag_str[tag_size] = html_code[html_ind];
				if (tag_str[tag_size] == '>' || html_ind == html_code_size) {
					in_tag = false;
					tag_str[tag_size + 1] = '\0';
				}

				tag_size++;
				html_ind++;
			}

			// выясняем тип тега
			TagType type = (!strstr(tag_str, "</")) ? TagType::Opener : TagType::Closing;
			// если открывающий - добавляем в стек, иначе проверяем что тег есть в стеке
			if (type == TagType::Opener && strcmp(tag_str, "<hr>") && strcmp(tag_str, "<br>"))
				stack->push(tag_str);
			else if (type == TagType::Closing) {
				// если стек пуст, но есть закрывающий тег - неверная расстановка
				if (stack->empty()) {
					incor_plmnt = true;
					free(tag_str);
					break;
				}

				char *top = stack->top();
				size_t top_size = strlen(top);
				if (top_size == tag_size - 1) {
					for (size_t i = 1; i < top_size; i++) {
						// если теги имеют разные названия - неверная расстановка
						if (top[i] != tag_str[i + 1]) {
							incor_plmnt = true;
							identity = false;
							break;
						}
					}
					if (identity)
						stack->pop();
				} else {
					// если открывающий и закрывающий теги имеют разные названия - неверная расстановка
					incor_plmnt = true;
					break;
				}
			}

			delete[] tag_str;
			tag_size = 0;
			identity = true;
			if (!identity)
				break;
		} else
			html_ind++;
	}
	if (!errno) {
		if (stack->empty() && !incor_plmnt)
			printf("correct\n");
		else if (!stack->empty() || incor_plmnt)
			printf("wrong\n");
	}

	delete stack;
	delete[] html_code;

	return 0;
}
