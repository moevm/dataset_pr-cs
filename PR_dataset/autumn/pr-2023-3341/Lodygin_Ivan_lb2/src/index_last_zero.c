int index_last_zero(int arr[], int arr_len) {
    int number;
    for (int i=0; i < arr_len; i++) {
        if (arr[i] == 0) {
            number = i;
        }
    }
    return number;
}