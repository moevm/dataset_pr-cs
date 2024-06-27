int index_first_zero(int arr[], int arr_len) {
    int number;
    for (int i=0; i < arr_len; i++) {
        if (arr[i] == 0) {
            number = i;
            break;
        }
    }
    return number;
}