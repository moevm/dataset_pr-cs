int index_first_negative(int arr[], int arr_len){
    int index = -1;
    for (int i = 0; i < arr_len; i++) {
        if (arr[i] < 0) {
            index = i;
            break;
        }
    }
    return index;
}