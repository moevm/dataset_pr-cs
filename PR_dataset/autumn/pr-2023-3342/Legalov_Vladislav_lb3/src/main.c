#include <stdio.h>
#include <stdlib.h>

#define BLOCK 10
#define LAST_STR "Количество предложений до %d и количество предложений после %d\n"
const size_t SIZE_POINTER_CHAR = sizeof(char*);

char* get_words(char *end_char){
	size_t size = 0, capacity = BLOCK;
	char* ans = malloc(BLOCK);
	char ch;
	while(1){
		if (size >= capacity - 1)
			ans = realloc(ans, (capacity = capacity + BLOCK));
		if (!ans)
			return NULL;
		ch = getchar();
		if ((ch == '\n') || (ch == '\t') || ((ch == ' ') && (size == 0)))
			continue;
		ans[size++] = ch;
		if ((ch == '.') || (ch == ';') || (ch == '?') || (ch == '!')){
			*end_char = ch;
			break;
		}
	}
	ans[size] = '\0';
	return ans;	
}

char** get_format_text(int *count_before, int *count_after){
	char** ans = malloc(BLOCK * SIZE_POINTER_CHAR);
	size_t size = 0, capacity = BLOCK;
	char ch;
	*count_before = 0;
	*count_after = 0;
	while (1){
		if (size >= capacity - 1)
			ans = realloc(ans, SIZE_POINTER_CHAR * (capacity = capacity + BLOCK));
		if (!ans)
			return NULL;
		ans[size++] = get_words(&ch);
		if (ch == '!')
			break;
		if (ch == '?'){
			++(*count_after);
			free(ans[size - 1]);
			ans[size - 1] = NULL;
		}			
	}
	*count_before = size - 1;
	*count_after = *count_before - *count_after;
	return ans;
}

void free_all(char **arr, int size){
	for (int i =0; i <= size; ++i)
		if (arr[i] != NULL)
			free(arr[i]);
	free(arr);
}

int main(){
	int count_before, count_after;
	char **res = get_format_text(&count_before, &count_after);
	for (int i =0; i <= count_before; ++i)
		if (res[i] != NULL)
			printf("%s\n", res[i]);
	printf(LAST_STR, count_before, count_after);
	free_all(res, count_before);
	return 0;
}
