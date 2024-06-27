#include <stdio.h>

int max(int arr[100], int arr_len);
int min(int arr[100], int arr_len);
int diff(int arr[100], int arr_len);
int sum(int arr[100], int arr_len);

int main() {
  
  int func_num;
  int arr[100];
  scanf("%d ", &func_num);
  char cur_char;
  scanf("%c", &cur_char);
  int arr_len = 0;
  for (int i = 0; i < 100; i++){
    arr[i] = 0;
  }
  int flag = 1;
  for (int i = 1; cur_char != '\n'; i++) {
    if (cur_char == '\n') {
        break;
    }
    else{
        if (cur_char == ' ') {
            arr_len += 1;
            flag = 1;
        }
        else if (cur_char == '-'){
            flag = -1;
        }
        else{
            arr[arr_len] *= 10;
            arr[arr_len] += flag*(cur_char - '0');
        }
    }
    scanf("%c", &cur_char);;
  }
  arr_len += 1;
  switch (func_num)
  {
  case 0:
    printf("%d\n", max(arr, arr_len));
    break;
  case 1:
    printf("%d\n", min(arr, arr_len));
    break;
  case 2:
    printf("%d\n", diff(arr, arr_len));
    break;
  case 3:
    printf("%d\n", sum(arr, arr_len));
    break;
  default:
    printf("Данные некорректны\n");
    break;
  }
  return 0;
}

int max(int arr[100], int arr_len){
    int mx = arr[0];
    for (int i = 1; i<arr_len; ++i) {
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }
    return mx;
}

int min(int arr[100], int arr_len){
    int mn = arr[0];
    for (int i = 1; i<arr_len; i++) {
        if (arr[i] < mn) {
            mn = arr[i];
        }
    }
    return mn;
}

int diff(int arr[100], int arr_len) {
    int mx = max(arr, arr_len);
    int mn = min(arr, arr_len);
    return (mx-mn);
}

int sum(int arr[100], int arr_len) {
    int mn = min(arr, arr_len);
    int sum_arr = 0;
    for (int i = 0; i<arr_len; i++) {
      if (arr[i] == mn) {
        return sum_arr;
      }
      sum_arr += arr[i];
    }
}



