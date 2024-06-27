int index_last_negative(int arr[], int arr_len) {
    int index = -1;
    for (int i = arr_len; i >0; i--) {
        if (arr[i] < 0) {
            index = i;
            break;
        }
    }
    return index;
}
